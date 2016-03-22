package main

import (
	"encoding/base64"
	"flag"
	"fmt"
	"image"
	"image/color"
	"image/png"
	"io"
	"log"
	"net/http"
	"net/url"
	"os"
	"os/exec"
	"strconv"
	"strings"
	"time"

	"parallel"
	"render"
)

const (
	maxWitdh  = 1 << 12
	maxHeight = 1 << 12
)

var (
	port      = flag.Int("port", 7777, "")
	addr      = flag.String("addr", "", "address of local render server")
	addrs     = flag.String("addrs", "", "addresses of render servers")
	batchSize = flag.Int("b", 64, "batch row count")
)

type img struct {
	Width  uint16
	Height uint16
	bs     []byte
}

func (i *img) Bounds() image.Rectangle {
	return image.Rectangle{image.ZP, image.Pt(int(i.Width), int(i.Height))}
}

func (i *img) At(x, y int) color.Color {
	var r, g, b, a uint8 = 127, 0, 0, 255
	if len(i.bs) > 0 {
		idx := ((int(i.Height)-1-y)*int(i.Width) + int(x)) * 3
		r = i.bs[idx]
		g = i.bs[idx+1]
		b = i.bs[idx+2]
	}
	return color.RGBA{r, g, b, a}
}

func (i *img) ColorModel() color.Model { return color.RGBAModel }

type server struct {
	*render.Client
	ss []*render.Client
}

func (s *server) handleIndex(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, `<!doctype html><html><head></head><body>
<a href="/examples">examples</a><br>
<a href="/proxy">proxy</a><br>
<a href="/ping">ping</a><br>
<a href="/register">register</a><br>
</body></html>`)
}

func (s *server) examples(w http.ResponseWriter, r *http.Request) {
	if err := exec.Command("ruby", "gen/examples.rb").Run(); err != nil {
		log.Printf("%v", err)
	}
	if f, err := os.Open("examples.html"); err == nil {
		io.Copy(w, f)
	}
}

func (s *server) parse(r *http.Request) ([]string, *img) {
	vals, _ := url.ParseQuery(r.URL.RawQuery)
	var wi, hi uint16 = 1024 / 2, 768 / 2
	i := &img{wi, hi, nil}
	var args []string
	{
		if c := vals.Get("c"); c != "" {
			args = append(args, "-c", c)
		}
	}
	{
		if w, _ := strconv.Atoi(vals.Get("w")); 0 < w && w <= maxWitdh {
			i.Width = uint16(w)
		}
		if h, _ := strconv.Atoi(vals.Get("h")); 0 < h && h <= maxHeight {
			i.Height = uint16(h)
		}
		args = append(args, "-d", fmt.Sprintf("%dX%d", i.Width, i.Height))
	}
	{
		for _, l := range vals["l"] {
			args = append(args, "-l", l)
		}
		for _, m := range vals["m"] {
			args = append(args, "-m", m)
		}
	}
	{
		if n, _ := strconv.Atoi(vals.Get("n")); 0 < n && n <= 6 {
			args = append(args, "-n", strconv.Itoa(n))
		}
	}
	return args, i
}

func (s *server) help(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "text/plain")
	a, _ := s.parse(r)
	if s.Client != nil {
		fmt.Fprintf(w, "%s\r\n", s.Explain(a))
	} else {
		for _, c := range s.ss {
			fmt.Fprintf(w, "# remote %s\r\n", c.Addr)
			//fmt.Fprintf(w, "%s\r\n", c.Explain(a))
		}
	}
}

func (s *server) proxyImage(w http.ResponseWriter, r *http.Request) {
	log.Printf("proxy image")
	w.Header().Set("Content-Type", "image/png")
	a, i := s.parse(r)
	a = append(a, "no-bmp-header")
	a = append(a, "no-bmp-padding")

	all := make([]byte, int(i.Height)*int(i.Width)*3)
	work := func(j, k int, c *render.Client) {
		b := append(a, "-e")
		p := fmt.Sprintf("%d-%d,%d-%d", 0, i.Width, j, k)
		log.Printf("rendering clip %s", p)
		b = append(b, p)
		bs := c.Render(b)
		l1, l2 := len(bs), int(i.Width)*(k-j)*3
		if l1 == l2 {
			off := j * int(i.Width) * 3
			for l := 0; l < l1; l++ {
				all[off+l] = bs[l]
			}
		} else {
			log.Printf("invalided length, want %d, got %d", l2, l1)
		}
	}

	var ts, te []int
	{
		d := *batchSize
		for j := 0; j < int(i.Height); j += d {
			k := j + d
			if k > int(i.Height) {
				k = int(i.Height)
			}
			ts = append(ts, j)
			te = append(te, k)
		}
	}
	begin := time.Now()
	parallel.Multi(len(s.ss), len(ts), func(j int, k int) { work(ts[j], te[j], s.ss[k]) })
	i.bs = all
	log.Printf("finish proxy image, took %s", time.Now().Sub(begin))
	png.Encode(w, i)
}

func (s *server) pass(w http.ResponseWriter, r *http.Request) {
	if s.Client == nil {
		return
	}
	str := r.Header.Get("X-rey-Pass")
	bs, _ := base64.StdEncoding.DecodeString(str)
	args := strings.Split(string(bs), "\r\n")
	pix := s.Client.Render(args)
	w.Header().Set("Content-Length", strconv.Itoa(len(pix)))
	w.Header().Set("Content-Type", "application/octet-stream")
	w.Header().Set("Content-Transfer-Encoding", "8BIT")
	w.Write(pix)
}

func (s *server) ping(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "text/plain")
	fmt.Fprintf(w, "OK\r\n")
	for _, c := range s.ss {
		if err := c.Ping(); err == nil {
			fmt.Fprintf(w, "%s OK\r\n", c.Addr)
		} else {
			fmt.Fprintf(w, "%s is down: %v\r\n", c.Addr, err)
		}
	}
}

func (s *server) register(w http.ResponseWriter, r *http.Request) {
	vals, _ := url.ParseQuery(r.URL.RawQuery)
	for a := range vals["a"] {
		log.Printf("register %q", a)
	}
	fmt.Fprintf(w, "TODO\r\n")
}

func init() { flag.Parse() }

func main() {
	var ss []*render.Client
	for _, a := range strings.Split(*addrs, ",") {
		if a == "" {
			continue
		}
		log.Printf("adding render server %q", a)
		c := render.New(a)
		c.BinMode = false
		c.PassMode = true
		ss = append(ss, c)
		if err := c.Ping(); err == nil {
			log.Printf("connected to %q", c.Addr)
		} else {
			log.Printf("%s is down: %v", c.Addr, err)
		}
	}
	var c *render.Client
	if *addr != "" {
		c = render.New(*addr)
	}
	s := &server{c, ss}
	http.HandleFunc("/", s.handleIndex)
	http.HandleFunc("/examples", s.examples)
	http.HandleFunc("/help", s.help)
	http.HandleFunc("/proxy", s.proxyImage)
	http.HandleFunc("/pass", s.pass)
	http.HandleFunc("/ping", s.ping)
	http.HandleFunc("/register", s.register)
	log.Printf("png proxy running at http://%s:%d/", "localhost", *port)
	log.Fatal(http.ListenAndServe(fmt.Sprintf(":%d", *port), nil))
}

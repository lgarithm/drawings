package main

import (
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
	"strconv"

	"render"
)

var (
	port = flag.Int("port", 7777, "")
	addr = flag.String("addr", "localhost:7778", "address of render server")
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

type server struct{ render.Client }

func (s *server) handleIndex(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, `<!doctype html><html><head></head><body>
<a href="/proxy">proxy</a><br>
<a href="/examples">examples</a><br>
</body></html>`)
}

func (s *server) examples(w http.ResponseWriter, r *http.Request) {
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
		if w, _ := strconv.Atoi(vals.Get("w")); 0 < w && w <= 4096 {
			i.Width = uint16(w)
		}
		if h, _ := strconv.Atoi(vals.Get("h")); 0 < h && h <= 4096 {
			i.Height = uint16(h)
		}
		args = append(args, "-d")
		args = append(args, fmt.Sprintf("%dX%d", i.Width, i.Height))
	}
	{
		if ls, ok := vals["l"]; ok && len(ls) > 0 {
			for _, l := range ls {
				args = append(args, "-l")
				args = append(args, l)
			}
		}
		if ms, ok := vals["m"]; ok && len(ms) > 0 {
			for _, m := range ms {
				args = append(args, "-m")
				args = append(args, m)
			}
		}
	}
	{
		if n, _ := strconv.Atoi(vals.Get("n")); 0 < n && n <= 6 {
			args = append(args, "-n")
			args = append(args, strconv.Itoa(n))
		}
	}
	return args, i
}

func (s *server) help(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "text/plain")
	a, _ := s.parse(r)
	usage := s.Explain(a)
	fmt.Fprintf(w, "%s\n", usage)
}

func (s *server) proxyImage(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "image/png")
	a, i := s.parse(r)
	a = append(a, "no-bmp-header")
	a = append(a, "no-bmp-padding")
	if bs := s.Render(a); len(bs) == int(i.Width)*int(i.Height)*3 {
		i.bs = bs
	} else {
		log.Printf("invalided length")
	}
	png.Encode(w, i)
}

func init() { flag.Parse() }

func main() {
	s := server{render.Client{*addr}}
	http.HandleFunc("/", s.handleIndex)
	http.HandleFunc("/examples", s.examples)
	http.HandleFunc("/help", s.help)
	http.HandleFunc("/proxy", s.proxyImage)
	log.Printf("png proxy running at http://%s:%d/", "localhost", *port)
	log.Fatal(http.ListenAndServe(fmt.Sprintf(":%d", *port), nil))
}

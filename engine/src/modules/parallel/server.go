package main

import (
	"flag"
	"fmt"
	"image"
	"image/color"
	"image/png"
	"log"
	"net/http"

	"render"
)

var (
	port = flag.Int("port", 7777, "")
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
		idx := (y*int(i.Width) + int(x)) * 3
		r = i.bs[idx]
		g = i.bs[idx+1]
		b = i.bs[idx+2]
	}
	return color.RGBA{r, g, b, a}
}
func (i *img) ColorModel() color.Model {
	return color.RGBAModel
}

type server struct{}

func (s *server) handleIndex(w http.ResponseWriter, r *http.Request) {
	fmt.Fprint(w, `<!doctype html><html><head></head></html>`)
}

func (s *server) handleImage(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "image/png")
	i := &img{1024 / 2, 768 / 2, nil}
	png.Encode(w, i)
}

func (s *server) proxyImage(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "image/png")
	var wi, hi uint16 = 1024 / 2, 768 / 2
	c := render.Client{"localhost:7778"}
	var args = []string{
		"no-bmp-header",
		"no-bmp-padding",
		"-d",
		fmt.Sprintf("%dX%d", wi, hi),
		"-l", "light((0,0,50), (.5, .5, .5))",
		"-m", "sphere(1, (0,0,1))",
		"-m", "floor",
		"-n", "3",
	}
	bs := c.Get(args)
	i := &img{wi, hi, bs}
	png.Encode(w, i)
}

func main() {
	s := server{}
	http.HandleFunc("/", s.handleIndex)
	http.HandleFunc("/image", s.handleImage)
	http.HandleFunc("/proxy", s.proxyImage)
	log.Printf("running at http://%s:%d/", "localhost", *port)
	log.Fatal(http.ListenAndServe(fmt.Sprintf(":%d", *port), nil))
}

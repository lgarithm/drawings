package main

import (
	"flag"
	"fmt"
	"io/ioutil"
	"os"

	"render"
)

var (
	addr = flag.String("addr", "localhost:7778", "address of render server")
)

func main() {
	names := []string{}
	n := 6
	for i := 0; i < n; i++ {
		names = append(names, fmt.Sprintf("output/%02d.bmp", i))
	}
	done := make(chan string, 40)
	for _, name := range names {
		go func(name string) { task(name); done <- name }(name)
	}
	for _ = range names {
		name := <-done
		fmt.Printf("%s is done\n", name)
	}
}

func task(name string) {
	c := &render.Client{*addr}
	w, h := 4096, 4096
	var args = []string{
		"-l", "light((0,0,50), (.5, .5, .5))",
		"-m", "sphere(1, (0,0,1))",
		"-m", "floor",
		"-n", "3",
		"-d", fmt.Sprintf("%dX%d", w, h),
	}
	bs := c.Render(args)
	if len(bs) != w*h*3+54 {
		fmt.Printf("invalied length\n")
		return
	}
	ioutil.WriteFile(name, bs, os.ModePerm)
}

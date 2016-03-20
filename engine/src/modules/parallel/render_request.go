package render

import (
	"fmt"
	"io"
	"log"
	"net"
)

type Client struct{ Addr string }

func (c *Client) Render(args []string) []byte {
	log.Printf("Connecting to %s", c.Addr)
	conn, err := net.Dial("tcp", c.Addr)
	if err != nil {
		log.Printf("dial error: %s", err)
		return nil
	}
	log.Printf("connection established")
	log.Printf("local addr: %s", conn.LocalAddr())
	log.Printf("remote addr: %s", conn.RemoteAddr())

	req := makeReq(args)
	fmt.Printf("%s\n", req)
	if _, err := conn.Write([]byte(req)); err != nil {
		log.Printf("error: %s", err)
		return nil
	}

	var tot int
	all := make([]byte, 1<<26)
	b := make([]byte, 1<<16)
	for {
		n, err := conn.Read(b)
		if err == io.EOF {
			break
		}
		if err != nil {
			break
		}
		for i := 0; i < n; i++ {
			all[tot] = b[i]
			tot++
		}
	}
	log.Printf("got %d\n", tot)
	return all[:tot]
}

func (c *Client) Explain(args []string) string {
	cmd := fmt.Sprintf("curl -sOJ %s/render \\\n", c.Addr)
	for _, a := range args {
		cmd += fmt.Sprintf("\t-H \"X-Rey: %s\" \\\n", a)
	}
	return cmd
}

func makeReq(args []string) string {
	req := "GET /render HTTP/1.1\r\n"
	req += "X-Rey: no-http-header\r\n"
	for _, a := range args {
		req += fmt.Sprintf("X-Rey: %s\r\n", a)
	}
	req += "\r\n"
	return req
}

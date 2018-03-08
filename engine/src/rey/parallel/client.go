package render

import (
	"compress/gzip"
	"encoding/base64"
	"fmt"
	"io/ioutil"
	"log"
	"net"
	"net/http"
	"net/url"
	"strings"
)

type Client struct {
	Addr             string
	BinMode          bool
	PassMode         bool
	passModeCompress bool
}

func New(addr string) *Client {
	log.Printf("adding client at %q", addr)
	if strings.HasPrefix(addr, "http://") || strings.HasPrefix(addr, "https://") {
		log.Printf("parsing %q as url", addr)
		u, err := url.Parse(addr)
		if err != nil {
			log.Printf("failed to parse url %q: %v", addr, err)
		}
		addr = u.Host
	}
	h, p, err := net.SplitHostPort(addr)
	if err != nil {
		h, p, err = net.SplitHostPort(addr + ":80")
	}
	return &Client{fmt.Sprintf("%s:%s", h, p), true, false, true}
}

func (c *Client) Explain(args []string) string {
	cmd := fmt.Sprintf("curl -sOJ %s/render \\\n", c.Addr)
	for _, a := range args {
		cmd += fmt.Sprintf("\t-H \"X-Rey: %s\" \\\n", a)
	}
	return cmd
}

func (c *Client) Ping() error {
	conn, err := net.Dial("tcp", c.Addr)
	if err != nil {
		return err
	}
	h, _, _ := net.SplitHostPort(c.Addr)
	req := ("GET /ping HTTP/1.1\r\n" +
		"Host: " + h + "\r\n" +
		"User-Agent: curl/7.43.0\r\n" +
		"Accept: */*\r\n" +
		"Connection: Close\r\n" +
		"\r\n")
	log.Printf("ping %s", c.Addr)
	if _, err = conn.Write([]byte(req)); err != nil {
		return err
	}
	log.Printf("waiting ping response from %q", c.Addr)
	bs, err := ioutil.ReadAll(conn)
	if err != nil {
		return err
	}
	if parts := strings.Split(string(bs), "\r\n\r\n"); len(parts) > 1 {
		if lines := strings.Split(parts[1], "\r\n"); len(lines) > 0 && lines[0] == "OK" {
			log.Printf("ping %q OK", c.Addr)
			return nil
		}
	}
	return fmt.Errorf("unexpected respone: %q", string(bs))
}

func (c *Client) Render(args []string) []byte {
	f := c.renderHttpMode
	if c.PassMode {
		f = c.renderPassMode
	} else if c.BinMode {
		f = c.renderBinMode
	}
	bs, err := f(args)
	if err != nil {
		log.Printf("render error: %v", err)
	}
	return bs
}

func (c *Client) renderPassMode(args []string) ([]byte, error) {
	req, err := http.NewRequest("GET", "http://"+c.Addr+"/pass", nil)
	if err != nil {
		return nil, fmt.Errorf("failed to create pass request: %v", err)
	}
	bs := []byte(strings.Join(args, "\r\n"))
	req.Header.Add("X-rey-Pass", base64.StdEncoding.EncodeToString(bs))
	if c.passModeCompress {
		req.Header.Add("X-rey-Pass-Compress", "true")
	}
	resp, err := http.DefaultClient.Do(req)
	if err != nil {
		return nil, fmt.Errorf("failed to request pass: %v", err)
	}
	r := resp.Body
	if c.passModeCompress {
		if r, err = gzip.NewReader(r); err != nil {
			return nil, err
		}
	}
	pix, err := ioutil.ReadAll(r)
	if err != nil {
		return nil, fmt.Errorf("failed to read pass result: %v", err)
	}
	return pix, nil
}

func (c *Client) renderHttpMode(args []string) ([]byte, error) {
	req, err := http.NewRequest("GET", "http://"+c.Addr+"/render", nil)
	if err != nil {
		return nil, fmt.Errorf("failed to create request: %v", err)
	}
	for _, a := range args {
		req.Header.Add("X-Rey", a)
	}
	req.Header.Add("Connection", "Close")
	for k, v := range req.Header {
		log.Printf("using header: %q: %q", k, v)
	}
	log.Printf("requesting rendering")
	resp, err := http.DefaultClient.Do(req)
	if err != nil {
		return nil, fmt.Errorf("failed to make request: %v", err)
	}
	log.Printf("reading rendering result")
	bs, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Printf("%v", resp)
		return nil, fmt.Errorf("failed to read response: %v", err)
	}
	return bs, nil
}

func (c *Client) renderBinMode(args []string) ([]byte, error) {
	log.Printf("Connecting to %s", c.Addr)
	conn, err := net.Dial("tcp", c.Addr)
	if err != nil {
		log.Printf("dial error: %s", err)
		return nil, err
	}
	log.Printf("connection established")
	log.Printf("local addr: %s", conn.LocalAddr())
	log.Printf("remote addr: %s", conn.RemoteAddr())

	req := c.makeBinModeReq(args)
	fmt.Printf("%s\n", req)
	if _, err := conn.Write([]byte(req)); err != nil {
		log.Printf("error: %s", err)
		return nil, err
	}
	return ioutil.ReadAll(conn)
}

func (c *Client) makeBinModeReq(args []string) string {
	req := "GET /render HTTP/1.1\r\n"
	if c.BinMode {
		req += "X-Rey: no-http-header\r\n"
	}
	for _, a := range args {
		req += fmt.Sprintf("X-Rey: %s\r\n", a)
	}
	req += "\r\n"
	return req
}

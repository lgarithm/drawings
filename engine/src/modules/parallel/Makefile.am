all: server client

gopath = $(PWD)/../../../build/go
outdir = ../../../build/bin

server: server.go
	mkdir -p ../../../build/go/src/render
	cp server.go ../../../build/go
	cp render_request.go ../../../build/go/src/render/
	cd ../../../build/go
	GOPATH=$(gopath) go build -o $(outdir)/server.out server.go

client: client.go
	mkdir -p ../../../build/go/src/render
	cp client.go ../../../build/go
	cp render_request.go ../../../build/go/src/render/
	cd ../../../build/go
	GOPATH=$(gopath) go build -o $(outdir)/client.out client.go

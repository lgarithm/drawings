all: server client_cli

builddir = $(PWD)/../../../build/go
gopath = $(builddir)
outdir = ../../../build/bin

server: server.go client parallel
	cp server.go $(builddir)
	cd $(builddir)
	GOPATH=$(gopath) go build -o $(outdir)/server.out server.go

client_cli: client_cli.go client
	cp client_cli.go $(builddir)
	cd $(builddir)
	GOPATH=$(gopath) go build -o $(outdir)/client.out client_cli.go

client: client.go
	mkdir -p $(builddir)/src/render
	cp client.go $(builddir)/src/render/

parallel: parallel.go
	mkdir -p $(builddir)/src/parallel
	cp parallel.go $(builddir)/src/parallel

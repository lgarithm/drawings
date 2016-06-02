default: pdf

all: pdf html

pdf: eps
	cd latex && make

html: svg
	guile html/gen.scm > html/index.html

eps:
	mpost fig.mp

svg:
	mkdir -p html
	mpost svg.mp

pdf: fig
	pdflatex bb8.tex
slides: fig
	pdflatex slides.tex
fig: fig.mp
	mpost fig.mp
gif: gif.mp
	mpost gif.mp
pdf2png: pdf
	ghostscript -dNOPAUSE -dBATCH -sDEVICE=png16m -r400 -dDownScaleFactor=1 -sOutputFile=pic-%02d.png bb8.pdf
png:
	ghostscript -dNOPAUSE -dBATCH -sDEVICE=png16m -r400 -dDownScaleFactor=1 -sOutputFile=pic-%02d.png gif.[0-9]*
ppm: gif
	ghostscript -dNOPAUSE -dBATCH -sDEVICE=ppm -sOutputFile=pic-%02d.ppm gif.[0-9]*
clean:
	-rm *.aux *.log *.pdf fig.? *.mpx

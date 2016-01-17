pdf: fig
	pdflatex bb8.tex
slides: fig
	pdflatex slides.tex
fig: fig.mp
	mpost fig.mp
gif: gif.mp
	mpost gif.mp
png: pdf
	ghostscript -dNOPAUSE -dBATCH -sDEVICE=png16m -r600 -dDownScaleFactor=1 -sOutputFile=pic-%02d.png bb8.pdf

clean:
	-rm *.aux *.log *.pdf fig.? *.mpx

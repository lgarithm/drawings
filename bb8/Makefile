pdf: fig
	pdflatex bb8.tex
fig: fig.mp
	mpost fig.mp
clean:
	-rm *.aux *.log *.pdf fig.? *.mpx
png: pdf
	ghostscript -dNOPAUSE -dBATCH -sDEVICE=png16m -r600 -dDownScaleFactor=1 -sOutputFile=pic-%02d.png bb8.pdf

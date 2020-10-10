all: instructions.pdf report

report:
	latexmk -pdf report.tex
 
%.pdf: %.tex
	pdflatex $*
	pdflatex $*

clean:
	rm *.pdf *.aux *.log *.out


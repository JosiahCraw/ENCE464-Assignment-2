all: instructions.pdf report

figures:
	python ../test/scripts/time.py --tt --st --stt --plot --save fig --data ../data

report: figures
	latexmk -pdf report.tex
 
%.pdf: %.tex
	pdflatex $*
	pdflatex $*

clean:
	rm *.pdf *.aux *.log *.out


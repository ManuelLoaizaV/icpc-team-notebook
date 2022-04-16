notebook: pdf/notebook.pdf

clean:
	rm -f pdf/notebook.pdf
	rm notebook.*

pdf/notebook.pdf: tex/*.tex
	pdflatex base/document.tex
	mv document.pdf notebook.pdf
	rm document.*
	mv notebook.pdf pdf/

# pdf/document.pdf: tex/*.tex bib/bibliography.bib
# 	pdflatex base/document.tex
# 	bibtex document
# 	pdflatex base/document
# 	mv document.pdf pdf/
# 	rm document.*
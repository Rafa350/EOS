# Compilador de XSM a C
cgen = C:\Users\Rafael\Documents\Projectes\Net\FSMCompiler\bin\Debug\FsmCompiler.exe
cgen_options = /G:CPP /P:MachineHeaderFileName=fsm_demo.h

# Compilador de XSM a DOT
dotgen = C:\Users\Rafael\Documents\Projectes\Net\FSMCompiler\bin\Debug\FsmCompiler.exe
dotgen_options = /G:DOT

# Compilador de DOT a PDF: 
dot = $(ProgramFiles)\Graphviz2.38\bin\dot.exe
dot_options = -Tpdf

targets = \
       fsm_Demo.c \
	   fsm_Demo.dot \
	   fsm_Demo.pdf

.SUFFIXES: .xsm .dot .c .pdf
.PHONY: all clean

all: $(targets)

clean:
	rm -rf fsm_*.pdf fsm_*.dot fsm_*.c

fsm_%.c: %.xsm
	$(cgen) $(cgen_options) $*.xsm
	
fsm_%.dot: %.xsm
	$(dotgen) $(dotgen_options)	$*.xsm
	
.dot.pdf:
	$(dot) $(dot_options) $*.dot -o $*.pdf

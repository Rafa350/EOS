# Compilador de XSM a C
cgen = C:\Users\Rafael\Documents\Projectes\Net\FSMCompiler\bin\Debug\FsmCompiler.exe
cgen_options = /G:CPP2 /P:MachineHeaderFileName=fsm_demo.h /P:MachineCodeFileName=fsm_demo.cpp /P:StateHeaderFileName=fsm_state.h /P:StateCodeFileName=fsm_state.cpp /P:StateBaseClassName=State

# Compilador de XSM a DOT
dotgen = C:\Users\Rafael\Documents\Projectes\Net\FSMCompiler\bin\Debug\FsmCompiler.exe
dotgen_options = /G:DOT

# Compilador de DOT a PDF: 
dot = $(ProgramFiles)\Graphviz2.38\bin\dot.exe
dot_options = -Tpdf

targets = \
       fsm_Demo.cpp \
	   fsm_Demo.dot \
	   fsm_Demo.pdf

.SUFFIXES: .xsm .dot .c .pdf
.PHONY: all clean

all: $(targets)

clean:
	rm -rf fsm_*.pdf fsm_*.dot fsm_*.cpp fsm_*.h

fsm_%.cpp: %.xsm
	$(cgen) $(cgen_options) $*.xsm
	
fsm_%.dot: %.xsm
	$(dotgen) $(dotgen_options)	$*.xsm
	
.dot.pdf:
	$(dot) $(dot_options) $*.dot -o $*.pdf

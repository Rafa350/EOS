# Compilador de XSM a C
cgen = C:\Users\Rafael\Documents\Projectes\Net\FSMCompiler\bin\Debug\FsmCompiler.exe
cgen_options = /G:CPP2 /P:NsName="eos" /P:ContextBaseClassName="FsmContextBase" /P:StateBaseClassName="FsmStateBase"

# Compilador de XSM a DOT
dotgen = C:\Users\Rafael\Documents\Projectes\Net\FSMCompiler\bin\Debug\FsmCompiler.exe
dotgen_options = /G:DOT

# Compilador de DOT a PDF: 
dot = $(ProgramFiles)\Graphviz2.38\bin\dot.exe
dot_options = -Tpdf

targets = \
       fsmContext.cpp \
	   fsmContext.dot \
	   fsmMachine.pdf

.SUFFIXES: .xsm .dot .c .pdf
.PHONY: all clean

all: $(targets)

clean:
	rm -rf fsm*.pdf fsm*.dot fsm*.cpp fsm*.h

fsm%.cpp: %.xsm
	$(cgen) $(cgen_options) $*.xsm
	
fsm%.dot: %.xsm
	$(dotgen) $(dotgen_options)	$*.xsm
	
.dot.pdf:
	$(dot) $(dot_options) $*.dot -o $*.pdf

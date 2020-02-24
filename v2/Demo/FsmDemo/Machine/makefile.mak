# Compilador de XSM a C
cgen = C:\Users\Rafael\Documents\Projectes\Net\FSMCompiler\bin\Debug\FsmCompiler.exe
cgen_opt = /G:CPP

# Compilador de XSM a DOT
dotgen = C:\Users\Rafael\Documents\Projectes\Net\FSMCompiler\bin\Debug\FsmCompiler.exe
dotgen_opt = /G:DOT

# Compilador de DOT a PDF: 
dot = $(ProgramFiles)\Graphviz2.38\bin\dot.exe
dot_opt = -Tpdf

targets = \
	MachineContext.cpp \
	MachineContext.h \
	MachineState.cpp \
	MachineState.h \
	Machine.pdf

.SUFFIXES: .xsm .dot .cpp .pdf
.PHONY: all clean

all: $(targets)

clean:
	rm -rf *.pdf *.cpp *.h

%Context.cpp: %.xsm
	$(cgen) $(cgen_opt) /P:OutputType=ContextCode /P:OwnerClassName=MyStateMachine /P:ContextBaseClassName=eos::FsmContextBase /P:ContextCodeFileName=$*Context.cpp /P:ContextHeaderFileName=$*Context.h /P:StateHeaderFileName=$*State.h $*.xsm
	
%Context.h: %.xsm
	$(cgen) $(cgen_opt) /P:OutputType=ContextHeader /P:OwnerClassName=MyStateMachine /P:ContextBaseClassName=eos::FsmContextBase /P:ConfigHeaderFileName=appMachineConfig.h /P:ContextHeaderFileName=$*Context.h $*.xsm

%State.cpp: %.xsm
	$(cgen) $(cgen_opt) /P:OutputType=StateCode /P:OwnerClassName=MyStateMachine /P:ContextBaseClassName=eos::FsmContextBase /P:StateBaseClassName=eos::FsmStateBase /P:StateCodeFileName=$*State.cpp /P:ContextHeaderFileName=$*Context.h /P:StateHeaderFileName=$*State.h $*.xsm
	
%State.h: %.xsm
	$(cgen) $(cgen_opt) /P:OutputType=StateHeader /P:OwnerClassName=MyStateMachine /P:ContextBaseClassName=eos::FsmContextBase /P:StateBaseClassName=eos::FsmStateBase /P:ConfigHeaderFileName=appMachineConfig.h /P:StateHeaderFileName=$*State.h $*.xsm

%.dot: %.xsm
	$(dotgen) $(dotgen_opt)	$*.xsm
	
.dot.pdf:
	$(dot) $(dot_opt) $*.dot -o $*.pdf

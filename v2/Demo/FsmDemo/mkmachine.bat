@echo off

rem "..\..\..\..\..\VS\FSMCompiler\Out\bin\x86\Debug\FSMCompiler.exe" machine.xsm /G:CPP /P:MachineHeaderFileName=fsmMachine.h /P:MachineCodeFileName=fsmMachine.c /P:StateHeaderFileName=fsmStates.h /P:StateCodeFileName=fsmStates.c 
"..\..\..\..\..\VS\FSMCompiler\Out\bin\x86\Debug\FSMCompiler.exe" machine.xsm /G:CPP /P:MachineClassName=MyMachine /P:MachineBaseClassName=Machine /P:StateBaseClassName=State /P:MachineHeaderFileName=fsmMachine.hpp /P:MachineCodeFileName=fsmMachine.cpp /P:StateHeaderFileName=fsmState.hpp /P:StateCodeFileName=fsmState.cpp

pause
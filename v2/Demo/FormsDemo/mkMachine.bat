@echo off

"..\..\..\..\Projectes VS\FSMCompiler\Out\bin\x86\Release\FSMCompiler.exe" machine.xsm /P:MachineHeaderFileName=fsmMachine.hpp /P:MachineCodeFileName=fsmMachine.cpp /P:StateHeaderFileName=fsmStates.hpp /P:StateCodeFileName=fsmStates.cpp /P:StateBaseClassName=eos::fsm::State /P:MachineClassName=MyMachine /P:MachineBaseClassName=eos::fsm::StateMachine

pause
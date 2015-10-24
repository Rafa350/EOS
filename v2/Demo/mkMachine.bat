@echo off

"..\..\..\..\Projectes VS\FSMCompiler\Out\bin\x86\Release\FSMCompiler.exe" machine.xsm /MH:fsmMachine.hpp /MC:fsmMachine.cpp /SH:fsmStates.hpp /SC:fsmStates.cpp /SBCN:eos::fsm::State /MCN:MyMachine /MBCN:eos::fsm::StateMachine

pause
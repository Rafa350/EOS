@echo off

"..\..\..\..\Projectes VS\FSMCompiler\Out\bin\x86\Release\FSMCompiler.exe" machine.xsm /MH:fsmMachine.hpp /MC:fsmMachine.cpp /SH:fsmState.hpp /SC:fsmState.cpp /MCN:MyMachine

pause
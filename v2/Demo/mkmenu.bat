@echo off

"..\..\..\PicLib\Tools\PicResourceCompiler.exe" menu.xmenu
del menu.mnu.c
del menu.mnu.h

pause


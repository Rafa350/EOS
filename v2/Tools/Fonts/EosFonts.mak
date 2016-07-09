# ---------------------------------------------------
# Macros for TOOLS

# cpp_compiler: Compilador CPP (Microchip XC32)
cpp_compiler="C:\Program Files\Microchip\xc32\v1.40\bin\xc32-c++.exe"
cpp_compiler_options=

# resource_compiler: Compilador de recursos
resource_compiler="C:\Users\Rafael\Documents\Projectes\MPLAB\EOS\v2\Tools\Bin\EosResourceCompiler.exe"
resource_compiler_options=/P:use-proxy-variable /P:output-extension=cpp /P:include-files=eosConfig.h


# ---------------------------------------------------
# Rules

all: "Out\Arial8pt.cpp" "Out\Arial10pt.cpp" "Out\Arial12pt.cpp" "Out\Arial24pt.cpp" "Out\Arial14pt.cpp" "Out\Arial18pt.cpp" "Out\ArialBold8pt.cpp" "Out\ArialBold10pt.cpp" "Out\ArialBold12pt.cpp" "Out\CourierNew7pt.cpp" "Out\CourierNew8pt.cpp" "Out\CourierNew10pt.cpp" "Out\CourierNewBold7pt.cpp" "Out\CourierNewBold8pt.cpp" "Out\CourierNewBold10pt.cpp" "Out\Consolas8pt.cpp" "Out/Consolas10pt.cpp" "Out/Consolas12pt.cpp"

"Out\Arial8pt.cpp": "Arial8pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out Arial8pt.xfont

"Out\Arial10pt.cpp": "Arial10pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out Arial10pt.xfont

"Out\Arial12pt.cpp": "Arial12pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out Arial12pt.xfont

"Out\Arial24pt.cpp": "Arial24pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out Arial24pt.xfont

"Out\Arial14pt.cpp": "Arial14pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out Arial14pt.xfont

"Out\Arial18pt.cpp": "Arial18pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out Arial18pt.xfont

"Out\ArialBold8pt.cpp": "ArialBold8pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out ArialBold8pt.xfont

"Out\ArialBold10pt.cpp": "ArialBold10pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out ArialBold10pt.xfont

"Out\ArialBold12pt.cpp": "ArialBold12pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out ArialBold12pt.xfont

"Out\CourierNew7pt.cpp": "CourierNew7pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out CourierNew7pt.xfont

"Out\CourierNew8pt.cpp": "CourierNew8pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out CourierNew8pt.xfont

"Out\CourierNew10pt.cpp": "CourierNew10pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out CourierNew10pt.xfont

"Out\CourierNewBold7pt.cpp": "CourierNewBold7pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out CourierNewBold7pt.xfont

"Out\CourierNewBold8pt.cpp": "CourierNewBold8pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out CourierNewBold8pt.xfont

"Out\CourierNewBold10pt.cpp": "CourierNewBold10pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out CourierNewBold10pt.xfont

"Out\Consolas8pt.cpp": "Consolas8pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out Consolas8pt.xfont

"Out/Consolas10pt.cpp": "Consolas10pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out Consolas10pt.xfont

"Out/Consolas12pt.cpp": "C:\Users\Rafael\Documents\Projectes\MPLab\EOS\v2\Tools\Fonts\Consolas12pt.xfont" "EosFonts.mak"
	$(resource_compiler) $(resource_compiler_options) /O:Out C:\Users\Rafael\Documents\Projectes\MPLab\EOS\v2\Tools\Fonts\Consolas12pt.xfont


target_sources(${TARGET_NAME} 
    PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES
		eosBrush.cpp
		eosCanvas.cpp
		eosConsole.cpp
		eosGraphics.cpp
		eosFont.cpp
		eosPen.cpp
		eosPoint.cpp
		eosRect.cpp
		eosSize.cpp
		eosTransformation.cpp
	PUBLIC
		eosCanvas_Core.cpp
		eosCanvas_Bitmap.cpp
		eosCanvas_Clipping.cpp
		eosCanvas_DrawBitmap.cpp
		eosCanvas_DrawCircle.cpp
		eosCanvas_DrawEllipse.cpp
		eosCanvas_DrawLine.cpp
		eosCanvas_DrawPolygon.cpp
		eosCanvas_DrawRectangle.cpp
		eosCanvas_DrawRoundRectangle.cpp
		eosCanvas_DrawText.cpp
		eosCanvas_DrawTriangle.cpp
		eosCanvas_Text.cpp
)	
	
target_sources(${TARGET_NAME} 
	PUBLIC 
		eosColor.cpp
		#eosColorMath.cpp
)

add_subdirectory("Fonts")

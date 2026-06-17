#add_subdirectory("Fonts")

target_sources(${TARGET_NAME} PUBLIC 
	eosBitmap.cpp
	eosBrush.cpp
	eosColor.cpp
	eosColorMath.cpp
	eosConsole.cpp
	eosFont.cpp
	eosGraphics.cpp
	eosGraphics_Bitmap.cpp
	eosGraphics_Circle.cpp
	eosGraphics_Clipping.cpp
	eosGraphics_Ellipse.cpp
	eosGraphics_Line.cpp
	eosGraphics_Polygon.cpp
	eosGraphics_Rectangle.cpp
	eosGraphics_RoundRectangle.cpp
	eosGraphics_Text.cpp
	eosGraphics_Triangle.cpp
	eosPen.cpp
	eosPoint.cpp
	eosRect.cpp
	eosSize.cpp
	eosText.cpp
	eosTransformation.cpp
)

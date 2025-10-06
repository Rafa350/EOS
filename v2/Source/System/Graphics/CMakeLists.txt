cmake_minimum_required(VERSION 4.0)

add_subdirectory("Fonts")

list(APPEND SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/eosBitmap.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosBrush.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosColor.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosColorMath.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosConsole.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosFont.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosGraphics.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosGraphics_Bitmap.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosGraphics_Circle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosGraphics_Clipping.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosGraphics_Ellipse.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosGraphics_Line.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosGraphics_Polygon.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosGraphics_Rectangle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosGraphics_RoundRectangle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosGraphics_Text.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosGraphics_Triangle.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosPen.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosPoint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosRect.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosSize.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosText.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/eosTransformation.cpp
)	

target_sources(${CMAKE_PROJECT_NAME} PUBLIC 
	${SOURCES}
)

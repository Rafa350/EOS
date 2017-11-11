#include "Controllers/Display/Drivers/eosRGBDirect.h"


using namespace eos;


RGBDirect_Driver::RGBDirect_Driver():
	screenWidth(RGBDIRECT_SCREEN_WIDTH),
	screenHeight(RGBDIRECT_SCREEN_HEIGHT) {

}


void RGBDirect_Driver::initialize() {

}


void RGBDirect_Driver::shutdown() {

}


void RGBDirect_Driver::displayOn() {

}


void RGBDirect_Driver::displayOff() {

}


void RGBDirect_Driver::setOrientation(
	DisplayOrientation orientation) {

}


void RGBDirect_Driver::clear(
	const Color &color) {

}


void RGBDirect_Driver::setPixel(
	int16_t x,
	int16_t y,
	const Color &color) {

}


void RGBDirect_Driver::setHPixels(
	int16_t x,
	int16_t y,
	int16_t size,
	const Color &color) {

}


void RGBDirect_Driver::setVPixels(
	int16_t x,
	int16_t y,
	int16_t size,
	const Color &color) {

}


void RGBDirect_Driver::setPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color &color) {

}


void RGBDirect_Driver::writePixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	const Color *colors) {

}


void RGBDirect_Driver::readPixels(
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height,
	Color *colors) {

}


void RGBDirect_Driver::vScroll(
	int16_t delta,
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height) {

}


void RGBDirect_Driver::hScroll(
	int16_t delta,
	int16_t x,
	int16_t y,
	int16_t width,
	int16_t height) {

}

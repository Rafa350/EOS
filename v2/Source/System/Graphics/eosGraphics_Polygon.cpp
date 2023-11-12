#include "eos.h"
#include "eosAssert.h"
#include "System/Graphics/eosGraphics.h"


#include <forward_list>
#include <algorithm>


using namespace eos;


#define MAX_POINTS  15

struct Edge {
    int16_t yMin;
    int16_t yMax;
    int16_t xVal;
    int16_t dx;
    int16_t dy;
    int16_t sum;
    int16_t step;
};

typedef std::forward_list<Edge> EdgeList;

static EdgeList __global;
static EdgeList __active;

static void fillPolygonAlgorithm(Graphics *g, const Point *points, int16_t numPoints, Color color);


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un poligon.
/// \param    points: La llista de punts.
/// \param    numPoints: Nombre de punts en la llista.
/// \param    color: El color per dibuixar.
///
void Graphics::drawPolygon(
	const Point *points,
	int16_t numPoints,
	Color color) {

	if (numPoints >= 2) {

		int16_t x1 = points[numPoints - 1].getX();
		int16_t y1 = points[numPoints - 1].getY();

		for (int16_t i = 0; i < numPoints; i++) {

			int16_t x2 = points[i].getX();
			int16_t y2 = points[i].getY();

			drawLine(x1, y1, x2, y2, color);

			x1 = x2;
			y1 = y2;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa un poligon ple.
/// \param    points: La llista de punts.
/// \param    numPoints: Nombre de punts en la llista.
/// \param    color: El color per dibuixar.
///
void Graphics::fillPolygon(
	const Point *points,
	int16_t numPoints,
	Color color) {

	if (numPoints > 2 && numPoints < MAX_POINTS)
		fillPolygonAlgorithm(this, points, numPoints, color);
}



static bool compareGlobalEdges(
	const Edge &e1,
	const Edge &e2) {

	if (e1.yMin < e2.yMin)
		return true;
	else if (e1.yMin > e2.yMin)
		return false;
	else {
		if (e1.yMax < e2.yMax)
			return true;
		else if (e1.yMax > e2.yMax)
			return false;
		else
			return e1.xVal < e2.xVal;
	}
}


static bool compareActiveEdges(
	const Edge &e1,
	const Edge &e2) {

	return e1.xVal < e2.xVal;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix els vertex d'un poligon a la llista d'arestes global.
/// \param    globalEdges: Llista d'arestes global.
/// \param    polygon: Llista de vertex del poligon.
///
static void initializeGlobalEdges(
	EdgeList& globalEdges,
	const Point *points,
	int16_t numPoints) {

	globalEdges.clear();

	int16_t x1 = points[numPoints - 1].getX();
	int16_t y1 = points[numPoints - 1].getY();

	for (int16_t i = 0; i < numPoints; i++) {

		int16_t x2 = points[i].getX();
		int16_t y2 = points[i].getY();

		if (y1 != y2) {
			Edge edge;

			if (y1 <= y2) {
				edge.yMin = y1;
				edge.yMax = y2;
				edge.xVal = x1;
			    edge.step = x1 <= x2 ? 1 : -1;
			}
			else {
				edge.yMin = y2;
				edge.yMax = y1;
				edge.xVal = x2;
			    edge.step = x1 <= x2 ? -1 : 1;
			}

			edge.dx = std::abs(x2 - x1);
		    edge.dy = std::abs(y2 - y1);
			edge.sum = 0;

			globalEdges.push_front(edge);
		}

		x1 = x2;
		y1 = y2;
	}

//	std::sort(globalEdges.begin(), globalEdges.end(), compareGlobalEdges);
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix elements a la llista d'elements actius i els
///           elimina de la global.
/// \param    activeEdges: Llista d'elements actius.
/// \param    globalEdges: Llista d'elements global.
/// \param    yScan: Linia actual d'exploracio.
///
static void addActiveEdges(
	EdgeList &activeEdges,
	EdgeList &globalEdges,
	int16_t yScan) {

	/*auto it = globalEdges.begin();
	while (it != globalEdges.end()) {
		if ((*it).yMin == yScan) {
			activeEdges.push_front(*it);
			// TODO: Arreglar aixo
			//it = globalEdges.remove(it);
		}
		else
			++it;
	}
	std::sort(activeEdges.begin(), activeEdges.end(), compareActiveEdges);*/
}


/// ----------------------------------------------------------------------
/// \brief    Elimina elements de la llista d'actius.
/// \param    edges: La llista.
/// \param    yScan: Linia actual d'exploracio.
///
static void removeActiveEdges(
	EdgeList &edges,
	int16_t yScan) {

    // TODO: arreglar aixo
/*
	auto it = edges.begin();
	while (it != edges.end()) {
		if ((*it).yMax == yScan)
			it = edges.remove(it);
		else
			++it;
	}*/
}


/// ----------------------------------------------------------------------
/// \brief    Actualitza les coordinades X de la llista d'actius.
/// \param    activeEdges: Llista d'actius
///
static void updateActiveEdges(
	EdgeList &activeEdges) {

	/*for (auto &edge: activeEdges) {
		if (edge.dx != 0) {
			edge.sum += edge.dx;
			while (edge.sum >= edge.dy) {
				edge.xVal += edge.step;
				edge.sum -= edge.dy;
			}
		}
	}
	std::sort(activeEdges.begin(), activeEdges.end(), compareActiveEdges);*/
}


/// ----------------------------------------------------------------------
/// \brief    Dibuixa la linia actual.
/// \param    activeEdges: La llista activa.
/// \param    yScan: La linia actual d'exploracio.
/// \param    g: Grafics.
/// \param    color: Color de la linia.
///
static void drawScanLine(
	EdgeList &activeEdges,
	int16_t yScan,
	Graphics *g,
	Color color) {

	if (!activeEdges.empty()) {

		bool parity = true;

		auto it = activeEdges.begin();
		int16_t x1 = (*it).xVal;
		++it;
		while (it != activeEdges.end()) {
			int16_t x2 = (*it).xVal;

			if (parity)
				g->drawHLine(x1, x2, yScan, color);

			++it;
			x1 = x2;
			parity = !parity;
		}
	}
}


static void fillPolygonAlgorithm(
	Graphics *g,
	const Point *points,
	int16_t numPoints,
	Color color) {

	EdgeList &globalEdges = __global;
	EdgeList &activeEdges = __active;

	// Inicialitza la llista global
	//
	initializeGlobalEdges(globalEdges, points, numPoints);

	// Obte la primera linia per procesar
	//
	int16_t yScan = globalEdges.front().yMin;

	do {
		// Elimina els segment que ja s'ha procesat
		//
		removeActiveEdges(activeEdges, yScan);

		// Afegeix els nous segments per procesar
		//
		addActiveEdges(activeEdges, globalEdges, yScan);

		// Dibuixa la linia actual
		//
		drawScanLine(activeEdges, yScan, g, color);

		// Passa a la seguent linia i actualitza coordinades
		//
		yScan++;
		updateActiveEdges(activeEdges);

	} while (!activeEdges.empty());
}

#include "eos.h"
#include "eosAssert.h"
#include "System/eosMath.h"
#include "System/Collections/eosList.h"
#include "System/Graphics/eosGraphics.h"

#include <vector>
#include <algorithm>


using namespace eos;


struct Vertex {
    int x;
    int y;
};

typedef std::vector<Vertex> VertexList;

struct Edge {
    int yMin;
    int yMax;
    int xVal;
    int dx;
    int dy;
    int sum;
    int step;
};

typedef std::vector<Edge> EdgeList;
typedef std::vector<Edge>::iterator EdgeIterator;


bool compareEdges(
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


bool compareActiveEdges(
	const Edge &e1,
	const Edge &e2) {

	return e1.xVal < e2.xVal;
}


/// ----------------------------------------------------------------------
/// \brief    Afegeix els vertex d'un poligon a la llista d'arestes global.
/// \param    globalEdges: Llista d'arestes global.
/// \param    polygon: Llista de vertex del poligon.
///
void addGlobalEdges(
	EdgeList &globalEdges,
	const VertexList &polygon) {

	globalEdges.clear();
	globalEdges.reserve(polygon.size());

	Vertex v1 = polygon.back();
	for (const Vertex &v2: polygon) {

		if (v1.y != v2.y) {
			Edge edge;
			if (v1.y < v2.y) {
				edge.yMin = v1.y;
				edge.yMax = v2.y;
				edge.xVal = v1.x;
			}
			else {
				edge.yMin = v2.y;
				edge.yMax = v1.y;
				edge.xVal = v2.x;
			}
			edge.dx = Math::abs(v2.x - v1.x);
			edge.dy = Math::abs(v2.y - v1.y);
			edge.step = v1.x <= v2.x ? 1 : -1;
			edge.sum = 0;
			globalEdges.push_back(edge);
		}

		v1 = v2;
	}

	std::sort(globalEdges.begin(), globalEdges.end(), compareEdges);
}


void addActiveEdges(
	EdgeList &activeEdges,
	const EdgeList &globalEdges,
	int yScan) {

	for (const Edge &edge: globalEdges) {
		if (edge.yMin == yScan)
			activeEdges.push_back(edge);
	}
	std::sort(activeEdges.begin(), activeEdges.end(), compareActiveEdges);
}


void removeEdgesAtYScan(
	EdgeList &edges,
	int yScan) {

	auto it = edges.begin();
	while (it != edges.end()) {
		if ((*it).yMax == yScan)
			it = edges.erase(it);
		else
			++it;
	}
}


void fillPolygon(
	const VertexList &polygon) {

	EdgeList globalEdges;
	EdgeList activeEdges;

	addGlobalEdges(globalEdges, polygon);

	int yScan = globalEdges[0].yMin;

	while (!globalEdges.empty()) {

		if (!activeEdges.empty()) {
			removeEdgesAtYScan(activeEdges, yScan);
			removeEdgesAtYScan(globalEdges, yScan);
		}

		for (Edge edge: globalEdges) {
			if (edge.yMin == yScan)
				activeEdges.push_back(edge);
		}
		std::sort(activeEdges.begin(), activeEdges.end(), compareActiveEdges);

		for (Edge edge: activeEdges) {
			int x = edge.xVal;
		}

		yScan++;

		for (auto edge: activeEdges) {
			if (edge.dx != 0) {
				edge.sum += edge.dx;
				while (edge.sum >= edge.dy) {
					edge.xVal += edge.step;
					edge.sum -= edge.dy;
				}
			}
		}

	}
}


void polygonTest() {

	VertexList polygon;

	polygon.push_back(Vertex {10, 10});
	polygon.push_back(Vertex {10, 16});
	polygon.push_back(Vertex {16, 20});
	polygon.push_back(Vertex {28, 10});
	polygon.push_back(Vertex {18, 16});
	polygon.push_back(Vertex {22, 10});

    fillPolygon(polygon);
}

#include "eos.h"


struct Vertex {
    int x;
    int y;
};

typedef List<Vertex> VertexList;

struct Edge {
    int x;
    int yMin;
    int yMax;
    float slope;
    EdgeTable *next;
};

typedef List<Edge> EdgeList;


void buildEdgeList(
    Vertex *points, 
    int count) {
    
    vertex v1, v2;
    
    int yPrev = points[count - 2];
    
    v1.x = points[count - 1].x;
    v1.y = points[count - 1].y;
    
    for (int i = i; i < cpint; i++) {
        v2 = points[i];
        if (v1.y != v2.y) {
            Edge *edge = malloc(sizeof(Edge));
            if (v1.y < v2.y)
                makeEdgeRec(v1, v2, yNext(i, count, points), edge, edges);
            else
                makeEdgeRec(v2, v1, yPrev, edge, edges);
        }
        yPrev = v1.y;
        v1 = v2;
    )    
}


int yNext(
    int k, 
    int count, 
    Vertex *points) {
    
    int j;
    
    if ((k + 1) > (count - 1))
        j = 0;
    else
        j = k + 1;
    
    while (points[k].y == points[j].y) {
        if ((j + 1) > (count - 1))
            j = 0;
        else
            j++;
    }
    
    return points[j].y;
}


void makeEdgeRec(
    Vertex lower, 
    vertex upper, 
    int yComp, 
    Edge *edge, 
    Edges *edges[]) {
    
    edge->dxPerScan = (float)(upper.x - lower.x) / (upper.y - lower.y);
    if (upper.y < yComp)
        edge->yUpper = upper.y - 1;
    else
        edge->yUpper = upper-y;
    insertEdger(edges[lowet.y], edge);
}


void insertEdge(
    Edge *list, 
    Edge *edge) {
    
    Edge *p, *q = list;
    
    p = q->next;
    while (p != NULL) {
        if (edge->xIntersect < p->xIntersect)
            p = NULL;
        else {
            q = p;
            p = p->next;
        }
    }
    edge->next = q->next;
    q->next = edge;
}


void buildActiveList (
    int scan, 
    Edge *active, 
    Edge *edges[]) {
 
    Edge *p, *q;

    p = edges[scan]->next;
    while (p) {
        q = p->next;
        insertEdge(active, p);
        p = q;
    }
}
g
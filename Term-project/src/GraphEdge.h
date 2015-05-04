/*
 * GraphEdge.h
 *
 *  Created on: Nov 4, 2014
 *      Author: harshul
 */

#ifndef GRAPHEDGE_H_
#define GRAPHEDGE_H_
#include "point.h"
#include "gtype.h"
#include "GridMap.h"
#include <vector>
//#include <unordered_map>
#include <map>
//#include <boost/unordered_map.hpp>

namespace std {

class GraphEdge {
public:
	GraphEdge(int numberOfSamples, int treeLength);
	//GridMap gmObj;
	GPoint edges[1][2];
	int countOfEdge;
	int sizeOfTree=0;
	int numberOfSamples, treeLength;
	int randNumber;
	int range_end = 500;
	double dist_SG = 0.00;
	int countNodesTree = 0;
	int nearestIndex = 0;
	int alpha = 3;
	int ctr;
	void setGridMapObject(GridMap gm);
	void addEdge(GPoint p1,GPoint p2);
	//void getEdgeForPoint(GPoint p1);
	bool isPointPresent(GPoint p1, int size, GridMap gm2);
	void increaseSizeEdgeArray();
	void printGraphEdges();
	int getIndex(GPoint p1, GridMap gm1);
	void printAllEdges(GPoint p1);
	int getLength(std::vector<GPoint> vect);
	void initTree(GPoint p1);
	int getNearestNodeIndex(GPoint pnt);
	double getDistance(GPoint p1, GPoint p2);
	bool isElementPresent(int num, std::vector<int> List);
	std::vector<std::vector<GPoint> > getTreeToMain();
	void makeTree(GridMap gm3, int treeSize,int startIndex, int goalIndex);
	bool areDoubleEqual(double a, double b, double x);
	bool isPointPresentString(GPoint p1, int size, GridMap gm2);

	/*GraphEdge();
	virtual ~GraphEdge();*/
};

} /* namespace std */
#endif /* GRAPHEDGE_H_ */

/*
 * Path.h
 *
 *  Created on: Nov 7, 2014
 *      Author: harshul
 */

#ifndef PATH_H_
#define PATH_H_

#include "GraphEdge.h"
#include "GridMap.h"
#include "gtype.h"
#include "point.h"
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
namespace std {

class Path {
public:

	vector<GPoint> path;
	int start, goal,len, treeSize, numberOfSamples;
	bool isStartPntPresent, isGoalPntPresent, appendStartFlag;

	GPoint startPnt;
	std::vector<std::vector<GPoint> > treeEdgesPath;
	Path(int start_index, int goal_index, GraphEdge geObj, GridMap gmObj, std::vector<std::vector<GPoint> > treeEdges,int treeSize, int numberOfSamples);
	void getPath(int goal_idx,GraphEdge geObj2, GridMap gm1, std::vector<std::vector<GPoint> > treeEdgesPath);
	void printPath(GraphEdge geObj, GridMap gm);
	int connectStartToTree(GPoint startPnt, GPoint goalPnt, GraphEdge geObj1, GridMap gm2);

};

} /* namespace std */
#endif /* PATH_H_ */

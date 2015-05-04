#include <iostream>
using namespace std;
#include "GridMap.h"
#include "CircularObstacle.h"
#include <boost/unordered_map.hpp>
#include "point.h"
#include "gtype.h"
#include "GraphEdge.h"
#include <fontconfig/fontconfig.h>
#include <random>
#include <functional>
#include <stdlib.h>
#include <zlib.h>
#include <vector>
#include "Path.h"
#include <cairo/cairo.h>

using namespace std;

int start_index;
int goal_index = 2142;
int countNodesTree = 0;
int treeSize = 1000;
int numberOfSamples = 1000;
std::vector<std::vector<GPoint> > tree;
int nearestIndex = 0;
//std::vector<int> randomNumberList;
std::vector<GPoint> pathPoints;
int range_end = 500;
int goal;
//Start node : (33.9734, 89.7077)
//Goal node : (240.522, 256.619)


int main() {

	GPoint startPnt = GPoint(41, 50);		//	(33.9734, 89.7077);
	GPoint goalPnt = GPoint(465, 252);		//432.962, 412.464)  Point @2163 is : (384.806, 484.686)


	/*Defining sample points */
	GridMap gm(numberOfSamples);
	gm.InitVariables();
	gm.InitPointsMap();


	/*Making rapidly exploring random tree*/
	GraphEdge geObj(numberOfSamples, treeSize);
	start_index = geObj.getIndex(startPnt,gm);
	goal_index = geObj.getIndex(goalPnt,gm);
	cout<<"\nstart_index = "<<start_index<<" || goal_index = "<<goal_index<<"\n";
	cout.flush();
	geObj.setGridMapObject(gm);
	geObj.makeTree(gm, treeSize, start_index, goal_index);

	tree  = geObj.getTreeToMain();
	cout<<"\nBack to main \n";
	cout.flush();


	/*Getting path based on  a fixed goal node*/
	cout<<"\nstartPnt : "<<startPnt.getX()<<"---"<<startPnt.getY();
	cout.flush();
	cout<<"\nstart_index : "<<geObj.getIndex(startPnt,gm);
	Path pathObj(start_index,goal_index,geObj,gm,tree,treeSize, numberOfSamples);

	goal = pathObj.connectStartToTree(startPnt, goalPnt,geObj, gm);

	pathObj.getPath(goal, geObj, gm, tree);

	pathObj.printPath(geObj, gm);


	return 0;
}



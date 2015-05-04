/*
 * GraphEdge.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: harshul
 */

#include "GraphEdge.h"
#include "point.h"
#include "gtype.h"
#include "GridMap.h"
#include <map>
#include <vector>
//#include <unordered_map>
#include <boost/unordered_map.hpp>
#include <cairo/cairo.h>
#include <time.h>
#include <cmath>
#include <string>


namespace std {


double minDistance = 0.0;
int minDistancePoint = 0;
int temp = 0;
std::vector<std::vector<GPoint> > treeEdges(1000);
std::vector<int> randomNumberList;
GridMap gmObj(temp);


GraphEdge::GraphEdge(int numberOfSamples, int treeLength)
{
	this->numberOfSamples = numberOfSamples;
	this->treeLength = treeLength;
}


void GraphEdge::setGridMapObject(GridMap gm)
{
	gmObj = gm;
}

void GraphEdge::addEdge(GPoint p1, GPoint p2)
{
	std::vector<GPoint> edgeEndPoints;

	edgeEndPoints.push_back(p2);

	int index = getIndex(p1,gmObj);
	treeEdges[index].push_back(p2);

	//cout<<"\nEdge added is  : ("<<p1.getX()<<", "<<p1.getY()<<") --> ("<<p2.getX()<<", "<<p2.getY()<<")\n\n";
	//cout.flush();
	sizeOfTree++;
}


int GraphEdge::getIndex(GPoint p1, GridMap gm1)
{
	//cout<<"\nnumberOfSamples   "<<this->numberOfSamples;
	for(int i = 0; i<this->numberOfSamples;i++)
	{
		if(i==41){cout<<"\ngm1.points[i].getX() : "<<gm1.points[i].getX(); cout<<"\np1 : "<<p1.getX();};
		if(gm1.points[i].getX() == p1.getX() && gm1.points[i].getY() == p1.getY())
		{
			return i;
		}
	}

}

bool GraphEdge::areDoubleEqual(double a, double b, double x)
{
	cout<<"\n("<<a<<"-"<<b<<")"<<(a-b);
	if(a>b){return ((a-b)<x);}
	else{return ((b-a)<x);}

}


bool GraphEdge::isPointPresent(GPoint p1, int size, GridMap gm2)
{
	int lenPoints = size;		//(sizeof(gmObj.points)/sizeof(gmObj.points[0]));
	cout<<"\nPoint being checked is : "<<p1.getX()<<"--"<<p1.getY();

	for (int i = 0;i<lenPoints;i++)
	{
		if(i == 2163)
		{
			cout<<"\nPoint @ 2163 is : (" <<gm2.points[2163].getX()<<", "<<gm2.points[2163].getY()<<")";
			cout<<"\n\nCOMPARISON"<<areDoubleEqual(gm2.points[2163].getX(),p1.getX(),0.001)<<" and "<<areDoubleEqual(gm2.points[2163].getX(),p1.getX(),0.001);
		}
		if((gm2.points[i].getX() == p1.getX()) && (gm2.points[i].getY() == p1.getY()))
		{
			return true;
		}
	}

	cout<<"\nSending values manually : "<<areDoubleEqual(484.686, 484.686, 0.001);

	return false;
}


bool GraphEdge::isPointPresentString(GPoint pt1, int size, GridMap gm3)
{
	int lenPoints = size;		//(sizeof(gmObj.points)/sizeof(gmObj.points[0]));
	cout<<"\nPoint being checked is : "<<pt1.getX()<<"--"<<pt1.getY();

	for (int i = 0;i<lenPoints;i++)
	{
		string str1 = std::to_string(gm3.points[i].getX());
		string str2 = std::to_string(pt1.getX());
		string str3 = std::to_string(gm3.points[i].getY());
		string str4 = std::to_string(pt1.getY());
		if(str1.compare(str2) && str3.compare(str4))
		{
			return true;
		}
	}

	return false;
}



void GraphEdge::printAllEdges(GPoint p1)
{
	int index = getIndex(p1,gmObj);
	int length = getLength(treeEdges[index]);
	for(int i = 0;i<length;i++){
		//cout<<"\n("<<treeEdges[index][i].getX()<<", "<<treeEdges[index][i].getY()<<")";

	}
}


/*Returns the length of a vector of type GPoint*/
int GraphEdge::getLength(std::vector<GPoint> vect)
{
	int count = 0;
	std::vector<GPoint>::iterator it;
	for(it = vect.begin();it!=vect.end();it++)
	{
		count++;
	}
	return count;
}


void GraphEdge::increaseSizeEdgeArray()
{
	int length = sizeof(edges)/sizeof(edges[0]);

	GPoint edgeArrayTemp[length][2];// = new GPoint[length][2];

	memcpy(edgeArrayTemp, edges, length);

}


void GraphEdge::initTree(GPoint p1)
{
	int index = getIndex(p1,gmObj);
}


int GraphEdge::getNearestNodeIndex(GPoint pnt)
{
	double dist;
	int len;
	for (int i = 0;i<1000;i++)
	{
		if(getLength(treeEdges[i])!=0)
		{
			//cout<<"\nLength at index "<<i<<" is "<<getLength(treeEdges[i]);
			dist = getDistance(gmObj.points[i],pnt);
			if(minDistance == 0)
			{
				minDistance = dist;
				minDistancePoint = i;
			}

			len = getLength(treeEdges[i]);
			for(int j = 0;j<len;j++)
			{
				dist = getDistance(treeEdges[i][j],pnt);
				if(dist<minDistance)
				{
					minDistance = dist;
					minDistancePoint = getIndex(treeEdges[i][j],gmObj);
				}

			}
		}

	}
	minDistance = 0;
	return minDistancePoint;

}


double GraphEdge::getDistance(GPoint p1, GPoint p2)
{
	return pow((pow((p1.getX() - p2.getX()),2) + pow((p1.getY() - p2.getY()),2)),0.5);
}

void GraphEdge::makeTree(GridMap gm3,int treeSize,int start_index, int goal_index)
{
		cout<<"\nNumber of samples and tree length set as : "<<this->numberOfSamples<<" "<<treeSize<<"SG"<<start_index<<"="<<goal_index;
		cout.flush();
		/*Setting up surface in
		 * cairo to print the tree*/
		cairo_surface_t *surface_1;
		cairo_t *cr_1;

		surface_1 = cairo_image_surface_create_from_png("terrain_project.png");//(CAIRO_FORMAT_ARGB32, range_end, range_end);
		cr_1 = cairo_create(surface_1);
		cairo_set_source_rgb(cr_1, 0, 0, 0);
		cairo_select_font_face(cr_1, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
		cairo_set_font_size(cr_1, 40.0);
		cairo_set_line_width (cr_1, 1.5);

		//dist_SG = getDistance(gm3.points[start_index],gm3.points[goal_index]);
		//double dist_SRandm = 0.00;
		//double dist_RandmG = 0.00;
		//bool beta = false;

		//srand (time(NULL));
		ctr = 0;
		randNumber = rand() % 1000;
		bool ret = false;
		randomNumberList.push_back(randNumber);  //This list will maintain the random numbers already selected
		cout<<"\nValue generated for the first time "<<randNumber;

		/*IF a particular random number (index) has
		 *already been considered, we don't consider it again.*/
		for(int i = 0;i<1000;i++)
		{
		ret = isElementPresent(randNumber, randomNumberList);
		if(i>0){
			while(ret)
			{
				randNumber = rand() % 1000;
				/*dist_SRandm = getDistance(gmObj.points[start_index],gmObj.points[randNumber]);
				dist_RandmG = getDistance(gmObj.points[randNumber],gmObj.points[goal_index]);
				beta = (dist_SRandm + dist_RandmG)>dist_SG;*/
				ret = isElementPresent(randNumber, randomNumberList);
			}

			randomNumberList.push_back(randNumber);
		}

		if(countNodesTree == 0)
		{
			addEdge(gm3.points[start_index],gm3.points[randNumber]);
			countNodesTree++;
		}
		else if(countNodesTree > 0)
		{
			/*cout<<"\ngmObj.points[start_index] : "<<nearestIndex<<"--("<<gmObj.points[nearestIndex].getX()<<", "<<gmObj.points[nearestIndex].getY()<<")";
			cout<<"\ngmObj.points[randNumber] : "<<randNumber<<"--"<<gmObj.points[randNumber].getX()<<", "<<gmObj.points[randNumber].getY()<<")";*/
			nearestIndex = getNearestNodeIndex(gm3.points[randNumber]);
			addEdge(gm3.points[nearestIndex],gm3.points[randNumber]);
			countNodesTree++;
		}
		cout<<"\n"<<i;


		  cairo_arc(cr_1, gm3.points[nearestIndex].getX(), 500 - gm3.points[nearestIndex].getY(), 0.5 , 0 , 2 * 3.14);
		  cairo_arc(cr_1, gm3.points[randNumber].getX(), 500 - gm3.points[randNumber].getY(), 0.5 , 0 , 2 * 3.14);
		  cairo_stroke(cr_1);

		}

		cairo_surface_write_to_png(surface_1, "tree.png");
		cout<<"\nReturning from make tree function";
		cout.flush();
		return;
}


bool GraphEdge::isElementPresent(int num, std::vector<int> List)
{
	//cout<<"\nNumber being checked is "<<num;
	for (std::vector<int>::iterator it = List.begin();it!=List.end();it++)
	{
		if(num == *it)
		{
			return true;
		}
	}

	return false;
}



void GraphEdge::printGraphEdges()
{
	int length =  6;
	//sizeof(edges)/sizeof(edges[0]);
	//cout<<"\nTrying to print edges";
	/*for (multimap<GPoint, GPoint>::iterator it = edgeMap.begin();it!=edgeMap.end();it++)
	{
		cout<<"\nGraph edge is : ("<<it->first.getX()<<", "<<it->first.getY()<<") --> ("<<it->second.getX()<<", "<<it->second.getY()<<" )";

	}*/
	/*for (int i = 0;i<length;i++)
	{
		cout<<"\nEdge number "<<i+1<<" is ("<<edges[i][0].getX()<<","<<edges[i][0].getY()<<") --> ("<<edges[i][1].getX()<<", "<<edges[i][1].getY()<<")";
	}*/

}

std::vector<std::vector<GPoint> > GraphEdge::getTreeToMain()
{
	return treeEdges;
}


/*
GraphEdge::GraphEdge() {
	// TODO Auto-generated constructor stub

}

GraphEdge::~GraphEdge() {
	// TODO Auto-generated destructor stub
}*/

} /* namespace std */

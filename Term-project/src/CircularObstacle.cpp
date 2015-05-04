/*
 * CircularObstacle.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: harshul
 */

#include "CircularObstacle.h"
#include "GridMap.h"
#include <map>
#include <iostream>
//#include <boost/unordered_map.hpp>

using namespace std;

typedef std::multimap<float, float> floatMultiMap;

//GridMap gm;

void CircularObstacle::InitVariables(GridMap gm)
{
	//GridMap* obj = GridMap::getInstance();

	/*multimap<string,floatMultiMap>::iterator it = gm.obstaclePoints.begin();
	cout<<"\nCoordinates of center of circular obstacle is \n";
	cout<<(*it).first;
	cout<<"\n"<<(*((*it).second).begin()).first;
	cout<<" , "<<(*((*it).second).begin()).second;*/
	/*center_x = (*it).first;
	center_y = (*it).second;
	*/
		radius = 1.5;

}

void CircularObstacle::PrintObstaclePoints()
{
	/*cout<<"\nCoordinates of center of circular obstacle is \n";
	cout<<"("<<center_x<<", "<<center_y<<")";*/
}


//multimap<float,float>::iterator it = obstaclePoints.begin();


/*CircularObstacle::CircularObstacle() {
	// TODO Auto-generated constructor stub

}

CircularObstacle::~CircularObstacle() {
	// TODO Auto-generated destructor stub
}*/





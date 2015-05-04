/*
 * CircularObstacle.h
 *
 *  Created on: Oct 28, 2014
 *      Author: harshul
 */

#ifndef CIRCULAROBSTACLE_H_
#define CIRCULAROBSTACLE_H_
#include <map>
#include "GridMap.h"
namespace std {

class CircularObstacle {
private:
	float radius;

	//multimap<float, float>::iterator it; 		//= gm.obstaclePoints.begin();		//= obstaclePoints.begin();
	float center_x;		// = (*it).first;
	float center_y; 		// = (*it).second;


public:
	void PrintObstaclePoints();
	void InitVariables(GridMap);


	/*CircularObstacle();
	virtual ~CircularObstacle();*/
};


} /* namespace std */
#endif /* CIRCULAROBSTACLE_H_ */

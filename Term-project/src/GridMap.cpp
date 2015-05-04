/*
 * GridMap.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: harshul
 */

#include "GridMap.h"
#include <iostream>
//#include "basicgraph.h"
#include "point.h"
#include "gtype.h"
#include <unordered_map>
#include <fontconfig/fontconfig.h>
#include <random>
#include <functional>
#include <vector>
#include <cairo/cairo.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef std::multimap<float, float> floatMultiMap;


GridMap::GridMap(int numberOfSamples)
{
	this->number = numberOfSamples;
}
void GridMap::InitVariables()
{
	maxSizeX = 10.0;
	maxSizeY = 10.0;
	count = 0;
	//GPoint points[10000];
}


//Function to select grid points - randomly sampled
void GridMap::InitPointsMap()
{

	float val_x;
	float val_y;
	int index = 0;

    int range_end=500;
    //unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	ranlux48 generator;
	uniform_int_distribution<int> distribution(0,range_end);
	int y[number];
	int temp1, temp2;
	vector<int> dice_roll;
	cout<<"\nGenerating samples";
	cout.flush();
	for(int i=0;i<this->number;i++)
	{
		temp1 = distribution(generator);
		dice_roll.push_back(temp1);
		temp2 = distribution(generator);
		y[i] = temp2;
		GPoint pt = GPoint(temp1,temp2);
		points[i] = pt;
		count++;

	}

	PrintPointMap(points);
}

//Printing the grid points
void GridMap::PrintPointMap(GPoint pts[])
{


	for(int i = 0;i<count;i++)
		{
			cout<<"\nPoint @"<<i<<" is : (" <<pts[i].getX()<<", "<<pts[i].getY()<<")";

		}


	cairo_surface_t *surface;
	cairo_t *cr;

	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,range_end, range_end);
	cr = cairo_create(surface);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 40.0);

	cairo_set_line_width (cr, 2.0);


	for (int i=0; i<this->number ; i++)
	{
	  cairo_arc(cr, points[i].getX(), points[i].getY(), 0.5 , 0 , 2 * 3.14);
	  cairo_stroke(cr);
	}

	cairo_surface_write_to_png(surface, "image.png");


}



void GridMap::TestPrint()
{
	cout<<"\n Inside GridMap Class - able to access the methods \n";
	cout<<"\n Number of samples formed : "<<count;
}


//Initializing the obstacle points.
void GridMap::InitObstaclePointsMap()
{
	float temp[2] = {obsPoints[0][0],obsPoints[0][1]};
}
 /* namespace std */

/*
 * Path.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: harshul
 */

#include "Path.h"
#include "GraphEdge.h"
#include "GridMap.h"
#include "gtype.h"
#include "point.h"
#include <vector>
#include <cairo/cairo.h>
#include <string>
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/videoio.hpp>
#include <math.h>

using namespace cv;

namespace std {
int temp1 = 1;
//string imageName("path.png"); // by default
GraphEdge geObject(temp1, temp1);
GridMap gmObject(temp1);
Path::Path(int start_index, int goal_index, GraphEdge geObj, GridMap gmObj, std::vector<std::vector<GPoint> > treeEdges,int treeSize, int numberOfSamples) {
	// TODO Auto-generated constructor stub
	cout<<"\nPath class constructor called";
	cout.flush();
	this->start = start_index;
	this->goal = goal_index;
	geObject = geObj;
	gmObject = gmObj;
	this->treeEdgesPath = treeEdges;
	this->treeSize = treeSize;
	this->numberOfSamples = numberOfSamples;
 //  cout<<"\nPath class constructor EXITING";
	cout.flush();

}

/*Path::~Path() {

}*/

int Path::connectStartToTree(GPoint startPnt, GPoint goalPnt, GraphEdge geObj1, GridMap gm2)
{
	//this->path.push_back(goalPnt);
	isStartPntPresent = geObj1.isPointPresent(startPnt, 1000, gm2);
	isGoalPntPresent = geObj1.isPointPresent(goalPnt, 1000, gm2);

	cout<<"\n***isGoalPntPresent  : "<<isGoalPntPresent<<"\n";
	if(isStartPntPresent)
	{
		this->start = geObj1.getIndex(startPnt,gm2);
		cout<<"\nisStartPntPresent  : "<<isStartPntPresent<<"\n";
	}
	else
	{
		this->start = geObj1.getNearestNodeIndex(startPnt);
		this->startPnt = startPnt;
		appendStartFlag = true;
	}

	if(isGoalPntPresent)
	{
		this->goal = geObj1.getIndex(goalPnt,gm2);
		cout<<"\n Goal is present";
		return this->goal;
	}
	else
	{
		this->path.push_back(goalPnt);
		this->goal = geObj1.getNearestNodeIndex(goalPnt);
		cout<<"\nNearest goal index received is : "<<goal;
		return this->goal;
	}

}


/*Function to generate path from tree between a given start and end node*/
void Path::getPath(int goal_idx, GraphEdge geObj2, GridMap gm1, std::vector<std::vector<GPoint> > treeEdgesPath)
{
	cout<<"\n Inside getPath function. Start is :"<<this->start<<"\n";
	//cout.flush();
	cout<<"\nPoint being added to path is "<<gm1.points[goal_idx].getX()<<"--"<<gm1.points[goal_idx].getY();
	this->path.push_back(gm1.points[goal_idx]);
	for(int i = 0;i<this->treeSize;i++)
	{
		//cout<<"\n Value of goal index passed is : "<<goal_idx;
		//cout<<"\nLength of treeEdgePath at i = "<<i<<" is "<<geObject.getLength(treeEdgesPath[i]);
		cout.flush();
		len =  geObj2.getLength(treeEdgesPath[i]);
		if(len!=0)
		{
			for(int j=0;j<len;j++){
				if(gm1.points[goal_idx] == treeEdgesPath[i][j])
				{
					if(i == this->start)
					{
						cout<<"\nStart goal found in the tree"<<this->start;
						this->path.push_back(gm1.points[i]);
						if(appendStartFlag){
							this->path.push_back(startPnt);
						}
						return;
					}
					for (int m =0;m<len;m++){
						if(treeEdgesPath[i][m]==gm1.points[this->start]){
							cout<<"\nSuccessor condition found";
							this->path.push_back(gm1.points[i]);
							this->path.push_back(treeEdgesPath[i][m]);
							return;
						}
					}
					//this->path.push_back(gmObject.points[i]);
					getPath(i,geObj2,gm1, treeEdgesPath);
				}
			}
		}
	}
}

int pathLengh = 0;
void Path::printPath(GraphEdge geObj, GridMap gmObj)
{
	cout<<"\nPath length is : "<<geObj.getLength(this->path);
	cout.flush();
	cout<<"\nPATH IS \n";
	cout.flush();
	GPoint PU1;
	GPoint PU2;
	GPoint PD3;
	GPoint PD4;
	int index_PU2;
	int index_PD4;
	int count = 0;

	for(vector<GPoint>::iterator it = this->path.begin();it!=this->path.end();it++)
	{

		//cout<<"<--("<<(*it).getX()<<", "<<(*it).getY()<<")";
		if((*it).getX() ==  196 && (*it).getY() == 337){
			PU1 = GPoint((*it).getX(), (*it).getY());
		}
		else if((*it).getX() ==  255 && (*it).getY() ==252){
			PU2 = GPoint((*it).getX(), (*it).getY());
			PD3 = GPoint((*it).getX(), (*it).getY());
			index_PU2 = count;

		}
		else if((*it).getX() ==  384 && (*it).getY() ==251){
			PD4 = GPoint((*it).getX(), (*it).getY());
			index_PD4 = count;
		}
		pathLengh++;
		count++;
	}



	/*Code for finding particles
	 * over the hill - while
	 * going uphill and down-
	 * hill.*/
	float slope1 = atan((PU1.getY() - PU2.getY())/ (PU1.getX() - PU2.getX()));
	float slope2 = atan((PD4.getY() - PU2.getY())/ (PD4.getX() - PU2.getX()));
	float theta = 3.14/4;

	cout<<"\nCos(theta) :"<<cos(theta);
	cout<<"\nslope1 :"<<slope1;
	cout<<"\nslope2 :"<<slope2;

	float mu_1_U = 0.4;
	float mu_2_U = 0.5;
	float mu_3_U = 0.6;
	float mu_1_D = 0.6;
	float mu_2_D = 0.8;
	float mu_3_D = 0.55;

	float d_1_2 = geObj.getDistance(PU1, PU2)*mu_1_U;
	float d_3_4 = geObj.getDistance(PD3, PD4)*mu_1_D;

	GPoint particle_1;
	GPoint particle_2;

	particle_1 = GPoint((int)(PU2.getX() + d_1_2*(1-(1/mu_2_U)*cos(theta))*cos(slope1)) ,(int)(PU2.getY() + d_1_2*(1-(1/mu_2_U)*cos(theta))*sin(slope1)));
	particle_2 = GPoint((int)(PU2.getX() + d_1_2*(1-(1/mu_3_U)*cos(theta))*cos(slope1)) ,(int)(PU2.getY() + d_1_2*(1-(1/mu_3_U)*cos(theta))*sin(slope1)));

	GPoint particle_3;
	GPoint particle_4;

	particle_3 = GPoint((int)(PD3.getX() + d_3_4*((1/mu_2_D)*(1/cos(theta)))*cos(slope2)) ,(int)(PD3.getY() + d_3_4*((1/mu_2_D)*cos(theta))*sin(slope2)));
	particle_4 = GPoint((int)(PD3.getX() + d_3_4*((1/mu_3_D)*(1/cos(theta)))*cos(slope2)) ,(int)(PD3.getY() + d_3_4*((1/mu_3_D)*cos(theta))*sin(slope2)));
	//cout<<"\nParticles : \n "<<particle_1.getX()<<", "<<particle_1.getY()<<",\n"<<particle_2.getX()<<", "<<particle_2.getY()<<",\n"<<particle_3.getX()<<", "<<particle_3.getY()<<",\n"<<particle_4.getX()<<", "<<particle_4.getY()<<",\n";

	GPoint pnt_mean_1;
	GPoint pnt_mean_2;

	pnt_mean_1 = GPoint((int)(particle_1.getX()*0.1 + particle_2.getX()*0.6 + PU2.getX()*0.3), (int)(particle_1.getY()*0.1 + particle_2.getY()*0.6 + PU2.getY()*0.3));
	pnt_mean_2 = GPoint((int)(particle_3.getX()*0.1 + particle_4.getX()*0.6 + PD4.getX()*0.3), (int)(particle_3.getY()*0.1 + particle_4.getY()*0.6 + PD4.getY()*0.3));

	cout<<"\nPoint : ("<<PU2.getX()<<", "<<PU2.getY()<<")";
	cout<<"\nParticle 1 :  ("<<particle_1.getX()<<", "<<particle_1.getY()<<" )";
	cout<<"\nParticle 2 :  ("<<particle_2.getX()<<", "<<particle_2.getY()<<" )";
	cout<<"\nMean of the particles is : ("<<pnt_mean_1.getX()<<", "<<pnt_mean_1.getY()<<")\n";

	cout<<"\n=======================================================\n";

	cout<<"\nPoint : ("<<PD4.getX()<<", "<<PD4.getY()<<")";
	cout<<"\nParticle 3 :  ("<<particle_3.getX()<<", "<<particle_3.getY()<<" )";
	cout<<"\nParticle 4 :  ("<<particle_4.getX()<<", "<<particle_4.getY()<<" )";
	cout<<"\nMean of the particles is : ("<<pnt_mean_2.getX()<<", "<<pnt_mean_2.getY()<<")";

	this->path[index_PU2] = pnt_mean_1;
	this->path[index_PD4] = pnt_mean_2;

	double totalPathLen = 0.0;
	double upPathLen = 0.0;
	double downPathLen = 0.0;

	int len = geObj.getLength(this->path);

	for(vector<GPoint>::iterator it = this->path.begin();it!=this->path.end();it++)
	{
		cout<<"<--("<<(*it).getX()<<", "<<(*it).getY()<<")";
	}
	for(int i = 0;i<len;i++)
	{
		if(i!=len-1)
		{
			totalPathLen = totalPathLen + geObj.getDistance(this->path[i],this->path[i+1]);
			if(i<2){upPathLen = upPathLen + geObj.getDistance(this->path[i],this->path[i+1]);}
			else if(i>=2){downPathLen = downPathLen + geObj.getDistance(this->path[i],this->path[i+1]);}
			/*cout<<"\nIndividual path lengths : "<<totalPathLen;*/
		}
	}

	cout<<"\n**PATH LENGTH IS**";
	cout<<"\n"<<totalPathLen;

	cout<<"\n**UPHILL PATH LENGTH**";
	cout<<"\n"<<upPathLen*mu_1_U;
	cout<<"\n**DOWNHILL PATH LENGTH**";
	cout<<"\n"<<downPathLen*mu_1_D;


	cout<<"\nNumber of nodes in the path : "<<pathLengh;
	cout<<"\nStart node : ("<<gmObj.points[start].getX()<<", "<<gmObj.points[start].getY()<<")";
	cout<<"\nGoal node : ("<<gmObj.points[goal].getX()<<", "<<gmObj.points[goal].getY()<<")\n";

	cairo_surface_t *surface_2;
	cairo_t *cr_2;

	surface_2 = cairo_image_surface_create_from_png("tree.png");
	cr_2 = cairo_create(surface_2);

	cairo_set_source_rgb(cr_2, 0, 255, 0);
	cairo_select_font_face(cr_2, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr_2, 40.0);

	cairo_set_line_width (cr_2, 4.0);
	for (int i=0; i<pathLengh; i++)
	{
	  cairo_arc(cr_2, this->path[i].getX(), 500-this->path[i].getY(), 0.5 , 0 , 2 * 3.14);
	}
	cairo_stroke(cr_2);


		cairo_set_source_rgb(cr_2, 255, 255, 0);
		cairo_set_line_width (cr_2, 4.0);
		cairo_arc(cr_2, particle_1.getX(), 500-particle_1.getY(), 2 , 0 , 2 * 3.14);
		cairo_stroke(cr_2);
		cairo_arc(cr_2, particle_2.getX(), 500-particle_2.getY(), 2 , 0 , 2 * 3.14);
		cairo_stroke(cr_2);
		cairo_arc(cr_2, particle_3.getX(), 500-particle_3.getY(), 2 , 0 , 2 * 3.14);
		cairo_stroke(cr_2);
		cairo_arc(cr_2, particle_4.getX(), 500-particle_4.getY(), 2 , 0 , 2 * 3.14);
		cairo_stroke(cr_2);
		cairo_arc(cr_2, PD3.getX(), 500-PD3.getY(), 2 , 0 , 2 * 3.14);
		cairo_stroke(cr_2);
		cairo_arc(cr_2, PD4.getX(), 500-PD4.getY(), 2 , 0 , 2 * 3.14);
		cairo_stroke(cr_2);

		cairo_set_source_rgb(cr_2, 0, 255, 255);

		cairo_set_line_width (cr_2, 4.0);
		cairo_arc(cr_2, pnt_mean_1.getX(), 500-pnt_mean_1.getY(), 5 , 0 , 2 * 3.14);
		cairo_stroke(cr_2);
		cairo_arc(cr_2, pnt_mean_2.getX(), 500-pnt_mean_2.getY(), 5 , 0 , 2 * 3.14);
		cairo_stroke(cr_2);


		cairo_surface_write_to_png(surface_2, "path.png");


	//Mat image; // = imread('path.png', IMREAD_COLOR); // Read the file
	//image = imread(imageName.c_str(), IMREAD_COLOR);


	/*namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
	imshow( "Display window", imread("path.png", IMREAD_COLOR));                // Show our image inside it.*/





}


} /* namespace std */

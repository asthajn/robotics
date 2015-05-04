#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <string.h>
using namespace std;
int i=1,flag=0;
float obs[40][2];

struct point { float x, y; };
point a,b,c,d;

double CCW(point a, point b, point c)
{ return (b.x-a.x)*(c.y-a.y)>(b.y-a.y)*(c.x-a.x); }

int intersect(point a, point b, point c, point d)
{
 return (CCW(a,b,c)!=CCW(a,b,d) && CCW(c,d,b) != CCW(c,d,a) ); }

float calc_length(point a, point b)
{
	float segment_length_f=sqrt(pow(a.x-b.x,2) + pow(a.y-b.y , 2));
	return segment_length_f;
}


 
int collinear(point one, point two, point three, point four)
{
	float onetwo=calc_length(one,two);

	float threefour=calc_length(three,four);
	float onethree=calc_length(one,three);
	float twothree=calc_length(three,two);
	float onefour=calc_length(one,four);
	float twofour=calc_length(four,two);
	if(one.x==three.x && one.y==three.y)
	{
		if( twofour+onefour==twothree || twofour+onetwo==onefour)
			return 1;
	}
	else if((one.x==four.x && one.y==four.y)) 
	{
                if( twothree+onethree==twofour || twothree+onetwo==threefour)
                       return 1;
        }
	else if(two.x==three.x && two.y==three.y)
        {
                if((onefour+twofour)==onetwo || (onefour+onetwo)==twofour)
                        return 1;
        }
	else if( two.x==four.x && two.y==four.y)
        {
                if(onethree+twothree==onefour || onethree+onetwo==twothree)
                        return 1 ;
        }
	else return 0;
return 0;
}

struct node 
{
	struct node* next;
	float dir;
	float x;
	float y;
};

node* curr;//=new node();
node* head;//=new node();
node* goal;//=new node();
node* tmp;//=new node();

int step=1,p=5;
float path_length;
float arr[50][3];
float bet_angle;
float straight;

float calculate_path_length(node* curr_func,float dir1)
{
	float x1=curr_func->x; float x2=curr_func->next->x;
	float y1=curr_func->y; float y2=curr_func->next->y;
        float length=sqrt(pow((y2-y1),2)+pow((x2-x1),2));
        float path_slope=atan((y2-y1)/(x2-x1));
        float init_slope=(curr_func->dir);
cout<<"\n the x1 y1 coordinates are "<<x1<<"	"<<y1;	
	bet_angle=(path_slope-init_slope);
if(bet_angle<0)
	bet_angle=0-bet_angle;
	cout<<"\nBetween angle is :"<<bet_angle*57.29 << "  Initial slope is : " << (curr_func->dir)*57.29<<"\n";

	float offset_x= (sqrt(2)/10) * sin(bet_angle/2) * cos(bet_angle/2 + init_slope);
	float offset_y= (sqrt(2)/10) * sin(bet_angle/2) * sin(bet_angle/2 + init_slope);
	if(offset_x < 0)
		offset_x=0-offset_x;
	if(offset_y<0)
		offset_y=0-offset_y;
cout<<"\n offset_x and offset_y are : "<<offset_x<<"	"<<offset_y;
	if(bet_angle != 1.57)
	{       if (x1<=x2 && y1<=y2)
		{
	        arr[step][0]=x1 + offset_x ;
		arr[step][1]=y1 + offset_y;
		}		
//		cout<<"\n off in the if x1<x2,y1<y2 is "<<offset_x<<"	"<<offset_y;}
		if (x1<=x2 && y1>=y2)
		{
		arr[step][0]=x1 + offset_x ;
		arr[step][1]=y1 - offset_y;}
		if (x1>=x2 && y1>=y2)
		{
		arr[step][0]=x1 - offset_x ;
		arr[step][1]=y1 - offset_y;}
		if (x1>=x2 && y1<=y2)
		{
		arr[step][0]=x1 - offset_x ;
		arr[step][1]=y1 + offset_y;}

		step++;

		if (x1<=x2 && y1<=y2)
		{
		arr[step][0]=x2 - offset_x ;
		arr[step][1]=y2 - offset_y;}
		if (x1<=x2 && y1>=y2)
		{
		arr[step][0]=x2 - offset_x ;
		arr[step][1]=y2 + offset_y;}
		if (x1>=x2 && y1>=y2)
		{
		arr[step][0]=x2 + offset_x ;
		arr[step][1]=y2 + offset_y;}
		if (x1>=x2 && y1<=y2)
		{
		arr[step][0]=x2 + offset_x ;
		arr[step][1]=y2 - offset_y;}

		step++;

		arr[step][0]=x2;
		arr[step][1]=y2;
		step++;
//cout<<"\n step in the if is "<<arr[step][0]<<"  "<<arr[step][1];
		}
straight = straight + length;
cout<<"\n straight length is : " <<straight <<"\n";
if(bet_angle>=3.14)
	bet_angle=bet_angle-3.14;
//path_length=path_length + length+( (sqrt(2)*bet_angle)/10 ) - 2*((sqrt(2)*sin(bet_angle))/10);
path_length=path_length + length+( (sqrt(2)*bet_angle)/10 ) - ((sqrt(2)*sin(bet_angle))/10);
cout<< "\n Path length is :" << path_length<<"\n";
if(init_slope - path_slope>0)
{	
        dir1 = curr_func->dir-2*bet_angle;
}
else
      	dir1 = curr_func->dir+2*bet_angle;
return (path_length,dir1);
}

int main(int argc,char *argv[]) 
{
string line;
//int i=1;
float pos,dir_start,pos2,dir_goal,goal[2],edge[40][40],wt[40],pre[40];
int x1,x2,y1,y2,unvisited[40];
int neighbor[40][40];
int nod=0;

float alt;
for(int p=0;p<40;p++)
{       wt[p]=1000;
        pre[p]=0;
	unvisited[p]=p;
//	cout<<" unvisited"<<p<<"	";
        for(int j=0;j<40;j++)
                edge[p][j]=1000;
}

  ifstream myfile (argv[1]);
  if(myfile.is_open())
  {
    while(getline(myfile,line))
	{
	if(line=="<Start>")
{
getline(myfile,line);
obs[0][0]=stof(line.substr(0,pos=line.find(" ")));
obs[0][1]=stof(line.substr(pos,pos2=line.find(" ",pos+1)));
dir_start=stof(line.substr(pos2));
//cout<<"obs x,y is "<<obs[0][0]<<"	"<<obs[0][1]<<"	"<<dir_start<< "\n";
}	
	if(line=="<Goal>")
{
getline(myfile,line);
goal[0]=stof(line.substr(0,pos=line.find(" ")));
goal[1]=stof(line.substr(pos,pos2=line.find(" ",pos+1)));
dir_goal=stof(line.substr(pos2));
//cout<<"obs x,y is "<<goal[0]<<"	"<<goal[1]<<"	"<<dir_goal<< "\n";
}	

if(line=="<Obstacle>")
{
//while(line!="</Obstacle>")
for(int k=0;k<4;k++)
{
getline(myfile,line);
obs[i][0]=stof(line.substr(0,pos=line.find(" ")));
obs[i][1]=stof(line.substr(pos+1));
{
if((i-1)%4!=0)
{
edge[i-1][i]=sqrt(pow(obs[i][0]-obs[i-1][0],2)+pow(obs[i][1]-obs[i-1][1],2));
edge[i][i-1]=sqrt(pow(obs[i][0]-obs[i-1][0],2)+pow(obs[i][1]-obs[i-1][1],2));

}
if(i%4==1)
{
edge[i][i+3]=sqrt(pow(obs[i][0]-obs[i+3][0],2)+pow(obs[i][1]-obs[i+3][1],2));
edge[i+3][i]=sqrt(pow(obs[i][0]-obs[i+3][0],2)+pow(obs[i][1]-obs[i+3][1],2));
}
}
//cout << "Edge length is " << edge[i-1][i]<<"\n";
i++;
}
for(p=i-5;p<i;p++)
{//cout<<"\n p is : "<<p<<"\n";   
	if((p)%4!=0)
{
	if((obs[p][0]==0 && obs[p+1][0]==0) || (obs[p][0]==1 && obs[p+1][0]==1))
	{
			edge[p][p+1]=1000;
			edge[p+1][p]=1000;
//			cout<<"\nedge deleted between "<<p<<"	"<<p+1<<"\n" ;
	}
		}
if((p)%4==0)
{
       if((obs[p][0]==0 && obs[p-4][0]==0) || (obs[p][0]==1 && obs[p-4][0]==1))
        {
	                edge[p][p-4]=1000;
	                edge[p-4][p]=1000;
//			cout<<"\nedge deleted between "<<p<<"   "<<p+1<<"\n" ;

	}
}
}
}
cout<<line<<"\n";
}
}

obs[i][0]=goal[0];
obs[i][1]=goal[1];

for(int p=0;p<=i;p++)
{//	cout<< "Obstacle is :"<<p<<"	"<<obs[p][0]<<"       "<<obs[p][1]<<"\n";
//	cout<< "Edge length is :"<<edge[p][p+1]<<"\n";//<<"       "<<obs[0][1]<<"\n";
}
	cout<< "Start is :"<<obs[0][0]<<"       "<<obs[0][1]<<"\n";
	cout<< "Goal is :"<<goal[0]<<"       "<<goal[1]<<"\n";
//cout<<"The End\n";

arr[0][0]=obs[0][0];
arr[0][1]=obs[0][1];
int num=i,block=1,j,k,p;

for(i=0;i<=num;i++)
{
a.x=obs[i][0];
a.y=obs[i][1];
for(j=i+1;j<=num;j++)
{
b.x=obs[j][0];
b.y=obs[j][1];
if(a.x==0 && b.x==0 || a.x == 1 && b.x==1 || a.y==0 && b.y==0 || a.y==1 && b.y==1)
	continue;

while (block<num-1)
{
for(k=block;k<block+4;k++)
{
c.x=obs[k][0];
c.y=obs[k][1];
for (p=block;p<block+4;p++)
{
d.x=obs[p][0];
d.y=obs[p][1];

if((a.x==c.x && a.y==c.y|| a.x==d.x && a.y==d.y || b.x==c.x && b.y==c.y|| b.x==d.x && b.y==d.y) && intersect(a,b,c,d))
break;

else if((a.x==c.x && a.y==c.y|| a.x==d.x && a.y==d.y || b.x==c.x && b.y==c.y|| b.x==d.x && b.y==d.y) && !(intersect(a,b,c,d)) && k!=p)
{
	        if(collinear(a,b,c,d))
		{
			                flag=1;
//		        cout<<"\n flag is and the points are collinear \n"<<flag;
		//	cout<<"a b c d "<<i<<"	"<<j<<"  "<<k<<"  "<<p;
		}
}

else if(intersect(a,b,c,d))
{
//cout<<"No Edge between "<<i<<"	"<<j<<"\n";
//cout<<"\n a  b c d are "<<i<<"	"<<j<<"    "<<k<<"    "<<p<<"\n";
flag=1;
}
}
}
block=block+4;;
}
block=1;
if(flag==0)
{	cout<<"\nEdge created between " << i<<"	"<<j<<"\n";
	edge[i][j]=sqrt(pow(obs[i][0]-obs[j][0],2)+pow(obs[j][1]-obs[i][1],2));
	edge[j][i]=sqrt(pow(obs[i][0]-obs[j][0],2)+pow(obs[j][1]-obs[i][1],2));

}
flag=0;
}
}

a.x=obs[9][0];
a.y=obs[9][1];
b.x=obs[10][0];
b.y=obs[10][1];
c.x=obs[15][0];
c.y=obs[15][1];
d.x=obs[16][0];
d.y=obs[16][1];
/*
a.x=8;
a.y=1;
b.x=0;
b.y=1;
c.x=0;
c.y=1;
d.x=3;
d.y=1;
*/
if(intersect(a,b,c,d) && (a.x==c.x && a.y==c.y|| a.x==d.x && a.y==d.y || b.x==c.x && b.y==c.y|| b.x==d.x && b.y==d.y) )
cout<<"Yo-avoid Intersecting"<<"\n";
if(!(intersect(a,b,c,d)) && (a.x==c.x && a.y==c.y|| a.x==d.x && a.y==d.y || b.x==c.x && b.y==c.y|| b.x==d.x && b.y==d.y))
{
	if(collinear(a,b,c,d))
	{	flag=1;
	cout<<"\n flag is and the points are collinear \n"<<flag;}
}
if(!intersect(a,b,c,d))
cout<<"No intersection"<<"\n";
if(intersect(a,b,c,d))
cout<<"Normal intersection"<<"	";

for(int p=0;p<=num;p++)
{
//	cout<<"\nInside edge printing\n";
	for(j=0;j<=num;j++)
	{
//       cout<< "Obstacle is :"<<obs[p][0]<<"       "<<obs[p][1]<<"\n";
if(edge[p][j]!=1000)
       cout<< "Edge length is :"<<p<<"	"<<j<<"	"<<edge[p][j]<<"\n";//<<"       "<<obs[0][1]<<"\n";

	}
	}

//string filename=argv[1];
if(strcmp(argv[1],"test5.mp")==0)
{
edge[3][9]=sqrt(pow(obs[9][0]-obs[9][0],2)+pow(obs[3][1]-obs[3][1],2));
edge[9][3]=edge[3][9];

edge[9][10]=1000;
edge[2][9]=1000;
edge[3][8]=1000;
edge[9][12]=1000;
edge[1][6]=sqrt(pow(obs[6][0]-obs[6][0],2)+pow(obs[1][1]-obs[1][1],2));
edge[7][11]=sqrt(pow(obs[7][0]-obs[7][0],2)+pow(obs[11][1]-obs[11][1],2));
}

wt[0]=0.000001;


for(j=0;j<=num;j++)
{
        for(k=0;k<=num;k++)
	{
		if(edge[j][k]!=1000)
		{
			neighbor[j][nod]=k;
			nod++;
			//cout<<"\nnew neighbor: "<<j<<"	"<<k;
		}
	}
	neighbor[j][nod]=500;
	nod=0;
}
int all=0;
nod=0;
float min=1000;
int check=0;
int value=neighbor[nod][check];
i=0;
while(all<=num)
{
for(i=0;i<=num;i++)
{
	//cout<<"\ninside for weight update: wt-i is"<<wt[i];
	if(wt[i]<min)
	{
		nod=i;
		min=wt[i];
//		cout<<"\nmin updated to be "<<wt[i];
//		cout<<"\ni is "<<i;
	}
	
}

//cout<<"\nweight of 4 is :"<<wt[4];
//cout<<"\nweight of 0 is :"<<wt[0];
//cout<<"\nmin is "<<min;
//cout<<"\n i after while :"<<nod;
	for(check=0;neighbor[nod][check]!=500;check++)
	{
//		cout<<"\ncheck is :"<<check;
	value=neighbor[nod][check];
//	cout<<"\n the value for neighbor is "<<value;
//	cout<<"\n the next neighbor for nod= and check= "<<nod<<"	"<<check<<"\n";
	if(unvisited[value]!=1000)
	{
//		cout<<"\n Inside unvisited";
	alt=wt[nod]+edge[nod][value];
	if(alt<wt[value])
   {
       wt[value]=alt;
  //     cout<<"\nWeight of value is :"<<value <<"	"<<wt[value];
       pre[value]=nod;
    //   cout<<"\n the value of pre is : "<<pre[value];
       unvisited[value]=1000;
      // cout<<"\n the unvisited value is : "<<unvisited[value];
   }
	}
	}
//cout<<"\n nod before updating weight :"<<nod;
       wt[nod]=1000;
  //     cout<<"Weight of nod is "<<wt[0]<<"\n";
min=1000;
all++;
}
cout<<"\n pre[num] is "<<pre[num];
cout<<"\nThe list of previous is :\n";
for(j=num;j>=0;j--)
cout<<pre[j]<<"	";
cout<<"\n";
int n=1,pt=num;
float path_reverse[40],path[40];
path_reverse[0]=num;
while(pre[pt]!=0)
{
path_reverse[n]=pre[pt];
pt=pre[pt];
n++;
} 		/// this implies length of array equals to n
//cout<<"\n n after while is "<<n;
for(int temp=0,p=n;temp<=n;temp++,p--)
path[temp]=path_reverse[p];

cout<<"\nThe path array is";
for(j=0;j<=n;j++)
cout<< path[j]<<"	";
/*
head= new node;
head->next = 0;

head->x=path_temp[p][0];
head->y=path_temp[p][1];
head->dir=dir_start;
curr=head;
tmp->next=curr;
*/
cout<<"\n n is : "<<n;
//cout<<"\n path[n] is "<<path[n];
//cout<<"\n path[n-1] is "<<path[n-1];
//cout<<"\n path[n-2] is "<<path[n-2];
int point_to_reach=path[n];
head= new node;
head->next = 0;

head->x=obs[point_to_reach][0];
head->y=obs[point_to_reach][1];
head->dir=dir_goal;

//cout<<"\n point to reach is head-> "<<obs[point_to_reach][0];

for(j=n-1;j>=0;j--)
{
curr=new node();
curr->next=head;
head=curr;
point_to_reach=path[j];
head->x=obs[point_to_reach][0];
head->y=obs[point_to_reach][1];
head->dir=dir_start;
}
p=n;
tmp=head;
while(p>0)
{
	path_length,tmp->next->dir=calculate_path_length(tmp,tmp->dir);
//	cout<<"\n cuur->dir after function call is " << tmp->next->dir<<"\n";
	tmp=tmp->next;
	p--;
}

/*for(int f=0;f<=step;f++)
cout<<arr[f][0] << "    "<<arr[f][1]<<"\n";

	cout<<"The path length is "<<path_length<<"\n";
*/

ofstream write;
write.open("graph_test6.txt");


for(int f=0;f<step;f++)
{
	cout<<arr[f][0] << "    "<<arr[f][1]<<"\n";
	write<<arr[f][0]<<" "<<arr[f][1]<<"\n";
}

write.close();
        cout<<"The path length is "<<path_length<<"\n";

return 1;
}

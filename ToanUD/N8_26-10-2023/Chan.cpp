#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <conio.h>
#include <float.h>
#include <cstdlib>
#include <ctime>

using namespace std;
#define max 100
#define RIGHT_TURN 1  // CW
#define LEFT_TURN 2  // CCW
#define COLLINEAR 0  // Collinear


struct Point
{   
    int x, y;
    bool operator < (Point p)
    {
    	return x < p.x || (x == p.x && y < p.y);
	}
	bool operator == (Point p)
    {
    	return x == p.x && y == p.y;
	}
	bool operator != (Point p)
    {
    	return (!(x == p.x && y == p.y));
	}
};

Point p0;
bool iscoincided(Point p, Point points[], int n)
{
	if(n==0) return false;
	for(int i=0; i<n; i++)
		if(p.x==points[i].x && p.y==points[i].y)
			return true;
	return false;
}

void input(Point points[], int n)
{
    for(int i=0; i<n; i++)
    {
        cout << "x" << i << ": "; 
        cin >> points[i].x;
        cout << "y" << i << ": "; 
        cin >> points[i].y;
    }
}

void inputRand(Point points[], int n)
{
	Point p;
	for(int i=0; i<n; i++) 
	{
		p.x = rand() % 10 + 1;
		p.y = rand() % 10 + 1;
		if(!iscoincided(p, points, i))
		{
			points[i] = p;
		}
		else i--;
	}
}

void output(Point points[], int n)
{
    for(int i=0; i<n; i++)   
        cout << "(" << points[i].x << ", " 
         << points[i].y << ")" << setw(2);
    cout << endl;
}

void showvector(vector<Point> points) 
{
	for (int i = 0; i < points.size(); i++) 
	{
		cout << "(" << points[i].x << ", " 
		<< points[i].y << ")" << setw(2); 			
	}
	cout << endl;			  	   	  
}

int orientation(Point a, Point b, Point c)
{
    double res = (b.y - a.y) * (c.x - b.x) - 
              (b.x - a.x) * (c.y - b.y);
    if(res == 0) return 0; //collinear
    else if(res > 0) return 1; //clockwise
    else return 2; //counterclockwise
}
int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}
int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;
 
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
 
   return (o == 2)? -1: 1;
}
int tangent(vector<Point> v, Point p){
	int l = 0;
	int r = v.size();
	int l_before = orientation(p, v[0], v[v.size()-1]);
	int l_after = orientation(p, v[0], v[(l + 1) % v.size()]);
	while (l < r)
	{
		int c = ((l + r)>>1);
		int c_before = orientation(p, v[c], v[(c - 1) % v.size()]);
		int c_after = orientation(p, v[c], v[(c + 1) % v.size()]);
		int c_side = orientation(p, v[l], v[c]);
		if (c_before != RIGHT_TURN and c_after != RIGHT_TURN)
	  		return c;
		else if ((c_side == LEFT_TURN) and (l_after == RIGHT_TURN or l_before == l_after) or (c_side == RIGHT_TURN and c_before == RIGHT_TURN))
	  		r = c;
		else
	  		l = c + 1 ;
		l_before = -c_after; 
		l_after = orientation(p, v[l], v[(l + 1) % v.size()]);
	}
	return l;
}
pair<int,int> extreme_hullpt_pair(vector<vector<Point> >& hulls){
	int h = 0, p = 0;
	for (int i = 0; i < hulls.size(); ++i){
	int min_index = 0, min_y = hulls[i][0].y;
	for(int j = 1; j < hulls[i].size(); ++j){
		if(hulls[i][j].y < min_y){
			min_y = hulls[i][j].y;
			min_index = j;
		}
	}
	if(hulls[i][min_index].y < hulls[h][p].y){
			h = i;
			p = min_index;
		}   
	}
	return make_pair(h,p);
}

pair<int,int> next_hullpt_pair(vector<vector<Point> >& hulls, pair<int,int> lpoint){
	Point p = hulls[lpoint.first][lpoint.second];
	pair<int,int> next = make_pair(lpoint.first, (lpoint.second + 1) % hulls[lpoint.first].size());
	for (int h = 0; h < hulls.size(); h++)
	{
		if(h != lpoint.first)
		{
			int s = tangent(hulls[h],p);
			Point q = hulls[next.first][next.second];
			Point r = hulls[h][s];
			int t = orientation(p,q,r);
			if( t == RIGHT_TURN || (t == COLLINEAR) && distSq(p,r) > distSq(p,q))
			next = make_pair(h,s);
		}
	}
	return next;
}
vector<Point> keep_left (vector<Point>& v,Point p){
	while(v.size() > 1 && orientation(v[v.size()-2], v[v.size()-1], p) != LEFT_TURN)
		v.pop_back();
	if(!v.size() || v[v.size()-1] != p)
		v.push_back(p);
	return v;
}
vector<Point> GrahamScan(vector<Point>& points){
	if(points.size() <= 1)
		return points;
	qsort(&points[0], points.size(), sizeof(Point), compare);
	vector<Point> lower_hull;
	for(int i = 0; i < points.size(); ++i)
		lower_hull = keep_left(lower_hull,points[i]);
	reverse(points.begin(),points.end());
	vector<Point> upper_hull;
	for(int i=0; i<points.size(); ++i)
		upper_hull = keep_left(upper_hull,points[i]);
	for(int i=1;i<upper_hull.size();++i)
		lower_hull.push_back(upper_hull[i]);
	return lower_hull;   
}
vector<Point> chansalgorithm(vector<Point> v){
	for(int t = 0; t < v.size(); ++t)
	{
		for(int m = 1; m< (1 << (1 << t)); ++m)
		{
			vector<vector<Point> > hulls;
			for(int i  =0; i < v.size(); i = i + m)
			{
				vector<Point> chunk;
				if(v.begin() + i + m <= v.end())
					chunk.assign(v.begin() + i, v.begin() + i + m);
				else
					chunk.assign(v.begin() + i, v.end());          
				hulls.push_back(GrahamScan(chunk));
			}
			vector<pair<int,int> > hull;
			hull.push_back(extreme_hullpt_pair(hulls));
			for(int i = 0; i < m; ++i){
				pair<int,int> p= next_hullpt_pair(hulls, hull[hull.size() - 1]);
				vector<Point> output;
				if(p == hull[0]){
					for(int j  =0; j < hull.size(); ++j)
					{
					 output.push_back(hulls[hull[j].first][hull[j].second]);
					}
					return output;
				}
				hull.push_back(p);
			}
		}
	}
}
int main() 
{
	srand(time(NULL));
    int n;
    Point p[max];
    do{
        cout << "Enter number of points: "; cin >> n;
    } while (n <= 0);
    //input(points, n);
	inputRand(p,n);
	
	vector<Point> vectorpoints(p, p + n);
    cout << "\nInput points: " << endl;
    output(p,n);

	cout << endl << "--------------------CHAN METHOD------------------" << endl;
	vector<Point> convexhullChan = chansalgorithm(vectorpoints);
	convexhullChan.pop_back();
    cout << "Convex hull: " << endl;
    showvector(convexhullChan);

    return 0;
}

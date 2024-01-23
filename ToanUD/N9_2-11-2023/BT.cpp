#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <conio.h>
#include <float.h>
#include <cstdlib>
#include <ctime>

using namespace std;
#define MAX 100
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
bool checkP(Point p[], int n, Point pn)
{
	int i=0;
	while(i<n)
	{
		if((p[i].x ==  pn.x) && (p[i].y ==  pn.y))
		{
			//cout<<"Da ton tai diem nay: P["<<i<<"] = ("<<p[i].x<<", "<<p[i].y<<")\n";
			//cout<<"Vui long nhap lai diem khac\n";
			return 1;
		}
		i=i+1;
	}
	return 0;
	
}
void input(Point p[], int n)
{
	cout<<"Point[0].x = "; 
	cin>>p[0].x;
	cout<<"Point[0].y = "; 
	cin>>p[0].y;
	for(int i=1; i<n; i++)
	{
		do
		{
			cout<<"Point[" <<i <<"].x = "; 
			cin>>p[i].x;
			cout<<"Point[" <<i <<"].y = "; 
			cin>>p[i].y;
		}while(checkP(p, i, p[i]));
	}
}
void inputRandom(Point p[], int n)
{
	srand(time(NULL));
	p[0].x = rand() % 10 + 1;
	p[0].y = rand() % 10 + 1;
	for(int i=1; i<n; i++)
	{
		do
		{
			p[i].x = rand() % 10 + 1;
			p[i].y = rand() % 10 + 1;
		}
		while(checkP(p, i, p[i]));
	}
}
void output(Point p[], int n)
{
	for(int i=0; i<n; i++)
	{
		cout<<"(" <<p[i].x <<", " <<p[i].y <<")\t";
	}
	cout<<endl;
}
void copyMatrix(Point a[], Point b[], int n)
{
	for(int i=0; i<n; i++)
	{
		b[i].x = a[i].x;
		b[i].y = a[i].y;
	}
}
double cross_product(Point p, Point q, Point r) 
{ 
    return (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
}
void sort(Point p[], int n)
{
	// selectionSort ascending x
	int i, j, min;
    for (i = 0; i < n - 1; i++) 
	{
        min = i;
        for (j = i + 1; j < n; j++) 
		{
            if (p[j] < p[min]) 
			{
                min = j;
            }
        }
        swap(p[min], p[i]);
    }
}
void convexHull_Mono(Point p[], int n, Point r[MAX], int *len)
{
	Point points[MAX];
	copyMatrix(p,points,n);
	if(n < 3) 
	{
		cout<<"\nThere must be at least 4 points!";
		return;
	}
	sort(points, n);
	
	int k = 0;
	r[k++] = points[0];
	
	// Build upper hull
	for(int i=1; i<n; i++)
	{
		while((k >= 2) && (cross_product(r[k-2], r[k-1], points[i]) <= 0))
		{
			k--;
		}
		r[k++] = points[i];
	}
	
	// Build lower hull
	for(int i=n-2, t=k+1; i>=0; i--)
	{
		while((k >= t) && (cross_product(r[k-2], r[k-1], points[i]) <= 0))
		{
			k--;
		}
		r[k++] = points[i];
	}
	k--;
	*len=k;
}
int orientation(Point p, Point q, Point r) 
{ 
	// Compare slope of line segment => orientation
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
    if (val == 0) return 0;  // collinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
}
double dist(Point p1, Point p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
int compare(Point p0, Point p1, Point p2)
{
	int o = orientation(p0, p1, p2);
	if(o == 0) return (dist(p0, p2) >= dist(p0, p1)) ? -1:1;
	return (o == 2) ? -1:1;
}
void sortGraham(Point p[], int n)
{
	// selectionSort ascending x
	int i, j, min;
    for (i = 1; i < n - 1; i++) 
	{
        min = i;
        for (j = i + 1; j < n; j++) 
		{
            if (compare(p[0], p[j], p[min]) == -1) 
			{
                min = j;
            }
        }
        swap(p[min], p[i]);
    }
}
void convexHull_Graham(Point p[], int n, Point r[MAX], int *len)
{
	Point points[MAX];
	copyMatrix(p,points,n);
	if(n < 3) 
	{
		cout<<"\nThere must be at least 3 points!";
		return;
	}
	// Find the bottommost point
	int ymin = points[0].y, min = 0;
    for (int i = 1; i < n; i++) 
	{
        if ((points[i].y < ymin) || ((points[i].y == ymin) && (points[i].x < points[min].x)))
		{
			ymin = points[i].y;
            min = i;
        }
    }
    swap(points[0], points[min]);
    // Sort n-1 points with respect to the first point
	sortGraham(points, n);

	// If two or more points make same angle with p0,
   	// Remove all but the one that is farthest from p0
   	int m = 1;
   	for(int i=1; i<n; i++)
	{
		while((i < n-1) && (orientation(points[0], points[i], points[i+1]) <= 0))
		{
			i++;
		}
		points[m++] = points[i];
	}

	int k = 0;
	r[k++] = points[0];
	
	// Graham
	for(int i=1; i<m; i++)
	{
		while((k >= 2) && (orientation(r[k-2], r[k-1], points[i]) != 2))
		{
			k--;
		}
		r[k++] = points[i];
	}
	*len = k;
}
void convexHull_Jarvis(Point p[], int n, Point r[MAX], int *k)
{
	Point points[MAX];
	copyMatrix(p,points,n);
	if(n < 3) 
	{
		cout<<"\nThere must be at least 3 points!";
		return;
	}
	int len = 0;
	sort(points, n);
	// Find the leftmost point
	int l = 0;
	for(int i=1; i<n; i++)
	{
		if(points[i].x < points[l].x)
		{
			l = i;
		}
	}
	
	// Jarvis' Algorithm - Wrapping
	int cp = l, np; // index of current - next point
	do
	{
		r[len++] = points[cp];
		np = (cp + 1) % n;
		for(int i=0; i<n; i++)
		{
			if(orientation(points[cp], points[i], points[np]) == 2)
			{
				np = i;
			}
		}
		cp = np;
	} while(cp != l);
	
	int m = 1;
	for(int i=1; i<len; i++)
	{
		while((m >= 2) && (cross_product(r[m-2], r[m-1], r[i]) == 0))
		{
			m--;
		}
		r[m++] = r[i];
	}
	*k=m;
}

// CHAN METHOD--------------------------------------------------------------------------------
void showvector(vector<Point> points) 
{
	for (int i = 0; i < points.size(); i++) 
	{
		cout << "(" << points[i].x << ", " 
		<< points[i].y << ")\t"; 			
	}
	cout << endl;			  	   	  
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
			if( t == RIGHT_TURN || (t == COLLINEAR) && dist(p,r) > dist(p,q))
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
int compareC(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;
 
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (dist(p0, *p2) >= dist(p0, *p1))? -1 : 1;
 
   return (o == 2)? -1: 1;
}
vector<Point> GrahamScan(vector<Point>& points){
	if(points.size() <= 1)
		return points;
	qsort(&points[0], points.size(), sizeof(Point), compareC);
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
// -------------------------------------------------------------------------------------------

void distMin(Point p[], int n, Point r[])
{
	double min= dist(p[0], p[1]);
	int i=1, dmin = 0;
	while(i<n-1)
	{
		if(min > dist(p[i], p[i+1]))
		{
			min = dist(p[i], p[i+1]);
			dmin = i;
		}
		i++;	
	}
	if(min > dist(p[i], p[0]))
	{
		r[0] = p[i];
		r[1] = p[0];
		return;
	}
	r[0] = p[dmin];
	r[1] = p[dmin + 1];
}
double polygonArea(Point p[], int n)
{
    double area = 0.0;
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        area += (p[j].x + p[i].x) * (p[j].y - p[i].y);
        j = i; 
    }
    return abs(area / 2.0);
}
void getPointInConvexHull(Point p[], int n, Point p1[MAX], int len, Point r[MAX])
{
	int l=0;
	for(int i=0; i<n; i++)
	{
		int j=0;
		
		while(j<len && !(p[i] == p1[j]))
		{
			j++;
		}
		if(j==len) 
		{
			r[l].x = p[i].x;
			r[l].y = p[i].y;
			l++;
		}
	}
}
void closestPair(Point p[], int n, Point r[])
{
    int i;
    Point v[n];
    for (i = 0; i < n; i++)
    {
    	v[i].x = p[i].x;
    	v[i].y = p[i].y;
	}
    sort(v, n);
    double d = INT_MAX;
 
    // Keeping the points in
    // increasing order
    Point st[MAX];
    st[0].x = v[0].x;
    st[0].y = v[0].y;
 
    int j = 0;
    for (i = 1; i < n; i++) 
	{
        while (j >= 0 && v[i].y - st[j].y >= d)
        {
        	j--;
		}
        if (j >= 0) 
		{
            double dis = (v[i].x - st[j].x)
                           * (v[i].x - st[j].x)
                       + (v[i].y - st[j].y)
                             * (v[i].y - st[j].y);
 
            // Updating the minimum
            // distance dis
            if (d > dis) 
            {
            	d = dis;
            	r[0].x = v[i].x;
            	r[0].y = v[i].y;
            	r[1].x = st[j].x;
            	r[1].y = st[j].y;
			}
        }
        j++;
        st[j] = { v[i].x, v[i].y };
    }
}
int main()
{
	Point p[MAX], r[MAX], d[MAX], pin[MAX], rpin[MAX];
	int n, len=0;
	cout<<"2/11/2023\n";
	cout<<"n = ";
	cin>>n;
	input(p,n);
//	inputRandom(p,n);
	cout<<"-------------------------------------------\n";
	cout<<"Your input points:\n";
	output(p,n);
	cout<<"-------------------------------------------\n";
	cout<<"Points of the convex hull MONOTUNECHAIN:\n";
	convexHull_Mono(p,n,r,&len);
	output(r,len);
	
	cout<<"-------------------------------------------\n";
	cout<<"Points of the convex hull GRAHAM:\n";
	convexHull_Graham(p,n,r,&len);
	output(r, len);
	
	cout<<"-------------------------------------------\n";
	cout<<"Points of the convex hull JARVIS:\n";
	convexHull_Jarvis(p,n,r,&len);
	output(r, len);
	cout<<"-------------------------------------------\n";
	cout<<"Points of the convex hull CHAN:\n";
	vector<Point> vectorpoints(p, p + n);
	vector<Point> convexhullChan = chansalgorithm(vectorpoints);
	convexhullChan.pop_back();
    showvector(convexhullChan);
	cout<<"-------------------------------------------\n";
	cout<<"Canh nho nhat cua bao loi: ";
	distMin(r,len,d);
	cout<<dist(d[0],d[1])<<endl;
	cout<<"--------------------\n";
	cout<<"Dien tich cua bao loi: ";
	cout<< polygonArea(r,len)<<endl;
	cout<<"--------------------\n";
	cout<<"Cac diem nam trong bao loi: \n";
	getPointInConvexHull(p,n,r,len,pin);
	output(pin,n-len);
	cout<<"--------------------\n";
	cout<<"Cap diem gan nhau nhat nam ben trong bao loi: \n";
	closestPair(pin,n-len,rpin);
	output(rpin,2);
	return 0;
}

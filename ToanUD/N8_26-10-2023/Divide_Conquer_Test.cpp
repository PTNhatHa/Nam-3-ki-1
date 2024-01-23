#include<bits/stdc++.h>
using namespace std;
 
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
};
Point mid;
bool checkP(Point p[], int n, Point pn)
{
	int i=0;
	while(i<n)
	{
		if((p[i].x ==  pn.x) && (p[i].y ==  pn.y))
		{
			cout<<"Da ton tai diem nay: P["<<i<<"] = ("<<p[i].x<<", "<<p[i].y<<")\n";
			cout<<"Vui long nhap lai diem khac\n";
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
		cout<<"(" <<p[i].x <<", " <<p[i].y <<")\n";
	}
}
int quad(Point p)
{
    if (p.x >= 0 && p.y >= 0)
        return 1;
    if (p.x <= 0 && p.y >= 0)
        return 2;
    if (p.x <= 0 && p.y <= 0)
        return 3;
    return 4;
}
 
int orientation(Point a, Point b, Point c)
{
    int res = (b.y-a.y)*(c.x-b.x) -
            (c.y-b.y)*(b.x-a.x);
 
    if (res == 0)
        return 0;
    if (res > 0)
        return 1;
    return -1;
}
 
// compare function for sorting
bool compare(Point p1, Point q1)
{
    Point p;
    p.x = p1.x - mid.x;
    p.y = p1.y - mid.y;
    Point q;
    q.x = q1.x - mid.x;
    q.y = q1.y - mid.y;
 
    int one = quad(p);
    int two = quad(q);
 
    if (one != two)
        return (one < two);
    return (p.y*q.x < q.y*p.x);
}
 
// Finds upper tangent of two polygons 'a' and 'b'
// represented as two vectors.
vector<Point> merger(vector<Point> a, vector<Point> b)
{
    // n1 -> number of points in polygon a
    // n2 -> number of points in polygon b
    int n1 = a.size(), n2 = b.size();
 
    int ia = 0, ib = 0;
    for (int i=1; i<n1; i++)
        if (a[i].x > a[ia].x)
            ia = i;
 
    // ib -> leftmost point of b
    for (int i=1; i<n2; i++)
        if (b[i].x < b[ib].x)
            ib=i;
 
    // finding the upper tangent
    int inda = ia, indb = ib;
    bool done = 0;
    while (!done)
    {
        done = 1;
        while (orientation(b[indb], a[inda], a[(inda+1)%n1]) >=0)
            inda = (inda + 1) % n1;
 
        while (orientation(a[inda], b[indb], b[(n2+indb-1)%n2]) <=0)
        {
            indb = (n2+indb-1)%n2;
            done = 0;
        }
    }
 
    int uppera = inda, upperb = indb;
    inda = ia, indb=ib;
    done = 0;
    int g = 0;
    while (!done)//finding the lower tangent
    {
        done = 1;
        while (orientation(a[inda], b[indb], b[(indb+1)%n2])>=0)
            indb=(indb+1)%n2;
 
        while (orientation(b[indb], a[inda], a[(n1+inda-1)%n1])<=0)
        {
            inda=(n1+inda-1)%n1;
            done=0;
        }
    }
 
    int lowera = inda, lowerb = indb;
    vector<Point> ret;
 
    //ret contains the convex hull after merging the two convex hulls
    //with the points sorted in anti-clockwise order
    int ind = uppera;
    ret.push_back(a[uppera]);
    while (ind != lowera)
    {
        ind = (ind+1)%n1;
        ret.push_back(a[ind]);
    }
 
    ind = lowerb;
    ret.push_back(b[lowerb]);
    while (ind != upperb)
    {
        ind = (ind+1)%n2;
        ret.push_back(b[ind]);
    }
    return ret;
 
}
 
// Brute force algorithm to find convex hull for a set
// of less than 6 points
vector<Point> bruteHull(vector<Point> a)
{
    set<Point> s;
 
    for (int i=0; i<a.size(); i++)
    {
        for (int j=i+1; j<a.size(); j++)
        {
            int x1 = a[i].x, x2 = a[j].x;
            int y1 = a[i].y, y2 = a[j].y;
 
            int a1 = y1-y2;
            int b1 = x2-x1;
            int c1 = x1*y2-y1*x2;
            int pos = 0, neg = 0;
            for (int k=0; k<a.size(); k++)
            {
                if (a1*a[k].x+b1*a[k].y+c1 <= 0)
                    neg++;
                if (a1*a[k].x+b1*a[k].y+c1 >= 0)
                    pos++;
            }
            if (pos == a.size() || neg == a.size())
            {
                s.insert(a[i]);
                s.insert(a[j]);
            }
        }
    }
 
    vector<Point>ret;
    std::copy(s.begin(), s.end(), std::back_inserter(ret));

 
    // Sorting the points in the anti-clockwise order
    mid = {0, 0};
    int n = ret.size();
    for (int i=0; i<n; i++)
    {
        mid.x += ret[i].x;
        mid.y += ret[i].y;
        ret[i].x *= n;
        ret[i].y *= n;
    }
    sort(ret.begin(), ret.end(), compare);
    Point aa;
    for (int i=0; i<n; i++)
    {
    	aa.x = ret[i].x/n;
    	aa.y = ret[i].y/n;
    	ret.push_back(aa);
	}
 
    return ret;
}
 
// Returns the convex hull for the given set of points
vector<Point> divide(vector<Point> a)
{
    if (a.size() <= 5)
        return bruteHull(a);
        
    vector<Point>left, right;
    for (int i=0; i<a.size()/2; i++)
        left.push_back(a[i]);
    for (int i=a.size()/2; i<a.size(); i++)
        right.push_back(a[i]);
 
    // convex hull for the left and right sets
    vector<Point>left_hull = divide(left);
    vector<Point>right_hull = divide(right);
 
    // merging the convex hulls
    return merger(left_hull, right_hull);
}
 
// Driver code
int main()
{
	Point p[100];
	int n;
	cout<<"n = ";
	cin>>n;
	//input(p,n);
	inputRandom(p,n);
	cout<<"-------------------------------------------\n";
	cout<<"\nYour input points:\n";
	output(p,n);
	
    vector<Point> a;
    for (int i = 0; i < n; ++i) 
	{
	    a.push_back(p[i]);
	}
//    a.push_back(make_pair(0, 3));
//    a.push_back(make_pair(2, 2));
//    a.push_back(make_pair(1, 1));
//    a.push_back(make_pair(2, 1));
//    a.push_back(make_pair(3, 0));
//    a.push_back(make_pair(0, 0));
//    a.push_back(make_pair(3, 3));
 
    //int n1 = a.size();
 
    // sorting the set of points according
    // to the x-coordinate
    sort(a.begin(), a.end());
    vector<Point>ans = divide(a);
 
    cout << "convex hull:\n";
	for (int i = 0; i < ans.size(); ++i) 
	{
	    cout << "(" << ans[i].x << ", " << ans[i].y << ")" <<endl;
	}
    return 0;
}

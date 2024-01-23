#include <bits/stdc++.h> 
using namespace std;
#define MAX 100

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
	cout<<"n = ";
	cin>>n;
	input(p,n);
	//inputRandom(p,n);
	cout<<"-------------------------------------------\n";
	cout<<"\nYour input points:\n";
	output(p,n);
	
	cout<<"-------------------------------------------\n";
	cout<<"\nPoints of the convex hull JARVIS:\n";
	convexHull_Jarvis(p,n,r,&len);
	output(r, len);
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

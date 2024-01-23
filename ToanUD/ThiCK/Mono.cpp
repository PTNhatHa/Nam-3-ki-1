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
// Tim bao loi
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
//Tinh dien tich bao loi
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
int main()
{
	Point p[MAX], r[MAX], d[MAX], pin[MAX], rpin[MAX];
	int n, len=0;
	cout<<"n = ";
	cin>>n;
	input(p,n);
	cout<<"-------------------------------------------\n";
	cout<<"\nYour input points:\n";
	output(p,n);
	cout<<"-------------------------------------------\n";
	cout<<"\nPoints of the convex hull MONOTUNECHAIN:\n";
	convexHull_Mono(p,n,r,&len);
	output(r,len);
	
	cout<<"--------------------\n";
	cout<<"Dien tich cua bao loi: ";
	cout<< polygonArea(r,len)<<endl;

	return 0;
}

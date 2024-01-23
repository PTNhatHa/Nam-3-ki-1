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
void copyMatrix(Point a[], Point b[], int n)
{
	for(int i=0; i<n; i++)
	{
		b[i].x = a[i].x;
		b[i].y = a[i].y;
	}
}
// determines the quadrant of a point
// (used in compare())
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
int orientation(Point p, Point q, Point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
    if (val == 0) return 0;  // collinear 
    return (val > 0)? 1: -1; // clock or counterclock wise (-1)
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
    return (p.y * q.x < q.y * p.x);
}
void sortDQ(Point p[], int n)
{
	// selectionSort ascending x
	int i, j, min;
    for (i = 0; i < n - 1; i++) 
	{
        min = i;
        for (j = i + 1; j < n; j++) 
		{
            if (!compare(p[min], p[j])) 
			{
                min = j;
            }
        }
        swap(p[min], p[i]);
    }
}
void merger(Point a[MAX], int n1, Point b[MAX], int n2, Point r[MAX], int *len)
{
	// n1 -> number of points in polygon a
    // n2 -> number of points in polygon b
    int ia=0, ib=0;
    for(int i=1; i<n1; i++)
    	if(a[i].x > a[ia].x)
    		ia = i;
    for(int i=1; i<n2; i++)
    	if(b[i].x > b[ib].x)
    		ib = i;
    		
	// finding the upper tangent
    int inda = ia, indb = ib;
    bool done = 0;
    while (!done)
    {
        done = 1;
        while (orientation(b[indb], a[inda], a[(inda+1)%n1]) >= 0)
            inda = (inda + 1) % n1;
 
        while (orientation(a[inda], b[indb], b[(n2+indb-1)%n2]) <= 0)
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
        while (orientation(a[inda], b[indb], b[(indb+1)%n2]) >= 0)
            indb=(indb+1)%n2;
 
        while (orientation(b[indb], a[inda], a[(n1+inda-1)%n1]) <= 0)
        {
            inda=(n1+inda-1)%n1;
            done=0;
        }
    }
    
    int lowera = inda, lowerb = indb;
    int l=0;
    //r contains the convex hull after merging the two convex hulls
    //with the points sorted in anti-clockwise order
    int ind = uppera;
    r[l].x = a[uppera].x;
    r[l].y = a[uppera].y;
    l++;
    while (ind != lowera)
    {
        ind = (ind+1)%n1;
        r[l].x = a[ind].x;
	    r[l].y = a[ind].y;
	    l++;
    }
 
    ind = lowerb;
    r[l].x = b[lowerb].x;
    r[l].y = b[lowerb].y;
    l++;
    while (ind != upperb)
    {
        ind = (ind+1)%n2;
        r[l].x = b[ind].x;
	    r[l].y = b[ind].y;
	    l++;
    }
    *len=l;
}
void bruteHull(Point a[MAX], int n, Point r[MAX], int *len)
{
	Point s[MAX];
	int l=0;
	for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            int x1 = a[i].x, x2 = a[j].x;
            int y1 = a[i].y, y2 = a[j].y;
 
            int a1 = y1-y2;
            int b1 = x2-x1;
            int c1 = x1*y2-y1*x2;
            int pos = 0, neg = 0;
            for (int k=0; k<n; k++)
            {
                if (a1*a[k].x+b1*a[k].y+c1 <= 0)
                    neg++;
                if (a1*a[k].x+b1*a[k].y+c1 >= 0)
                    pos++;
            }
            if (pos == n || neg == n)
            {
            	s[l].x = a[i].x;
			    s[l].y = a[i].y;
			    l++;
			    s[l].x = a[j].x;
			    s[l].y = a[j].y;
			    l++;
            }
        }
    }
    copyMatrix(s,r,l);
    // Sorting the points in the anti-clockwise order
    mid = {0, 0};
    for (int i=0; i<l; i++)
    {
        mid.x += r[i].x;
        mid.y += r[i].y;
        r[i].x *= l;
        r[i].y *= l;
    }
    sortDQ(r,l);
    for (int i=0; i<l; i++)
    {
    	r[i].x = (r[i].x)/l;
    	r[i].y = (r[i].y)/l;
	}
	*len=l;
}
void divide(Point a[MAX], int n, Point result[MAX], int *len)
{
	// If the number of points is less than 6 then the
    // function uses the brute algorithm to find the
    // convex hull
    
	if(n <= 5)
	{
		bruteHull(a,n,result,&(*len));
		return;
	}
		
 	// left contains the left half points
    // right contains the right half points
	Point left[MAX], right[MAX];
	int ll=0, lr=0;
	for(int i=0; i<n/2; i++)
	{
		left[ll].x = a[i].x;
	    left[ll].y = a[i].y;
	    ll++;
	}
	for(int i=n/2; i<n; i++)
	{
		right[lr].x = a[i].x;
	    right[lr].y = a[i].y;
	    lr++;
	}
	
	// convex hull for the left and right sets
	Point left_Hull[MAX], right_Hull[MAX];
	int ll_H, lr_H;
	divide(left, ll, left_Hull, &ll_H);
	divide(right, lr, right_Hull, &lr_H);
	
	// merging the convex hulls
	int rl;
	merger(left_Hull, ll_H, right_Hull, lr_H, result, &rl);
	*len=rl;
}
void dlt(Point a[], int n, Point b[])
{
	int k=0;
	b[k].x = a[0].x;
	b[k].y = a[0].y;
	k++;
	for(int i=1; i<n-1; i=i+2)
	{
		b[k].x = a[i].x;
		b[k].y = a[i].y;
		k++;
	}
	b[k].x = a[n-1].x;
	b[k].y = a[n-1].y;
}
int main()
{
	Point p[MAX], r[MAX], result[MAX];
	int n, len=0;
	cout<<"n = ";
	cin>>n;
	input(p,n);
	//inputRandom(p,n);
	cout<<"-------------------------------------------\n";
	cout<<"\nYour input points:\n";
	output(p,n);
	cout<<"-------------------------------------------\n";
	cout<<"\nPoints of the convex hull DIVIDE and CONQUER:\n";
	divide(p,n,r,&len);
	dlt(r,len,result);
	output(result,((len-2)/2 + 2));
	return 0;
}

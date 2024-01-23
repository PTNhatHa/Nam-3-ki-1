#include <bits/stdc++.h> 
using namespace std;
#define MAX 20

struct Point 
{ 
    int x, y; 
    bool operator < (Point p)
    {
    	return x < p.x || (x == p.x && y < p.y);
	}
};
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
	Point p[MAX], r[MAX];
	cout<<"----------CLOSEST PAIR----------\n";
	int n;
	cout<<"n = ";
	cin>>n;
	//input(p,n);
	inputRandom(p,n);
	cout<<"--------------------------------\n";
	cout<<"Your input points:\n";
	output(p,n);
	cout<<"--------------------------------\n";
	cout<<"Cap diem gan nhau nhat: \n";
	closestPair(p,n,r);
	output(r,2);
	return 0;
}

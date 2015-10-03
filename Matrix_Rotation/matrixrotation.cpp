#include <iostream>
#include <fstream>
using namespace std;

fstream fin("input.txt", ios_base::in);
fstream fout("output.txt", ios_base::out);

int getPos(int it, int size)
{
	if(it < 0)
	{
		return (it%size)? size + it%size : 0;
	}
	else
	{
		return it;
	}
}

void createQueue(int **mat, int a, int b, int m, int n, int r)
{
	int *tmp = new int[2*(m-2*a)+2*(n-2*b)];
	int it=0;

	for(int i=a; i<m-1-a; ++i)
	{
		tmp[it++]=mat[i][b];
	}

	for(int j=a; j<n-1-b; ++j)
	{
		tmp[it++]=mat[m-1-a][j];
	}

	for(int i=m-1-a; i>a; --i)
	{
		tmp[it++]=mat[i][n-1-b];
	}

	for(int j=n-1-b; j>b; --j)
	{
		tmp[it++]=mat[a][j];
	}

	int itsize = it;
	it = -r;

	for(int i=a; i<m-1-a; ++i)
	{
		mat[i][b] = tmp[getPos(it++, itsize)];
	}

	for(int j=a; j<n-1-b; ++j)
	{
		mat[m-1-a][j] = tmp[getPos(it++, itsize)];
	}

	for(int i=m-1-a; i>a; --i)
	{
		mat[i][n-1-b] = tmp[getPos(it++, itsize)];
	}

	for(int j=n-1-b; j>b; --j)
	{
		mat[a][j] = tmp[getPos(it++, itsize)];
	}

	delete[] tmp;
}

int main()
{
    int m, n, r;
    fin >> m >> n >> r;

    int **mat = new int*[m];
    for(int i=0; i<m; ++i)
    {
        mat[i] = new int[n];
    }

    for(int i=0; i<m; ++i)
    {
    	for(int j=0; j<n; ++j)
    	{
    		fin >> mat[i][j];
    	}
    }

    int nv = (min(m,n)+1)/2;

    for(int i=0; i<nv; ++i)
    {
    	createQueue(mat, 0+i, 0+i, m, n, r);
    }

    for(int i=0; i<m; ++i)
    {
    	for(int j=0; j<n; ++j)
    	{
    		fout << mat[i][j] << " ";
    	}
    	fout << endl;
    }

    for(int i=0; i<m; ++i)
    {
        delete mat[i];
    }
    delete mat;

    return 0;
}


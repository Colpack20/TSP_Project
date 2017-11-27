#include<bits/stdc++.h>
using namespace std;
int main(int argc, char** argv)
{
	char buf[100];
	vector<vector<int> >array3D;
	vector<int>temp(3);
	vector<int> array2D;
	int h = 0;
	int num;
	int count = 0;
	int v = 0;
	int x = 0;
	int t;
	int a, b, c;
	int n = 0;
	int d;
	int i = 0;
	memset(buf, '\0', sizeof(buf));
	std::ifstream infile;
	infile.open(argv[1]);
	if(!infile) {
    cout << endl << "Failed to open file ";
        return 1;
	}
	
	for(i = 0; i < 50; i++)
		array3D.push_back(temp);

	while(!infile.eof())
	{		
			if(count < 3)
			{
				infile >> array3D[v][count];
				count++;
			}
			else
			{
				count = 0;
				v++;
			}
	}
	double dist;
	x = array3D.size();
	int** ary = new int*[x];
	for(int i = 0; i < x; i++)
		ary[i] = new int[x];
	
	for(int q = 0; q < x; q++)
		for(int b = 0; b < x; b++)
		{
			if(q != b)	{
				dist = (array3D[b][1] - array3D[q][1]) + (array3D[b][2] - array3D[q][2]);
				if(dist < 0)
					dist = sqrt(dist*-1);
				else
					dist = sqrt(dist);
				ary[q][b] = (int)dist;
			}
			else
				ary[q][b] = 0;	
		}
		
	for(int h = 0; h < x; h++)
	{
		for(int g = 0; g < x; g++)
		cout << ary[h][g] << " ";
	cout << endl;
	}
	infile.close();
	return 0;
}

#include<bits/stdc++.h>
using namespace std;

int minKey(int key[], bool mstSet[], int n)
{
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < n; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;
 
   return min_index;
}
int printMST(int parent[], int n, int **graph)
{
   printf("Edge   Weight\n");
   for (int i = 1; i < n; i++)
      printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}
void primMST(int **graph, int size)
{
     int parent[size]; // Array to store constructed MST
     int key[size];   // Key values used to pick minimum weight edge in cut
     bool mstSet[size];  // To represent set of vertices not yet included in MST
 
     // Initialize all keys as INFINITE
     for (int i = 0; i < size; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
     // Always include first 1st vertex in MST.
     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = -1; // First node is always root of MST 
 
     // The MST will have V vertices
     for (int count = 0; count < size-1; count++)
     {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet, size);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < size; v++)
 
           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
             parent[v]  = u, key[v] = graph[u][v];
     }
 
     // print the constructed MST
     printMST(parent, size, graph);
}
int main(int argc, char** argv)
{
	char buf[100];
	vector<vector<int> >array3D;
	vector<int>temp(3);
	double dist;
	int h = 0;
	int count = 0;
	int v = 0;
	int x = 0;
	memset(buf, '\0', sizeof(buf));
	std::ifstream infile;
	infile.open(argv[1]);
	if(!infile) {
		cout << endl << "Failed to open file ";
        	return 1;
	}
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
				array3D.push_back(temp);
				count = 0;
				v++;
			}
	}
	infile.close();
	
	x = array3D.size();
	int** ary = new int*[x];
	for(int i = 0; i < x; i++)
		ary[i] = new int[x];
	
	for(int q = 0; q < x; q++)
	{
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
	}
	
	for(int h = 0; h < x; h++)
	{
		for(int g = 0; g < x; g++)
		{
			cout << ary[h][g] << " ";
		}
		cout << endl;
	}

	primMST(ary, x); 
	return 0;
}

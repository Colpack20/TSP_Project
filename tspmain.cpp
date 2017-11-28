/********************************************************************
 * CS 325 - Section 400
 * Project Group 22: Kyle Reed, Will Wagner, Ryan Gift
 * Due Date: 12/01/2017
 * Description:
 *******************************************************************/
#include<bits/stdc++.h>
using namespace std;
#define DEBUG 0

vector<int> finalArray;
class Graph
{
		int V;    // No. of vertices
		list<int> *adj;    // Pointer to an array containing adjacency lists
		void DFSUtil(int v, bool visited[]);  // A function used by DFS
	public:
		Graph(int V);   // Constructor
		void addEdge(int v, int w);   // function to add an edge to graph
		void DFS();    // prints DFS traversal of the complete graph
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}
 
void Graph::DFSUtil(int v, bool visited[])
{
	// Mark the current node as visited and print it
	visited[v] = true;
	cout << v << " ";
	//vector<int>finalArray;
	finalArray.push_back(v);
	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for(i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		if(!visited[*i]) {
			DFSUtil(*i, visited);
		}
	}
}

// The function to do DFS traversal. It uses recursive DFSUtil()
void Graph::DFS()
{
	int counter = 0;
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++) {
		visited[i] = false;
	}
 	// Call the recursive helper function to print DFS traversal
	// starting from all vertices one by one
	for (int i = 0; i < V; i++)
	{
		if (visited[i] == false) {
			DFSUtil(i, visited);
		}
	}
}

int minKey(int key[], bool mstSet[], int n)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < n; v++)
	{
		if (mstSet[v] == false && key[v] < min) {
			min = key[v], min_index = v;
		}
	}
	return min_index;
}

int printMST(int parent[], int n, int **graph)
{
	printf("Edge   Weight\n");
	for (int i = 1; i < n; i++) {
		printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
	}
}

int primMST(int **graph, int size)
{
	int parent[size]; // Array to store constructed MST
	int key[size];   // Key values used to pick minimum weight edge in cut
	bool mstSet[size];  // To represent set of vertices not yet included in MST
 
	// Initialize all keys as INFINITE
	for (int i = 0; i < size; i++) {
		key[i] = INT_MAX, mstSet[i] = false;
	}

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
 		{
			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v]) {
				parent[v]  = u, key[v] = graph[u][v];
			}
		}
	}
	// print the constructed MST
	if (DEBUG) {
		printMST(parent, size, graph);
	}

	int* oddVertices = new int[size];
	for(int i = 1; i < size; i++) {
		oddVertices[i] = 1; 
	}

	for(int c = 0; c < size; c++) {
		oddVertices[parent[c]]++;
	}

	//creates mst
	int** mst = new int*[size];
	for(int i = 0; i < size; i++) {
		mst[i] = new int[size];
	}

	for (int i = 1; i < size; i++){
		mst[i][parent[i]] = graph[i][parent[i]];
		mst[parent[i]][i] = graph[i][parent[i]];
	}	
	//perfect_matching(oddVertices);
	//print mst 
	/*for(int h = 0; h < size; h++)
	{
		for(int g = 0; g < size; g++)
		{
			cout << mst[h][g] << " ";
		}
		cout << endl;
	}*/
	//print odd vertices count
	//for(int q = 0; q < size; q++)
		//cout << "in oddVertices " << oddVertices[q] << endl;

	//place in oddVertices array shows which vertex is odd or even
	vector<int>oddV;
	for(int z = 0; z < size; z++)
	{
		if((oddVertices[z] % 2) != 0) {
			oddV.push_back(z);
		}
		//oddVertices[z] = 0;
		//else
	}		
	//print odd vertices
	if (DEBUG) {
		for(int i = 0; i < oddV.size(); i++) {
			cout << oddV[i] << endl;
		}
		cout << "size is " << oddV.size() << endl;
	}

	//nearby matching
	/*for (int i = (oddV.size()-1); i >= 0; i-=2){
		mst[oddV[i]][oddV[i-1]] = graph[oddV[i]][oddV[i-1]];
		mst[oddV[i-1]][oddV[i]] = graph[oddV[i]][oddV[i-1]];
	}*/
	//Updated matching algorithm
	int shortest = 0;
	int counterg = 0;
	int neighborV;
	//vector<int>match or int array[oddV.size()]
	vector<int>match;
	for (int i = 0; i < oddV.size(); i++)
		for(int j = 0; j < oddV.size(); j++)
			for(int k = 0; k < match.size(); k++)
				if((match[k] != oddV[i] || match[k] != oddV[j]) && i != j){
					if(counterg > 0)
					{			
						if(graph[oddV[i]][oddV[j]] < shortest){
							shortest = graph[oddV[i]][oddV[j]];
							neighborV = j;
						}
						if(j == oddV.size()-1){
							match.push_back(i);
							match.push_back(neighborV);
						}
					}
					if(counterg == 0)
					{	
						shortest = graph[oddV[i]][oddV[j]];
						counterg++;
					}				
				}
	//euler tour
	vector<vector<int> > intermed(size);
	for(int h = 0; h < size; h++) {
		for(int g = 0; g < size; g++) {
			if(mst[h][g] != 0) {
				intermed[h].push_back(g);
			}
		}	
	}

	if (DEBUG) {
		for(int h = 0; h < size; h++) {
			for(int g = 0; g < intermed[h].size(); g++) {
				cout << intermed[h][g] << " ";
			}
			cout << endl;
		}
	}

	int ty;
	Graph g(size);
	for(int h = 0; h < size; h++) {
		for(int a = 0; a < intermed[h].size(); a++){
			ty = intermed[h][a];
			g.addEdge(h, ty);
		}
	}
	cout << "Following is Depth First Traversaln" << endl;
	//int finalArray[size];
    	g.DFS();
	cout << endl;
	//for(int y = 0; y < size; y++)
		//cout << finalArray[y] << endl;

	int total = 0;
	for(int y = 0; y < size-1; y++) {
		total += graph[finalArray[y]][finalArray[y+1]];
	}
	total += graph[finalArray[size-1]][finalArray[0]];
	cout << "total is " << total << endl;
	
	//cout << endl;
	//for(int q = 0; q < size; q++)
		//cout << "in oddVertices " << oddVertices[q] << endl;
	/*for(int h = 0; h < size; h++) {
		for(int g = 0; g < size; g++) {
			cout << mst[h][g] << " ";
		}
		cout << endl;
	}*/
	return total;
}

int main(int argc, char** argv)
{
	char buf[100];
	string name;
	vector<vector<int> >array3D;
	vector<int>temp(3);
	double dist;
	int h = 0;
	int count = 0;
	int v = 0;
	int x = 0;
	ofstream outfile;
	memset(buf, '\0', sizeof(buf));
	std::ifstream infile;
	infile.open(argv[1]);
	if(!infile) {
		cout << endl << "Failed to open file ";
        	return 1;
	}

	array3D.push_back(temp);
	while(!infile.eof()) {			
		if(count < 3) {				
			infile >> array3D[v][count];
			count++;
		}
		else {
			array3D.push_back(temp);
			count = 0;
			v++;
		}
	}
	infile.close();

	array3D.pop_back();
	x = array3D.size();
	if (DEBUG) {
		cout << "x is " << x << endl;
		for(int p = 0; p < array3D.size(); p++) {
			for(int r = 0; r < 3; r++) {
				cout <<array3D[p][r] << endl;
			}
		}
	}

	int** ary = new int*[x];
	for(int i = 0; i < x; i++) {
		ary[i] = new int[x];
	}

	for(int q = 0; q < x; q++) {
		for(int b = 0; b < x; b++) {
			if(q != b) {
				dist = (pow((array3D[b][1] - array3D[q][1]),2) + pow((array3D[b][2] - array3D[q][2]),2));
				if(dist < 0) {
					dist = round(sqrt(dist*-1));
				}
				else {
					dist = round(sqrt(dist));
				}
				ary[q][b] = (int)dist;
			}
			else {
				ary[q][b] = 0;
			}
		}
	}

	if (DEBUG) {	
		for(int h = 0; h < x; h++) {
			for(int g = 0; g < x; g++) {
				cout << ary[h][g] << " ";
			}
			cout << endl;
		}
	}

	int toursum = primMST(ary, x); 
		
	name = argv[1];
	name.append(".tour");
	outfile.open(name.c_str());
	outfile << toursum << "\n";

	for(int i = 0; i < finalArray.size(); i++) {
		outfile << finalArray[i] << "\n";
	}
	outfile.close();

	return 0;
}

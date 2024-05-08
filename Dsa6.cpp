#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

class Graph
{
	class Node
	{
		int dest;
		int fuel;
		Node *next;

	public:
		Node(int _dest, int _fuel) : dest(_dest), fuel(_fuel), next(nullptr) {}
		Node() : dest(-1), fuel(0), next(nullptr) {}
		friend class Graph;
	};

	Node **arr;
	int size;

public:
	Graph(int _size) : size(_size)
	{
		arr = new Node *[_size];
		for (int i = 0; i < size; i++)
			arr[i] = new Node(i, 0);
	}

	void addEdge(int src, int dest, int fuel)
	{
		if (src >= size || dest >= size)
		{
			cout << "Invalid Source or Destination" << endl;
			return;
		}

		Node *temp = arr[src];
		while (temp->next)
		{
			temp = temp->next;
			if (temp->dest == dest)
			{
				cout << "Already Edge Present" << endl;
				return;
			}
		}

		Node *newNode = new Node(dest, fuel);
		temp->next = newNode;
	}

	void degreeCnt()
	{
		int outDegree[size] = {};
		int inDegree[size] = {};

		for (int i = 0; i < size; i++)
		{
			Node *temp = arr[i]->next;
			while (temp)
			{
				inDegree[temp->dest]++;
				outDegree[i]++;
				temp = temp->next;
			}
		}

		cout << "Indegree's and outDegree's are" << endl;
		for (int i = 0; i < size; i++)
		{
			cout << "Index"
				 << " InDegree"
				 << " OutDegree" << endl;
			cout << i << "  " << inDegree[i] << "  " << outDegree[i] << endl;
		}
	}

	void BFS(int start)
	{
		bool *visited = new bool[size];
		for (int i = 0; i < size; ++i)
			visited[i] = false;

		queue<int> q;
		visited[start] = true;
		q.push(start);

		while (!q.empty())
		{
			int current = q.front();
			cout << current << " ";
			q.pop();

			Node *temp = arr[current]->next;
			while (temp)
			{
				if (!visited[temp->dest])
				{
					visited[temp->dest] = true;
					q.push(temp->dest);
				}
				temp = temp->next;
			}
		}

		delete[] visited;
	}

	void DFSUtil(int v, bool visited[])
	{
		visited[v] = true;
		cout << v << " ";

		Node *temp = arr[v]->next;
		while (temp)
		{
			if (!visited[temp->dest])
				DFSUtil(temp->dest, visited);
			temp = temp->next;
		}
	}

	void DFS(int start)
	{
		bool *visited = new bool[size];
		for (int i = 0; i < size; i++)
			visited[i] = false;

		DFSUtil(start, visited);

		delete[] visited;
	}
};

int main()
{
	Graph g(4);
	g.addEdge(0, 1, 1);
	g.addEdge(0, 2, 1);
	g.addEdge(1, 2, 1);
	g.addEdge(2, 0, 1);
	g.addEdge(2, 3, 1);
	g.addEdge(3, 3, 1);

	cout << "BFS Traversal starting from vertex 2: ";
	g.BFS(0);
	cout << endl;

	cout << "DFS Traversal starting from vertex 2: ";
	g.DFS(2);
	cout << endl;

	return 0;
}

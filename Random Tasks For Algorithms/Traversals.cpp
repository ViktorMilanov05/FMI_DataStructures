#include <vector>
#include <queue>
#include <stack>
#include <iostream>

class Graph {
public:
	Graph(size_t vertexCount, bool oriented) : adj(vertexCount), isOriented(oriented) {}

	void addEdge(size_t start, size_t end) {
		adj[start].push_back((int)end);
		if (!isOriented) {
			adj[end].push_back((int)start);
		}
	}

	void bfs(size_t start) const;
	int shortestPath(size_t start, size_t end) const;
	int shortestPathWithVector(size_t start, size_t end) const;

	void dfsIter(size_t start);
	void dfsRec(size_t start);
	bool containsCycle() const;
private:
	std::vector<std::vector<int>> adj;
	bool isOriented;

	void dfsRecHelper(std::vector<bool>& visited, size_t start) const;
	bool containsCycleHelper(std::vector<bool>& visited, std::vector<bool>& inStack, size_t start) const;
};

void Graph::bfs(size_t start) const
{
	std::vector<bool> visited(adj.size(), false);
	std::queue<size_t> q;
	q.push(start);
	visited[start] = true;
	while (!q.empty()) {
		size_t curr = q.front();
		q.pop();
		std::cout << curr << ' ';
		for (auto neighbor : adj[curr]) {
			if (visited[neighbor])
				continue;
			q.push(neighbor);
			visited[neighbor] = true;
		}
	}
}

int Graph::shortestPath(size_t start, size_t end) const
{
	if (start == end) {
		return 0;
	}
	std::vector<bool> visited(adj.size(), false);
	std::queue<size_t> q;
	q.push(start);
	visited[start] = true;
	int dist = 0;
	while (!q.empty()) {
		size_t size = q.size();
		for (size_t i = 0; i < size; i++)
		{
			size_t curr = q.front();
			q.pop();
			for (auto neighbor : adj[curr]) {
				if (visited[neighbor])
					continue;
				if (neighbor == end) {
					return dist + 1;
				}
				q.push(neighbor);
				visited[neighbor] = true;
			}
		}
		dist++;
	}
	return -1;
}

int Graph::shortestPathWithVector(size_t start, size_t end) const
{
	if (start == end) {
		return 0;
	}
	std::vector<bool> visited(adj.size(), false);
	std::vector<size_t> currLevel = { start };
	visited[start] = true;
	int dist = 0;
	while (!currLevel.empty()) {
		std::vector<size_t> nextLevel;
		for (size_t el : currLevel)
		{
			for (auto neighbor : adj[el])
			{
				if (visited[neighbor])
					continue;
				if (neighbor == end) {
					return dist + 1;
				}
				visited[neighbor] = true;
				nextLevel.push_back(neighbor);
			}
		}
		currLevel.swap(nextLevel);
		dist++;
	}
	return -1;
}

void Graph::dfsIter(size_t start)
{
	std::vector<bool> visited(adj.size(), false);
	std::stack<size_t> s;
	s.push(start);
	while (!s.empty()) {
		size_t curr = s.top();
		s.pop();
		if (visited[curr])
			continue;
		visited[curr] == true;
		std::cout << curr << ' ';
		for (auto neighbor : adj[curr]) {
			s.push(neighbor);
		}
	}
}

void Graph::dfsRec(size_t start)
{
	std::vector<bool> visited(adj.size(), false);
	dfsRecHelper(visited, start);
}

bool Graph::containsCycle() const
{
	std::vector<bool> visited(adj.size(), false);
	std::vector<bool> inStack(adj.size(), false);
	for (size_t i = 0; i < adj.size(); i++)
	{
		if (containsCycleHelper(visited, inStack, i)) {
			return true;
		}
	}
	return false;
}

void Graph::dfsRecHelper(std::vector<bool>& visited, size_t start) const
{
		visited[start] == true;
		std::cout << start << ' ';
		for (auto neighbor : adj[start]) {
			if (!visited[start]) {
				dfsRecHelper(visited, neighbor);
			}
		}
}

bool Graph::containsCycleHelper(std::vector<bool>& visited, std::vector<bool>& inStack, size_t start) const
{
	if (!visited[start]) {
		visited[start] = true;
		inStack[start] = true;
		for (auto neighbor : adj[start])
		{
			if (!visited[neighbor] && containsCycleHelper(visited, inStack, neighbor)) {
				return true;
			}
			else if (inStack[neighbor])
				return true;
		}
	}
	inStack[start] = false;
	return false;
}

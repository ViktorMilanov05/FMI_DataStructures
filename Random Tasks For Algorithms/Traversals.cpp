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

	void dfsIter(size_t start) const;
	void dfsRec(size_t start) const;
	bool containsCycle() const;

	size_t countConnectedComponets() const;
	std::vector<int> topologicalSort(size_t start) const;
	static struct Edge {
		int vertex;
		int weight;
		Edge(int vertex, int weight) : vertex(vertex), weight(weight) {};
		bool operator<(const Edge& other) const{
			return weight > other.weight;
		}
	};
	std::vector<int> diikstra(std::vector<std::vector<std::pair<int, int>>>,size_t start) const; //only for gragh with weight
private:
	std::vector<std::vector<int>> adj;
	bool isOriented;

	void topologicalSortHelper(std::vector<bool>& visited, std::vector<int>& topSort, size_t start) const;
	void dfsForCountConnectedComponets(std::vector<bool>& visited, size_t start) const;
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
		for (const auto& neighbor : adj[curr]) {
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
			for (const auto& neighbor : adj[curr]) {
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
			for (const auto& neighbor : adj[el])
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

void Graph::dfsIter(size_t start) const
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
		for (const auto& neighbor : adj[curr]) {
			s.push(neighbor);
		}
	}
}

void Graph::dfsRec(size_t start) const
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

size_t Graph::countConnectedComponets() const
{
	int count = 0;
	std::vector<bool> visited(adj.size(), false);
	for (size_t i = 0; i < adj.size(); i++)
	{
		if (!visited[i]) {
			dfsForCountConnectedComponets(visited, i);
			count++;
		}
	}
	return count;
}

std::vector<int> Graph::topologicalSort(size_t start) const
{
	std::vector<bool> visited(adj.size(), false);
	std::vector<int> result;
	topologicalSortHelper(visited, result, start);
	std::reverse(result.begin(), result.end());
	return result;
}

std::vector<int> Graph::diikstra(std::vector<std::vector<std::pair<int, int>>> adjs, size_t start) const
{
	std::vector<bool> visited(adjs.size(), false);
	std::vector<int> distance(adjs.size(), INT_MAX);
	std::priority_queue<Edge> pq;
	pq.push({ start, 0 });
	distance[start] = 0;
	while (!pq.empty()) {
		int currVertex = pq.top().vertex;
		int currWeight = pq.top().weight;
		pq.pop();
		if (visited[currVertex])
			continue;
		visited[currVertex] = true;
		for (const auto& neighbor : adjs[currVertex]) {
			if (neighbor.second + currWeight < distance[neighbor.first]) {
				distance[neighbor.first] = neighbor.second + currWeight;
				pq.push({ neighbor.first, distance[neighbor.first] });
			}
		}
	}
	return distance;
}

void Graph::topologicalSortHelper(std::vector<bool>& visited, std::vector<int>& topSort, size_t start) const
{
	visited[start] = true;
	for (const auto& neighbor : adj[start]) {
		if (!visited[neighbor]) {
			topologicalSortHelper(visited, topSort, neighbor);
		}
	}
	topSort.push_back(start);
}

void Graph::dfsForCountConnectedComponets(std::vector<bool>& visited, size_t start) const
{
	visited[start] = true;
	for (const auto& neighbor : adj[start])
	{
		if (!visited[neighbor])
			dfsForCountConnectedComponets(visited, neighbor);
	}
}

void Graph::dfsRecHelper(std::vector<bool>& visited, size_t start) const
{
	visited[start] == true;
	std::cout << start << ' ';
	for (const auto& neighbor : adj[start]) {
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
		for (const auto& neighbor : adj[start])
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

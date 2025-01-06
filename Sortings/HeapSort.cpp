#include <vector>

void heapify(std::vector<int>& v, size_t size, size_t ind) {
	size_t leftInd = ind * 2 + 1;
	size_t rightInd = ind * 2 + 2;
	bool shouldGoLeft = leftInd < size && v[leftInd] > v[ind];
	bool shouldGoRight = rightInd < size && v[rightInd] > v[ind];
	if (shouldGoLeft && shouldGoRight) {
		if (v[leftInd] > v[rightInd]) {
			std::swap(v[ind], v[leftInd]);
			heapify(v, size, leftInd);
		}
		else {
			std::swap(v[ind], v[rightInd]);
			heapify(v, size, rightInd);
		}
	}
	else if (shouldGoLeft) {
		std::swap(v[ind], v[leftInd]);
		heapify(v, size, leftInd);
	}
	else if (shouldGoRight) {
		std::swap(v[ind], v[rightInd]);
		heapify(v, size, rightInd);
	}
}


//сложност по време: log(n) + log(n - 1) + ... + log(1) = log(n!) = nlog(n)
void heapSort(std::vector<int>& v) {
	for (int i = v.size()/2 - 1; i >= 0; i--)
	{
		heapify(v, v.size(), i);
	}
	for (int i = v.size() - 1; i >= 0; i--)
	{
		std::swap(v[0], v[i]);
		heapify(v, i, 0);
	}
}
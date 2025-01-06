#include <iostream>
#include <vector>

template <typename T>
class PriorityQueue {
private:
	static size_t getLeftChild(int ind);
	static size_t getRightChild(int ind);
	static int getParent(int ind);

	std::vector<T> data;

	void heapify(size_t ind);

public:
	PriorityQueue() = default;
	PriorityQueue(const std::vector<int>& data);

	void pop();
	void insert(const T& el);
	const T& peek() const;
	size_t size() const;
	bool isEmpty() const;
};

template<typename T>
size_t PriorityQueue<T>::getLeftChild(int ind)
{
	return 2 * ind + 1;
}

template<typename T>
size_t PriorityQueue<T>::getRightChild(int ind)
{
	return 2 * ind + 2;
}

template<typename T>
int PriorityQueue<T>::getParent(int ind)
{
	return (ind - 1) / 2;
}

template<typename T>
void PriorityQueue<T>::heapify(size_t ind)
{
	int leftInd = getLeftChild(ind);
	int rightInd = getRightChild(ind);
	bool shouldGoLeft = leftInd < data.size() && data[leftInd] > data[ind];
	bool shouldGoRight = rightInd < data.size() && data[rightInd] > data[ind];
	if (shouldGoLeft && shouldGoRight) {
		if (data[leftInd] > data[rightInd]) {
			std::swap(data[ind], data[leftInd]);
			heapify(leftInd);
		}
		else {
			std::swap(data[ind], data[rightInd]);
			heapify(rightInd);
		}
	}
	else if (shouldGoLeft) {
		std::swap(data[ind], data[leftInd]);
		heapify(leftInd);
	}
	else if (shouldGoRight) {
		std::swap(data[ind], data[rightInd]);
		heapify(rightInd);
	}
}

//анализ по памет
//сума на височините на дървото: сума от i = 1 до log(n)  i * n/2^i/2 изкраваме n пред сумата
//n* сума от i = 1 до log(n)  i/2^(i + 1)
//изкарваме 1/2 и понеже е константа можем да я премахнем
//n* сума от i = 1 до log(n)  i/2^i
//искаме да докажем че е константа за това използваме критерии на Даламбер
//lim(до безкрайност)(аn + 1)/an < 0 тогава ред е сходящ, ако е сходящ то е константа
//lim(до безкрайност)(n+1/2^n+1/n/2^n)
//lim(до безкрайност)(n+1/2^n+1) * (2^n/n)
//lim(до безкрайност) (n + 1)/2*n
//изкарваме единицата и получаваме lim(до безкрайност)n/2*n < 0 => редът е сходящ и сума от i = 1 до log(n)  i/2^i e константа
// n * константа = n => 0(n)
template<typename T>
PriorityQueue<T>::PriorityQueue(const std::vector<int>& data) : data(data)
{
	for (size_t i = data.size() / 2 - 1; i >= 0; i--)
	{
		heapify(i);
	}
}

template<typename T>
void PriorityQueue<T>::pop()
{
	if (isEmpty()) {
		throw std::exception("Empty Queue");
	}
	data[0] = data[data.size() - 1];
	data.pop_back();
	if (data.size > 1) {
		heapify(0);
	}
}

template<typename T>
void PriorityQueue<T>::insert(const T& el)
{
	data.push_back(el);
	int ind = data.size() - 1;
	int parent = getParent(ind);
	while (ind > 0 && data[ind] > data[parent]) {
		std::swap(data[ind], data[parent]);
		ind = parent;
		parent = getParent(ind);
	}
}

template<typename T>
const T& PriorityQueue<T>::peek() const
{
	if (isEmpty()) {
		throw std::exception("Empty Queue");
	}
	return data[0];
}

template<typename T>
size_t PriorityQueue<T>::size() const
{
	return data.size();
}

template<typename T>
bool PriorityQueue<T>::isEmpty() const
{
	return data.size() == 0;
}

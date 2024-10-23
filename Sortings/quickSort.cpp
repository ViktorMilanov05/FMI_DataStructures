#include <iostream>

template <class T>
int partition(T* arr, size_t len) {
	if (arr[0] > arr[len - 1])
		std::swap(arr[0], arr[len - 1]);
	T& pivot = arr[len - 1];
	int left = 0;
	int right = len - 1;
	while (true) {
		while (arr[++left] < pivot);
		while (arr[--right] > pivot) {
			if (left == right) {
				break;
			}
		}
		if (left >= right) {
			break;
		}
		std::swap(arr[left], arr[right]);
	}
	std::swap(arr[left], pivot);
	return left;
}

template <class T>
void quickSort(T* arr, size_t len) {
	if (!arr, len <= 1) {
		return;
	}
	int pivotInd = partition(arr, len);
	quickSort(arr, pivotInd);
	quickSort(arr + pivotInd + 1, len - pivotInd - 1);
}

int main()
{
	int arr[]{4,2,1,5,3};
	quickSort(arr, 5);
	for (size_t i = 0; i < 5; i++)
	{
		std::cout << arr[i] << " ";
	}
}
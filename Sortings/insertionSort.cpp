#include <iostream>

template <class T>
void insertionSort(T* arr, size_t len) {
	for (size_t i = 1; i < len; i++)
	{
		T el = arr[i];
		unsigned ind = i - 1;
		while (ind >= 0 && arr[ind] > el) {
			arr[ind + 1] = arr[ind];
			ind--;
		}
		arr[ind + 1] = el;
	}
}

int main()
{
	int arr[]{4,2,1,5,3};
	insertionSort(arr, 5);
	for (size_t i = 0; i < 5; i++)
	{
		std::cout << arr[i] << " ";
	}
}
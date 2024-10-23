#include <iostream>

template <class T>
void bubbleSort(T* arr, size_t len) {
	int end = len - 1;
	for (size_t i = 0; i < len - 1; i++)
	{
		unsigned lastSwappedInd = 0;
		for (size_t j = 0; j < end; j++)
		{
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				lastSwappedInd = j;
			}
		}
		if (lastSwappedInd == 0) {
			return;
		}
		end = lastSwappedInd;
	}
}

int main()
{
	int arr[]{4,2,1,5,3};
	bubbleSort(arr, 5);
	for (size_t i = 0; i < 5; i++)
	{
		std::cout << arr[i] << " ";
	}
}
#include <iostream>

template <class T>
void selectionSort(T* arr, size_t len) {
	for (size_t i = 0; i < len - 1; i++)
	{
		int minElInd = i;
		for (size_t j = i + 1; j < len; j++)
		{
			if (arr[j] < arr[minElInd]) {
				minElInd = j;
			}
		}
		if (minElInd != i) {
			std::swap(arr[i], arr[minElInd]);
		}
	}
}

int main()
{
	int arr[]{4,2,1,5,3};
	selectionSort(arr, 5);
	for (size_t i = 0; i < 5; i++)
	{
		std::cout << arr[i] << " ";
	}
}
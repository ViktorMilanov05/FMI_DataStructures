#include <iostream>

template <class T>
void merge(T* arr1, size_t len1, T* arr2, size_t len2, T* res) {
	unsigned firstInd = 0;
	unsigned secondInd = 0;
	unsigned resInd = 0;

	while (firstInd < len1 && secondInd < len2) {
		res[resInd++] = (arr1[firstInd] < arr2[secondInd] ? arr1[firstInd++] : arr2[secondInd++]);
	}
	while (firstInd < len1) {
		res[resInd++] = arr1[firstInd++];
	}
	while (secondInd < len2) {
		res[resInd++] = arr2[secondInd++];
	}
}

template <class T>
void mergeSortStep(T* arr, size_t len, T* buffer) {
	if (len == 1)
		return;
	unsigned mid = len / 2;
	mergeSortStep(arr, mid, buffer);
	mergeSortStep(arr + mid, len - mid, buffer);
	merge(arr, mid, arr + mid, len - mid, buffer);
	for (size_t i = 0; i < len; i++)
	{
		arr[i] = buffer[i];
	}
}

template <class T>
void mergeSort(T* arr, size_t len) {
	if (!arr || len <= 1)
		return;
	T* buffer = new T[len];
	mergeSortStep(arr, len, buffer);
	delete[] buffer;
}

int main()
{
	int arr[]{4,2,1,5,3};
	mergeSort(arr, 5);
	for (size_t i = 0; i < 5; i++)
	{
		std::cout << arr[i] << " ";
	}
}
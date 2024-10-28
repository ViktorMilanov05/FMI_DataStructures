#include <iostream>
#include <vector>

/*Даден е масив от цели числа. Да се преброят инверсиите в него.*/

int merge(int* first, int len1, int* second, int len2, int* res) {
	int firstIter = 0;
	int secondIter = 0;
	int resIter = 0;
	int inv = 0;

	while (firstIter < len1 && secondIter < len2) {
		if (first[firstIter] <= second[secondIter]) {
			res[resIter++] = first[firstIter++];
		}
		else {
			res[resIter++] = second[secondIter++];
			inv += (len1 - firstIter);
		}
	}
	while (firstIter < len1) {
		res[resIter++] = first[firstIter++];
	}
	while (secondIter < len2) {
		res[resIter++] = second[secondIter++];
	}
	return inv;
}

int mergeSort(int* nums, int* buffer, int len) {
	if (len == 1)
		return 0;
	int mid = len / 2;

	int inversion = 0;
	inversion += mergeSort(nums, buffer, mid);
	inversion += mergeSort(nums + mid, buffer, len - mid);

	inversion += merge(nums, mid, nums + mid, len - mid, buffer);
	for (size_t i = 0; i < len; i++)
	{
		nums[i] = buffer[i];
	}
	return inversion;
}

int inversionsCount(int* nums, int count) {
	if (!nums || count == 0) {
		return 0;
	}

	int* arr = new int[count];
	int inversions = mergeSort(nums, arr, count);
	delete[] arr;
	return inversions;
}

int main()
{
    int arr[] = {2, 4, 1, 3, 5};
    std::cout << inversionsCount(arr, 5);
}

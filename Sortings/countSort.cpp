#include <iostream>
#include <string>

struct Student
{
	std::string name;
	int grade;
};

void countSort(Student* arr, size_t len) {
	const size_t COUNT_OF_DOMAIN = 5;
	int* countArr = new int[COUNT_OF_DOMAIN] {0};
	for (size_t i = 0; i < len; i++)
	{
		countArr[arr[i].grade - 2]++;
	}
	for (size_t i = 1; i < COUNT_OF_DOMAIN; i++)
	{
		countArr[i] += countArr[i - 1];
	}
	Student* res = new Student[len];
	for (int i = len - 1; i >= 0; i--)
	{
		size_t ind = --countArr[arr[i].grade - 2];
		res[ind] = arr[i];
	}
	for (size_t i = 0; i < len; i++)
	{
		arr[i] = res[i];
	}
	delete[] res;
	delete[] countArr;

}

int main()
{
	Student arr[] = { { "Petur", 4 }, { "Ivan", 6 }, { "Alex", 4 }, { "Vladimir", 5 }, { "Katerina", 5 } };

	countSort(arr, sizeof(arr) / sizeof(Student));

	for (int i = 0; i < sizeof(arr) / sizeof(Student); i++)
		std::cout << "Name: " << arr[i].name << ", grade: " << arr[i].grade << std::endl;

}
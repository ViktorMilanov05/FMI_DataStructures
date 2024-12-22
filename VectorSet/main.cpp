#include <iostream>
#include "VectorSet.h"

void printVector(const VectorSet& v) {
	size_t n = v.getSize();
	for (size_t i = 0; i < n; i++)
	{
		std::cout << v[i] << ' ';
	}
	std::cout << std::endl;
}

int main()
{
	VectorSet v;
	v.push_back(1);
	
	printVector(v); // 1

	v.push_back(1);

	printVector(v); // 1 1
	
	v.push_back(0);

	printVector(v); // 1 1 0

	v.push_back(1); 
	
	printVector(v); // 1 1 0 1

	v.pop_front();

	printVector(v); // 1 0 1

	v.push_back(1);

	printVector(v); // 1 0 1 1

	v.push_back(1);

	printVector(v); // 1 0 1 1 1

	v.push_back(0);

	printVector(v); // 1 0 1 1 1 0

	v.push_back(1);

	printVector(v); // 1 0 1 1 1 0 1

	v.push_back(1);

	printVector(v); // 1 0 1 1 1 0 1 1

	v.push_back(0); 

	printVector(v); // 1 0 1 1 1 0 1 1 0

	v.pop_back();

	printVector(v); // 1 0 1 1 1 0 1 1

	const_iterator i = v.c_begin();
	i++;
	i++;

	v.insert(i, 1);

	printVector(v); // 1 0 1 1 1 1 0 1 1

	i--;

	v.remove(i);

	printVector(v);  // 1 1 1 1 1 0 1 1
}
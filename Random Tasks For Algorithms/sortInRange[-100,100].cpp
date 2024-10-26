#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*Даден е масив от цели числа в диапазона [-100, 100]. Сортирайте го с линейна сложност.*/

void countSort(std::vector<int>& arr) {
    const int DOMAIN_COUNT = 201;
    std::vector<int> countArr(DOMAIN_COUNT);
    for (size_t i = 0; i < arr.size(); i++)
    {
        countArr[arr[i] + 100]++;
    }
    for (size_t i = 1; i < DOMAIN_COUNT; i++)
    {
        countArr[i] += countArr[i - 1];
    }
    std::vector<int> res(arr.size());
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        int ind = --countArr[arr[i] + 100];
        res[ind] = arr[i];
    }
    for (size_t i = 0; i < arr.size(); i++)
    {
        arr[i] = res[i];
    }
}

int main()
{
    std::vector<int> nums = { 55, -19, 27, 0, -100, 100, -35, 11 };
    countSort(nums);

    for (const auto& num : nums) {
        std::cout << num << ' ';
    }
}
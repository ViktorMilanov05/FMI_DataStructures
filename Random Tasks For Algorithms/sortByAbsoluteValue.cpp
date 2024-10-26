#include <iostream>
#include <vector>

/*Даден е масив от цели числа в диапазона [-100, 100]. 
Пренаредете масива така, че числата с еднакви абсолютни стойности да бъдат поставени едно до друго.*/

void rearrangeArray(std::vector<int>& nums) {
    std::vector<int> result;
    std::vector<int> positive(101);
    std::vector<int> negative(101);

    for (size_t i = 0; i < nums.size(); i++)
    {
        if (nums[i] >= 0) {
            positive[nums[i]]++;
        }
        else {
            negative[-nums[i]]++;
        }
    }

    for (int i = 0; i <= 100; ++i) {
        for (int j = 0; j < positive[i]; ++j) {
            result.push_back(i);
        }
        for (int j = 0; j < negative[i]; ++j) {
            result.push_back(-i);
        }
    }

    for (size_t i = 0; i < nums.size(); i++)
    {
        nums[i] = result[i];
    }
}


int main()
{
    std::vector<int> nums = { -1, 5, 3, 4, 1, -3, -4, -5, 1 };
    std::vector<int> result;

    rearrangeArray(nums);

    for (size_t i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << ' ';
    }

}

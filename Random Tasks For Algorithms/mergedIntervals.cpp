#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*Даден е масив от интервали. Обединете всички интервали, които се припокриват (т.е. интервали, които имат общи стойности или се застъпват).

Вход:

[[1,3], [2,4], [5,7], [6,8]]
Изход:

[[1,4], [5,8]]*/


std::vector<std::vector<int>> mergeIntervals(std::vector<std::vector<int>>& intervals) {
    std::sort(intervals.begin(), intervals.end());

    std::vector<std::vector<int>> merged;
    merged.push_back(intervals[0]);

    for (const auto& interval : intervals) {
        auto& last = merged.back();
        if (last[1] >= interval[0]) {
            last[1] = interval[1];
        }
        else {
            merged.push_back(interval);
        }
    }
    return merged;
}

int main()
{
    std::vector<std::vector<int>> intervals = { {1,3}, {2,4}, {5,7}, {6,8} };
    auto result = mergeIntervals(intervals);

    for (const auto& interval : result) {
        std::cout << "[" << interval[0] << "," << interval[1] << "] ";
    }

}
#include <iostream>
#include <vector>

/*Принтирайте всички булеви вектори до n*/

void print(const std::vector<bool>& vector) {
    for (auto i = vector.begin(); i < vector.end(); i++)
    {
        std::cout << (*i) << ' ';
    }
    std::cout << std::endl;
}

void next(std::vector<bool>& vector) {
    int ind = vector.size() - 1;
    while (ind >= 0 && vector[ind] == 1) {
        vector[ind--] = 0;
    }
    if (ind >= 0) {
        vector[ind] = 1;
    }
}

void nextWithIterators(std::vector<bool>& vector) {
    auto cur = vector.rbegin();
    while (cur != vector.rend() && (*cur) == 1) {
        *cur++ = 0;
    }
    if (cur != vector.rend()) {
        *cur = 1;
    }
}

void generateBoolVectors(int n) {
    std::vector<bool> boolVector(n, 0);
    int count = 1 << n;
    for (size_t i = 0; i < count; i++)
    {
        print(boolVector);
        nextWithIterators(boolVector);
    }
}


int main()
{
    generateBoolVectors(3);
}


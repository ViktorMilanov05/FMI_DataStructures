#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*Пренаредете масив от цели числа така, че всички прости числа да бъдат преди съставните числа.*/

std::vector<bool> generatePrimeSieve(int maxElement) {
    std::vector<bool> isPrime(maxElement + 1, true);
    isPrime[0] = isPrime[1] = false;
    int maxPossible = sqrt(maxElement);
    for (int i = 2; i <= maxPossible; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= maxElement; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}

void rearrangePrimesFirst(std::vector<int>& arr) {
    int maxElement = *max_element(arr.begin(), arr.end());
    std::vector<bool> isPrime = generatePrimeSieve(maxElement);

    std::vector<int> primes;
    std::vector<int> composites;

    for (int num : arr) {
        if (isPrime[num]) {
            primes.push_back(num);
        }
        else {
            composites.push_back(num);
        }
    }
    sort(primes.begin(), primes.end());
    sort(composites.begin(), composites.end());
    arr.clear();
    arr.insert(arr.end(), primes.begin(), primes.end());
    arr.insert(arr.end(), composites.begin(), composites.end());
}

int main()
{
    std::vector<int> arr = { 10, 3, 5, 9, 2, 8 };
    rearrangePrimesFirst(arr);

    for (int num : arr) {
        std::cout << num << " ";
    }
}


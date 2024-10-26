#include <iostream>
#include <string>
#include <vector>

/*You are given a vector of words, where each word consists entirely of lowercase Latin letters. 
Write a program that rearranges the vector such that all words starting with the letter 'a' 
appear first, followed by words starting with the letter 'b', and so on, in alphabetical order. */

void sortWords(std::vector<std::string>& words) {
	const size_t COUNT_OF_DOMAIN = 26;
	std::vector<int> countArr(COUNT_OF_DOMAIN);
	for (size_t i = 0; i < words.size(); i++)
	{
		countArr[words[i][0] - 'a']++;
	}
	for (size_t i = 1; i < COUNT_OF_DOMAIN; i++)
	{
		countArr[i] += countArr[i - 1];
	}
	int index = 0;
    	while(index < words.size()){
        	int correctIndex = count[words[index][0] - 'a'] - 1;

       	 	if (index == correctIndex || count[words[index][0] - 'a'] <= index)
                	index++;
        	else {
            		std::swap(words[index], words[correctIndex]);
            		count[words[correctIndex][0] - 'a']--;
        	}
    	}
}

int main()
{
	std::vector<std::string> words = { "banana", "apple", "alpaca", "cat", "biscuit", "elephant", "string", "house", "progress", "trousers", "mouse" };
	sortWords(words);
	for (size_t i = 0; i < words.size(); i++)
	{
		std::cout << words[i] << " ";
	}
}

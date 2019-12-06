#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

bool isValid(long input)
{
    bool isDuplicateFound = false;
    int dupCount = 0;
    vector<int> digits;
    while (input > 0)
    {
        int newInput = input/10;
        int remainder = input - newInput*10;
        digits.push_back(remainder);
        input = newInput;
    }

    // reverse order
    int prevDigit = digits[digits.size() - 1];
    for (int i = digits.size() - 2; i>= 0; i--)
    {
        int currentDigit = digits[i];

        if (currentDigit != prevDigit && dupCount != 0)
        {
            if (dupCount == 1)
                isDuplicateFound = true;
            dupCount = 0;
        }

        if (currentDigit < prevDigit)
            return false;

        if (currentDigit == prevDigit && !isDuplicateFound)
        {
            dupCount++;
        }

        prevDigit = currentDigit;
    }

    if (dupCount > 1)
    {
        isDuplicateFound = false;
    }
    else if (dupCount == 1)
    {
        isDuplicateFound = true;
    }
    
    return isDuplicateFound;
}

int main()
{
    long start = 284639;
    long end = 748759;

    long res = 0;
    for (long i = start; i <= end; i++)
    {
        if (isValid(i))
            res++;
    }

    cout<<"answer is "<<res<<endl;

	return 0;
}
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

bool isValid(long input)
{
    bool isDuplicate = false;
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
        if (currentDigit < prevDigit)
            return false;

        if (currentDigit == prevDigit)
            isDuplicate = true;

        prevDigit = currentDigit;
    }

    return isDuplicate;
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
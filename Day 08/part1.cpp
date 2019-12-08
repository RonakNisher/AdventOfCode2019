#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	string line;
	ifstream myfile ("Day 08/input.txt");
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
			// No-op
		}
		myfile.close();
	}

	const int width = 25;
	const int height = 6;

	const int noOfPixelsInLayer = width * height;

	int lowest0Pixels = INT_MAX;
	int result = 0;

	int noOf0Pixels = 0;
	int noOf1Pixels = 0;
	int noOf2Pixels = 0;


	for (int layer = 0; layer < line.size(); layer+=noOfPixelsInLayer)
	{
		for (int pixel = 0; pixel < noOfPixelsInLayer; pixel++)
		{
			switch (line[pixel + layer])
			{
				case '0':
					{
						noOf0Pixels++;
						break;
					}

				case '1':
					{
						noOf1Pixels++;
						break;
					}

				case '2':
					{
						noOf2Pixels++;
						break;
					}
			}
		}


		if (noOf0Pixels < lowest0Pixels)
		{
			lowest0Pixels = noOf0Pixels;
			result = noOf1Pixels * noOf2Pixels;
		}

		noOf0Pixels = 0;
		noOf1Pixels = 0;
		noOf2Pixels = 0;
	}

	cout<<"result is "<<result<<endl;

	return 0;
}
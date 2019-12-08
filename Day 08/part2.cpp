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
			//No-op
		}
		myfile.close();
	}

	const int width = 25;
	const int height = 6;

	const int noOfPixelsInLayer = width * height;

    vector<int> image(noOfPixelsInLayer, 2);

	for (int layer = 0; layer < line.size(); layer+=noOfPixelsInLayer)
	{
		for (int pixel = 0; pixel < noOfPixelsInLayer; pixel++)
		{
            // skip processing as there is a non transparent pixel at the position
            if (image[pixel] != 2)
                continue;

			switch (line[pixel + layer])
			{
				case '0':
					{
						image[pixel] = 0;
						break;
					}

				case '1':
					{
						image[pixel] = 1;
						break;
					}

				case '2':
					{
						break;
					}
			}
		}
	}

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int val = image[row * width + col];
            if (val == 1)
                cout<<val<<" ";
            else
                cout<<"  ";
        }
        cout<<endl;
    }

	return 0;
}
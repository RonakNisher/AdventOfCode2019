#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int sizeOfGrid = 20000;
int currentMinDist = INT_MAX;
vector<string> split(string input, const string& delimiters)
{
	vector<string> res;
	
	string val = "";
	for (auto i : input) {
		if(!isspace(i) && delimiters.find(i) == -1)
		{
			val.push_back(i);
		}
		else
		{
			if (val != "")
			{
				res.push_back(val);
				val = "";
			}
		}
	}
	
	if(val != "")
		res.push_back(val);
	return res;
}

void printMap(vector<vector<int>>& map)
{
    for (int y = 0; y < 5000; y++)
    {
        for (int x = 0; x < 5000; x++)
        {
            cout<<map[y][x];
        }
        cout<<endl;
    }
}

void fillMap(vector<vector<int>>& map, int posX, int posY, int wireNumber, int noOfSteps)
{
    int currentVal = map[posY][posX];

    if (wireNumber == 1)
    {
        if (currentVal == 0)
            currentVal = noOfSteps;
        map[posY][posX] = currentVal;
    }
    else
    {
        if (currentVal != 0)
        {
            int distInSteps = currentVal + noOfSteps;
            if (distInSteps < currentMinDist)
                currentMinDist = distInSteps;
        }
    }
}

pair<int, int> getLocation(const string& code, vector<vector<int>>& map, int currentX, int currentY, int wireNumber, int& noOfSteps)
{
    char opCode = code[0];
    int steps = stoi(code.substr(1));

    int newX = currentX;
    int newY = currentY;

    switch (opCode)
    {
        case 'U':
            for (int i = 1; i <= steps; i++)
            {
                fillMap(map, newX, newY - i, wireNumber, noOfSteps++);
            }
            newY -= steps;
            break;

        case 'D':
            for (int i = 1; i <= steps; i++)
            {
                fillMap(map, newX, newY + i, wireNumber, noOfSteps++);
            }
            newY += steps;
            break;

        case 'L':
            for (int i = 1; i <= steps; i++)
            {
                fillMap(map, newX - i, newY, wireNumber, noOfSteps++);
            }
            newX -= steps;
            break;

        case 'R':
            for (int i = 1; i <= steps; i++)
            {
                fillMap(map, newX + i, newY, wireNumber, noOfSteps++);
            }
            newX += steps;
            break;
    
    default:
        break;
    }
    return make_pair(newX, newY);
}

void drawWires(vector<string>& wire, vector<vector<int>>& map, int wireNumber)
{
    int currentX = sizeOfGrid/2;
    int currentY = sizeOfGrid/2;
    int noOfSteps = 1;
    for (const string& code : wire)
    {
        pair<int, int> location = getLocation(code, map, currentX, currentY, wireNumber, noOfSteps);

        currentX = location.first;
        currentY = location.second;
    }
}

int main()
{
	string line;
    vector<vector<string>> wires = {{}, {}};
	ifstream myfile ("Day 03/input.txt");
	if (myfile.is_open())
	{
        int i = 0;
		while ( getline(myfile,line) )
		{
			std::vector<string> words = split(line, ",");
            for(auto word:words)
            {
                wires[i].push_back(word);
            }
            i++;
		}
		myfile.close();
	}

    vector<vector<int>> map;
    map.reserve(sizeOfGrid);

    for(int i = 0; i<sizeOfGrid; i++)
    {
        map[i].reserve(sizeOfGrid);
        for (int j = 0; j < sizeOfGrid; j++)
            map[i].push_back(0);
    }

    // draw wires
    int i = 1;
    for (auto wire : wires)
    {
        drawWires(wire, map, i);
        i++;
    }

    cout<<"Min Dist is "<<currentMinDist<<endl;

	return 0;
}
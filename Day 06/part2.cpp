#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

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

struct Node
{
    string name;
    string prev = "#";
    vector<string> next;
};

int main()
{
	string line;
	string orbitYou;
	string orbitSan;
    map<string, Node> objects;
	ifstream myfile ("Day 06/input.txt");
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
			std::vector<string> words = split(line, ")");
            Node& posCurrent = objects[words[0]];
            Node& posNext = objects[words[1]];

            if (posCurrent.name.empty())
            {
                posCurrent.name = words[0];
            }

            if (posNext.name.empty())
            {
                posNext.name = words[1];
            }

            // forward fill
            posCurrent.next.push_back(words[1]);

            // back fill
            posNext.prev = words[0];

            if (posNext.name == "YOU")
                orbitYou = words[0];

            if (posNext.name == "SAN")
                orbitSan = words[0];
		}

		myfile.close();
	}

    int result = 0;

    // find the full orbit path for orbit YOU
    vector<string> orbitPathsYou = {orbitYou};
    string prev = objects[orbitYou].prev;
    while (prev != "#")
    {
        orbitPathsYou.push_back(prev);
        prev = objects[prev].prev;
    }

    // find the common path
    prev = objects[orbitSan].prev;
    while (prev != "#")
    {
        result++;

        auto it = std::find(orbitPathsYou.begin(), orbitPathsYou.end(), prev);
        if (it != orbitPathsYou.end())
        {   
            int dist = distance(orbitPathsYou.begin(), it);
            result += dist;
            break;
        }

        prev = objects[prev].prev;
    }

	cout<<"result is "<<result<<endl;

	return 0;
}
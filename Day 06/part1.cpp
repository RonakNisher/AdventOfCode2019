#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

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
		}

		myfile.close();
	}

    int result = 0;

    for (auto object : objects)
    {
        string prev = object.second.prev;

        while (prev != "#")
        {
            result++;
            prev = objects[prev].prev;
        }
    }

	cout<<"result is "<<result<<endl;

	return 0;
}
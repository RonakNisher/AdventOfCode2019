#include <string>
#include <iostream>
#include <fstream>
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

int main()
{
	string line;
    vector<int> input;
	int result = 0;
	ifstream myfile ("Day 02/input.txt");
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
			std::vector<string> words = split(line, ",");
			for (auto word : words) 
			{
                input.emplace_back(stoi(word));
			}
		}
		myfile.close();
	}

    // break the prog
    input[1] = 12;
    input[2] = 2;

    for (int i = 0; i<input.size(); i+=4)
    {
        int opcode = input[i+0];

        if (opcode == 99)
            break;

        switch (opcode)
        {
            case 1:
                input[input[i + 3]] = input[input[i + 1]] + input[input[i + 2]];
                break;

            case 2:
                input[input[i + 3]] = input[input[i + 1]] * input[input[i + 2]];
                break;

            default:
                break;
        }
    }

	cout<<"result is "<<input[0]<<endl;

	return 0;
}
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

int getOpcode(string ins)
{
    int size = ins.size();
    if (size == 1 || size == 2)
        return stoi(ins);

    return stoi(ins.substr(size - 2));
}

int getParam(string ins, vector<int>& inp, int pos, int value)
{
    int size = ins.size();
    if (size < 2 + pos)
    {
        // mode 0
        return inp[value];
    }
    else
    {
        // find mode
        char mode = ins[size - 2 - pos];

        if (mode == '1')
            return value;
        else
            return inp[value];
    }
    
}

int main()
{
	string line;
    vector<int> input;
	int result = 0;
	ifstream myfile ("Day 05/input.txt");
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

    for (int i = 0; i<input.size();)
    {
        string command = to_string(input[i]);

        int opcode = getOpcode(command);

        if (opcode == 99)
            break;

        switch (opcode)
        {
            case 1:
                input[input[i + 3]] = getParam(command, input, 1, input[i + 1]) + getParam(command, input, 2, input[i + 2]);
                i+=4;
                break;

            case 2:
                input[input[i + 3]] = getParam(command, input, 1, input[i + 1]) * getParam(command, input, 2, input[i + 2]);
                i+=4;
                break;

            case 3:
                input[input[i + 1]] = 1; //only input
                i+=2;
                break;

            case 4:
                cout<<getParam(command, input, 1, input[i + 1])<<endl;
                i+=2;
                break;

            default:
                break;
        }
    }

	return 0;
}
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

void resetInput(vector<int>& newInput, vector<int>& original)
{
	newInput = original;
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

int getThrusterOutput(vector<int>& input, int phaseSetting, int programInput)
{
	int output;
	int nextInput = phaseSetting; // first input is phase setting

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
                input[input[i + 1]] = nextInput;
				nextInput = programInput; // set the next input to programInput
                i+=2;
                break;

            case 4:
				output = getParam(command, input, 1, input[i + 1]);
                i+=2;
                break;

            case 5:
                if (getParam(command, input, 1, input[i + 1]) != 0)
                    i = getParam(command, input, 2, input[i + 2]);
                else
                {
                    i+=3;
                }
                break;

            case 6:
                if (getParam(command, input, 1, input[i + 1]) == 0)
                    i = getParam(command, input, 2, input[i + 2]);
                else
                {
                    i+=3;
                }
                break;

            case 7:
                input[input[i + 3]] = getParam(command, input, 1, input[i + 1]) < getParam(command, input, 2, input[i + 2]) ? 1 : 0;
                i+=4;
                break;

            case 8:
                input[input[i + 3]] = getParam(command, input, 1, input[i + 1]) == getParam(command, input, 2, input[i + 2]) ? 1 : 0;
                i+=4;
                break;

            default:
                break;
        }
    }

	return output;
}

bool isValid(int a, int b, int c, int d, int e)
{
	if (a == b || a == c || a == d || a == e
	|| b == c || b == d || b == e
	|| c == d || c == e
	|| d == e)
		return false;
	
	return true;
}

int main()
{
	string line;
    vector<int> input;
	int result = 0;
	ifstream myfile ("Day 07/input.txt");
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

	vector<int> original = input;
	long maxOutput = INT_MIN;
	vector<int> maxSequence;

	for (int a = 0; a < 5; a++)
	{
		for (int b = 0; b < 5; b++)
		{
			for (int c = 0; c < 5; c++)
			{
				for (int d = 0; d < 5; d++)
				{
					for (int e = 0; e < 5; e++)
					{

						if (!isValid(a, b, c , d, e))
							continue;

						int output = getThrusterOutput(input, a, 0);
						resetInput(input, original);

						output = getThrusterOutput(input, b, output);
						resetInput(input, original);

						output = getThrusterOutput(input, c, output);
						resetInput(input, original);

						output = getThrusterOutput(input, d, output);
						resetInput(input, original);

						output = getThrusterOutput(input, e, output);
						resetInput(input, original);

						if (output > maxOutput)
						{
							maxOutput = output;
							maxSequence = {a, b, c, d, e};
						}
					}
				}
			}
		}
	}

	cout<<"Max output is "<<maxOutput<<endl;

	return 0;
}
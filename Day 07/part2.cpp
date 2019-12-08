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

void resetInput(vector<long>& newInput, vector<long>& original)
{
	newInput = original;
}

int getParam(string ins, vector<long>& inp, int pos, long value)
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

pair<long, bool> getThrusterOutput(vector<long>& input, int phaseSetting, long programInput, int& ipCounter)
{
	long output = 0;
	// first input to program is phase setting, every other time it's programInput
    long nextInput = ipCounter == 0 ? phaseSetting : programInput; 

    int count = 0;
	for (int i = ipCounter; i<input.size();)
    {
        string command = to_string(input[i]);

        int opcode = getOpcode(command);
        if (opcode == 99)
        {
            break;

        }

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

                ipCounter = i; // save off the ip counter
                return make_pair(output, false);
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

	return make_pair(output, true);
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
    vector<long> input;
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

	vector<long> original = input;
	vector<long> stateA;
	vector<long> stateB;
	vector<long> stateC;
	vector<long> stateD;
	vector<long> stateE;

    int ipCounterA = 0;
    int ipCounterB = 0;
    int ipCounterC = 0;
    int ipCounterD = 0;
    int ipCounterE = 0;

	long maxOutput = INT_MIN;
    long inp = 0;
	vector<int> maxSequence;

	for (int a = 5; a < 10; a++)
	{
		for (int b = 5; b < 10; b++)
		{
			for (int c = 5; c < 10; c++)
			{
				for (int d = 5; d < 10; d++)
				{
					for (int e = 5; e < 10; e++)
					{
						if (!isValid(a, b, c , d, e))
							continue;

                        resetInput(stateA, original);
                        resetInput(stateB, original);
                        resetInput(stateC, original);
                        resetInput(stateD, original);
                        resetInput(stateE, original);

                        ipCounterA = 0;
                        ipCounterB = 0;
                        ipCounterC = 0;
                        ipCounterD = 0;
                        ipCounterE = 0;

                        bool isHalt = false;
                        long output = 0;
                        inp = 0;

                        while (!isHalt)
                        {
                            inp = output;
                            std::tie(output, isHalt) = getThrusterOutput(stateA, a, inp, ipCounterA);
                            std::tie(output, isHalt) = getThrusterOutput(stateB, b, output, ipCounterB);


                            std::tie(output, isHalt) = getThrusterOutput(stateC, c, output, ipCounterC);

                            std::tie(output, isHalt) = getThrusterOutput(stateD, d, output, ipCounterD);


                            std::tie(output, isHalt) = getThrusterOutput(stateE, e, output, ipCounterE);
                        }


						if (inp > maxOutput)
						{
							maxOutput = inp;
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
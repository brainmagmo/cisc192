#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

int getIntegerWithPrompt(string prompt);
bool isIntegerInput(string s);
bool getyesno();

int main()
{
	vector<int> theList;
	int min = 0, max = 0;
	long int sum = 0;
	int iInputs = 0;
	while (iInputs <= 0)
	{
		iInputs = getIntegerWithPrompt("Please enter the number of random numbers to be generated: ");
		if (iInputs <= 0)
			cout << "\nPlease enter a positive number!\n";
	}
	cout << "What is the range?" << endl;
	while (min >= max)
	{
		min = getIntegerWithPrompt("Minimum ");
		max = getIntegerWithPrompt("Maximum ");
		if (min > max)
			cout << "Not a valid range." << endl;
	}
	int range = max - min;
	int blocks = range / RAND_MAX;
	srand(time(0));
	for (int i = 0; i < iInputs; i++)
	{
		int r = 0;
		if (blocks)
		{
			r += (rand() % blocks) * RAND_MAX;
			r += rand() % (range % RAND_MAX);
		}
		else
			r += (rand() % range);
		r += min;
		theList.push_back(r);
		sum += r;
	}
	cout << "\nThe total of " << iInputs << " real random numbers is : " << sum;
	cout << "\nThe average of " << iInputs << " real random numbers is : " << (sum / static_cast<float>(iInputs));
	cout << "The list of real random numbers is: ";
	int width = 0;
	int dying = iInputs;
	while (dying > 1)
	{
		++width;
		dying = dying / 10;
	}
	for (unsigned int i = 0; i < theList.size(); i++)
	{
		if (i % 5 == 0)
		{
			cout << endl;
		}
		cout << setw(width + 3) << theList[i] << ' ';
	}
	sort(theList.begin(), theList.end());
	cout << endl << endl << "The list of after sorting is: ";
	for (unsigned int i = 0; i < theList.size(); i++)
	{
		if (i % 5 == 0)
		{
			cout << endl;
		}
		cout << setw(5) << theList[i] << ' ';
	}
	bool repeat = false;
	bool flag = false;
	do
	{
		//cout << endl << "Please enter a number to be searched: ";
		int userinput;
		cout << endl << endl;
		userinput = getIntegerWithPrompt("Please enter a number to be searched: ");
		flag = binary_search(theList.begin(), theList.end(), userinput);
		cout << "The number \'" << userinput << "\' was" << (flag ? " " : " not ") << "found." << endl;
		cout << "Would you like to search again? ";
		repeat = getyesno();
	} while (repeat);
	cout << "\nThank you. See you again!";
	return 0;
}

bool getyesno()
{
	string input;
	bool retry = false;
	do
	{
		getline(cin, input);
		if (input[0] == 'y' || input[0] == 'Y')
			return true;
		else if (input[0] == 'n' || input[0] == 'N')
			return false;
		else
		{
			cout << "\nInvalid Input!\nPlease enter y/n: ";
			retry = true;
		}
	} while (retry);
	return false;
}

int getIntegerWithPrompt(string prompt)
{
	bool test = false;
	int n = -1;
	string sinput;
	do {
		cout << prompt;
		//How many Students would you like to add: 2 \n\n

		getline(cin, sinput);
		if (sinput.length() > 7)
		{
			cout << "Number is too large" << endl;
			continue;
		}
		if (!isIntegerInput(sinput))
		{
			cout << "Not a valid input! Please enter a number." << endl;
			continue;
		}
		else {
			n = stoi(sinput);
			test = true;
			//if (n < 0)
			//{
			//	cout << "Please enter a non-negative number." << endl;
			//	continue;
			//}
		}

	} while (!test);
	return n;
}

bool isIntegerInput(string s)
{
	bool ret = true;
	//s = s.substr(s.find_first_not_of(' '), s.find_last_not_of(' ') + 1);
	for (unsigned int i = 0; i < s.length(); i++)
	{
		ret = ret && ((s[i] <= '9') && ('0' <= s[i]));
		if (i == 0)
		{
			ret = ret || (s[i] == '-');
		}
	}
	return ret;
}

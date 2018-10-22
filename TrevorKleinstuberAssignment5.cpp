/*Trevor Kleinstuber
Prof Tran
Assignment 5
Purpose:write a primality test.
2018 Oct 22
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <math.h>

using namespace std;
bool getyes();
bool isPrime(int);
int validInt(int);

int main() {
	int iTry;
	vector<int> vPrimes;
	string fName;
	do {
		cout << "\nEnter an integer: ";
		ENTER:
		cin >> iTry;
		iTry = validInt(iTry);
		if (isPrime(iTry))
			cout << endl << iTry << " is a prime number!";
		else {
			if (iTry < 2) {
				cout << "Please enter an integer greater than one: ";
				goto ENTER;
			}
			else {
				cout << endl << iTry << " is not a prime number.";
			}
		}
		cout << "\nWould you like to enter another number? ";
	} while (getyes());
	cout << "\nApplication is terminating...";
	cout << "\nEnter a file name for writing prime numbers: ";
	getline(cin, fName);
	ofstream ofs;
	ofs.open(fName.c_str());
	cout << "\nWhat is the limit value you want to generate prime numbers ? ";
	cin >> iTry;
	iTry = validInt(iTry);
	cout << "\nThe list of prime numbers up to the value " << iTry << " is:";
	int line = 0;
	for (int i = 0; i <= iTry; i++)
	{
		if (isPrime(i))
		{
			cout << ((line % 10 == 0) ? "\n" : "\t");
			line++;
			cout << i;
			vPrimes.push_back(i);
		}
	}
	for (int x : vPrimes)
		ofs << x << "\t";
	return 0;
}

bool getyes()
{
	string inS = "N";
	do {
		if (!(inS == "Y" || inS == "N" || inS == "YES" || inS == "NO"))
			cout << "\nPlease enter yes/no:";
		getline(cin, inS);
		for (int i = 0; i < inS.size(); i++) {
			*(inS + i) = toupper(inS[i]);
		}
	} while (!(inS == "Y" || inS == "N" || inS == "YES" || inS == "NO"));
	return (inS == "Y" || inS == "YES");
}

bool isPrime(int iTest)
{
	if (iTest < 2)
		return false;
	for (int i = 2; i <= sqrt(iTest) + 1; i++)
		if (!(iTest % i))
			return false;
	return true;
}

int validInt(int i)
{
	while (cin.fail())
	{
		cout << "\nInvalid Input! Please re - enter:";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> i;
	}
	cin.ignore(INT_MAX, '\n');
	return i;
}
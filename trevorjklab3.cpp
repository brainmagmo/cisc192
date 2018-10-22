/*
TREVOR J KLEINSTUBER
2018 SEPTEMBER 9
CISC 196
PROF TRAN*/
/*Lab 3:
Using vector (STL: Standard Template Library) to create a Student List that contains Student’s
Full Name (First Name, and/or Middle Name, and Last Name), Student’s ID, and Student’s
Enrolled Classes. A user should be able to perform the following tasks in any order as follows:
1. Reading the Student List from an external text file. :)
2. Adding Student(s) into the Student List. The Student’s info should include Student’s Full
Names (First Name, and/or Middle Name, and Last Name), Student’s IDs, and Student’s
Enrolled Classes. :)
3. Displaying the content of the Student List. :)
4. Sorting the Student List. :)
5. Writing/saving the Student List to an external text file. :)
6. Searching for a Student’s Info (Full Name, IDs, etc.) from the Student List. :)
7. Ending the program. :)
Furthermore, your program should:
• Validate all users’ inputs that include integer and/or character. :)
• Include at least three functions declarations/prototypes and three functions
\definitions. :)
Things you should do:
1. Check for empty \list with options Displaying, Sorting, Writing, and Searching. :)
Extra Credits:
1. Same file could not open and read again:		 :)
2. Searching for duplicate ID when adding ID:		 :)
5. If the length of a name is greater than 25
characters, adjust the name so that it stills align
with the rest of the info appropriately:	:)
7. Sorting by ID beside name:
matching substrings :)
8. Searching by ID beside name:	  			:)
Add sentinel for changes :)
Avoid adding same student twice whether adding manually or auto //$
Dont redisplay menu on bad choice?  :)
Make yes/no function. //$
*/
#include <iostream>  //cin, cout
#include <fstream> 
#include <iomanip>   //setw
#include <vector>
#include <string>    //getline
#include <algorithm> //search, sort
#include <cstdlib>   //time
using namespace std;
/**simple counter of occurences of c in s*/
int ccount(string s, char c);
/**verifies an input string is an storable as an integer
replaced by validateInteger
bool isIntegerInput(string & s);
verifies an cin >> int operration and prompts user until cin is good*/
int validateInteger(int maybe);
/**take a string value
 and return an all caps version*/
string toUpperS(string s);
/**take a char value
 and return an all caps version*/
char toUpperC(char c);
/**prompts user to input an integer n such that n >= 0 (and n < = 99999)
@param s is a prompt which is displayed and does not affect output
s should clearly indicate a number is being asked for*/
int getNNIntegerWithPrompt(const string prompt);
/**takes a string and capitalizes alphabetic chars which follow
whitespace ('\t', '\n', ' '), and sends other alphabetic chars
to lowercase.
e.g. "tRan johN" -> "Tran John"*/
string to_Pretty_Print(string name);
char toLowerC(char);
/**generates a random student ID (7 digits)
use srand() before calling*/
string randID();
/**splits a string s into a vector of strings using
delim to separate values
used for importing*/
vector<string> splitStingBy(string s, char delim);
/**unusued function for extra credit
replaced by improving searchByValue
vector<Student> findBySubstring(vector<Student>& roster, string substr);
replaces underscores with spaces*/
string txtToName(string);
/**replaces spaces with underscores*/
string nameToTxt(string name);
/**replaces spaces with underscores
and squishes to a single string with an underscore between names*/
string nameToTxt(vector<string> vs);
/**bread and butter of the program:
a Student class which holds a name, id, and class list
The student class stores a student's name, id, and classes.
It contains operator overloads on the comparison
operators < <= > >= ==, which compare by name & id
Students name and classes are stored as vectors of strings*/
class Student {
public:
	vector<string> name;
	string studentID;
	vector<string> clase;
	Student() {
		name = {};
		studentID = "";
		clase = {};
	}
	Student(vector<string> vs) {
		name = vs;
		studentID = "";
		clase = {};
	}
	Student(string id) {
		name = {};
		studentID = id;
		clase = {};
	}
	void addName(string aname) {
		name.push_back(aname);
	}
	void addNames(vector<string> vname) {
		for (unsigned int i = 0u; i < vname.size(); i++) {
			name.push_back(vname[i]);
		}
	}
	void addID(string id) {
		studentID = id;
	}
	void addClass(string clas) {
		clase.push_back(clas);
	}
	void addClasses(vector<string> vclas) {
		for (unsigned int i = 0u; i < vclas.size(); i++) {
			clase.push_back(vclas[i]);
		}
	}
	/*returns a string containing spaces and possible newline characters*/
	string fullName() {
		string s = "";
		for (unsigned int i = 0u; i < name.size(); i++) {
			if (name[i] != "|") {
				//Char Max means {"St George", "David", "Paul-Ryan"} comes after {"St George-David", "Paul", "Ryan"}
				s += name[i] + (char)CHAR_MAX;
			}
		}
		return s;
	}
	/*returns a comma-separated string of classes*/
	string classlist() {
		string s = "";
		for (unsigned int i = 0u; i < clase.size() - 1; i++) {
			s += toUpperS(clase[i]);
			s += ",";
		}
		if (clase.size() > 0)
			s += clase.back();
		return s;
	}
	bool operator < (Student &t) {
		bool ret;
		ret = (this->fullName() < t.fullName());
		if (!ret && this->fullName() == t.fullName())
			ret = (this->studentID < t.studentID);
		return ret;
	}
	bool operator == (Student &t) {
		return !(t < *this)
			&& !(*this < t);
	}
	bool operator > (Student &t) {
		return (t < *this);
	}
	bool operator <= (Student &t) {
		return !(t < *this);
	}
	bool operator >= (Student &t) {
		return !(*this < t);
	}
};
//-----------------------------------------------------------------------------------------
/**prompts user to look for a name on the roster,
assumes the roster is sorted.**/
void searchByValue(vector<Student> &roster);
//abstraction of < overload from Student
//s < t if names are same but ids are different
bool beforeAlphabetically(Student & s, Student & t) {
	return (s < t);
};
/**checks only last names.*/
bool beforeByLastName(Student & s, Student & t) {
	bool ret;
	ret = (s.name[s.name.size() - 1] < t.name[t.name.size() - 1]);
	return ret;
}
/**for sorting by id*/
bool beforeByID(Student & s, Student & t) {
	return (s.studentID < t.studentID);
};
/**used by displayRoster and searchByValue*/
void displayStudent(Student & s);
/**displays the roster as a table*/
void displayRoster(vector<Student> & vs);
/**prompts user to fill out roster.
can enter any number of students*/
bool addStudents(vector<Student> & vs);
/**prompts user to enter a character between a and g*/
char getMenuChoice();
/**prompts user to select a sorting method then executes with sort()*/
bool executeSort(vector<Student> & vs);
/**clean cout call with menu text with options A to G*/
void displayMenu();
/**
@param vs is a roster which a file is copied to
user is prompted to enter name of file to be extracted
:)implemented : files already opened tracker
file should be a whitespace-delimited list of students
each student should be 5 white-space free strings:
3 names, an id, then a classlist
names should have underscores instead of spaces,
(except after first name and before last name)
eg: st_john paul germain_jr 100000 engl_101
Names with fewer than three parts should use | in place of missing names:
e.g.
Cher | | 999999999 music_619
Paul | Blart 505050505 crim_just_2
id can be alphanumeric
eg: abc123
classlist should be a comma-delimited string
eg cisc_192,cisc_193,engl_101
recommended: newline after each student. Not enforced.
*/
bool importFromFile(vector<Student> & vs);
/**prompts user for a filename, then saves roster vs
to file, in the form that can be read by importFromFile
recommended: filename should be a .txt
*/
bool exportRoster(vector<Student> & vs);
/**global variables to determine field widths in display functions
if 25 is changed, match change in Student.fullName*/
const unsigned int fieldLengths[3] = { 25, 15, 15 };
//-----------------------------------------------------------------------------------------
//** ********* M A I N **************//
//-----------------------------------------------------------------------------------------
int main() {
	bool unsavedChangedExist = false;
	srand((unsigned)time(0));
	const char IMPORT = 'A',
		ADDING = 'B',
		DISPLAY = 'C',
		SORT = 'D',
		EXPORT = 'E',
		SEARCH = 'F',
		ENDING = 'G';
	char choice;
	vector<Student> mainRoster;
	bool exit_ = false;
	do {
		displayMenu();
		Getting:
		choice = getMenuChoice(); //
		/*prevent unexpected operations on an empty roster*/
		if (mainRoster.size() == 0 && choice >= 'C' && choice <= 'F') {
			cout << endl << "The list is empty. Please load information into the list." << endl;
			continue;
		}
		switch (choice) {
		case (IMPORT):
			unsavedChangedExist = importFromFile(mainRoster);
			break;
		case (ADDING):
			unsavedChangedExist = addStudents(mainRoster);
			break;
		case (DISPLAY):
			displayRoster(mainRoster);
			break;
		case (SORT):
			unsavedChangedExist = executeSort(mainRoster);
			break;
		case (EXPORT):
			unsavedChangedExist = exportRoster(mainRoster);
			break;
		case (SEARCH):
			searchByValue(mainRoster);
			break;
		case (ENDING):
			exit_ = true;
			break;
		default:
			cout << endl << "Please select a valid choice.";
			goto Getting;
		}
	} while (!exit_);
	cout << endl << "The program is closing.";
	if (unsavedChangedExist) {
		cout << endl << "You have unsaved changes";
		cout << endl << "Would you like to save changes? ";
		choice = toUpperC(cin.get());
		cin.ignore(INT_MAX, '\n');
		if (choice == 'Y') {
			unsavedChangedExist = exportRoster(mainRoster);
			if (!unsavedChangedExist)
				cout << endl << "Changes saved.";
		}
		else if (choice == 'N') {
			cout << endl << "Changes discarded";
		}
	}
	cout << endl << "Thank you for using this program.";
	return unsavedChangedExist;
}
//-----------------------------------------------------------------------------------------
void displayMenu() {
	cout << endl
		<< endl << "**************************************************************"
		<< endl << "\t\tStudent Enrollment Application"
		<< endl << "**************************************************************"
		<< endl << "A: Import \ta Student List from an external text file."
		<< endl << "B: Add    \tStudents' Information into the Student List manually."
		<< endl << "C: Display \tthe Student List."
		<< endl << "D: Sort   \tthe Student List."
		<< endl << "E: Export \tthe Student List to an external text file."
		<< endl << "F: Search \tfor Students in the Student List."
		<< endl << "G: Exit   \tthe program."
		<< endl
		<< endl << "\tWhat option would you like to perform? ";
}
bool importFromFile(vector<Student> & roster) {
	/*List of files opened so far*/
	static vector<string> openedFiles;
	string fInput;
	ifstream fileRoster;
	bool validinput = false;
	cout << endl << "Enter the password/filename: ";
	getline(cin, fInput);
	if (find(openedFiles.begin(), openedFiles.end(), fInput) != openedFiles.end()) {
		cout << endl << "File already opened.";
		return false;
	}
	fileRoster.open(fInput.c_str());
	while (!fileRoster) {
		cout << endl << "Opening Error!";
		char inc;
		do {
			cout << endl << "Would you like to try again, Yes / No ? ";
			getline(cin, fInput);
			inc = toUpperC(fInput[0]);
			if (inc == 'Y' || inc == 'N')
				validinput = true;
			else
				cout << endl << "What? ";
		} while (!validinput);
		if (inc == 'N')
			break;
		else if (inc == 'Y') {
			validinput = false;
			cout << endl << "Please enter the password/filename: ";
			getline(cin, fInput);
			fileRoster.open(fInput.c_str());
		}
	}
	if (!fileRoster)
		return false;//user gives up on opening a file
	openedFiles.push_back(fInput);
	int count = 0;
	string fname, mname, lname, id, clss;
	while (fileRoster >> fname >> mname >> lname >> id >> clss) {
		Student s = Student(id);
		s.addName(txtToName(toUpperS(fname)));
		s.addNames(splitStingBy(toUpperS(mname), '_'));
		s.addName(txtToName(toUpperS(lname)));
		s.addClasses(splitStingBy(toUpperS(clss), ','));
		roster.push_back(s);
		count++;
	}
	cout << endl << "The size of the list is : " << roster.size()
		<< " after adding " << count << " Students.";
	cout << endl << "The file " << fInput << " is opened and read successfully!";
	fileRoster.close();
	return true;
}
string txtToName(string s) {
	char * cs = new char[s.length() + 1];
	for (unsigned int i = 0u; i < s.size(); i++) {
		if (s[i] == '_')
			s[i] = ' ';
	}
	return string(s);
}
string nameToTxt(string name) {
	vector<string> n;
	n.push_back(name);
	return nameToTxt(n);
}
string nameToTxt(vector<string> name) {
	string r;
	/*remove spaces in names*/
	for (unsigned int i = 0u; i < name.size(); i++) {
		for (unsigned int n = 1; n < name[i].size(); n++) {
			if (name[i][n] == ' ')
				name[i][n] = '_';
		}
	}
	r += name[0] + "\t";
	/*add sentinels for missing middle or last names*/
	if (name.size() < 3)
		r += "|";
	else {
		for (unsigned int i = 1; i < name.size() - 2; i++) {
			r += name[i] + "_";
		}
		r += name[name.size() - 2];
	}
	if (name.size() == 1)
		r += "\t |";
	else
		r += "\t" + name[name.size() - 1];
	return r;
}
bool exportRoster(vector<Student>& roster) {
	ofstream outStream;
	string input;
	bool success = true;
	int retries = -1;
	do
	{
		++retries;
		cout << "Please enter a name for your file :";
		getline(cin, input);
		ifstream iss(input.c_str());
		if (iss.good())//able to open file -> file exists already
		{
			char choice = '?';
			do {
				cout << endl << "Do you want to replace file " << input << "?";
				choice = toUpperC(cin.get());
				cin.ignore(INT_MAX, '\n');
				if (choice == 'Y') {
					success = true;
					cout << endl << "Replacing file";
				}
				else if (choice == 'N') {
					success = false;
				}
			} while (choice != 'N' && choice != 'Y');
		}//end file exists test
		iss.close();
		iss.clear();
	} while (!success && retries < 5);
	if (retries >= 3) {
		cout << endl << "Save Failed:" << " Too Many Tries. Sorry.";
		return true;
	}
	//*file does not exist or user consents to replace*/
	outStream.open(input.c_str());
	while (outStream.fail()) {
		outStream.clear();
		cout << endl << " Please enter a new file name :";
		getline(cin, input);
		outStream.open(input.c_str());
	}
	for (unsigned int i = 0u; i < roster.size(); ++i) {
		Student s = roster[i];
		outStream << nameToTxt(s.name) << '\t'
			<< s.studentID << '\t'
			<< s.classlist() << '\n';
	}
	cout << endl << "Export Successful";
	outStream.close();
	return false;//changes are saved
}
void searchByValue(vector<Student>& roster) //sorted roster
{
	string userInput;
	bool repeat = false;
	bool methodselected = false;
	bool test = false;
	int methodchoice = 0;
	do {//while repeat
		vector<Student> results(roster.size());
		do { //while !methodselected
			cout << endl << "Search Menu :"
				<< endl << "1. Search by Name"
				<< endl << "2. Search by ID"
				<< endl << "\tto search by or else you will receive inaccurate results."
				<< endl << "What would you like to search : 1 for Name, 2 for ID ? ";
			cin >> methodchoice;
			methodchoice = validateInteger(methodchoice);
			if (methodchoice == 1 || methodchoice == 2)
				methodselected = true;
			else
				cout << endl << "Invalid choice.";
		} while (!methodselected);
		switch (methodchoice) {
		case (1):
		{
			cout << endl << "Enter the name to be searched: ";
			getline(cin, userInput);
			userInput = toUpperS(userInput);
			//* fill result with students via copy_if, then resize reuslts*/
			sort(roster.begin(), roster.end(), beforeAlphabetically);
			auto it = copy_if(roster.begin(), roster.end(), results.begin(),
				[userInput](Student who) {
				return who.fullName().find(userInput) != string::npos;
			});
			results.resize(distance(results.begin(), it));
			test = results.size() > 0;
			cout << endl << "The name: " << userInput << " was"
				<< (test ? " " : " not ")
				<< "found in the Student List. " << endl;
		}
		break;
		case (2):
		{
			cout << endl << "Enter the ID to be searched: ";
			getline(cin, userInput);
			userInput = toUpperS(userInput);
			sort(roster.begin(), roster.end(), beforeByID);
			//* fill results by copy_if? , then resize reuslts */
			auto it = copy_if(roster.begin(), roster.end(), results.begin(),
				[userInput](Student who) {
				/*check for substring*/
				return who.studentID.find(userInput) != string::npos;
			});//using lambda function. Requires C++11
			results.resize(distance(results.begin(), it));
			test = results.size() > 0;//false if no students found because of resize
			cout << endl << "The ID: " << userInput << " was"
				<< (test ? " " : " not ")
				<< "found in the Student List. " << endl;
		}
		break;
		default:
			cerr << "Error in searchByValue";
		}
		for (unsigned n = 0; n < results.size(); ++n) {
			displayStudent(results[n]);
		}
		bool repeat = false;
		char yn = ' ';
		do {
			cout << endl << "Would you like to search more? "
				<< endl << "Enter Y for Yes, and N for No: ";
			getline(cin, userInput);
			yn = toUpperC(userInput[0]);
			if (!(repeat = (yn == 'Y' || yn == 'N')))
				cout << endl << "Invalid Input.";
		} while (!repeat);
		repeat = (yn == 'Y');
	} while (repeat);
}
int validateInteger(int maybe) {
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << endl << "Invalid input. Please enter a number: ";
		cin >> maybe;
	}
	cin.ignore(INT_MAX, '\n');
	return maybe;
}
char toUpperC(char c) {
	return ((c <= 'z' && 'a' <= c) ? (c + ('Z' - 'z')) : c);
}
string toUpperS(string s) {
	for (unsigned int i = 0u; i < s.size(); i++) {
		s[i] = toUpperC(s[i]);
	}
	return s;
}
int getNNIntegerWithPrompt(const string prompt) {
	int n = -1;
	string sinput;
	int tries = -1;
	do {
		tries++;
		cout << endl << prompt;
		cin >> n;
		n = validateInteger(n);
		if (n < 0)
			cout << endl << "The number must be positive.";
	} while (n < 0 && tries < 5);
	if (tries == 5) {
		cout << endl << "Number not received.";
		return 0;
	}
	return n;
}
string to_Pretty_Print(string name) {
	if (name.size() == 0)
		return "";
	else {
		string out_Name;
		out_Name = toUpperS(name);
		char c;
		char * d = &out_Name[0];
		*d = toUpperC(*d);
		for (unsigned int i = 0u; i < out_Name.size(); i++) {
			c = out_Name[i];
			d = &out_Name[i + 1];
			if (('A' <= c && c <= 'Z')
				|| ('a' <= c && c <= 'z')) {
				*d = toLowerC(*d);
			}
			else {
				*d = toUpperC(*d);
			}
		}
		return out_Name;
	}
}
char toLowerC(char c) {
	return ((c <= 'Z' && 'A' <= c) ? (c + ('z' - 'Z')) : c);
}
void displayStudent(Student & s) {
	unsigned int width = 0;
	for (unsigned int i = 0u; i < s.name.size() - 1; i++) {
		if (s.name[i] != "|") {
			cout << s.name[i];
			width += s.name[i].size() + 1;
			if (width + s.name[i + 1].size() >= fieldLengths[0]) {
				cout << endl;
				width = 0;
			}
			else
				cout << " ";
		}
	}
	cout << left << setw(fieldLengths[0] - width) << (s.name.back() == "|" ? " " : s.name.back());
	cout << setw(fieldLengths[1]) << s.studentID
		<< setw(fieldLengths[2]) << s.classlist();
	cout << endl;
}
void displayRoster(vector<Student> & roster) {
	cout << endl << "The Student List has the size of: " << roster.size() << endl;

	cout << left << setw(fieldLengths[0]) << "Name:"
		<< setw(fieldLengths[1]) << "ID:"
		<< setw(fieldLengths[2]) << "Enrolled Class(es):" << endl;
	for (unsigned int i = 0u; i < fieldLengths[0] + fieldLengths[1] + fieldLengths[2]; i++) {
		cout << '_';
	}
	cout << endl;
	for (unsigned int i = 0u; i < roster.size(); i++) {
		displayStudent(roster[i]);
	}
}
/*takes a string a separates into a vector of strings using a delimiter*/
vector<string> splitStingBy(string name, char delim) {
	vector<string> ret = {};
	string hold = "";
	char test;
	for (auto i : name) {
		test = i;
		if (test == delim) {
			ret.push_back(hold);
			hold = "";
		}
		else
			hold += test;
	}
	if (hold.size() > 0)
		ret.push_back(hold);
	return ret;
}
/*prompts user for a menu choice and returns a char between A and G*/
char getMenuChoice() {
	string choice;
	char ch;
	bool invalid = false;
	do
	{
		if (invalid) {
			cout << endl << "Sorry. Valid Options are A to G.";
			//displayMenu();
		}
		cout << endl << "Please enter menu selection: ";
		getline(cin, choice);
		ch = toUpperC(choice[0]);
		invalid = (ch < 'A' || ch > 'G' || choice.length() > 1);
	} while (invalid);
	return ch;
}
/*prompts user for sorting method, then sorts roster*/
bool executeSort(vector<Student>& roster) {
	int choice;
	bool done = false;
	unsigned tries = 0;
	do {
		cout << endl << "\tS o r t   M e n u:"
			<< endl << "-------------------------"
			<< endl << "1. Sort by First Name."
			<< endl << "2. Sort by Student ID."
			<< endl << "3. Sort by Last Name."
			<< endl << "What would you like to sort?"
			<< endl << "Please enter 1 for Name, 2 for ID, 3 for Sort : ";
		cin >> choice;
		choice = validateInteger(choice);
		switch (choice) {
		case (1):
			sort(roster.begin(), roster.end(), beforeAlphabetically);
			done = true;
			break;
		case (2):
			sort(roster.begin(), roster.end(), beforeByID);
			done = true;
			break;
		case (3):
			sort(roster.begin(), roster.end(), beforeByLastName);
			done = true;
			break;
		default:
			cout << endl << "Sorry, that's invalid input.";
			tries++;
			done = false;
			if (tries > 5u) {
				cout << endl << "Too many attempts";
				return false;
			}
			break;//do..while
		}
	} while (!done);
	if (done) {
		cout << "\nSort successful.";
		return true;
	}
	return false;
}
bool addStudents(vector<Student> & roster) {
	string userInput;
	int iNewStudents;
	iNewStudents = getNNIntegerWithPrompt("How many Students would you like to add? : ");
	for (int i = 1; i <= iNewStudents; i++) {
		vector<string> iname;
		string iden;
		vector<string> vclas;
		cout << endl << "Student " << i << ":";
		userInput = "";
		while (userInput.length() == 0) {
			cout << endl << left << setw(40) << "Please enter the Student's name: ";
			getline(cin, userInput);
		}
		iname = splitStingBy(toUpperS(userInput), ' ');
		cout << "S t u d e n t I D :" << endl
			<< "1. Enter ID manually." << endl
			<< "2. Generate ID automatically.";
		int opt = getNNIntegerWithPrompt("Please select Student's ID method: ");
		bool idOpted = false;
		do {
			switch (opt) {
			case (1):
				cout << endl << setw(40) << "Please enter the Student's ID: ";
				getline(cin, userInput);
				if (userInput.length() == 0)
					continue;//get a new ID if the ID is blank
				iden = toUpperS(userInput);
				idOpted = true;
				break;
			case (2):
				iden = randID();
				cout << endl << setw(40) << "The Student's ID is: " << iden << endl;
				idOpted = true;
				break;
			default:
				cout << "Sorry, that's not a valid choice.";
				cout << "1: Manual\n2: Auto";
				opt = getNNIntegerWithPrompt("Please select Student's ID method... ");
				break;
			}
			for (unsigned i = 0; i < roster.size(); ++i) {
				if (iden == roster[i].studentID) {
					cout << endl << "ID number is already used.";
					idOpted = false;
					break;
				}
			}
		} while (!idOpted);
		int nClasses =
			getNNIntegerWithPrompt("How many Classes would you like to add? ");
		for (int j = 0; j < nClasses; j++) {
			userInput = "";
			while (userInput.length() == 0) {
				cout << setw(40) << "Please enter a Student's class: ";
				getline(cin, userInput);
			}
			vclas.push_back(toUpperS(userInput));
		}
		Student toAdd = Student(iname);
		toAdd.addID(iden);
		toAdd.addClasses(vclas);
		roster.push_back(toAdd);
	}
	return iNewStudents;
}
/* digit by digit is prettier*/
string randID() {
	string id;
	for (int i = 0; i < 7; i++) {
		id += '0' + (rand() % 10);
	}
	return id;
}
/** Function that return count of the given  
character in the string 
Ripped from web www.geeksforgeeks.org/program-count-occurrence-given-character-string/ */
int ccount(string s, char c) {
	int res = 0;
	for (unsigned int i = 0u; i < s.length(); i++) {
		if (s[i] == c)
			res++;
	}
	return res;
}
/*** ~ . _ .  I N S  . _ .  ~ * ~ * ~ . _ . B E R . _ .  . _ .  . _ .
. _ .  V O R  . _ .  I N S  K L E  ~ * ~ * ~
. _ .  ~ * ~ * S T U ~ ~ * ~ * ~ J O H N ~ * ~ * ~ . _ .  . _ .  I N S  . _ .
T R E  ~ * ~ * ~ . _ .  . _ .****/
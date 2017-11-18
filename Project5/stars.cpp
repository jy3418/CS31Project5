#include "utilities.h"
#include <iostream>
using namespace std;

const char WORDFILENAME[] = "C:/Users/jy341/Desktop/smallwords.txt";

int main()
{
	char w[9000][7];
	int n = getWords(w, 9000, WORDFILENAME);
	if (n == 2)
	{
		cout << "getWords successfully found the file and read its two words." << endl;
		cout << "You're ready to start working on Project 5." << endl;
	}
	else if (n == -1)
		cout << "The path to your file of words is probably incorrect" << endl;
	else
		cout << "getWords found the file, but loaded " << n
		<< " words instead of 2" << endl;
}
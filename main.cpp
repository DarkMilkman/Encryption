#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

bool checkIfNumber(std::string s);
int convertToIntEncryption(char c, int method, int startingNum);
char convertToCharEncryption(int i, int method, char startingChar);
int createRandomNumber(int num, int mult, int add, int modNum);
std::vector<int> createRandomNumberVec(int startingSeed, int mult, int add, int modNum);

using namespace std;

int main(int argc, char* argv[])
{
	cout << "Press ESC to Quit, will exit before the next input \n";
////////////////////////////////////////////////////////////////////////////////////////////////
	//Varibles

#pragma region initVars

	const int MODNUM = 95;
	const int STARTINGNUM = 999;
	const char STARTINGCHAR = '\n';

	vector<int> intTextVec;
	vector<int> randVec;
	vector<int> encryptedIntVec;
	vector<char> encryptedCharVec;

	string isEncryptInput;
	string isReadFromFile;

	bool isEncypt;
	bool firstTimeThrough = true;
	bool running = true;
	bool readFromFile;
	bool goodFileName;
	bool goodWriteFileName;


	string plainText;
	string convertMethodString;
	string startingSeedString;
	string mutipleNumberString;
	string addingNumberString;
	string differenceNumberString;

	string readInFile;
	string writeToFile;
	string totalFileText;

	int convertMethod;
	int startingSeed;
	int mutipleNumber;
	int addingNumber;
	int differenceNumber;

	int totalIndexNum;

#pragma endregion
	
/////////////////////////////////////////////////////////////////////////////////////////
	
	while (running)
	{

#pragma region resetVars

		//resetting the data 
		goodFileName = false;
		goodWriteFileName = false;
		readFromFile = false;
		readInFile = " ";
		writeToFile = " ";

		convertMethodString = " ";
		startingSeedString = " ";
		mutipleNumberString = " ";
		addingNumberString = " ";
		differenceNumberString = " ";
		isEncryptInput = " ";
		isReadFromFile = " ";

		convertMethod = atoi(convertMethodString.c_str());
		startingSeed = atoi(startingSeedString.c_str());
		mutipleNumber = atoi(mutipleNumberString.c_str());
		addingNumber = atoi(addingNumberString.c_str());
		differenceNumber = atoi(differenceNumberString.c_str());

		intTextVec.clear();
		randVec.clear();
		encryptedIntVec.clear();
		encryptedCharVec.clear();
		plainText.clear();
		totalFileText.clear();

#pragma endregion

		//Input
		if (!firstTimeThrough)
			cin.ignore();

		firstTimeThrough = false;

		//check to see if read in from file
		while (isReadFromFile[0] != 'Y' && isReadFromFile[0] != 'N' && isReadFromFile[0] != 'y' && isReadFromFile[0] != 'n')
		{
			cout << "Read from file (Y or N): ";
			cin >> isReadFromFile;
		}

		if (isReadFromFile[0] == 'Y' || isReadFromFile[0] == 'y')
		{
			readFromFile = true;
		}
		else if (isReadFromFile[0] == 'N' || isReadFromFile[0] == 'n')
		{
			readFromFile = false;
		}

#pragma region GetPlainText
		if (readFromFile)
		{
			cin.ignore();
			while (!goodFileName)
			{

				cout << "Enter in The Name and extension of the file you want to encrypt/decrypt:";
				getline(cin, readInFile);

				string fileName = readInFile; //"..\\Debug\\" + readInFile;
				//string fileName = "..\\Release\\" + readInFile;

				ifstream file(fileName);

				if (file.is_open())
				{
					cout << "File was opened\n";
					string textBuffer;

					while (!file.eof())
					{
						getline(file, textBuffer);
						totalFileText += textBuffer +'\n';

					}

					goodFileName = true;
					file.close();

				}
				else
				{

					cout << "File couldn't be opened\n";
				}
			}

			cout << "Enter in The Name and extension of the file you want output to:";
			getline(cin, writeToFile);

		}
		else
		{
			cin.ignore();

			while (plainText.empty())
			{
				cout << "Enter in the Text:";
				getline(cin, plainText);
			}
		}
#pragma endregion

#pragma region inputIntVars

		while (!checkIfNumber(convertMethodString))
		{
			cout << "Enter in the method to encrypt (integer 0 - 2): ";
			cin >> convertMethodString;
			convertMethod = atoi(convertMethodString.c_str());
		}
		
		while (!checkIfNumber(startingSeedString))
		{
			cout << "Enter in the starting seed (integer): ";
			cin >> startingSeedString;
			startingSeed = atoi(startingSeedString.c_str());
		}

		while (!checkIfNumber(mutipleNumberString))
		{
			cout << "Enter in a Multiple number (integer): ";
			cin >> mutipleNumberString;
			mutipleNumber = atoi(mutipleNumberString.c_str());
		}
		
		while (!checkIfNumber(addingNumberString))
		{
			cout << "Enter in an Adding number (integer): ";
			cin >> addingNumberString;
			addingNumber = atoi(addingNumberString.c_str());
		}

		while (!checkIfNumber(differenceNumberString))
		{
			cout << "Enter in a Difference number (integer): ";
			cin >> differenceNumberString;
			differenceNumber = atoi(differenceNumberString.c_str());
		}

#pragma endregion

		while (isEncryptInput[0] != 'D' && isEncryptInput[0] != 'E' && isEncryptInput[0] != 'd' && isEncryptInput[0] != 'e')
		{
			cout << "Encryt or Decrypt (E or D): ";
			cin >> isEncryptInput;
		}

		if (isEncryptInput[0] == 'E' || isEncryptInput[0] == 'e')
		{
			isEncypt = true;
		}
		else if (isEncryptInput[0] == 'D' || isEncryptInput[0] == 'd')
		{
			isEncypt = false;
		}

		//use to quit
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			running = false;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//converting input into useable data

		vector<char> plainTextVec(plainText.begin(), plainText.end());
		vector<char> fileTextVec(totalFileText.begin(), totalFileText.end());

#pragma region convertToInt

		if (readFromFile)
		{
			for (std::vector<char>::iterator fit = fileTextVec.begin(); fit != fileTextVec.end(); ++fit)
			{
				if (convertToIntEncryption(*fit, convertMethod, STARTINGNUM) == STARTINGNUM)
				{
					intTextVec.push_back(STARTINGNUM);
				}
				else
				{
					intTextVec.push_back(convertToIntEncryption(*fit, convertMethod, STARTINGNUM));
				}
			}
		}
		else 
		{
			for (std::vector<char>::iterator fit = plainTextVec.begin(); fit != plainTextVec.end(); ++fit)
			{
				intTextVec.push_back(convertToIntEncryption(*fit, convertMethod, STARTINGNUM));
			}
		}

#pragma endregion

#pragma region Encrypt/Decrypt

		randVec = createRandomNumberVec(startingSeed, mutipleNumber, addingNumber, MODNUM);

		totalIndexNum = differenceNumber;
		totalIndexNum = ((totalIndexNum % MODNUM + MODNUM) % MODNUM);
		
		for (std::vector<int>::iterator iit = intTextVec.begin(); iit != intTextVec.end(); ++iit)
		{
			if (isEncypt)
			{
				if (*iit != STARTINGNUM)
					encryptedIntVec.push_back((*iit + randVec[totalIndexNum]) % MODNUM);
				else
					encryptedIntVec.push_back(*iit);

			}
			else
			{
				if (*iit != STARTINGNUM)
				{
					int i = *iit - randVec[totalIndexNum];
					encryptedIntVec.push_back((i % MODNUM + MODNUM) % MODNUM);
				}
				else 
					encryptedIntVec.push_back(*iit);

			}

			totalIndexNum += differenceNumber;
			totalIndexNum = ((totalIndexNum % MODNUM + MODNUM) % MODNUM);
		}

#pragma endregion

#pragma region convertToChar

		for (std::vector<int>::iterator eiit = encryptedIntVec.begin(); eiit != encryptedIntVec.end(); ++eiit)
		{
			if (convertToCharEncryption(*eiit, convertMethod, STARTINGCHAR) == STARTINGCHAR)
			{
				encryptedCharVec.push_back(STARTINGCHAR);
			}
			else
			{
				encryptedCharVec.push_back(convertToCharEncryption(*eiit, convertMethod, STARTINGCHAR));
			}
		}

#pragma endregion

#pragma region OutputtingData

		cout << "Output:\"";

		if (readFromFile)
		{
			cout << "is written to " << writeToFile;

			string fileName = writeToFile; //"..\\Debug\\" + writeToFile;
			//string fileName = "..\\Release\\" + writeToFile;

			ofstream output(fileName);

			for (std::vector<char>::iterator ecit = encryptedCharVec.begin(); ecit != encryptedCharVec.end(); ++ecit)
			{
				output << *ecit;
			}

			output.close();
		}
		else
		{
			for (std::vector<char>::iterator ecit = encryptedCharVec.begin(); ecit != encryptedCharVec.end(); ++ecit)
			{
				std::cout << *ecit;
			}
		}
		std::cout  << "\"" << "\n\n";

#pragma endregion

	}

	system("Pause");
	return 0;
};

bool checkIfNumber(std::string s)
{
	for (string::const_iterator it = s.begin(); it != s.end(); ++it)
	{
		if (!isdigit(*it)) 
			return false;
	}

	return true;
}

int convertToIntEncryption(char c, int method, int startingNum)
{
	int newInt = startingNum;

	switch (method)
	{
#pragma region case 1
		case 1:
		{
			switch (c)
			{
				case ' ':
				{
					newInt = 94;
					break;
				}
				case '!':
				{
					newInt = 93;
					break;
				}
				case '"':
				{
					newInt = 92;
					break;
				}
				case '#':
				{
					newInt = 91;
					break;
				}
				case '$':
				{
					newInt = 90;
					break;
				}
				case '%':
				{
					newInt = 89;
					break;
				}
				case '&':
				{
					newInt = 88;
					break;
				}
				case '\'':
				{
					newInt = 87;
					break;
				}
				case '(':
				{
					newInt = 86;
					break;
				}
				case ')':
				{
					newInt = 85;
					break;
				}
				case '*':
				{
					newInt = 84;
					break;
				}
				case '+':
				{
					newInt = 83;
					break;
				}
				case ',':
				{
					newInt = 82;
					break;
				}
				case '-':
				{
					newInt = 81;
					break;
				}
				case '.':
				{
					newInt = 80;
					break;
				}
				case '/':
				{
					newInt = 79;
					break;
				}
				case '0':
				{
					newInt = 78;
					break;
				}
				case '1':
				{
					newInt = 77;
					break;
				}
				case '2':
				{
					newInt = 76;
					break;
				}
				case '3':
				{
					newInt = 75;
					break;
				}
				case '4':
				{
					newInt = 74;
					break;
				}
				case '5':
				{
					newInt = 73;
					break;
				}
				case '6':
				{
					newInt = 72;
					break;
				}
				case '7':
				{
					newInt = 71;
					break;
				}
				case '8':
				{
					newInt = 70;
					break;
				}
				case '9':
				{
					newInt = 69;
					break;
				}
				case ':':
				{
					newInt = 68;
					break;
				}
				case ';':
				{
					newInt = 67;
					break;
				}
				case '<':
				{
					newInt = 66;
					break;
				}
				case '=':
				{
					newInt = 65;
					break;
				}
				case '>':
				{
					newInt = 64;
					break;
				}
				case '?':
				{
					newInt = 63;
					break;
				}
				case '@':
				{
					newInt = 62;
					break;
				}
				case 'A':
				{
					newInt = 61;
					break;
				}
				case 'B':
				{
					newInt = 60;
					break;
				}
				case 'C':
				{
					newInt = 59;
					break;
				}
				case 'D':
				{
					newInt = 58;
					break;
				}
				case 'E':
				{
					newInt = 57;
					break;
				}
				case 'F':
				{
					newInt = 56;
					break;
				}
				case 'G':
				{
					newInt = 55;
					break;
				}
				case 'H':
				{
					newInt = 54;
					break;
				}
				case 'I':
				{
					newInt = 53;
					break;
				}
				case 'J':
				{
					newInt = 52;
					break;
				}
				case 'K':
				{
					newInt = 51;
					break;
				}
				case 'L':
				{
					newInt = 50;
					break;
				}
				case 'M':
				{
					newInt = 49;
					break;
				}
				case 'N':
				{
					newInt = 48;
					break;
				}
				case 'O':
				{
					newInt = 47;
					break;
				}
				case 'P':
				{
					newInt = 46;
					break;
				}
				case 'Q':
				{
					newInt = 45;
					break;
				}
				case 'R':
				{
					newInt = 44;
					break;
				}
				case 'S':
				{
					newInt = 43;
					break;
				}
				case 'T':
				{
					newInt = 42;
					break;
				}
				case 'U':
				{
					newInt = 41;
					break;
				}
				case 'V':
				{
					newInt = 40;
					break;
				}
				case 'W':
				{
					newInt = 39;
					break;
				}
				case 'X':
				{
					newInt = 38;
					break;
				}
				case 'Y':
				{
					newInt = 37;
					break;
				}
				case 'Z':
				{
					newInt = 36;
					break;
				}
				case '[':
				{
					newInt = 35;
					break;
				}
				case '\\':
				{
					newInt = 34;
					break;
				}
				case ']':
				{
					newInt = 33;
					break;
				}
				case '^':
				{
					newInt = 32;
					break;
				}
				case '_':
				{
					newInt = 31;
					break;
				}
				case '`':
				{
					newInt = 30;
					break;
				}
				case 'a':
				{
					newInt = 29;
					break;
				}
				case 'b':
				{
					newInt = 28;
					break;
				}
				case 'c':
				{
					newInt = 27;
					break;
				}
				case 'd':
				{
					newInt = 26;
					break;
				}
				case 'e':
				{
					newInt = 25;
					break;
				}
				case 'f':
				{
					newInt = 24;
					break;
				}
				case 'g':
				{
					newInt = 23;
					break;
				}
				case 'h':
				{
					newInt = 22;
					break;
				}
				case 'i':
				{
					newInt = 21;
					break;
				}
				case 'j':
				{
					newInt = 20;
					break;
				}
				case 'k':
				{
					newInt = 19;
					break;
				}
				case 'l':
				{
					newInt = 18;
					break;
				}
				case 'm':
				{
					newInt = 17;
					break;
				}
				case 'n':
				{
					newInt = 16;
					break;
				}
				case 'o':
				{
					newInt = 15;
					break;
				}
				case 'p':
				{
					newInt = 14;
					break;
				}
				case 'q':
				{
					newInt = 13;
					break;
				}
				case 'r':
				{
					newInt = 12;
					break;
				}
				case 's':
				{
					newInt = 11;
					break;
				}
				case 't':
				{
					newInt = 10;
					break;
				}
				case 'u':
				{
					newInt = 9;
					break;
				}
				case 'v':
				{
					newInt = 8;
					break;
				}
				case 'w':
				{
					newInt = 7;
					break;
				}
				case 'x':
				{
					newInt = 6;
					break;
				}
				case 'y':
				{
					newInt = 5;
					break;
				}
				case 'z':
				{
					newInt = 4;
					break;
				}
				case '{':
				{
					newInt = 3;
					break;
				}
				case '|':
				{
					newInt = 2;
					break;
				}
				case '}':
				{
					newInt = 1;
					break;
				}
				case '~':
				{
					newInt = 0;
					break;
				}

				default:
				{
					//printf("couldn't convet to number: %s, \n", c);
					break;
				}
			}

			break;
		}
#pragma endregion

#pragma region case 2
	case 2:
	{
		switch (c)
		{
			case ' ':
			{
				newInt = 0;
				break;
			}
			case '!':
			{
				newInt = 2;
				break;
			}
			case '"':
			{
				newInt = 4;
				break;
			}
			case '#':
			{
				newInt = 6;
				break;
			}
			case '$':
			{
				newInt = 8;
				break;
			}
			case '%':
			{
				newInt = 10;
				break;
			}
			case '&':
			{
				newInt = 12;
				break;
			}
			case '\'':
			{
				newInt = 14;
				break;
			}
			case '(':
			{
				newInt = 16;
				break;
			}
			case ')':
			{
				newInt = 18;
				break;
			}
			case '*':
			{
				newInt = 20;
				break;
			}
			case '+':
			{
				newInt = 22;
				break;
			}
			case ',':
			{
				newInt = 24;
				break;
			}
			case '-':
			{
				newInt = 26;
				break;
			}
			case '.':
			{
				newInt = 28;
				break;
			}
			case '/':
			{
				newInt = 30;
				break;
			}
			case '0':
			{
				newInt = 32;
				break;
			}
			case '1':
			{
				newInt = 34;
				break;
			}
			case '2':
			{
				newInt = 36;
				break;
			}
			case '3':
			{
				newInt = 38;
				break;
			}
			case '4':
			{
				newInt = 40;
				break;
			}
			case '5':
			{
				newInt = 42;
				break;
			}
			case '6':
			{
				newInt = 44;
				break;
			}
			case '7':
			{
				newInt = 46;
				break;
			}
			case '8':
			{
				newInt = 48;
				break;
			}
			case '9':
			{
				newInt = 50;
				break;
			}
			case ':':
			{
				newInt = 52;
				break;
			}
			case ';':
			{
				newInt = 54;
				break;
			}
			case '<':
			{
				newInt = 56;
				break;
			}
			case '=':
			{
				newInt = 58;
				break;
			}
			case '>':
			{
				newInt = 60;
				break;
			}
			case '?':
			{
				newInt = 62;
				break;
			}
			case '@':
			{
				newInt = 64;
				break;
			}
			case 'A':
			{
				newInt = 66;
				break;
			}
			case 'B':
			{
				newInt = 68;
				break;
			}
			case 'C':
			{
				newInt = 70;
				break;
			}
			case 'D':
			{
				newInt = 72;
				break;
			}
			case 'E':
			{
				newInt = 74;
				break;
			}
			case 'F':
			{
				newInt = 76;
				break;
			}
			case 'G':
			{
				newInt = 78;
				break;
			}
			case 'H':
			{
				newInt = 80;
				break;
			}
			case 'I':
			{
				newInt = 82;
				break;
			}
			case 'J':
			{
				newInt = 84;
				break;
			}
			case 'K':
			{
				newInt = 86;
				break;
			}
			case 'L':
			{
				newInt = 88;
				break;
			}
			case 'M':
			{
				newInt = 90;
				break;
			}
			case 'N':
			{
				newInt = 92;
				break;
			}
			case 'O':
			{
				newInt = 94;
				break;
			}
			case 'P':
			{
				newInt = 1;
				break;
			}
			case 'Q':
			{
				newInt = 3;
				break;
			}
			case 'R':
			{
				newInt = 5;
				break;
			}
			case 'S':
			{
				newInt = 7;
				break;
			}
			case 'T':
			{
				newInt = 9;
				break;
			}
			case 'U':
			{
				newInt = 11;
				break;
			}
			case 'V':
			{
				newInt = 13;
				break;
			}
			case 'W':
			{
				newInt = 15;
				break;
			}
			case 'X':
			{
				newInt = 17;
				break;
			}
			case 'Y':
			{
				newInt = 19;
				break;
			}
			case 'Z':
			{
				newInt = 21;
				break;
			}
			case '[':
			{
				newInt = 23;
				break;
			}
			case '\\':
			{
				newInt = 25;
				break;
			}
			case ']':
			{
				newInt = 27;
				break;
			}
			case '^':
			{
				newInt = 29;
				break;
			}
			case '_':
			{
				newInt = 31;
				break;
			}
			case '`':
			{
				newInt = 33;
				break;
			}
			case 'a':
			{
				newInt = 35;
				break;
			}
			case 'b':
			{
				newInt = 37;
				break;
			}
			case 'c':
			{
				newInt = 39;
				break;
			}
			case 'd':
			{
				newInt = 41;
				break;
			}
			case 'e':
			{
				newInt = 43;
				break;
			}
			case 'f':
			{
				newInt = 45;
				break;
			}
			case 'g':
			{
				newInt = 47;
				break;
			}
			case 'h':
			{
				newInt = 49;
				break;
			}
			case 'i':
			{
				newInt = 51;
				break;
			}
			case 'j':
			{
				newInt = 53;
				break;
			}
			case 'k':
			{
				newInt = 55;
				break;
			}
			case 'l':
			{
				newInt = 57;
				break;
			}
			case 'm':
			{
				newInt = 59;
				break;
			}
			case 'n':
			{
				newInt = 61;
				break;
			}
			case 'o':
			{
				newInt = 63;
				break;
			}
			case 'p':
			{
				newInt = 65;
				break;
			}
			case 'q':
			{
				newInt = 67;
				break;
			}
			case 'r':
			{
				newInt = 69;
				break;
			}
			case 's':
			{
				newInt = 71;
				break;
			}
			case 't':
			{
				newInt = 73;
				break;
			}
			case 'u':
			{
				newInt = 75;
				break;
			}
			case 'v':
			{
				newInt = 77;
				break;
			}
			case 'w':
			{
				newInt = 79;
				break;
			}
			case 'x':
			{
				newInt = 81;
				break;
			}
			case 'y':
			{
				newInt = 83;
				break;
			}
			case 'z':
			{
				newInt = 85;
				break;
			}
			case '{':
			{
				newInt = 87;
				break;
			}
			case '|':
			{
				newInt = 89;
				break;
			}
			case '}':
			{
				newInt = 91;
				break;
			}
			case '~':
			{
				newInt = 93;
				break;
			}

			default:
			{
				//printf("couldn't convet to number: %s, \n", c);
				break;
			}
		}
		break;
	}
#pragma endregion

#pragma region case 0/default
		default:
		{
			switch (c)
			{
				case ' ':
				{
					newInt = 0;
					break;
				}
				case '!':
				{
					newInt = 1;
					break;
				}
				case '"':
				{
					newInt = 2;
					break;
				}
				case '#':
				{
					newInt = 3;
					break;
				}
				case '$':
				{
					newInt = 4;
					break;
				}
				case '%':
				{
					newInt = 5;
					break;
				}
				case '&':
				{
					newInt = 6;
					break;
				}
				case '\'':
				{
					newInt = 7;
					break;
				}
				case '(':
				{
					newInt = 8;
					break;
				}
				case ')':
				{
					newInt = 9;
					break;
				}
				case '*':
				{
					newInt = 10;
					break;
				}
				case '+':
				{
					newInt = 11;
					break;
				}
				case ',':
				{
					newInt = 12;
					break;
				}
				case '-':
				{
					newInt = 13;
					break;
				}
				case '.':
				{
					newInt = 14;
					break;
				}
				case '/':
				{
					newInt = 15;
					break;
				}
				case '0':
				{
					newInt = 16;
					break;
				}
				case '1':
				{
					newInt = 17;
					break;
				}
				case '2':
				{
					newInt = 18;
					break;
				}
				case '3':
				{
					newInt = 19;
					break;
				}
				case '4':
				{
					newInt = 20;
					break;
				}
				case '5':
				{
					newInt = 21;
					break;
				}
				case '6':
				{
					newInt = 22;
					break;
				}
				case '7':
				{
					newInt = 23;
					break;
				}
				case '8':
				{
					newInt = 24;
					break;
				}
				case '9':
				{
					newInt = 25;
					break;
				}
				case ':':
				{
					newInt = 26;
					break;
				}
				case ';':
				{
					newInt = 27;
					break;
				}
				case '<':
				{
					newInt = 28;
					break;
				}
				case '=':
				{
					newInt = 29;
					break;
				}
				case '>':
				{
					newInt = 30;
					break;
				}
				case '?':
				{
					newInt = 31;
					break;
				}
				case '@':
				{
					newInt = 32;
					break;
				}
				case 'A':
				{
					newInt = 33;
					break;
				}
				case 'B':
				{
					newInt = 34;
					break;
				}
				case 'C':
				{
					newInt = 35;
					break;
				}
				case 'D':
				{
					newInt = 36;
					break;
				}
				case 'E':
				{
					newInt = 37;
					break;
				}
				case 'F':
				{
					newInt = 38;
					break;
				}
				case 'G':
				{
					newInt = 39;
					break;
				}
				case 'H':
				{
					newInt = 40;
					break;
				}
				case 'I':
				{
					newInt = 41;
					break;
				}
				case 'J':
				{
					newInt = 42;
					break;
				}
				case 'K':
				{
					newInt = 43;
					break;
				}
				case 'L':
				{
					newInt = 44;
					break;
				}
				case 'M':
				{
					newInt = 45;
					break;
				}
				case 'N':
				{
					newInt = 46;
					break;
				}
				case 'O':
				{
					newInt = 47;
					break;
				}
				case 'P':
				{
					newInt = 48;
					break;
				}
				case 'Q':
				{
					newInt = 49;
					break;
				}
				case 'R':
				{
					newInt = 50;
					break;
				}
				case 'S':
				{
					newInt = 51;
					break;
				}
				case 'T':
				{
					newInt = 52;
					break;
				}
				case 'U':
				{
					newInt = 53;
					break;
				}
				case 'V':
				{
					newInt = 54;
					break;
				}
				case 'W':
				{
					newInt = 55;
					break;
				}
				case 'X':
				{
					newInt = 56;
					break;
				}
				case 'Y':
				{
					newInt = 57;
					break;
				}
				case 'Z':
				{
					newInt = 58;
					break;
				}
				case '[':
				{
					newInt = 59;
					break;
				}
				case '\\':
				{
					newInt = 60;
					break;
				}
				case ']':
				{
					newInt = 61;
					break;
				}
				case '^':
				{
					newInt = 62;
					break;
				}
				case '_':
				{
					newInt = 63;
					break;
				}
				case '`':
				{
					newInt = 64;
					break;
				}
				case 'a':
				{
					newInt = 65;
					break;
				}
				case 'b':
				{
					newInt = 66;
					break;
				}
				case 'c':
				{
					newInt = 67;
					break;
				}
				case 'd':
				{
					newInt = 68;
					break;
				}
				case 'e':
				{
					newInt = 69;
					break;
				}
				case 'f':
				{
					newInt = 70;
					break;
				}
				case 'g':
				{
					newInt = 71;
					break;
				}
				case 'h':
				{
					newInt = 72;
					break;
				}
				case 'i':
				{
					newInt = 73;
					break;
				}
				case 'j':
				{
					newInt = 74;
					break;
				}
				case 'k':
				{
					newInt = 75;
					break;
				}
				case 'l':
				{
					newInt = 76;
					break;
				}
				case 'm':
				{
					newInt = 77;
					break;
				}
				case 'n':
				{
					newInt = 78;
					break;
				}
				case 'o':
				{
					newInt = 79;
					break;
				}
				case 'p':
				{
					newInt = 80;
					break;
				}
				case 'q':
				{
					newInt = 81;
					break;
				}
				case 'r':
				{
					newInt = 82;
					break;
				}
				case 's':
				{
					newInt = 83;
					break;
				}
				case 't':
				{
					newInt = 84;
					break;
				}
				case 'u':
				{
					newInt = 85;
					break;
				}
				case 'v':
				{
					newInt = 86;
					break;
				}
				case 'w':
				{
					newInt = 87;
					break;
				}
				case 'x':
				{
					newInt = 88;
					break;
				}
				case 'y':
				{
					newInt = 89;
					break;
				}
				case 'z':
				{
					newInt = 90;
					break;
				}
				case '{':
				{
					newInt = 91;
					break;
				}
				case '|':
				{
					newInt = 92;
					break;
				}
				case '}':
				{
					newInt = 93;
					break;
				}
				case '~':
				{
					newInt = 94;
					break;
				}
				default:
				{
					//printf("couldn't convet to number, \n");
					break;
				}
			}
			break;
		}
#pragma endregion

	}

	return newInt;
	
};

char convertToCharEncryption(int i, int method, char startingChar)
{
	char newchar = startingChar;

	switch (method)
	{
#pragma region case 1
		case 1:
		{
			switch (i)
			{
				case 94:
				{
					newchar = ' ';
					break;
				}
				case 93:
				{
					newchar = '!';
					break;
				}
				case 92:
				{
					newchar = '"';
					break;
				}
				case 91:
				{
					newchar = '#';
					break;
				}
				case 90:
				{
					newchar = '$';
					break;
				}
				case 89:
				{
					newchar = '%';
					break;
				}
				case 88:
				{
					newchar = '&';
					break;
				}
				case 87:
				{
					newchar = '\'';
					break;
				}
				case 86:
				{
					newchar = '(';
					break;
				}
				case 85:
				{
					newchar = ')';
					break;
				}
				case 84:
				{
					newchar = '*';
					break;
				}
				case 83:
				{
					newchar = '+';
					break;
				}
				case 82:
				{
					newchar = ',';
					break;
				}
				case 81:
				{
					newchar = '-';
					break;
				}
				case 80:
				{
					newchar = '.';
					break;
				}
				case 79:
				{
					newchar = '/';
					break;
				}
				case 78:
				{
					newchar = '0';
					break;
				}
				case 77:
				{
					newchar = '1';
					break;
				}
				case 76:
				{
					newchar = '2';
					break;
				}
				case 75:
				{
					newchar = '3';
					break;
				}
				case 74:
				{
					newchar = '4';
					break;
				}
				case 73:
				{
					newchar = '5';
					break;
				}
				case 72:
				{
					newchar = '6';
					break;
				}
				case 71:
				{
					newchar = '7';
					break;
				}
				case 70:
				{
					newchar = '8';
					break;
				}
				case 69:
				{
					newchar = '9';
					break;
				}
				case 68:
				{
					newchar = ':';
					break;
				}
				case 67:
				{
					newchar = ';';
					break;
				}
				case 66:
				{
					newchar = '<';
					break;
				}
				case 65:
				{
					newchar = '=';
					break;
				}
				case 64:
				{
					newchar = '>';
					break;
				}
				case 63:
				{
					newchar = '?';
					break;
				}
				case 62:
				{
					newchar = '@';
					break;
				}
				case 61:
				{
					newchar = 'A';
					break;
				}
				case 60:
				{
					newchar = 'B';
					break;
				}
				case 59:
				{
					newchar = 'C';
					break;
				}
				case 58:
				{
					newchar = 'D';
					break;
				}
				case 57:
				{
					newchar = 'E';
					break;
				}
				case 56:
				{
					newchar = 'F';
					break;
				}
				case 55:
				{
					newchar = 'G';
					break;
				}
				case 54:
				{
					newchar = 'H';
					break;
				}
				case 53:
				{
					newchar = 'I';
					break;
				}
				case 52:
				{
					newchar = 'J';
					break;
				}
				case 51:
				{
					newchar = 'K';
					break;
				}
				case 50:
				{
					newchar = 'L';
					break;
				}
				case 49:
				{
					newchar = 'M';
					break;
				}
				case 48:
				{
					newchar = 'N';
					break;
				}
				case 47:
				{
					newchar = 'O';
					break;
				}
				case 46:
				{
					newchar = 'P';
					break;
				}
				case 45:
				{
					newchar = 'Q';
					break;
				}
				case 44:
				{
					newchar = 'R';
					break;
				}
				case 43:
				{
					newchar = 'S';
					break;
				}
				case 42:
				{
					newchar = 'T';
					break;
				}
				case 41:
				{
					newchar = 'U';
					break;
				}
				case 40:
				{
					newchar = 'V';
					break;
				}
				case 39:
				{
					newchar = 'W';
					break;
				}
				case 38:
				{
					newchar = 'X';
					break;
				}
				case 37:
				{
					newchar = 'Y';
					break;
				}
				case 36:
				{
					newchar = 'Z';
					break;
				}
				case 35:
				{
					newchar = '[';
					break;
				}
				case 34:
				{
					newchar = '\\';
					break;
				}
				case 33:
				{
					newchar = ']';
					break;
				}
				case 32:
				{
					newchar = '^';
					break;
				}
				case 31:
				{
					newchar = '_';
					break;
				}
				case 30:
				{
					newchar = '`';
					break;
				}
				case 29:
				{
					newchar = 'a';
					break;
				}
				case 28:
				{
					newchar = 'b';
					break;
				}
				case 27:
				{
					newchar = 'c';
					break;
				}
				case 26:
				{
					newchar = 'd';
					break;
				}
				case 25:
				{
					newchar = 'e';
					break;
				}
				case 24:
				{
					newchar = 'f';
					break;
				}
				case 23:
				{
					newchar = 'g';
					break;
				}
				case 22:
				{
					newchar = 'h';
					break;
				}
				case 21:
				{
					newchar = 'i';
					break;
				}
				case 20:
				{
					newchar = 'j';
					break;
				}
				case 19:
				{
					newchar = 'k';
					break;
				}
				case 18:
				{
					newchar = 'l';
					break;
				}
				case 17:
				{
					newchar = 'm';
					break;
				}
				case 16:
				{
					newchar = 'n';
					break;
				}
				case 15:
				{
					newchar = 'o';
					break;
				}
				case 14:
				{
					newchar = 'p';
					break;
				}
				case 13:
				{
					newchar = 'q';
					break;
				}
				case 12:
				{
					newchar = 'r';
					break;
				}
				case 11:
				{
					newchar = 's';
					break;
				}
				case 10:
				{
					newchar = 't';
					break;
				}
				case 9:
				{
					newchar = 'u';
					break;
				}
				case 8:
				{
					newchar = 'v';
					break;
				}
				case 7:
				{
					newchar = 'w';
					break;
				}
				case 6:
				{
					newchar = 'x';
					break;
				}
				case 5:
				{
					newchar = 'y';
					break;
				}
				case 4:
				{
					newchar = 'z';
					break;
				}
				case 3:
				{
					newchar = '{';
					break;
				}
				case 2:
				{
					newchar = '|';
					break;
				}
				case 1:
				{
					newchar = '}';
					break;
				}
				case 0:
				{
					newchar = '~';
					break;
				}

				default:
				{
					//printf("couldn't convet to letter: %s, \n", i);
					break;
				}
			}

			break;
		}
#pragma endregion

#pragma region case 2
	case 2:
	{
		switch (i)
		{
			case 0:
			{
				newchar = ' ';
				break;
			}
			case 2:
			{
				newchar = '!';
				break;
			}
			case 4:
			{
				newchar = '"';
				break;
			}
			case 6:
			{
				newchar = '#';
				break;
			}
			case 8:
			{
				newchar = '$';
				break;
			}
			case 10:
			{
				newchar = '%';
				break;
			}
			case 12:
			{
				newchar = '&';
				break;
			}
			case 14:
			{
				newchar = '\'';
				break;
			}
			case 16:
			{
				newchar = '(';
				break;
			}
			case 18:
			{
				newchar = ')';
				break;
			}
			case 20:
			{
				newchar = '*';
				break;
			}
			case 22:
			{
				newchar = '+';
				break;
			}
			case 24:
			{
				newchar = ',';
				break;
			}
			case 26:
			{
				newchar = '-';
				break;
			}
			case 28:
			{
				newchar = '.';
				break;
			}
			case 30:
			{
				newchar = '/';
				break;
			}
			case 32:
			{
				newchar = '0';
				break;
			}
			case 34:
			{
				newchar = '1';
				break;
			}
			case 36:
			{
				newchar = '2';
				break;
			}
			case 38:
			{
				newchar = '3';
				break;
			}
			case 40:
			{
				newchar = '4';
				break;
			}
			case 42:
			{
				newchar = '5';
				break;
			}
			case 44:
			{
				newchar = '6';
				break;
			}
			case 46:
			{
				newchar = '7';
				break;
			}
			case 48:
			{
				newchar = '8';
				break;
			}
			case 50:
			{
				newchar = '9';
				break;
			}
			case 52:
			{
				newchar = ':';
				break;
			}
			case 54:
			{
				newchar = ';';
				break;
			}
			case 56:
			{
				newchar = '<';
				break;
			}
			case 58:
			{
				newchar = '=';
				break;
			}
			case 60:
			{
				newchar = '>';
				break;
			}
			case 62:
			{
				newchar = '?';
				break;
			}
			case 64:
			{
				newchar = '@';
				break;
			}
			case 66:
			{
				newchar = 'A';
				break;
			}
			case 68:
			{
				newchar = 'B';
				break;
			}
			case 70:
			{
				newchar = 'C';
				break;
			}
			case 72:
			{
				newchar = 'D';
				break;
			}
			case 74:
			{
				newchar = 'E';
				break;
			}
			case 76:
			{
				newchar = 'F';
				break;
			}
			case 78:
			{
				newchar = 'G';
				break;
			}
			case 80:
			{
				newchar = 'H';
				break;
			}
			case 82:
			{
				newchar = 'I';
				break;
			}
			case 84:
			{
				newchar = 'J';
				break;
			}
			case 86:
			{
				newchar = 'K';
				break;
			}
			case 88:
			{
				newchar = 'L';
				break;
			}
			case 90:
			{
				newchar = 'M';
				break;
			}
			case 92:
			{
				newchar = 'N';
				break;
			}
			case 94:
			{
				newchar = 'O';
				break;
			}
			case 1:
			{
				newchar = 'P';
				break;
			}
			case 3:
			{
				newchar = 'Q';
				break;
			}
			case 5:
			{
				newchar = 'R';
				break;
			}
			case 7:
			{
				newchar = 'S';
				break;
			}
			case 9:
			{
				newchar = 'T';
				break;
			}
			case 11:
			{
				newchar = 'U';
				break;
			}
			case 13:
			{
				newchar = 'V';
				break;
			}
			case 15:
			{
				newchar = 'W';
				break;
			}
			case 17:
			{
				newchar = 'X';
				break;
			}
			case 19:
			{
				newchar = 'Y';
				break;
			}
			case 21:
			{
				newchar = 'Z';
				break;
			}
			case 23:
			{
				newchar = '[';
				break;
			}
			case 25:
			{
				newchar = '\\';
				break;
			}
			case 27:
			{
				newchar = ']';
				break;
			}
			case 29:
			{
				newchar = '^';
				break;
			}
			case 31:
			{
				newchar = '_';
				break;
			}
			case 33:
			{
				newchar = '`';
				break;
			}
			case 35:
			{
				newchar = 'a';
				break;
			}
			case 37:
			{
				newchar = 'b';
				break;
			}
			case 39:
			{
				newchar = 'c';
				break;
			}
			case 41:
			{
				newchar = 'd';
				break;
			}
			case 43:
			{
				newchar = 'e';
				break;
			}
			case 45:
			{
				newchar = 'f';
				break;
			}
			case 47:
			{
				newchar = 'g';
				break;
			}
			case 49:
			{
				newchar = 'h';
				break;
			}
			case 51:
			{
				newchar = 'i';
				break;
			}
			case 53:
			{
				newchar = 'j';
				break;
			}
			case 55:
			{
				newchar = 'k';
				break;
			}
			case 57:
			{
				newchar = 'l';
				break;
			}
			case 59:
			{
				newchar = 'm';
				break;
			}
			case 61:
			{
				newchar = 'n';
				break;
			}
			case 63:
			{
				newchar = 'o';
				break;
			}
			case 65:
			{
				newchar = 'p';
				break;
			}
			case 67:
			{
				newchar = 'q';
				break;
			}
			case 69:
			{
				newchar = 'r';
				break;
			}
			case 71:
			{
				newchar = 's';
				break;
			}
			case 73:
			{
				newchar = 't';
				break;
			}
			case 75:
			{
				newchar = 'u';
				break;
			}
			case 77:
			{
				newchar = 'v';
				break;
			}
			case 79:
			{
				newchar = 'w';
				break;
			}
			case 81:
			{
				newchar = 'x';
				break;
			}
			case 83:
			{
				newchar = 'y';
				break;
			}
			case 85:
			{
				newchar = 'z';
				break;
			}
			case 87:
			{
				newchar = '{';
				break;
			}
			case 89:
			{
				newchar = '|';
				break;
			}
			case 91:
			{
				newchar = '}';
				break;
			}
			case 93:
			{
				newchar = '~';
				break;
			}

			default:
			{
				//printf("couldn't convet to letter: %s, \n", i);
				break;
			}
		}

		break;
	}
#pragma endregion

#pragma region case 0/default
		default:
			switch (i)
			{
				case 0:
				{
					newchar = ' ';
					break;
				}
				case 1:
				{
					newchar = '!';
					break;
				}
				case 2:
				{
					newchar = '"';
					break;
				}
				case 3:
				{
					newchar = '#';
					break;
				}
				case 4:
				{
					newchar = '$';
					break;
				}
				case 5:
				{
					newchar = '%';
					break;
				}
				case 6:
				{
					newchar = '&';
					break;
				}
				case 7:
				{
					newchar = '\'';
					break;
				}
				case 8:
				{
					newchar = '(';
					break;
				}
				case 9:
				{
					newchar = ')';
					break;
				}
				case 10:
				{
					newchar = '*';
					break;
				}
				case 11:
				{
					newchar = '+';
					break;
				}
				case 12:
				{
					newchar = ',';
					break;
				}
				case 13:
				{
					newchar = '-';
					break;
				}
				case 14:
				{
					newchar = '.';
					break;
				}
				case 15:
				{
					newchar = '/';
					break;
				}
				case 16:
				{
					newchar = '0';
					break;
				}
				case 17:
				{
					newchar = '1';
					break;
				}
				case 18:
				{
					newchar = '2';
					break;
				}
				case 19:
				{
					newchar = '3';
					break;
				}
				case 20:
				{
					newchar = '4';
					break;
				}
				case 21:
				{
					newchar = '5';
					break;
				}
				case 22:
				{
					newchar = '6';
					break;
				}
				case 23:
				{
					newchar = '7';
					break;
				}
				case 24:
				{
					newchar = '8';
					break;
				}
				case 25:
				{
					newchar = '9';
					break;
				}
				case 26:
				{
					newchar = ':';
					break;
				}
				case 27:
				{
					newchar = ';';
					break;
				}
				case 28:
				{
					newchar = '<';
					break;
				}
				case 29:
				{
					newchar = '=';
					break;
				}
				case 30:
				{
					newchar = '>';
					break;
				}
				case 31:
				{
					newchar = '?';
					break;
				}
				case 32:
				{
					newchar = '@';
					break;
				}
				case 33:
				{
					newchar = 'A';
					break;
				}
				case 34:
				{
					newchar = 'B';
					break;
				}
				case 35:
				{
					newchar = 'C';
					break;
				}
				case 36:
				{
					newchar = 'D';
					break;
				}
				case 37:
				{
					newchar = 'E';
					break;
				}
				case 38:
				{
					newchar = 'F';
					break;
				}
				case 39:
				{
					newchar = 'G';
					break;
				}
				case 40:
				{
					newchar = 'H';
					break;
				}
				case 41:
				{
					newchar = 'I';
					break;
				}
				case 42:
				{
					newchar = 'J';
					break;
				}
				case 43:
				{
					newchar = 'K';
					break;
				}
				case 44:
				{
					newchar = 'L';
					break;
				}
				case 45:
				{
					newchar = 'M';
					break;
				}
				case 46:
				{
					newchar = 'N';
					break;
				}
				case 47:
				{
					newchar = 'O';
					break;
				}
				case 48:
				{
					newchar = 'P';
					break;
				}
				case 49:
				{
					newchar = 'Q';
					break;
				}
				case 50:
				{
					newchar = 'R';
					break;
				}
				case 51:
				{
					newchar = 'S';
					break;
				}
				case 52:
				{
					newchar = 'T';
					break;
				}
				case 53:
				{
					newchar = 'U';
					break;
				}
				case 54:
				{
					newchar = 'V';
					break;
				}
				case 55:
				{
					newchar = 'W';
					break;
				}
				case 56:
				{
					newchar = 'X';
					break;
				}
				case 57:
				{
					newchar = 'Y';
					break;
				}
				case 58:
				{
					newchar = 'Z';
					break;
				}
				case 59:
				{
					newchar = '[';
					break;
				}
				case 60:
				{
					newchar = '\\';
					break;
				}
				case 61:
				{
					newchar = ']';
					break;
				}
				case 62:
				{
					newchar = '^';
					break;
				}
				case 63:
				{
					newchar = '_';
					break;
				}
				case 64:
				{
					newchar = '`';
					break;
				}
				case 65:
				{
					newchar = 'a';
					break;
				}
				case 66:
				{
					newchar = 'b';
					break;
				}
				case 67:
				{
					newchar = 'c';
					break;
				}
				case 68:
				{
					newchar = 'd';
					break;
				}
				case 69:
				{
					newchar = 'e';
					break;
				}
				case 70:
				{
					newchar = 'f';
					break;
				}
				case 71:
				{
					newchar = 'g';
					break;
				}
				case 72:
				{
					newchar = 'h';
					break;
				}
				case 73:
				{
					newchar = 'i';
					break;
				}
				case 74:
				{
					newchar = 'j';
					break;
				}
				case 75:
				{
					newchar = 'k';
					break;
				}
				case 76:
				{
					newchar = 'l';
					break;
				}
				case 77:
				{
					newchar = 'm';
					break;
				}
				case 78:
				{
					newchar = 'n';
					break;
				}
				case 79:
				{
					newchar = 'o';
					break;
				}
				case 80:
				{
					newchar = 'p';
					break;
				}
				case 81:
				{
					newchar = 'q';
					break;
				}
				case 82:
				{
					newchar = 'r';
					break;
				}
				case 83:
				{
					newchar = 's';
					break;
				}
				case 84:
				{
					newchar = 't';
					break;
				}
				case 85:
				{
					newchar = 'u';
					break;
				}
				case 86:
				{
					newchar = 'v';
					break;
				}
				case 87:
				{
					newchar = 'w';
					break;
				}
				case 88:
				{
					newchar = 'x';
					break;
				}
				case 89:
				{
					newchar = 'y';
					break;
				}
				case 90:
				{
					newchar = 'z';
					break;
				}
				case 91:
				{
					newchar = '{';
					break;
				}
				case 92:
				{
					newchar = '|';
					break;
				}
				case 93:
				{
					newchar = '}';
					break;
				}
				case 94:
				{
					newchar = '~';
					break;
				}
				default:
				{
					//printf("couldn't convet to letter\n");
					break;
				}
			}

			break;
#pragma endregion

	}

	return newchar;

};

int createRandomNumber(int num, int mult, int add, int modNum)
{
	return (mult*num + add) % modNum;
};

std::vector<int> createRandomNumberVec(int startingSeed, int mult, int add, int modNum)
{
	std::vector<int> randVec;

	randVec.push_back(createRandomNumber(startingSeed, mult, add, modNum));

	for (int i = 1; i <= 94; i++)
	{
		randVec.push_back(createRandomNumber(randVec[i - 1], mult, add, modNum));
	}
	return randVec;
};

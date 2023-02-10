#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

void FunctionID(int ID)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 2);
	switch (ID)
	{
	case 1:
		cout << endl << "\t------------------------------------------------------------------" << endl;
		cout << endl << "\t|                           ALL DATA                             |" << endl;
		cout << endl << "\t__________________________________________________________________" << endl << endl;
		break;
	case 2:
		cout << endl << "\t------------------------------------------------------------------" << endl;
		cout << endl << "\t|                        SEARCH IN DATA                          |" << endl;
		cout << endl << "\t__________________________________________________________________" << endl << endl;
		break;
	case 3:
		cout << endl << "\t------------------------------------------------------------------" << endl;
		cout << endl << "\t|                         ENTER STOCK                            |" << endl;
		cout << endl << "\t__________________________________________________________________" << endl << endl;
		break;
	case 4:
		cout << endl << "\t------------------------------------------------------------------" << endl;
		cout << endl << "\t|                         BUY A BOOK                             |" << endl;
		cout << endl << "\t__________________________________________________________________" << endl << endl;
		break;
	case 0:
		cout << endl << "\t------------------------------------------------------------------" << endl;
		cout << endl << "\t|                    LIBRARY MANAGMENT SYSTEM                    |" << endl;
		cout << endl << "\t__________________________________________________________________" << endl << endl;
		break;
	}
	SetConsoleTextAttribute(h, 15);
}
bool Search(string searchTerm,bool buyIt)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char available = '0';
	fstream Data("Data.csv");
	ofstream temp("Temp.txt", ios::trunc);
	temp.clear();
	int i = 1;
	SetConsoleTextAttribute(h, 3);
	cout << "\n\tSL_NO.\t| BOOK_NAME\t\t| AUTHOR\t| PAGES\t| CHAPTERS \n\n";
	SetConsoleTextAttribute(h, 15);
	string line;
	if (Data.is_open()) {
		while (getline(Data, line)) {
			if (line.find(searchTerm) != std::string::npos)
			{
				if (buyIt)
				{
					size_t found = line.find('1');
					line.replace(found, 1, 1, '0');
					temp << line << endl;
					cout << line << endl;
				}
				else
				{
					size_t found = line.find(',');
					while (found != std::string::npos) 
					{
						line.replace(found, 1, 1, '\t');
						found = line.find(',');
					}
					cout << i << " : " << line << endl;
				}
				available = line[0];
				i++;
			}
			else
			{
				temp << line << endl;
			}
		}
		Data.close();
	}
	else
	{
		cout << "!!!!!!!!!!!!!!!!!Unable to open file !!!!!!!!!!!!!!!!!" << endl;
	}
//	temp.close();
	if (temp.is_open() && buyIt) 
	{
		ofstream Data("Data.csv");
		ifstream temp("Temp.txt", ios::in);
		while (getline(temp, line))
		{
			Data << line << endl;
		}
	}
	Data.close();
	temp.close();
	remove("Temp.txt");
	cout << endl;
	return bool(available - 48);
}
void ShowData()
{

	ifstream Data("Data.csv");
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 3);
	cout << "\n\tSL_NO.\t| BOOK_NAME\t\t| AUTHOR\t| PAGES\t| CHAPTERS \n\n";
	SetConsoleTextAttribute(h, 15);
	if (Data.is_open()) {
		string line;
		while (getline(Data, line)) 
		{
				size_t found = line.find(',');
				while (found != std::string::npos) 
				{
					line.replace(found, 1, 1, '\t');
					found = line.find(',');
				}
				cout << line << endl;
		}
		Data.close();
	}
	else {
		cout << "!!!!!!!!!!!!!!!!!Unable to open file !!!!!!!!!!!!!!!!!" << endl;
	}
	cout << endl << endl;
}
void EnterStock()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int BookPages, BookChapter;
	string BookName = "None", BookAuthor = "None", BookNo="0000";
	ofstream Data("Data.csv", ios::app);
	bool runLoop = 1;
	while (runLoop)
	{
		cout << "Enter the Book Number        : ";cin >> BookNo;
		cout << "Enter the Book Name          : ";
		cin.ignore();
		getline(cin, BookName);
		cout << "Enter the Author Name        : ";
		getline(cin, BookAuthor);
		cout << "Enter the Number of Pages    : ";cin >> BookPages;
		cout << "Enter the Number of Chapters : ";cin >> BookChapter;

		if (Data.is_open())
		{
			Data << 1 << "," << BookNo << "," << BookName << "," << BookAuthor << "," << BookPages << "," << BookChapter << endl;
			SetConsoleTextAttribute(h, 2);
			cout << "\n===========================================================" << endl;
			cout << "\n               !Stock has been updated! " << endl;
			cout << "\n===========================================================" << endl;
			SetConsoleTextAttribute(h, 15);
			cout << "\t1 to Add more 0 to Exit";cin >> runLoop;

		}
		else
		{
			SetConsoleTextAttribute(h, 2);
			cout << "!!!!!!!!!!!!!!!!!Unable to open file!!!!!!!!!!!!!!!!!" << endl;
		}
		system("cls");
		FunctionID(3);
	}
	Data.close();
}
void Issue()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 3);
	string srNo;
	bool buyIt = 0;
	cout << "\nWrtie the Serial Number of book : ";cin >> srNo;
	SetConsoleTextAttribute(h, 3);
	if (Search(srNo,false))
	{
		SetConsoleTextAttribute(h, 2);
		cout << "\n\============================================================================";
		cout << "\n\tBook is Available !";
		cout << "\n\============================================================================";
		SetConsoleTextAttribute(h, 15);
		cout << "\n\tPress 1 to Buy it : ";cin >> buyIt;
		if (buyIt)
		{
			Search(srNo,buyIt);
			SetConsoleTextAttribute(h, 2);
			cout << "==========================================================================";
			cout << "\n\tCongratulations Book is Yours \n";
			cout << "==========================================================================\n\n";

		}
	}
	else
	{
		SetConsoleTextAttribute(h, 4);
		cout << "\n==========================================================================";
		cout << "\n\t\tSorry! Book is not Available" << endl;
		cout << "\n==========================================================================\n\n";

	}

}

int main()
{
	string searchTerm;
	int option;
	int *pOption = &option;

	while (*pOption!=5)
	{
		system("cls");
		FunctionID(0);
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << " 1 Show all data " << endl;
		cout << " 2 Search in data " << endl;
		cout << " 3 Enter Data " << endl;
		cout << " 4 Buy Book " << endl;
		cout << " 5 Exit " << endl << endl;
		cout << "Enter the Option : ";cin >> option;
		system("cls");
		SetConsoleTextAttribute(h, 15);
		switch (option)
		{
		case 1:FunctionID(1);ShowData();break;
		case 2:FunctionID(2);
				SetConsoleTextAttribute(h, 3);
				cout << "\n\tEnter a search term: ";
				cin >> searchTerm;
				Search(searchTerm, false);
				break;
		case 3:FunctionID(3);EnterStock();break;
		case 4:FunctionID(4);Issue();
		}
		system("pause");
	}
}
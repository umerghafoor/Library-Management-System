#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool Search(string searchTerm,bool buyIt)
{
	char available = '0';
	fstream Data("Data.csv");
	fstream temp("Temp.csv",ios::app);
	int i = 1;
	cout << "\tSL_NO.\t| BOOK_NAME\t| AUTHOR\t| PAGES\t| CHAPTERS \n\n";
	if (Data.is_open()) {
		string line;
		while (getline(Data, line)) {
			if (line.find(searchTerm) != std::string::npos)
			{
				if (buyIt)
				{
					temp << line << endl;
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
		}
		Data.close();
	}
	else
	{
		cout << "!!!!!!!!!!!!!!!!!Unable to open file !!!!!!!!!!!!!!!!!" << endl;
	}

	if (temp.is_open() && buyIt) 
	{
		ofstream Data("Data.csv");
		Data.clear();
		string line;
		while (getline(temp, line))
		{
			Data << line << endl;
		}
	}
	Data.close();

	return bool(available - 48);
}


void ShowData()
{

	ifstream Data("Data.csv");
	
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
}

void EnterStock()
{
	int BookPages, BookChapter;
	string BookName = "None", BookAuthor = "None", BookNo="00000";
	ofstream Data("Data.csv", ios::app);
	while (true)
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
			cout << "\n               !Stock has been updated! " << endl;
		}
		else
		{
			cout << "!!!!!!!!!!!!!!!!!Unable to open file!!!!!!!!!!!!!!!!!" << endl;
		}
	}
	Data.close();
}

void Issue()
{
	string srNo;
	bool buyIt = 0;
	cout << "Wrtie the Serial Number of book : ";cin >> srNo;
	if (Search(srNo,false))
	{
		cout << "\nBook is Available";
		cout << "\nPress 1 to Buy it : ";cin >> buyIt;
		if (buyIt)
		{
			Search(srNo,buyIt);
			cout << "\tCongratulations Book is Yours \n";
		}


	}

}

int main()
{
	string searchTerm;
	while (true)
	{
		ShowData();
		Issue();
		ShowData();
		cout << "Enter a search term: ";
		cin >> searchTerm;
		Search(searchTerm, false);
		EnterStock();
	}
}
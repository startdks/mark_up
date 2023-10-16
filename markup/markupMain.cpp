/*
* Name: DONG KI, SIN
* Date: Mar, 27, 2023
* Purpose:  Create a C++ 20 application that converts a text file into a format more appropriate for use in a webpage, smartphone, or e-book reader. 
*/

#include "markup_header.hpp"
#include <filesystem>
using namespace std::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
	vector<string> argument;
	ifstream infile;
	vector<string> fileName;
	bool report = false;
	bool paragraph = false;
	bool colorize = false;
	bool keyswitch = false;
	vector<string> keywordVector;

	for (int i = 0; i < argc; i++)
	{
		argument.push_back(argv[i]);
		if (argument[i] == "--help") 
		{
			helpPrint(); //print help and quit
			return 1;
		}
	}

	for (int i = 1; i < argument.size(); i++) 
	{
		if (colorize) {
			keywordVector.push_back(argument[i]); //store keywords
		}
		else if (argument[i] == "--keywords") 
		{
			if (!report && !paragraph && argument.size() == i) {
				cout << "Error: unknown switch \"" << argument[i] << "\"\n";
				return 1;
			}
			colorize = true;
		}
		else if (argument[i][0] == '-' && !report && !paragraph) { 
			for (int j = 1; j < argument[i].size(); j++) {
				if (argument[i][j] == 'r') { //r switch = true
					report = true;
				}
				else if (argument[i][j] == 'p') { //r switch = true
					paragraph = true;
				}
				else if (argument[i] != "--keywords") {
					cout << "Error: unknown switch \"" << argument[i] << "\"\n";
					return 1;
				}

			}
			keyswitch = true;
		}
		else {
			fileName.push_back(argument[i]);  //store fileName
			if (fileName.size() == 2) {
				if (fileName[0] == fileName[1]) {
					cout << "Error: input and output files are the same.\n";
					return 1;
				}
			}
			else if (fileName.size() > 2) {
				cout << "Error: too many command line arguments \"" << fileName[2] << "\"\n";
				return 1;
			}
		}

	}

	if (!fileName.size()) 
	{
		cout << "Error: text file not specified.\n";
		return 1;
	}
	else if (fileName.size() == 1) 
	{
		if (fileName[0].substr(fileName[0].size() - 4, fileName[0].size()) == "html")  //chage to output fileName
		{
			cout << "Error: input and output files are the same.\n";
			return 1;
		}
	}

	if (!keywordVector.size() && colorize) 
	{
		cout << "Error: keyword list is empty.\n";
	}
	else if (keywordVector.size() > 12) 
	{
		cout << "Error: keyword list is too large (maximum 12).\n";
		return 1;
	}


	if (!infile) 
	{
		cout << "Error: text filename " << fileName[0] << " --> No such file or directory\n";
	}

	vector<string> color = { "Red", "SpringGreen", "Teal", "DodgerBlue", "Green", "Blue", "DarkTurquoise", "Magenta", "Indigo", "DarkRed", "DeepPink", "OrangeRed" };
	map<string, int> kewordsMap;

	for (string s : keywordVector) //copy keywordVector to kewordsMap
	{
		kewordsMap[s] = 0;
	}

	int totalTag = 0;
	int lineCnt = 0;
	if (fileName.size())
	{
		string stringWord;
		vector<string> rawStringWords;
		infile.open(fileName[0]);

		while (getline(infile, stringWord))
		{
			if (stringWord != "")
			{
				rawStringWords.push_back(stringWord);
				for (auto s : kewordsMap)
				{
					size_t pos = stringWord.find(s.first); //find keywords
					while (pos != string::npos)
					{
						totalTag++;
						kewordsMap[s.first]++;
						pos = stringWord.find(s.first, pos + 1);
						
					}
					
				}
			}
			rawStringWords.push_back("\n");
			lineCnt++;
		}



		vector<string> newWords;
		newWords.push_back("<!DOCTYPE html>\n");
		newWords.push_back("<html>\n");
		newWords.push_back("<head>\n");
		newWords.push_back("<title>");
		newWords.push_back(fileName[0].substr(0, fileName[0].size() - 4));
		newWords.push_back("</title>\n");
		newWords.push_back("<style>\n");
		newWords.push_back("</style>\n");
		newWords.push_back("</head>\n");
		newWords.push_back("<body>\n");
		int paraCnt = 0;
		if (paragraph)
		{
			newWords.push_back("<p>\n");
		}
		for (int i = 0; i < rawStringWords.size(); i++)
		{
			if ((i > 0 && i + 1 < rawStringWords.size()) && ((rawStringWords[i - 1] == "\n" && rawStringWords[i] == "\n") || (rawStringWords[i + 1] == "\n" && rawStringWords[i] == "\n")))
			{
				
				if (rawStringWords[i - 1] != "\n")
				{
					newWords.push_back("\n");
				}
				newWords.push_back("<br>\n");
			}
			else
			{
				newWords.push_back(rawStringWords[i]);
			}
		}

		if (!paragraph)
		{
			newWords[newWords.size() - 1] = ("\n<br>\n");
		}
		else 
		{
			newWords[newWords.size() - 1] = ("\n</p>\n");
		}
		newWords.push_back("</body>\n");
		newWords.push_back("</html>");
		
		
		if (report) //report
		{
			reportTrue(newWords, paraCnt, lineCnt, totalTag);
			tagPrint(kewordsMap, color);
		}

		if (paragraph) //get <p> and </p>
		{

			paragraphTrue(newWords);
		}

		

		


	//output file
	std::ofstream outputFile(fileName[0].substr(0, fileName[0].size() - 4) + ".html");
	if (outputFile.is_open())
	{
		for (string c : newWords)
		{
			outputFile << c;
		}
		outputFile.close();
	}
	else
	{
		std::cerr << "Unable to open file\n";
	}

	}
	EXIT_SUCCESS;
}

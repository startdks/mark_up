/*
* Name: DONG KI, SIN
* Date: Mar, 27, 2023
* Purpose: implement functions
*/

#include "markup_header.hpp"
using namespace std;



/*
fn: helpPrint;
input: () ;
output: void
purpose: print Help prompt
*/

void helpPrint()
{
	cout << endl << "usage: markup[--help][-rp] textFilename[htmlFilename][--keywords Args...]" << endl << endl;
	cout << "--help          display the help text for the program." << endl;
	cout << "- r             report convertion metrics" << endl;
	cout << "- p             use <p> tag for paragraph breaks" << endl << endl;
	cout << "textFilename    the name of the ASCII text file to process" << endl;
	cout << "htmlFilename    the name of the HTML file receiving the output." << endl;
	cout << "		If not provided the text filename will be used" << endl;
	cout << "		If not provided the text filename will be used" << endl;
	cout << "		with its extension changed to \".html\"" << endl << endl;
	cout << "--keywords      keywords to highlight" << endl;
}



/*
fn: reportTrue;
input: (vector<string> & newWords, int &paraCnt, int &lineCnt, int & totalTag)  ;
output: void
purpose: count paragraphs and prompt number of lines, paragraphs, tags
*/
void reportTrue(vector<string> & newWords, int &paraCnt, int &lineCnt, int & totalTag) 
{
	for (int i = 1; i < newWords.size() - 1; i++)
	{

		if (newWords[i + 1] != "<br>\n" && newWords[i] == "<br>\n")
		{
			paraCnt++;
		}
	}
	cout << "# lines input = " << lineCnt << endl;
	cout << "# paragraphs output = " << paraCnt << endl;
	cout << "# tag = " << totalTag << endl;
}


/*
fn: paragraphTrue;
input: (vector<string>& newWords) ;
output: void
purpose: insert <p> and </p>
*/
void paragraphTrue(vector<string>& newWords)
{
	for (int i = 1; i < newWords.size() - 1; i++)
	{

		if (newWords[i + 1] != "<br>\n" && newWords[i] == "<br>\n")
		{
			newWords[i] = ("<p>\n");
		}

		if (newWords[i - 1] == "\n" && newWords[i] == "<br>\n")
		{
			newWords[i] = ("</p>\n");
		}
	}
}



/*
fn: tagPrint;
input: (map<string, int> &kewordsMap, vector<string>& color) ;
output: void
purpose: print kewords and color and number of frequency.
*/
void tagPrint(map<string, int> &kewordsMap, vector<string>& color)
{
	int index = 0;
	for (auto s : kewordsMap)
	{
		cout << "	# " << s.first << " (" << color[index++] << ") = " << s.second << endl;
	}
}
/*
* Name: DONG KI, SIN
* Date: Mar, 27, 2023
* Purpose: holds structs, function, declaration
*/

#include<string>
#include<fstream>
#include <iostream>
#include<vector>
#include<map>
using namespace std;


void helpPrint();

void reportTrue(vector<string> & newWords, int &paraCnt, int &lineCnt, int& totalTag);

void paragraphTrue(vector<string>& newWords);

void tagPrint(map<string, int>& kewordsMap, vector<string>& color);
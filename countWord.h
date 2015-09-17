//
// Created by yueg on 8/22/15.
//

#ifndef FINDWORD_COUNTWORD_H
#define FINDWORD_COUNTWORD_H
#include <map>
#include <string>
#include <vector>
using namespace std;
map<string, int> getTermsMapFromVec(vector<string> vec);
vector<string> getTermsFromFile(const char *termsTableFileName, const char *inputFileName);
vector<string> getTermsFromStr(const char *termsTableFileName, string str);
map<string, int> getMultiTermsMap(vector<vector<string>> ts);

#endif //FINDWORD_COUNTWORD_H

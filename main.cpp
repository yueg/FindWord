#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "searchTerm.h"
#include "tl_codetbl.h"
#include "Utility.h"
#include "countWord.h"
#include "fileOperation.h"

using namespace std;
using namespace encoding;


int main(int argc, char **argv) {
    vector<string> termsVec1 =getTermsFromFile("/home/yueg/innotree/FindWord/business.seg", "/home/yueg/innotree/FindWord/input01.seg");
    vector<string> termsVec2 =getTermsFromFile("/home/yueg/innotree/FindWord/business.seg", "/home/yueg/innotree/FindWord/input02.seg");
    vector<vector<string>> terms;
    terms.push_back(termsVec1);
    terms.push_back(termsVec2);
//    map<string, int> wordMap = getTermsMapFromVec(termsVec1);
    map<string, int> wordMap = getMultiTermsMap(terms);
    map<string, int>::iterator iter;
    for(iter = wordMap.begin(); iter != wordMap.end(); iter++)
    {
        string word = iter->first;
        const char *temp = word.c_str();
        char *w = (char *)malloc(word.size() * 2 + 1);
        conv_gbk_2_utf8(temp, word.size() * 2, w, word.size() * 2);
        cout << w <<"  " << iter->second << endl;
    }
    return 0;
}

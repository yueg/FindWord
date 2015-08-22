//
// Created by yueg on 8/22/15.
//

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "countWord.h"
using namespace std;

map<string, int> getWordMapFromVec(vector<string> vec) {
    map<string, int> ret;
    for(int i = 0; i < vec.size(); i++) {
        string word = vec[i];
        map<string, int>::iterator iter = ret.find(word);
        if(iter == ret.end()) {
            ret.insert(make_pair(word, 1));
        }
        else {
            ret[word]++;
        }
    }
    return ret;
};

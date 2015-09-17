//
// Created by yueg on 8/22/15.
//

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "countWord.h"
#include "tl_codetbl.h"
#include "Utility.h"
#include "searchTerm.h"
using namespace std;
using namespace encoding;

/**
 * 从term列表文件和输入新闻内容获得term列表
 * @param const char *termsTableFileName
 * @param const char *inputFileName
 * @return vector<string> ret
 */
vector<string> getTermsFromFile(const char *termsTableFileName, const char *inputFileName) {
    void *wordDic = LoadDicFromFile(termsTableFileName);
    vector<string> ret;
    FILE *fp = fopen(inputFileName, "r");
    if(NULL == fp) {
        fprintf(stderr, "open input file error:%s\n", inputFileName);
        return ret;
    }
    char *s = (char *)malloc(2048);
    while(fgets(s, 2048, fp)) {
        vector<string> temp;
        searchLongTerms(wordDic, s, temp, 100);
        ret.insert(ret.end(), temp.begin(), temp.end());
    }
    UnloadDic(wordDic);
    fclose(fp);
    return ret;
}

/**
 * 从term列表文件和输入新闻内容获得term列表
 * @param const char *termsTableFileName
 * @param const char *inputFileName
 * @return vector<string> ret
 */
vector<string> getTermsFromStr(const char *termsTableFileName, string str) {
    void *wordDic = LoadDicFromFile(termsTableFileName);
    vector<string> ret;
    searchLongTerms(wordDic, str.c_str(), ret, 100);
    UnloadDic(wordDic);
    return ret;
}

/**
 * 统计单个新闻中的term数量到map中
 * @param vector<string> vec
 * @return map<string, int> ret
 */
map<string, int> getTermsMapFromVec(vector<string> vec) {
    map<string, int> ret;
    for(int i = 0; i < vec.size(); i++) {
        const char *temp1 = vec[i].c_str();
        char *temp2 = (char *)malloc(vec[i].size() + 1);
        sbc2dbc(temp1, temp2, vec[i].size());
        string word(temp2);
        map<string, int>::iterator iter = ret.find(word);
        if(iter == ret.end()) {
            ret.insert(make_pair(word, 1));
        }
        else{
            ret[word]++;
        }
    }
    return ret;
};

/**
 * 获得每个term出现的新闻次数
 */
map<string, int> getMultiTermsMap(vector<vector<string>> ts) {
    map<string, int> ret;
    for(int i = 0; i < ts.size(); i++) {
        map<string, int> mapTemp;
        map<string, int>::iterator iter;
        for(int j = 0; j < ts[i].size(); j++) {
            string word = ts[i][j];
            iter = mapTemp.find(word);
            if(iter == mapTemp.end()) {
                mapTemp.insert(make_pair(word, 1));
            }
        }
        for(iter = mapTemp.begin(); iter != mapTemp.end(); iter++) {
            string word = iter->first;
            map<string, int>::iterator it = ret.find(word);
            if(it == ret.end()) {
                ret.insert(make_pair(word, 1));
            }
            else {
                ret[word]++;
            }
        }
    }
    return ret;
}




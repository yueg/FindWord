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
using namespace std;
using namespace encoding;

bool writeRes2File(const char *filename, string str) {
    FILE *fp = fopen(filename, "w");
    if(NULL == fp) {
        fprintf(stderr, "open result file error:%s\n", filename);
        return false;
    }
    int stringLen = str.size();
    int count = fwrite(str.c_str(), stringLen, sizeof(char), fp);
    fclose(fp);
}

char * readInputFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if(NULL == fp) {
        fprintf(stderr, "open input file error:%s\n", filename);
        return NULL;
    }
    fseek(fp,0L,SEEK_END);
    int flen = ftell(fp);
    cout << flen << endl;
    char *str = (char *)malloc(flen+1);
    fseek(fp,0L,SEEK_SET);
    fread(str,flen,1,fp);
    str[flen]=0;
    return str;
}

vector<string> getWordsFromFile(const char *filename) {
    void *wordDic = LoadDicFromFile("/home/yueg/innotree/FindWord/business.seg");
    vector<string> ret;
    FILE *fp = fopen(filename, "r");
    if(NULL == fp) {
        fprintf(stderr, "open input file error:%s\n", filename);
        return ret;
    }
    char *s;
    while(fgets(s, 2048, fp)) {
        vector<string> temp;
        searchLongTerms(wordDic, s, temp, 100);
        ret.insert(ret.end(), temp.begin(), temp.end());
    }
    return ret;
}


int main(int argc, char **argv) {
//    void *wordDic = LoadDicFromFile("/home/yueg/innotree/FindWord/business.seg");
//    char *inputString = readInputFromFile("/home/yueg/innotree/FindWord/input.seg");
//    vector<string> wordVec;
//    bool ret = searchLongTerms(wordDic, inputString, wordVec, 100);
    vector<string> wordVec = getWordsFromFile("/home/yueg/innotree/FindWord/input01.seg");
    string str;
    for(int i = 0; i < wordVec.size(); i++)
    {
        const char *str1 = wordVec[i].c_str();
        char *str2 = (char *)malloc(wordVec[i].size());
        int count = sbc2dbc(str1, str2, wordVec[i].size());
        string str3(str2);
        str += str3 + "\n";
    }
    map<string, int> wordMap = getWordMapFromVec(wordVec);
    map<string, int>::iterator iter;
    for(iter = wordMap.begin(); iter != wordMap.end(); iter++)
    {
        string word = iter->first;
        const char *temp = word.c_str();
        char *w = (char *)malloc(word.size() * 2 + 1);
        conv_gbk_2_utf8(temp, word.size() * 2, w, word.size() * 2);
        cout << w <<"  " << iter->second << endl;
    }
    bool write2FileRet = writeRes2File("/home/yueg/innotree/FindWord/ret.seg", str);
    return 0;
}

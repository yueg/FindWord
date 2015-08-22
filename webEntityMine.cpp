//============================================================================
// Name        : webEntityMine.cpp
// Author      : beck
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "searchTerm.h"
using namespace std;
#define MAX_WORD_NUM  (65536*10)

string readdata(char *data)
{
	string cdata = data;
	unsigned int pos =  cdata.find("content");
	pos += 10;
	if(cdata.length() <= pos) return "";
	cdata = cdata.substr(pos, cdata.length()-pos);

	string content = "";
	while( cdata.length()>1){
		if( strncmp(cdata.c_str(),"{\"txt\"",6)!=0 ){
			break;
		}

		int pos = cdata.find(":",8);
		if(pos <0 ){
			break;
		}

		int clen = atoi(cdata.substr(8,pos).c_str());
		//printf("tag=2,pos=%d,clen=%d,cdata[%d]:%s\n",pos,clen,cdata.length(),cdata.c_str());
		string text = cdata.substr(pos+1, clen);
		//printf("clen=%d\ttext=%s\t",clen,text.c_str());

		const char* ptr = cdata.c_str()+pos+1+clen;
		string tag = "";
		if(strncmp(ptr,"\',\"tag",5)==0) {
			int epos = cdata.find("\"}",pos+1+clen+9);
			tag = cdata.substr(pos+1+clen+9, epos -pos-1-clen-9);
			//printf("tag3=%s\n", tag.c_str());

			cdata = cdata.substr(epos+3, cdata.length()-epos -3);
		}else{
			int epos = pos+1+clen;
			//printf("\ntag=6:pos=%d,clen=%d,epos:%d,cdatalen:%d\n",pos,clen,epos,cdata.length() );
			cdata = cdata.substr(epos+3, cdata.length()-epos -3);
		}
		if( strcmp(tag.c_str(), "description")!=0 && strcmp(tag.c_str(), "keywords")!=0 && strcmp(tag.c_str(), "imgalt")!=0
				&& strcmp(tag.c_str(), "crumb")!=0){
			content += text;
		}
		//printf("\n");
	}
	//printf("content:%s\n",content.c_str());

	return content;
}

int main(int argc, char **argv) {
	setbuf(stdout, NULL);
	FILE *fp = NULL;
	/*if (argc > 1) {
		fp = fopen(argv[1], "r");
	} else {
		fp = stdin;
	}*/
	fp = stdin;

	bool needParse = false;
	if(argc>1){
		if(strcmp(argv[1], "-n") == 0 ){
			needParse = true;
		}
	}

	void * dicHandle = LoadDicFromFile("entity.txt");

	//text
	/*std::vector<std::string> termsResult;
	//bool bfind = searchTerms(dicHandle, "新笑傲江湖，女相，搜神记,流星雨3，步步惊心2，杜拉拉2，爱情公寓4，花非花雾非雾，天使的幸福，爱情正美味，转身说爱你，胜女的时代", termsResult);
	bool bfind = searchTerms(dicHandle,"▪ 大明王朝1566 ( 2006)▪ 大宅门 ( 2001)",termsResult);
	printf("\n1b=%d, size=%d\n",bfind, termsResult.size());
	for(unsigned int i=0; i< termsResult.size(); i++){

		printf("%d=%s\n",i, termsResult.at(i).c_str());
	}

	std::map<std::string,int> m_allbooks; //gbk
	searchLongTerms(dicHandle,"▪ 大明王朝1566 ( 2006)▪ 大宅门 ( 2001)",	termsResult,m_allbooks);
	printf("\n2b=%d, size=%d\n", bfind, termsResult.size());
	for (unsigned int i = 0; i < termsResult.size(); i++) {

		printf("%d=%s\n", i, termsResult.at(i).c_str());
	}*/

	char buf[MAX_WORD_NUM];
	while (fgets(buf, MAX_WORD_NUM, fp)) {
		int n = strlen(buf);
		while (n > 0 && isspace(buf[n - 1])) {
			buf[--n] = '\0';
		}
		if (n < 1)	continue;

		char *ptr = strtok(buf, "\t");
		if(NULL == ptr)  continue;
		string url = ptr;
		ptr = strtok(NULL,"\t");
		if(NULL == ptr)  continue;
		string title = ptr;
		ptr = strtok(NULL,"\t");
		if(NULL == ptr)  continue;
		string content = ptr;
		if(needParse) {
			content = readdata(ptr);
		}

		char output[6536];
		int outlength = 6536;
		bool bmine = webEntityMine(dicHandle, title.c_str(),title.length(), content.c_str(), content.length(), output, outlength);

		if(bmine){
			printf("%s\t%s\t%s\n", url.c_str(),title.c_str(),  output);
		}
	}
	fclose(fp);
	UnloadDic(dicHandle);



	return 0;
}

#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<list>
using namespace std;
#define NAMESIZE 20
#define MAX 1000
struct Node {
	int level;
	vector<int>kids;
}nd[MAX];
char nametable[MAX][NAMESIZE] = { 0 };
int cnt = 0;
Node* root = NULL;
int getid(char name[]) {//获?取?名?字?对?应畖的?id 
	int id = -1;
	for (int i = 0; i < cnt; ++i) {
		if (strcmp(name, nametable[i]) == 0) {
			id = i;
		}
	}
	return id;
}
void build() {//从洙?文?件t中D载?入?家ò谱×树骸? 文?件t格?式?：阰当獭?前°人?姓?名? 第台?几?代洙?孩￠子哩?个?数簓 孩￠子哩甶名?字? 
	FILE* fp;
	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("家ò谱×文?件t不?存?在ú\n");
	}
	else {
		char name[NAMESIZE];
		int num, par;
		while (!feof(fp)) {
			fscanf(fp, "%s", &name);
			int id = getid(name);
			if (id == -1) {
				strcpy(nametable[cnt], name);
				id = cnt++;
			}
			par = id;
			fscanf(fp, "%d", &nd[par].level);
			fscanf(fp, "%d", &num);
			for (int i = 0; i < num; ++i) {
				fscanf(fp, "%s", name);
				id = getid(name);
				if (id == -1) {
					strcpy(nametable[cnt], name);
					id = cnt++;
				}
				nd[par].kids.push_back(id);
			}
		}
		fclose(fp);
	}
}
bool checkbro(int id1, int id2) {//检ì查é二t人?是?否?为a兄?弟台?姐?妹? 
	for (int i = 0; i < cnt; ++i) {
		bool flag1 = 0, flag2 = 0;
		for (int j = 0; j < nd[i].kids.size(); ++j) {
			if (nd[i].kids[j] == id1)flag1 = 1;
			if (nd[i].kids[j] == id2)flag2 = 1;
		}
		if (flag1 && flag2)return 1;
	}
	return 0;
}
bool checklov(int id1, int id2) {//检ì查é二t人?是?否?为a夫え?妻T 
	if (nd[id1].kids.size() != 0 && nd[id1].kids.size() == nd[id1].kids.size()) {
		for (int i = 0; i < nd[id1].kids.size(); ++i) {
			if (nd[id1].kids[i] != nd[id2].kids[i])return 0;
		}
		return 1;
	}
	else return 0;
}
bool checkson(int id1, int id2) {//检ì查é是?否?为a父?子哩?关?系μ 
	for (int i = 0; i < nd[id1].kids.size(); ++i) {
		if (nd[id1].kids[i] == id2)return 1;
	}
	return 0;
}
void relation(char name1[], char name2[]) {//计?算?两?人?关?系μ 
	int id1 = getid(name1), id2 = getid(name2);
	if (id1 == -1)printf("%s不?存?在ú\n", name1);
	if (id2 == -1)printf("%s不?存?在ú\n", name2);
	if (id1 == -1 || id2 == -1)return;
	if (nd[id1].level == nd[id2].level) {
		if (checkbro(id1, id2)) {
			printf("%s与?%s为a兄?弟台?姐?妹?\n", name1, name2);
		}
		else if (checklov(id1, id2)) {
			printf("%s与?%s为a夫え?妻T\n", name1, name2);
		}
		else {
			printf("%s与?%s同?辈?但?非?直±系μ兄?弟台?姐?妹?以?及°夫え?妻T\n", name1, name2);
		}
	}
	else {
		if (nd[id1].level > nd[id2].level) {
			if (checkson(id2, id1))printf("%s是?%s的?父?母?\n", name2, name1);
			else printf("%s是?%s大洙?d辈?的?长¤辈?\n", name2, name1, nd[id1].level - nd[id2].level);
		}
		else {
			if (checkson(id1, id2))printf("%s是?%s的?父?母?\n", name1, name2);
			else printf("%s是?%s大洙?d辈?的?长¤辈?\n", name1, name2, nd[id2].level - nd[id1].level);
		}
	}
}
void print() {//输?出?全?部?家ò谱×树骸?信?息￠ 
	for (int i = 0; i < cnt; ++i) {
		printf("姓?名?：阰%s 第台?d代洙?", nametable[i], nd[i].level);
		if (nd[i].kids.size() == 0)printf("无T子哩?嗣?\n");
		else {
			printf("孩￠子哩?：阰");
			for (int j = 0; j < nd[i].kids.size(); ++j) {
				printf("%s ", nametable[nd[i].kids[j]]);
			}
			printf("\n");
		}
	}
}
void menu() {
	printf("*****************************\n");
	printf("*******1 计?算?成é员±关?系μ********\n");
	printf("*******2 输?出?家ò谱×树骸? ********\n");
	printf("*******3 退?出?        ********\n");
	printf("*****************************\n");
	printf("请?选?择?功|能ü：阰");
}
void cal() {
	char name1[NAMESIZE], name2[NAMESIZE];
	printf("请?输?入?需è计?算?关?系μ的?两?个?家ò庭?成é员±姓?名?：阰");
	scanf("%s%s", name1, name2);
	relation(name1, name2);
}
int main(void) {
	build();
	menu();
	char ch;
	while (1) {
		ch = getchar();
		if (ch == '1') {
			cal();
			menu();
		}
		else if (ch == '2') {
			print();
			menu();
		}
		else if (ch == '3')break;
	}
	return 0;
}
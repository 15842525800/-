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
int getid(char name[]) {//��?ȡ?��?��?��?Ӧ�|��?id 
	int id = -1;
	for (int i = 0; i < cnt; ++i) {
		if (strcmp(name, nametable[i]) == 0) {
			id = i;
		}
	}
	return id;
}
void build() {//���?��?��t��D��?��?�Ҩ��ס�����? ��?��t��?ʽ?���o��̡?ǰ����?��?��? ��̨?��?���?��������?��?���y ���������i��?��? 
	FILE* fp;
	fp = fopen("data.txt", "r");
	if (!fp) {
		printf("�Ҩ��ס���?��t��?��?�ڨ�\n");
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
bool checkbro(int id1, int id2) {//�쨬�騦��t��?��?��?Ϊa��?��̨?��?��? 
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
bool checklov(int id1, int id2) {//�쨬�騦��t��?��?��?Ϊa��?��T 
	if (nd[id1].kids.size() != 0 && nd[id1].kids.size() == nd[id1].kids.size()) {
		for (int i = 0; i < nd[id1].kids.size(); ++i) {
			if (nd[id1].kids[i] != nd[id2].kids[i])return 0;
		}
		return 1;
	}
	else return 0;
}
bool checkson(int id1, int id2) {//�쨬�騦��?��?Ϊa��?����?��?ϵ�� 
	for (int i = 0; i < nd[id1].kids.size(); ++i) {
		if (nd[id1].kids[i] == id2)return 1;
	}
	return 0;
}
void relation(char name1[], char name2[]) {//��?��?��?��?��?ϵ�� 
	int id1 = getid(name1), id2 = getid(name2);
	if (id1 == -1)printf("%s��?��?�ڨ�\n", name1);
	if (id2 == -1)printf("%s��?��?�ڨ�\n", name2);
	if (id1 == -1 || id2 == -1)return;
	if (nd[id1].level == nd[id2].level) {
		if (checkbro(id1, id2)) {
			printf("%s��?%sΪa��?��̨?��?��?\n", name1, name2);
		}
		else if (checklov(id1, id2)) {
			printf("%s��?%sΪa��?��T\n", name1, name2);
		}
		else {
			printf("%s��?%sͬ?��?��?��?ֱ��ϵ����?��̨?��?��?��?�����?��T\n", name1, name2);
		}
	}
	else {
		if (nd[id1].level > nd[id2].level) {
			if (checkson(id2, id1))printf("%s��?%s��?��?ĸ?\n", name2, name1);
			else printf("%s��?%s���?d��?��?���豲?\n", name2, name1, nd[id1].level - nd[id2].level);
		}
		else {
			if (checkson(id1, id2))printf("%s��?%s��?��?ĸ?\n", name1, name2);
			else printf("%s��?%s���?d��?��?���豲?\n", name1, name2, nd[id2].level - nd[id1].level);
		}
	}
}
void print() {//��?��?ȫ?��?�Ҩ��ס�����?��?Ϣ�� 
	for (int i = 0; i < cnt; ++i) {
		printf("��?��?���o%s ��̨?d���?", nametable[i], nd[i].level);
		if (nd[i].kids.size() == 0)printf("��T����?��?\n");
		else {
			printf("��������?���o");
			for (int j = 0; j < nd[i].kids.size(); ++j) {
				printf("%s ", nametable[nd[i].kids[j]]);
			}
			printf("\n");
		}
	}
}
void menu() {
	printf("*****************************\n");
	printf("*******1 ��?��?�ɨ�Ա����?ϵ��********\n");
	printf("*******2 ��?��?�Ҩ��ס�����? ********\n");
	printf("*******3 ��?��?        ********\n");
	printf("*****************************\n");
	printf("��?ѡ?��?��|�ܨ����o");
}
void cal() {
	char name1[NAMESIZE], name2[NAMESIZE];
	printf("��?��?��?�訨��?��?��?ϵ�̵�?��?��?�Ҩ�ͥ��?�ɨ�Ա����?��?���o");
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
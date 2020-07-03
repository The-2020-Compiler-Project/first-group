#ifndef COMPILE
#define COMPILE
#include<iostream>
#include<vector>
#include<set>
#include<string.h>
#include<fstream>
#include<map>
#include <iomanip>
#include<stack>
#include<string>
#include<fstream>
using namespace std;
set<string> keyword={"int","while","cin","cout","return","if","else","float","char","void","string"};//�ؼ��ʱ�
set<char> mark={'-','*','+','/','{','}',',',';','(',')','[',']'};//�����
set<string> mark1={"int","void","float","string","char"};
struct token
{
    char type;//����
    string value;//ֵ
};
vector<token> GT,CT,BT,JT,ST,cT;//�ؼ��ֱ� ������ ��ʶ���� ����� �ַ��� �ַ�

void  autoinit();
int  automaton(string strline, int i, vector<token> &token1);
void  dotoken();
char *filename;
vector<vector<token>> all;
int totalrow;//�ļ�������
int chart[18][256];//״̬ת�Ʊ�
void readin();
void Intersection(string &a,string b);
string Getf(int v,int & H0);
void Getfirst();
void Printfirst();
void Getfollow();
void Printfollow();
void Gettable();
string Getp(int i);
void PrintT();

map<string,int> Getnu;//�ñ�ż�¼ÿ�����ս�����ս��
string Getch[100];//��Ŷ�Ӧ�ķ��ս�����ս��
vector<string> Process;//��������ʽ��ϣ�����A->bAc�洢ΪA bAc�ȶ�ȡ���ս�����ո�ֿ�������Ϊ���ʽ
vector<string> Production;//�洢ȥ���׵ķ��ս��
int table[100][100];//������
int num=0;//�ս�����Ϸ��ս��������
int numvt=0; //�ս���ͷ��ս���ֽ�㣬�ı�ű�ʾ���ǿգ���@��ʾ
string first[100];
string follow[200];
string word;
vector<string> process1;

struct fourarray
{
    token name1,name2,name3,name4;//��Ԫʽ
};
vector<fourarray> chararray;//�����Ԫʽ����
stack<token> backtoken,optstack;//    ������ջ
stack<string> optcharstack,semantictoken;//������ջ ����ջ
int nowuse=0;

int level=0;
struct charttype//������ͺ�λ��
{
    char type;//����
    int point;//λ��
};
struct mainchart//����
{
    string name;//����
    string type;//����
    string cat;//
    charttype address;//��ַ
    int length;
};
mainchart mainchart1[100];

struct funcchart//������
{
    int level;//���
    int off;//���
    int fn;//��������
    mainchart para[5];//���
    int length;
};
funcchart funcchart1[5];
struct vall//���¼
{
    string name;//����
    string type;//��ʶ������
    int low;
    int up;
    int length;
};

struct typechart//���ͱ�
{
    char type;//�������͹̶�Ϊ��a'
    int a[3];//��ʼ ��ֹ  ÿһ���Ĵ�С
    char type1;//ÿ�����ݵ�����
};
vector<int> length;
vector<typechart> typechart1;
vall vall1[100];

#endif
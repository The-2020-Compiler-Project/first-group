#ifndef COMPILE
#define COMPILE
#include<iostream>
#include<vector>
#include<set>
#include<string.h>
#include<fstream>
#include<map>
#include<iomanip>
#include<stack>
#include<string>
#include<fstream>
#include<stdlib.h>
using namespace std;
set<string> keyword={"int","while","cin","cout","return","if","else","float","char","void","string","struct"};//关键词表
set<char> mark={'-','*','+','/','{','}',',',';','(',')','[',']'};//界符表
set<string> mark1={"int","void","float","string","char"};
struct token
{
    char type;//类型
    string value;//值
};
vector<token> GT,CT,BT,JT,ST,cT;//关键字表 常数表 标识符表 界符表 字符串 字符

void  autoinit();
int  automaton(string strline, int i, vector<token> &token1);
void  dotoken();
char *filename;
vector<vector<token>> all;
int totalrow;//文件的行数
int chart[18][256];//状态转移表
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
void targetcode(); // 目标代码生成

map<string,int> Getnu;//用标号记录每个非终结符和终结符
string Getch[100];//标号对应的非终结符和终结符
vector<string> Process;//单个生成式组合，例如A->bAc存储为A bAc先读取非终结符，空格分开，后面为表达式
vector<string> Production;//存储去掉首的非终结符
int table[100][100];//分析表
int num=0;//终结符加上非终结符的数量
int numvt=0; //终结符和非终结符分界点，改标号表示的是空，用@表示
string first[100];
string follow[200];
string word;
vector<string> process1;

struct fourarray
{
    token name1,name2,name3,name4;//四元式
};
vector<fourarray> chararray,newchararrray;//存放四元式序列
stack<token> backtoken,optstack;//    操作数栈
stack<string> optcharstack,semantictoken;//操作符栈 语义栈
int nowuse=0;

int level=0;
struct charttype//表格类型和位置
{
    char type;//类型
    int point;//位置
};
struct mainchart//主表
{
    string name;//名字
    string type;//类型
    string cat;//
    charttype address;//地址
    int length;
};
mainchart mainchart1[100];

struct funcchart//函数表
{
    int level;//层次
    int off;//入口
    int fn;//参数个数
    mainchart para[5];//入口
    int length;
};
funcchart funcchart1[5];
struct vall//活动记录
{
    string name;//名字
    string type;//标识符名字
    int low;
    int up;
    int length;
};

struct typechart//类型表
{
    char type;//数组类型固定为‘a'
    charttype address;
};
struct numchart//数组表
{
    int low,up;//起始和终止
    char type;//类型
    int size;//每一个单元格的大小
};
struct structchart//结构体表
{
    string name;//名字
    int off;//距离开始位置
    char type;//类型
};
vector<numchart> numchart1;
vector<structchart> structchart1;
vector<int> length;

vector<typechart> typechart1;
vall vall1[100];

set<string> mark2={"+","-","*","/",">=","==","<=",">","<"};
struct newfour
{
    vector<string> idenchar;//副标识符 
    int node,parent;//图
    vector<int> children;
    token fuhao;//主标识符
    string nihao;//运算符号
};
vector<newfour> newfour1;
vector<fourarray> inoutfour;
set<string>     mark4={"if","else","do","while","end"};

#endif
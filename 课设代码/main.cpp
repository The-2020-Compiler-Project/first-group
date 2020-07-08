#include "compile.h"

void autoinit()
{
    for (int hh = 0; hh < 18; hh++) //状态转移方程初始化
    {
        for (int kk = 0; kk < 256; kk++)
            chart[hh][kk] = 0;
    }
    for (int hh = 65; hh <= 90; hh++)
    {
        chart[1][hh] = 2;
        chart[2][hh] = 2;
    }
    for (int hh = 97; hh <= 122; hh++)
    {
        chart[1][hh] = 2;
        chart[2][hh] = 2;
    }
    for (int hh = 48; hh <= 57; hh++)
    {
        chart[1][hh] = 3;
        chart[2][hh] = 2;
        chart[3][hh] = 3;
        chart[4][hh] = 5;
        chart[5][hh] = 5;
    }
    chart[3][46] = 4;
    chart[1]['<'] = 6;
    chart[6]['<'] = 7;
    chart[1]['>'] = 8;
    chart[8]['>'] = 9;
    chart[1]['/'] = 10;
    chart[10]['/'] = 11;
    chart[6]['='] = 12;
    chart[8]['='] = 13;
    chart[1]['='] = 14;
    chart[14]['='] = 15;
}
int judgeB(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (BT[i].value == str)
            return 1;
    }
    return 0;
}
int automaton(string strline, int i, vector<token> &token1)
{
    string strline1 = "";
    int kk1 = 1, kk2 = 1, j;
    for (j = i; i < strline.size(); j++)
    {
        kk1 = kk2;
        kk2 = chart[kk1][strline[j]];
        if (kk2 == 0)
            break;
        strline1 += strline[j];
    }
    switch (kk1)
    {
    case 2:
    {
        if (keyword.find(strline1) != keyword.end())
        {
            token token2;
            token2.type = 'G';
            token2.value = strline1;
            token1.push_back(token2);
            GT.push_back(token2);
        }
        else
        {
            token token2;
            token2.type = 'B';
            token2.value = strline1;
            token1.push_back(token2);
            BT.push_back(token2);
        }
        break;
    }
    case 3:
    {
        token token2;
        token2.type = 'C';
        token2.value = strline1;
        token1.push_back(token2);
        CT.push_back(token2);
        break;
    }
    case 5:
    {
        token token2;
        token2.type = 'C';
        token2.value = strline1;
        token1.push_back(token2);
        CT.push_back(token2);
        break;
    }
    case 6:
    {
        token token2;
        token2.type = 'J';
        token2.value = strline1;
        token1.push_back(token2);
        JT.push_back(token2);
        break;
    }
    case 7:
    {
        token token2;
        token2.type = 'J';
        token2.value = strline1;
        token1.push_back(token2);
        JT.push_back(token2);
        break;
    }
    case 8:
    {
        token token2;
        token2.type = 'J';
        token2.value = strline1;
        token1.push_back(token2);
        JT.push_back(token2);
        break;
    }
    case 9:
    {
        token token2;
        token2.type = 'J';
        token2.value = strline1;
        token1.push_back(token2);
        JT.push_back(token2);
        break;
    }
    case 11:
    {
        j = strline.size();
        break;
    }
    case 12:
    {
        token token2;
        token2.type = 'J';
        token2.value = strline1;
        token1.push_back(token2);
        break;
    }
    case 13:
    {
        token token2;
        token2.type = 'J';
        token2.value = strline1;
        token1.push_back(token2);
        JT.push_back(token2);
        break;
    }
    case 14:
    {
        token token2;
        token2.type = 'J';
        token2.value = strline1;
        token1.push_back(token2);
        JT.push_back(token2);
        break;
    }
    case 15:
    {
        token token2;
        token2.type = 'J';
        token2.value = strline1;
        token1.push_back(token2);
        JT.push_back(token2);
        break;
    }
    default: //其余态报错
    {
        cout << "出现错误";
    }
    }
    j--;
    return j;
}
void dotoken(char *filename)
{
    totalrow = 0;
    ifstream file;
    file.open(filename, ios::in);
    if (!file.is_open())
        return;
    string strline;
    while (getline(file, strline))
    {
        totalrow++;
        cout << strline << endl;
        vector<token> token1; //包含整行的token
        int i;
        strline += '@';
        for (i = 0; i < strline.size(); i++)
        {
            if (strline[i] == ' ')
                continue;
            else if (strline[i] == '#')
                break;
            else if (strline[i] == '@')
                break;
            else if (strline[i] == '\'')
            {
                i++;
                token token2; //某个token
                token2.type = 'c';
                token2.value = strline[i];
                token1.push_back(token2);
                cT.push_back(token2);
                i++;
                if (strline[i] != '\'')
                    cout << "error";
            }
            else if (strline[i] == '\"')
            {
                i++;
                int k;
                string strline2 = "";
                for (k = i; k < strline.size(); k++)
                {
                    if (strline[k] == '\"')
                        break;
                    else if (strline[k] == '@')
                    {
                        cout << "error";
                        break;
                    }
                    else
                    {
                        strline2 += strline[k];
                    }
                }
                i = k;
                token token2; //某个token
                token2.type = 'S';
                token2.value = strline2;
                token1.push_back(token2);
                ST.push_back(token2);
            }
            else if (mark.find(strline[i]) != mark.end())
            {
                token token2; //某个token
                token2.type = 'J';
                token2.value = strline[i];
                token1.push_back(token2);
                JT.push_back(token2);
            }
            else
            {
                int j = automaton(strline, i, token1);
                i = j;
            }
        }
        all.push_back(token1);
    }
    file.close();
}
void readin()
{
    memset(table, -1, sizeof(table));
    Getnu["#"] = 0;
    Getch[0] = "#";
    ifstream fp;
    fp.open("zhongjie.txt");
    if (!fp.is_open())
    {
        cout << "error" << endl;
        return;
    }
    string x;
    do
    {
        fp >> x;
        Getnu[x] = ++num;
        Getch[num] = x;
    } while (!fp.eof());
    fp.close();
    numvt = ++num;
    Getnu["@"] = numvt;
    Getch[num] = ("@");
    fp.open("nozhongjie.txt");
    if (!fp.is_open())
    {
        cout << "error" << endl;
        return;
    }
    do
    {
        fp >> x;
        Getnu[x] = ++num;
        Getch[num] = x;
    } while (!fp.eof());
    fp.close();
    fp.open("chanshengshi.txt");
    if (!fp.is_open())
    {
        cout << "error" << endl;
        return;
    }
    string pro, head, ss, dd; //head为开头非终结符(单词)，pro为表达式的一个单词，ss为整个表达式，表达式由|分开
    ss.clear();
    dd.clear();
    while (fp >> head && head != "end") //读取开头的非终结符(单词)连带后面的多个产生式
    {
        dd.clear();
        ss = head;
        fp >> pro; //除去->
        do
        {
            fp >> pro;
            if (pro == "|")
            {
                Process.push_back(ss);
                Production.push_back(dd);
                dd.clear();
                ss.clear();
                ss = head;
            }
            else
            {
                ss = ss + " " + pro;
                if (dd == "")
                    dd += pro;
                else
                    dd = dd + " " + pro;
            }
        } while (fp.peek() != '\n');
        Production.push_back(dd);
        Process.push_back(ss);
    }
}

string Gainfirst(string sb) //获取process的非终结符首
{
    string ss;
    int i = 0;
    while (sb[i] != ' ')
    {
        ss += sb[i];
        i++;
    }
    return ss;
}

string Gainsecond(string sb) //获取process的右式首词
{
    string ss;
    int i = 0;
    while (sb[i++] != ' ')
    {
    }
    while (sb[i] != ' ' && i < sb.size())
    {
        ss += sb[i];
        i++;
    }
    return ss;
}

void Intersection(string &a, string b) //取a,b交集赋值给a
{
    set<char> SETE;
    for (int i = 0; i < a.size(); i++)
        SETE.insert(a[i]);
    for (int i = 0; i < b.size(); i++)
        SETE.insert(b[i]);
    string SS;
    set<char>::iterator I;
    for (I = SETE.begin(); I != SETE.end(); I++)
        SS += *I;
    a = SS;
}

string Getf(int v, int &H0) //求first集时首尾情况考虑
{
    if (v == numvt)
    {
        H0 = 1;
    }
    if (v < numvt)
        return first[v];
    string SS;
    for (int i = 0; i < Process.size(); i++)
    {
        if (Getnu[Gainfirst(Process[i])] == v)
        {
            string Second;
            int t = 0;
            while (Process[i][t] != ' ')
                ++t;
            ++t;
            while (Process[i][t] != ' ' && t != Process[i].size())
            {
                Second += Process[i][t];
                ++t;
            }
            SS += Getf(Getnu[Second], H0);
        }
    }
    return SS;
}

void Getfirst() //得到first集
{
    for (int i = 1; i <= numvt; i++)
    {
        first[i] += ('0' + i); //非终结符事先加上‘0’的ascii码
    }
    for (int j = 0; j < Process.size(); j++)
    {
        int k = 0;
        int H0 = 0;
        while (Process[j][k] != ' ')
            k++; //跳过第一个终结符记录
        do
        {
            H0 = 0;
            k++;
            if (k >= Process[j].size())
            {
                first[Getnu[Gainfirst(Process[j])]] += ('0' + numvt);
                break;
            }
            string ss;
            while (Process[j][k] != ' ')
            {
                ss += Process[j][k];
                k++;
                if (k >= Process[j].size())
                {
                    Intersection(first[Getnu[Gainfirst(Process[j])]], Getf(Getnu[ss], H0));
                    break;
                }
            }
            Intersection(first[Getnu[Gainfirst(Process[j])]], Getf(Getnu[ss], H0));
            ss.clear();
        } while (H0);
    }
}

void Printfirst() //打印first集
{
    cout << "first集:" << endl;
    for (int i = 1; i <= num; i++)
    {
        cout << "first [" << Getch[i] << "]: ";
        for (int j = 0; j < first[i].size(); j++)
            cout << Getch[first[i][j] - '0'] << " ";
        cout << endl;
    }
    cout << endl;
}

void Getfollow() //得到follow集
{
    Intersection(follow[Getnu[Gainfirst(Process[0])]], "0"); //首个加入#
    for (int j = 0; j < Process.size(); j++)
    {
        int jj = 0;
        while (Process[j][jj++] != ' ')
        {
        } //跳过左式终结符
        for (; jj < Process[j].size(); jj++)
        {
            string ss, hehe;
            while (Process[j][jj] != ' ' && jj < Process[j].size())
            {
                ss += Process[j][jj];
                jj++;
            }
            if (Getnu[ss] <= numvt)
            {
                ss.clear();
                continue;
            }
            int k = jj;
            int H0;
            do
            {
                hehe.clear();
                H0 = 0;
                k++;
                if (k >= Process[j].size())
                {
                    Intersection(follow[Getnu[ss]], follow[Getnu[Gainfirst(Process[j])]]);
                    break;
                }
                while (Process[j][k] != ' ')
                {
                    hehe += Process[j][k];
                    k++;
                    if (k >= Process[j].size())
                    {
                        break;
                    }
                }
                Intersection(follow[Getnu[ss]], Getf(Getnu[hehe], H0));
            } while (H0);
        }
    }
}

void Printfollow() //打印follow集
{
    cout << "follow集：" << endl;
    for (int i = numvt + 1; i <= num; i++)
    {
        cout << "follow [" << Getch[i] << "]: ";
        for (int j = 0; j < follow[i].size(); j++)
            cout << Getch[follow[i][j] - '0'] << " ";
        cout << endl;
    }
    cout << endl;
}

void Gettable()
{
    for (int i = 0; i < Process.size(); i++)
    {
        if (Gainsecond(Process[i]) == "@")
        {
            string Follow = follow[Getnu[Gainfirst(Process[i])]];
            for (int k = 0; k < Follow.size(); k++)
            {
                table[Getnu[Gainfirst(Process[i])]][Follow[k] - '0'] = i;
            }
        }
        string temp = first[Getnu[Gainsecond(Process[i])]];
        for (int j = 0; j < temp.size(); j++)
        {
            if (temp[j] != (numvt + '0'))
            {
                table[Getnu[Gainfirst(Process[i])]][temp[j] - '0'] = i;
            }
            else
            {
                string Follow = follow[Getnu[Gainsecond(Process[i])]];
                for (int k = 0; k < Follow.size(); k++)
                {
                    table[Getnu[Gainfirst(Process[i])]][Follow[k] - '0'] = i;
                }
            }
        }
    }
}

string Getp(int i)
{
    string ss;
    ss = to_string(i);
    return ss;
}

void PrintT()
{
    cout << "预测分析表：" << endl;
    string ss;
    int t;
    cout << left << setw(12) << " ";
    for (int i = 0; i < numvt; i++)
    {
        ss = Getch[i];
        t = ss.size();
        cout << left << setw(t + 2) << ss;
    }
    cout << endl;
    for (int i = numvt + 1; i <= num; i++)
    {
        cout << left << setw(12) << Getch[i];
        for (int j = 0; j < numvt; j++)
        {
            ss = Getch[j];
            t = ss.size();
            cout << left << setw(t + 2) << Getp(table[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}
void initProcess()
{
    ifstream file;
    char *filename = "chanshengshi1.txt";
    file.open(filename, ios::in);
    if (!file.is_open())
        return;
    string strline;
    while (getline(file, strline))
    {
        process1.push_back(strline);
    }
}
void createfour(char ch)
{
    if (ch == 'A')
    {
        optstack.push(backtoken.top());
    }
    else if (ch == 'B')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'J';
        fourarray1.name1.value = "*";
        token token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name3 = token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name2 = token2;
        fourarray1.name4.type = 'B';
        fourarray1.name4.value = "t" + to_string(nowuse);
        optstack.push(fourarray1.name4);
        nowuse++;
        chararray.push_back(fourarray1);
    }
    else if (ch == 'C')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'J';
        fourarray1.name1.value = "/";
        token token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name3 = token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name2 = token2;
        fourarray1.name4.type = 'B';
        fourarray1.name4.value = "t" + to_string(nowuse);
        optstack.push(fourarray1.name4);
        nowuse++;
        chararray.push_back(fourarray1);
    }
    else if (ch == 'D')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'J';
        fourarray1.name1.value = "+";
        token token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name3 = token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name2 = token2;
        fourarray1.name4.type = 'B';
        fourarray1.name4.value = "t" + to_string(nowuse);
        optstack.push(fourarray1.name4);
        nowuse++;
        chararray.push_back(fourarray1);
    }
    else if (ch == 'E')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'J';
        fourarray1.name1.value = "-";
        token token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name3 = token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name2 = token2;
        fourarray1.name4.type = 'B';
        fourarray1.name4.value = "t" + to_string(nowuse);
        optstack.push(fourarray1.name4);
        nowuse++;
        chararray.push_back(fourarray1);
    }
    else if (ch == 'F')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'J';
        fourarray1.name1.value = "=";
        token token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name2 = token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name4 = token2;
        fourarray1.name3.type = 'J';
        fourarray1.name3.value = "_";
        chararray.push_back(fourarray1);
    }
    else if (ch == 'G')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'G';
        fourarray1.name1.value = "if";
        token token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name2 = token2;
        fourarray1.name3.type = 'J';
        fourarray1.name3.value = "_";
        fourarray1.name4.type = 'J';
        fourarray1.name4.value = "_";
        chararray.push_back(fourarray1);
    }
    else if (ch == 'H')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'G';
        fourarray1.name1.value = "else";
        fourarray1.name2.type = 'J';
        fourarray1.name2.value = "_";
        fourarray1.name3.type = 'J';
        fourarray1.name3.value = "_";
        fourarray1.name4.type = 'J';
        fourarray1.name4.value = "_";
        chararray.push_back(fourarray1);
    }
    else if (ch == 'I')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'G';
        fourarray1.name1.value = "end";
        fourarray1.name2.type = 'J';
        fourarray1.name2.value = "_";
        fourarray1.name3.type = 'J';
        fourarray1.name3.value = "_";
        fourarray1.name4.type = 'J';
        fourarray1.name4.value = "_";
        chararray.push_back(fourarray1);
    }
    else if (ch == 'J')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'G';
        fourarray1.name1.value = "while";
        fourarray1.name2.type = 'J';
        fourarray1.name2.value = "_";
        fourarray1.name3.type = 'J';
        fourarray1.name3.value = "_";
        fourarray1.name4.type = 'J';
        fourarray1.name4.value = "_";
        chararray.push_back(fourarray1);
    }
    else if (ch == 'K')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'G';
        fourarray1.name1.value = "do";
        token token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name2 = token2;
        fourarray1.name3.type = 'J';
        fourarray1.name3.value = "_";
        fourarray1.name4.type = 'J';
        fourarray1.name4.value = "_";
        chararray.push_back(fourarray1);
    }
    else if (ch == 'L')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'G';
        fourarray1.name1.value = "end";
        fourarray1.name2.type = 'J';
        fourarray1.name2.value = "_";
        fourarray1.name3.type = 'J';
        fourarray1.name3.value = "_";
        fourarray1.name4.type = 'J';
        fourarray1.name4.value = "_";
        chararray.push_back(fourarray1);
    }
    else if (ch == 'M')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'G';
        fourarray1.name1.value = "cout";
        fourarray1.name2.type = 'J';
        fourarray1.name2.value = "_";
        fourarray1.name3.type = 'J';
        fourarray1.name3.value = "_";
        token token2;
        token2 = backtoken.top();
        fourarray1.name4 = token2;
        chararray.push_back(fourarray1);
    }
    else if (ch == 'N')
    {
        fourarray fourarray1;
        fourarray1.name1.type = 'G';
        fourarray1.name1.value = "cin";
        fourarray1.name2.type = 'J';
        fourarray1.name2.value = "_";
        fourarray1.name3.type = 'J';
        fourarray1.name3.value = "_";
        token token2;
        token2 = backtoken.top();
        fourarray1.name4 = token2;
        chararray.push_back(fourarray1);
    }
    else if (ch == 'O' || ch == 'P' || ch == 'Q' || ch == 'R' || ch == 'S')
    {
        optcharstack.push(backtoken.top().value);
    }
    else if (ch == 'T')
    {
        fourarray fourarray1;
        token token2;
        fourarray1.name1.value = optcharstack.top();
        optcharstack.pop();
        fourarray1.name1.type = 'J';
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name3 = token2;
        token2 = optstack.top();
        optstack.pop();
        fourarray1.name2 = token2;
        token2.type = 'B';
        token2.value = "t" + to_string(nowuse);
        nowuse++;
        fourarray1.name4 = token2;
        chararray.push_back(fourarray1);
        optstack.push(token2);
    }
}
void reseveread(string x)
{
    vector<string> nihao;
    string xx = "";
    for (int i = 0; i < x.size(); i++)
    {
        if (x[i] == ' ')
        {
            nihao.push_back(xx);
            xx = "";
        }
        else
        {
            xx = xx + x[i];
        }
    }
    nihao.push_back(xx);
    for (int i = nihao.size() - 1; i >= 0; i--)
    {
        semantictoken.push(nihao[i]);
    }
}
bool iszchar(string token2)
{
    if (token2[0] <= 'Z' && token2[0] >= 'A')
        return false;
    else
    {
        return true;
    }
}
string returntype(token token2)
{
    if (token2.type == 'B')
        return "id";
    else if (token2.type == 'C')
        return "number";
    else if (token2.type == 'c')
        return "ch";
    else if (token2.type == 'S')
        return "str";
    else
    {
        return token2.value;
    }
}
void printfour()
{
    for (int i = 0; i < chararray.size(); i++)
    {
        cout << left << setw(10) << chararray[i].name1.value << left << setw(10) << chararray[i].name2.value << left << setw(10) << chararray[i].name3.value << left << setw(10) << chararray[i].name4.value << endl;
    }
}
void semantic_analysis()
{
    semantictoken.push("Funcdef");
    token token2;
    token2.type = 'J';
    token2.value = "@";
    vector<token> ALL;
    for (int i = 0; i < all.size(); i++)
    {
        for (int j = 0; j < all[i].size(); j++)
        {
            ALL.push_back(all[i][j]);
        }
    }
    ALL.push_back(token2);
    int num = 0;
    while (num < ALL.size())
    {
        string str1;
        str1 = semantictoken.top();
        semantictoken.pop();
        cout << str1 << "  " << ALL[num].value << endl;
        if (str1.size() == 1 && str1[0] <= 'Z' && str1[0] >= 'A')
        {
            createfour(str1[0]);
        }
        else
        {
            if (iszchar(str1))
            {
                if (str1 == returntype(ALL[num]))
                {
                    backtoken.push(ALL[num]);
                    num++;
                }
                else
                {
                    cout << "错误";
                    system("pause");
                    return;
                }
            }
            else
            {
                int i = table[Getnu[str1]][Getnu[returntype(ALL[num])]];
                if (i == -1)
                {
                    cout << "错误";
                    system("pause");
                    return;
                }
                else
                {
                    if (process1[i] == "@")
                        continue;
                    reseveread(process1[i]);
                }
            }
            if (num == ALL.size() - 1)
            {
                break;
            }
        }
    }
}
bool isinout(fourarray jsd) //判断是否为输入输出语句
{
    if (jsd.name1.value == "cin" || jsd.name1.value == "cout")
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool iskeywords(fourarray jsd) //是否为if else或while语句
{
    if (mark4.find(jsd.name1.value) != mark4.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
void doequal(fourarray jsd) //等于号时
{
    int num = -1;
    for (int k = 0; k < newfour1.size(); k++)
    {
        for (int kk = 0; kk < newfour1[k].idenchar.size(); kk++)
        {
            if (newfour1[k].idenchar[kk] == jsd.name2.value)
                num = k;
        }
        if (jsd.name2.value == newfour1[k].fuhao.value)
        {
            num = k;
        }
    }
    if (num == -1)
    {
        newfour newfour2;
        newfour2.node = newfour1.size();
        newfour2.nihao = "=";
        newfour2.fuhao = jsd.name4;
        newfour2.idenchar.push_back(jsd.name2.value);
        newfour2.parent = -1;
        newfour1.push_back(newfour2);
    }
    else
    {
        if (jsd.name2.value[0] == 't')
        {
            newfour1[num].idenchar.push_back(newfour1[num].fuhao.value);
            newfour1[num].fuhao = jsd.name4;
        }
        else
        {
            newfour1[num].idenchar.push_back(jsd.name4.value);
        }
    }
}
void noequal(fourarray jsd) //非等于号时
{
    int children1 = -1, children2 = -1;
    if (jsd.name2.type == 'C')
    {
        newfour newfour3;
        newfour3.nihao = "=";
        newfour3.node = newfour1.size();
        newfour3.parent = -1;
        newfour3.fuhao = jsd.name2;
        newfour1.push_back(newfour3);
    }
    if (jsd.name3.type == 'C')
    {
        newfour newfour3;
        newfour3.nihao = "=";
        newfour3.node = newfour1.size();
        newfour3.parent = -1;
        newfour3.fuhao = jsd.name3;
        newfour1.push_back(newfour3);
    }
    for (int k = 0; k < newfour1.size(); k++)
    {
        for (int kk = 0; kk < newfour1[k].idenchar.size(); kk++)
        {
            if (jsd.name2.value == newfour1[k].idenchar[kk])
            {
                children1 = k;
            }
            if (jsd.name3.value == newfour1[k].idenchar[kk])
            {
                children2 = k;
            }
        }
        if (jsd.name2.value == newfour1[k].fuhao.value)
        {
            children1 = k;
        }
        if (jsd.name3.value == newfour1[k].fuhao.value)
        {
            children2 = k;
        }
    }
    if (children1 == -1)
    {
        newfour newfour2;
        children1 = newfour1.size();
        newfour2.parent = -1;
        newfour2.fuhao = jsd.name2;
        newfour2.nihao = "=";
        newfour2.node = newfour1.size();
        newfour1.push_back(newfour2);
    }
    if (children2 == -1)
    {
        newfour newfour2;
        children2 = newfour1.size();
        newfour2.parent = -1;
        newfour2.fuhao = jsd.name3;
        newfour2.nihao = "=";
        newfour2.node = newfour1.size();
        newfour1.push_back(newfour2);
    }
    newfour newfour2;
    newfour2.node = newfour1.size();
    newfour2.nihao = jsd.name1.value;
    newfour2.fuhao = jsd.name4;
    newfour2.parent = -1;
    if (children1 == -1)
    {
    }
    else
    {
        newfour2.children.push_back(children1);
        newfour1[children1].parent = newfour1.size();
    }
    if (children2 == -1)
    {
    }
    else
    {
        newfour2.children.push_back(children2);
        newfour1[children2].parent = newfour1.size();
    }
    newfour1.push_back(newfour2);
}
void dofour() //生成新四元式
{
    stack<fourarray> nihao;
    int visit[newfour1.size()] = {0};
    for (int k = newfour1.size() - 1; k >= 0; k--)
    {
        if (newfour1[k].parent == -1 && newfour1[k].children.size() == 0)
            continue;
        else
        {
            if (newfour1[k].nihao == "=" && newfour1[k].idenchar.size() != 0)
            {
                fourarray fourarray2;
                token token2;
                token2.type = 'G';
                token2.value = "=";
                fourarray2.name1 = token2;
                fourarray2.name4 = newfour1[k].fuhao;
                token2.type = 'G';
                token2.value = "_";
                fourarray2.name3 = token2;
                token2.type = 'B';
                token2.value = newfour1[k].idenchar[0];
                fourarray2.name2 = token2;
                nihao.push(fourarray2);
            }
            else if (mark2.find(newfour1[k].nihao) != mark2.end())
            {
                fourarray fourarray2;
                token token2;
                token2.type = 'G';
                token2.value = newfour1[k].nihao;
                fourarray2.name1 = token2;
                fourarray2.name2 = newfour1[newfour1[k].children[0]].fuhao;
                fourarray2.name3 = newfour1[newfour1[k].children[1]].fuhao;
                fourarray2.name4 = newfour1[k].fuhao;
                nihao.push(fourarray2);
            }
        }
    }
    while (!nihao.empty())
    {
        fourarray fourarray2;
        fourarray2 = nihao.top();
        nihao.pop();
        newchararrray.push_back(fourarray2);
    }
}
int optimifour(int i) //优化一个块
{
    for (int j = i; j < chararray.size(); j++)
    {
        if (isinout(chararray[j]))
        {
            inoutfour.push_back(chararray[j]);
            continue;
        }
        if (iskeywords(chararray[j]))
        {
            dofour();
            newchararrray.push_back(chararray[j]);
            newfour1.clear();
            return j;
        }
        if (chararray[j].name1.value == "=")
        {
            doequal(chararray[j]);
        }
        else
        {
            noequal(chararray[j]);
        }
    }
    return chararray.size();
}
void dooptimifour() //所有块优化
{
    int i = 0;
    while (i < chararray.size())
    {
        int j = optimifour(i);
        i = j + 1;
    }
}
void printfnewfour() //打印
{
    for (int k = 0; k < newchararrray.size(); k++)
    {
        cout << left << setw(10) << newchararrray[k].name1.value;
        cout << left << setw(10) << newchararrray[k].name2.value;
        cout << left << setw(10) << newchararrray[k].name3.value;
        cout << left << setw(10) << newchararrray[k].name4.value << endl;
    }
}
void insertfour()
{
    for (int k = 0; k < inoutfour.size(); k++)
    {
        if (inoutfour[k].name1.value == "cout")
        {
            newchararrray.push_back(inoutfour[k]);
        }
        else
        {
            newchararrray.insert(newchararrray.begin(), inoutfour[k]);
        }
    }
}

// 四元式预处理
void actionprep()
{
    token t1, t2;
    t1.type = 'E';
    t1.value = "return";
    t2.type = 'E';
    t2.value = '_';
    fourarray fileend;
    fileend.name1 = t1;
    fileend.name2 = t2;
    fileend.name3 = t2;
    fileend.name4 = t2;
    newchararrray.push_back(fileend);
    for (int i = 0; i < newchararrray.size(); i++)
    {
        if (newchararrray[i].name1.value == "return")
            break;
        else if (newchararrray[i].name1.value == "while")
        {
            fourarray temp;
            temp.name1 = newchararrray[i].name1;
            temp.name2 = newchararrray[i].name2;
            temp.name3 = newchararrray[i].name3;
            temp.name4 = newchararrray[i].name4;
            newchararrray[i].name1 = newchararrray[i + 1].name1;
            newchararrray[i].name2 = newchararrray[i + 1].name2;
            newchararrray[i].name3 = newchararrray[i + 1].name3;
            newchararrray[i].name4 = newchararrray[i + 1].name4;
            newchararrray[i + 1].name1 = temp.name1;
            newchararrray[i + 1].name2 = temp.name2;
            newchararrray[i + 1].name3 = temp.name3;
            newchararrray[i + 1].name4 = temp.name4;
            i++;
        }
    }
    cout << "------------------------------------------" << endl;
    return;
}

// 生成目标代码
void CreateTarget()
{
    char *target = "final.asm";
    int w = 0;
    int w1 = 3;
    int w2 = 3;
    std::fstream targetFile(target, ios::out | ios::in);
    targetFile << "DSEG    SEGMENT  " << endl;
    // 数据段
    
    targetFile << "string  DB 'PLEASE INPUT:','$'" << endl;
    targetFile << "cnt     DW 1000 DUP(0)" << endl;
    targetFile << "float   DD 1000 DUP(0)" << endl;
    targetFile << "bool    DB 1000 DUP(0)" << endl;
    targetFile << "char    DB 1000 DUP(0)" << endl;
    int rpg = 0;
    int bat = 0;
    targetFile << "DSEG    ENDS" << endl;
    targetFile << "SSEG    SEGMENT STACK" << endl;
    targetFile << "SSEG    ENDS" << endl;
    targetFile << "CSEG    SEGMENT" << endl;
    targetFile << "        ASSUME  CS:CSEG,DS:DSEG" << endl;
    targetFile << "        ASSUME  SS:SSEG" << endl;
    targetFile << "MAIN" << ':' << endl;
    targetFile << "        MOV AX,DSEG" << endl;
    targetFile << "        MOV DS,AX" << endl;
    targetFile << "        MOV AX,SSEG" << endl;
    targetFile << "        MOV SS,AX" << endl;
    // 标号序号
    int ifendid = 0;
    int whileendid = 0;
    int elseid = 0;
    int doid = 0;
    int actid = 0;
    int showid = 0;
    int ifid = 0;
    int hexid = 0;
    int flagIW = 0;
    // 代码段
    for (int i = 0; i < newchararrray.size(); i++)
    {
        string key = newchararrray[i].name1.value;
        if (key == "+" || key == "-")
        {
            targetFile << "        MOV AX," << newchararrray[i].name2.value << endl;
            if (key == "+")
            {
                targetFile << "        ADD AX,";
            }
            else if (key == "-")
            {
                targetFile << "        SUB AX,";
            }
            targetFile << newchararrray[i].name3.value << endl;
            targetFile << "        MOV " << newchararrray[i].name4.value << ",AX" << endl;
        }
        else if (key == "*")
        {
            if ((int)newchararrray[i].name2.value[0] >= 48 && (int)newchararrray[i].name2.value[0] <= 57)
            {
                targetFile << "        MOV AL," << newchararrray[i].name2.value << endl;
            }
            else
            {
                targetFile << "        MOV SI,OFFSET " << newchararrray[i].name2.value << endl;
                targetFile << "        MOV AL,BYTE PTR [SI]" << endl;
            }
            if ((int)newchararrray[i].name3.value[0] >= 48 && (int)newchararrray[i].name3.value[0] <= 57)
            {
                targetFile << "        MUL " << newchararrray[i].name3.value << endl;
            }
            else
            {
                targetFile << "        MOV SI,OFFSET " << newchararrray[i].name2.value << endl;
                targetFile << "        MUL BYTE PTR [SI]" << endl;
            }
            targetFile << "        MOV " << newchararrray[i].name4.value << ",AX" << endl;
        }
        else if (key == "/")
        {
            targetFile << "        MOV AX," << newchararrray[i].name3.value << endl;
            if ((int)newchararrray[i].name2.value[0] >= 48 && (int)newchararrray[i].name2.value[0] <= 57)
            {
                targetFile << "        DIV " << newchararrray[i].name2.value << endl;
            }
            else
            {
                targetFile << "        MOV SI,OFFSET " << newchararrray[i].name2.value << endl;
                targetFile << "        DIV BYTE PTR [SI]" << endl;
            }
            targetFile << "        AND AH,00H" << endl;
            targetFile << "        MOV " << newchararrray[i].name4.value << ",AX" << endl;
        }
        else if (key == ">" || key == "<" || key == ">=" || key == "<=" || key == "==")
        {
            targetFile << "compare" << actid << ":   " << endl;
            targetFile << "        MOV AX," << newchararrray[i].name2.value << endl;
            targetFile << "        MOV BX," << newchararrray[i].name3.value << endl;
            targetFile << "        CMP AX,BX" << endl;
            targetFile << "        ";
            if (key == ">")
                targetFile << "JA ";
            else if (key == "<")
                targetFile << "JB ";
            else if (key == ">=")
                targetFile << "JAE ";
            else if (key == "<=")
                targetFile << "JBE ";
            else if (key == "==")
                targetFile << "JNE ";
        }
        else if (key == "=")
        {
            targetFile << "        MOV " << newchararrray[i].name4.value << "," << newchararrray[i].name2.value << endl;
        }
        else if (key == "if")
        {
            targetFile << "else" << elseid << endl;
            targetFile << "if" << ifid++ << ':' << endl;
            flagIW = 1;
        }
        else if (key == "else")
        {
            targetFile << "        JMP end" << ifendid << endl;
            targetFile << "else" << elseid++ << ":" << endl;
        }
        else if (key == "end" && flagIW == 1)
        {
            actid++;
            targetFile << "end" << ifendid++ << ':' << endl;
            flagIW = 0;
        }
        else if (key == "while")
        {
            targetFile << "whileend" << whileendid << endl;
            flagIW = 2;
        }
        else if (key == "do")
        {
            targetFile << "do" << doid++ << ":" << endl;
        }
        else if (key == "end" && flagIW == 2)
        {
            targetFile << "        JMP compare" << actid++ << endl;
            targetFile << "whileend" << whileendid++ << ":" << endl;
            flagIW = 0;
        }
        else if (key == "return")
        {
            targetFile << "        MOV AH,4CH" << endl;
            targetFile << "        INT 21H" << endl;
        }
        else if (key == "cout")
        {
            targetFile << "        MOV CL,16" << endl;
            targetFile << "show" << showid << ':' << endl;
            targetFile << "        SUB CL,04" << endl;
            targetFile << "        MOV AX," << newchararrray[i].name4.value << endl;
            targetFile << "        SHR AX,CL" << endl;
            targetFile << "        AND AX,000FH" << endl;
            targetFile << "        MOV DL,AL" << endl;
            targetFile << "        CMP DL,10" << endl;
            targetFile << "        JB  hex" << hexid << endl;
            targetFile << "        ADD DL,07H" << endl;
            targetFile << "hex" << hexid++ << ':' << endl;
            targetFile << "        ADD DL,30H" << endl;
            targetFile << "        MOV AH,02H" << endl;
            targetFile << "        INT 21H" << endl;
            targetFile << "        CMP CL,0" << endl;
            targetFile << "        JNE show" << showid++ << endl;
            targetFile << "        MOV DL,'H'" << endl;
            targetFile << "        MOV AH,02H" << endl;
            targetFile << "        INT 21H" << endl;
            targetFile << "        MOV DL,0AH" << endl;
            targetFile << "        MOV AH,02H" << endl;
            targetFile << "        INT 21H" << endl;
            targetFile << "        MOV DL,0dH" << endl;
            targetFile << "        INT 21H" << endl;
        }
        else if (key == "cin")
        {
            targetFile << "        MOV DX,OFFSET string" << endl;
            targetFile << "        MOV AH,09H" << endl;
            targetFile << "        INT 21H" << endl;
            targetFile << "        MOV AH,01" << endl;
            targetFile << "        INT 21H" << endl;
            targetFile << "        SUB AL,30H" << endl;
            targetFile << "        AND AX,00FFH" << endl;
            targetFile << "        MOV " << newchararrray[i].name4.value << ",AX" << endl;
            targetFile << "        MOV DL,0AH" << endl;
            targetFile << "        MOV AH,02H" << endl;
            targetFile << "        INT 21H" << endl;
            targetFile << "        MOV DL,0dH" << endl;
            targetFile << "        INT 21H" << endl;
        }
    }
    targetFile << "CSEG    ENDS" << endl;
    targetFile << "        END "
               << "MAIN" << endl;
    targetFile.close();
    std::fstream acto(target, ios::out | ios::in);
    char stri[10000];
    for (int i = 0; i < 10000; i++)
    {
        stri[i] = NULL;
    }
    acto.get(stri, 10000, EOF);
    acto.close();
    cout << stri;
    return;
}

void targetcode()
{
    cout << "--------------Target Code-----------------" << endl;
    actionprep();
    CreateTarget();
    return;
}

int main()
{
    char *filepath = "in.txt";
    autoinit();
    dotoken(filepath);
    readin();
    Getfirst();
    int n = 20;
    while (n--)
    {
        Getfollow();
    }
    Gettable();
    initProcess();
    semantic_analysis();
    printfour();
    dooptimifour();
    cout << endl
         << endl
         << endl;
    insertfour();
    printfnewfour();
    targetcode();
    system("pause");
    return 0;
}
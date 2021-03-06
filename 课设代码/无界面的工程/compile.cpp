#include "compile.h"

void edit()
{
    ifstream fp1;
    ofstream fp2;
    fp1.open("error.txt");
    fp2.open("in.txt");
    if (!fp1.is_open() || !fp2.is_open())
    {
        cout << "error" << endl;
        return;
    }
    string ss;
    while (!fp1.eof())
    {
        fp1 >> ss;
        if (ss == "#include" || ss == "using" || (ss[0] == '/' && ss[1] == '/'))
        {
            getline(fp1, ss);
            continue;
        }
        fp2 << ss;
        while (fp1.peek() != '\n' && !fp1.eof())
        {
            fp1 >> ss;
            if (ss[0] == '/' && ss[1] == '/')
            {
                getline(fp1, ss);
                break;
            }
            fp2 << " " << ss;
        }
        if (!fp1.eof())
            fp2 << '\n';
    }
    fp1.close();
    fp2.close();
}
bool redef_or_notdef()
{
    bool flag = true;
    set<string> teststack = {};
    for (int i = 1; i < all.size(); i++)
    {
        int j = 0;
        if (all[i][0].value == "int" || all[i][0].value == "char" || all[i][0].value == "float" || all[i][0].value == "string" || all[i][0].value == "struct")
        {
            j = 2;
            if (all[i].size() == 1)
                continue;
            if (teststack.find(all[i][1].value) == teststack.end())
                teststack.insert(all[i][1].value);
            else
            {
                cout << "重定义标识符：" << all[i][1].value << endl;
                flag = false;
            }
        }
        for (; j < all[i].size(); j++)
        {
            if (all[i][j].type == 'B')
            {
                if (teststack.find(all[i][j].value) != teststack.end())
                    continue;
                cout << "未定义标识符：" << all[i][j].value << endl;
                flag = false;
            }
        }
    }
    return flag;
}
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

// 符号表输出
void printchart()
{
    cout << endl
         << "符号表如下" << endl;
    cout << left << setw(10) << "name" << left << setw(10) << "type" << left << setw(10) << "cat" << left << setw(10) << "address" << endl;
    for (int k = 0; k < mainchart1[0].length; k++)
    {
        cout << left << setw(10) << mainchart1[k].name;
        cout << left << setw(10) << mainchart1[k].type;
        cout << left << setw(10) << mainchart1[k].cat;
        cout << left << setw(2) << mainchart1[k].address.point << ' ' << mainchart1[k].address.type << endl;
    }
    // cout << "函数表如下" << endl;
    // cout << left << setw(10) << "level" << left << setw(10) << "off" << left << setw(10) << "fn" << endl;
    // for (int k = 0; k < funcchart1[0].length; k++)
    // {
    //     cout << left << setw(10) << funcchart1[k].level;
    //     cout << left << setw(10) << funcchart1[k].off;
    //     cout << left << setw(10) << funcchart1[k].fn << endl;
    //     cout << left << setw(10) << "name" << left << setw(10) << "type" << left << setw(10) << "cat" << left << setw(10) << "address" << endl;
    //     for (int j = 0; j < funcchart1[k].para[0].length; j++)
    //     {
    //         cout << left << setw(10) << funcchart1[k].para[j].name;
    //         cout << left << setw(10) << funcchart1[k].para[j].type;
    //         cout << left << setw(10) << funcchart1[k].para[j].cat;
    //         cout << left << setw(2) << funcchart1[k].para[j].address.point << ' ' << funcchart1[k].para[j].address.type << endl;
    //     }
    // }
    // cout << "类型表如下" << endl;
    // cout << left << setw(10) << "type" << left << setw(10) << "address" << endl;
    // for (int k = 0; k < typechart1.size(); k++)
    // {
    //     cout << left << setw(10) << typechart1[k].type << typechart1[k].address.point << ' ' << typechart1[k].address.type << endl;
    // }
    // cout << "结构体表如下" << endl;
    // cout << left << setw(10) << "name" << left << setw(10) << "off" << left << setw(10) << "type" << endl;
    // for (int k = 0; k < structchart1.size(); k++)
    // {
    //     cout << left << setw(10) << structchart1[k].name << left << setw(10) << structchart1[k].off << left << setw(10) << structchart1[k].type << endl;
    // }
    // cout << "长度表" << endl;
    // for (int k = 0; k < length.size(); k++)
    // {
    //     cout << length[k] << endl;
    // }
    // cout << "活动记录如下" << endl;
    // cout << left << setw(10) << "name" << left << setw(10) << "type" << left << setw(10) << "low" << left << setw(10) << "up" << endl;
    // for (int k = 0; k < vall1[0].length; k++)
    // {
    //     cout << left << setw(10) << vall1[k].name;
    //     cout << left << setw(10) << vall1[k].type;
    //     cout << left << setw(10) << vall1[k].low;
    //     cout << left << setw(10) << vall1[k].up << endl;
    // }
}
int judge(vector<token> token2) //判断
{
    if (token2[0].value == "struct") //结构体
        return 4;
    if (token2.size() < 3)
        return 100;
    if (mark1.find(token2[0].value) != mark1.end())
    {
        if ((token2[1].type == 'B' || token2[1].value == "main") && token2[2].value == "(") //判断函数
        {
            return 1;
        }
        else if (token2[1].type == 'B' && token2[2].value == "[") //数组
        {
            return 3;
        }
        else //其他
        {
            return 2;
        }
    }
    else
    {
        return 100;
    }
}
int returnint(string xx)
{
    int total = 0;
    for (int i = 0; i < xx.size(); i++)
    {
        total = total * 10;
        total = total + xx[i] - 48;
    }
    return total;
}
//返回变量类型长度
int returnsize(token token1)
{
    if (token1.value == "int" || token1.value == "float")
    {
        return 4;
    }
    else if (token1.value == "char")
    {
        return 1;
    }
    else
    {
        return token1.value.size();
    }
}
//数组的填写
void numchartwrite(vector<token> token1)
{
    mainchart1[mainchart1[0].length].name = token1[1].value;
    mainchart1[mainchart1[0].length].type = "t" + to_string(typechart1.size());
    mainchart1[mainchart1[0].length].cat = "d";
    mainchart1[mainchart1[0].length].address.type = 'l';
    mainchart1[mainchart1[0].length].address.point = length.size();
    mainchart1[0].length++;
    typechart typechart2;
    typechart2.type = 'a';
    typechart2.address.type = 'n';
    typechart2.address.point = numchart1.size();
    typechart1.push_back(typechart2);
    numchart numchart2;
    numchart2.low = 1;
    numchart2.up = returnint(token1[3].value);
    numchart2.type = token1[0].value[0];
    numchart2.size = returnsize(token1[0]);
    numchart1.push_back(numchart2);
    vall1[vall1[0].length].name = "局部变量";
    vall1[vall1[0].length].type = token1[1].value;
    vall1[vall1[0].length].low = vall1[vall1[0].length - 1].up + 1;
    vall1[vall1[0].length].up = vall1[vall1[0].length].low + numchart2.up * numchart2.size - 1;
    vall1[0].length++;
    length.push_back(numchart2.up * numchart2.size);
}
//赋值行启作用
void vallsomevar(vector<token> token1)
{
    for (int i = 1; i < token1.size(); i++)
    {
        if (token1[i].type == 'B')
        {
            vall1[vall1[0].length].name = "局部变量";
            vall1[vall1[0].length].type = token1[i].value;
            vall1[vall1[0].length].low = vall1[vall1[0].length - 1].up + 1;
            if (token1[0].value == "int" || token1[0].value == "float")
            {
                vall1[vall1[0].length].up = vall1[vall1[0].length].low + returnsize(token1[0]) - 1;
                vall1[0].length++;
            }
            else
            {
                if (token1[0].value == "string")
                {
                    for (int k = i; k < token1.size(); k++)
                    {
                        if (token1[k].type == 'S')
                        {
                            vall1[vall1[0].length].up = vall1[vall1[0].length].low + token1[k].value.size() - 1;
                            vall1[0].length++;
                        }
                    }
                }
                else if (token1[0].value == "char")
                {
                    vall1[vall1[0].length].up = vall1[vall1[0].length].low;
                    vall1[0].length++;
                }
            }
        }
    }
}
//赋值时填写
void varwrite(vector<token> token1)
{
    for (int i = 1; i < token1.size(); i++)
    {
        if (token1[i].type == 'B')
        {
            mainchart1[mainchart1[0].length].name = token1[i].value;
            mainchart1[mainchart1[0].length].type = token1[0].value;
            mainchart1[mainchart1[0].length].cat = "v";
            mainchart1[mainchart1[0].length].address.type = 'v';
            for (int k = 0; k < vall1[0].length; k++)
            {
                if (vall1[k].type == token1[i].value)
                {
                    mainchart1[mainchart1[0].length].address.point = k;
                }
            }
            mainchart1[0].length++;
            //地址
        }
    }
}
//结构体表
int structchartwrite(vector<vector<token>> token1, int i)
{
    mainchart1[mainchart1[0].length].name = token1[i][1].value;
    mainchart1[mainchart1[0].length].type = "t" + to_string(typechart1.size());
    mainchart1[mainchart1[0].length].cat = "d";
    mainchart1[mainchart1[0].length].address.type = 'l';
    mainchart1[mainchart1[0].length].address.point = length.size();
    mainchart1[0].length++;
    i++;
    i++;
    int size = 0;
    typechart typechart2;
    typechart2.type = 'S';
    typechart2.address.type = 'S';
    typechart2.address.point = structchart1.size();
    typechart1.push_back(typechart2);
    while (1)
    {
        if (token1[i][0].value == "}")
            break;
        vallsomevar(token1[i]);
        varwrite(token1[i]);
        structchart structchart2;
        structchart2.name = token1[i][1].value;
        structchart2.off = size;
        structchart2.type = token1[i][0].value[0];
        structchart1.push_back(structchart2);
        size = size + returnsize(token1[i][0]);
        i++;
    }
    length.push_back(size);
    return i;
}
//函数表的填写
void funcwrite(vector<token> token1)
{
    mainchart1[mainchart1[0].length].name = token1[1].value;
    mainchart1[mainchart1[0].length].type = token1[0].value;
    mainchart1[mainchart1[0].length].cat = "f";
    mainchart1[mainchart1[0].length].address.type = 'f';
    mainchart1[mainchart1[0].length].address.point = funcchart1[0].length;
    mainchart1[0].length++;
    funcchart1[funcchart1[0].length].off = 3;
    funcchart1[funcchart1[0].length].level = level;
    funcchart1[funcchart1[0].length].fn = 0;
    funcchart1[funcchart1[0].length].para[0].length = 0;
    for (int i = 2; i < token1.size(); i++)
    {
        if (token1[i].type == 'B')
        {
            mainchart1[mainchart1[0].length].name = token1[i].value;
            funcchart1[funcchart1[0].length].para[funcchart1[funcchart1[0].length].para[0].length].name = token1[i].value;
            mainchart1[mainchart1[0].length].type = token1[i - 1].value;
            funcchart1[funcchart1[0].length].para[funcchart1[funcchart1[0].length].para[0].length].type = token1[i - 1].value;
            mainchart1[mainchart1[0].length].cat = 'v';
            funcchart1[funcchart1[0].length].para[funcchart1[funcchart1[0].length].para[0].length].cat = 'v';
            mainchart1[mainchart1[0].length].address.type = 'v';
            funcchart1[funcchart1[0].length].para[funcchart1[funcchart1[0].length].para[0].length].address.type = 'v';
            for (int k = 0; k < vall1[0].length; k++)
            {
                if (vall1[k].type == token1[i].value)
                {
                    mainchart1[mainchart1[0].length].address.point = k;
                    funcchart1[funcchart1[0].length].para[funcchart1[funcchart1[0].length].para[0].length].address.point = k;
                }
            }
            mainchart1[0].length++;
            funcchart1[funcchart1[0].length].para[0].length++;
        }
    }
    funcchart1[0].length++;
}
//活动记录初始化
void vallinit()
{
    vall1[0].length = 0;
    vall1[vall1[0].length].name = "old sp";
    vall1[vall1[0].length].type = "";
    vall1[vall1[0].length].low = 0;
    vall1[vall1[0].length].up = 0;
    vall1[0].length++;
    vall1[vall1[0].length].name = "返回地址";
    vall1[vall1[0].length].type = "";
    vall1[vall1[0].length].low = 1;
    vall1[vall1[0].length].up = 1;
    vall1[0].length++;
    vall1[vall1[0].length].name = "全局display变量";
    vall1[vall1[0].length].type = "";
    vall1[vall1[0].length].low = 2;
    vall1[vall1[0].length].up = 2;
    vall1[0].length++;
}
//函数行启作用
void writevarnum(vector<token> token1)
{
    int num = 0;
    vall1[vall1[0].length].name = "参数个数";
    vall1[vall1[0].length].type = "";
    vall1[vall1[0].length].low = 3;
    vall1[vall1[0].length].up = 3;
    vall1[0].length++;
    for (int i = 2; i < token1.size(); i++)
    {
        if (token1[i].type == 'B')
        {
            num++;
        }
    }
    vall1[vall1[0].length - 1].type = to_string(num);
    for (int i = 2; i < token1.size(); i++)
    {
        if (token1[i].type == 'B')
        {
            vall1[vall1[0].length].name = "形式单元";
            vall1[vall1[0].length].type = token1[i].value;
            vall1[vall1[0].length].low = vall1[vall1[0].length - 1].up + 1;
            vall1[vall1[0].length].up = vall1[vall1[0].length].low + returnsize(token1[i - 1]) - 1;
            vall1[0].length++;
        }
    }
    vall1[vall1[0].length].name = "display表";
    vall1[vall1[0].length].type = "0";
    vall1[vall1[0].length].low = vall1[vall1[0].length - 1].up + 1;
    vall1[vall1[0].length].up = vall1[vall1[0].length - 1].up + 1;
    vall1[0].length++;
}
//活动记录符号表的填写
void chartwrite(vector<vector<token>> token1)
{
    vallinit();
    mainchart1[0].length = 0;
    funcchart1[0].length = 0;
    for (int i = 0; i < token1.size(); i++)
    {
        int k = judge(token1[i]);
        if (k == 1)
        {
            writevarnum(token1[i]);
            level++;
            funcwrite(token1[i]);
        }
        else if (k == 2)
        {
            vallsomevar(token1[i]);
            varwrite(token1[i]);
        }
        else if (k == 3)
        {
            numchartwrite(token1[i]);
        }
        else if (k == 4)
        {
            i = structchartwrite(token1, i);
        }
        else
        {
            continue;
        }
    }
}

// 四元式预处理
void prefourele()
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
    newchararrray.push_back(fileend); //四元式末尾程序结束标志
    for (int i = 0; i < newchararrray.size(); i++)
    {
        if (newchararrray[i].name1.value == "return")
            break;
        else if (newchararrray[i].name1.value == "while") //将循环条件提前
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

// 符号表搜索
string typesearch(string value)
{
    for (int k = 0; k < mainchart1[0].length; k++)
    {
        if (value == mainchart1[k].name)
            return mainchart1[k].type; // 返回类型
    }
    return "NULL"; // 未搜索到，返回NULL字符串
}

// 生成目标代码
void CreateTarget()
{
    char *target = "final.asm";
    int w = 0;
    int w1 = 3;
    int w2 = 3;
    std::fstream targetFile(target, ios::out | ios::trunc);
    targetFile << "DSEG    SEGMENT  " << endl;
    // 数据段
    vector<string> finished;
    for (int i = 0; i < newchararrray.size(); i++)
    {
        if (newchararrray[i].name4.value == "_")
            continue;
        // 判断符号是否已经申明，避免重定义
        bool flag = false;
        for (int ls = 0; ls < finished.size(); ls++)
            if (finished[ls] == newchararrray[i].name4.value)
                flag = true;
        if (flag == false)
            finished.push_back(newchararrray[i].name4.value);
        else if (flag == true)
            continue;
        string typeK = typesearch(newchararrray[i].name4.value);
        // 为中间变量时，根据运算符，搜索第二个符号的类型，以确定类型
        if (typeK == "NULL")
        {
            int Len = newchararrray[i].name4.value.length();
            targetFile << newchararrray[i].name4.value;
            while (Len < 8) // 补充空格，使代码工整
            {
                targetFile << " ";
                Len++;
            }
            string key = newchararrray[i].name1.value;
            if (key == "+" || key == "-" || key == "*" || key == "/" || key == "=")
            {
                string temp = typesearch(newchararrray[i].name2.value); //搜索第二个符后的类型
                if (temp == "int" || temp == "float")
                    targetFile << "DW 0" << endl;
                else if (temp == "char")
                    targetFile << "DB 0" << endl;
                else if (temp == "string")
                    targetFile << "DB 1000 DUP(0) , '$'" << endl;
                else //避免出现未定义的变量导致生成代码出错
                {
                    cout << "ERROR" << endl;
                    exit(0);
                }
            }
            else //运算符不为上述，则为比较运算，bool型
            {
                targetFile << "DB 0" << endl;
            }
        }
        else // 符号在符号表中，根据类型生成对应申明语句
        {
            int Len = newchararrray[i].name4.value.length();
            targetFile << newchararrray[i].name4.value;
            while (Len < 8) // 补充空格使代码工整
            {
                targetFile << " ";
                Len++;
            }
            if (typeK == "int" || typeK == "float")
                targetFile << "DW 0" << endl;
            else if (typeK == "char")
                targetFile << "DB 0" << endl;
            else if (typeK == "string")
                targetFile << "DB 1000 DUP(0) , '$'" << endl;
        }
    }
    //常规代码
    targetFile << "string  DB 'PLEASE INPUT:','$'" << endl;
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
    // 标号序号，控制标号防止重定义
    int ifendid = 0;
    int whileendid = 0;
    int elseid = 0;
    int doid = 0;
    int actid = 0;
    int coutid = 0;
    int ifid = 0;
    int couthid = 0;
    int flagIW = 0;
    // 代码段
    for (int i = 0; i < newchararrray.size(); i++)
    {
        string key = newchararrray[i].name1.value;
        if (key == "+" || key == "-") //加减法
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
        else if (key == "*") //乘法
        {
            if ((int)newchararrray[i].name2.value[0] >= 48 && (int)newchararrray[i].name2.value[0] <= 57) //第一个为立即数时
            {
                targetFile << "        MOV AL," << newchararrray[i].name2.value << endl;
            }
            else //不为立即数时
            {
                targetFile << "        MOV SI,OFFSET " << newchararrray[i].name2.value << endl;
                targetFile << "        MOV AL,BYTE PTR [SI]" << endl;
            }
            if ((int)newchararrray[i].name3.value[0] >= 48 && (int)newchararrray[i].name3.value[0] <= 57) //第二个为立即数时
            {
                targetFile << "        MUL " << newchararrray[i].name3.value << endl;
            }
            else //不为立即数时
            {
                targetFile << "        MOV SI,OFFSET " << newchararrray[i].name2.value << endl;
                targetFile << "        MUL BYTE PTR [SI]" << endl;
            }
            targetFile << "        MOV " << newchararrray[i].name4.value << ",AX" << endl;
        }
        else if (key == "/") //除法
        {
            targetFile << "        MOV AX," << newchararrray[i].name3.value << endl;
            if ((int)newchararrray[i].name2.value[0] >= 48 && (int)newchararrray[i].name2.value[0] <= 57) //除数为立即数时
            {
                targetFile << "        DIV " << newchararrray[i].name2.value << endl;
            }
            else //除数不为立即数时
            {
                targetFile << "        MOV SI,OFFSET " << newchararrray[i].name2.value << endl;
                targetFile << "        DIV BYTE PTR [SI]" << endl;
            }
            targetFile << "        AND AH,00H" << endl;
            targetFile << "        MOV " << newchararrray[i].name4.value << ",AX" << endl;
        }
        else if (key == ">" || key == "<" || key == ">=" || key == "<=" || key == "==") //判断语句
        {
            targetFile << "compare" << actid << ":   " << endl;
            targetFile << "        MOV AX," << newchararrray[i].name2.value << endl;
            targetFile << "        MOV BX," << newchararrray[i].name3.value << endl;
            targetFile << "        CMP AX,BX" << endl;
            targetFile << "        ";
            // 根据判断语句生成对应跳转代码，跳转位置稍后填写
            if (key == ">")
                targetFile << "JB ";
            else if (key == "<")
                targetFile << "JA ";
            else if (key == ">=")
                targetFile << "JBE ";
            else if (key == "<=")
                targetFile << "JAE ";
            else if (key == "==")
                targetFile << "JNE ";
        }
        else if (key == "=") //赋值语句
        {
            targetFile << "        MOV " << newchararrray[i].name4.value << "," << newchararrray[i].name2.value << endl;
        }
        else if (key == "if")
        {
            targetFile << "else" << elseid << endl;      //填写跳转语句的标号
            targetFile << "if" << ifid++ << ':' << endl; //添加if语句标号
            flagIW = 1;
        }
        else if (key == "else")
        {
            targetFile << "        JMP ifend" << ifendid << endl; //跳出if
            targetFile << "else" << elseid++ << ":" << endl;      //添加else语句标号
        }
        else if (key == "end" && flagIW == 1)
        {
            actid++;
            targetFile << "ifend" << ifendid++ << ':' << endl; //添加if结束后的标号
            flagIW = 0;
        }
        else if (key == "while")
        {
            targetFile << "whileend" << whileendid << endl; //添加跳转语句的标号
            flagIW = 2;
        }
        else if (key == "do")
        {
            targetFile << "do" << doid++ << ":" << endl; //循环体标号
        }
        else if (key == "end" && flagIW == 2)
        {
            targetFile << "        JMP compare" << actid++ << endl; //跳转回循环条件判断
            targetFile << "whileend" << whileendid++ << ":" << endl;
            flagIW = 0;
        }
        else if (key == "return") //程序末尾
        {
            targetFile << "        MOV AH,4CH" << endl;
            targetFile << "        INT 21H" << endl;
        }
        else if (key == "cout") //输出语句
        {
            targetFile << "        MOV CL,16" << endl;
            targetFile << "cout" << coutid << ':' << endl;
            targetFile << "        SUB CL,04" << endl;
            targetFile << "        MOV AX," << newchararrray[i].name4.value << endl;
            targetFile << "        SHR AX,CL" << endl;
            targetFile << "        AND AX,000FH" << endl;
            targetFile << "        MOV DL,AL" << endl;
            targetFile << "        CMP DL,10" << endl;
            targetFile << "        JB  couth" << couthid << endl;
            targetFile << "        ADD DL,07H" << endl;
            targetFile << "couth" << couthid++ << ':' << endl;
            targetFile << "        ADD DL,30H" << endl;
            targetFile << "        MOV AH,02H" << endl;
            targetFile << "        INT 21H" << endl;
            targetFile << "        CMP CL,0" << endl;
            targetFile << "        JNE cout" << coutid++ << endl;
            targetFile << "        MOV DL,'H'" << endl;
            targetFile << "        MOV AH,02H" << endl;
            targetFile << "        INT 21H" << endl;
            targetFile << "        MOV DL,0AH" << endl;
            targetFile << "        MOV AH,02H" << endl;
            targetFile << "        INT 21H" << endl;
            targetFile << "        MOV DL,0DH" << endl;
            targetFile << "        INT 21H" << endl;
        }
        else if (key == "cin") //输入语句
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
            targetFile << "        MOV DL,0DH" << endl;
            targetFile << "        INT 21H" << endl;
        }
    }
    // 代码段结束，给出程序入口
    targetFile << "CSEG    ENDS" << endl;
    targetFile << "        END "
               << "MAIN" << endl;
    targetFile.close();
    // 在命令行输出
    std::fstream fileout(target, ios::out | ios::in);
    char filecon[10000];
    for (int i = 0; i < 10000; i++)
    {
        filecon[i] = NULL;
    }
    fileout.get(filecon, 10000, EOF);
    fileout.close();
    cout << filecon;
    return;
}

void targetcode()
{
    chartwrite(all);
    printchart();
    cout << "------------------------------------------" << endl;
    cout << "--------------Target Code-----------------" << endl;
    prefourele();
    CreateTarget();
    return;
}

int main()
{
    char *filepath = "in.txt";
    edit();
    autoinit();
    dotoken(filepath);
    bool flag = redef_or_notdef();
    if (flag == false)
        exit(0);
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
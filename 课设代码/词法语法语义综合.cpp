#include "compile.h"

void autoinit()
{
    for(int hh=0;hh<18;hh++)//状态转移方程初始化
    {
        for(int kk=0;kk<256;kk++)
            chart[hh][kk]=0;
    }
    for(int hh=65;hh<=90;hh++)
    {
        chart[1][hh]=2;
        chart[2][hh]=2;
    }
    for(int hh=97;hh<=122;hh++)
    {
        chart[1][hh]=2;
        chart[2][hh]=2;
    }
    for(int hh=48;hh<=57;hh++)
    {
        chart[1][hh]=3;
        chart[2][hh]=2;
        chart[3][hh]=3;
        chart[4][hh]=5;
        chart[5][hh]=5;
    }
    chart[3][46]=4;
    chart[1]['<']=6;
    chart[6]['<']=7;
    chart[1]['>']=8;
    chart[8]['>']=9;
    chart[1]['/']=10;
    chart[10]['/']=11;
    chart[6]['=']=12;
    chart[8]['=']=13;
    chart[1]['=']=14;
    chart[14]['=']=15;
}
int automaton(string strline,int i,vector<token> &token1)//自动机
{
    string strline1="";
    int kk1=1,kk2=1,j;
    for(j=i;i<strline.size();j++)
    {
        kk1=kk2;
        kk2=chart[kk1][strline[j]];
        if(kk2==0)
            break;
        strline1+=strline[j];
    }
    switch(kk1)
    {
        case 2:
        {
            if(keyword.find(strline1)!=keyword.end())
            {
                token token2;
                token2.type='G';
                token2.value=strline1;
                token1.push_back(token2);
            }
            else
            {
                token token2;
                token2.type='B';
                token2.value=strline1;
                token1.push_back(token2);
            }
            break;   
        }
        case 3:
        {
            token token2;
            token2.type='C';
            token2.value=strline1;
            token1.push_back(token2);
            break;
        }
        case 5:
        {
            token token2;
            token2.type='C';
            token2.value=strline1;
            token1.push_back(token2);
            break;
        }
        case 6:
        {
            token token2;
            token2.type='J';
            token2.value=strline1;
            token1.push_back(token2);
            break;
        }
        case 7:
        {
            token token2;
            token2.type='J';
            token2.value=strline1;
            token1.push_back(token2);
            break;
        }
        case 8:
        {
            token token2;
            token2.type='J';
            token2.value=strline1;
            token1.push_back(token2);
            break;
        }
        case 9:
        {
            token token2;
            token2.type='J';
            token2.value=strline1;
            token1.push_back(token2);
            break;
        }
        case 11:
        {
            j=strline.size();
            break;
        }
        case 13:
        {
            token token2;
            token2.type='J';
            token2.value=strline1;
            token1.push_back(token2);
            break;
        }
        case 14:
        {
            token token2;
            token2.type='J';
            token2.value=strline1;
            token1.push_back(token2);
            break;
        }
        case 15:
        {
            token token2;
            token2.type='J';
            token2.value=strline1;
            token1.push_back(token2);
            break;
        }
        default://其余态报错
        {
            cout<<"出现错误";
        }
    }
    j--;
    return j;
}
int level=0;
set<string> mark1={"int","void","float","string","char"};
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
struct vall
{
    string name;//名字
    string type;//标识符名字
    int low;
    int up;
    int length;
};
vall vall1[100];
void printchart()
{   
    cout<<"符号表如下"<<endl;
    cout<<"name"<<"       "<<"type"<<"       "<<"cat"<<"       "<<"address"<<endl;
    for(int k=0;k<mainchart1[0].length;k++)
    {
        cout<<mainchart1[k].name<<"       ";
        cout<<mainchart1[k].type<<"       ";
        cout<<mainchart1[k].cat<<"       ";
        cout<<mainchart1[k].address.point<<' '<<mainchart1[k].address.type<<endl;
    }
    cout<<"函数表如下"<<endl;
    cout<<"level"<<"       "<<"off"<<"       "<<"fn"<<endl;
    for(int k=0;k<funcchart1[0].length;k++)
    {
        cout<<funcchart1[k].level<<"       ";
        cout<<funcchart1[k].off<<"       ";
        cout<<funcchart1[k].fn<<"       "<<endl;
        cout<<"name"<<"       "<<"type"<<"       "<<"cat"<<"       "<<"address"<<endl;
        for(int j=0;j<funcchart1[k].para[0].length;j++)
        {
            cout<<funcchart1[k].para[j].name<<"       ";
            cout<<funcchart1[k].para[j].type<<"       ";
            cout<<funcchart1[k].para[j].cat<<"       ";
            cout<<funcchart1[k].para[j].address.point<<' '<<funcchart1[k].para[j].address.type<<endl;
        }
    }
    cout<<"活动记录如下"<<endl;
    cout<<"name"<<"       "<<"type"<<"       "<<"low"<<"       "<<"up"<<endl;
    for(int k=0;k<vall1[0].length;k++)
    {
        cout<<vall1[k].name<<"       ";
        cout<<vall1[k].type<<"       ";
        cout<<vall1[k].low<<"       ";
        cout<<vall1[k].up<<endl;
    }
}
int judge(vector<token> token2)//判断
{
    if(token2.size()<3)
        return 100;
    if(mark1.find(token2[0].value)!=mark1.end())
    {
        if((token2[1].type=='B'||token2[1].value=="main")&&token2[2].value=="(")
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return 100;
    }
    
}
void funcwrite(vector<token> token1)//函数表的填写
{
    mainchart1[mainchart1[0].length].name=token1[1].value;
    mainchart1[mainchart1[0].length].type=token1[0].value;
    mainchart1[mainchart1[0].length].cat="f";
    mainchart1[mainchart1[0].length].address.type='f';
    mainchart1[mainchart1[0].length].address.point=funcchart1[0].length;
    mainchart1[0].length++;
    funcchart1[funcchart1[0].length].off=3;
    funcchart1[funcchart1[0].length].level=level;
    funcchart1[funcchart1[0].length].fn=0;
    funcchart1[funcchart1[0].length].para[0].length=0;
    for(int i=2;i<token1.size();i++)
    {
        if(token1[i].type=='B')
        {
            mainchart1[mainchart1[0].length].name=token1[i].value;
            funcchart1[funcchart1[0].length].para[funcchart1[funcchart1[0].length].para[0].length].name=token1[i].value;
            mainchart1[mainchart1[0].length].type=token1[i-1].value;
            funcchart1[funcchart1[0].length].para[funcchart1[funcchart1[0].length].para[0].length].type=token1[i-1].value;
            mainchart1[mainchart1[0].length].cat='v';
            funcchart1[funcchart1[0].length].para[funcchart1[funcchart1[0].length].para[0].length].cat='v';
            mainchart1[mainchart1[0].length].address.type='v';
            funcchart1[funcchart1[0].length].para[funcchart1[funcchart1[0].length].para[0].length].address.type='v';
            for(int k=0;k<vall1[0].length;k++)
            {
                if(vall1[k].type==token1[i].value)
                {
                    mainchart1[mainchart1[0].length].address.point=k;
                    funcchart1[funcchart1[0].length].para[funcchart1[funcchart1[0].length].para[0].length].address.point=k;
                }
            }
            mainchart1[0].length++;
            funcchart1[funcchart1[0].length].para[0].length++;
        }
    }
    funcchart1[0].length++;
}
void varwrite(vector<token> token1)//赋值时填写
{
    for(int i=1;i<token1.size();i++)
    {
        if(token1[i].type=='B')
        {
            mainchart1[mainchart1[0].length].name=token1[i].value;
            mainchart1[mainchart1[0].length].type=token1[0].value;
            mainchart1[mainchart1[0].length].cat="v";
            mainchart1[mainchart1[0].length].address.type='v';
            for(int k=0;k<vall1[0].length;k++)
            {
                if(vall1[k].type==token1[i].value)
                {
                    mainchart1[mainchart1[0].length].address.point=k;
                }
            }
            mainchart1[0].length++;
            //地址
        }
    }
}
void vallinit()//活动记录初始化
{
    vall1[0].length=0;
    vall1[vall1[0].length].name="old sp";
    vall1[vall1[0].length].type="";
    vall1[vall1[0].length].low=0;
    vall1[vall1[0].length].up=0;
    vall1[0].length++;
    vall1[vall1[0].length].name="返回地址";
    vall1[vall1[0].length].type="";
    vall1[vall1[0].length].low=1;
    vall1[vall1[0].length].up=1;
    vall1[0].length++;
    vall1[vall1[0].length].name="全局display变量";
    vall1[vall1[0].length].type="";
    vall1[vall1[0].length].low=2;
    vall1[vall1[0].length].up=2;
    vall1[0].length++;
}
int returnsize(token token1)//返回变量类型长度
{
    if(token1.value=="int"||token1.value=="float")
    {
        return 4;
    }
    else if(token1.value=="char")
    {
        return 1;
    }
    else
    {
        return token1.value.size();
    }  
}
void writevarnum(vector<token> token1)//函数行启作用
{
    int num=0;
    vall1[vall1[0].length].name="参数个数";
    vall1[vall1[0].length].type="";
    vall1[vall1[0].length].low=3;
    vall1[vall1[0].length].up=3;
    vall1[0].length++;
    for(int i=2;i<token1.size();i++)
    {
        if(token1[i].type=='B')
        {
            num++;
        }
    }
    vall1[vall1[0].length-1].type=to_string(num);
    for(int i=2;i<token1.size();i++)
    {
        if(token1[i].type=='B')
        {
            vall1[vall1[0].length].name="形式单元";
            vall1[vall1[0].length].type=token1[i].value;
            vall1[vall1[0].length].low=vall1[vall1[0].length-1].up+1;
            vall1[vall1[0].length].up=vall1[vall1[0].length].low+returnsize(token1[i-1])-1;
            vall1[0].length++;
        }
    }
    vall1[vall1[0].length].name="display表";
    vall1[vall1[0].length].type="0";
    vall1[vall1[0].length].low=vall1[vall1[0].length-1].up+1;
    vall1[vall1[0].length].up=vall1[vall1[0].length-1].up+1;
    vall1[0].length++;

}
void vallsomevar(vector<token> token1)//赋值行启作用
{
    for(int i=1;i<token1.size();i++)
    {
        if(token1[i].type=='B')
        {
            vall1[vall1[0].length].name="局部变量";
            vall1[vall1[0].length].type=token1[i].value;
            vall1[vall1[0].length].low=vall1[vall1[0].length-1].up+1;
            if(token1[0].value=="int"||token1[0].value=="float")
            {
                vall1[vall1[0].length].up=vall1[vall1[0].length].low+returnsize(token1[0])-1;
                vall1[0].length++;
            }
            else
            {
                if(token1[0].value=="string")
                {
                    for(int k=i;k<token1.size();k++)
                    {
                        if(token1[k].type=='S')
                        {
                            vall1[vall1[0].length].up=vall1[vall1[0].length].low+token1[k].value.size()-1;
                            vall1[0].length++;
                        }
                    }
                }
                else if(token1[0].value=="char")
                {
                    vall1[vall1[0].length].up=vall1[vall1[0].length].low;
                    vall1[0].length++;
                }
            }
            
        }
        
    }
}
void chartwrite(vector<vector<token>> token1)//活动记录符号表的填写
{
    vallinit();
    mainchart1[0].length=0;
    funcchart1[0].length=0;
    for(int i=0;i<token1.size();i++)
    {
        int k=judge(token1[i]);
        cout<<k<<endl;
        if(k==1)
        {
            writevarnum(token1[i]);
            level++;
            funcwrite(token1[i]);
        }
        else if(k==2)
        {
            vallsomevar(token1[i]);
            varwrite(token1[i]);
        }
        else
        {
            continue;
        }
    }
}
void dotoken(char *filename)
{
    totalrow=0;
    ifstream file;
    file.open(filename,ios::in);
    if(!file.is_open())
        return ;
    string strline;
    while(getline(file,strline))
    {
        totalrow++;
        cout<<strline<<endl;
        vector<token> token1;//包含整行的token
        int i;
        strline+='@';
        for(i=0;i<strline.size();i++)
        {
            if(strline[i]==' ')
                continue;
            else if(strline[i]=='@')
                break;
            else if(strline[i]=='\'')
            {
                i++;
                token token2;//某个token
                token2.type='c';
                token2.value=strline[i];
                token1.push_back(token2);
                i++;
                if(strline[i]!='\'')
                    cout<<"error";
            }
            else if(strline[i]=='\"')
            {
                i++;
                int k;
                string strline2="";
                for(k=i;k<strline.size();k++)
                {
                    if(strline[k]=='\"')
                        break;
                    else if(strline[k]=='@')
                    {
                        cout<<"error";
                        break;
                    }
                    else
                    {   
                        strline2+=strline[k];
                    }
                }
                i=k;
                token token2;//某个token
                token2.type='S';
                token2.value=strline2;
                token1.push_back(token2);
            }
            else if(mark.find(strline[i])!=mark.end())
            {
                token token2;//某个token
                token2.type='J';
                token2.value=strline[i];
                token1.push_back(token2);
            }
            else
            {
                int j=automaton(strline,i,token1);
                i=j;
            }
        }
        all.push_back(token1);
    }
}

int main()
{
    char* filepath="in.txt";
    autoinit();
    dotoken(filepath);
    
    for(int i=0;i<all.size();i++)
    {
        for(int j=0;j<all[i].size();j++)
        {
            cout<<all[i][j].type<<' '<<all[i][j].value<<"         ";
        }
        cout<<endl;
    }
    chartwrite(all);
    cout<<vall1[0].length;
    printchart();
    system("pause");
    return 0;
}
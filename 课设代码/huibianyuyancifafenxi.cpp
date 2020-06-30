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
int automaton(string strline,int i,vector<token> &token1)
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
    char* filepath="error.txt";
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
    system("pause");
    return 0;

}
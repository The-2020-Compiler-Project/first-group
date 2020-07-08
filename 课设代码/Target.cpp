#include "compile.h"
enum type
{
	number,
	ch,
	id,
	undefine
};
enum typ1
{
	in,
	fl,
	chars,
	boo
};
enum typ2
{
	var,
	fu
};
typ1 kindget(char cmp[15]);
// 标识符活动记录,类型登记
struct actrecord
{
	char id[15];
	int low;
	int up;
	typ1 s1;
	typ2 s2;
};
actrecord st1[100];
// 四元式结构
struct elem4
{
	int idact;
	char id1[15];
	char id2[15];
	type type1;
	type type2;
	char id3[15];
};
elem4 foure[100];
char ctable[20][10] = {"+", "-", "*", "/", ">", "<", ">=", "<=", "==", "=", "if", "else", "ie", "while", "do", "we", "return", "cout", "cin", "_"};

// 接口调整
void initFile()
{
	
}

// 四元式预处理，使之更适应生成目标代码
void actionprep()
{
	elem4 exchange;
	cout << "下面进行四元式预处理..." << endl;
	for (int i = 0;; i++)
	{
		if (foure[i].idact == -1)
			break;
		if ((foure[i].idact == 10) | (foure[i].idact == 13))
		{
			exchange.idact = foure[i].idact;
			strcpy_s(exchange.id1, foure[i].id1);
			exchange.type1 = foure[i].type1;
			strcpy_s(exchange.id2, foure[i].id2);
			exchange.type2 = foure[i].type2;
			strcpy_s(exchange.id3, foure[i].id3);
			foure[i].idact = foure[i + 1].idact;
			strcpy_s(foure[i].id1, foure[i + 1].id1);
			foure[i].type1 = foure[i + 1].type1;
			strcpy_s(foure[i].id2, foure[i + 1].id2);
			foure[i].type2 = foure[i + 1].type2;
			strcpy_s(foure[i].id3, foure[i + 1].id3);
			foure[i + 1].idact = exchange.idact;
			strcpy_s(foure[i + 1].id1, exchange.id1);
			foure[i + 1].type1 = exchange.type1;
			strcpy_s(foure[i + 1].id2, exchange.id2);
			foure[i + 1].type2 = exchange.type2;
			strcpy_s(foure[i + 1].id3, exchange.id3);
			i++;
		}
		else if (foure[i].idact <= 3)
		{
			exchange.idact = foure[i].idact;
			strcpy_s(exchange.id1, foure[i].id1);
			exchange.type1 = foure[i].type1;
			strcpy_s(exchange.id2, foure[i].id2);
			exchange.type2 = foure[i].type2;
			strcpy_s(exchange.id3, foure[i].id3);
			foure[i].idact = foure[i - 1].idact;
			strcpy_s(foure[i].id1, foure[i - 1].id1);
			foure[i].type1 = foure[i - 1].type1;
			strcpy_s(foure[i].id2, foure[i - 1].id2);
			foure[i].type2 = foure[i - 1].type2;
			strcpy_s(foure[i].id3, foure[i - 1].id3);
			foure[i - 1].idact = exchange.idact;
			strcpy_s(foure[i - 1].id1, exchange.id1);
			foure[i - 1].type1 = exchange.type1;
			strcpy_s(foure[i - 1].id2, exchange.id2);
			foure[i - 1].type2 = exchange.type2;
			strcpy_s(foure[i - 1].id3, exchange.id3);
		}
	}
	return;
}

// 对符号表进行预处理，为生成中间代码做准备
void symbolprep()
{
	char s1[] = "symbol.cr";
	char s2[] = "vall.cr";
	int i = 0;
	std::fstream act1(s1, ios::out | ios::in); //打开符号表文件
	std::fstream act2(s2, ios::out | ios::in); //打开活动记录文件
	act1 >> st1[i].id;
	char cmp[15];
	act2 >> cmp;
	while (strcmp(st1[i].id, cmp) != 0)
	{
		strcpy_s(cmp, "_");
		act2 >> cmp;
	}
	act2 >> st1[i].low;
	act2 >> st1[i].up;
	strcpy_s(cmp, "");
	act1 >> cmp;
	if (strcmp(cmp, "int") == 0)
		st1[i].s1 = in;
	else if (strcmp(cmp, "char") == 0)
		st1[i].s1 = chars;
	else if (strcmp(cmp, "float") == 0)
		st1[i].s1 = fl;
	strcpy_s(cmp, "");
	act1 >> cmp;
	st1[i++].s2 = fu;
	while (!act1.eof())
	{
		act1 >> st1[i].id;
		act2 >> cmp;
		act2 >> st1[i].low;
		act2 >> st1[i].up;
		strcpy_s(cmp, "");
		act1 >> cmp;
		if (strcmp(cmp, "int") == 0)
			st1[i].s1 = in;
		else if (strcmp(cmp, "char") == 0)
			st1[i].s1 = chars;
		else if (strcmp(cmp, "float") == 0)
			st1[i].s1 = fl;
		act1 >> cmp;
		st1[i++].s2 = var;
	}
	strcpy_s(st1[i - 1].id, "_");
	int low = 0;
	int gdot = 0;
	for (int i = 0;; i++)
	{
		if (strcmp(st1[i].id, "_") == 0)
		{
			gdot = i;
			low = st1[i - 1].up + 1;
			break;
		}
	}
	for (int i = 0;; i++)
	{
		if (foure[i].idact == -1)
			break;
		switch (foure[i].idact)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		{
			strcpy_s(st1[gdot].id, foure[i].id3);
			st1[gdot].low = low;
			st1[gdot].up = low + 4 - 1;
			st1[gdot].s1 = in;
			st1[gdot].s2 = var;
			low = st1[gdot++].up + 1;
		}
		break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		{
			strcpy_s(st1[gdot].id, foure[i].id3);
			st1[gdot].low = low;
			st1[gdot].up = low;
			st1[gdot].s1 = boo;
			st1[gdot++].s2 = var;
			low++;
		}
		break;
		default:;
		}
	}
	strcpy_s(st1[gdot].id, "_");
}

typ1 kindget(char cmp[15])
{
	for (int i = 0;; i++)
	{
		if (strcmp(st1[i].id, cmp) == 0)
			return st1[i].s1;
	}
}
// 生成目标代码
void CreateTarget()
{
	char target[] = "target.asm";
	int w = 0;
	int w1 = 3;
	int w2 = 3;
	std::fstream act(target, ios::out | ios::in);
	act << "DSEG    SEGMENT  " << endl;
	for (int i = 0;; i++)
	{
		if (strcmp(st1[i].id, "_") == 0)
			break;
		if (st1[i].s2 == fu)
			continue;
		int s = strlen(st1[i].id);
		act << st1[i].id;
		while (s < 8)
		{
			act << " ";
			s++;
		}
		switch (st1[i].s1)
		{
		case fl:
		case in:
			act << "DW 0" << endl;
			break;
		case chars:
			act << "DB 0" << endl;
			break;
		case boo:
			act << "DB 0" << endl;
			break;
		}
	}
	act << "string  DB 'PLEASE INPUT:','$'" << endl;
	act << "cnt     DW 1000 DUP(0)" << endl;
	act << "float   DD 1000 DUP(0)" << endl;
	act << "bool    DB 1000 DUP(0)" << endl;
	act << "char    DB 1000 DUP(0)" << endl;
	int rpg = 0;
	int bat = 0;
	act << "DSEG    ENDS" << endl;
	act << "SSEG    SEGMENT STACK" << endl;
	act << "SSEG    ENDS" << endl;
	act << "CSEG    SEGMENT" << endl;
	act << "        ASSUME  CS:CSEG,DS:DSEG" << endl;
	act << "        ASSUME  SS:SSEG" << endl;
	act << "main" << ':' << endl;
	act << "        MOV AX,DSEG" << endl;
	act << "        MOV DS,AX" << endl;
	act << "        MOV AX,SSEG" << endl;
	act << "        MOV SS,AX" << endl;
	int ifendid = 0;
	int whileendid = 0;
	int elseid = 0;
	int doid = 0;
	int actid = 0;
	int showid = 0;
	int ifid = 0;
	int hexid = 0;
	for (int i = 0;; i++)
	{
		if (foure[i].idact == -1)
			break;
		if (foure[i].idact == 16)
			continue;
		typ1 kind1;
		kind1 = kindget(foure[i].id3);
		switch (foure[i].idact)
		{
		case 0:
		case 1:
		{
			act << "        MOV AX,";
			switch (foure[i].type1)
			{
			case number:
			{
				int value = atoi(foure[i].id1);
				char cmp2[15];
				_itoa_s(value, cmp2, 16);
				int c0 = 4 - strlen(cmp2);
				while (c0 > 0)
				{
					act << '0';
					c0--;
				}
				act << cmp2 << 'H' << endl;
			}
			break;
			case ch:
				cout << "ERROR:wrong type" << endl;
				getchar();
				exit(1);
			case id:
				act << foure[i].id1 << endl;
			}
			switch (foure[i].idact)
			{
			case 0:
				act << "        ADD AX,";
				break;
			case 1:
				act << "        SUB AX,";
			}
			switch (foure[i].type2)
			{
			case number:
			{
				int value = atoi(foure[i].id2);
				char cmp2[15];
				_itoa_s(value, cmp2, 16);
				int c0 = 4 - strlen(cmp2);
				while (c0 > 0)
				{
					act << '0';
					c0--;
				}
				act << cmp2 << 'H' << endl;
			}
			break;
			case ch:
				cout << "ERROR:wrong type" << endl;
				getchar();
				exit(1);
			case id:
				act << foure[i].id2 << endl;
			}
			act << "        MOV " << foure[i].id3 << ",AX" << endl;
		}
		break;
		case 2:
		{
			switch (foure[i].type1)
			{
			case ch:
				cout << "ERROR:wrong type" << endl;
				getchar();
				exit(1);
			case id:
			{
				act << "        MOV SI,OFFSET " << foure[i].id1 << endl;
				act << "        MOV AL,BYTE PTR [SI]" << endl;
			}
			break;
			case number:
			{
				act << "        MOV AL,";
				int value = atoi(foure[i].id1);
				char cmp2[15];
				_itoa_s(value, cmp2, 16);
				int c0 = 2 - strlen(cmp2);
				while (c0 > 0)
				{
					act << '0';
					c0--;
				}
				act << cmp2 << 'H' << endl;
			}
			}
			switch (foure[i].type2)
			{
			case ch:
				cout << "ERROR:wrong type" << endl;
				getchar();
				exit(1);
			case id:
			{
				act << "        MOV SI,OFFSET " << foure[i].id2 << endl;
				act << "        MUL BYTE PTR [SI]" << endl;
			}
			break;
			case number:
			{
				act << "        MUL ";
				int value = atoi(foure[i].id2);
				char cmp2[15];
				_itoa_s(value, cmp2, 16);
				int c0 = 2 - strlen(cmp2);
				while (c0 > 0)
				{
					act << '0';
					c0--;
				}
				act << cmp2 << 'H' << endl;
			}
			}
			act << "        MOV " << foure[i].id3 << ",AX" << endl;
		}
		break;
		case 3:
		{
			act << "        MOV AX,";
			switch (foure[i].type2)
			{
			case ch:
				cout << "ERROR:wrong type" << endl;
				getchar();
				exit(1);
			case id:
				act << foure[i].id2 << endl;
				break;
			case number:
			{
				int value = atoi(foure[i].id2);
				char cmp2[15];
				_itoa_s(value, cmp2, 16);
				int c0 = 4 - strlen(cmp2);
				while (c0 > 0)
				{
					act << '0';
					c0--;
				}
				act << cmp2 << 'H' << endl;
			}
			}
			switch (foure[i].type1)
			{
			case ch:
				cout << "ERROR:wrong type" << endl;
				getchar();
				exit(1);
			case id:
			{
				act << "        MOV SI,OFFSET " << foure[i].id1 << endl;
				act << "        DIV BYTE PTR [SI]" << endl;
			}
			break;
			case number:
			{
				act << "        DIV ";
				int value = atoi(foure[i].id1);
				char cmp2[15];
				_itoa_s(value, cmp2, 16);
				int c0 = 2 - strlen(cmp2);
				while (c0 > 0)
				{
					act << '0';
					c0--;
				}
				act << cmp2 << 'H' << endl;
			}
			}
			act << "        AND AH,00H" << endl;
			act << "        MOV " << foure[i].id3 << ",AX" << endl;
		}
		break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		{
			act << "compare" << actid << ":   " << endl;
			act << "        MOV AX,";
			switch (foure[i].type1)
			{
			case ch:
				cout << "ERROR:wrong type" << endl;
				getchar();
				exit(1);
			case id:
			{
				act << foure[i].id1 << endl;
			}
			break;
			case number:
			{
				int value = atoi(foure[i].id1);
				char cmp2[15];
				_itoa_s(value, cmp2, 16);
				int c0 = 4 - strlen(cmp2);
				while (c0 > 0)
				{
					act << '0';
					c0--;
				}
				act << cmp2 << 'H' << endl;
			}
			}
			act << "        MOV BX,";
			switch (foure[i].type2)
			{
			case ch:
				cout << "ERROR:wrong type" << endl;
				getchar();
				exit(1);
			case id:
			{
				act << foure[i].id2 << endl;
			}
			break;
			case number:
			{
				int value = atoi(foure[i].id2);
				char cmp2[15];
				_itoa_s(value, cmp2, 16);
				int c0 = 4 - strlen(cmp2);
				while (c0 > 0)
				{
					act << '0';
					c0--;
				}
				act << cmp2 << 'H' << endl;
			}
			}
			act << "        CMP AX,BX" << endl;
			act << "        ";
			switch (foure[i].idact)
			{
			case 4:
				act << "JA ";
				break;
			case 5:
				act << "JB ";
				break;
			case 6:
				act << "JAE ";
				break;
			case 7:
				act << "JBE ";
				break;
			case 8:
				act << "JNE ";
				break;
			}
		}
		break;
		case 9:
		{
			switch (foure[i].type1)
			{
			case number:
			{
				switch (kind1)
				{
				case fl:
				case in:
				{
					int value = atoi(foure[i].id1);
					char cmp2[15];
					_itoa_s(value, cmp2, 16);
					act << "        MOV " << foure[i].id3 << ",";
					int c0 = 4 - strlen(cmp2);
					while (c0 > 0)
					{
						act << '0';
						c0--;
					}
					act << cmp2 << 'H' << endl;
				}
				break;
				case chars:
					cout << "ERROR:wrong type" << endl;
					getchar();
					exit(1);
				}
			}
			break;
			case ch:
			{
				act << "        MOV " << foure[i].id3 << ",'" << foure[i].id1 << "'" << endl;
			}
			break;
			case id:
				typ1 kind2 = kindget(foure[i].id1);
				switch (kind2)
				{
				case in:
				case fl:
				{
					act << "        MOV AX," << foure[i].id1 << endl;
					act << "        MOV " << foure[i].id3 << ",AX" << endl;
				}
				break;
				case chars:
					act << "        MOV AL," << foure[i].id1 << endl;
					act << "        MOV " << foure[i].id3 << ",AL" << endl;
				}
			}
		}
		break;
		case 10: // if
		{
			act << "else" << elseid << endl;
			act << "if" << ifid++ << ':' << endl;
		}
		break;
		case 11:
		{
			act << "        JMP ifend" << ifendid << endl;
			act << "else" << elseid++ << ":" << endl;
		}
		break;
		case 12: // if end
		{
			actid++;
			act << "ifend" << ifendid++ << ':' << endl;
		}
		break;
		case 13: // while
		{
			act << "whileend" << whileendid << endl;
		}
		break;
		case 14:
		{
			act << "do" << doid++ << ":" << endl;
		}
		break;
		case 15: // while end
		{
			act << "        JMP compare" << actid++ << endl;
			act << "whileend" << whileendid++ << ":" << endl;
		}
		break;
		case 16: // return
		{
			act << "        MOV AH,4CH" << endl;
			act << "        INT 21H" << endl;
		}
		break;
		case 17:
		{
			act << "        MOV CL,16" << endl;
			act << "show" << showid << ':' << endl;
			act << "        SUB CL,04" << endl;
			act << "        MOV AX," << foure[i].id3 << endl;
			act << "        SHR AX,CL" << endl;
			act << "        AND AX,000FH" << endl;
			act << "        MOV DL,AL" << endl;
			act << "        CMP DL,10" << endl;
			act << "        JB  hex" << hexid << endl;
			act << "        ADD DL,07H" << endl;
			act << "hex" << hexid++ << ':' << endl;
			act << "        ADD DL,30H" << endl;
			act << "        MOV AH,02H" << endl;
			act << "        INT 21H" << endl;
			act << "        CMP CL,0" << endl;
			act << "        JNE show" << showid++ << endl;
			act << "        MOV DL,'H'" << endl;
			act << "        MOV AH,02H" << endl;
			act << "        INT 21H" << endl;
			act << "        MOV DL,0AH" << endl;
			act << "        MOV AH,02H" << endl;
			act << "        INT 21H" << endl;
			act << "        MOV DL,0dH" << endl;
			act << "        INT 21H" << endl;
		}
		break;
		case 18:
		{
			act << "        MOV DX,OFFSET string" << endl;
			act << "        MOV AH,09H" << endl;
			act << "        INT 21H" << endl;
			act << "        MOV AH,01" << endl;
			act << "        INT 21H" << endl;
			act << "        SUB AL,30H" << endl;
			act << "        AND AX,00FFH" << endl;
			act << "        MOV " << foure[i].id3 << ",AX" << endl;
			act << "        MOV DL,0AH" << endl;
			act << "        MOV AH,02H" << endl;
			act << "        INT 21H" << endl;
			act << "        MOV DL,0dH" << endl;
			act << "        INT 21H" << endl;
		}
		default:;
		}
	}
	act << "CSEG    ENDS" << endl;
	act << "        END "
		<< "main" << endl;
	act.close();
	cout << "生成的目标代码如下所示" << endl;
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
	char four[] = "fourele.cr";
	std::fstream act(four, ios::out | ios::in);
	int c1 = 3;
	int c2 = 3;
	int i = 0;
	while (!act.eof())
	{
		act >> foure[i].idact;
		act >> foure[i].id1;
		act >> c1;
		foure[i].type1 = (type)c1;
		act >> foure[i].id2;
		act >> c2;
		foure[i].type2 = (type)c2;
		act >> foure[i++].id3;
	}
	act.close();
	actionprep();
	symbolprep();
	CreateTarget();
	cout << "目标代码完成生成，按下任意键结束编译...";
	getchar();
	return;
}
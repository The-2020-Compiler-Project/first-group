DSEG    SEGMENT  
string  DB 'PLEASE INPUT:','$'
cnt     DW 1000 DUP(0)
float   DD 1000 DUP(0)
bool    DB 1000 DUP(0)
char    DB 1000 DUP(0)
DSEG    ENDS
SSEG    SEGMENT STACK
SSEG    ENDS
CSEG    SEGMENT
        ASSUME  CS:CSEG,DS:DSEG
        ASSUME  SS:SSEG
MAIN:
        MOV AX,DSEG
        MOV DS,AX
        MOV AX,SSEG
        MOV SS,AX
        MOV DX,OFFSET string
        MOV AH,09H
        INT 21H
        MOV AH,01
        INT 21H
        SUB AL,30H
        AND AX,00FFH
        MOV i,AX
        MOV DL,0AH
        MOV AH,02H
        INT 21H
        MOV DL,0dH
        INT 21H
        MOV a,11
        MOV d,2
compare0:   
        MOV AX,a
        MOV BX,d
        CMP AX,BX
        JBE else0
if0:
        MOV AX,a
        ADD AX,d
        MOV r,AX
        MOV AX,d
        MOV SI,OFFSET a
        DIV BYTE PTR [SI]
        AND AH,00H
        MOV lo,AX
        JMP end0
else0:
        MOV SI,OFFSET a
        MOV AL,BYTE PTR [SI]
        MOV SI,OFFSET a
        MUL BYTE PTR [SI]
        MOV t3,AX
        MOV AX,a
        ADD AX,t3
        MOV s,AX
end0:
compare1:   
        MOV AX,i
        MOV BX,10
        CMP AX,BX
        JB whileend0
do0:
        MOV AX,i
        ADD AX,1
        MOV i,AX
        JMP compare1
whileend0:
        MOV CL,16
show0:
        SUB CL,04
        MOV AX,r
        SHR AX,CL
        AND AX,000FH
        MOV DL,AL
        CMP DL,10
        JB  hex0
        ADD DL,07H
hex0:
        ADD DL,30H
        MOV AH,02H
        INT 21H
        CMP CL,0
        JNE show0
        MOV DL,'H'
        MOV AH,02H
        INT 21H
        MOV DL,0AH
        MOV AH,02H
        INT 21H
        MOV DL,0dH
        INT 21H
        MOV AH,4CH
        INT 21H
CSEG    ENDS
        END MAIN


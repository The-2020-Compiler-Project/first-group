DSEG    SEGMENT  
i       DW 0
a       DW 0
d       DW 0
t0      DB 0
r       DW 0
lo      DW 0
t3      DW 0
t6      DB 0
string  DB 'PLEASE INPUT:','$'
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
        MOV DL,0DH
        INT 21H
        MOV a,2
        MOV d,11
compare0:   
        MOV AX,a
        MOV BX,d
        CMP AX,BX
        JAE else0
if0:
        MOV AX,a
        ADD AX,d
        MOV r,AX
        MOV AX,5
        MOV SI,OFFSET a
        DIV BYTE PTR [SI]
        AND AH,00H
        MOV lo,AX
        JMP ifend0
else0:
        MOV SI,OFFSET a
        MOV AL,BYTE PTR [SI]
        MOV SI,OFFSET a
        MUL BYTE PTR [SI]
        MOV t3,AX
        MOV AX,a
        ADD AX,t3
        MOV r,AX
        MOV SI,OFFSET a
        MOV AL,BYTE PTR [SI]
        MOV SI,OFFSET a
        MUL BYTE PTR [SI]
        MOV lo,AX
ifend0:
compare1:   
        MOV AX,i
        MOV BX,10
        CMP AX,BX
        JA whileend0
do0:
        MOV AX,i
        ADD AX,1
        MOV i,AX
        JMP compare1
whileend0:
        MOV CL,16
cout0:
        SUB CL,04
        MOV AX,lo
        SHR AX,CL
        AND AX,000FH
        MOV DL,AL
        CMP DL,10
        JB  couth0
        ADD DL,07H
couth0:
        ADD DL,30H
        MOV AH,02H
        INT 21H
        CMP CL,0
        JNE cout0
        MOV DL,'H'
        MOV AH,02H
        INT 21H
        MOV DL,0AH
        MOV AH,02H
        INT 21H
        MOV DL,0DH
        INT 21H
        MOV CL,16
cout1:
        SUB CL,04
        MOV AX,i
        SHR AX,CL
        AND AX,000FH
        MOV DL,AL
        CMP DL,10
        JB  couth1
        ADD DL,07H
couth1:
        ADD DL,30H
        MOV AH,02H
        INT 21H
        CMP CL,0
        JNE cout1
        MOV DL,'H'
        MOV AH,02H
        INT 21H
        MOV DL,0AH
        MOV AH,02H
        INT 21H
        MOV DL,0DH
        INT 21H
        MOV AH,4CH
        INT 21H
CSEG    ENDS
        END MAIN

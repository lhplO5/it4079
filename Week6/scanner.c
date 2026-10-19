#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"

TokenType Token;
int		  Num;
char	  Id[MAX_IDENT_LEN + 1];

FILE * f;
int ch;

TokenType checkKeyword(char * str){
	int i;
	//TODO -> ok 
	for (i = 0; i < KEYWORDS_COUNT; i++) {
        if (strcmp(str, keywords[i].string) == 0)
            return keywords[i].Token;
    }
	return TK_IDENT;
}

// char getCh(){
//   return toupper(fgetc(f));
// }
int getCh() {
    int c = fgetc(f);
    return (c == EOF) ? EOF : toupper((unsigned char)c);
}

TokenType getToken(){
	int i;
	int c; 

	//q_0 -> q_0
	// loop skip white space 
	while (ch != EOF && isspace((unsigned char)ch)) ch = getCh(); //dau phan cach
	if (ch == EOF)
		return TK_NONE; 
	// q_0 -letter> q_1 - letter/number ->q1
	if( isalpha(ch)){		//bat dau la mot chu cai
		i = 0; 
		while (isalnum((unsigned char)ch)) {
            if (i < MAX_IDENT_LEN)
                Id[i++] = ch;
            ch = getCh();
        }
		Id[i] = '\0';
		return checkKeyword(Id);

	}
	// q_0 -number> q_2 - number ->q2

	else if( isdigit(ch)){  //bat dau la mot chu so
		//TODO
		i = 0; 
		Num = 0; 
		while (isdigit((unsigned char)ch)) {
            if (i < MAX_NUMBER_LEN)
                Num = Num * 10 + (ch - '0');
            i++;
            ch = getCh();        
		}
		if (i > MAX_NUMBER_LEN)
            printf("so qua lon, toi da %d chu so\n", MAX_NUMBER_LEN);
		return TK_NUMBER;		//chu y canh bao: so qua lon
	}
	// q_0 -':'> q_3 - '=' ->q4

	 else if (ch == ':') {   //doan nhan tu vung :=
		ch = getCh();
		if(ch == '='){
			ch = getCh();
			return SB_ASSIGN;
		}
		return TK_NONE;
	}else {
			// q_0 - cac dau con lai -> q_....

        switch (ch) {
            case '+': ch = getCh(); return SB_PLUS;
            case '-': ch = getCh(); return SB_MINUS;
            case '*': ch = getCh(); return SB_TIMES;
            case '/': ch = getCh(); return SB_SLASH;
            case '=': ch = getCh(); return SB_EQU;
            case '#': ch = getCh(); return SB_NEQ;
            case '<':
                ch = getCh();
                if (ch == '=') {
                    ch = getCh();
                    return SB_LEQ;
                }
                return SB_LSS;
            case '>':
                ch = getCh();
                if (ch == '=') {
                    ch = getCh();
                    return SB_GEQ;
                }
                return SB_GTR;
            case '%': ch = getCh(); return SB_PERCENT;
            case '(': ch = getCh(); return SB_LPARENT;
            case ')': ch = getCh(); return SB_RPARENT;
            case '[': ch = getCh(); return SB_LBRACK;
            case ']': ch = getCh(); return SB_RBRACK;
            case '.': ch = getCh(); return SB_PERIOD;
            case ',': ch = getCh(); return SB_COMMA;
            case ';': ch = getCh(); return SB_SEMICOLON;
            default:
                ch = getCh();
                return TK_NONE;
		}
	}
}


void compile(char *filename) {
    if ((f = fopen(filename, "rt")) == NULL) {
        printf("File %s not found\n", filename);
        return;
    }

    ch = ' ';

    do {
        Token = getToken();
        printf(" %s", TabToken[Token]);

        if (Token == TK_IDENT)
            printf("(%s)\n", Id);
        else if (Token == TK_NUMBER)
            printf("(%d)\n", Num);
        else
            printf("\n");

    } while (Token != TK_NONE);

    fclose(f);
}

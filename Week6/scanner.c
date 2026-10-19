#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"

TokenType Token;
int		  Num;
char	  Id[MAX_IDENT_LEN + 1];

FILE * f;
char ch;

TokenType checkKeyword(char * str){
	int i;
	//TODO
	return TK_IDENT;
}

char getCh(){
  return toupper(fgetc(f));
}

TokenType getToken(){
	//TODO

	while((ch==' ') || ch=='\n' || (ch=='\t')) ch = getCh(); //dau phan cach

	if( isalpha(ch)){		//bat dau la mot chu cai
		//TODO
		//............
		return checkKeyword(Id);
	}else if( isdigit(ch)){  //bat dau la mot chu so
		//TODO
		//............
		return TK_NUMBER;		//chu y canh bao: so qua lon
	} else if (ch == ':') {   //doan nhan tu vung :=
		//TODO
		//............
		return SB_ASSIGN;
	}else {
		//TODO
		//............
		return TK_NONE;
	}
}


void compile(char * filename){
  	if((f = fopen(filename,"rt")) == NULL) printf("File %s not found",filename);
  	else{
		ch =' ';
		do{
		 	Token = getToken();
			printf(" %s",TabToken[Token]);
			if(Token == TK_IDENT) printf("(%s) \n",Id);
			else if(Token == TK_NUMBER) printf("(%d) \n",Num);
			else printf("\n");
		}while(Token != TK_NONE);
	}
  fclose(f);
}

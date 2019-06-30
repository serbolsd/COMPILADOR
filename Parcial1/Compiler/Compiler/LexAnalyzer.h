#pragma once
#include <Windows.h>
#include <vcclr.h>
#include "ErrorsModule.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "Token.h"


using namespace System;


namespace Compiler {
#define LEX_INVALID_CHAR "invalid character"
#define LEX_STRING_NOT_CLOSED "string not closed"
#define LEX_COMMENT_NOT_CLOSED "comment not closed"
#define LEX_INVALID_FLOAT "invalid float"
#define LEX_INVALID_INT "invalid int"
#define LEX_INVALID_OP_LOG "invalid operator logical"

	public class LexAnalyzer
	{
	public:
		LexAnalyzer();
		~LexAnalyzer();
		LexAnalyzer(ErrorsModule^erromod);
		bool parseSourceCode(const char*src);
		msclr::gcroot<ErrorsModule^>m_refErrorsMod;
	private:
		ERROR_PHASE m_phase = ERROR_PHASE::LEX_ANALYZER;
		//ErrorsModule m_refErrorsMod;
		int m_numeberLine=0;
		std::map<std::string, std::string> m_keyWords;
		std::vector<Token*> m_Tokens;
		void letrasParse(const char*src,int&i);
		void numParse(const char*src,int&i);
		void floatParse(const char*src,int&i, std::string str = "");
		void comentaryOneLineParse(const char*src,int&i);
		void comentaryMoreLineParse(const char*src,int&i);
		void stringParse(const char*src,int&i);
		void detecteToken(std::string lexema,int type);
		std::vector<char> separators = { ';',':',',' };
		//std::vector<char> digit = { '0','1','2', };
		std::vector <char> op_arit = { '+','-','*','/','%' };
		std::vector <char> op_dim = { '{','}','(',')','[',']' };
		std::vector <char> op_log = { '!','|','&','=' };
		std::vector <char> op_arit_inv = { '^'};
		std::vector <std::string> op_logComplete = { "!","||","&&","==" };
		std::string equidad = { "=" };
		std::vector <std::string> m_keyword = { "main","var", "int","float","string","bool","void","function","for","while","if","else","switch","case","default","print","read","return","true","flase","inc","dec" };
		std::vector <char> m_invalid_simbolos = { '#','$','@','ñ','Ñ','~', '¼' };
		char space = ' ';
	public:
		void clearTokens();
		//bool parseSourceCode(const char* src);
		void getTokens(std::vector<Token*>*tokensVec);
		Token* getNextToken();
		Token* getPrevToken();
		Token* peeckToken(int idx);
		void addToken(std::string lex, int lineNum, TOKEN_TYPE tp);
		String^ getTokensList();
	};

}

#include "stdafx.h"
#include "Token.h"

Compiler::Token::Token(std::string lex, TOKEN_TYPE tp, int lineNum)
{
	m_lex=lex;
	m_Type = tp;
	m_lineNumber = lineNum;

}

Compiler::Token::~Token()
{
	m_lex.clear();
}

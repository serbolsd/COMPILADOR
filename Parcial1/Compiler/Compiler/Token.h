#pragma once
#include <iostream>
#include <string>
using namespace System;
namespace Compiler
{
	enum TOKEN_TYPE
	{
		UNDEFINDED=0,
		KEYWORD,
		ID,
		INT,
		FLOAT,
		LOGIC_OPERATOR,
		ARITMETIC_OPERATOR,
		DIMENCIONAL_OPERATO,
		ASIGNATION,
		SEPARATOR,
		STRING,
		COMENTARY
		//AGREGAR TODOS LOS TIPOS
	};
	class Token
	{
	public:
		Token(std::string lex, TOKEN_TYPE tp, int lineNum);
		~Token();
	private:
		std::string m_lex;
		int m_lineNumber;
		TOKEN_TYPE m_Type;
	public:
		std::string getLex() const { return m_lex;};
		int getType() const { return m_Type; };
		int getLineNumber() const { return m_lineNumber; };

	};
	
}


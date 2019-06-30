#pragma once
#include "Syntax_State.h"
namespace Compiler
{
	//Compiler::Token * t = m_lex->getNextToken();
	class Syntax_State_Function :Syntax_State
	{
	public:
		Syntax_State_Function(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Function();
		void checkSyntax();
	};
}


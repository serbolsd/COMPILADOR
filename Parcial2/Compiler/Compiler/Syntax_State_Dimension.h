#pragma once
#include "Header.h"
#include "Syntax_State.h"
#include "Token.h"
namespace Compiler
{
	class Syntax_State_Dimension:Syntax_State
	{
	public:
		Syntax_State_Dimension(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Dimension();
		void checkSyntax();
	};
}

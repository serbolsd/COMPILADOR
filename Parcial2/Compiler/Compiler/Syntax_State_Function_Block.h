#pragma once
#include "Syntax_State.h"
namespace Compiler
{
	class Syntax_State_Function_Block:Syntax_State
	{
	public:
		Syntax_State_Function_Block(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Function_Block();
		void checkSyntax();
	};
}


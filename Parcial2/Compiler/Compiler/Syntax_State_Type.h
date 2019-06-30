#pragma once
#include "Syntax_State.h"
namespace Compiler
{
	class Syntax_State_Type :Syntax_State
	{
	public:
		Syntax_State_Type(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntax_State_Type();
		void checkSyntax();
	};
}
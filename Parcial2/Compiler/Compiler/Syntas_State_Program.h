#pragma once
#include "Header.h"
#include "Syntax_State.h"
#include "Token.h"
namespace Compiler
{
	class Syntas_State_Program:Syntax_State
	{
	private:

	public:
		Syntas_State_Program(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName);
		~Syntas_State_Program();
		void checkSyntax();
	};
}

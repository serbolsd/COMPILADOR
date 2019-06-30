#pragma once
#include "SyntaxAnalysis.h"
namespace Compiler
{
	class Syntax_State
	{
	private:
		//SymbolTable * m_stab;
	public:
		LexAnalyzer *m_lex;
		SyntaxAnalysis *m_syn;
		Syntax_State * m_parent;
		std::string m_stateName;
		Syntax_State();
		Syntax_State(LexAnalyzer *lex, SyntaxAnalysis *syn, Syntax_State *parent, std::string m_stateName);
		~Syntax_State();
		void checkSyntax();
	};
}

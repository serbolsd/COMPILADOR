#include "stdafx.h"
#include "Syntax_State.h"


Compiler::Syntax_State::Syntax_State()
{
}

Compiler::Syntax_State::Syntax_State(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
{
	m_lex = lex;
	m_syn = syn;
	m_parent = parent;
	m_stateName = stateName;
}

Compiler::Syntax_State::~Syntax_State()
{
	delete m_lex;
	delete m_syn;
	delete m_parent;
}

void Compiler::Syntax_State::checkSyntax()
{
}

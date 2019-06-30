#include "stdafx.h"
#include "Syntax_State_Function_Block.h"
#include "Syntax_State_Var.h"
#include "Syntax_State_Dimension.h"
#include "Syntax_State_Type.h"
#include "Syntax_State_BlockVar.h"
#include <sstream>



Compiler::Syntax_State_Function_Block::Syntax_State_Function_Block(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{
}

Compiler::Syntax_State_Function_Block::~Syntax_State_Function_Block()
{
}

void Compiler::Syntax_State_Function_Block::checkSyntax()
{
	bool conti = true;
	Compiler::Token*t = m_lex->getNextToken();
	int index = m_lex->m_tokensIndex;
	while (conti)
	{
		if (t->getLex()=="}")
		{
			conti = false;
			break;
		}
		else if (t==nullptr)
		{
			//agregar error
			return;
		}
		t = m_lex->getNextToken();
	}
	t=m_lex->setIndexToken(index);
	conti = true;
	while (conti)
	{
		if (t == nullptr)
		{
			conti = false;
			break;
		}
		if (t != nullptr &&t->getType() != ID)
		{
			//AGRAGAR ERROR
		}
		if (t->getLex()=="var")
		{
			Syntax_State_BlockVar *BV = new Syntax_State_BlockVar(m_lex,m_syn,m_parent,m_stateName);
			BV->checkSyntax();
			t = m_lex->getNextToken();
			t = m_lex->getPrevToken();
		}
		if (t->getLex() == "}")
		{
			//t = m_lex->getNextToken();
			conti = false;
			break;
		}
		t = m_lex->getNextToken();
	}
}

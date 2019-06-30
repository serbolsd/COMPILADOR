#include "stdafx.h"
#include "Syntax_State_Var.h"
#include "Syntax_State_Dimension.h"
#include "Syntax_State_Type.h"

Compiler::Syntax_State_Var::Syntax_State_Var(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{
}

Compiler::Syntax_State_Var::~Syntax_State_Var()
{
}

void Compiler::Syntax_State_Var::checkSyntax()
{
	bool conti = true;
	while (conti)
	{

		Compiler::Token*t = m_lex->getNextToken();
		if (t==nullptr)
		{
			conti = false;
			break;
		}
		if (t!=nullptr &&t->getType()!=ID)
		{
			//AGRAGAR ERROR
		}
		else if(t != nullptr)
		{
			m_syn->m_IDs.push_back(t->getLex());
			m_syn->linea.push_back(t->getLineNumber());
			t = m_lex->getNextToken();
			//si es [ pasar al estado de dimencion
		}
		//t = m_lex->getNextToken();
		if (t != nullptr &&t->getLex()=="[")
		{
			Syntax_State_Dimension* dim = new Syntax_State_Dimension(m_lex,m_syn,m_parent,m_stateName);
			dim->checkSyntax();
			t = m_lex->getNextToken();
			t = m_lex->getNextToken();
		}
		else
		{
			m_syn->m_Dimension.push_back("0");
		}
		if (t != nullptr &&t->getLex() == ":")
		{
			Syntax_State_Type*typ = new Syntax_State_Type(m_lex, m_syn, m_parent, m_stateName);
			typ->checkSyntax();
			return;
		}
		if (t != nullptr &&t->getLex()!=":"&&t->getLex() != ",")
		{
			if (t->getLex() == ";")
			{
				conti = false;
				break;
			}
			//aregar error
			return;
		}
		
	}
	
}
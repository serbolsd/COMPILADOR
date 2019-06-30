#include "stdafx.h"
#include "Syntax_State_Main.h"
#include "Syntax_State_Params.h"
#include "Syntax_State_Type.h"
#include "Syntax_State_Dimension.h"
#include "Syntax_State_MainParams.h"
#include "Syntax_State_Function_Block.h"


Compiler::Syntax_State_Main::Syntax_State_Main(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	: Syntax_State(lex, syn, parent, stateName)
{
}

Compiler::Syntax_State_Main::~Syntax_State_Main()
{
}

void Compiler::Syntax_State_Main::checkSyntax()
{
	m_syn->category = Compiler::ESYMBOL_CAT::LOCAL_VAR;
	m_syn->function = "main";
	m_syn->category = Compiler::ESYMBOL_CAT::PARAMETER;
	Compiler::Token * t = m_lex->getNextToken();
	bool conti = true;
	while (conti)
	{
		if (t == nullptr)
		{
			break;
		}
		if (t != nullptr &&t->getType() != ID)
		{
			//AGRAGAR ERROR
		}
		if (t != nullptr &&t->getLex() == "(")
		{
			m_syn->function = "main";
			Syntax_State_MainParams * mparm = new Syntax_State_MainParams(m_lex, m_syn, m_parent, m_stateName);
			mparm->checkSyntax();
			m_syn->cleanParams();
			t = m_lex->getNextToken();
		}

		if (t != nullptr &&t->getLex() == "{")
		{
			m_syn->function = "main";
			m_syn->category = Compiler::ESYMBOL_CAT::LOCAL_VAR;
			Syntax_State_Function_Block *fBlock = new Syntax_State_Function_Block(m_lex, m_syn, m_parent, m_stateName);
			fBlock->checkSyntax();
			m_syn->cleanLocal();
			t = m_lex->getNextToken();
			t = m_lex->getPrevToken();
		}
		if (t != nullptr &&t->getLex() != ":")
		{
			if (t->getLex() == "}")
			{
				t = m_lex->getNextToken();
				break;
			}
			//aregar error
			return;
		}
		t = m_lex->getNextToken();

	}
}

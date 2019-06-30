#include "stdafx.h"
#include "Syntas_State_Program.h"
#include "Syntax_State_Var.h"
#include "Syntax_State_Function.h"
#include "Syntax_State_Main.h"


Compiler::Syntas_State_Program::Syntas_State_Program(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex,syn,parent,stateName)
{
}

Compiler::Syntas_State_Program::~Syntas_State_Program()
{
}



void Compiler::Syntas_State_Program::checkSyntax()
{
	bool contin = true;
	Compiler::Token * t=m_lex->getNextToken();
	while (contin)
	{
		std::string st = t->getLex();
		if(t != nullptr &&t->getLex()=="var")
		{
			m_syn->category = Compiler::ESYMBOL_CAT::GLOBAL_VAR;
			Syntax_State_Var *var=new Syntax_State_Var(m_lex,m_syn,m_parent,m_stateName);
			var->checkSyntax();
			t = m_lex->getNextToken();
			if (t== nullptr)
			{
				contin = false;
				break;
			}
			m_syn->cleanIDs();
			m_syn->cleanLocal();
			m_syn->cleanParams();
		}
		if (t != nullptr &&t->getLex()=="function")
		{
			m_syn->category = Compiler::ESYMBOL_CAT::FUNCTION;
			Syntax_State_Function* func = new Syntax_State_Function(m_lex, m_syn, m_parent, m_stateName);
			func->checkSyntax();
			t = m_lex->getNextToken();
			t = m_lex->getPrevToken();
			if (t == nullptr)
			{
				contin = false;
				break;
			}
			m_syn->cleanIDs();
			m_syn->cleanLocal();
			m_syn->cleanParams();

		}
		if (t != nullptr &&t->getLex() == "main")
		{
			//m_syn->category = Compiler::ESYMBOL_CAT::FUNCTION;
			Syntax_State_Main* ma = new Syntax_State_Main(m_lex, m_syn, m_parent, m_stateName);
			ma->checkSyntax();
			t = m_lex->getNextToken();
			if (t == nullptr)
			{
				contin = false;
				break;
			}
			m_syn->cleanIDs();
			m_syn->cleanLocal();
			m_syn->cleanParams();

		}
		if (t == nullptr)
		{
			break;
		}

	}
	m_syn->cleanIDs();
	m_syn->cleanLocal();
	m_syn->cleanParams();
}

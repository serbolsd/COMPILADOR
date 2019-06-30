#include "Header.h"
#include "Syntax_State.h"
#include "stdafx.h"
#include "Syntax_State_Function.h"
#include "Syntax_State_Var.h"
#include "Syntax_State_Params.h"
#include "Syntax_State_Type.h"
#include "Syntax_State_Function_Block.h"
#include "Token.h"


Compiler::Syntax_State_Function::Syntax_State_Function(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{

}

Compiler::Syntax_State_Function::~Syntax_State_Function()
{
}

void Compiler::Syntax_State_Function::checkSyntax()
{
	Compiler::Token * t = m_lex->getNextToken();
	while (t != nullptr)
	{
		if (t == nullptr)
		{
			break;
		}
		if (t != nullptr &&t->getType() != ID)
		{
			//AGRAGAR ERROR
		}
		else if (t != nullptr)
		{
			m_syn->m_IDs.push_back(t->getLex());
			m_syn->linea.push_back(t->getLineNumber());
			t = m_lex->getNextToken();
			//si es [ pasar al estado de dimencion
		}
		//t = m_lex->getNextToken();
		m_syn->m_Dimension.push_back("0");
		if (t != nullptr &&t->getLex() == "(")
		{
			m_syn->function = m_syn->m_IDs[0];
			Syntax_State_Params * parm = new Syntax_State_Params(m_lex, m_syn, m_parent, m_stateName);
			parm->checkSyntax();
			m_syn->cleanParams();
			t = m_lex->getNextToken();
		}
		if (t != nullptr &&t->getLex() == ":")
		{
			m_syn->category = Compiler::ESYMBOL_CAT::FUNCTION;
			Syntax_State_Type*typ = new Syntax_State_Type(m_lex, m_syn, m_parent, m_stateName);
			typ->checkSyntax();
		}
		if (t != nullptr &&t->getLex() == "{")
		{
			m_syn->function = m_syn->m_IDs[0];
			m_syn->category = Compiler::ESYMBOL_CAT::LOCAL_VAR;
			Syntax_State_Function_Block *fBlock= new Syntax_State_Function_Block(m_lex, m_syn, m_parent, m_stateName);
			fBlock->checkSyntax();
			t = m_lex->getNextToken();
			t = m_lex->getPrevToken();
			m_syn->cleanLocal();
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

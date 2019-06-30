#include "stdafx.h"
#include "Syntax_State_Params.h"
#include "Syntax_State_Type.h"
#include "Syntax_State_Dimension.h"


Compiler::Syntax_State_Params::Syntax_State_Params(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{
}

void Compiler::Syntax_State_Params::checkSyntax()
{
	m_syn->category = Compiler::ESYMBOL_CAT::PARAMETER;
	bool conti = true;
	while (conti)
	{

		Compiler::Token*t = m_lex->getNextToken();
		if (t == nullptr)
		{
			conti = false;
			break;
		}
		if (t != nullptr &&t->getType() != ID)
		{
			//AGRAGAR ERROR
			// NOT VALID PARAM
		}
		else if (t != nullptr)
		{
			m_syn->m_ParamsIDs.push_back(t->getLex());
			m_syn->lineaParams.push_back(t->getLineNumber());
			t = m_lex->getNextToken();
			//si es [ pasar al estado de dimencion
		}
		//t = m_lex->getNextToken();
		if (t != nullptr &&t->getLex() == "[")
		{
			Syntax_State_Dimension* dim = new Syntax_State_Dimension(m_lex, m_syn, m_parent, m_stateName);
			dim->checkSyntax();
			t = m_lex->getNextToken();
			t = m_lex->getNextToken();
		}
		else
		{
			m_syn->m_DimensionParams.push_back("0");
		}
		if (t != nullptr &&t->getLex() == ":")
		{
			Syntax_State_Type*typ = new Syntax_State_Type(m_lex, m_syn, m_parent, m_stateName);
			typ->checkSyntax();
			t = m_lex->getNextToken();
		}
		if (t != nullptr&&t->getLex() == ")")
		{
			
			return;
			break;
		}
		if (t != nullptr &&t->getLex() != ":"&&t->getLex() != ","&&t->getType() != ID)
		{

			//aregar error
			return;
		}

	}
}

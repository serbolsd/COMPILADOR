#include "stdafx.h"
#include "Syntax_State_Dimension.h"
#include "Syntax_State.h"
#include <cstdlib>

Compiler::Syntax_State_Dimension::Syntax_State_Dimension(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{
}

Compiler::Syntax_State_Dimension::~Syntax_State_Dimension()
{
}

void Compiler::Syntax_State_Dimension::checkSyntax()
{
	if (m_syn->category==Compiler::ESYMBOL_CAT::PARAMETER)
	{
		Compiler::Token*t = m_lex->getNextToken();
		if (t->getType() != Compiler::TOKEN_TYPE::INT)
		{
			// Agregar Error
			m_syn->m_ParamsIDs.pop_back();
			m_syn->m_DimensionParams.pop_back();
			m_syn->lineaParams.pop_back();
			return;
		}
		int n = std::atoi(t->getLex().c_str());
		if (n<0)
		{
			//agregar error;
			m_syn->m_ParamsIDs.pop_back();
			m_syn->m_DimensionParams.pop_back();
			m_syn->lineaParams.pop_back();
			return;
		}
		m_syn->m_DimensionParams.push_back(t->getLex());
		return;
	}
	else if (m_syn->category == Compiler::ESYMBOL_CAT::LOCAL_VAR)
	{
		Compiler::Token*t = m_lex->getNextToken();
		if (t->getType() != Compiler::TOKEN_TYPE::INT)
		{
			// Agregar Error
			return;
		}
		int n = std::atoi(t->getLex().c_str());
		if (n < 0)
		{
			//agregar error;
			m_syn->m_LocalIDs.pop_back();
			m_syn->m_LocalDimension.pop_back();
			m_syn->lineaLocal.pop_back();
			return;
		}
		m_syn->m_LocalDimension.push_back(t->getLex());
		return;
	}
	else
	{
		Compiler::Token*t = m_lex->getNextToken();
		if (t->getType()!=Compiler::TOKEN_TYPE::INT)
		{
			// Agregar Error
			m_syn->m_IDs.pop_back();
			m_syn->m_Dimension.pop_back();
			m_syn->linea.pop_back();
			return;
		}
		int n = std::atoi(t->getLex().c_str());
		if (n < 0)
		{
			//agregar error;
			m_syn->m_IDs.pop_back();
			m_syn->m_Dimension.pop_back();
			m_syn->linea.pop_back();
			return;
		}
		m_syn->m_Dimension.push_back(t->getLex());
		return;

	}
}

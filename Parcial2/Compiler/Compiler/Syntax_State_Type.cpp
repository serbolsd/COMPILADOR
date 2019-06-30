#include "stdafx.h"
#include "Syntax_State_Type.h"
#include "Syntax_State.h"
#include <sstream>



Compiler::Syntax_State_Type::Syntax_State_Type(LexAnalyzer * lex, SyntaxAnalysis * syn, Syntax_State * parent, std::string stateName)
	:Syntax_State(lex, syn, parent, stateName)
{
}

Compiler::Syntax_State_Type::~Syntax_State_Type()
{
}

void Compiler::Syntax_State_Type::checkSyntax()
{
	Compiler::Token*t = m_lex->getNextToken();
	if (t->getLex() == "int")
	{
		m_syn->tipe="int";
	}
	else if (t->getLex() == "float")
	{
		m_syn->tipe = "float";

	}
	else if (t->getLex() == "string")
	{
		m_syn->tipe = "string";
	}
	else if (t->getLex() == "bool")
	{
		m_syn->tipe = "bool";
	}
	else
	{
		// Agregar Error
		return;
	}
	if (m_syn->category == Compiler::ESYMBOL_CAT::PARAMETER)
	{
		for (int i = 0; i < m_syn->m_ParamsIDs.size(); i++)
		{
			int number;
			std::istringstream iss(m_syn->m_DimensionParams[i]);
			iss >> number;
			if (m_syn->m_stab->addSymbol(m_syn->lineaParams[i], m_syn->m_ParamsIDs[i], number, m_syn->category, m_syn->function, m_syn->tipe))
			{

			}
			else
			{
				//agregar error de agregado de symbolo
			}
		}
		m_syn->m_ParamsIDs.clear();
		m_syn->m_DimensionParams.clear();
		m_syn->lineaParams.clear();
		return;
	}
	else if (m_syn->category == Compiler::ESYMBOL_CAT::LOCAL_VAR)
	{
		for (int i = 0; i < m_syn->m_LocalIDs.size(); i++)
		{
			int number;
			std::istringstream iss(m_syn->m_LocalDimension[i]);
			iss >> number;
			if (m_syn->m_stab->addSymbol(m_syn->lineaLocal[i], m_syn->m_LocalIDs[i], number, m_syn->category, m_syn->function, m_syn->tipe))
			{

			}
			else
			{
				//agregar error de agregado de symbolo
			}
		}
		m_syn->m_ParamsIDs.clear();
		m_syn->m_DimensionParams.clear();
		m_syn->lineaParams.clear();
		return;
	}
	else if (m_syn->category == Compiler::ESYMBOL_CAT::FUNCTION)
	{
		for (int i = 0; i < m_syn->m_IDs.size(); i++)
		{
			int number;
			std::istringstream iss(m_syn->m_Dimension[i]);
			iss >> number;
			if (m_syn->m_stab->addSymbol(m_syn->linea[0], m_syn->m_IDs[0], number, Compiler::ESYMBOL_CAT::FUNCTION, "<GLOBAL SCOPE>", m_syn->tipe))
			{

			}
			else
			{
				//agregar error de agregado de symbolo
			}
		}
	}
	else
	{
		t = m_lex->getNextToken();
		if (t->getLex() == ";")
		{
			for (int i = 0; i < m_syn->m_IDs.size(); i++)
			{
				int number;
				std::istringstream iss(m_syn->m_Dimension[i]);
				iss >> number;
				if (m_syn->m_stab->addSymbol(m_syn->linea[i],m_syn->m_IDs[i], number, m_syn->category,m_syn->function,m_syn->tipe))
				{

				}
				else
				{
					//agregar error de agregado de symbolo
				}
			}
			return;
		}
		else
		{
			// Agregar error
		}
	}
}

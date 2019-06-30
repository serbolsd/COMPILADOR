#include "stdafx.h"
#include "SyntaxAnalysis.h"
#include "Syntax_State.h"
#include "Syntas_State_Program.h"
#include <Windows.h>
#include <vcclr.h>
#include "ErrorsModule.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "Token.h"

Compiler::SyntaxAnalysis::SyntaxAnalysis(LexAnalyzer *lex, ErrorsModule ^err, SymbolTable * stab)
{
	m_lex = lex;
	m_err = err;
	m_stab = stab;
}

Compiler::SyntaxAnalysis::~SyntaxAnalysis()
{
}

void Compiler::SyntaxAnalysis::checkSyntax(SyntaxAnalysis * syn)
{
	Syntas_State_Program * prog = new Syntas_State_Program(m_lex,syn,nullptr,"program");
	prog->checkSyntax();
}

void Compiler::SyntaxAnalysis::cleanIDs()
{
	m_IDs.clear();
	m_Dimension.clear();
	linea.clear();
	function = "<GLOBAL SCOPE>";
	tipe ="<UNKNOW>";
	category = ESYMBOL_CAT::GLOBAL_VAR;
}

void Compiler::SyntaxAnalysis::cleanParams()
{
	m_ParamsIDs.clear();
	m_DimensionParams.clear();
	lineaParams.clear();
	function = "<GLOBAL SCOPE>";
	tipe = "<UNKNOW>";
	category = ESYMBOL_CAT::GLOBAL_VAR;
}

void Compiler::SyntaxAnalysis::cleanLocal()
{
	m_LocalIDs.clear();
	m_LocalDimension.clear();
	lineaLocal.clear();
	function = "<GLOBAL SCOPE>";
	tipe = "<UNKNOW>";
	category = ESYMBOL_CAT::GLOBAL_VAR;
}

String^ Compiler::SyntaxAnalysis::getSymbolTable()
{
	String^ str;
	for (int i = 0; i <m_stab->m_symbols.size(); i++)
	{

			if (m_stab->m_symbols[i]->getType() != "<UNKNOW>")
			{
				str += m_stab->m_symbols[i]->getLine().ToString();
				str += "\n";
				str += gcnew String(m_stab->m_symbols[i]->getSymbol().c_str());
				str += "\n";
				switch (m_stab->m_symbols[i]->getCat())
				{
				case Compiler::ESYMBOL_CAT::UNDEFINE:
					str += "UNDEFINE";
					break;
				case Compiler::ESYMBOL_CAT::GLOBAL_VAR:
					str += "GLOBAL_VAR";
					break;
				case Compiler::ESYMBOL_CAT::LOCAL_VAR:
					str += "LOCAL_VAR";
					break;
				case Compiler::ESYMBOL_CAT::PARAMETER:
					str += "PARAMETER";
					break;
				case Compiler::ESYMBOL_CAT::FUNCTION:
					str += "FUNCTION";
					break;
				default:
					break;
				}
				str += "\n";
				str += m_stab->m_symbols[i]->getDim().ToString();
				str += "\n";
				str += gcnew String(m_stab->m_symbols[i]->getType().c_str());
				str += "\n";
				str += gcnew String(m_stab->m_symbols[i]->getFunction().c_str());
				str += "\n";
			}
			else
			{

			}
			Compiler::LocalNode *ln = m_stab->m_symbols[i]->getNodolocal();
			while (ln!=nullptr)
			{
				str += ln->getLine().ToString();
				str += "\n";
				str += gcnew String(m_stab->m_symbols[i]->getSymbol().c_str());
				str += "\n";
				switch (ln->getCat())
				{
				case Compiler::ESYMBOL_CAT::UNDEFINE:
					str += "UNDEFINE";
					break;
				case Compiler::ESYMBOL_CAT::GLOBAL_VAR:
					str += "GLOBAL_VAR";
					break;
				case Compiler::ESYMBOL_CAT::LOCAL_VAR:
					str += "LOCAL_VAR";
					break;
				case Compiler::ESYMBOL_CAT::PARAMETER:
					str += "PARAMETER";
					break;
				case Compiler::ESYMBOL_CAT::FUNCTION:
					str += "FUNCTION";
					break;
				default:
					break;
				}
				str += "\n";
				str += ln->getDim().ToString();
				str += "\n";
				str += gcnew String(ln->getType().c_str());
				str += "\n";
				str += gcnew String(ln->getFunc().c_str());
				str += "\n";
				ln = ln->getNodolocal();
			}
	}
	return str;
}

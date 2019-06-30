#include "stdafx.h"
#include "SymbolTable.h"


Compiler::SymbolTable::SymbolTable()
{
}

Compiler::SymbolTable::~SymbolTable()
{
}

void Compiler::SymbolTable::getAllSymbols()
{
}

bool Compiler::SymbolTable::addSymbol(int lineNum,std::string sym, int dim, ESYMBOL_CAT cat, std::string func, std::string tp)
{
	bool esto = symbolExists(sym, cat, func);
	if (!esto)
	{
		if (cat == ESYMBOL_CAT::GLOBAL_VAR)
		{
			GlobalNode* newGlobal = new GlobalNode();
			newGlobal->setLine(lineNum);
			newGlobal->setSymbol(sym);
			newGlobal->setDim(dim);
			newGlobal->setCat(cat);
			newGlobal->setType(tp);
			newGlobal->setFunction(func);
			m_symbols.push_back(newGlobal);
			//volver a llamar al exist
			//verificar que no exista como funcion
			//error
		}
		if (cat == ESYMBOL_CAT::FUNCTION)
		{
			GlobalNode* newGlobal = new GlobalNode();
			newGlobal->setLine(lineNum);
			newGlobal->setSymbol(sym);
			newGlobal->setDim(dim);
			newGlobal->setCat(cat);
			newGlobal->setType(tp);
			newGlobal->setFunction(func);
			m_symbols.push_back(newGlobal);
			//volver a llamar al exist
			//verificar que no exista como funcion
			//error
		}
		if (cat == ESYMBOL_CAT::PARAMETER)
		{
			GlobalNode* newGlobal = new GlobalNode();
			//newGlobal->setLine(lineNum);
			newGlobal->setSymbol(sym);
			//newGlobal->setDim(dim);
			newGlobal->setCat(Compiler::ESYMBOL_CAT::UNDEFINE);
			newGlobal->setType("<UNKNOW>");
			//newGlobal->setFunction(func);
			m_symbols.push_back(newGlobal);
			LocalNode *newln = m_symbols[m_symbols.size()-1]->getNodolocal();
			newln = new LocalNode();
			newln->setLine(lineNum);
			//newln->setSymbol(sym);
			newln->setDim(dim);
			newln->setCat(cat);
			newln->setType(tp);
			newln->setFunc(func);
			m_symbols[m_symbols.size() - 1]->setNodolocal(newln);
			//volver a llamar al exist
			//verificar que no exista como funcion
			//error
		}
		if (cat == ESYMBOL_CAT::LOCAL_VAR)
		{
			GlobalNode* newGlobal = new GlobalNode();
			//newGlobal->setLine(lineNum);
			newGlobal->setSymbol(sym);
			//newGlobal->setDim(dim);
			newGlobal->setCat(Compiler::ESYMBOL_CAT::UNDEFINE);
			newGlobal->setType("<UNKNOW>");
			//newGlobal->setFunction(func);
			m_symbols.push_back(newGlobal);
			LocalNode *newln = m_symbols[m_symbols.size() - 1]->getNodolocal();
			newln = new LocalNode();
			newln->setLine(lineNum);
			//newln->setSymbol(sym);
			newln->setDim(dim);
			newln->setCat(cat);
			newln->setType(tp);
			newln->setFunc(func);
			m_symbols[m_symbols.size() - 1]->setNodolocal(newln);
			//volver a llamar al exist
			//verificar que no exista como funcion
			//error
		}
		//if (cat == ESYMBOL_CAT::LOCAL_VAR)
		//{
		//	//verificar que no exista como parametro de la misma funcion
		//	//verificar que no se llame igual que la funcion
		//	//error
		//}
		//if (cat == ESYMBOL_CAT::PARAMETER)
		//{
		//	//verificar que no se llame igual que una variable de la misma funcion
		//	//verificar que no se llame como una funcion
		//	//error
		//}
	}
	else
	{
		int index;
		for (int i = 0; i < m_symbols.size(); i++)
		{
			if (m_symbols[i]->getSymbol() == sym)
			{
				index = i;
				break;
			}
		}
		if (cat == ESYMBOL_CAT::PARAMETER)
		{
			LocalNode *getln = m_symbols[index]->getNodolocal();
			while (getln != nullptr)
			{
				getln = getln->getNodolocal();
			}
			LocalNode *newln = new LocalNode();
			newln->setLine(lineNum);
			//newln->setSymbol(sym);
			newln->setDim(dim);
			newln->setCat(cat);
			newln->setType(tp);
			newln->setFunc(func);
			getln->setNodoLocal(newln);
			//m_symbols.push_back(newGlobal);
			//volver a llamar al exist
			//verificar que no exista como funcion
			//error
		}
		if (cat == ESYMBOL_CAT::LOCAL_VAR)
		{
			LocalNode *getln = m_symbols[index]->getNodolocal();
			while (getln != nullptr)
			{
				getln = getln->getNodolocal();
			}
			LocalNode *newln = new LocalNode();
			newln->setLine(lineNum);
			//newln->setSymbol(sym);
			newln->setDim(dim);
			newln->setCat(cat);
			newln->setType(tp);
			newln->setFunc(func);
			getln->setNodoLocal(newln);
			//volver a llamar al exist
			//verificar que no exista como funcion
			//error
		}
		//agregar error (symbolo ya esta definifo)

	}
	return false;

}

bool Compiler::SymbolTable::symbolExists(std::string sym, ESYMBOL_CAT cat, std::string func)
{
	bool find = false;
	int index;
	if (m_symbols.size()<=0)
	{
		return false;
	}
	for (int i = 0; i < m_symbols.size(); i++)
	{
		if (m_symbols[i]->getSymbol()== sym)
		{
			index = i;
			find = true;
		}
	}
	if (!find)
	{
		return false;
	}
	else
	{
		if (cat==ESYMBOL_CAT::GLOBAL_VAR|| cat == ESYMBOL_CAT::FUNCTION)
		{
			//auto it = m_symbols.find(sym);
			//GlobalNode * n = it->second;
			if (m_symbols[index]->getCat()==cat)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			//auto it = m_symbols.find(sym);
			//LocalNode * n = it->second->getNodolocal();
			LocalNode* n = m_symbols[index]->getNodolocal();
			while (n!=nullptr)
			{
				if (n->getFunc()==func)
				{
					if (n->getCat()==cat)
					{
						return true;
					}
				}
				n = n->getNodolocal();
			}
			return false;
		}
	}
	return false;
}

void Compiler::SymbolTable::reset()
{
	for (int i = 0; i < m_symbols.size(); i++)
	{
		m_symbols[i]->reset();
		delete m_symbols[i];
		m_symbols[i]=nullptr;
	}
	m_symbols.clear();
}

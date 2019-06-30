#pragma once
#include <string.h>
#include <iostream>
#include <map>
#include "GlobalNode.h"
#include <vector>
namespace Compiler 
{
	
	class SymbolTable
	{

	public:
		SymbolTable();
		~SymbolTable();
	private:
		//std::map<std::string, GlobalNode*> m_symbols;
	public:
		std::vector<GlobalNode*> m_symbols;
		void getAllSymbols();
		bool addSymbol(int lineNum,std::string sym, int dim, ESYMBOL_CAT cat, std::string func, std::string tp);
		bool symbolExists(std::string sym, ESYMBOL_CAT cat, std::string func);
		std::string getSymbolScope(std::string name);
		std::string getSymbolType();
		bool updateSymbolType();
		void reset();
	};
}


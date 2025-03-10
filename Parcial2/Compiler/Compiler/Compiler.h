#pragma once

#include "LexAnalyzer.h"
#include "ErrorsModule.h"
#include "SymbolTable.h"
#include "SyntaxAnalysis.h"
#include "SemanticAnalysis.h"
using namespace System;

namespace Compiler {
	public ref class Manager
	{
	private:
		void lexAnalysis(String ^ srcCode);
		void sinAnalysis(String ^ srcCode);
		LexAnalyzer *lex;
		ErrorsModule ^err;
		SymbolTable* symTable=nullptr;
		SyntaxAnalysis * sin;
		SemanticAnalysis * sem;
	public:
		Manager();
		~Manager();
		cli::array<String^>^compileProgram(String^srcCode);
		String^ TokenLex;
		String^ SymbolTable;


		// TODO: Agregar aquí los métodos de la clase.
	};
}

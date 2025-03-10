#pragma once

#include "LexAnalyzer.h"
#include "ErrorsModule.h"
using namespace System;

namespace Compiler {
	public ref class Manager
	{
	private:
		void lexAnalysis(String ^ srcCode);
		LexAnalyzer *lex;
		ErrorsModule ^err;

	public:
		Manager();
		~Manager();
		cli::array<String^>^compileProgram(String^srcCode);
		String^ TokenLex;


		// TODO: Agregar aquí los métodos de la clase.
	};
}

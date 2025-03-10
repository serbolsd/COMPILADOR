#include "stdafx.h"

#include "Compiler.h"
void Compiler::Manager::lexAnalysis(String ^ srcCode)
{
	if (lex!=nullptr)
	{
		lex->parseSourceCode((const char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(srcCode).ToPointer());
	}
	//throw gcnew System::NotImplementedException();
}

void Compiler::Manager::sinAnalysis(String ^ srcCode)
{
	if (sin != nullptr)
	{
		sin->checkSyntax(sin);
	}
}

Compiler::Manager::Manager()
{
	err = gcnew ErrorsModule;
	lex = new LexAnalyzer(err);
	symTable = new Compiler::SymbolTable();
	sem = new SemanticAnalysis();
	sin = new SyntaxAnalysis(lex,err, symTable);

}

Compiler::Manager::~Manager()

{
	if (lex!=nullptr)
	{
		delete lex;
		lex = nullptr;
	}
	if (symTable!=nullptr)
	{
		delete symTable;
		symTable = nullptr;
	}
	if (sin)
	{
		delete sin;
		sin = nullptr;
	}
	if (sem)
	{
		delete sem;
		sem = nullptr;
	}
}

cli::array<String^>^ Compiler::Manager::compileProgram(String ^ srcCode)
{
	cli::array<String^>^compilationdetails;
	lex->clearTokens();
	err->clearErrors();
	symTable->reset();
	lexAnalysis(srcCode);
	sinAnalysis(srcCode);
	compilationdetails = gcnew cli::array<String^>(4);
	TokenLex = lex->getTokensList();
	SymbolTable = sin->getSymbolTable();
	//compilationdetails = gcnew cli::array<String^>(1);
	String^ outErrors;
	if (lex->m_errorsExcedet)
	{
		for (int i = 0; i < err->m_errorsArray->Length; i++)
		{
			// Concatenate in strings the group of line, lexem and type
			outErrors += err->m_errorsArray[i] + "\r\n";
		}

		compilationdetails[0] = gcnew String("---DEMASIADOS ERRORES, NO SE PUDO TERMINAR DE COMPILAR---");
		compilationdetails[1] = gcnew String(TokenLex);
		compilationdetails[2] = gcnew String(outErrors);
		compilationdetails[3] = gcnew String(SymbolTable);
	}
	else
	{
		for (int i = 0; i < err->m_errorsArray->Length; i++)
		{
			// Concatenate in strings the group of line, lexem and type
			outErrors += err->m_errorsArray[i] + "\r\n";
		}

		compilationdetails[0] = gcnew String("---COMILER OK---");
		compilationdetails[1] = gcnew String(TokenLex);
		compilationdetails[2] = gcnew String(outErrors);
		compilationdetails[3] = gcnew String(SymbolTable);
	}
		return compilationdetails;
	// TODO: insertar una instrucción return aquí
}
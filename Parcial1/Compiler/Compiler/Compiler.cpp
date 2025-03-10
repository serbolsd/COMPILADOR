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

Compiler::Manager::Manager()
{
	err = gcnew ErrorsModule;
	lex = new LexAnalyzer(err);
}

Compiler::Manager::~Manager()

{
	if (lex!=nullptr)
	{
		delete lex;
		lex = nullptr;
	}
}

cli::array<String^>^ Compiler::Manager::compileProgram(String ^ srcCode)
{
	cli::array<String^>^compilationdetails;
	lex->clearTokens();
	err->clearErrors();
	lexAnalysis(srcCode);
	compilationdetails = gcnew cli::array<String^>(3);
	TokenLex = lex->getTokensList();
	//compilationdetails = gcnew cli::array<String^>(1);
	String^ outErrors;
	if (err->m_numErrors>=MAX_ERRORS)
	{
		compilationdetails[0] = gcnew String("---DEMASIADOS ERRORES, NO SE PUDO COMPILAR---");
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
	}
		return compilationdetails;
	// TODO: insertar una instrucción return aquí
}
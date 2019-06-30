#pragma once
using namespace System;
#define  MAX_ERRORS 30
public enum class ERROR_PHASE
{
	GLOBAL,
	LEX_ANALYZER,
	SYN_ANALYZER,
	SEM_ANALYZER,
	CODE_GENERATION
};
namespace Compiler {
	public ref class ErrorsModule
	{
	public:
		ErrorsModule();
		~ErrorsModule();

	private:
	public:
		int m_numErrors;
		cli::array<String^>^m_errorsArray;
		Void clearErrors();
		bool addError(ERROR_PHASE phase, int lineNumber, String^errorDesc,String^errorLine);
		cli::array<String^>^getErrors() 
		{
			return m_errorsArray;
		}

	};
}
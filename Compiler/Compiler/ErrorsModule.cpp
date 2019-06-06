#include "stdafx.h"
#include "ErrorsModule.h"


Compiler::ErrorsModule::ErrorsModule()
{
	m_numErrors = 0;
	m_errorsArray = gcnew cli::array<String^>(MAX_ERRORS);
	for (int i = 0; i < MAX_ERRORS; i++)
	{
		m_errorsArray[i] = gcnew String("");
	}
}

Compiler::ErrorsModule::~ErrorsModule()
{
}



Void Compiler::ErrorsModule::clearErrors()
{
	m_numErrors = 0;
	m_errorsArray->Clear;
	return Void();
}

bool Compiler::ErrorsModule::addError(ERROR_PHASE phase, int lineNumber, String ^ errorDesc, String ^ errorLine)
{
	if (m_numErrors<(MAX_ERRORS-1))
	{
		m_errorsArray->SetValue(String::Format("{0}: {1}{2}{3}", phase.ToString(), lineNumber + " ", errorDesc + " ", errorLine + " "), m_numErrors);
		m_numErrors++;
		return true;
	}
	return false;
}

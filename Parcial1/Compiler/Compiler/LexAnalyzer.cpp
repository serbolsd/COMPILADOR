#include "stdafx.h"
#include "LexAnalyzer.h"

Compiler::LexAnalyzer::LexAnalyzer()
{
	m_keyWords.insert(std::make_pair("var", ""));
	m_keyWords.insert(std::make_pair("for", ""));
	m_keyWords.insert(std::make_pair("while", ""));
	m_keyWords.insert(std::make_pair("int", ""));
	m_keyWords.insert(std::make_pair("float", ""));
	m_keyWords.insert(std::make_pair("if", ""));
	m_keyWords.insert(std::make_pair("bool", ""));
	m_keyWords.insert(std::make_pair("string", ""));
	m_keyWords.insert(std::make_pair("void", ""));
	m_keyWords.insert(std::make_pair("function", ""));
	m_keyWords.insert(std::make_pair("else", ""));
	m_keyWords.insert(std::make_pair("main", ""));
	m_keyWords.insert(std::make_pair("switch", ""));
	m_keyWords.insert(std::make_pair("default", ""));
	m_keyWords.insert(std::make_pair("print", ""));
	m_keyWords.insert(std::make_pair("read", ""));
	m_keyWords.insert(std::make_pair("case", ""));
	m_keyWords.insert(std::make_pair("return", ""));
	m_keyWords.insert(std::make_pair("true", ""));
	m_keyWords.insert(std::make_pair("false", ""));
	m_keyWords.insert(std::make_pair("inc", ""));
	m_keyWords.insert(std::make_pair("dec", ""));
}

Compiler::LexAnalyzer::~LexAnalyzer()
{
}
Compiler::LexAnalyzer::LexAnalyzer(ErrorsModule^ erromod)
{
	m_refErrorsMod = erromod;
	m_keyWords.insert(std::make_pair("var", ""));
	m_keyWords.insert(std::make_pair("for", ""));
	m_keyWords.insert(std::make_pair("while", ""));
	m_keyWords.insert(std::make_pair("int", ""));
	m_keyWords.insert(std::make_pair("float", ""));
	m_keyWords.insert(std::make_pair("if", ""));
	m_keyWords.insert(std::make_pair("bool", ""));
	m_keyWords.insert(std::make_pair("string", ""));
	m_keyWords.insert(std::make_pair("void", ""));
	m_keyWords.insert(std::make_pair("function", ""));
	m_keyWords.insert(std::make_pair("else", ""));
	m_keyWords.insert(std::make_pair("main", ""));
	m_keyWords.insert(std::make_pair("switch", ""));
	m_keyWords.insert(std::make_pair("default", ""));
	m_keyWords.insert(std::make_pair("print", ""));
	m_keyWords.insert(std::make_pair("read", ""));
	m_keyWords.insert(std::make_pair("case", ""));
	m_keyWords.insert(std::make_pair("return", ""));
	m_keyWords.insert(std::make_pair("true", ""));
	m_keyWords.insert(std::make_pair("false", ""));
	m_keyWords.insert(std::make_pair("inc", ""));
	m_keyWords.insert(std::make_pair("dec", ""));
}

bool Compiler::LexAnalyzer::parseSourceCode(const char*src)
{
	int i = 0;
	while (src[i]!='\0')
	{
		bool bcomplete=false;
		if ((src[i] == '\r'|| src[i] == '\n')&&!bcomplete)
		{
			if (src[i] == '\r'&&src[i+1] == '\n')
			{

			}
			else if (src[i] == '\n'&&src[i - 1] == '\r')
			{

			}
			else
			{
				m_numeberLine++;

			}
			bcomplete = true;
		}
		if (!bcomplete)
		{
			for (int j = 0; j < separators.size(); j++)
			{
				if (src[i] == separators[j])
				{
					std::string newLex;
					newLex = src[i];
					detecteToken(newLex, Compiler::TOKEN_TYPE::SEPARATOR);
					bcomplete = true;
				}
			}
		}
		if (!bcomplete)
		{
			for (int j = 0; j < op_arit.size(); j++)
			{

				if (src[i] == op_arit[j])
				{
					if (src[i] == '/'&&src[i + 1] == '/')
					{
						comentaryOneLineParse(src, i);
						break;
					}
					if (src[i] == '/'&&src[i + 1] == '*')
					{
						comentaryMoreLineParse(src, i);
						break;
					}
					if (src[i] == '-'&&src[i + 1] >='0'&&src[i + 1] <= '9')
					{
						numParse(src,i);
						break;
					}
					if (src[i] == '-'&&src[i + 1] >= '.')
					{
						floatParse(src, i);
						break;
					}
					std::string newstring;
					newstring = src[i];
					detecteToken(newstring, Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR);
					bcomplete = true;
				}
			}
		}
		if (!bcomplete)
		{
			for (int j = 0; j < op_dim.size(); j++)
			{
				if (src[i] == op_dim[j])
				{
					std::string newstring;
					newstring = src[i];
					detecteToken(newstring, Compiler::TOKEN_TYPE::DIMENCIONAL_OPERATO);
					bcomplete = true;
				}
			}
		}
		if (!bcomplete)
		{
			for (int j = 0; j < op_log.size(); j++)
			{
				if (src[i] == op_log[j])
				{
					if (src[i] == '|'&&src[i + 1] == '|')
					{
						std::string newLex;
						newLex += src[i];
						i++;
						newLex += src[i];
						detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
					}
					else if (src[i] == '&'&&src[i + 1] == '&')
					{
						std::string newLex;
						newLex += src[i];
						i++;
						newLex += src[i];
						detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
					}
					else if (src[i] == '=')
					{
						std::string newLex;
						newLex += src[i];
						if (src[i + 1] == '=')
						{
							i++;
							newLex += src[i];
							detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
						}
						else
						{
							detecteToken(newLex, Compiler::TOKEN_TYPE::ASIGNATION);
						}
					}
					else if (src[i] == '!')
					{
						std::string newLex;
						newLex += src[i];
						detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
						
					}
					else
					{
						//agregar error
						std::string error;
						error += src[i];
						String^ desc =gcnew String (error.c_str());
						String^errordes = LEX_INVALID_OP_LOG;
						m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
					}
					bcomplete = true;
				}
			}
		}
		if (src[i] == '"'&&!bcomplete)
		{
			stringParse(src, i);
			bcomplete = true;
		}
		if (((src[i] >='a'&&src[i] <= 'z')|| (src[i] >= 'A'&&src[i] <= 'Z')|| src[i]=='_') && !bcomplete)
		{
			letrasParse(src,i);
			bcomplete = true;
		}
		if ((src[i] >= '0'&&src[i] <= '9') && !bcomplete)
		{
			numParse(src, i);
			bcomplete = true;
		}
		if ((src[i] =='.') && !bcomplete)
		{
			floatParse(src, i);
			bcomplete = true;
		}
		if (src[i] == '\0')
		{
			break;
		}
		if (!bcomplete)
		{
			for (int j = 0; j < m_invalid_simbolos.size(); j++)
			{
				if (src[i] == m_invalid_simbolos[j])
				{
					std::string error;
					error = src[i];
					String^ desc = gcnew String(error.c_str());
					String^errordes = LEX_INVALID_CHAR;
					m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
					bcomplete = true;
					break;
				}
			}

		}
		i++;
	}
	return true;
}


void Compiler::LexAnalyzer::letrasParse(const char * src, int & i)
{
	std::string lex;
	bool safe=false;
	while (!safe)
	{
		if (src[i] == space || src[i] == '\t')
		{
			if (lex[lex.size()-1]=='_')
			{
				String^ desc = gcnew String(lex.c_str());
				String^errordes = LEX_INVALID_CHAR;
				m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
			}
			else
			{
				detecteToken(lex, Compiler::TOKEN_TYPE::ID);
			}
			safe = false;
			return;
		}
		if (src[i] == '"')
		{
			detecteToken(lex, Compiler::TOKEN_TYPE::ID);

			stringParse(src, i);
			return;
		}
		for (int j = 0; j < separators.size(); j++)
		{
			if (src[i]== separators[j])
			{
				if (lex[lex.size() - 1] == '_')
				{
					String^ desc = gcnew String(lex.c_str());
					String^errordes = LEX_INVALID_CHAR;
					m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
				}
				else
				{
					detecteToken(lex, Compiler::TOKEN_TYPE::ID);
				}
				std::string newLex;
				newLex = src[i];
				detecteToken(newLex, Compiler::TOKEN_TYPE::SEPARATOR);
				safe = true;
				return;
			}
		}
		for (int j = 0; j < op_arit.size(); j++)
		{
			
			if (src[i] == op_arit[j])
			{
				if (lex[lex.size() - 1] == '_')
				{
					String^ desc = gcnew String(lex.c_str());
					String^errordes = LEX_INVALID_CHAR;
					m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
				}
				else
				{
					detecteToken(lex, Compiler::TOKEN_TYPE::ID);
				}
				if (src[i] == '/'&&src[i + 1] == '/')
				{
					comentaryOneLineParse(src, i);
					return;
				}
				if (src[i] == '/'&&src[i + 1] == '*')
				{
					comentaryMoreLineParse(src, i);
					return;
				}
				if (src[i] == '-'&&src[i + 1] >= '0'&&src[i + 1] <= '9')
				{
					numParse(src, i);
					return;
				}
				if (src[i] == '-'&&src[i + 1] == '.')
				{
					floatParse(src, i);
					return;
				}
				std::string newstring;
				newstring = src[i];
				detecteToken(newstring, Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR);
				safe = true;
				return;
			}
		}
		for (int j = 0; j < op_dim.size(); j++)
		{
			if (src[i] == op_dim[j])
			{
				if (lex[lex.size() - 1] == '_')
				{
					String^ desc = gcnew String(lex.c_str());
					String^errordes = LEX_INVALID_CHAR;
					m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
				}
				else
				{
					detecteToken(lex, Compiler::TOKEN_TYPE::ID);
				}
				std::string newstring;
				newstring = src[i];
				detecteToken(newstring, Compiler::TOKEN_TYPE::DIMENCIONAL_OPERATO);
				safe = true;
				return;
			}
		}
		for (int j = 0; j < op_log.size(); j++)
		{
			
			if (src[i] == op_log[j])
			{
				if (lex[lex.size() - 1] == '_')
				{
					String^ desc = gcnew String(lex.c_str());
					String^errordes = LEX_INVALID_CHAR;
					m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
				}
				else
				{
					detecteToken(lex, Compiler::TOKEN_TYPE::ID);
				}
				if (src[i]=='|'&&src[i+1] == '|')
				{
					std::string newLex;
					newLex += src[i];
					i++;
					newLex += src[i];
					detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);

				}
				else if (src[i] == '&'&&src[i + 1] == '&')
				{
					std::string newLex;
					newLex += src[i];
					i++;
					newLex += src[i];
					detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
				}
				else if (src[i] == '=')
				{
					std::string newLex;
					newLex += src[i];
					if (src[i+1] == '=')
					{
						i++;
						newLex += src[i];
						detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
					}
					else
					{
						detecteToken(newLex, Compiler::TOKEN_TYPE::ASIGNATION);
					}
				}
				else if (src[i] == '!')
				{
					std::string newLex;
					newLex += src[i];
					detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
				}
				else
				{
					std::string error;
					error += src[i];
					String^ desc = gcnew String(error.c_str());
					String^errordes = LEX_INVALID_OP_LOG;
					m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
				}
				safe = true;
				return;
			}
		}
		if (src[i] == '\n' || src[i] == '\r' || src[i] == '\0')
		{
			if (lex[lex.size() - 1] == '_')
			{

				String^ desc = gcnew String(lex.c_str());
				String^errordes = LEX_INVALID_CHAR;
				m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
			}
			else
			{
				detecteToken(lex,Compiler::TOKEN_TYPE::ID);
			}
			m_numeberLine++;
			safe = true;
			return;
		}
		
		lex += src[i];
		i++;
	}
	
	return;
}

void Compiler::LexAnalyzer::numParse(const char * src, int & i)
{
	std::string lex;
	bool safe = false;
	while (!safe)
	{
		lex += src[i];
		i++;
		if (src[i] == '.')
		{
			//detecteToken(lex, Compiler::TOKEN_TYPE::INT);
			floatParse(src, i, lex);
			return;
		}
		if (src[i] == space || src[i] == '\t')
		{

			detecteToken(lex, Compiler::TOKEN_TYPE::INT);
			safe = false;
			return;
		}
		for (int j = 0; j < separators.size(); j++)
		{
			if (src[i] == separators[j])
			{

				detecteToken(lex, Compiler::TOKEN_TYPE::INT);
				std::string newLex;
				newLex = src[i];
				detecteToken(newLex, Compiler::TOKEN_TYPE::SEPARATOR);
				safe = true;
				return;
			}
		}
		for (int j = 0; j < op_arit.size(); j++)
		{

			if (src[i] == op_arit[j])
			{

				detecteToken(lex, Compiler::TOKEN_TYPE::INT);
				if (src[i] == '/'&&src[i + 1] == '/')
				{
					comentaryOneLineParse(src, i);
					return;
				}
				if (src[i] == '/'&&src[i + 1] == '*')
				{
					comentaryMoreLineParse(src, i);
					return;
				}
				if (src[i] == '-'&&src[i + 1] >= '0'&&src[i + 1] <= '9')
				{
					numParse(src, i);
					return;
				}
				if (src[i] == '-'&&src[i + 1] >= '.')
				{
					floatParse(src, i);
					return;
				}
				std::string newstring;
				newstring = src[i];
				detecteToken(newstring, Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR);
				safe = true;
				return;
			}
		}
		for (int j = 0; j < op_dim.size(); j++)
		{
			if (src[i] == op_dim[j])
			{

				detecteToken(lex, Compiler::TOKEN_TYPE::INT);
				std::string newstring;
				newstring = src[i];
				detecteToken(newstring, Compiler::TOKEN_TYPE::DIMENCIONAL_OPERATO);
				safe = true;
				return;
			}
		}
		for (int j = 0; j < op_log.size(); j++)
		{

			if (src[i] == op_log[j])
			{

				detecteToken(lex, Compiler::TOKEN_TYPE::INT);
				if (src[i] == '|'&&src[i + 1] == '|')
				{
					std::string newLex;
					newLex += src[i];
					i++;
					newLex += src[i];
					detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);

				}
				else if (src[i] == '&'&&src[i + 1] == '&')
				{
					std::string newLex;
					newLex += src[i];
					i++;
					newLex += src[i];
					detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
				}
				else if (src[i] == '=')
				{
					std::string newLex;
					newLex += src[i];
					if (src[i + 1] == '=')
					{
						i++;
						newLex += src[i];
						detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
					}
					else
					{
						detecteToken(newLex, Compiler::TOKEN_TYPE::ASIGNATION);
					}
				}
				else if (src[i] == '!')
				{
					std::string newLex;
					newLex += src[i];
					detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
				}
				else
				{
					std::string error;
					error += src[i];
					String^ desc = gcnew String(error.c_str());
					String^errordes = LEX_INVALID_OP_LOG;
					m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);

				}
				safe = true;
				return;
			}
		}
		if (src[i] == '\n' || src[i] == '\r' || src[i] == '\0')
		{
			detecteToken(lex, Compiler::TOKEN_TYPE::INT);

			m_numeberLine++;
			safe = true;
			return;
		}
	}
	return;
}

void Compiler::LexAnalyzer::floatParse(const char * src, int & i,std::string str)
{
	std::string lex;
	lex += str;
	bool safe = false;
	while (!safe)
	{
		lex += src[i];
		i++;
		if (src[i] == space || src[i] == '\t')
		{

			detecteToken(lex, Compiler::TOKEN_TYPE::FLOAT);
			return;
			safe = false;
		}
		for (int j = 0; j < separators.size(); j++)
		{
			if (src[i] == separators[j])
			{

				detecteToken(lex, Compiler::TOKEN_TYPE::FLOAT);
				std::string newLex;
				newLex = src[i];
				detecteToken(newLex, Compiler::TOKEN_TYPE::SEPARATOR);
				safe = true;
				return;
			}
		}
		for (int j = 0; j < op_arit.size(); j++)
		{

			if (src[i] == op_arit[j])
			{

				detecteToken(lex, Compiler::TOKEN_TYPE::FLOAT);
				if (src[i] == '/'&&src[i + 1] == '/')
				{
					comentaryOneLineParse(src, i);
					return;
				}
				if (src[i] == '/'&&src[i + 1] == '*')
				{
					comentaryMoreLineParse(src, i);
					return;
				}
				if (src[i] == '-'&&src[i + 1] >= '0'&&src[i + 1] <= '9')
				{
					numParse(src, i);
					return;
				}
				if (src[i] == '-'&&src[i + 1] >= '.')
				{
					floatParse(src, i);
					return;
				}
				std::string newstring;
				newstring = src[i];
				detecteToken(newstring, Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR);
				safe = true;
				return;
			}
		}
		for (int j = 0; j < op_dim.size(); j++)
		{
			if (src[i] == op_dim[j])
			{

				detecteToken(lex, Compiler::TOKEN_TYPE::FLOAT);
				std::string newstring;
				newstring = src[i];
				detecteToken(newstring, Compiler::TOKEN_TYPE::DIMENCIONAL_OPERATO);
				safe = true;
				return;
			}
		}
		for (int j = 0; j < op_log.size(); j++)
		{

			if (src[i] == op_log[j])
			{

				detecteToken(lex, Compiler::TOKEN_TYPE::FLOAT);
				if (src[i] == '|'&&src[i + 1] == '|')
				{
					std::string newLex;
					newLex += src[i];
					i++;
					newLex += src[i];
					detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);

				}
				else if (src[i] == '&'&&src[i + 1] == '&')
				{
					std::string newLex;
					newLex += src[i];
					i++;
					newLex += src[i];
					detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
				}
				else if (src[i] == '=')
				{
					std::string newLex;
					newLex += src[i];
					if (src[i + 1] == '=')
					{
						i++;
						newLex += src[i];
						detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
					}
					else
					{
						detecteToken(newLex, Compiler::TOKEN_TYPE::ASIGNATION);
					}
				}
				else if (src[i] == '!')
				{
					std::string newLex;
					newLex += src[i];
					detecteToken(newLex, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
				}
				else
				{
					std::string error;
					error += src[i];
					String^ desc = gcnew String(error.c_str());
					String^errordes = LEX_INVALID_OP_LOG;
					m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);

				}
				safe = true;
				return;
			}
		}
		if (src[i] == '\n' || src[i] == '\r' || src[i] == '\0')
		{
			detecteToken(lex, Compiler::TOKEN_TYPE::FLOAT);

			m_numeberLine++;
			safe = true;
			return;
		}
	}
	return;
	//getTokens(m_Tokens);
}

void Compiler::LexAnalyzer::comentaryOneLineParse(const char * src, int & i)
{
	std::string lex;
	while (true)
	{
		if (src[i] == '\n' || src[i] == '\r' || src[i] == '\0')
		{
			detecteToken(lex, Compiler::TOKEN_TYPE::COMENTARY);

			m_numeberLine++;
			return;
		}
		lex += src[i];
		i++;
	}
}

void Compiler::LexAnalyzer::comentaryMoreLineParse(const char * src, int & i)
{
	std::string lex;
	while (true)
	{
		if (src[i] =='*'&&src[i+1] == '/'&&lex.size()>2)
		{
			lex += src[i];
			i++;
			lex += src[i];
			detecteToken(lex, Compiler::TOKEN_TYPE::COMENTARY);
			m_numeberLine++;
			return;
		}
		if (src[i] == '\0')
		{
			//agregar error
			//std::string error;
			// += src[i];
			String^ desc = gcnew String(lex.c_str());
			String^errordes = LEX_COMMENT_NOT_CLOSED;
			m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);

			return;
		}
		lex += src[i];
		i++;
	}
}

void Compiler::LexAnalyzer::stringParse(const char * src, int & i)
{
	std::string lex;
	while (true)
	{
		if (src[i]=='"'&&lex.size()>1)
		{
			lex += src[i];
			detecteToken(lex, Compiler::TOKEN_TYPE::STRING);
			return;
		}
		if (src[i] == '\r'|| src[i] == '\n'||src[i] == '\0')
		{
			//agregar error
			String^ desc = gcnew String(lex.c_str());
			String^errordes = LEX_STRING_NOT_CLOSED;
			m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
			m_numeberLine++;
			return;
		}
		lex += src[i];
		i++;
	}
}

void Compiler::LexAnalyzer::detecteToken(std::string lexema,int type)
{
	Compiler::TOKEN_TYPE tType= Compiler::TOKEN_TYPE::UNDEFINDED;
	switch (type)
	{
	case Compiler::TOKEN_TYPE::ID:
		tType = Compiler::TOKEN_TYPE::ID;
		break;
	case Compiler::TOKEN_TYPE::INT:
		tType = Compiler::TOKEN_TYPE::INT;
		break;
	case Compiler::TOKEN_TYPE::FLOAT:
		tType = Compiler::TOKEN_TYPE::FLOAT;
		break;
	case Compiler::TOKEN_TYPE::LOGIC_OPERATOR:
		tType = Compiler::TOKEN_TYPE::LOGIC_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR:
		tType = Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::DIMENCIONAL_OPERATO:
		tType = Compiler::TOKEN_TYPE::DIMENCIONAL_OPERATO;
		break;
	case Compiler::TOKEN_TYPE::ASIGNATION:
		tType = Compiler::TOKEN_TYPE::ASIGNATION;
		break;
	case Compiler::TOKEN_TYPE::SEPARATOR:
		tType = Compiler::TOKEN_TYPE::SEPARATOR;
		break;
	case Compiler::TOKEN_TYPE::STRING:
		tType = Compiler::TOKEN_TYPE::STRING;
		break;
	case Compiler::TOKEN_TYPE::COMENTARY:
		tType = Compiler::TOKEN_TYPE::COMENTARY;
		break;
	default:
		break;
	}
	for (int i = 0; i < m_keyword.size(); i++)
	{
		if (lexema== m_keyword[i])
		{
			tType = Compiler::TOKEN_TYPE::KEYWORD;
		}
	}
	if (tType == Compiler::TOKEN_TYPE::ID)
	{
		for (int i = 0; i < lexema.size(); i++)
		{
			if (!(lexema[i] >= 'a'&&lexema[i] <= 'z') && !(lexema[i] >= 'A'&&lexema[i] <= 'Z') && lexema[i] != '_'&& !(lexema[i] >= '0'&&lexema[i] <= '9'))
			{
				String^ desc = gcnew String(lexema.c_str());
				String^errordes = LEX_INVALID_CHAR;
				m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
				return;//agregar error
			}
		}
	}

	if (tType == Compiler::TOKEN_TYPE::INT)
	{
		for (int i = 0; i < lexema.size(); i++)
		{
			if (!(lexema[i] >= '0'&&lexema[i] <= '9') && lexema[i] != '-')
			{
				String^ desc = gcnew String(lexema.c_str());
				String^errordes = LEX_INVALID_INT;
				m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
				return;//agregar error
				
			}
		}
	}
	if (tType == Compiler::TOKEN_TYPE::FLOAT)
	{
		int numPoints = 0;
		for (int i = 0; i < lexema.size(); i++)
		{
			if (!(lexema[i] >= '0'&&lexema[i] <= '9')&& lexema[i]!='.'&& lexema[i] != '-')
			{
				String^ desc = gcnew String(lexema.c_str());
				String^errordes = LEX_INVALID_FLOAT;
				m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
				return;//agregar error
				
			}
			if (lexema[i] == '.')
			{
				numPoints++;
			}
			if (numPoints>1)
			{
				String^ desc = gcnew String(lexema.c_str());
				String^errordes = LEX_INVALID_FLOAT;
				m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
				return;//agregar error
				//agregar error
				return;
			}
		}
	}

	addToken(lexema.c_str(), m_numeberLine, tType);
}

void Compiler::LexAnalyzer::clearTokens()
{
	m_Tokens.clear();
}

void Compiler::LexAnalyzer::getTokens(std::vector<Token*>* tokensVec)
{
	//m_Tokens.clear;
}

void Compiler::LexAnalyzer::addToken(std::string lex, int lineNum, TOKEN_TYPE tp)
{
	std::string lexema = lex;
	Compiler::Token*tok = new Compiler::Token(lexema, tp, lineNum);
	m_Tokens.push_back(tok);
}

String^ Compiler::LexAnalyzer::getTokensList()
{
	String^ str;
	for (int i = 0; i < m_Tokens.size(); i++)
	{
		str += m_Tokens[i]->getLineNumber().ToString();
		str += "@";
		std::string st = m_Tokens[i]->getLex();
		String^ strr = gcnew String(st.c_str());
		str += strr;
		str += "@";
		int num = m_Tokens[i]->getType();
		switch (num)
		{
		case UNDEFINDED:
			str += "UNDEFINDED";
			break;
		case KEYWORD:
			str += "KEYWORD";
			break;
		case ID:
			str += "ID";
			break;
		case INT:
			str += "INT";
			break;
		case FLOAT:
			str += "FLOAT";
			break;
		case LOGIC_OPERATOR:
			str += "LOGIC_OPERATOR";
			break;
		case ARITMETIC_OPERATOR:
			str += "ARITMETIC_OPERATOR";
			break;
		case DIMENCIONAL_OPERATO:
			str += "DIMENCIONAL_OPERATO";
			break;
		case ASIGNATION:
			str += "ASIGNATION";
			break;
		case SEPARATOR:
			str += "SEPARATOR";
			break;
		case STRING:
			str += "STRING";
			break;
		case COMENTARY:
			str += "COMENTARY";
			break;
		default:
			break;
		}
		str += "@";
	}
	m_numeberLine = 0;
	return str;
}

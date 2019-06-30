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
	while (m_errorsExcedet || src[i] != '\0')
	{
		while (src[i] != '\0')
		{
			if (m_errorsExcedet)
			{
				break;
			}
			bool bcomplete = false;
			//salto de linea
			if ((src[i] == '\r' || src[i] == '\n'))
			{
				if (src[i] == '\r'&&src[i + 1] == '\n')
				{
					i++;
					m_numeberLine++;
				}
				else
				{
					m_numeberLine++;

				}
				break;
			}
			if (src[i] == ' '|| src[i] == '\t')
			{
				break;
			}
			// deliomitadores
			for (int j = 0; j < delimitador.size(); j++)
			{
				if (src[i] == delimitador[j])
				{
					std::string newLex;
					newLex = src[i];
					detecteToken(newLex, m_numeberLine, Compiler::TOKEN_TYPE::DELIMITER);
					bcomplete = true;
					break;
				}
			}
			if (bcomplete)
			{
				break;
			}
			//operador aritmetico
			for (int j = 0; j < op_arit.size(); j++)
			{

				if (src[i] == op_arit[j])
				{
					if (src[i] == '/'&&src[i + 1] == '/')
					{
						comentaryOneLineParse(src, i);
						bcomplete = true;
						break;
					}
					if (src[i] == '/'&&src[i + 1] == '*')
					{
						comentaryMoreLineParse(src, i);
						bcomplete = true;
						break;
					}
					if (src[i] == '-'&&src[i + 1] >= '0'&&src[i + 1] <= '9')
					{
						numParse(src, i);
						bcomplete = true;
						break;
					}
					if (src[i] == '-'&&src[i + 1] >= '.')
					{
						floatParse(src, i);
						bcomplete = true;
						break;
					}
					std::string newstring;
					newstring = src[i];
					detecteToken(newstring, m_numeberLine, Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR);
					bcomplete = true;
					break;
				}
			}
			if (bcomplete)
			{
				break;
			}
			//operador dimensional
			for (int j = 0; j < op_dim.size(); j++)
			{
				if (src[i] == op_dim[j])
				{
					std::string newstring;
					newstring = src[i];
					detecteToken(newstring, m_numeberLine, Compiler::TOKEN_TYPE::DIMENCIONAL_OPERATOR);
					bcomplete = true;
					break;
				}
			}
			if (bcomplete)
			{
				break;
			}
			//operador agrupacion
			for (int j = 0; j < op_agrup.size(); j++)
			{
				if (src[i]== op_agrup[j])
				{
					std::string newstring;
					newstring = src[i];
					detecteToken(newstring, m_numeberLine, Compiler::TOKEN_TYPE::AGRUPE_OPERATOR);
					bcomplete = true;
					break;
				}
			}
			if (bcomplete)
			{
				break;
			}
			//operador logico
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
						detecteToken(newLex, m_numeberLine, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
					}
					else if (src[i] == '&'&&src[i + 1] == '&')
					{
						std::string newLex;
						newLex += src[i];
						i++;
						newLex += src[i];
						detecteToken(newLex, m_numeberLine, Compiler::TOKEN_TYPE::LOGIC_OPERATOR);
					}
					else
					{
						//agregar error
						std::string error;
						error += src[i];
						String^ desc = gcnew String(error.c_str());
						String^errordes = LEX_INVALID_OP_LOG;
						m_errorsExcedet=m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
					}
					bcomplete = true;
					break;
				}
			}
			if (bcomplete)
			{
				break;
			}
			//relative operator
			for (int j = 0; j < op_rel.size(); j++)
			{
				if (src[i]== op_rel[j])
				{

					if (src[i+1]=='=')
					{
						std::string newLex;
						newLex += src[i];
						i++;
						newLex += src[i];
						detecteToken(newLex, m_numeberLine, Compiler::TOKEN_TYPE::RELATIVE_OPERATOR);

					}
					else if (src[i] == '!')
					{
						std::string newLex;
						newLex += src[i];
						detecteToken(newLex, m_numeberLine, Compiler::TOKEN_TYPE::UNILATERAL_LOGIC_OPERATOR);
					}
					else if (src[i] == '=')
					{
						std::string newLex;
						newLex += src[i];
						detecteToken(newLex, m_numeberLine, Compiler::TOKEN_TYPE::ASIGNATION);
					}
					else
					{
						std::string newLex;
						newLex += src[i];
						detecteToken(newLex, m_numeberLine, Compiler::TOKEN_TYPE::RELATIVE_OPERATOR);
					}
					bcomplete = true;
					break;
				}
			}
			if (bcomplete)
			{
				break;
			}
			//string
			if (src[i] == '"')
			{
				stringParse(src, i);
				break;
			}
			//ID
			if (((src[i] >= 'a'&&src[i] <= 'z') || (src[i] >= 'A'&&src[i] <= 'Z') || src[i] == '_'))
			{
				letrasParse(src, i);
				break;
			}
			//numero
			if ((src[i] >= '0'&&src[i] <= '9'))
			{
				numParse(src, i);
				break;
			}
			//float
			if ((src[i] == '.'))
			{
				floatParse(src, i);
				break;
			}
			//end
			if (src[i] == '\0')
			{
				break;
			}

			std::string error;
			error = src[i];
			String^ desc = gcnew String(error.c_str());
			String^errordes = LEX_INVALID_CHAR;
			m_errorsExcedet = m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
			bcomplete = true;
			break;
		}
		if (src[i] == '\0')
		{
			break;
		}
		i++;
	}
	return true;
}


void Compiler::LexAnalyzer::letrasParse(const char * src, int & i)
{
	std::string lex;
	while (true)
	{
		if (!((src[i] >= 'a'&&src[i] <= 'z') || (src[i] >= 'A'&&src[i] <= 'Z') || src[i] == '_'|| (src[i] >= '0'&& src[i] <= '9')))
		{
			if (lex[lex.size() - 1] == '_')
			{

				String^ desc = gcnew String(lex.c_str());
				String^errordes = LEX_INVALID_CHAR;
				m_errorsExcedet = m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
			}
			else
			{
				detecteToken(lex, m_numeberLine, Compiler::TOKEN_TYPE::ID);
			}
			i--;
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
		if (!(src[i] >= '0' && src[i] <= '9'))
		{
			if (src[i] == '.')
			{
				//detecteToken(lex, Compiler::TOKEN_TYPE::INT);
				floatParse(src, i, lex);
				return;
			}
			detecteToken(lex, m_numeberLine, Compiler::TOKEN_TYPE::INT);
			i--;
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
		if (!(src[i] >= '0' && src[i] <= '9'))
		{
			if ((lex[lex.size() - 1] == '.'))
			{
				String^ desc = gcnew String(lex.c_str());
				String^errordes = LEX_INVALID_FLOAT;
				m_errorsExcedet = m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
			}
			else
			{
				detecteToken(lex, m_numeberLine, Compiler::TOKEN_TYPE::FLOAT);

			}
			i--;
			return;
		}
	}
	return;
	//getTokens(m_Tokens);
}

void Compiler::LexAnalyzer::comentaryOneLineParse(const char * src, int & i)
{
	std::string lex;
	i++;
	i++;
	while (true)
	{
		if (src[i] == '\n' || src[i] == '\r' || src[i] == '\0')
		{
			//detecteToken(lex, m_numeberLine, Compiler::TOKEN_TYPE::COMENTARY);
			comentarys.push_back(lex);
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
	i++;
	i++;
	int numLineaInit=m_numeberLine;
	while (true)
	{
		if ((src[i] == '\r' || src[i] == '\n'))
		{
			if (src[i] == '\r'&&src[i + 1] == '\n')
			{
				lex += src[i];
				i++;
				m_numeberLine++;
			}
			else
			{
				m_numeberLine++;

			}
		}
		if (src[i] =='*'&&src[i+1] == '/')
		{
			//lex += src[i];
			i++;
			//lex += src[i];
			//i++;
			//detecteToken(lex, numLineaInit,Compiler::TOKEN_TYPE::COMENTARY);
			comentarys.push_back(lex);
			//m_numeberLine++;
			return;
		}
		if (src[i] == '\0')
		{
			//agregar error
			//std::string error;
			// += src[i];
			String^ desc = gcnew String(lex.c_str());
			String^errordes = LEX_COMMENT_NOT_CLOSED;
			m_errorsExcedet = m_refErrorsMod->addError(m_phase, numLineaInit, errordes, desc);

			return;
		}
		lex += src[i];
		i++;
	}
}

void Compiler::LexAnalyzer::stringParse(const char * src, int & i)
{
	std::string lex;
	lex += src[i];
	i++;
	while (true)
	{
		if (src[i]=='"')
		{
			lex += src[i];
			//i++;
			detecteToken(lex,m_numeberLine, Compiler::TOKEN_TYPE::STRING);

			return;
		}
		if (src[i] == '\r'|| src[i] == '\n'||src[i] == '\0')
		{
			//agregar error
			String^ desc = gcnew String(lex.c_str());
			String^errordes = LEX_STRING_NOT_CLOSED;
			m_errorsExcedet = m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
			m_numeberLine++;
			//i++;
			return;
		}
		lex += src[i];
		i++;
	}
}

void Compiler::LexAnalyzer::detecteToken(std::string lexema,int line,int type)
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
	case Compiler::TOKEN_TYPE::UNILATERAL_LOGIC_OPERATOR:
		tType = Compiler::TOKEN_TYPE::UNILATERAL_LOGIC_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR:
		tType = Compiler::TOKEN_TYPE::ARITMETIC_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::DIMENCIONAL_OPERATOR:
		tType = Compiler::TOKEN_TYPE::DIMENCIONAL_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::AGRUPE_OPERATOR:
		tType = Compiler::TOKEN_TYPE::AGRUPE_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::RELATIVE_OPERATOR:
		tType = Compiler::TOKEN_TYPE::RELATIVE_OPERATOR;
		break;
	case Compiler::TOKEN_TYPE::ASIGNATION:
		tType = Compiler::TOKEN_TYPE::ASIGNATION;
		break;
	case Compiler::TOKEN_TYPE::DELIMITER:
		tType = Compiler::TOKEN_TYPE::DELIMITER;
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
	//if (tType == Compiler::TOKEN_TYPE::ID)
	//{
	//	for (int i = 0; i < lexema.size(); i++)
	//	{
	//		if (!(lexema[i] >= 'a'&&lexema[i] <= 'z') && !(lexema[i] >= 'A'&&lexema[i] <= 'Z') && lexema[i] != '_'&& !(lexema[i] >= '0'&&lexema[i] <= '9'))
	//		{
	//			String^ desc = gcnew String(lexema.c_str());
	//			String^errordes = LEX_INVALID_CHAR;
	//			m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
	//			return;//agregar error
	//		}
	//	}
	//}

	//if (tType == Compiler::TOKEN_TYPE::INT)
	//{
	//	for (int i = 0; i < lexema.size(); i++)
	//	{
	//		if (!(lexema[i] >= '0'&&lexema[i] <= '9') && lexema[i] != '-')
	//		{
	//			String^ desc = gcnew String(lexema.c_str());
	//			String^errordes = LEX_INVALID_INT;
	//			m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
	//			return;//agregar error
	//			
	//		}
	//	}
	//}
	//if (tType == Compiler::TOKEN_TYPE::FLOAT)
	//{
	//	int numPoints = 0;
	//	for (int i = 0; i < lexema.size(); i++)
	//	{
	//		if (!(lexema[i] >= '0'&&lexema[i] <= '9')&& lexema[i]!='.'&& lexema[i] != '-')
	//		{
	//			String^ desc = gcnew String(lexema.c_str());
	//			String^errordes = LEX_INVALID_FLOAT;
	//			m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
	//			return;//agregar error
	//			
	//		}
	//		if (lexema[i] == '.')
	//		{
	//			numPoints++;
	//		}
	//		if (numPoints>1)
	//		{
	//			String^ desc = gcnew String(lexema.c_str());
	//			String^errordes = LEX_INVALID_FLOAT;
	//			m_refErrorsMod->addError(m_phase, m_numeberLine, errordes, desc);
	//			return;//agregar error
	//			//agregar error
	//			return;
	//		}
	//	}
	//}

	addToken(lexema.c_str(), line, tType);
}

void Compiler::LexAnalyzer::clearTokens()
{
	for (size_t i = 0; i < m_Tokens.size(); i++)
	{
		delete m_Tokens[i];
	}
	m_Tokens.clear();
}

void Compiler::LexAnalyzer::getTokens(std::vector<Token*>* tokensVec)
{
	//m_Tokens.clear;
}

Compiler::Token * Compiler::LexAnalyzer::getNextToken()
{
	m_tokensIndex++;
	if (m_tokensIndex>=m_Tokens.size())
	{
		return nullptr;
	}
	return m_Tokens[m_tokensIndex];
	
}

Compiler::Token * Compiler::LexAnalyzer::getPrevToken()
{
	m_tokensIndex--;
	return m_Tokens[m_tokensIndex];
}

Compiler::Token * Compiler::LexAnalyzer::peeckToken(int idx)
{
	if (idx>=m_Tokens.size()||idx<0)
	{
		//invalid index
		return nullptr;
	}
	return m_Tokens[idx];
}

Compiler::Token * Compiler::LexAnalyzer::setIndexToken(int idx)
{
	m_tokensIndex = idx;
	return m_Tokens[m_tokensIndex];
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
		str += "\n";
		std::string st = m_Tokens[i]->getLex();
		String^ strr = gcnew String(st.c_str());
		str += strr;
		str += "\n";
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
		case UNILATERAL_LOGIC_OPERATOR:
			str += "UNILATERAL_LOGIC_OPERATOR";
			break;
		case ARITMETIC_OPERATOR:
			str += "ARITMETIC_OPERATOR";
			break;
		case DIMENCIONAL_OPERATOR:
			str += "DIMENCIONAL_OPERATOR";
			break;
		case AGRUPE_OPERATOR:
			str += "AGRUPE_OPERATOR";
			break;
		case RELATIVE_OPERATOR:
			str += "RELATIVE_OPERATOR";
			break;
		case ASIGNATION:
			str += "ASIGNATION";
			break;
		case DELIMITER:
			str += "DELIMITER";
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
		str += "\n";
	}
	m_numeberLine = 1;
	m_tokensIndex = -1;
	return str;
}

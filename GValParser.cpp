#include <GValParser.h>
#include <stdio.h>

GValParserToken::GValParserToken()
{
}

GValParserToken::GValParserToken(int type_, const GVal & value_)
{
	type = type_;
	value = value_;
}

GValParser::GValParser()
{
	parserState = PS_NOT_OPENED;
	inputStream = 0;
}

GValParser::~GValParser()
{
}

GVal GValParser::parseString(const std::string &s)
{
	openString(s);
	return parse();
}

GVal GValParser::parseFile(const std::string &inputFileName)
{
	return GVal();
}

void GValParser::openFile(const std::string &inputFileName)
{
}

void GValParser::openString(const std::string &s)
{
	inputString = s;
	inputStringPosition = 0;
	parserState = PS_PARSING_STRING;
}

int GValParser::getChar()
{
	if (returnedChars.empty())
		return getCharFromStream();
	int c = returnedChars.back();
	returnedChars.pop_back();
	return c;
}

void GValParser::returnChar(int c)
{
	returnedChars.push_back(c);
}

int GValParser::getCharFromStream()
{
	switch (parserState)
	{
	case GValParser::PS_NOT_OPENED:
		return EOF;
	case GValParser::PS_PARSING_STRING:
		if (inputStringPosition < (int)inputString.size())
		{
			int c = inputString[inputStringPosition];
			inputStringPosition++;
			return c;
		}
		return EOF;
	case GValParser::PS_PARSING_FILE:
		return EOF;
	default:
		return EOF;
	}
}

GVal GValParser::parse()
{
	GValParserToken token = lex();
	switch (token.type)
	{
	case GValParserToken::TT_TRUE:
		return GVal(true);
	case GValParserToken::TT_FALSE:
		return GVal(false);
	case GValParserToken::TT_INT:
	case GValParserToken::TT_FLOAT:
	case GValParserToken::TT_DOUBLE:
	case GValParserToken::TT_STRING:
		return token.value;
	default:
		break;

	}
	return GVal();
}

GValParserToken GValParser::lex()
{
	skipWhiteSpaceAndComments();
	bool r = tryParseString();
	if (r)
	{
		return GValParserToken(GValParserToken::TT_STRING, lexerValue);
	}
	return GValParserToken();
}

void GValParser::skipWhiteSpaceAndComments()
{
	for (;;)
	{
		bool r1 = skipWhiteSpace();
		bool r2 = skipComments();
		if (!r1 && !r2)
			break;
	}
}

bool GValParser::skipWhiteSpace()
{
	bool r = false;
	for (;;)
	{
		int c = getChar();
		if (c == ' ' || c == '\n' || c == '\n' || c == '\r' || c == EOF)
		{
			r = true;
			continue;
		}
		returnChar(c);
		break;
	}
	return r;
}

bool GValParser::skipComments()
{
	int c = getChar();
	if (c == '/')
	{
		int c2 = getChar();
		if (c2 == '/')
		{
			for (;;)
			{
				int c = getChar();
				if (c == '\n' || c == '\r' || c == EOF)
					return true;
			}
		}
		if (c2 == '*')
		{
			for (;;)
			{
				c = getChar();
				if (c == EOF)
				{
					returnChar(c);
					warning("unfinished comment.");
					return true;
				}
				int c2 = getChar();
				if (c == '*' && c2 == '/')
					return true;
				returnChar(c2);
			}
		}
		returnChar(c2);
	}
	returnChar(c);
	return false;
}

bool GValParser::tryParseString()
{
	int c = getChar();
	if (c == '\'')
	{
		tmpChars.clear();
		for (;;)
		{
			int c = getChar();
			if (c == EOF)
			{
				error("premature end of file: unfinished string.");
				lexerValue = GVal(std::string(&tmpChars[0], tmpChars.size()));
				return true;
			}
			if (c == '\'')
			{
				lexerValue = GVal(std::string(&tmpChars[0], tmpChars.size()));
				return true;
			}
			tmpChars.push_back((char)c);
		}
	}
	return false;
}

void GValParser::warning(const std::string &msg)
{
	progressReporter.warning(msg);
}

void GValParser::error(const std::string &msg)
{
	progressReporter.error(msg);
}


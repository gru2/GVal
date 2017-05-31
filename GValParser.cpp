#include <GValParser.h>
#include <toString.h>
#include <GValUtils.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

GValParserToken::GValParserToken()
{
	type = TT_NULL;
}

GValParserToken::GValParserToken(int type_, const GVal & value_)
{
	type = type_;
	value = value_;
}

bool GValParserToken::isLiteral()
{
	if (type == TT_TRUE || type == TT_FALSE || type == TT_INT ||
		type == TT_FLOAT || type == TT_DOUBLE || type == TT_STRING)
		return true;
	return false;
}

GVal GValParserToken::getValue()
{
	if (type == TT_TRUE)
		return GVal(true);
	if (type == TT_FALSE)
		return GVal(false);
	return value;
}

GValParser::GValParser()
{
	parserState = PS_NOT_OPENED;
	inputStringPosition = 0;
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
	case '{':
		return parseMap();
	case '[':
		return parseList();
	case GValParserToken::TT_MAI:
		return parseMultiArray(GVal::GVT_INT);
	case GValParserToken::TT_MAF:
		return parseMultiArray(GVal::GVT_FLOAT);
	case GValParserToken::TT_MAD:
		return parseMultiArray(GVal::GVT_DOUBLE);
	case GValParserToken::TT_MAG:
		return parseMultiArray(GVal::GVT_GENERIC);
	default:
		error("sintax error: unexpected token" + toString(token.type));
		break;
	}
	return GVal();
}

GVal GValParser::parseMap()
{
	GVal v;
	v.setMap();
	for (;;)
	{
		GValParserToken token = lex();
		if (token.type == '}')
			return v;
		returnToken(token);
		parseSlot(v);
	}
	return v;
}

void GValParser::expectToken(int expectedTokenType)
{
	GValParserToken token = lex();
	if (token.type == expectedTokenType)
		return;
	error("sintax error: expected token " + toString(expectedTokenType) + ", buf found token " + toString(token.type));
}

void GValParser::parseSlot(GVal &v)
{
	GVal key = parse();
	expectToken('=');
	GVal value = parse();
	expectToken(';');
	v.set(key, value);
}

// '[' [expr (, expr)* ']'
GVal GValParser::parseList()
{
	GVal v;
	v.setMultiArray(0, GVal::GVT_GENERIC);
	GValParserToken token = lex();
	if (token.type == ']')
		return v;
	returnToken(token);
	GVal u = parse();
	v.pushBack(u);
	for (;;)
	{
		GValParserToken token = lex();
		if (token.type == ']')
			break;
		if (token.type == ',')
		{
			GVal u = parse();
			v.pushBack(u);
		}
		else
		{
			error("syntax error (2), unexpected token:" + toString(token.type));
			break;
		}
	}
	return v;
}

GVal GValParser::parseMultiArray(GVal::GValType type)
{
	std::cout << "parseMultiArray...\n";
	expectToken('(');
	expectToken(GValParserToken::TT_INT);
	SmallVector<size_t, 4> shape;
	shape.push_back(lexerValue.asInt());
	for (;;)
	{
		GValParserToken token = lex();
		if (token.type == ')')
			break;
		if (token.type == ',')
		{
			expectToken(GValParserToken::TT_INT);
			shape.push_back(lexerValue.asInt());
		}
		else
		{
			error("syntax error, unexpected token:" + toString(token.type));
			return GVal();
		}
	}
	std::cout << "MA<" + toString(type) + ">(";
	for (size_t i = 0; i < shape.size(); i++)
	{
		std::cout << (unsigned)shape[(unsigned)i] << " ";
	}
	std::cout << ")\n";

	GVal u = parse();
	std::cout << "u = " << toString(u) << "\n";
	GVal v = gvalToMultiArray(u, shape, type);
	return v;
}

GValParserToken GValParser::lex()
{
	if (returnedTokens.empty())
		return getNextTokenFromStream();
	GValParserToken tok = returnedTokens.back();
	returnedTokens.pop_back();
	return tok;
}

void GValParser::returnToken(const GValParserToken &token)
{
	returnedTokens.push_back(token);
}

GValParserToken GValParser::getNextTokenFromStream()
{
	skipWhiteSpaceAndComments();
	if (tryParseString())
		return GValParserToken(GValParserToken::TT_STRING, lexerValue);
	if (tryParseNumber())
	{
		if (lexerValue.getType() == GVal::GVT_INT)
			return GValParserToken(GValParserToken::TT_INT, lexerValue);
		if (lexerValue.getType() == GVal::GVT_FLOAT)
			return GValParserToken(GValParserToken::TT_FLOAT, lexerValue);
		if (lexerValue.getType() == GVal::GVT_DOUBLE)
			return GValParserToken(GValParserToken::TT_DOUBLE, lexerValue);
	}
	if (tryParseKeyword("true"))
		return GValParserToken(GValParserToken::TT_TRUE, GVal());
	if (tryParseKeyword("false"))
		return GValParserToken(GValParserToken::TT_FALSE, GVal());
	if (tryParseKeyword("MAI"))
		return GValParserToken(GValParserToken::TT_MAI, GVal());
	if (tryParseKeyword("MAF"))
		return GValParserToken(GValParserToken::TT_MAF, GVal());
	if (tryParseKeyword("MAD"))
		return GValParserToken(GValParserToken::TT_MAD, GVal());
	if (tryParseKeyword("MAG"))
		return GValParserToken(GValParserToken::TT_MAG, GVal());
	int c = getChar();
	return GValParserToken(c, GVal());
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
		if (c == ' ' || c == '\t' || c == '\n' || c == '\n' || c == '\r' || c == EOF)
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
		buffer.clear();
		for (;;)
		{
			c = getChar();
			if (c == EOF)
			{
				error("premature end of file: unfinished string.");
				lexerValue = GVal(std::string(&buffer[0], buffer.size()));
				return true;
			}
			if (c == '\'')
			{
				lexerValue = GVal(std::string(&buffer[0], buffer.size()));
				return true;
			}
			buffer.push_back((char)c);
		}
	}
	returnChar(c);
	return false;
}

//         +-----------------------P1
//         |        +--------------P2
//         | P1.5   |       +------P3
//         v  v     v       v   v--P4
// [+|-] N+ [. [N*]] [e[+|-] N+] [f]
bool GValParser::tryParseNumber()
{
	int c = getChar();
	bool floatingPointDetected = false;
	int sign = 1;
	bool isFloat = false;
	buffer.clear();
	if (c == '+' || c == '-')
	{
		if (c == '-')
			sign = -1;
		buffer.push_back(c);
		c = getChar();
	}
	if (c < '0' || c > '9')
	{
		returnChar(c);
		if (!buffer.empty())
			returnChar(buffer.front());
		return false;
	}
	buffer.clear();
	for (;;)
	{
		advanceChar(c);
		if (c < '0' || c > '9')
			break;
	}
	// P1
	if (c == '.')
	{
		advanceChar(c);
		floatingPointDetected = true;
		// P1.5
		if (c >= '0' && c <= '9')
		{
			for (;;)
			{
				advanceChar(c);
				if (c < '0' || c > '9')
					break;
			}
		}
	}
	// P2
	if (c == 'E' || c == 'e')
	{
		advanceChar(c);
		if (c == '+' || c == '-')
			advanceChar(c);
		// P3
		if (c >= '0' && c <= '9')
		{
			for (;;)
			{
				advanceChar(c);
				if (c < '0' || c > '9')
					break;
			}
		}
		else
		{
			// TODO - Handle cases like 1.5e (without completed exponent).
		}
	}
	// P4
	if (c == 'f')
	{
		advanceChar(c);
		isFloat = true;
	}
	returnChar(c);
	buffer.push_back(0);
	if (floatingPointDetected)
	{
		if (isFloat)
			lexerValue.setFloat(float(sign) * (float)atof(&buffer[0]));
		else
			lexerValue.setDouble(double(sign) * atof(&buffer[0]));
	}
	else
	{
		lexerValue.setInt(sign * atoi(&buffer[0]));
	}
	return true;
}

bool GValParser::tryParseKeyword(const std::string &keyword)
{
	int n = (int)keyword.size();
	buffer.clear();
	for (int i = 0; i < n; i++)
	{
		int c = getChar();
		buffer.push_back(c);
		int t = keyword[i];
		if (c != t)
		{
			int m = (int)buffer.size();
			for (int i = 0; i < m; i++)
			{
				int t = buffer[m - i - 1];
				returnChar(t);
			}
			return false;
		}
	}
	return true;
}

void GValParser::advanceChar(int &c)
{
	buffer.push_back(c);
	c = getChar();
}

void GValParser::warning(const std::string &msg)
{
	progressReporter.warning(msg);
}

void GValParser::error(const std::string &msg)
{
	progressReporter.error(msg);
}

GVal gvParseString(const std::string &x)
{
	GValParser parser;
	return parser.parseString(x);
}

#ifndef __GVAL_PARSER_H
#define __GVAL_PARSER_H

#include <GValProgressReporter.h>
#include <GVal.h>
#include <string>
#include <vector>
#include <stdio.h>

class GValParserToken
{
public:
	GValParserToken();
	GValParserToken(int type_, const GVal &value_);

	enum TokenType { TT_TRUE, TT_FALSE, TT_INT, TT_FLOAT, TT_DOUBLE, TT_STRING };
	int type;
	GVal value;
};

class GValParser
{
public:
	enum ParserState { PS_NOT_OPENED, PS_PARSING_STRING, PS_PARSING_FILE };

	GValParser();
	~GValParser();

	GVal parseString(const std::string &s);
	GVal parseFile(const std::string &inputFileName);

	void openFile(const std::string &inputFileName);
	void openString(const std::string &s);

	int getChar();
	void returnChar(int c);
	int getCharFromStream();

	GVal parse();

	// lexer
	GValParserToken lex();
	void skipWhiteSpaceAndComments();
	bool skipWhiteSpace();
	bool skipComments();
	bool tryParseString();

	void warning(const std::string &msg);
	void error(const std::string &msg);

	std::vector<char> tmpChars;
	GVal lexerValue;
	ParserState parserState;
	GValProgressReporter progressReporter;
	std::string inputString;
	int inputStringPosition = 0;
	std::vector<int> returnedChars;
	std::vector<GValParserToken> returnedTokens;
	FILE *inputStream;
};

#endif

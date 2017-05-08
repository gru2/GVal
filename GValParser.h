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

	enum TokenType {
		TT_NULL = 256, TT_TRUE, TT_FALSE, TT_INT, TT_FLOAT,
		TT_DOUBLE, TT_STRING, TT_MAI, TT_MAF, TT_MAD, TT_MAG
	};
	int type;
	GVal value;

	bool isLiteral();
	GVal getValue();
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

	// parser
	GVal parse();
	GVal parseMap();
	void expectToken(int expectedTokenType);
	void parseSlot(const GValParserToken &token, GVal &v);
	GVal parseList();
	GVal parseMai();

	// lexer
	GValParserToken lex();
	void returnToken(const GValParserToken &token);
	GValParserToken getNextTokenFromStream();
	void skipWhiteSpaceAndComments();
	bool skipWhiteSpace();
	bool skipComments();
	bool tryParseString();
	bool tryParseNumber();
	bool tryParseKeyword(const std::string &keyword);
	void advanceChar(int &c);

	void warning(const std::string &msg);
	void error(const std::string &msg);

	std::vector<char> buffer;
	GVal lexerValue;
	ParserState parserState;
	GValProgressReporter progressReporter;
	std::string inputString;
	int inputStringPosition;
	std::vector<int> returnedChars;
	std::vector<GValParserToken> returnedTokens;
	FILE *inputStream;
};

#endif

#include <gtest.h>
#include "lexiconalysis.h"


namespace {
	std::set<std::string> func1 = { "sin(", "cos(", "(" };
	std::set<std::string> func2 = { "max(", "sin(" };
	std::unordered_map <std::string, std::string> variables;
	std::unordered_map <std::string, std::string> constants = { {"Pi", "3.14159265359"} };
}


TEST(Lexiconalysis, LexiconalysisbadInput1) {
	std::string input = "00.0";
	lexiconalysis lex;
	EXPECT_ANY_THROW(lex.analyse(input, variables, constants, func1, func2));   
}

TEST(Lexiconalysis, LexiconalysisbadInput2) {
	std::string input = "1+.+1";
	lexiconalysis lex;
	EXPECT_ANY_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisbadInput3) {
	std::string input = "1.1.";
	lexiconalysis lex;
	EXPECT_ANY_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisbadInput4) {
	std::string input = "1 + . + 2";
	lexiconalysis lex;
	EXPECT_ANY_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisbadInput5) {
	std::string input = "1ya = 12";
	lexiconalysis lex;
	EXPECT_ANY_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisbadInput6) {
	std::string input = "f(1, 2, 3)";
	lexiconalysis lex;
	EXPECT_ANY_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisbadInput7) {
	std::string input = ".12.";
	lexiconalysis lex;
	EXPECT_ANY_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisbadInput8) {
	std::string input = "Sin(1)";
	lexiconalysis lex;
	EXPECT_ANY_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisbadInput9) {
	std::string input = "y.a = 123";
	lexiconalysis lex;
	EXPECT_ANY_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisbadInput10) {
	std::string input = "1ya 234";
	lexiconalysis lex;
	EXPECT_ANY_THROW(lex.analyse(input, variables, constants, func1, func2));
}


TEST(Lexiconalysis, LexiconalysisGoodInput1) {
	std::string input = "1";
	lexiconalysis lex;
	EXPECT_NO_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisGoodInput2) {
	std::string input = "-1";
	lexiconalysis lex;
	EXPECT_NO_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisGoodInput3) {
	std::string input = "1.";
	lexiconalysis lex;
	EXPECT_NO_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisGoodInput4) {
	std::string input = ".1";
	lexiconalysis lex;
	EXPECT_NO_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisGoodInput5) {
	std::string input = "(1)";
	lexiconalysis lex;
	EXPECT_NO_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisGoodInput6) {
	std::string input = "     1      +2   ";
	lexiconalysis lex;
	EXPECT_NO_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisGoodInput7) {
	std::string input = "var";
	lexiconalysis lex;
	EXPECT_NO_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisGoodInput8) {
	std::string input = "max(1, 2, 3)";
	lexiconalysis lex;
	EXPECT_NO_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisGoodInput9) {
	std::string input = "sin(Pi / 2)";
	lexiconalysis lex;
	EXPECT_NO_THROW(lex.analyse(input, variables, constants, func1, func2));
}

TEST(Lexiconalysis, LexiconalysisGoodInput10) {
	std::string input = "1.0 * (-1 + 2.3) - sin(Pi/2) +      9";
	lexiconalysis lex;
	EXPECT_NO_THROW(lex.analyse(input, variables, constants, func1, func2));
}


TEST(lexiconalysis, LexiconalysisGoodReturn1) {
	std::string input = "1 + 1";
	lexiconalysis lex;
	
	std::vector<std::pair<std::string, std::string>> lexems = lex.analyse(input, variables, constants, func1, func2);
	std::vector<std::pair<std::string, std::string>> rightLexems{ {"integer", "1"}, {"operation", "+"}, {"integer", "1"}}; 

	EXPECT_EQ(rightLexems, lexems);
}

TEST(lexiconalysis, LexiconalysisGoodReturn2) {
	std::string input = "var = .0";
	lexiconalysis lex;

	std::vector<std::pair<std::string, std::string>> lexems = lex.analyse(input, variables, constants, func1, func2);
	std::vector<std::pair<std::string, std::string>> rightLexems{ {"variable", "var"}, {"equal", "="}, {"float", "0.00"} };

	EXPECT_EQ(rightLexems, lexems);
}

TEST(lexiconalysis, LexiconalysisGoodReturn3) {
	std::string input = "max(.2  ,  1.   )     ";
	lexiconalysis lex;

	std::vector<std::pair<std::string, std::string>> lexems = lex.analyse(input, variables, constants, func1, func2);
	std::vector<std::pair<std::string, std::string>> rightLexems{ {"func2", "max("}, {"float", "0.20"}, {"comma", ","}, {"float", "1.0"}, {"closing bracket", ")"} };

	EXPECT_EQ(rightLexems, lexems);
}

TEST(lexiconalysis, LexiconalysisGoodReturn4) {
	std::string input = "sin(var1 / Pi)";
	lexiconalysis lex;

	std::vector<std::pair<std::string, std::string>> lexems = lex.analyse(input, variables, constants, func1, func2);
	std::vector<std::pair<std::string, std::string>> rightLexems{ {"func1","sin("}, {"variable", "var1"}, {"operation", "/"}, {"constant", "Pi"},{"closing bracket", ")"}};

	EXPECT_EQ(rightLexems, lexems);
}

TEST(lexiconalysis, LexiconalysisGoodReturn5) {
	std::string input = "                ";
	lexiconalysis lex;

	std::vector<std::pair<std::string, std::string>> lexems = lex.analyse(input, variables, constants, func1, func2);
	std::vector<std::pair<std::string, std::string>> rightLexems{ };

	EXPECT_EQ(rightLexems, lexems);
}
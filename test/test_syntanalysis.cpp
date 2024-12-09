#include <gtest.h>
#include "syntanalysis.h"


namespace {
	std::set<std::string> func1 = { "sin(", "cos(", "(" };
	std::set<std::string> func2 = { "max(", "sin(" };
	std::unordered_map <std::string, std::string> variables;
	std::unordered_map <std::string, std::string> constants = { {"Pi", "3.14159265359"} };
}


TEST(Syntanalysis, SyntanalysisBadInput1) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"constant", "Pi"}, {"equal", "="}, {"float", "3.0"}};
	EXPECT_ANY_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisBadInput2) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"func1", "("}, {"closing bracket", ")"} };
	EXPECT_ANY_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisBadInput3) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"variable", "var"}, {"equal", "="}};
	EXPECT_ANY_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisBadInput4) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"float", "3.0"}, {"operation", "+"}, {"operation", "*"}, {"float", "2.0"}};
	EXPECT_ANY_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisBadInput5) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"operation", "*"}, {"float", "10.0"} };
	EXPECT_ANY_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisBadInput6) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"variable", "a"}, {"variable", "b"}, {"equal", "="}, {"float", "2.0"} };
	EXPECT_ANY_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisBadInput7) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"func1", "("}, {"float", "3.0"}, {"operation", "*"}, {"float", "2.0"}};
	EXPECT_ANY_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisBadInput8) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"func2", "max("}, {"comma", ","}, {"float", "3.0"}, {"closing bracket", ")"} };
	EXPECT_ANY_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisBadInput9) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"func2", "min("}, {"float", "3.0"}, {"comma", ","}, {"closing bracket", ")"} };
	EXPECT_ANY_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisBadInput10) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"func1", "sin("}, {"closing bracket", ")"} };
	EXPECT_ANY_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}


TEST(Syntanalysis, SyntanalysisGoodInput1) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"func1", "sin("}, {"constant", "Pi"}, {"closing bracket", ")"}};
	EXPECT_NO_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisGoodInput2) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"variable", "var"}, {"equal", "="}, {"float", "0.1"} };
	EXPECT_NO_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisGoodInput3) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"func2", "max("}, {"constant", "Pi"},{"comma", ","},{"float", "3.0"}, { "closing bracket", ")" }};
	EXPECT_NO_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisGoodInput4) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"operation", "-"}, {"constant", "Pi"} };
	EXPECT_NO_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

TEST(Syntanalysis, SyntanalysisGoodInput5) {
	syntanalysis syn;
	std::vector<std::pair<std::string, std::string>> lexems = { {"operation", "-"}, {"operation", "-"}, {"operation", "-"}, {"float", "0.3"} };
	EXPECT_NO_THROW(syn.analyse(lexems, variables, constants, func1, func2));
}

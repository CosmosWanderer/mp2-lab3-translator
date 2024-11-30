#include <gtest.h> 
#include "transformator.h"

// Поступает набор лексем, возвращаем этот набор в постфиксной форме

TEST(Transformator, GoodTransform1) {
	std::vector<std::pair<std::string, std::string>> lexems = { {"float","1.0"}, {"operation", "+"}, {"float", "2.0"}};
	std::vector<std::pair<std::string, std::string>> PostfixForm = { {"float","1.0"}, {"float", "2.0"}, {"operation", "+"} };
	transformator tr;

	EXPECT_EQ(PostfixForm, tr.transform(lexems));
}

TEST(Transformator, GoodTransform2) {
	std::vector<std::pair<std::string, std::string>> lexems = { {"operation","-u"}, {"float", "2.0"} };
	std::vector<std::pair<std::string, std::string>> PostfixForm = { {"float", "2.0"}, {"operation", "-u"} };
	transformator tr;

	EXPECT_EQ(PostfixForm, tr.transform(lexems));
}

TEST(Transformator, GoodTransform3) {
	std::vector<std::pair<std::string, std::string>> lexems = { {"float","1.0"}, {"operation", "+"}, {"float", "2.0"},  {"operation", "*"}, {"float", "3.0"} };
	std::vector<std::pair<std::string, std::string>> PostfixForm = { {"float","1.0"}, {"float", "2.0"}, {"float", "3.0"}, {"operation", "*"}, {"operation", "+"} };
	transformator tr;

	EXPECT_EQ(PostfixForm, tr.transform(lexems));
}


TEST(Transformator, GoodTransform4) {
	std::vector<std::pair<std::string, std::string>> lexems = { {"func1","sin("}, {"float", "2.0"},  {"operation", "*"}, {"float", "3.0"}, {"closing bracket", ")"} };
	std::vector<std::pair<std::string, std::string>> PostfixForm = {{"float", "2.0"}, {"float", "3.0"}, {"operation", "*"}, {"func1", "sin("} };
	transformator tr;

	EXPECT_EQ(PostfixForm, tr.transform(lexems));
}

TEST(Transformator, GoodTransform5) {
	std::vector<std::pair<std::string, std::string>> lexems = { {"func2","max("}, {"float", "2.0"},  {"comma", ","}, {"float", "3.0"}, {"closing bracket", ")"} };
	std::vector<std::pair<std::string, std::string>> PostfixForm = { {"float", "2.0"}, {"comma", ","}, {"float", "3.0"}, {"func2", "max("} };
	transformator tr;

	EXPECT_EQ(PostfixForm, tr.transform(lexems));
}
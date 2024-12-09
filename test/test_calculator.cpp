#include <gtest.h>
#include "calculator.h"


TEST(Calculator, GoodCalculation1) {
	std::vector<std::pair<std::string, std::string>> PostfixForm = { {"float", "2.0"}, {"comma", ","}, {"float", "3.0"}, {"func2", "max("} };
	calculator cl;
	std::string ans = cl.calculate(PostfixForm);

	std::string rightAns = "3.0";
	EXPECT_EQ(ans, rightAns);
}

TEST(Calculator, GoodCalculation2) {
	std::vector<std::pair<std::string, std::string>> PostfixForm = { {"float", "2.0"}, {"float", "1.5"}, { "float", "3.0" }, {"operation", "*"}, {"operation", "+"}};
	calculator cl;
	std::string ans = cl.calculate(PostfixForm);

	std::string rightAns = "6.50";
	EXPECT_EQ(ans, rightAns);
}

TEST(Calculator, GoodCalculation3) {
	std::vector<std::pair<std::string, std::string>> PostfixForm = { {"float", "2.0"}, {"float", "2.0"}, {"operation", "-"}, {"func1", "cos("} };
	calculator cl;
	std::string ans = cl.calculate(PostfixForm);

	std::string rightAns = "1.0";
	EXPECT_EQ(ans, rightAns);
}

TEST(Calculator, GoodCalculation4) {
	std::vector<std::pair<std::string, std::string>> PostfixForm = { {"float", "0.3"}, {"operation", "-u"} };
	calculator cl;
	std::string ans = cl.calculate(PostfixForm);

	std::string rightAns = "-0.30";
	EXPECT_EQ(ans, rightAns);
}

TEST(Calculator, GoodCalculation5) {
	std::vector<std::pair<std::string, std::string>> PostfixForm = { {"float", "1"}, {"float", "0.5"}, { "operation", "-u" }, {"operation",  "+"}};
	calculator cl;
	std::string ans = cl.calculate(PostfixForm);

	std::string rightAns = "0.50";
	EXPECT_EQ(ans, rightAns);
}


TEST(Calculator, ThrowIfDivisionByZero) {
	std::vector<std::pair<std::string, std::string>> PostfixForm = { {"float", "1.0"}, {"float", "0.0"}, { "operation", "/" }};
	calculator cl;
	EXPECT_ANY_THROW(cl.calculate(PostfixForm));
}
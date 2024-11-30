#include <gtest.h>
#include "translator.h"

// Получает на вход строчку, возвращает значение выражения/сохраняет значение в переменную. В случае проблем выкидывает ошибку


// Throw если ошибка в выражении

TEST(Translator, TranslatorBadInput1) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "1 + 2 * ()";
	EXPECT_ANY_THROW(tr.execute(input));
}

TEST(Translator, TranslatorBadInput2) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "max(, 12, 23)";
	EXPECT_ANY_THROW(tr.execute(input));
}

TEST(Translator, TranslatorBadInput3) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "1ar = 123";
	EXPECT_ANY_THROW(tr.execute(input));
}

TEST(Translator, TranslatorBadInput4) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "(123 + 32 ( 48 - 1))";
	EXPECT_ANY_THROW(tr.execute(input));
}

TEST(Translator, TranslatorBadInput5) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "sin( = 123";
	EXPECT_ANY_THROW(tr.execute(input));
}

TEST(Translator, TranslatorBadInput6) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "2 / 0";
	EXPECT_ANY_THROW(tr.execute(input));
}

TEST(Translator, TranslatorBadInput7) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "Pi = 4";
	EXPECT_ANY_THROW(tr.execute(input));
}

TEST(Translator, TranslatorBadInput8) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "a + b = 123";
	EXPECT_ANY_THROW(tr.execute(input));
}

TEST(Translator, TranslatorBadInput9) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "a.b = 1";
	EXPECT_ANY_THROW(tr.execute(input));
}

TEST(Translator, TranslatorBadInput10) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "*1";
	EXPECT_ANY_THROW(tr.execute(input));
}

// Правильно считает ответ

TEST(Translator, TranslatorRightAns1) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "1 + 2";
	std::string rightAns = "3.0";
	EXPECT_EQ(rightAns, tr.execute(input));
}

TEST(Translator, TranslatorRightAns2) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "sin(Pi/2)";
	std::string rightAns = "1.0";
	EXPECT_EQ(rightAns, tr.execute(input));
}

TEST(Translator, TranslatorRightAns3) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "20 - 4 * 3 + (3 - 2) * 2";
	std::string rightAns = "10.0";
	EXPECT_EQ(rightAns, tr.execute(input));
}

TEST(Translator, TranslatorRightAns4) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "max(1, 2, 3, 4, 10, 2, 3, 4, 0)";
	std::string rightAns = "10.0";
	EXPECT_EQ(rightAns, tr.execute(input));
}

TEST(Translator, TranslatorRightAns5) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	std::string input = "1 + sin(max(1, Pi) / 2)";
	std::string rightAns = "2.0";
	EXPECT_EQ(rightAns, tr.execute(input));
}

// Корректно записывает/считывает переменные

TEST(Translator, TranslatorWorkWithVariables1) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	tr.execute("var = 2.0");

	std::string rightAns = "2.0";
	EXPECT_EQ(rightAns, tr.execute("var"));
}
TEST(Translator, TranslatorWorkWithVariables2) {
	translator tr;
	tr.constants.insert({ "Pi", "3.14159265359" });
	tr.constants.insert({ "e", "2.7182" });
	functions f;
	std::set<std::string> f1 = f.func1;
	std::set<std::string> f2 = f.func2;
	tr.addFunctions(f1, f2);

	tr.execute("var = 2.0");
	tr.execute("rav = 0.15");
	tr.execute("var = var * 2 + rav + sin(Pi / 2)");

	std::string rightAns = "5.150";
	EXPECT_EQ(rightAns, tr.execute("var"));
}
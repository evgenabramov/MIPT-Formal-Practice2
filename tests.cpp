#include "gtest/gtest.h"
#include "Algo.h"

TEST(SimpleCase, OneTerminal) {
  Algo early_algorithm;
  Grammar grammar;
  std::vector<std::string> raw_rules_data = {
      "S->(S)S",
      "S->a"
  };
  for (const std::string& raw_format : raw_rules_data) {
    grammar.AddRule(raw_format);
  }
  EXPECT_TRUE(early_algorithm.Check(grammar, "(a)a"));
  EXPECT_TRUE(early_algorithm.Check(grammar, "((a)a)a"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "(b)b"));
}

TEST(EmptyRightPart, OneTypeOfBrackets) {
  Algo early_algorithm;
  Grammar grammar;
  std::vector<std::string> raw_rules_data = {
      "S->(S)S",
      "S->"
  };
  for (const std::string& raw_format : raw_rules_data) {
    grammar.AddRule(raw_format);
  }
  EXPECT_TRUE(early_algorithm.Check(grammar, "()()"));
  EXPECT_TRUE(early_algorithm.Check(grammar, "()"));
  EXPECT_TRUE(early_algorithm.Check(grammar, ""));
  EXPECT_TRUE(early_algorithm.Check(grammar, "((())(()())())"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "((())(()())()("));
  EXPECT_FALSE(early_algorithm.Check(grammar, "("));
}

TEST(EmptyRightPart, FewTypesOfBrackets) {
  Algo early_algorithm;
  Grammar grammar;
  std::vector<std::string> raw_rules_data = {
      "S->(S)S",
      "S->[S]S",
      "S->{S}S",
      "S->"
  };
  for (const std::string& raw_format : raw_rules_data) {
    grammar.AddRule(raw_format);
  }
  EXPECT_TRUE(early_algorithm.Check(grammar, "()[]"));
  EXPECT_TRUE(early_algorithm.Check(grammar, "{[]}"));
  EXPECT_TRUE(early_algorithm.Check(grammar, ""));
  EXPECT_TRUE(early_algorithm.Check(grammar, "{{{{}}}}[()]([])"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "{{{{{{]]]]]]"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "}[{}"));
}

TEST(RegularExpressions, TwoLettersAlphabet) {
  Algo early_algorithm;
  Grammar grammar;
  std::vector<std::string> raw_rules_data = {
      "S->0",
      "S->1",
      "S->a",
      "S->b",
      "S->(S*S)",
      "S->S*S",
      "S->(S+S)",
      "S->S+S",
      "S->(SS)",
      "S->SS"
  };
  for (const std::string& raw_format : raw_rules_data) {
    grammar.AddRule(raw_format);
  }
  EXPECT_TRUE(early_algorithm.Check(grammar, "a+b"));
  EXPECT_TRUE(early_algorithm.Check(grammar, "a*a+b"));
  EXPECT_TRUE(early_algorithm.Check(grammar, "(a+b)(a*ab)+1*b+0"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "a++a"));
  EXPECT_FALSE(early_algorithm.Check(grammar, ""));
  EXPECT_FALSE(early_algorithm.Check(grammar, "A+a"));
}

TEST(SameNumberOfLetters, TwoTerminals) {
  Algo early_algorithm;
  Grammar grammar;
  std::vector<std::string> raw_rules_data = {
      "S->aSbS",
      "S->bSaS",
      "S->"
  };
  for (const std::string& raw_format : raw_rules_data) {
    grammar.AddRule(raw_format);
  }
  EXPECT_TRUE(early_algorithm.Check(grammar, "ab"));
  EXPECT_TRUE(early_algorithm.Check(grammar, "ababbbaa"));
  EXPECT_TRUE(early_algorithm.Check(grammar, ""));
  EXPECT_FALSE(early_algorithm.Check(grammar, "abbbbb"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "a"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "bbb"));
}

TEST(NotOneDifferenceBetweenNumberOfLetters, TwoTerminals) {
  // {a^n b^m : n - m != 1}
  Algo early_algorithm;
  Grammar grammar;
  std::vector<std::string> raw_rules_data = {
      "S->aB",
      "B->aB",
      "B->aBb",
      "B->a",
      "S->C",
      "S->D",
      "C->Cb",
      "C->aCb",
      "C->b",
      "D->aDb",
      "D->"
  };
  for (const std::string& raw_format : raw_rules_data) {
    grammar.AddRule(raw_format);
  }
  EXPECT_TRUE(early_algorithm.Check(grammar, "ab"));
  EXPECT_TRUE(early_algorithm.Check(grammar, "aabb"));
  EXPECT_TRUE(early_algorithm.Check(grammar, ""));
  EXPECT_TRUE(early_algorithm.Check(grammar, "abb"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "aab"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "a"));
}

TEST(DoubledNumberOfLetters, TwoTerminals) {
  // {w : |w|_b = 2|w|_a && for each prefix w' |w'|_b <= 2|w'|_a}
  Algo early_algorithm;
  Grammar grammar;
  std::vector<std::string> raw_rules_data = {
      "S->",
      "S->aSbSbS"
  };
  for (const std::string& raw_format : raw_rules_data) {
    grammar.AddRule(raw_format);
  }
  EXPECT_TRUE(early_algorithm.Check(grammar, "abb"));
  EXPECT_TRUE(early_algorithm.Check(grammar, "aabbbb"));
  EXPECT_TRUE(early_algorithm.Check(grammar, ""));
  EXPECT_TRUE(early_algorithm.Check(grammar, "ababbb"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "b"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "ab"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "bba"));
}

TEST(TestForPractice, FirstVariant) {
  Algo early_algorithm;
  Grammar grammar;
  std::vector<std::string> raw_rules_data = {
      "S->C",
      "S->CS",
      "C->Dc",
      "D->aDb",
      "D->"
  };
  for (const std::string& raw_format : raw_rules_data) {
    grammar.AddRule(raw_format);
  }
  EXPECT_TRUE(early_algorithm.Check(grammar, "abcabc"));
  EXPECT_TRUE(early_algorithm.Check(grammar, "aabbcccaaabbbccc"));
  EXPECT_TRUE(early_algorithm.Check(grammar, "c"));
  EXPECT_TRUE(early_algorithm.Check(grammar, "ccccc"));
  EXPECT_FALSE(early_algorithm.Check(grammar, ""));
  EXPECT_FALSE(early_algorithm.Check(grammar, "aaaaaabbbbbcc"));
  EXPECT_FALSE(early_algorithm.Check(grammar, "aabb"));
}
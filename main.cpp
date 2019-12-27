#include <iostream>
#include "Algo.h"

int main() {
  Algo early_algorithm;
  Grammar grammar;

  std::cout << "Number of rules : ";
  size_t num_rules = 0;
  std::cin >> num_rules;

  std::cout << "Rules : \n";
  for (size_t i = 0; i < num_rules; ++i) {
    std::string raw_format;
    std::cin >> raw_format;
    try {
      grammar.AddRule(raw_format);
    } catch (std::exception& error) {
      std::cerr << error.what() << std::endl;
      return 1;
    }
  }

  std::cout << "Word to search : ";
  std::string word;
  std::cin >> word;

  if (early_algorithm.Check(grammar, word)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  std::cout << std::endl;
  return 0;
}
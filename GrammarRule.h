#pragma once

#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>

struct GrammarRule {
  explicit GrammarRule(const std::string& raw_format);

  GrammarRule(const std::string& left_part, const std::string& right_part);

  GrammarRule(const GrammarRule& other) = default;

  bool operator<(const GrammarRule& other) const;

  bool operator==(const GrammarRule& other) const;

  struct Symbol {
    Symbol() = default;
    Symbol(const Symbol& other) = default;
    explicit Symbol(const char symbol) : symbol_(symbol),
                                         is_terminal_(!isupper(symbol)) {}

    bool operator==(const Symbol& other) const;

    char symbol_;
    bool is_terminal_;
  };

  Symbol left_part_;
  std::vector<Symbol> right_part_;

  static const std::string transition_symbols;
};

#include "Grammar.h"

void Grammar::AddRule(const std::string& raw_format) {
  rules_.emplace_back(raw_format);
}

void Grammar::AddRule(const GrammarRule& rule) {
  rules_.push_back(rule);
}
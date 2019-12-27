#include "GrammarRule.h"

struct Grammar {
  void AddRule(const std::string& raw_format);

  void AddRule(const GrammarRule& rule);

  static const char start_symbol = 'S';

  std::vector<GrammarRule> rules_;
};

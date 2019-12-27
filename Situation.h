#include "GrammarRule.h"

struct Situation {
  Situation(const GrammarRule& rule, size_t previous_level_position, size_t point_position) :
      rule_(rule), previous_level_position_(previous_level_position), point_position_(point_position) {}

  Situation(const Situation& other) = default;

  bool CheckNextSymbolIsTerminal() const;

  bool CheckRuleCompleted() const;

  char GetNextSymbol() const;

  Situation MovePointRight() const;

  bool operator==(const Situation& other) const;

  bool operator<(const Situation& other) const;

  GrammarRule rule_;
  size_t previous_level_position_;
  size_t point_position_;
};
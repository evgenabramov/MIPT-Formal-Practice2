#include "Situation.h"
#include <tuple>

bool Situation::CheckNextSymbolIsTerminal() const {
  if (CheckRuleCompleted()) {
    return false;
  }
  return rule_.right_part_[point_position_].is_terminal_;
}

char Situation::GetNextSymbol() const {
  return rule_.right_part_[point_position_].symbol_;
}

bool Situation::CheckRuleCompleted() const {
  return point_position_ == rule_.right_part_.size();
}

Situation Situation::MovePointRight() const {
  return Situation(rule_, previous_level_position_, point_position_ + 1);
}

bool Situation::operator==(const Situation& other) const {
  return (rule_ == other.rule_ &&
      previous_level_position_ == other.previous_level_position_ &&
      point_position_ == other.point_position_);
}

bool Situation::operator<(const Situation& other) const {
  return std::make_tuple(rule_, previous_level_position_, point_position_)
      < std::make_tuple(other.rule_, other.previous_level_position_, other.point_position_);
}
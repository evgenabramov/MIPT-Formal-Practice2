#include "GrammarRule.h"

const std::string GrammarRule::transition_symbols = "->";

GrammarRule::GrammarRule(const std::string& left_part, const std::string& right_part) {
  if (left_part.empty()) {
    throw std::invalid_argument("Bad rule input format\n"
                                "Left part of the rule is empty");
  }

  if (left_part.size() > 1) {
    throw std::invalid_argument("Bad rule input\n"
                                "Grammar is not context-free (more than 1 symbol in left part)");
  }

  left_part_ = Symbol(left_part[0]);
  if (left_part_.is_terminal_) {
    throw std::invalid_argument("Bad rule input\n"
                                "Grammar is not context-free (has terminal symbols in left part)");
  }

  for (const char& symbol : right_part) {
    right_part_.emplace_back(symbol);
  }
}

GrammarRule::GrammarRule(const std::string& raw_format) {
  if (raw_format.find(transition_symbols) == -1) {
    throw std::invalid_argument("Bad rule input\n"
                                "Format : [Left Part (not empty)]->[Right Part (may be empty)]");
  }
  size_t entry_index = raw_format.find(transition_symbols);
  *this = GrammarRule(raw_format.substr(0, entry_index),
                      raw_format.substr(entry_index + transition_symbols.size()));
}

bool GrammarRule::Symbol::operator==(const Symbol& other) const {
  return symbol_ == other.symbol_;
}

bool GrammarRule::operator==(const GrammarRule& other) const {
  return left_part_ == other.left_part_ && right_part_ == other.right_part_;
}

bool GrammarRule::operator<(const GrammarRule& other) const {
  if (left_part_.symbol_ != other.left_part_.symbol_) {
    return left_part_.symbol_ < other.left_part_.symbol_;
  }
  size_t min_right_part_size = std::min(right_part_.size(), other.right_part_.size());
  for (size_t index = 0; index < min_right_part_size; ++index) {
    if (right_part_[index].symbol_ < other.right_part_[index].symbol_) {
      return true;
    }
  }
  return right_part_.size() < other.right_part_.size();
}
#include "Algo.h"

bool Algo::Check(Grammar grammar, const std::string& word) {
  grammar_ = grammar;
  word_ = word;
  situation_lists_.clear();
  situation_lists_.resize(word.size() + 1);
  Situation fake_start_situation = GetFakeStartSituation();
  situation_lists_[0].insert(fake_start_situation);
  for (size_t position = 0; position <= word.size(); ++position) {
    Scan(position);
    size_t old_situation_list_size = 0;
    do {
      old_situation_list_size = situation_lists_[position].size();
      Complete(position);
      Predict(position);
    } while (situation_lists_[position].size() != old_situation_list_size);
  }
  Situation final_situation = fake_start_situation.MovePointRight();
  const std::set<Situation>& last_situation_list = situation_lists_[word.size()];
  return (std::find(last_situation_list.begin(),
                    last_situation_list.end(), final_situation) != last_situation_list.end());
}

Situation Algo::GetFakeStartSituation() {
  std::string fake_rule_raw_format = std::string(1, Grammar::start_symbol) + "->" + Grammar::start_symbol;
  GrammarRule fake_rule(fake_rule_raw_format);
  fake_rule.left_part_.symbol_ = fake_start_symbol;
  grammar_.AddRule(fake_rule);
  return Situation(fake_rule, 0, 0);
}

void Algo::Scan(size_t position) {
  if (position == 0) {
    return;
  }
  for (const Situation& situation : situation_lists_[position - 1]) {
    if (situation.CheckNextSymbolIsTerminal() && situation.GetNextSymbol() == word_[position - 1]) {
      situation_lists_[position].insert(situation.MovePointRight());
    }
  }
}

void Algo::Predict(size_t position) {
  for (Situation situation : situation_lists_[position]) {
    if (!situation.CheckRuleCompleted() && !situation.CheckNextSymbolIsTerminal()) {
      for (const GrammarRule& rule : grammar_.rules_) {
        if (situation.GetNextSymbol() == rule.left_part_.symbol_) {
          situation_lists_[position].insert(Situation(rule, position, 0));
        }
      }
    }
  }
}

void Algo::Complete(size_t position) {
  for (const Situation& situation : situation_lists_[position]) {
    if (situation.CheckRuleCompleted()) {
      for (const Situation& upper_situation : situation_lists_[situation.previous_level_position_]) {
        if (!upper_situation.CheckRuleCompleted() && upper_situation.GetNextSymbol() == situation.rule_.left_part_.symbol_) {
          situation_lists_[position].emplace(upper_situation.MovePointRight());
        }
      }
    }
  }
}

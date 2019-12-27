#include "Grammar.h"
#include "Situation.h"
#include "set"

class Algo {
 public:
  bool Check(Grammar grammar, const std::string& word);

 private:
  Situation GetFakeStartSituation();

  void Scan(size_t position);

  void Predict(size_t position);

  void Complete(size_t position);

  Grammar grammar_;
  std::string word_;
  std::vector<std::set<Situation>> situation_lists_;
  static const char fake_start_symbol = '$';
};
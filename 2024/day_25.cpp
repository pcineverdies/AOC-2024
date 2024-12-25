#include "../common/common.h"

static void solve() {
  std::string input = aoc::getInput("2024/day_25.txt");

  aoc::result_t result;
  vvu_t keys;
  vvu_t locks;
  vvc_t schematic;

  auto isRowFull = [](const vc_t &row) -> b {
    return std::ranges::all_of(row, [](c c) { return c == '#'; });
  };

  auto countColumns = [](const vvc_t &schematic) -> vu_t {
    vu_t ans(schematic[0].size(), -1);
    for (u j = 0; j < schematic[0].size(); j++) {
      for (const auto &r : schematic)
        ans[j] += (r[j] == '#');
    }
    return ans;
  };

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    if (line.size() < 2) {
      if (isRowFull(schematic[0]))
        locks.push_back(countColumns(schematic));
      else
        keys.push_back(countColumns(schematic));
      schematic.clear();
    } else {
      schematic.push_back(aoc::strToVectorChar(line));
    }
    return aoc::ExitCode(aoc::Code::OK);
  });

  for (auto &key : keys) {
    for (auto &lock : locks) {
      bool correct = true;
      for (u i = 0; i < 5; i++)
        correct = correct and (key[i] + lock[i] <= 5);
      result.first += correct;
    }
  }

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

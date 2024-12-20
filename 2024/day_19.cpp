#include "../common/common.h"

static std::unordered_map<s, u> memo = {{"", 1}};
static vs_t towels;

static u tryBuild(const s &target) {
  u sum = 0;

  if (memo.contains(target))
    return memo.at(target);

  for (auto &av : towels)
    if (target.substr(0, av.size()) == av)
      sum += tryBuild(target.substr(av.size()));

  memo.insert({target, sum});

  return sum;
}

static void solve() {
  std::string input = aoc::getInput("2024/day_19.txt");
  aoc::result_t result;

  aoc::forLineVoid(input, [&](const s &line) {
    if (line.find(',') != std::string::npos) {
      aoc::forMatchesVoid(line, rx(R"(\w+)"),
                          [&](const s &match) { towels.push_back(match); });
    } else if (line.find(',') == std::string::npos and line.size() != 0) {
      u alt = tryBuild(line);
      result.first += !(alt == 0), result.second += alt;
    }
  });

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

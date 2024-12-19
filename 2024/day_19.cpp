#include "../common/common.h"

static std::unordered_map<s, u> memo = {{"", 1}};
static vs_t towels, designs;

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
  u counter = 0;

  aoc::forLineVoid(input, [&](const s &line) {
    if (counter++ == 0) {
      aoc::forMatchesVoid(line, rx(R"(\w+)"),
                          [&](const s &match) { towels.push_back(match); });
    } else
      designs.push_back(line);
  });

  designs.erase(designs.begin());

  for (auto &t : designs) {
    u alternatives = tryBuild(t);
    result.first += (alternatives == 0) ? 0 : 1;
    result.second += alternatives;
  }

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

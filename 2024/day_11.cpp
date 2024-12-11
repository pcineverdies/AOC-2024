#include "../common/common.h"

static std::map<std::pair<u, u>, u> memo;

static u step(u stone, u iter) {

  if (iter == 0)
    return 1;

  auto digits = [](u num) -> u { return (u)(log10(abs((long long)num))) + 1; };

  if (memo.contains({stone, iter}))
    return memo[{stone, iter}];

  u d = digits(stone);
  u ans = 0;
  if (stone == 0) {
    ans = step(1, iter - 1), memo.insert({{1, iter - 1}, ans});
  } else if ((d & 1) == 0) {
    u s1 = stone / (u)pow(10, d / 2), s2 = stone % (u)pow(10, d / 2);
    u a1 = step(s1, iter - 1), a2 = step(s2, iter - 1);
    memo.insert({{s1, iter - 1}, a1}), memo.insert({{s2, iter - 1}, a2});
    ans = a1 + a2;
  } else {
    ans = step(stone * 2024, iter - 1);
    memo.insert({{stone * 2024, iter - 1}, ans});
  }
  return ans;
}

static void solve() {
  std::string input = aoc::getInput("2024/day_11.txt");

  aoc::result_t result;
  vu_t stones;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    stones = aoc::strToVector(line);
    return aoc::ExitCode(aoc::Code::OK);
  });

  for (auto &x : stones)
    result.first += step(x, 25), result.second += step(x, 75);

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

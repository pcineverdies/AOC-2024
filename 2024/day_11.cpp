#include "../common/common.h"

static std::map<std::pair<u, u>, u> memo;

static u step(u s, u i) {

  if (i == 0)
    return 1;

  if (memo.contains({s, i}))
    return memo[{s, i}];

  u d = log10(abs((long long)s)) + 1, ans = 0;
  u ns = (s == 0) ? 1 : s * 2024;

  if (s and !(d & 1)) {
    u s1 = s / (u)pow(10, d / 2), s2 = s % (u)pow(10, d / 2);
    u a1 = step(s1, i - 1), a2 = step(s2, i - 1);
    memo.insert({{s1, i - 1}, a1}), memo.insert({{s2, i - 1}, a2});
    ans = a1 + a2;
  } else
    ans = step(ns, i - 1), memo.insert({{ns, i - 1}, ans});

  return ans;
}

static void solve() {
  std::string input = aoc::getInput("2024/day_11.txt");

  aoc::result_t result;
  vu_t stones;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    stones = aoc::strToVector(line);
    for (auto &x : stones)
      result.first += step(x, 25), result.second += step(x, 75);
    return aoc::ExitCode(aoc::Code::OK);
  });

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

#include "../common/common.h"

static u dfs(const vvc_t &grid, u s, u t, usu_t &r) {

  if (t == '9' + 1) {
    r.insert(s);
    return 1;
  }

  u ans = 0;

  if ((u)aoc::get(grid, s >> 16, (s + 1) & 0xffff).value_or(0) == t)
    ans += dfs(grid, s + 1, t + 1, r);
  if ((u)aoc::get(grid, s >> 16, (s - 1) & 0xffff).value_or(0) == t)
    ans += dfs(grid, s - 1, t + 1, r);
  if ((u)aoc::get(grid, (s + 0x10000) >> 16, s & 0xffff).value_or(0) == t)
    ans += dfs(grid, s + 0x10000, t + 1, r);
  if ((u)aoc::get(grid, (s - 0x10000) >> 16, s & 0xffff).value_or(0) == t)
    ans += dfs(grid, s - 0x10000, t + 1, r);

  return ans;
}

static void solve() {
  std::string input = aoc::getInput("2024/day_10.txt");

  aoc::result_t result;
  vvc_t grid;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    grid.push_back(aoc::strToVectorChar(line));
    return aoc::ExitCode(aoc::Code::OK);
  });

  aoc::forIndex(0, grid.size(), 0, grid[0].size(), [&](u i, u j) {
    if (grid[i][j] == '0') {
      usu_t reached;
      result.second += dfs(grid, (i << 16) + j, '1', reached);
      result.first += reached.size();
    }
  });

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

#include "../common/common.h"

static void dfs(const vvc_t &g, u s, u t, usu_t &r, u &ans) {

  if (t == ':')
    r.insert(s), ans++;
  else {
    if ((u)aoc::get(g, s + aoc::R).value_or(0) == t)
      dfs(g, s + aoc::R, t + 1, r, ans);
    if ((u)aoc::get(g, s + aoc::L).value_or(0) == t)
      dfs(g, s + aoc::L, t + 1, r, ans);
    if ((u)aoc::get(g, s + aoc::U).value_or(0) == t)
      dfs(g, s + aoc::U, t + 1, r, ans);
    if ((u)aoc::get(g, s + aoc::D).value_or(0) == t)
      dfs(g, s + aoc::D, t + 1, r, ans);
  }
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
      dfs(grid, aoc::getCoordinate(i, j), '1', reached, result.second);
      result.first += reached.size();
    }
  });

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

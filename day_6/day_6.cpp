#include "../common/common.h"
#include <cassert>

using usu_t = std::unordered_set<u>;

static bool explore(const vvc_t &g, usu_t &v, usu_t &p, u i, u d, usu_t &o,
                    b t = false) {

  if (p.contains((d << 16) + i))
    return true;
  p.insert((d << 16) + i);

  if (!t)
    v.insert(i);

  u ni = d == 0 ? i - 256 : d == 1 ? i + 1 : d == 2 ? i + 256 : i - 1;
  u nd = (d + 1) % 4;

  auto next = aoc::get(g, ni >> 8, ni & 255);
  if (!next.has_value())
    return false;

  if (!t and next.value() != '#' and !o.contains(ni) and !v.contains(ni)) {
    usu_t cp = p, co = {ni};
    if (explore(g, v, cp, i, nd, co, true))
      o.insert(ni);
  }

  return next.value() == '#' or (t and o.contains(ni))
             ? explore(g, v, p, i, nd, o, t)
             : explore(g, v, p, ni, d, o, t);
}

static void solve() {
  std::string input = aoc::getInput("day_6/input.txt");

  aoc::result_t result;
  vvc_t grid;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    grid.push_back(aoc::strToVectorChar(line));
    return aoc::ExitCode(aoc::Code::OK);
  });

  u ii = 0;
  for (u i = 0; i < grid.size(); i++) {
    for (u j = 0; j < grid[0].size(); j++)
      ii = (grid[i][j] == '^') ? (i << 8) + j : ii;
  }

  usu_t visited, positions, obstacles;
  explore(grid, visited, positions, ii, 0, obstacles);
  result.first = visited.size();
  result.second =
      obstacles.contains(ii) ? obstacles.size() - 1 : obstacles.size();

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

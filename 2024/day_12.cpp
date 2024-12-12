#include "../common/common.h"

static usu_t coveredPlot;
using mvu_t = std::unordered_map<u, vu_t>;

static u countEdges(mvu_t &dirs) {

  u ans = 4;

  auto s = [](u a, u b, bool horizontal = true) -> bool {
    auto [cay, cax] = aoc::getCoordinate(a);
    auto [cby, cbx] = aoc::getCoordinate(b);
    if (horizontal)
      std::swap(cay, cax), std::swap(cby, cbx);
    return cay < cby or (cay == cby and cax > cbx);
  };

  auto count = [&](const vu_t &v, bool horizontal) {
    for (u i = 0; i < v.size() - 1; i++) {
      uu e = aoc::getCoordinate(v[i]), en = aoc::getCoordinate(v[i + 1]);
      if (horizontal)
        std::swap(e.first, e.second), std::swap(en.first, en.second);
      ans += (e.first != en.first or e.second != en.second + 1);
    }
  };

  std::sort(dirs[aoc::U].begin(), dirs[aoc::U].end(),
            [&](u a, u b) { return s(a, b, false); });
  std::sort(dirs[aoc::D].begin(), dirs[aoc::D].end(),
            [&](u a, u b) { return s(a, b, false); });
  std::sort(dirs[aoc::R].begin(), dirs[aoc::R].end(), s);
  std::sort(dirs[aoc::L].begin(), dirs[aoc::L].end(), s);
  count(dirs[aoc::D], false), count(dirs[aoc::U], false);
  count(dirs[aoc::R], true), count(dirs[aoc::L], true);

  return ans;
}

static std::pair<u, u> bfs(const vvc_t &grid, u start, mvu_t &dirs) {

  if (coveredPlot.contains(start))
    return {0, 0};
  coveredPlot.insert(start);

  u a = 1, p = 0;
  auto explore = [&](u dir) {
    auto m = aoc::get(grid, start + dir);
    if (m.has_value() and m.value() == aoc::get(grid, start).value()) {
      auto res = bfs(grid, start + dir, dirs);
      a += res.first, p += res.second;
    } else
      dirs[dir].push_back(start), p += 1;
  };

  explore(aoc::L), explore(aoc::R), explore(aoc::U), explore(aoc::D);

  return {a, p};
}

static void solve() {
  std::string input = aoc::getInput("2024/day_12.txt");

  aoc::result_t result;
  vvc_t grid;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    grid.push_back(aoc::strToVectorChar(line));
    return aoc::ExitCode(aoc::Code::OK);
  });

  aoc::forIndex(0, grid.size(), 0, grid[0].size(), [&](u i, u j) {
    if (!coveredPlot.contains(aoc::getCoordinate(i, j))) {
      mvu_t dirs;
      auto res = bfs(grid, aoc::getCoordinate(i, j), dirs);
      result.first += res.first * res.second;
      result.second += res.first * countEdges(dirs);
    }
  });

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

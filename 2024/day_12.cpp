#include "../common/common.h"

static usu_t coveredPlot;
using mvu_t = std::unordered_map<u, vu_t>;

static u countEdges(mvu_t &dirs) {

  auto sv = [](u a, u b) -> bool {
    auto ca = aoc::getCoordinate(a), cb = aoc::getCoordinate(b);
    return ca.first < cb.first or
           (ca.first == cb.first and ca.second > cb.second);
  };
  auto sh = [](u a, u b) -> bool {
    auto ca = aoc::getCoordinate(a), cb = aoc::getCoordinate(b);
    return ca.second < cb.second or
           (ca.second == cb.second and ca.first > cb.first);
  };

  std::sort(dirs[aoc::U].begin(), dirs[aoc::U].end(), sv);
  std::sort(dirs[aoc::D].begin(), dirs[aoc::D].end(), sv);
  std::sort(dirs[aoc::R].begin(), dirs[aoc::R].end(), sh);
  std::sort(dirs[aoc::L].begin(), dirs[aoc::L].end(), sh);

  u nedges = 4;

  auto countv = [&](const vu_t &v) {
    for (u i = 0; i < v.size() - 1; i++) {
      auto edge = aoc::getCoordinate(v[i]);
      auto edgeNext = aoc::getCoordinate(v[i + 1]);
      if (edge.first != edgeNext.first or edge.second != edgeNext.second + 1)
        nedges++;
    }
  };

  auto counth = [&](const vu_t &v) {
    for (u i = 0; i < v.size() - 1; i++) {
      auto edge = aoc::getCoordinate(v[i]);
      auto edgeNext = aoc::getCoordinate(v[i + 1]);
      if (edge.second != edgeNext.second or edge.first != edgeNext.first + 1)
        nedges++;
    }
  };

  countv(dirs[aoc::D]), countv(dirs[aoc::U]);
  counth(dirs[aoc::R]), counth(dirs[aoc::L]);

  return nedges;
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

  for (u i = 0; i < grid.size(); i++) {
    for (u j = 0; j < grid[0].size(); j++) {
      u plot = aoc::getCoordinate(i, j);
      if (!coveredPlot.contains(plot)) {
        mvu_t dirs;
        auto res = bfs(grid, plot, dirs);
        result.first += res.first * res.second;
        result.second += res.first * countEdges(dirs);
      }
    }
  }

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

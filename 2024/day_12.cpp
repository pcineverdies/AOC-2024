#include "../common/common.h"

using namespace aoc;
static usu_t coveredPlot;
static vvc_t grid;

static std::tuple<u, u, u> bfs(u s) {

  u a = 1, p = 0, e = 0;
  if (coveredPlot.contains(s))
    return {0, 0, 0};
  coveredPlot.insert(s);

  auto v = [&s](u d) {
    auto m = aoc::get(grid, s + d);
    return m.has_value() and m.value() == aoc::get(grid, s).value();
  };

  auto x = [&v, &s, &a, &p, &e](u d) {
    if (v(d)) {
      auto r = bfs(s + d);
      a += std::get<0>(r), p += std::get<1>(r), e += std::get<2>(r);
    } else
      p += 1;
  };

  x(L), x(R), x(U), x(D);

  e += (!(v(L) || v(U)) + !(v(L) || v(D)) + !(v(R) || v(U)) + !(v(R) || v(D)) +
        (v(L) && v(D) && !v(DL)) + (v(L) && v(U) && !v(UL)) +
        (v(R) && v(U) && !v(UR)) + (v(R) && v(D) && !v(DR)));

  return {a, p, e};
}

static void solve() {
  std::string input = aoc::getInput("2024/day_12.txt");

  aoc::result_t result;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    grid.push_back(aoc::strToVectorChar(line));
    return aoc::ExitCode(aoc::Code::OK);
  });

  aoc::forIndex(0, grid.size(), 0, grid[0].size(), [&](u i, u j) {
    if (!coveredPlot.contains(aoc::getCoordinate(i, j))) {
      auto res = bfs(aoc::getCoordinate(i, j));
      result.first += std::get<0>(res) * std::get<1>(res);
      result.second += std::get<0>(res) * std::get<2>(res);
    }
  });

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

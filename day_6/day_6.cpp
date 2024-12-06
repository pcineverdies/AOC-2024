#include "../common/common.h"
#include <cassert>

using usu_t = std::unordered_set<u>;

static bool explore(const vvc_t &grid, usu_t &points, usu_t &positions,
                    usu_t &obs, u point, u dir, b spec = false) {

  if (positions.contains((dir << 16) + point))
    return true;

  positions.insert((dir << 16) + point);

  if (!spec)
    points.insert(point);

  u pointNext = dir == 0   ? point - 0x100
                : dir == 1 ? point + 1
                : dir == 2 ? point + 0x100
                           : point - 1;

  auto next = aoc::get(grid, pointNext >> 8, pointNext & 0xff);
  if (!next.has_value())
    return false;

  if (!spec and next.value() != '#' and !obs.contains(pointNext) and
      !points.contains(pointNext)) {
    usu_t pc = positions, oc = {pointNext};
    if (explore(grid, points, pc, oc, point, (dir + 1) % 4, true))
      obs.insert(pointNext);
  }

  return next.value() == '#' or (spec and obs.contains(pointNext))
             ? explore(grid, points, positions, obs, point, (dir + 1) % 4, spec)
             : explore(grid, points, positions, obs, pointNext, dir, spec);
}

static void solve() {
  std::string input = aoc::getInput("day_6/input.txt");

  aoc::result_t result;
  vvc_t grid;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    grid.push_back(aoc::strToVectorChar(line));
    return aoc::ExitCode(aoc::Code::OK);
  });

  u index = 0;
  aoc::forIndex(0, grid.size(), 0, grid[0].size(), [&](int i, int j) {
    index = (grid[i][j] == '^') ? (i << 8) + j : index;
  });

  usu_t visited, positions, obstacles;
  explore(grid, visited, positions, obstacles, index, 0);
  result = {visited.size(), obstacles.size()};

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

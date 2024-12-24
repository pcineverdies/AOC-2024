#include "../common/common.h"
static vvc_t grid;

static vu_t getPath(u start, u end) {
  vu_t ans;

  ans.push_back(start);
  while (start != end) {
    for (auto &dir : aoc::DIRS) {
      if (aoc::get(grid, start + dir) != '#' and
          (ans.size() < 2 or ans[ans.size() - 2] != start + dir)) {
        start += dir;
        break;
      }
    }
    ans.push_back(start);
  }

  return ans;
}

static u cheatCount(const vu_t &path, u limit) {

  u ans = 0, il = path.size() - 1;

  for (u i = 0; i < path.size(); i++) {
    for (u j = i + 1; j < path.size(); j++) {
      u d = aoc::manhattan(path[i], path[j]);
      u nl = i + (path.size() - j) + d - 1;
      ans += (d <= limit and nl < il and il - nl >= 100);
    }
  }

  return ans;
}

static void solve() {
  std::string input = aoc::getInput("2024/day_20.txt");

  u start = 0, end = 0;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    grid.push_back(aoc::strToVectorChar(line));
    return aoc::ExitCode(aoc::Code::OK);
  });

  aoc::forIndex(0, grid.size(), 0, grid[0].size(), [&](u i, u j) {
    start = grid[i][j] == 'S' ? aoc::getCoordinate(i, j) : start;
    end = grid[i][j] == 'E' ? aoc::getCoordinate(i, j) : end;
  });

  auto path = getPath(start, end);
  aoc::printResult({cheatCount(path, 2), cheatCount(path, 20)});
}

int main(int argc, char *argv[]) { solve(); }

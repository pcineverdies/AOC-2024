#include "../common/common.h"

#define W 71
#define M 1024

static void explore(const vu_t &grid, uu &result) {

  struct Path {
    u position;
    usu_t visited;

    Path(u p, usu_t v) : position(p), visited(std::move(v)) {}

    bool operator<(const Path &rhs) const {
      return visited.size() > rhs.visited.size();
    }
  };

  for (u i = M; i < grid.size(); i++) {
    u pathLength = -1;
    std::priority_queue<Path> queue;
    umuu_t scoreTile;
    Path path(0, {0});

    queue.emplace(path);

    while (!queue.empty()) {

      path = queue.top();
      queue.pop();

      if (path.position == aoc::getCoordinate(W - 1, W - 1)) {
        pathLength = path.visited.size();
        break;
      }

      for (auto &dir : aoc::DIRS) {

        auto next = path.position + dir;
        Path newPath(next, path.visited);
        newPath.visited.insert(next);

        if ((next >> 16) >= W or (next & 0xffff) >= W or
            (std::find(grid.begin(), grid.begin() + i, next) !=
             grid.begin() + i) or
            path.visited.contains(next) or
            (scoreTile.contains(next) and
             scoreTile[next] <= newPath.visited.size()))
          continue;

        scoreTile[next] = newPath.visited.size();
        queue.push(newPath);
      }
    }

    if (i == M)
      result.first = pathLength;

    if (pathLength == (u)-1) {
      result.second = i;
      return;
    }

    while (!path.visited.contains(grid[i + 1]))
      i++;
  }
}

static void solve() {
  std::string input = aoc::getInput("2024/day_18.txt");

  aoc::result_t result;
  vu_t bytes;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    auto nums = aoc::strToVector(line);
    bytes.push_back(aoc::getCoordinate(nums[1], nums[0]));
    return aoc::ExitCode(aoc::Code::OK);
  });

  explore(bytes, result);
  auto [y, x] = aoc::getCoordinate(bytes[result.second - 1]);
  std::cout << aoc::Color::CYAN << "~> Part 1 result: " << aoc::Color::RESET
            << result.first << std::endl;
  std::cout << aoc::Color::CYAN << "~> Part 2 result: " << aoc::Color::RESET
            << x << "," << y << std::endl;
}

int main(int argc, char *argv[]) { solve(); }

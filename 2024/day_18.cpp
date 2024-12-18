#include "../common/common.h"

#define W 71
#define M 1024

static void explore(const vu_t &grid, uu &result) {

  const u end = aoc::getCoordinate(W - 1, W - 1);

  struct Path {
    u position;
    u length;
    usu_t visited;

    Path(u p, u l, usu_t &v) : position(p), length(l), visited(v) {}

    bool operator<(const Path &rhs) const { return length > rhs.length; }
  };

  for (u i = M; i < grid.size(); i++) {
    u pathLength = -1;
    std::priority_queue<Path> queue;
    std::unordered_map<u, u> scoreTile;
    usu_t visited;
    queue.emplace(0, 0, visited);

    while (!queue.empty()) {

      Path path = queue.top();
      queue.pop();

      if (path.position == end) {
        pathLength = path.length;
        break;
      }

      for (auto &dir : aoc::DIRS) {

        auto next = path.position + dir;
        auto [ny, nx] = aoc::getCoordinate(next);
        if (ny >= W or nx >= W or
            (std::find(grid.begin(), grid.begin() + i, next) !=
             grid.begin() + i) or
            path.visited.contains(next) or
            (scoreTile.contains(next) and scoreTile[next] <= path.length + 1))
          continue;

        scoreTile[next] = path.length + 1;

        Path newPath(next, path.length + 1, path.visited);
        newPath.visited.insert(next);

        queue.push(newPath);
      }
    }

    if (i == M)
      result.first = pathLength;

    if (pathLength == (u)-1) {
      result.second = i;
      return;
    }
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
  std::cout << x << "," << y << std::endl;

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

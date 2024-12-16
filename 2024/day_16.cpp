#include "../common/common.h"
#include <climits>

static uu findMinPath(const vvc_t &map, u start, u end) {

  struct Path {
    u dir;
    u pos;
    u estimated;
    u length;
    u rounds;
    usu_t visited;

    Path(u d, u p, u l, u r, usu_t &v, u end)
        : dir(d), pos(p), length(l), rounds(r), visited(v) {
      auto [y1, x1] = aoc::getCoordinate(pos);
      auto [y0, x0] = aoc::getCoordinate(end);
      estimated = std::abs((ii)y1 - (ii)y0) + std::abs((ii)x1 - (ii)x0);
    }

    u score() const { return length + 1000 * rounds; }

    bool operator<(const Path &rhs) const {
      const u factor = 500;
      return score() + estimated * factor >
             rhs.score() + rhs.estimated * factor;
    }
  };

  std::priority_queue<Path> queue;
  vu_t dirs = {aoc::D, aoc::U, aoc::L, aoc::R};
  std::unordered_set<u> visited;

  visited.insert(start);

  queue.emplace(aoc::R, start, 0, 0, visited, end);
  u bestPathScore = 0;

  while (!queue.empty()) {
    auto path = queue.top();
    queue.pop();
    if (path.score() > 100000)
      std::cout << path.score() << std::endl;

    if (path.pos == end) {
      if (bestPathScore == 0)
        bestPathScore = path.score();
      if (path.score() == bestPathScore) {
        for (auto &x : path.visited)
          visited.insert(x);
      } else {
        return {bestPathScore, visited.size()};
      }
    }

    for (auto &dir : dirs) {

      if (path.visited.contains((path.pos + dir)) or
          (aoc::get(map, path.pos + dir).value() == '#'))
        continue;

      path.visited.insert(path.pos + dir);
      queue.emplace(dir, path.pos + dir, path.length + 1,
                    path.rounds + (dir != path.dir), path.visited, end);
      path.visited.erase(path.pos + dir);
    }
  }

  return {bestPathScore, visited.size()};
}

static void solve() {
  std::string input = aoc::getInput("2024/day_16.txt");

  aoc::result_t result;
  vvc_t map;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    map.push_back(aoc::strToVectorChar(line));
    return aoc::ExitCode(aoc::Code::OK);
  });

  u start = 0, end = 0;
  for (u i = 0; i < map.size(); i++) {
    for (u j = 0; j < map[0].size(); j++) {
      if (map[i][j] == 'S')
        start = aoc::getCoordinate(i, j);
      if (map[i][j] == 'E')
        end = aoc::getCoordinate(i, j);
    }
  }

  result = findMinPath(map, start, end);
  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

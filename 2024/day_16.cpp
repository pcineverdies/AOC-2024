#include "../common/common.h"
#include <climits>

static uu findMinPath(const vvc_t &map, u start, u end) {

  struct Path {
    u position;
    u direction;
    u score;
    usu_t visited;

    Path(u p, u d, u s, usu_t &v)
        : position(p), direction(d), score(s), visited(v) {}

    bool operator<(const Path &rhs) const { return score > rhs.score; }
  };

  std::priority_queue<Path> queue;
  std::unordered_map<u, u> scoreTile;
  u maxScore = LONG_LONG_MAX;
  usu_t visited;

  visited.insert(start);
  queue.emplace(start, aoc::R, 0, visited);
  scoreTile.insert({start + (aoc::R << 32), 0});

  while (!queue.empty()) {
    Path path = queue.top();
    queue.pop();

    if (path.score > maxScore)
      continue;

    if (path.position == end) {
      if (maxScore == LONG_LONG_MAX) {
        maxScore = path.score;
      }
      if (maxScore == path.score) {
        for (auto &x : path.visited)
          visited.insert(x);
      }
    }

    for (auto &dir : aoc::DIRS) {

      if (aoc::get(map, path.position + dir).value() == '#' or
          path.visited.contains(path.position + dir) or
          (scoreTile.contains(path.position + dir + (dir << 32)) and
           scoreTile[path.position + dir + (dir << 32)] <
               path.score + 1 + 1000 * (path.direction != dir)))
        continue;

      Path newPath(path.position + dir, dir,
                   path.score + 1 + 1000 * (path.direction != dir),
                   path.visited);

      scoreTile[path.position + dir + (dir << 32)] = newPath.score;
      newPath.visited.insert(path.position + dir);

      queue.push(newPath);
    }
  }

  return {maxScore, visited.size()};
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
  aoc::forIndex(0, map.size(), 0, map[0].size(), [&](u i, u j) {
    start = map[i][j] == 'S' ? aoc::getCoordinate(i, j) : start;
    end = map[i][j] == 'E' ? aoc::getCoordinate(i, j) : end;
  });

  result = findMinPath(map, start, end);
  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

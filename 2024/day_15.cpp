#include "../common/common.h"

static u findRobot(const vvc_t &m) {
  for (u i = 0; i < m.size(); i++) {
    for (u j = 0; j < m[0].size(); j++) {
      if (m[i][j] == '@')
        return aoc::getCoordinate(i, j);
    }
  }
  return 0;
}

static void getScore(const vvc_t &m, u &score) {
  for (u i = 0; i < m.size(); i++) {
    for (u j = 0; j < m[0].size(); j++)
      score += (m[i][j] == 'O' or m[i][j] == '[') * (i * 100 + j);
  }
}

static vu_t dirs;

static bool canMove(const vvc_t &map, u pos, u dir) {
  c tile = aoc::get(map, pos).value();
  if (tile == '.')
    return true;
  if (tile == 'O')
    return canMove(map, pos + dir, dir);
  if (tile == '[' and (dir == aoc::U or dir == aoc::D))
    return canMove(map, pos + dir, dir) and
           canMove(map, pos + dir + aoc::R, dir);
  if (tile == ']' and (dir == aoc::U or dir == aoc::D))
    return canMove(map, pos + dir, dir) and
           canMove(map, pos + dir + aoc::L, dir);
  if (tile == '[' and dir == aoc::R)
    return canMove(map, pos + 2 * dir, dir);
  if (tile == ']' and dir == aoc::L)
    return canMove(map, pos + 2 * dir, dir);
  return false;
}

static void swap(vvc_t &map, u pos, u dir) {
  c tile = aoc::get(map, pos).value();
  if (tile == 'O')
    swap(map, pos + dir, dir);
  if (tile == '[' and (dir == aoc::U or dir == aoc::D))
    swap(map, pos + dir, dir), swap(map, pos + dir + aoc::R, dir);
  if (tile == ']' and (dir == aoc::U or dir == aoc::D))
    swap(map, pos + dir, dir), swap(map, pos + dir + aoc::L, dir);
  if ((tile == '[' or tile == ']') and (dir == aoc::R or dir == aoc::L))
    swap(map, pos + dir, dir);

  auto [y0, x0] = aoc::getCoordinate(pos);
  auto [y1, x1] = aoc::getCoordinate(pos - dir);
  std::swap(map[y0][x0], map[y1][x1]);
}

static void move(vvc_t &map, u pos) {
  for (auto &dir : dirs) {
    if (canMove(map, pos + dir, dir))
      swap(map, pos + dir, dir), pos += dir;
  }
}

static void solve() {
  std::string input = aoc::getInput("2024/day_15.txt");

  aoc::result_t result;
  vvc_t map1, map2;
  bool mapDone = false;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    if (mapDone) {
      auto dv = aoc::strToVectorChar(line);
      for (auto &x : dv) {
        dirs.push_back(x == '^'   ? aoc::U
                       : x == 'v' ? aoc::D
                       : x == '>' ? aoc::R
                                  : aoc::L);
      }
    }
    if (line.size() < 3)
      mapDone = true;
    if (!mapDone) {
      vc_t row = aoc::strToVectorChar(line), row2;
      for (auto &x : row) {
        row2.push_back(x == 'O' ? '[' : x);
        row2.push_back(x == 'O' ? ']' : x == '@' ? '.' : x);
      }
      map1.push_back(row), map2.push_back(row2);
    }

    return aoc::ExitCode(aoc::Code::OK);
  });

  move(map1, findRobot(map1)), getScore(map1, result.first);
  move(map2, findRobot(map2)), getScore(map2, result.second);

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

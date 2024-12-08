#include "../common/common.h"

using usu_t = std::unordered_set<u>;

static void solve() {
  std::string input = aoc::getInput("day_8/input.txt");

  aoc::result_t result;
  usu_t antinodesFirst, antinodesSecond;
  std::map<char, vu_t> antennas;
  u size = 0;

  auto insert = [&](u x, u y, u s, u m) {
    if (x < s and y < s) {
      if (m == 1)
        antinodesFirst.insert((y << 8) + x);
      antinodesSecond.insert((y << 8) + x);
    }
  };

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    for (u j = 0; j < line.size(); j++)
      if (line[j] != '.')
        antennas[line[j]].push_back((size << 8) + j);
    size++;
    return aoc::ExitCode(aoc::Code::OK);
  });

  for (auto &[c, a] : antennas) {
    aoc::forIndex(0, a.size(), [&](int i) {
      aoc::forIndex(0, i, [&](int j) {
        u a1y = a[i] >> 8, a1x = a[i] & 0xff;
        u a2y = a[j] >> 8, a2x = a[j] & 0xff;
        if (a2x <= a1x)
          std::swap(a2x, a1x), std::swap(a2y, a1y);
        aoc::forIndex(0, 50, [&](int m) {
          u diffx = std::abs((int)a1x - (int)a2x) * m,
            diffy = std::abs((int)a1y - (int)a2y) * m;
          u ant1x = a1x - diffx, ant1y = a1y + ((a2y >= a1y) ? -diffy : +diffy),
            ant2x = a2x + diffx, ant2y = a2y + ((a2y >= a1y) ? +diffy : -diffy);
          insert(ant1x, ant1y, size, m), insert(ant2x, ant2y, size, m);
        });
      });
    });
  }

  result = {antinodesFirst.size(), antinodesSecond.size()};

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

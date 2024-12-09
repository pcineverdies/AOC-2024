#include "../common/common.h"

static void solve() {
  std::string input = aoc::getInput("day_9/input.txt");

  aoc::result_t result;
  vu_t disk1, disk2;
  vc_t diskCompressed;
  u toCover = 0;

  auto computeChecksum = [](const vu_t &v, u &result) {
    for (u i = 0; i < v.size(); i++) {
      if (v[i] != (u)-1)
        result += i * v[i];
    }
  };

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    diskCompressed = aoc::strToVectorChar(line);
    return aoc::ExitCode(aoc::Code::OK);
  });

  for (u i = 0; i < diskCompressed.size(); i++) {
    for (u j = 0; j < (u)(diskCompressed[i] - '0'); j++) {
      disk1.push_back(i & 1 ? -1 : i >> 1);
      disk2.push_back(i & 1 ? -1 : i >> 1);
      toCover = (i & 1) ? toCover : i >> 1;
    }
  }

  u left = disk1.size() - 1, right = 0;
  while (right < left) {
    while (right < left && disk1[right] != (u)-1)
      right++;
    while (right < left && disk1[left] == (u)-1)
      left--;
    std::swap(disk1[right++], disk1[left--]);
  }

  do {

    u sizeFile = 0, sizeSpace = 0, indexFile = 0;

    for (u index = disk2.size() - 1; index >= 0; index--) {
      if (disk2[index] == toCover)
        sizeFile++, indexFile = index;
      if (disk2[index] < toCover)
        break;
    }

    for (u index = 0; index < disk2.size(); index++) {
      sizeSpace = (disk2[index] == (u)-1) ? sizeSpace + 1 : 0;
      if (disk2[index] == toCover)
        break;
      if (sizeSpace == sizeFile) {
        for (u i = 0; i < sizeFile; i++)
          disk2[index - sizeSpace + i + 1] = toCover, disk2[indexFile + i] = -1;
        break;
      }
    }

  } while (--toCover != 0);

  computeChecksum(disk1, result.first), computeChecksum(disk2, result.second);

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

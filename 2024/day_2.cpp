#include "../common/common.h"

/// Check whether the input vector `v` is safe acccording to the specifications
/// of AOC day 2. If it is not, try to apply recursively the function to the
/// array without at most `toRemove` elements (1 for part 2 of the exercise)
static bool isLevelSafe(const vu_t &v, u toRemove = 0) {

  u size = v.size();
  bool areGt = false, areLt = false, isDiffOutOfRange = false;

  // For each pair of adjacent elements, check whether they are GT, LT or if the
  // difference is out of the correct range.
  for (u i = 1; i < size; i++) {
    int n0 = v[i - 1], n1 = v[i], diff = std::abs(n0 - n1);
    areGt = areGt || n0 > n1, areLt = areLt || n0 < n1;
    isDiffOutOfRange = isDiffOutOfRange || diff == 0 || diff > 3;
  }

  // For a level to be correct, the following two conditions must hold together:
  // 1. Either all the pairs are GT or all the elements are LT: this is the xor
  // of the two conditions.
  // 2. No difference can be out of range.
  if ((areGt ^ areLt) && !isDiffOutOfRange)
    return true;

  // If the condition is not true and `toRemove > 0`, then we try to iterate the
  // function over each possible vector obtained by `v` by removing one element.
  // Such a brute-force approach is clearly sub-optimal.
  if (toRemove) {
    for (u i = 0; i < size; i++) {
      vu_t c = v;
      c.erase(c.begin() + i);
      if (isLevelSafe(c, toRemove - 1))
        return true;
    }
  }

  return false;
}

static void solve() {
  std::string input = aoc::getInput("2024/day_2.txt");

  aoc::result_t result;

  aoc::forLine(input, [&](const std::string &line) -> aoc::ExitCode {
    std::vector<u> v = aoc::strToVector(line);

    result.first += isLevelSafe(v);
    result.second += isLevelSafe(v, 1);

    return aoc::ExitCode(aoc::Code::OK);
  });

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

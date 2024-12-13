#include "../common/common.h"

static u getCost(uu a, uu b, uu p, bool p2) {

  double m = 10000000000000, ax = a.first, ay = a.second, bx = b.first,
         by = b.second, px = p.first + p2 * m, py = p.second + p2 * m,
         den = ax * by - ay * bx, r1 = (px * by - py * bx) / den,
         r2 = (ax * py - ay * px) / den;

  return (floor(r1) == r1 and floor(r2) == r2) ? (u)r1 * 3 + (u)r2 : 0;
}

static void solve() {
  std::string input = aoc::getInput("2024/day_13.txt");
  aoc::result_t result;
  std::vector<uu> buttonsA, buttonsB, prizes;
  u counter = 0;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    vu_t nums = aoc::strToVector(line);
    if (counter == 0)
      buttonsA.emplace_back(nums[0], nums[1]);
    if (counter == 1)
      buttonsB.emplace_back(nums[0], nums[1]);
    if (counter == 2)
      prizes.emplace_back(nums[0], nums[1]);
    counter = (counter + 1) % 4;
    return aoc::ExitCode(aoc::Code::OK);
  });

  for (u i = 0; i < prizes.size(); i++)
    result.first += getCost(buttonsA[i], buttonsB[i], prizes[i], false),
        result.second += getCost(buttonsA[i], buttonsB[i], prizes[i], true);

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

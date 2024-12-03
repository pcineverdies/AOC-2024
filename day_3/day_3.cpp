#include "../common/common.h"

static void solve() {
  std::string input = aoc::getInput("day_3/input.txt");

  unsigned result1 = 0, result2 = 0;

  // Initially multiplications are active
  bool isMulActive = true;

  aoc::forLine(input, [&](const std::string &line) -> aoc::ExitCode {
    return aoc::forMatches(
        line, std::regex(R"(mul\(\d{1,3},\d{1,3}\)|do\(\)|don't\(\))"),
        [&](const std::string &match) -> aoc::ExitCode {
          // Possibly modify the status of isMulActive
          isMulActive = match == "do()"      ? true
                        : match == "don't()" ? false
                                             : isMulActive;

          // Possibly modify the results
          aoc::runOnMatch(match, std::regex(R"(^mul\((\d{1,3}),(\d{1,3})\)$)"),
                          [&](const std::smatch &mulMatch) -> aoc::ExitCode {
                            unsigned mul = std::stoul(mulMatch[1]) *
                                           std::stoul(mulMatch[2]);
                            result1 += mul;
                            result2 += isMulActive ? mul : 0;
                            return aoc::ExitCode(aoc::Code::OK);
                          });

          return aoc::ExitCode(aoc::Code::OK);
        });
  });

  aoc::printResult(result1, result2);
}

int main(int argc, char *argv[]) { solve(); }

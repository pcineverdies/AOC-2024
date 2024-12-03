#include "../common/common.h"

static void solve() {
  std::string input = aoc::getInput("day_1/input.txt");

  std::vector<unsigned> v1, v2;
  unsigned result1 = 0, result2 = 0;
  std::map<unsigned, unsigned> occurrences;

  aoc::forLine(input, [&](const std::string &line) -> aoc::ExitCode {
    if (!aoc::runOnMatch(line, std::regex(R"((\d+)(\s+)(\d+))"),
                         [&](const std::smatch &m) -> aoc::ExitCode {
                           unsigned n1 = std::stoul(m[1]),
                                    n2 = std::stoul(m[3]);
                           v1.push_back(n1), v2.push_back(n2),
                               occurrences[n2]++;
                           return aoc::ExitCode(aoc::Code::OK);
                         })
             .isOk())
      return aoc::ExitCode(aoc::Code::PARSING_ERROR);
    return aoc::ExitCode(aoc::Code::OK);
  });

  std::sort(v1.begin(), v1.end());
  std::sort(v2.begin(), v2.end());

  aoc::zip<unsigned>(v1, v2, [&](unsigned a, unsigned b) -> aoc::ExitCode {
    result1 += std::abs((int)a - (int)b);
    result2 += a * occurrences[a];
    return aoc::ExitCode(aoc::Code::OK);
  });

  aoc::printResult(result1, result2);
}

int main(int argc, char *argv[]) { solve(); }

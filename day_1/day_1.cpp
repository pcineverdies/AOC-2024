#include "../common/common.h"

static void solve() {
  std::string input = aoc::getInput("day_1/input.txt");

  std::vector<unsigned> v1, v2;
  unsigned result1 = 0, result2 = 0;
  std::map<unsigned, unsigned> occurrences;

  aoc::forLine(input, [&](const std::string &line) -> aoc::ExitCode {
    std::regex pattern(R"((\d+)(\s+)(\d+))");
    std::smatch matches;
    if (std::regex_match(line, matches, pattern)) {
      unsigned n1 = std::stoul(matches[1]);
      unsigned n2 = std::stoul(matches[3]);
      v1.push_back(n1), v2.push_back(n2), occurrences[n2]++;
      return aoc::ExitCode(aoc::Code::OK);
    }

    return aoc::ExitCode(aoc::Code::PARSING_ERROR, line);
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

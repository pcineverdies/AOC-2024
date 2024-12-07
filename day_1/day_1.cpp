#include "../common/common.h"

static void solve() {
  std::string input = aoc::getInput("day_1/input.txt");

  std::vector<u> v1, v2;
  aoc::result_t result;
  std::map<u, u> occurrences;

  aoc::forLine(input, [&](const std::string &line) -> aoc::ExitCode {
    aoc::runOnMatch(line, std::regex(R"((\d+)(\s+)(\d+))"),
                    [&](const std::smatch &m) -> void {
                      u n1 = std::stoul(m[1]), n2 = std::stoul(m[3]);
                      v1.push_back(n1), v2.push_back(n2), occurrences[n2]++;
                    });

    return aoc::ExitCode(aoc::Code::OK);
  });

  std::sort(v1.begin(), v1.end());
  std::sort(v2.begin(), v2.end());

  aoc::zip<u>(v1, v2, [&](u a, u b) -> aoc::ExitCode {
    result.first += std::abs((int)a - (int)b);
    result.second += a * occurrences[a];
    return aoc::ExitCode(aoc::Code::OK);
  });

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

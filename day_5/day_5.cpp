#include "../common/common.h"

using muu_t = std::map<unsigned, unsigned>;

static void solve() {
  std::string input = aoc::getInput("day_5/input.txt");

  aoc::result_t result;

  std::map<unsigned, std::unordered_set<unsigned>> deps;
  vvu_t updates;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    aoc::runOnMatch(line, std::regex(R"(^(\d+)\|(\d+)$)"),
                    [&](const std::smatch &dep) -> aoc::ExitCode {
                      deps[std::stoul(dep[1].str())].insert(
                          std::stoul(dep[2].str()));
                      return aoc::ExitCode(aoc::Code::OK);
                    });

    aoc::runOnMatch(line, std::regex(R"(^\d+(,\d+)*$)"),
                    [&](const std::smatch &dep) -> aoc::ExitCode {
                      auto nums = aoc::stringToUnsigned(line);
                      updates.push_back(nums);
                      return aoc::ExitCode(aoc::Code::OK);
                    });

    return aoc::ExitCode(aoc::Code::OK);
  });

  // Try to sort the numbers according to the dependencies of each component. If
  // they are valid, the output of the sorting will be the list itself.
  for (auto &update : updates) {
    auto nums = update;
    std::sort(nums.begin(), nums.end(), [&](u a, u b) -> bool {
      return !deps.contains(a) ? false : deps[a].contains(b);
    });
    if (aoc::equalVectors(nums, update))
      result.first += nums[nums.size() / 2];
    else
      result.second += nums[nums.size() / 2];
  }

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

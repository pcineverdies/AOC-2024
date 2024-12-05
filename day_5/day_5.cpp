#include "../common/common.h"

static void solve() {
  s input = aoc::getInput("day_5/input.txt");

  aoc::result_t result;

  std::map<u, std::unordered_set<u>> deps;
  vvu_t updates;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    aoc::runOnMatch(
        line, std::regex(R"(^(\d+)\|(\d+)$)"), [&](const std::smatch &dep) {
          deps[std::stoul(dep[1].str())].insert(std::stoul(dep[2].str()));
        });

    aoc::runOnMatch(line, std::regex(R"(.*,.*)"), [&](const std::smatch &dep) {
      updates.push_back(aoc::stringToUnsigned(line));
    });

    return aoc::ExitCode(aoc::Code::OK);
  });

  for (vu_t &update : updates) {
    vu_t nums = update;
    std::sort(nums.begin(), nums.end(), [&](u a, u b) -> bool {
      return deps.contains(a) and deps[a].contains(b);
    });

    if (aoc::equalVectors(nums, update))
      result.first += nums[nums.size() / 2];
    else
      result.second += nums[nums.size() / 2];
  }

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

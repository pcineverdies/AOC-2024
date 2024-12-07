#include "../common/common.h"

using vu64_t = std::vector<u64>;

static u64 applyOperators(vu64_t &operands, u64 operators) {
  u64 result = operands[0], size = operands.size();

  auto concat = [](u64 a, u64 b) -> u64 {
    u64 power = (u64)std::ceil(std::log10(b + 1)), p = 1;
    while (power--)
      p *= 10;
    return a * p + b;
  };

  for (u64 i = 1; i < size; i++) {
    u64 op = (operators >> (2 * i - 2)) & 3;
    if (op == 0)
      result += operands[i];
    else if (op == 1)
      result *= operands[i];
    else if (op == 2)
      result = concat(result, operands[i]);
    else
      aoc::handleExitCode(aoc::ExitCode(aoc::Code::RUNTIME_ERROR));
  }

  return result;
};

static bool tryOperators(u64 result, vu64_t &operands, bool concat = false) {

  u size = operands.size();
  std::queue<std::pair<u64, u64>> next;
  std::unordered_set<u64> covered;
  next.emplace(0, 1);
  next.emplace(1, 1);
  if (concat)
    next.emplace(2, 1);

  while (!next.empty()) {
    auto [operators, mask] = next.front();
    next.pop();

    if (!covered.contains(operators)) {
      u64 computed = applyOperators(operands, operators);
      covered.insert(operators);
      if (computed == result)
        return true;
    }

    if (mask != size - 1) {
      next.emplace(operators, mask + 1);
      next.emplace(operators | (1 << (mask << 1)), mask + 1);
      if (concat)
        next.emplace(operators | (2 << (mask << 1)), mask + 1);
    }
  }

  return false;
}

static void solve() {
  std::string input = aoc::getInput("day_7/input.txt");

  aoc::result_t result;
  std::vector<std::pair<u64, vu64_t>> bridges;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    auto t = aoc::strToVector(line);
    u64 val = t[0];
    t.erase(t.begin());
    bridges.emplace_back(val, t);
    return aoc::ExitCode(aoc::Code::OK);
  });

  for (auto &bridge : bridges) {
    result.first +=
        tryOperators(bridge.first, bridge.second) ? bridge.first : 0;
    result.second +=
        tryOperators(bridge.first, bridge.second, true) ? bridge.first : 0;
  }

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

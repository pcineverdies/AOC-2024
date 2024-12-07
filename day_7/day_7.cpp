#include "../common/common.h"

static u applyOperators(vu_t &operands, u operators) {
  u result = operands[0], size = operands.size();

  auto concat = [](u a, u b) -> u {
    u power = (u)std::ceil(std::log10(b + 1)), p = 1;
    while (power--)
      p *= 10;
    return a * p + b;
  };

  for (u i = 1; i < size; i++) {
    u op = (operators >> (2 * i - 2)) & 3;
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

static bool tryOperators(u result, vu_t &operands, bool concat = false) {

  u size = operands.size();
  std::queue<std::pair<u, u>> next;
  std::unordered_set<u> covered;
  next.emplace(0, 1);
  next.emplace(1, 1);
  if (concat)
    next.emplace(2, 1);

  while (!next.empty()) {
    auto [operators, mask] = next.front();
    next.pop();

    if (!covered.contains(operators)) {
      u computed = applyOperators(operands, operators);
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
  std::vector<std::pair<u, vu_t>> bridges;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    auto t = aoc::strToVector(line);
    u val = t[0];
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

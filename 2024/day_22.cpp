#include "../common/common.h"

static inline u step(u value) {
  value = (value ^ (value * 64)) % 16777216;
  value = (value ^ (value / 32)) % 16777216;
  value = (value ^ (value * 2048)) % 16777216;
  return value;
}

static void solve() {
  std::string input = aoc::getInput("2024/day_22.txt");

  aoc::result_t result;
  vu_t nums;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    nums.push_back(aoc::strToVector(line)[0]);
    return aoc::ExitCode(aoc::Code::OK);
  });

  std::unordered_map<u, u> sum;
  for (auto &x : nums) {
    usu_t foundSequences;
    u32 sequence = 0;
    for (int i = 0; i < 2000; i++) {
      u prev = x;
      x = step(x);
      u8 diff = (x % 10) - (prev % 10);
      sequence = (sequence << 8) | diff;

      if (i >= 4) {
        if (foundSequences.contains(sequence))
          continue;
        foundSequences.insert(sequence);
        sum[sequence] += (x % 10);
      }
    }
    result.first += x;
  }

  for (auto &[sequence, value] : sum)
    result.second = std::max(result.second, value);

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

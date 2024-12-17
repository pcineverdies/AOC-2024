#include "../common/common.h"

static s runProgram(const vu_t &program, vu_t &registers) {

  auto getCombo = [&](u value) -> u {
    if (value <= 3)
      return value;
    if (value <= 6)
      return registers[value - 4];
    std::cout << "Wrong combo input" << std::endl;
    exit(1);
  };

  u instructionPointer = 0;
  s output = "";
  while (instructionPointer < program.size()) {
    u instruction = program[instructionPointer++];
    u operand = program[instructionPointer++];
    if (instruction == 0) {
      registers[0] = registers[0] / pow(2, getCombo(operand));
    } else if (instruction == 1) {
      registers[1] = registers[1] ^ operand;
    } else if (instruction == 2) {
      registers[1] = getCombo(operand) & 7;
    } else if (instruction == 3) {
      instructionPointer = registers[0] == 0 ? instructionPointer : operand;
    } else if (instruction == 4) {
      registers[1] = registers[1] ^ registers[2];
    } else if (instruction == 5) {
      output += std::to_string(getCombo(operand) & 7) + ",";
    } else if (instruction == 6) {
      registers[1] = registers[0] / pow(2, getCombo(operand));
    } else if (instruction == 7) {
      registers[2] = registers[0] / pow(2, getCombo(operand));
    } else {
      std::cout << "Wrong instruction parsed" << std::endl;
      exit(1);
    }
  }

  output.pop_back();
  return output;
}

static vu_t dfs(const std::unordered_map<u, vu_t> &link, const vu_t &program,
                u index) {
  u value = program[index];

  if (index == 0)
    return link.at(value);

  vu_t result, available = dfs(link, program, index - 1);

  for (auto &av : available) {
    for (auto &x : link.at(value)) {
      if ((x & 0b111111) == ((av >> (index * 3)) & 0b111111))
        result.push_back(av | ((x & 0b111111000) << (index * 3)));
    }
  }

  return result;
}

static void solve() {
  std::string input = aoc::getInput("2024/day_17.txt");

  u lineCounter = 0;
  vu_t registers, program;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    program = aoc::strToVector(line);
    if (lineCounter++ < 3)
      registers.push_back(program[0]);

    return aoc::ExitCode(aoc::Code::OK);
  });

  auto result1 = runProgram(program, registers);

  std::unordered_map<u, vu_t> link;

  for (u i = 0; i < 512; i++) {
    registers = {i, 0, 0};
    auto v = aoc::strToVector(runProgram(program, registers));
    link[v[0]].push_back(i);
  }

  auto all = dfs(link, program, program.size() - 1);
  u result2 = *std::ranges::min_element(all);

  std::cout << aoc::Color::CYAN << "~> Part 1 result: " << aoc::Color::RESET
            << result1 << std::endl;
  std::cout << aoc::Color::CYAN << "~> Part 2 result: " << aoc::Color::RESET
            << result2 << std::endl;
}

int main(int argc, char *argv[]) { solve(); }

#include "../common/common.h"

using m_t = std::vector<std::vector<char>>;

static void countXMAS(const m_t &matrix, aoc::result_t &result, int it = 4) {

  int n = matrix.size(), m = matrix[0].size();
  auto rotated = matrix;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {

      if (aoc::get(matrix[i], j + 0) == 'X' and
          aoc::get(matrix[i], j + 1) == 'M' and
          aoc::get(matrix[i], j + 2) == 'A' and
          aoc::get(matrix[i], j + 3) == 'S')
        result.first++;

      if (aoc::get(aoc::get(matrix, i + 0), j + 0) == 'X' and
          aoc::get(aoc::get(matrix, i + 1), j + 1) == 'M' and
          aoc::get(aoc::get(matrix, i + 2), j + 2) == 'A' and
          aoc::get(aoc::get(matrix, i + 3), j + 3) == 'S')
        result.first++;

      if (aoc::get(aoc::get(matrix, i + 0), j + 0) == 'A' and
          aoc::get(aoc::get(matrix, i + 1), j + 1) == 'M' and
          aoc::get(aoc::get(matrix, i - 1), j + 1) == 'M' and
          aoc::get(aoc::get(matrix, i + 1), j - 1) == 'S' and
          aoc::get(aoc::get(matrix, i - 1), j - 1) == 'S')
        result.second++;

      rotated[j][n - 1 - i] = matrix[i][j];
    }
  }

  if (--it)
    countXMAS(rotated, result, it);
};

static void solve() {
  std::string input = aoc::getInput("day_4/input.txt");

  aoc::result_t result;
  m_t matrix;

  aoc::forLine(input, [&](const std::string &line) -> aoc::ExitCode {
    matrix.push_back(aoc::strToVectorChar(line));
    return aoc::ExitCode(aoc::Code::OK);
  });

  countXMAS(matrix, result);

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

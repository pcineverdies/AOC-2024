#include "../common/common.h"

static void countXMAS(const vvc_t &matrix, aoc::result_t &result, ii it) {

  auto rotated = matrix;

  aoc::forIndex(0, matrix.size(), 0, matrix[0].size(), [&](ii i, ii j) {
    result.first += aoc::get(matrix, i, j + 0).value_or(0) == 'X' and
                    aoc::get(matrix, i, j + 1).value_or(0) == 'M' and
                    aoc::get(matrix, i, j + 2).value_or(0) == 'A' and
                    aoc::get(matrix, i, j + 3).value_or(0) == 'S';

    result.first += aoc::get(matrix, i + 0, j + 0).value_or(0) == 'X' and
                    aoc::get(matrix, i + 1, j + 1).value_or(0) == 'M' and
                    aoc::get(matrix, i + 2, j + 2).value_or(0) == 'A' and
                    aoc::get(matrix, i + 3, j + 3).value_or(0) == 'S';

    result.second += aoc::get(matrix, i + 0, j + 0).value_or(0) == 'A' and
                     aoc::get(matrix, i + 1, j + 1).value_or(0) == 'M' and
                     aoc::get(matrix, i - 1, j + 1).value_or(0) == 'M' and
                     aoc::get(matrix, i + 1, j - 1).value_or(0) == 'S' and
                     aoc::get(matrix, i - 1, j - 1).value_or(0) == 'S';

    rotated[j][matrix.size() - 1 - i] = matrix[i][j];
  });

  if (--it)
    countXMAS(rotated, result, it);
};

static void solve() {
  std::string input = aoc::getInput("2024/day_4.txt");

  aoc::result_t result;
  vvc_t matrix;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    matrix.push_back(aoc::strToVectorChar(line));
    return aoc::ExitCode(aoc::Code::OK);
  });

  countXMAS(matrix, result, 4);

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

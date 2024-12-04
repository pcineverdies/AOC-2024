#include "../common/common.h"

static void countAndRotate(std::vector<std::vector<char>> &matrix,
                           unsigned &result1, unsigned &result2) {
  int n = matrix.size();
  int m = matrix[0].size();
  auto rotated = matrix;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {

      // Count XMAS from left to right
      if (j + 4 <= m and matrix[i][j] == 'X' and matrix[i][j + 1] == 'M' and
          matrix[i][j + 2] == 'A' and matrix[i][j + 3] == 'S')
        result1++;

      // Count XMAS towards down-right
      if (j + 4 <= m and i + 4 <= n and matrix[i][j] == 'X' and
          matrix[i + 1][j + 1] == 'M' and matrix[i + 2][j + 2] == 'A' and
          matrix[i + 3][j + 3] == 'S')
        result1++;

      // Count X-MAS with 'M' on the right and 'S' on the left
      if (i >= 1 and j >= 1 and i < n - 1 and j < m - 1 and
          matrix[i][j] == 'A' and matrix[i + 1][j + 1] == 'M' and
          matrix[i - 1][j + 1] == 'M' and matrix[i + 1][j - 1] == 'S' and
          matrix[i - 1][j - 1] == 'S')
        result2++;

      // Compute next rotation
      rotated[j][n - 1 - i] = matrix[i][j];
    }
  }

  matrix = rotated;
};

static void solve() {
  std::string input = aoc::getInput("day_4/input.txt");

  unsigned result1 = 0, result2 = 0;
  std::vector<std::vector<char>> matrix;

  aoc::forLine(input, [&](const std::string &line) -> aoc::ExitCode {
    matrix.push_back(aoc::strToVectorChar(line));
    return aoc::ExitCode(aoc::Code::OK);
  });

  for (int i = 0; i < 4; i++)
    countAndRotate(matrix, result1, result2);

  aoc::printResult(result1, result2);
}

int main(int argc, char *argv[]) { solve(); }

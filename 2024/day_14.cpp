#include "../common/common.h"

constexpr ii WX = 101, WY = 103;

static void solve() {
  std::string input = aoc::getInput("2024/day_14.txt");

  aoc::result_t result;
  std::vector<std::pair<ii, ii>> pos, vel;

  aoc::forLine(input, [&](const s &line) -> aoc::ExitCode {
    auto nums = aoc::strToVectorSigned(line);
    pos.emplace_back(nums[0], nums[1]);
    vel.emplace_back(nums[2], nums[3]);
    return aoc::ExitCode(aoc::Code::OK);
  });

  for (u time = 1; time < 10000; time++) {
    for (u i = 0; i < pos.size(); i++) {
      pos[i].first += vel[i].first, pos[i].second += vel[i].second;
      pos[i].first += pos[i].first < 0 ? WX : pos[i].first >= WX ? -WX : 0;
      pos[i].second += pos[i].second < 0 ? WY : pos[i].second >= WY ? -WY : 0;
    }

    if (time == 100) {
      std::vector<u> q = {0, 0, 0, 0};
      for (auto &x : pos) {
        q[0] += x.first < WX / 2 and x.second < WY / 2;
        q[1] += x.first > WX / 2 and x.second < WY / 2;
        q[2] += x.first < WX / 2 and x.second > WY / 2;
        q[3] += x.first > WX / 2 and x.second > WY / 2;
      }
      result.first = q[0] * q[1] * q[2] * q[3];
    }

    bool correct = true;
    for (ii i = 0; i < WY; i++) {
      for (ii j = 0; j < WX; j++) {
        u counter = 0;
        for (auto &x : pos)
          counter += x.first == j and x.second == i;
        correct = correct ? counter <= 1 : correct;
      }
    }

    if (correct) {
      result.second = time;
      break;
    }
  }

  aoc::printResult(result);
}

int main(int argc, char *argv[]) { solve(); }

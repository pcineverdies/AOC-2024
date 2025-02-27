#include "common.h"

std::string aoc::ExitCode::getExitCodeName() const {
  auto e = this->getExitCode();
  switch (e) {
  case FILE_ERROR:
    return "[FILE ERROR]";
  case PARSING_ERROR:
    return "[PARSING ERROR]";
  case RUNTIME_ERROR:
    return "[RUNTIME ERROR]";
  default:
    return "[ERROR NAME NOT FOUND]";
  }
}
void aoc::forIndex(ii starti, ii endi, ii startj, ii endj,
                   const std::function<void(int, int)> &f) {
  for (ii i = starti; i < endi; i++) {
    for (ii j = startj; j < endj; j++) {
      f(i, j);
    }
  }
}

void aoc::forIndex(ii starti, ii endi, const std::function<void(int)> &f) {
  for (ii i = starti; i < endi; i++)
    f(i);
}

void aoc::handleExitCode(const ExitCode &e) {

  if (!e.isOk()) {
    std::cerr << aoc::Color::RED << e.getExitCodeName() << aoc::Color::RESET
              << std::endl;

    if (e.hasMessage()) {
      std::cerr << aoc::Color::MAGENTA << e.getMessage() << aoc::Color::RESET
                << std::endl;
    }

    e.terminate();
  }
}

std::string aoc::getInput(const std::string &fileName) {
  std::ifstream file(fileName);

  if (!file.is_open())
    aoc::handleExitCode(ExitCode(Code::FILE_ERROR));

  std::string res((std::istreambuf_iterator<char>(file)),
                  std::istreambuf_iterator<char>());
  return res;
}

u aoc::forLine(const std::string &s,
               const std::function<ExitCode(const std::string &line)> &f) {
  std::istringstream stream(s);
  std::string line;
  u counter = 0;

  while (std::getline(stream, line))
    counter++, handleExitCode(f(line));

  return counter;
}

u aoc::forLineVoid(const std::string &s,
                   const std::function<void(const std::string &line)> &f) {
  std::istringstream stream(s);
  std::string line;
  u counter = 0;

  while (std::getline(stream, line))
    counter++, f(line);

  return counter;
}

template <typename T>
void aoc::zip(std::vector<T> &a, std::vector<T> &b,
              const std::function<ExitCode(T, T)> &f) {
  if (u n = a.size(); n == b.size()) {
    for (u i = 0; i < n; i++)
      handleExitCode(f(a[i], b[i]));
  } else {
    handleExitCode(ExitCode(Code::RUNTIME_ERROR,
                            "-> Vectors of different sizes on `zip`"));
  }
}

template <typename T>
T aoc::get(const std::vector<T> &v, int i, T def) {
  if (i < 0 or i >= (int)v.size())
    return def;
  return v.at(i);
}

void aoc::printResult(const std::pair<u64, u64> &s) {
  std::cout << aoc::Color::CYAN << "~> Part 1 result: " << aoc::Color::RESET
            << s.first << std::endl;
  std::cout << aoc::Color::CYAN << "~> Part 2 result: " << aoc::Color::RESET
            << s.second << std::endl;
}

void aoc::printBinary(u val) {
  u mask = (u)1 << 63;
  while (mask) {
    std::cout << ((val & mask) ? "1" : "0");
    mask >>= 1;
  }
}

std::vector<u64> aoc::strToVector(const std::string &s) {
  std::regex pattern(R"(\d+)");
  auto begin = std::sregex_iterator(s.begin(), s.end(), pattern);
  auto end = std::sregex_iterator();

  std::vector<u64> result;

  for (auto it = begin; it != end; ++it)
    result.push_back(std::stoull(it->str()));

  return result;
}

std::vector<ii> aoc::strToVectorSigned(const std::string &s) {
  std::regex pattern(R"(-?\d+)");
  auto begin = std::sregex_iterator(s.begin(), s.end(), pattern);
  auto end = std::sregex_iterator();

  std::vector<ii> result;

  for (auto it = begin; it != end; ++it)
    result.push_back(std::stoll(it->str()));

  return result;
}

std::vector<char> aoc::strToVectorChar(const std::string &s) {
  std::vector<char> res;
  for (auto &x : s)
    res.push_back(x);
  return res;
}

std::string aoc::vectorCharToStr(const std::vector<char> &c) {
  std::string res = "";
  for (auto &x : c)
    res += x;
  return res;
}

aoc::ExitCode
aoc::forMatches(const std::string &s, const std::regex &p,
                const std::function<ExitCode(const std::string &match)> &f) {
  auto begin = std::sregex_iterator(s.begin(), s.end(), p);
  auto end = std::sregex_iterator();

  for (auto it = begin; it != end; ++it) {
    auto result = f(it->str());
    if (!result.isOk())
      handleExitCode(result);
  }

  return ExitCode(Code::OK);
}

void aoc::forMatchesVoid(
    const std::string &s, const std::regex &p,
    const std::function<void(const std::string &match)> &f) {
  auto begin = std::sregex_iterator(s.begin(), s.end(), p);
  auto end = std::sregex_iterator();

  for (auto it = begin; it != end; ++it)
    f(it->str());
}

aoc::ExitCode
aoc::runOnMatch(const std::string &s, const std::regex &p,
                const std::function<ExitCode(const std::smatch &match)> &f) {
  std::smatch match;
  if (std::regex_match(s, match, p)) {
    auto result = f(match);
    if (!result.isOk())
      handleExitCode(result);
    return result;
  }

  return ExitCode(Code::PARSING_ERROR);
}

void aoc::runOnMatch(const std::string &s, const std::regex &p,
                     const std::function<void(const std::smatch &match)> &f) {
  std::smatch match;
  if (std::regex_match(s, match, p))
    f(match);
}

template <typename T>
std::optional<T> aoc::get(const std::vector<std::vector<T>> &v, int i, int j) {
  int n = (int)v.size();
  if (n == 0)
    return {};
  int m = (int)v[0].size();
  if (i < 0 or i >= n or j < 0 or j >= m)
    return {};
  return v.at(i).at(j);
}

template <typename T>
std::optional<T> aoc::get(const std::vector<std::vector<T>> &v, u pos) {
  u n = (int)v.size();
  if (n == 0)
    return {};
  u m = (int)v[0].size();
  u i = pos >> 16, j = pos & 0xffff;
  if (i >= n or j >= m)
    return {};
  return v.at(i).at(j);
}

std::vector<u> aoc::stringToUnsigned(const std::string &str, char sep) {
  std::vector<u> numbers;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, sep))
    numbers.push_back(std::stoull(token));

  return numbers;
}

template <typename T>
bool aoc::equalVectors(const std::vector<T> &a, const std::vector<T> &b) {
  if (a.size() != b.size())
    return false;

  for (u i = 0; i < a.size(); i++)
    if (a[i] != b[i])
      return false;

  return true;
}

u aoc::manhattan(u start, u end) {
  auto [starty, startx] = aoc::getCoordinate(start);
  auto [endy, endx] = aoc::getCoordinate(end);
  return (u)std::abs((ii)starty - (ii)endy) +
         (u)std::abs((ii)startx - (ii)endx);
}

u aoc::getCoordinate(const u &y, const u &x) { return (y << 16) + x; }

std::pair<u, u> aoc::getCoordinate(const u &c) { return {c >> 16, c & 0xffff}; }

// Template declaration

template void aoc::zip<u>(std::vector<u> &, std::vector<u> &,
                          const std::function<ExitCode(u, u)> &);
template char aoc::get(const std::vector<char> &, int, char);
template u aoc::get(const std::vector<u> &, int, u);
template int aoc::get(const std::vector<int> &, int, int);
template std::optional<char> aoc::get(const std::vector<std::vector<char>> &,
                                      int, int);
template std::optional<int> aoc::get(const std::vector<std::vector<int>> &, int,
                                     int);
template std::optional<u> aoc::get(const std::vector<std::vector<u>> &, int,
                                   int);
template bool aoc::equalVectors(const std::vector<u> &, const std::vector<u> &);

template std::optional<char> aoc::get(const std::vector<std::vector<char>> &v,
                                      u pos);
template std::optional<u> aoc::get(const std::vector<std::vector<u>> &v, u pos);

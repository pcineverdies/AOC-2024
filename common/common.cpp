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

unsigned
aoc::forLine(const std::string &s,
             const std::function<ExitCode(const std::string &line)> &f) {
  std::istringstream stream(s);
  std::string line;
  unsigned counter = 0;

  while (std::getline(stream, line))
    counter++, handleExitCode(f(line));

  return counter;
}

template <typename T>
void aoc::zip(std::vector<T> &a, std::vector<T> &b,
              const std::function<ExitCode(T, T)> &f) {
  if (unsigned n = a.size(); n == b.size()) {
    for (unsigned i = 0; i < n; i++)
      handleExitCode(f(a[i], b[i]));
  } else {
    handleExitCode(ExitCode(Code::RUNTIME_ERROR,
                            "-> Vectors of different sizes on `zip`"));
  }
}

template <typename T>
void aoc::printResult(const T &r1, const T &r2) {
  std::cout << aoc::Color::CYAN << "~> Part 1 result: " << aoc::Color::RESET
            << r1 << std::endl;
  std::cout << aoc::Color::CYAN << "~> Part 2 result: " << aoc::Color::RESET
            << r2 << std::endl;
}

std::vector<unsigned> aoc::strToVector(const std::string &s) {
  std::regex pattern(R"(\d+)");
  auto begin = std::sregex_iterator(s.begin(), s.end(), pattern);
  auto end = std::sregex_iterator();

  std::vector<unsigned> result;

  for (auto it = begin; it != end; ++it)
    result.push_back(std::stoul(it->str()));

  return result;
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

// Template declaration

template void aoc::zip<unsigned int>(
    std::vector<unsigned int> &, std::vector<unsigned int> &,
    const std::function<ExitCode(unsigned int, unsigned int)> &);

template void aoc::printResult<unsigned>(const unsigned &, const unsigned &);

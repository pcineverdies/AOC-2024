#include <algorithm>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <regex>
#include <sstream>
#include <stack>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace aoc {

using result_t = std::pair<unsigned, unsigned>;

/// Define literal constants used to print on terminal with multiple colors.
namespace Color {
const std::string RED = "\033[0;31m";
const std::string GREEN = "\033[1;32m";
const std::string YELLOW = "\033[1;33m";
const std::string CYAN = "\033[0;36m";
const std::string MAGENTA = "\033[0;35m";
const std::string RESET = "\033[0m";
}; // namespace Color

/// Define all the available error codes of the system.
enum Code {
  OK = 0,
  FILE_ERROR = 1,
  PARSING_ERROR = 2,
  RUNTIME_ERROR = 3,
};

/// Class wrapper of an exit code together with an optional message.
class ExitCode {

  /// Error code.
  const Code e;

  /// Optional message associated with the message.
  const std::optional<std::string> m;

public:
  /// Constructor of the class.
  ExitCode(Code e, const std::optional<std::string> &m = std::nullopt)
      : e(e), m(m) {}

  /// Get the message.
  std::string getMessage() const { return m.value_or(""); }

  /// Return true if the error code has a message, false otherwise.
  bool hasMessage() const { return m.has_value(); }

  /// Get the exit code.
  Code getExitCode() const { return e; }

  /// Get a literal name of the exit code.
  std::string getExitCodeName() const;

  /// Returns true if the exit code is OK
  bool isOk() const { return e == Code::OK; }

  void terminate() const { exit(e); }
};

/// Read the input file as a string.
std::string getInput(const std::string &fileName);

/// Run function `f` over each line of the input string `s`; return the number
/// of lines analyzed.
unsigned forLine(const std::string &s,
                 const std::function<ExitCode(const std::string &line)> &f);

/// Zip two vectors and run function `f` of each pair of elements.
template <typename T>
void zip(std::vector<T> &a, std::vector<T> &b,
         const std::function<ExitCode(T, T)> &f);

/// Handle an exit code: return without doing anything if no error is found,
/// otherwise terminate while printing the cause of the error and the possible
/// optional message associated to it.
void handleExitCode(const ExitCode &e);

/// Convert a string of unsinged numbers into a vector of unsinged
std::vector<unsigned> strToVector(const std::string &s);

/// Print the result of the two parts of aoc
template <typename T>
void printResult(const T &r1, const T &r2);

/// Print the result of the two parts of aoc
void printResult(const std::pair<unsigned, unsigned> &s);

/// Convert a string to a vector of character
std::vector<char> strToVectorChar(const std::string &s);

/// Covert a vector of character to a string
std::string vectorCharToStr(const std::vector<char> &c);

/// Run a function for each single patch of regex `p` over `s`
aoc::ExitCode
forMatches(const std::string &s, const std::regex &p,
           const std::function<ExitCode(const std::string &match)> &f);

/// Run a function for the match of `p` over `s`
aoc::ExitCode
runOnMatch(const std::string &s, const std::regex &p,
           const std::function<ExitCode(const std::smatch &match)> &f);

template <typename T>
T get(const std::vector<T> &v, int i, T def = T());

} // namespace aoc

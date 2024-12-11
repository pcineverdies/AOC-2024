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

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u = u64;
using ii = int;
using s = std::string;
using c = char;
using b = bool;
using vu_t = std::vector<u>;
using vi_t = std::vector<int>;
using vc_t = std::vector<char>;
using vs_t = std::vector<std::string>;
using vvu_t = std::vector<std::vector<u>>;
using vvi_t = std::vector<std::vector<int>>;
using vvc_t = std::vector<std::vector<char>>;
using vvs_t = std::vector<std::vector<std::string>>;
using vvs_t = std::vector<std::vector<std::string>>;
using usu_t = std::unordered_set<u>;

namespace aoc {

constexpr u U = -0x10000;
constexpr u D = 0x10000;
constexpr u L = -1;
constexpr u R = 1;

using result_t = std::pair<uint64_t, uint64_t>;

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
u forLine(const std::string &s,
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
std::vector<u> strToVector(const std::string &s);

/// Print the result of the two parts of aoc
template <typename T>
void printResult(const T &r1, const T &r2);

/// Print the result of the two parts of aoc
void printResult(const std::pair<u, u> &s);

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

/// Run a function `f on each meatch of regex `p` over `s`
void runOnMatch(const std::string &s, const std::regex &p,
                const std::function<void(const std::smatch &match)> &f);

/// Convert a string to a vector of unsigned using `sep` as separator
std::vector<u> stringToUnsigned(const std::string &str, char sep = ',');

/// Check whether two vectors are identical (same size and same elements)
template <typename T>
bool equalVectors(const std::vector<T> &a, const std::vector<T> &b);

/// Get element `i` from `v` if in range, `def` otherwise
template <typename T>
T get(const std::vector<T> &v, int i, T def = T());

template <typename T>
std::optional<T> get(const std::vector<std::vector<T>> &v, u pos);

/// Get element `i``j` from matrix `v`
template <typename T>
std::optional<T> get(const std::vector<std::vector<T>> &v, int i, int j);

// Run a function for indexes from `starti` to `endi` and from `startj` to
// `endj`
void forIndex(ii starti, ii endi, ii startj, ii endj,
              const std::function<void(int, int)> &f);

/// Run a function for index from `starti` to `endi`
void forIndex(ii starti, ii endi, const std::function<void(int)> &f);

/// Print an unsigned in binary format
void printBinary(u val);

u getCoordinate(const u &y, const u &x);

} // namespace aoc

#include "../common/common.h"

static std::vector<std::string> getSubstringsBySpace(const std::string &input) {
  std::vector<std::string> substrings;
  std::stringstream ss(input);
  std::string word;

  while (ss >> word)
    substrings.push_back(word);

  return substrings;
}

static u getValue(const s &in) { return (in[0] << 16) | (in[1] << 8) | in[2]; }
static u getOp(const s &in) { return in == "XOR" ? 0 : in == "OR" ? 2 : 1; }

static s getString(u in) {
  s result = "";
  result += (in >> 16) & 0xff;
  result += (in >> 8) & 0xff;
  result += (in >> 0) & 0xff;
  return result;
}

struct Operation {
  u s1;
  u s2;
  u op;
  u d;
  s line;

  Operation(u f, u s, u t, u d, const std::string &o)
      : s1(f), s2(s), op(t), d(d), line(o) {}
  Operation() = default;
};

static void solve() {
  s input = aoc::getInput("2024/day_24.txt");
  u result1 = 0;
  s result2 = "";
  bool initial = true;
  vs_t toswap;

  std::map<u, u> vals;
  std::unordered_map<u, Operation> defs;
  std::unordered_map<u, usu_t> deps;

  aoc::forLineVoid(input, [&](const s &line) {
    if (initial) {
      if (line.size() < 2)
        initial = false;
      else
        vals[getValue(line.substr(0, 3))] = line[5] - '0';
    } else {
      auto subs = getSubstringsBySpace(line);
      u s1 = getValue(subs[0]), s2 = getValue(subs[2]), d = getValue(subs[4]),
        op = getOp(subs[1]);
      defs[d] = Operation(s1, s2, op, d, line);

      deps[d] = {};
      if (!vals.contains(s1))
        deps[d].insert(s1);
      if (!vals.contains(s2))
        deps[d].insert(s2);
    }
  });

  for (u i = 1; i < 45; i++) {
    std::vector<Operation> adderOps;
    u d0 = i % 10, d1 = i / 10, eq = ((d1 + '0') << 8) | (d0 + '0');
    vu_t d;

    for (auto &x : defs) {
      if (((x.second.s1 & 0xffff) == eq) or ((x.second.s2 & 0xffff) == eq)) {
        d.push_back(x.first);
        adderOps.push_back(x.second);
      }
    }

    for (auto &[def, op] : defs) {
      if (op.s1 == d[0] or op.s2 == d[0] or op.s1 == d[1] or op.s2 == d[1])
        adderOps.push_back(op);
    }

    std::sort(adderOps.begin(), adderOps.end(),
              [&](Operation &op1, Operation &op2) { return op1.op < op2.op; });

    for (auto &x : adderOps)
      std::cout << x.line << std::endl;

    // The valeus to swap were found by visually analyzing the input. Then, the
    // conditions to find the specific wrong pairs have been hardcoded
    if ((adderOps[1].d & 0xffff) != eq) {
      toswap.push_back(getString(adderOps[1].d));
      toswap.push_back('z' + getString(eq));
    }

    if (adderOps.size() == 5 and
        (adderOps[2].d != adderOps[4].s1 and adderOps[2].d != adderOps[4].s2)) {
      toswap.push_back(getString(adderOps[2].d));
      toswap.push_back(getString(adderOps[0].d));
    }
  }

  std::sort(toswap.begin(), toswap.end());
  for (u i = 0; i < toswap.size(); i++) {
    result2 += toswap[i];
    if (i != toswap.size() - 1)
      result2 += ',';
  }

  while (defs.size() != 0) {
    for (auto &x : deps) {
      if (x.second.size() == 0 and !vals.contains(x.first)) {
        auto def = defs[x.first];
        defs.erase(x.first);
        u val1 = vals[def.s1];
        u val2 = vals[def.s2];
        u result = def.op == 0   ? val1 ^ val2
                   : def.op == 2 ? val1 | val2
                                 : val1 & val2;
        vals.insert({x.first, result});
        for (auto &y : deps) {
          y.second.erase(x.first);
        }
      }
    }
  }

  u mask = 1;
  for (auto &x : vals) {
    if (getString(x.first)[0] == 'z') {
      result1 |= (x.second) ? mask : 0;
      mask <<= 1;
    }
  }

  std::cout << aoc::Color::CYAN << "~> Part 1 result: " << aoc::Color::RESET
            << result1 << std::endl;
  std::cout << aoc::Color::CYAN << "~> Part 2 result: " << aoc::Color::RESET
            << result2 << std::endl;
}

int main(int argc, char *argv[]) { solve(); }

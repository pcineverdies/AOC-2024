#include "../common/common.h"

static s getstring(u value) {
  s ss = "";
  ss += (char)(value >> 8);
  ss += (char)(value & 0xff);
  return ss;
}

using g_t = std::unordered_map<u, usu_t>;

static void bronKerbosch(usu_t r, usu_t p, usu_t x, const g_t &graph,
                         std::vector<usu_t> &cliques) {
  if (p.empty() && x.empty()) {
    cliques.emplace_back(r.begin(), r.end());
    return;
  }

  auto pcopy = p;
  for (u v : pcopy) {
    usu_t rnew = r, pnew, xnew;
    rnew.insert(v);

    for (u neighbor : graph.at(v)) {
      if (p.count(neighbor))
        pnew.insert(neighbor);
    }

    for (u neighbor : graph.at(v)) {
      if (x.count(neighbor))
        xnew.insert(neighbor);
    }

    bronKerbosch(rnew, pnew, xnew, graph, cliques);
    p.erase(v), x.insert(v);
  }
}

static std::vector<usu_t> findAllCliques(const g_t &graph) {
  std::vector<usu_t> cliques;
  usu_t r, p, x;

  for (const auto &pair : graph)
    p.insert(pair.first);

  bronKerbosch(r, p, x, graph, cliques);

  return cliques;
}

static void solve() {
  std::string input = aoc::getInput("2024/day_23.txt");

  u result1 = 0;
  g_t connections;
  usu_t triples;
  std::vector<s> password;
  u maxsize = 0;
  s result2 = "";

  aoc::forLineVoid(input, [&](const s &line) {
    s l1 = line.substr(0, 2), l2 = line.substr(3, 2);
    u lu1 = (l1[0] << 8) | l1[1], lu2 = (l2[0] << 8) | l2[1];
    connections[lu1].insert(lu2);
    connections[lu2].insert(lu1);
  });

  for (auto &[n1, conn1] : connections) {
    for (auto &n2 : conn1) {
      for (auto &n3 : connections[n2]) {
        if (connections[n1].contains(n2) and connections[n2].contains(n3) and
            connections[n3].contains(n1)) {
          vu_t nums = {n1, n2, n3};
          std::sort(nums.begin(), nums.end());
          u triple = (nums[0] << 32) | (nums[1] << 16) | nums[2];
          if (!triples.contains(triple)) {
            result1 += (((n1 >> 8) == 't') or ((n2 >> 8) == 't') or
                        ((n3 >> 8) == 't'));
            triples.insert(triple);
          }
        }
      }
    }
  }

  std::vector<usu_t> cliques = findAllCliques(connections);

  for (auto &x : cliques) {
    if (x.size() > maxsize) {
      password.clear();
      for (auto &node : x)
        password.push_back(getstring(node));
      maxsize = x.size();
    }
  }

  std::sort(password.begin(), password.end());
  for (int i = 0; i < password.size(); i++) {
    result2 += password[i];
    if (i != password.size() - 1)
      result2 += ",";
  }

  std::cout << aoc::Color::CYAN << "~> Part 1 result: " << aoc::Color::RESET
            << result1 << std::endl;
  std::cout << aoc::Color::CYAN << "~> Part 2 result: " << aoc::Color::RESET
            << result2 << std::endl;
}

int main(int argc, char *argv[]) { solve(); }

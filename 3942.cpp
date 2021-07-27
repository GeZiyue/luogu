#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <typename T>
void read(T &);
template <typename T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

const int N = 100005;

void dfs(int u, int fa);

int f[N][2];
std::vector<int> G[N];
int ans;
int n, k, id;

int main() {
  read(n), read(k), read(id);
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    G[u].push_back(v), G[v].push_back(u);
  }
  dfs(1, 0);
  ans += bool(~f[1][1]);
  write(ans), EL;
  return 0;
}

void dfs(int u, int fa) {
  f[u][0] = 1e9, f[u][1] = 0;
  for (int v : G[u]) {
    if (v == fa) continue;
    dfs(v, u);
    if (~f[v][1]) f[u][1] = std::max(f[u][1], f[v][1] + 1);
    f[u][0] = std::min(f[u][0], f[v][0] + 1);
  }
  if (f[u][1] == k) {
    f[u][0] = 0;
    f[u][1] = -1;
    ++ans;
  }
  if (f[u][0] + f[u][1] <= k) f[u][1] = -1;
}

template <typename T>
void read(T &Re) {
  T k = 0;
  char ch = getchar();
  int flag = 1;
  while (!isNum(ch)) {
    if (ch == '-') flag = -1;
    ch = getchar();
  }
  while (isNum(ch)) k = k * 10 + ch - '0', ch = getchar();
  Re = flag * k;
}
template <typename T>
void write(const T &Wr) {
  if (Wr < 0) {
    putchar('-'), write(-Wr);
  } else if (Wr < 10) {
    putchar(Wr + '0');
  } else {
    write(Wr / 10), putchar((Wr % 10) + '0');
  }
}

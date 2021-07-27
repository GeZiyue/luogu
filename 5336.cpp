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

const int N = 55;

void upd(int &x, int y) { x = std::min(x, y); }

int f[N][N][N][N], g[N][N];
int a[N], all[N], tot;
int x, y;
int n;

int main() {
  memset(f, 0x3f, sizeof(f)), memset(g, 0x3f, sizeof(g));
  read(n), read(x), read(y);
  for (int i = 1; i <= n; ++i) read(a[i]), all[i] = a[i];
  std::sort(all + 1, all + n + 1);
  tot = std::unique(all + 1, all + n + 1) - all - 1;
  for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(all + 1, all + tot + 1, a[i]) - all;
  for (int i = 1; i <= n; ++i) f[i][i][a[i]][a[i]] = 0;
  for (int l = n; l >= 1; --l) {
    for (int r = l; r <= n; ++r) {
      for (int mn = 1; mn <= tot; ++mn) {
        for (int mx = mn; mx <= tot; ++mx) {
          upd(f[l][r][std::min(mn, a[r])][std::max(mx, a[r])], f[l][r - 1][mn][mx]);
          for (int k = l; k < r; ++k) upd(f[l][r][mn][mx], f[l][k][mn][mx] + g[k + 1][r]);
        }
      }
      for (int mn = 1; mn <= tot; ++mn) {
        for (int mx = mn; mx <= tot; ++mx) {
          upd(g[l][r], f[l][r][mn][mx] + x + y * (all[mx] - all[mn]) * (all[mx] - all[mn]));
        }
      }
    }
  }
  write(g[1][n]), EL;
  return 0;
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

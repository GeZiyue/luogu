#include <bits/stdc++.h>

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

const int N = 205;
const int M = 1 << 20;
const int Mod = 998244353;

int pow(int a, int b, int ans = 1);
int det(int n);

int A[N][N];
bool f[N][N][N];
int cnt[N][N], tmp[N][N];
int k, n[N], m[N];
int T;

int main() {
  read(T);
  while (T--) {
    memset(f, 0, sizeof(f));
    read(k);
    for (int i = 1; i <= k; ++i) read(n[i]);
    for (int i = 1; i < k; ++i) read(m[i]);
    for (int i = 1; i < k; ++i) {
      for (int j = 1; j <= m[i]; ++j) {
        int u, v;
        read(u), read(v);
        f[i][u][v] = true;
      }
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n[1]; ++i) cnt[i][i] = 1;
    for (int i = 1; i < k; ++i) {
      for (int j = 1; j <= n[1]; ++j)
        for (int k = 1; k <= n[i + 1]; ++k) tmp[j][k] = 0;
      for (int j = 1; j <= n[1]; ++j) {
        for (int k = 1; k <= n[i]; ++k) {
          for (int l = 1; l <= n[i + 1]; ++l) {
            tmp[j][l] = (tmp[j][l] + 1ll * cnt[j][k] * f[i][k][l]) % Mod;
          }
        }
      }
      for (int j = 1; j <= n[1]; ++j)
        for (int k = 1; k <= n[i + 1]; ++k) cnt[j][k] = tmp[j][k];
    }
    for (int i = 1; i <= n[1]; ++i)
      for (int j = 1; j <= n[1]; ++j) A[i][j] = cnt[i][j];
    write(det(n[1])), EL;
  }
  return 0;
}

int det(int n) {
  int ans = 1;
  for (int i = 1; i <= n; ++i) {
    int tmp = 0;
    for (int j = i; j <= n; ++j) {
      if (A[j][i]) {
        tmp = j;
        break;
      }
    }
    if (!tmp) return 0;
    if (i != tmp) {
      std::swap(A[i], A[tmp]);
      ans = Mod - ans;
    }
    ans = 1ll * ans * A[i][i] % Mod;
    int iv = pow(A[i][i], Mod - 2);
    for (int j = i; j <= n; ++j) A[i][j] = 1ll * A[i][j] * iv % Mod;
    for (int j = i + 1; j <= n; ++j) {
      for (int k = n; k >= i; --k) {
        A[j][k] = (A[j][k] - 1ll * A[i][k] * A[j][i] % Mod + Mod) % Mod;
      }
    }
  }
  return ans;
}
int pow(int a, int b, int ans) {
  while (b) {
    if (b & 1) ans = 1ll * ans * a % Mod;
    a = 1ll * a * a % Mod;
    b >>= 1;
  }
  return ans;
}

template <typename T>
void read(T &Re) {
  T k = 0;
  char ch = getchar();
  int flag = 1;
  while (!std::isdigit(ch)) {
    if (ch == '-') flag = -1;
    ch = getchar();
  }
  while (std::isdigit(ch)) k = k * 10 + ch - '0', ch = getchar();
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

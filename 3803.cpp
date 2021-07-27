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

const int N = 2100000;
const int Mod = 998244353;
typedef std::vector<int> Poly;

int pow(int a, int b, int ans = 1);

namespace Pol {
int add(int a, int b) { return (a += b) >= Mod ? a -= Mod : a; }
int sub(int a, int b) { return (a -= b) < 0 ? a += Mod : a; }
void inc(int &a, int b) { (a += b) >= Mod ? a -= Mod : a; }
void dec(int &a, int b) { (a -= b) < 0 ? a += Mod : a; }
int &reduce(int &x) { return x += x >> 31 & Mod; }
void init_Poly(int n = N);
void DIT(int *A, int lim);
void DIF(int *A, int lim);
Poly mult(const Poly &A, int n, const Poly &B, int m);
ull tmp[N];
int gw[N];
}  // namespace Pol

int n, m;

int main() {
  Pol::init_Poly();
  read(n), read(m);
  ++n, ++m;
  Poly F(n), G(m);
  for (int i = 0; i < n; ++i) read(F[i]);
  for (int i = 0; i < m; ++i) read(G[i]);
  Poly ans = Pol::mult(F, n, G, m);
  for (int i = 0; i < n + m - 1; ++i) write(ans[i]), SP;
  EL;
  return 0;
}

namespace Pol {
void DIT(int *A, int lim) {
  for (int i = 0; i < lim; ++i) tmp[i] = A[i];
  for (int l = 1; l < lim; l <<= 1) {
    ull *k = tmp;
    for (int *g = gw; k < tmp + lim; k += (l << 1), ++g) {
      for (ull *x = k; x < k + l; ++x) {
        int o = x[l] % Mod;
        x[l] = 1ll * (*x + Mod - o) * *g % Mod, *x += o;
      }
    }
  }
  int iv = pow(lim, Mod - 2);
  for (int i = 0; i < lim; ++i) A[i] = 1ll * tmp[i] % Mod * iv % Mod;
  std::reverse(A + 1, A + lim);
}
void DIF(int *A, int lim) {
  for (int i = 0; i < lim; ++i) tmp[i] = A[i];
  for (int l = lim / 2; l >= 1; l >>= 1) {
    ull *k = tmp;
    for (int *g = gw; k < tmp + lim; k += (l << 1), ++g) {
      for (ull *x = k; x < k + l; ++x) {
        int o = 1ll * x[l] * *g % Mod;
        x[l] = *x + Mod - o, *x += o;
      }
    }
  }
  for (int i = 0; i < lim; ++i) A[i] = tmp[i] % Mod;
}
Poly mult(const Poly &A, int n, const Poly &B, int m) {
  int lim = 1;
  while (lim < (n + m - 1)) lim <<= 1;
  static int tA[N], tB[N];
  std::copy_n(A.begin(), n, tA), std::fill(tA + n, tA + lim, 0);
  std::copy_n(B.begin(), m, tB), std::fill(tB + m, tB + lim, 0);
  DIF(tA, lim), DIF(tB, lim);
  for (int i = 0; i < lim; ++i) tA[i] = 1ll * tA[i] * tB[i] % Mod;
  DIT(tA, lim);
  Poly ans(n + m - 1);
  std::copy_n(tA, n + m - 1, ans.begin());
  return ans;
}
void init_Poly(int n) {
  int t = 1;
  while ((1 << t) < n) ++t;
  t = std::min(t - 1, 21);
  gw[0] = 1, gw[1 << t] = pow(pow(3, 119), 1 << (21 - t));
  for (int i = t; i; --i) gw[1 << (i - 1)] = 1ll * gw[1 << i] * gw[1 << i] % Mod;
  for (int i = 1; i < (1 << t); ++i) gw[i] = 1ll * gw[i & (i - 1)] * gw[i & -i] % Mod;
}
}  // namespace Pol

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

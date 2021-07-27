#include <bits/stdc++.h>

#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

const int N = 100005;

int f[N];
int a[N];
int n, m, s;

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", f + i), s += f[i];
  for (int i = 1; i <= m; ++i) {
    int x;
    scanf("%d", &x), ++a[x];
  }
  std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
  for (int i = 1; i <= n; ++i) pq.emplace(((a[i] + 1ll) * s - 1) / f[i] + 1, i);
  int tend = (m + s - 1) / s * s;
  for (int i = m + 1; i <= tend; ++i) {
    auto [x, p] = pq.top();
    pq.pop();
    if (i > x) {
      printf("%d\n", i - m - 2);
      return 0;
    }
    pq.emplace(((++a[p] + 1ll) * s - 1) / f[p] + 1, p);
  }
  puts("forever");
  return 0;
}

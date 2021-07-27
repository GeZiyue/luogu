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

const int N = 100005;

class Seg_Tree {
 public:
  int sum[N << 2], tag[N << 2];
  Seg_Tree() {
    memset(sum, 0, sizeof(sum));
    memset(tag, -1, sizeof(tag));
  }
  void pushdown(int x, int xl, int xr);
  void cover(int x, int xl, int xr, int ul, int ur, int num);
  int query(int x, int xl, int xr, int ql, int qr);
} cov, cls;

void dfs1(int u);
void dfs2(int u);
void update(int u, int v);
int query(int u, int v);

int fa[N], dep[N], siz[N], son[N], dfn[N], top[N], dtot;
int ltim[N];
std::vector<int> G1[N];
int nowtime;
int n, q;

int main() {
  int T;
  read(T);
  while (T--) {
    memset(ltim, -1, sizeof(ltim));
    memset(son, 0, sizeof(son));
    memset(cov.sum, 0, sizeof(cov.sum));
    memset(cls.sum, 0, sizeof(cls.sum));
    memset(cov.tag, -1, sizeof(cov.tag));
    memset(cls.tag, -1, sizeof(cls.tag));
    dtot = 0;
    read(n), read(q);
    for (int i = 1; i <= n; ++i) G1[i].clear();
    for (int i = 1; i < n; ++i) {
      int u, v;
      read(u), read(v);
      G1[u].push_back(v), G1[v].push_back(u);
    }
    dfs1(1);
    top[1] = 1;
    dfs2(1);
    for (int i = 1; i <= q; ++i) {
      nowtime = i;
      int op, u, v;
      read(op), read(u), read(v);
      if (op == 1) {
        update(u, v);
      } else {
        write(query(u, v)), EL;
      }
    }
  }
  return 0;
}

void update(int u, int v) {
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    cls.cover(1, 1, n, dfn[top[u]], dfn[u], nowtime);
    if (son[u]) cov.cover(1, 1, n, dfn[son[u]], dfn[son[u]], 0);
    if (u != top[u]) cov.cover(1, 1, n, dfn[top[u]] + 1, dfn[u], 1);
    ltim[top[u]] = nowtime;
    u = fa[top[u]];
  }
  if (dep[u] < dep[v]) std::swap(u, v);
  if (son[u]) cov.cover(1, 1, n, dfn[son[u]], dfn[son[u]], 0);
  if (v != top[v]) cov.cover(1, 1, n, dfn[v], dfn[v], 0);
  cls.cover(1, 1, n, dfn[v], dfn[u], nowtime);
  if (u != v) cov.cover(1, 1, n, dfn[v] + 1, dfn[u], 1);
}
int query(int u, int v) {
  int ans = 0;
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    if (u != top[u]) ans += cov.query(1, 1, n, dfn[top[u]] + 1, dfn[u]);
    bool flag1 = ltim[top[u]] >= cls.query(1, 1, n, dfn[top[u]], dfn[top[u]]);
    bool flag2 = fa[top[u]] && (ltim[top[u]] >= cls.query(1, 1, n, dfn[fa[top[u]]], dfn[fa[top[u]]]));
    if (flag1 && flag2) ++ans;
    u = fa[top[u]];
  }
  if (dep[u] < dep[v]) std::swap(u, v);
  if (u != v) ans += cov.query(1, 1, n, dfn[v] + 1, dfn[u]);
  return ans;
}
void Seg_Tree::pushdown(int x, int xl, int xr) {
  if (~tag[x]) {
    int xm = (xl + xr) >> 1;
    sum[x << 1] = (xm - xl + 1) * tag[x];
    sum[x << 1 | 1] = (xr - xm) * tag[x];
    tag[x << 1] = tag[x << 1 | 1] = tag[x];
    tag[x] = -1;
  }
}
void Seg_Tree::cover(int x, int xl, int xr, int ul, int ur, int num) {
  if (ul <= xl && xr <= ur) {
    sum[x] = (xr - xl + 1) * num;
    tag[x] = num;
    return;
  }
  pushdown(x, xl, xr);
  int xm = (xl + xr) >> 1;
  if (ul <= xm) cover(x << 1, xl, xm, ul, ur, num);
  if (ur > xm) cover(x << 1 | 1, xm + 1, xr, ul, ur, num);
  sum[x] = sum[x << 1] + sum[x << 1 | 1];
}
int Seg_Tree::query(int x, int xl, int xr, int ql, int qr) {
  if (ql <= xl && xr <= qr) return sum[x];
  pushdown(x, xl, xr);
  int xm = (xl + xr) >> 1;
  int ans = 0;
  if (ql <= xm) ans += query(x << 1, xl, xm, ql, qr);
  if (qr > xm) ans += query(x << 1 | 1, xm + 1, xr, ql, qr);
  return ans;
}

void dfs1(int u) {
  siz[u] = 1;
  for (int v : G1[u]) {
    if (v == fa[u]) continue;
    fa[v] = u;
    dep[v] = dep[u] + 1;
    dfs1(v);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
void dfs2(int u) {
  dfn[u] = ++dtot;
  if (son[u]) {
    top[son[u]] = top[u];
    dfs2(son[u]);
  }
  for (int v : G1[u]) {
    if (v == fa[u] || v == son[u]) continue;
    top[v] = v;
    dfs2(v);
  }
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

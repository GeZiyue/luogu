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

int main() {
  int a, b;
  read(a), read(b);
  write(a + b), EL;
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
  while (isNum(ch)) k = (k << 1) + (k << 3) + ch - '0', ch = getchar();
  Re = flag * k;
}
template <typename T>
void write(const T &Wr) {
  if (Wr < 0) {
    putchar('-'), write(-Wr);
  } else {
    if (Wr < 10) {
      putchar(Wr + '0');
    } else {
      write(Wr / 10), putchar((Wr % 10) + '0');
    }
  }
}

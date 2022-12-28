#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

long snafutolong(string snafu) {
  int len = snafu.length() - 1;
  long res = 0;
  for (auto ch : snafu) {
    if (ch == '-') {
      res -= pow(5, len);
    } else if (ch == '=') {
      res -= 2 * pow(5, len);
    } else {
      res += stoi(string(1, ch)) * pow(5, len);
    }
    len -= 1;
  }
  return res;
}

string longtosnafu(long value) {
  string res = "";
  while (value) {
    long rem = value % 5;
    value /= 5;
    if (rem <= 2) {
      res = to_string(rem) + res;
    } else if (rem == 3) {
      res = "=" + res;
      value += 1;
    } else {
      res = "-" + res;
      value += 1;
    }
  }
  return res;
}

int main() {
  ifstream file("data/25");
  string str;
  long res = 0;
  while (getline(file, str)) {
    res += snafutolong(str);
  }
  cout << longtosnafu(res) << endl;
}

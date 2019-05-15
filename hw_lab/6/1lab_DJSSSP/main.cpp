#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int T;
    cout<<"input Number of test case: ";
    cin >> T;
    if (T < 1 || T > 30) {
        printf("Number of test case should be in [1, 30].\n");
        return -1;
    }
    for (int i = 0; i < T; i ++) {
        cout<<"input Number of vertices in test case " << i+1 << ": ";
        int n;
        cin >> n;
        if (n < 1 || n > 1000) {
          printf("Number of vertices should be in [1, 1000].\n");
          return -1;
        }
        int ans = 0;
        while (n > 1) {
            if (n % 3 == 0) {
                ans ++;
                n /= 3;
            }else {
                ans += n % 3;
                n -= n % 3;
            }
        }
        ans -= (n == 0);
        cout << "the shortest path is: " << ans << endl;
    }
    return 0;
}

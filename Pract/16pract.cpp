#include <iostream>

using namespace std;

void factorization(int n) {
	cout << n;
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int n;
	cin >> n;
	factorization(n);
}

/*#include <iostream>
#include <vector>

using namespace std;

int fac(int n) {
    for (int i = 2; i <= n; i++) if (!(n % i)) return i;
    return 1;
}

void factorization(int num) {
    for (int i = 2; i <= num;) {
        if (!(num % i)) {}
    }

}

int main() {
    int num;

    cin >> num;

    factorization(num);

    return 0;
}*/
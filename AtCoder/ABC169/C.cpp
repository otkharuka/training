#include <iostream>
#include <math.h>

using namespace std;

int main() {
	long long A;
	double B;
	cin >> A >> B;
	//double ‚Å‚»‚Ì‚Ü‚ÜŒvZ‚·‚é‚Æ‚Í¸“x‚ª‚½‚è‚È‚¢
	//cout << static_cast<long long> (A * B);
	long b = round(B * 100);
	cout << static_cast<long long> (A *  b / 100);
	cin >> A;
	return 0;
}
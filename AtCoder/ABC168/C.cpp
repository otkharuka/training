#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int main() {
	long double A, B, H, M;
	cin >> A >> B >> H >> M;

	long double theta = (6.0 * M) - (30.0 * H + 0.5 * M);
	long double rad = theta * M_PI / 180.0;
	long double dist = A * (A - 2.0 * B * cosl(rad)) + B * B;

	//cout << sqrtl(dist) << endl;
	cout << fixed << setprecision(21) << sqrt(dist);
	
	return 0;
}
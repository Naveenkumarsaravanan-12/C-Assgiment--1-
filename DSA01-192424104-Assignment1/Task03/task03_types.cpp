// Task 3 - Data types, sizes, ranges, double-vs-paise precision and int overflow
#include <climits>
#include <cfloat>
#include <iomanip>
#include <iostream>
#include <cmath>
int main()
{
std::cout << "---- sizeof on this system ----\n";
std::cout << "bool " << sizeof(bool) << "\n";
std::cout << "char " << sizeof(char) << "\n";
std::cout << "short " << sizeof(short) << "\n";
std::cout << "int " << sizeof(int) << "\n";
std::cout << "unsigned int " << sizeof(unsigned int) << "\n";
std::cout << "long " << sizeof(long) << "\n";
std::cout << "long long " << sizeof(long long) << "\n";
std::cout << "float " << sizeof(float) << "\n";
std::cout << "double " << sizeof(double) << "\n";
std::cout << "\n---- ranges from <climits> / <cfloat> ----\n";
std::cout << "INT_MIN " << INT_MIN << "\n";
std::cout << "INT_MAX " << INT_MAX << "\n";
std::cout << "UINT_MAX " << UINT_MAX << "\n";
std::cout << "LLONG_MIN " << LLONG_MIN << "\n";
std::cout << "LLONG_MAX " << LLONG_MAX << "\n";
std::cout << "DBL_DIG " << DBL_DIG << " reliable decimal digits\n";
std::cout << "\n---- precision problem: double rupees ----\n";
double r = 0.0;
for (int i = 0; i < 10; ++i) r += 0.10; // ten journeys of 10 paise
std::cout << std::setprecision(17) << "0.10 added 10 times = " << r
<< " (r == 1.0 is " << std::boolalpha << (r == 1.0) << ")\n";
// the first-version bug: fare computed as double then truncated to paise
double fareRs = 10 * 1.2 * 0.7; // Rs 10, peak, student
long long wrong = static_cast<long long>(fareRs * 100);
long long right = 1000LL * (100 + 20) / 100 * (100 - 30) / 100;
std::cout << "double fare = " << fareRs << " -> truncated paise = " << wrong
<< " ; integer paise = " << right << " (off by "
<< right - wrong << " paisa)\n";
std::cout << "\n---- error growth: n fares of Rs 0.10 ----\n";
for (long long n : {20000LL, 500000LL, 3000000LL}) {
double d = 0.0;
long long p = 0;
for (long long i = 0; i < n; ++i) { d += 0.10; p += 10; }
std::cout << std::setprecision(12) << "n=" << std::setw(8) << n
<< " double=" << d << " exact=" << p / 100.0
<< " abs error=" << std::scientific << std::setprecision(3)
<< std::fabs(d - p / 100.0) << std::fixed << "\n";
}
std::cout << "\n---- overflow: day's collection for the whole network ----\n";
long long journeys = 3000000, avgFarePaise = 2000;
long long total = journeys * avgFarePaise;
int wrapped = static_cast<int>(total); // what an int total would hold
std::cout << "long long total = " << total << " paise (Rs " << total / 100 << ")\n";
std::cout << "INT_MAX = " << INT_MAX << " paise (Rs " << INT_MAX / 100 << ")\n";
std::cout << "stored in int = " << wrapped << " <- wrong, overflowed\n";
}

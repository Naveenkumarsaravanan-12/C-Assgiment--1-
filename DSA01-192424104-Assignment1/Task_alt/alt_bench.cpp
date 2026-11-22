// Measurements for the "Alternative Concept and Complexity Analysis" sections
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
constexpr long long N = 200000000; // 2 x 10^8 operations
constexpr long long FARE_TABLE[] = {1000, 2000, 3000};
enum class Zone { Inner, Middle, Outer };
bool peakExpr(int h) { return (h >= 8 && h < 10) || (h >= 17 && h < 20); }
constexpr bool PEAK_TABLE[24] = {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0};
bool peakTable(int h) { return PEAK_TABLE[h]; }
long long fareSwitch(Zone z)
{
switch (z) {
case Zone::Inner: return 1000;
case Zone::Middle: return 2000;
case Zone::Outer: return 3000;
}
return 0;
}
long long fareArray(Zone z) { return FARE_TABLE[static_cast<int>(z)]; }
template <class F> double timeIt(F f)
{
auto t0 = std::chrono::steady_clock::now();
long long sink = f();
auto t1 = std::chrono::steady_clock::now();
volatile long long keep = sink; (void)keep;
return std::chrono::duration<double, std::milli>(t1 - t0).count();
}
int main()
{
std::cout << std::fixed << std::setprecision(1);
volatile int seed = 0; // stops the compiler pre-computing the loops
double a = timeIt([&] { long long c = 0; for (long long i = 0; i < N; ++i) c += peakExpr((i
+ seed) % 24); return c; });
double b = timeIt([&] { long long c = 0; for (long long i = 0; i < N; ++i) c +=
peakTable((i + seed) % 24); return c; });
std::cout << "Peak check, && / || expression : " << a << " ms for " << N << " calls\n";
std::cout << "Peak check, bool peak[24] table: " << b << " ms for " << N << " calls\n";
double c = timeIt([&] { long long s = 0; for (long long i = 0; i < N; ++i) s +=
fareSwitch(static_cast<Zone>((i + seed) % 3)); return s; });
double d = timeIt([&] { long long s = 0; for (long long i = 0; i < N; ++i) s +=
fareArray(static_cast<Zone>((i + seed) % 3)); return s; });
std::cout << "Base fare, switch : " << c << " ms for " << N << " calls\n";
std::cout << "Base fare, array by zone : " << d << " ms for " << N << " calls\n";
// reading 1,000,000 numbers: stream extraction vs getline + stoi
std::ostringstream big;
for (int i = 0; i < 1000000; ++i) big << (i % 24) << '\n';
std::string text = big.str();
double e = timeIt([&] { std::istringstream in(text); long long s = 0; int v; while (in >>
v) s += v; return s; });
double f = timeIt([&] {
std::istringstream in(text);
long long s = 0;
std::string line;
while (std::getline(in, line)) s += std::stoi(line);
return s;
});
std::cout << "Read 1,000,000 numbers, cin >> : " << e << " ms\n";
std::cout << "Read 1,000,000 numbers, getline+stoi: " << f << " ms\n";
std::cout << "sizeof(PEAK_TABLE) = " << sizeof(PEAK_TABLE) << " bytes, sizeof(FARE_TABLE) = " << sizeof(FARE_TABLE) << " bytes\n";
}

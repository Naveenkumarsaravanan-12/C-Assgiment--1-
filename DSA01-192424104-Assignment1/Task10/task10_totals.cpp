// Task 10 - double rupees vs integer paise vs int totals for 20,000 / 500,000 / 3,000,000 journeys
#include <chrono>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include "../Task09/metro_v1.hpp"
// "first version" style fare: double rupees
double fareDouble(Zone z, int hour, Category c)
{
double base = (z == Zone::Inner) ? 10.0 : (z == Zone::Middle) ? 20.0 : 30.0;
if (isPeak(hour)) base *= 1.2;
if (c == Category::Student) base *= 0.7;
if (c == Category::Senior) base *= 0.5;
return base;
}
int main()
{
std::cout << std::fixed;
std::cout << std::setw(10) << "journeys" << std::setw(18) << "paise total (LL)"
<< std::setw(22) << "double total x100" << std::setw(14) << "difference"
<< std::setw(16) << "int total" << '\n';
for (long long n : {20000LL, 500000LL, 3000000LL}) {
long long totalPaise = 0;
double totalRupees = 0.0;
unsigned int wrapped = 0; // int arithmetic, done unsigned to avoid UB
for (long long i = 0; i < n; ++i) {
Zone z = static_cast<Zone>(i % 3);
int hour = static_cast<int>((i * 7) % 24);
Category c = (i % 5 == 0) ? Category::Student : (i % 11 == 0) ? Category::Senior :
Category::Adult;
long long f = fare(z, hour, c);
totalPaise += f;
totalRupees += fareDouble(z, hour, c);
wrapped += static_cast<unsigned int>(f);
}
std::cout << std::setw(10) << n << std::setw(18) << totalPaise
<< std::setw(22) << std::setprecision(4) << totalRupees * 100
<< std::setw(14) << std::setprecision(6) << totalRupees * 100 -
static_cast<double>(totalPaise)
<< std::setw(16) << static_cast<int>(wrapped) << '\n';
}
std::cout << "INT_MAX = " << INT_MAX << "\n\n";
// time per addition and space per variable
const std::size_t N = 3000000;
std::vector<int> fi(N, 2000);
std::vector<long long> fl(N, 2000);
std::vector<double> fd(N, 20.0);
auto t0 = std::chrono::steady_clock::now();
unsigned int si = 0; for (std::size_t i = 0; i < N; ++i) si += static_cast<unsigned
int>(fi[i]);
auto t1 = std::chrono::steady_clock::now();
long long sl = 0; for (std::size_t i = 0; i < N; ++i) sl += fl[i];
auto t2 = std::chrono::steady_clock::now();
double sd = 0; for (std::size_t i = 0; i < N; ++i) sd += fd[i];
auto t3 = std::chrono::steady_clock::now();
auto ns = [](auto a, auto b) { return std::chrono::duration<double, std::nano>(b -
a).count() / 3000000.0; };
std::cout << std::setprecision(3);
std::cout << "int sum=" << static_cast<int>(si) << " " << ns(t0, t1) << " ns/add sizeof=" << sizeof(int) << '\n';
std::cout << "long long sum=" << sl << " " << ns(t1, t2) << " ns/add sizeof=" <<
sizeof(long long) << '\n';
std::cout << "double sum=" << std::setprecision(1) << sd << " " << std::setprecision(3)
<< ns(t2, t3) << " ns/add sizeof=" << sizeof(double) << '\n';
}

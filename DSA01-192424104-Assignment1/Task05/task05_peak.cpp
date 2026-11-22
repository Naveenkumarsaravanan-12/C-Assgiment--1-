// Task 5 - peak check, surcharge and concession expressions
#include <iostream>
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int STUDENT_CONCESSION_PERCENT = 30;
bool isPeak(int hour)
{
return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20); // brackets show intent
}
bool isPeakNoBrackets(int hour)
{
return hour >= 8 && hour < 10 || hour >= 17 && hour < 20; // same meaning: && binds tighter than ||
}
int main()
{
bool same = true;
std::cout << "hour : peak\n";
for (int h = 0; h < 24; ++h) {
if (isPeak(h) != isPeakNoBrackets(h)) same = false;
if (isPeak(h) || h == 7 || h == 10 || h == 16 || h == 20)
std::cout << (h < 10 ? " " : "") << h << " : " << std::boolalpha << isPeak(h) <<
'\n';
}
std::cout << "Both forms agree for all 24 hours: " << std::boolalpha << same << '\n';
long long base = 3000; // Outer, Rs 30.00
long long peakFare = base + base * PEAK_SURCHARGE_PERCENT / 100; // * and / before +
long long studentFare = peakFare - peakFare * STUDENT_CONCESSION_PERCENT / 100;
bool peak = isPeak(9);
long long fare = peak ? base + base * PEAK_SURCHARGE_PERCENT / 100 : base; // ?: has lower precedence than +
fare -= fare * STUDENT_CONCESSION_PERCENT / 100; // compound assignment, right-to-left
std::cout << "Outer peak fare (paise) : " << peakFare << '\n';
std::cout << "Outer peak student fare (paise) : " << studentFare << '\n';
std::cout << "Same through ?: and -= : " << fare << '\n';
int i = 5;
int j = i++; // j gets 5, then i becomes 6
int m = 5;
int n = ++m; // m becomes 6, then n gets 6
std::cout << "i++ : j=" << j << " i=" << i << " ++m : n=" << n << " m=" << m << '\n';
}

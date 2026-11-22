// Task 6 - journeys at exactly 10 AM and 8 PM (peak window is [8,10) and [17,20))
#include <iomanip>
#include <iostream>
enum class Zone { Inner, Middle, Outer };
constexpr int BASE_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;
bool isPeak(int hour) { return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20); }
long long fare(Zone z, bool peak)
{
long long base = 0;
switch (z) {
case Zone::Inner: base = BASE_PAISE[0]; break;
case Zone::Middle: base = BASE_PAISE[1]; break;
case Zone::Outer: base = BASE_PAISE[2]; break;
}
if (peak) base += base * PEAK_SURCHARGE_PERCENT / 100;
return base;
}
bool canTravel(long long balance, long long f) { return balance - f >= MIN_BALANCE_PAISE; }
int main()
{
long long balance = 100000; // Rs 1000, large enough to focus on the peak rule
int hours[] = {9, 10, 19, 20};
for (int h : hours) {
long long f = fare(Zone::Outer, isPeak(h));
if (canTravel(balance, f)) balance -= f;
std::cout << std::setw(2) << h << ":00 peak=" << std::boolalpha << std::setw(5) <<
isPeak(h)
<< " Outer fare Rs " << f / 100 << '.' << std::setw(2) << std::setfill('0')
<< f % 100
<< std::setfill(' ') << '\n';
}
}

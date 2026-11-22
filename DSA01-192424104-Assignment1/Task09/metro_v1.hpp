// metro_v1.hpp - final design of the fare logic (three zones)
#pragma once
enum class Zone { Inner, Middle, Outer };
enum class Category { Adult, Student, Senior };
constexpr long long BASE_PAISE[] = {1000, 2000, 3000}; // Rs 10, 20, 30 - the ONLY place fares are typed
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int STUDENT_CONCESSION_PERCENT = 30;
constexpr int SENIOR_CONCESSION_PERCENT = 50;
constexpr long long MIN_BALANCE_PAISE = 5000; // Rs 50 must remain
constexpr int PEAK_AM_START = 8, PEAK_AM_END = 10; // [8,10)
constexpr int PEAK_PM_START = 17, PEAK_PM_END = 20; // [17,20)
inline bool isPeak(int hour)
{
return (hour >= PEAK_AM_START && hour < PEAK_AM_END) ||
(hour >= PEAK_PM_START && hour < PEAK_PM_END);
}
inline long long baseFare(Zone z)
{
long long base = 0;
switch (z) {
case Zone::Inner: base = BASE_PAISE[0]; break;
case Zone::Middle: base = BASE_PAISE[1]; break;
case Zone::Outer: base = BASE_PAISE[2]; break;
}
return base;
}
inline int concessionPercent(Category c)
{
switch (c) {
case Category::Student: return STUDENT_CONCESSION_PERCENT;
case Category::Senior: return SENIOR_CONCESSION_PERCENT;
case Category::Adult: return 0;
}
return 0;
}
// Fare in integer paise: surcharge first, concession second.
inline long long fare(Zone z, int hour, Category c)
{
long long f = baseFare(z);
if (isPeak(hour)) f += f * PEAK_SURCHARGE_PERCENT / 100;
f -= f * concessionPercent(c) / 100;
return f;
}
class SmartCard {
long long balance_;
public:
explicit SmartCard(long long paise = 0) : balance_(paise < 0 ? 0 : paise) {}
long long balance() const { return balance_; }
bool canTravel(long long f) const { return f >= 0 && balance_ - f >= MIN_BALANCE_PAISE; }
bool deduct(long long f)
{
if (!canTravel(f)) return false;
balance_ -= f;
return true;
}
bool recharge(long long paise)
{
if (paise <= 0) return false;
balance_ += paise;
return true;
}
};

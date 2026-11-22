// metro_v2.hpp - REVISED design: four zones, weekend discount, monthly pass
#pragma once
enum class Zone { Inner, Middle, Outer, Airport };
enum class Category { Adult, Student, Senior };
constexpr int ZONE_COUNT = 4;
constexpr long long BASE_PAISE[ZONE_COUNT] = {1000, 2000, 3000, 6000}; // Airport = Rs 60
static_assert(sizeof(BASE_PAISE) / sizeof(BASE_PAISE[0]) == ZONE_COUNT, "fare table must have one entry per zone");
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int WEEKEND_DISCOUNT_PERCENT = 10;
constexpr int STUDENT_CONCESSION_PERCENT = 30;
constexpr int SENIOR_CONCESSION_PERCENT = 50;
constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int PEAK_AM_START = 8, PEAK_AM_END = 10, PEAK_PM_START = 17, PEAK_PM_END = 20;
inline bool isPeak(int hour)
{
return (hour >= PEAK_AM_START && hour < PEAK_AM_END) || (hour >= PEAK_PM_START && hour <
PEAK_PM_END);
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
// Separate rule: peak surcharge OR weekend discount, never both (surcharge wins in peak hours).
inline long long timeAdjusted(long long base, int hour, bool weekend)
{
if (isPeak(hour)) return base + base * PEAK_SURCHARGE_PERCENT / 100;
if (weekend) return base - base * WEEKEND_DISCOUNT_PERCENT / 100;
return base;
}
inline long long fare(Zone z, int hour, bool weekend, Category c)
{
long long f = timeAdjusted(BASE_PAISE[static_cast<int>(z)], hour, weekend); // table lookup, no switch
return f - f * concessionPercent(c) / 100;
}
// Monthly pass: unlimited journeys when the farthest zone travelled is one of two chosen zones.
class Pass {
Zone a_, b_;
bool active_;
public:
Pass() : a_(Zone::Inner), b_(Zone::Inner), active_(false) {}
Pass(Zone a, Zone b) : a_(a), b_(b), active_(true) {}
bool covers(Zone z) const { return active_ && (z == a_ || z == b_); }
};
class SmartCard {
long long balance_;
Pass pass_;
public:
explicit SmartCard(long long paise = 0) : balance_(paise < 0 ? 0 : paise) {}
void buyPass(const Pass& p) { pass_ = p; }
long long balance() const { return balance_; }
bool canTravel(long long f) const { return f >= 0 && balance_ - f >= MIN_BALANCE_PAISE; }
// Returns true if the journey is allowed; 'charged' receives the amount deducted.
bool travel(Zone z, int hour, bool weekend, Category c, long long& charged)
{
if (pass_.covers(z)) { charged = 0; return true; } // covered by the pass: free, nothing deducted
long long f = fare(z, hour, weekend, c);
if (!canTravel(f)) { charged = 0; return false; }
balance_ -= f;
charged = f;
return true;
}
bool recharge(long long paise)
{
if (paise <= 0) return false;
balance_ += paise;
return true;
}
};

// Task 7 - OBJECT-ORIENTED version: SmartCard keeps balance private
#include <iostream>
enum class Zone { Inner, Middle, Outer };
class FareTable {
static constexpr long long BASE[3] = {1000, 2000, 3000};
static constexpr int PEAK_PERCENT = 20;
public:
static long long fare(Zone z, bool peak)
{
long long base = BASE[static_cast<int>(z)];
return peak ? base + base * PEAK_PERCENT / 100 : base;
}
};
class SmartCard {
static constexpr long long MIN_BALANCE = 5000; // the ONLY place the rule is written
long long balance_; // private: cannot be set from outside
public:
explicit SmartCard(long long paise) : balance_(paise < 0 ? 0 : paise) {}
long long balance() const { return balance_; }
bool canTravel(long long fare) const { return fare >= 0 && balance_ - fare >=
MIN_BALANCE; }
bool deduct(long long fare)
{
if (!canTravel(fare)) return false; // negative balance is impossible balance_ -= fare;
return true;
}
bool recharge(long long paise)
{
if (paise <= 0) return false;
balance_ += paise;
return true;
}
};
int main()
{
SmartCard card(10000);
struct Trip { Zone z; bool peak; };
Trip trips[] = {{Zone::Inner, false}, {Zone::Outer, true}, {Zone::Middle, false}};
for (const Trip& t : trips) {
long long f = FareTable::fare(t.z, t.peak);
if (card.deduct(f)) std::cout << "paid " << f << " balance " << card.balance() << '\n';
else std::cout << "denied balance " << card.balance() << '\n';
}
std::cout << "deduct(9999) accepted? " << std::boolalpha << card.deduct(9999)
<< " balance still " << card.balance() << '\n';
std::cout << "recharge(-500) accepted? " << card.recharge(-500) << '\n';
std::cout << "sizeof(SmartCard) = " << sizeof(SmartCard) << " bytes\n";
}

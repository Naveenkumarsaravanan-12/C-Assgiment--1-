// Task 7 - PROCEDURAL version: global data + free functions
#include <iostream>
long long balance = 10000; // global: any function can change it
long long fareFor(int zone, bool peak)
{
long long base = (zone == 0) ? 1000 : (zone == 1) ? 2000 : 3000;
return peak ? base + base * 20 / 100 : base;
}
bool canTravel(long long f) { return balance - f >= 5000; } // min balance typed here ...
void travel(int zone, bool peak)
{
long long f = fareFor(zone, peak);
if (balance - f >= 5000) { balance -= f; std::cout << "paid " << f << " balance " <<
balance << '\n'; } // ... and here
else std::cout << "denied balance " << balance << '\n';
}
int main()
{
travel(0, false);
travel(2, true);
travel(1, false);
balance -= 9999; // nothing stops this careless line
std::cout << "after careless change: balance = " << balance << " paise\n";
}

// Task 12B - what happens if ONLY the enum is extended and the old switch is left alone
#include <iostream>
enum class Zone { Inner, Middle, Outer, Airport }; // fourth zone added to the enum
constexpr int BASE_PAISE[] = {1000, 2000, 3000}; // table still has 3 entries
long long fare(Zone z)
{
long long base = 0;
switch (z) { // no case for Airport
case Zone::Inner: base = BASE_PAISE[0]; break;
case Zone::Middle: base = BASE_PAISE[1]; break;
case Zone::Outer: base = BASE_PAISE[2]; break;
}
return base;
}
int main()
{
std::cout << "Airport fare from the old switch = " << fare(Zone::Airport) << " paise (free travel to the airport!)\n";
}

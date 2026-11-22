// Task 2 - Tokens, keywords, identifiers and constants
#include <iostream>
#define OLD_SURCHARGE 20 // macro: no type, no scope, replaced by the preprocessor
#define FARE_PLUS_TAX 10 + 2 // classic macro trap: no brackets
const int MIN_BAL_CONST = 5000; // const: typed, but may be evaluated at run time
constexpr long long BASE_PAISE[] = {1000, 2000, 3000}; // constexpr: guaranteed compile-time value
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000;
enum class Zone { Inner, Middle, Outer }; // scoped, strongly typed
enum OldZone { INNER, MIDDLE, OUTER }; // plain enum: names leak, converts to int
constexpr long long baseFare(Zone z) { return BASE_PAISE[static_cast<int>(z)]; }
static_assert(baseFare(Zone::Outer) == 3000, "Outer base fare must be Rs 30");
int main()
{
// Tokens in the next statement: keyword = constexpr/long/long/int, identifier = peak,
// constant = 3000, operator = * and /, punctuators = ( ) ; { }
constexpr long long peak = baseFare(Zone::Outer) * PEAK_SURCHARGE_PERCENT / 100;
std::cout << "Outer peak surcharge (paise) : " << peak << '\n';
std::cout << "FARE_PLUS_TAX * 3 (macro) : " << FARE_PLUS_TAX * 3
<< " <- expands to 10 + 2 * 3, not (10+2)*3\n";
std::cout << "(10+2) * 3 (what was intended) : " << (10 + 2) * 3 << '\n';
int fromPlainEnum = OUTER; // compiles silently: enum -> int
std::cout << "Plain enum OUTER as int : " << fromPlainEnum << '\n';
std::cout << "Scoped enum needs a cast : " << static_cast<int>(Zone::Outer) <<
'\n';
std::cout << "sizeof(Zone) : " << sizeof(Zone) << " bytes\n";
std::cout << "sizeof(BASE_PAISE) : " << sizeof(BASE_PAISE) << " bytes (array of 3 long long)\n";
std::cout << "MIN_BAL_CONST + MIN_BALANCE_PAISE : " << MIN_BAL_CONST + MIN_BALANCE_PAISE <<
'\n';
std::cout << "OLD_SURCHARGE : " << OLD_SURCHARGE << '\n';
}

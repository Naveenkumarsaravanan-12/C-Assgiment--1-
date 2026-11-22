// Task 8 - safe input with cin, cin.fail(), cin.clear(), cin.ignore() and iomanip output
#include <iomanip>
#include <iostream>
#include <limits>
enum class Zone { Inner, Middle, Outer };
constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
bool readInt(const char* prompt, int lo, int hi, int& out)
{
for (;;) {
std::cout << prompt << std::flush;
int v;
if (!(std::cin >> v)) {
if (std::cin.eof()) return false; // input finished
std::cin.clear(); // clear the error state
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad line
std::cout << " invalid input - digits only, try again\n";
continue;
}
if (v < lo || v > hi) {
std::cout << " out of range (" << lo << ".." << hi << "), try again\n";
continue;
}
out = v;
return true;
}
}
void printMoney(long long paise)
{
std::cout << "Rs " << std::setw(5) << paise / 100 << '.' << std::setfill('0') <<
std::setw(2)
<< paise % 100 << std::setfill(' ');
}
int main()
{
int hour, zone, category, recharge;
if (!readInt("Hour of journey (0-23) : ", 0, 23, hour)) return 1;
if (!readInt("Farthest zone (0=Inner,1=Middle,2=Outer): ", 0, 2, zone)) return 1;
if (!readInt("Category (0=Adult,1=Student,2=Senior) : ", 0, 2, category)) return 1;
if (!readInt("Recharge in whole rupees (0-5000) : ", 0, 5000, recharge)) return 1;
long long balance = 10000 + recharge * 100LL;
bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
long long f = BASE_PAISE[zone];
if (peak) f += f * 20 / 100;
if (category == 1) f -= f * 30 / 100;
if (category == 2) f -= f * 50 / 100;
bool ok = balance - f >= 5000;
std::cout << "\n==== JOURNEY REPORT ====\n";
std::cout << std::left << std::setw(16) << "Hour" << std::right << std::setw(6) <<
hour << " " << (peak ? "(peak)" : "(off-peak)") << '\n';
std::cout << std::left << std::setw(16) << "Fare" << std::right; printMoney(f);
std::cout << '\n';
std::cout << std::left << std::setw(16) << "Opening bal." << std::right;
printMoney(balance); std::cout << '\n';
if (ok) balance -= f;
std::cout << std::left << std::setw(16) << "Closing bal." << std::right;
printMoney(balance); std::cout << '\n';
std::cout << "Status " << (ok ? "ALLOWED" : "DENIED") << '\n';
std::cout << std::fixed << std::setprecision(2) << "Balance as double (display only): Rs "
<< balance / 100.0 << '\n';
}

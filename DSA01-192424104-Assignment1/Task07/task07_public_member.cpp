// Task 7 - ALTERNATIVE: public data member. Same time and space, but the rule can be broken.
#include <iostream>
struct SmartCard { long long balance = 10000; }; // public by default
int main()
{
SmartCard c;
c.balance -= 15000; // compiles, runs: balance is now negative and below Rs 50
std::cout << "balance = " << c.balance << " paise (rule 'never below Rs 50' broken)\n";
std::cout << "sizeof(SmartCard) = " << sizeof(SmartCard) << " bytes\n";
}

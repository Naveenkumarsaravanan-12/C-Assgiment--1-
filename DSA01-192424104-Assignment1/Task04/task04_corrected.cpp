// Task 4 - corrected version: every conversion is explicit
#include <iostream>
int main()
{
int a{7}, b{2};
double c{static_cast<double>(a / b)}; // integer division made explicit: 3
double d{static_cast<double>(a) / b}; // real division: 3.5
std::cout << c << ' ' << d << '\n';
char ch{static_cast<char>('A' + 2)}; // int -> char made visible
std::cout << ch << ' ' << static_cast<int>(ch) + 1 << '\n';
bool flag{5 != 0}; // bool{5} would be a narrowing error
std::cout << flag << ' ' << std::boolalpha << flag << '\n';
unsigned int u{1};
int s{-1};
bool less = s < 0 || static_cast<unsigned int>(s) < u; // compare as signed first
std::cout << (less ? "s < u" : "s >= u") << '\n';
}

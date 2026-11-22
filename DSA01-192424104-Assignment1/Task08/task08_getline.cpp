// Task 8 - ALTERNATIVE: getline + stoi inside try/catch
#include <iostream>
#include <string>
int main()
{
std::string line;
int accepted = 0;
while (std::getline(std::cin, line)) {
try {
std::size_t used = 0;
int v = std::stoi(line, &used);
if (used != line.size()) throw std::invalid_argument("trailing characters");
std::cout << "accepted " << v << '\n';
++accepted;
} catch (const std::invalid_argument& e) {
std::cout << "rejected \"" << line << "\" (" << e.what() << ")\n";
} catch (const std::out_of_range&) {
std::cout << "rejected \"" << line << "\" (out of range for int)\n";
}
}
std::cout << accepted << " values accepted\n";
}

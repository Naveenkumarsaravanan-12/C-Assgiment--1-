// Task 11 - ALTERNATIVE: fare table read from a configuration file at start-up
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
int main()
{
auto t0 = std::chrono::steady_clock::now();
std::ifstream in("fares.cfg");
if (!in) { std::cout << "cannot open fares.cfg - gate refuses to start\n"; return 1; }
std::vector<long long> fares;
std::string line;
while (std::getline(in, line)) {
if (line.empty() || line[0] == '#') continue;
std::istringstream ss(line);
int zone; long long paise;
if (!(ss >> zone >> paise) || zone != static_cast<int>(fares.size()) || paise <= 0) {
std::cout << "bad line in fares.cfg: \"" << line << "\"\n"; return 1;
}
fares.push_back(paise);
}
auto t1 = std::chrono::steady_clock::now();
double us = std::chrono::duration<double, std::micro>(t1 - t0).count();
std::cout << "loaded " << fares.size() << " fares in " << us << " microseconds\n";
for (std::size_t z = 0; z < fares.size(); ++z) std::cout << "zone " << z << " = " <<
fares[z] << " paise\n";
std::cout << "space used: " << fares.size() * sizeof(long long) << " bytes (+ vector overhead " << sizeof(fares) << ")\n";
}

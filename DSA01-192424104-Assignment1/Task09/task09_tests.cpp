// Task 9 - table-driven tests for the fare logic
#include <iomanip>
#include <iostream>
#include <string>
#include "metro_v1.hpp"

// input validation helpers (invalid cases)
bool parseZone(int code, Zone& z)
{
    if (code < 0 || code > 2) return false;
    z = static_cast<Zone>(code);
    return true;
}
bool parseHour(const std::string& s, int& hour)
{
    try {
        std::size_t used = 0;
        int v = std::stoi(s, &used);
        if (used != s.size() || v < 0 || v > 23) return false;
        hour = v;
        return true;
    } catch (...) { return false; }
}
struct Case {
    const char* name;
    Zone zone; int hour; Category cat;
    long long startBalance;
    long long expectFare;
    bool expectAllowed;
    long long expectBalance;
};
int main()
{
    const Case cases[] = {
        // normal journeys
        {"Inner 12:00 adult", Zone::Inner, 12, Category::Adult, 10000, 1000, true, 9000},
        {"Inner 09:00 adult", Zone::Inner, 9, Category::Adult, 10000, 1200, true, 8800},
        {"Middle 12:00 adult", Zone::Middle, 12, Category::Adult, 10000, 2000, true, 8000},
        {"Middle 18:00 adult", Zone::Middle, 18, Category::Adult, 10000, 2400, true, 7600},
        {"Outer 22:00 adult", Zone::Outer, 22, Category::Adult, 10000, 3000, true, 7000},
        {"Outer 08:00 adult", Zone::Outer, 8, Category::Adult, 10000, 3600, true, 6400},
        // boundary hours (Inner zone)
        {"hour 07 (before peak)", Zone::Inner, 7, Category::Adult, 10000, 1000, true, 9000},
        {"hour 08 (peak starts)", Zone::Inner, 8, Category::Adult, 10000, 1200, true, 8800},
        {"hour 10 (peak ended)", Zone::Inner, 10, Category::Adult, 10000, 1000, true, 9000},
        {"hour 16 (before eve.)", Zone::Inner, 16, Category::Adult, 10000, 1000, true, 9000},
        {"hour 17 (peak starts)", Zone::Inner, 17, Category::Adult, 10000, 1200, true, 8800},
        {"hour 19 (still peak)", Zone::Inner, 19, Category::Adult, 10000, 1200, true, 8800},
        {"hour 20 (peak ended)", Zone::Inner, 20, Category::Adult, 10000, 1000, true, 9000},
        // balance boundary: exactly Rs 50 must remain
        {"leaves exactly Rs 50", Zone::Inner, 12, Category::Adult, 6000, 1000, true, 5000},
        {"leaves Rs 49.99", Zone::Inner, 12, Category::Adult, 5999, 1000, false, 5999},
        {"balance already Rs 50", Zone::Inner, 12, Category::Adult, 5000, 1000, false, 5000},
        // concessions
        {"Outer 22:00 student", Zone::Outer, 22, Category::Student, 10000, 2100, true, 7900},
        {"Inner 18:00 senior", Zone::Inner, 18, Category::Senior, 10000, 600, true, 9400},
    };
    int pass = 0, total = 0;
    std::cout << std::left << std::setw(24) << "Test" << std::right << std::setw(8) << "ExpFare"
              << std::setw(8) << "ActFare" << std::setw(9) << "ExpAllow" << std::setw(9) << "ActAllow"
              << std::setw(8) << "ExpBal" << std::setw(8) << "ActBal" << " Result\n";
    for (const Case& c : cases) {
        long long f = fare(c.zone, c.hour, c.cat);
        SmartCard card(c.startBalance);
        bool allowed = card.deduct(f);
        bool ok = (f == c.expectFare) && (allowed == c.expectAllowed) && (card.balance() == c.expectBalance);
        ++total; if (ok) ++pass;
        std::cout << std::left << std::setw(24) << c.name << std::right << std::setw(8) << c.expectFare
                  << std::setw(8) << f << std::setw(9) << std::boolalpha << c.expectAllowed
                  << std::setw(9) << allowed << std::setw(8) << c.expectBalance << std::setw(8)
                  << card.balance() << (ok ? " PASS" : " FAIL") << '\n';
    }
    // invalid cases
    Zone z; int h;
    auto report = [&](const char* name, bool expect, bool actual) {
        bool ok = expect == actual; ++total; if (ok) ++pass;
        std::cout << std::left << std::setw(40) << name << "expected " << std::setw(6) << std::boolalpha << expect
                  << "actual " << std::setw(6) << actual << (ok ? "PASS" : "FAIL") << '\n';
    };
    std::cout << "\nInvalid-input tests (true = input accepted)\n";
    report("unknown zone code 7 rejected", false, parseZone(7, z));
    report("zone code 2 accepted", true, parseZone(2, z));
    SmartCard c2(10000);
    report("recharge of -500 rejected", false, c2.recharge(-500));
    report("recharge of 0 rejected", false, c2.recharge(0));
    report("recharge of 5000 accepted", true, c2.recharge(5000));
    report("hour \"ab\" (letters) rejected", false, parseHour("ab", h));
    report("hour \"9x\" rejected", false, parseHour("9x", h));
    report("hour \"24\" rejected", false, parseHour("24", h));
    report("hour \"9\" accepted", true, parseHour("9", h));
    // five journeys whose total was calculated by hand
    std::cout << "\nFive journeys (hand-calculated total = Rs 97.00)\n";
    struct J { Zone z; int hour; Category c; long long hand; };
    const J js[] = {
        {Zone::Inner, 12, Category::Adult, 1000},
        {Zone::Middle, 9, Category::Adult, 2400},
        {Zone::Outer, 22, Category::Student, 2100},
        {Zone::Inner, 17, Category::Senior, 600},
        {Zone::Outer, 19, Category::Adult, 3600},
    };
    SmartCard card(20000);
    long long sum = 0, handSum = 0;
    for (const J& j : js) {
        long long f = fare(j.z, j.hour, j.c);
        card.deduct(f);
        sum += f; handSum += j.hand;
        std::cout << " fare " << std::setw(5) << f << " hand " << std::setw(5) << j.hand
                  << (f == j.hand ? " match" : " MISMATCH") << '\n';
    }
    bool ok = (sum == 9700) && (handSum == 9700) && (card.balance() == 10300);
    ++total; if (ok) ++pass;
    std::cout << " program total " << sum << " hand total " << handSum << " closing balance "
              << card.balance() << (ok ? " PASS" : " FAIL") << '\n';
    std::cout << "\n" << pass << " of " << total << " tests passed\n";
    return pass == total ? 0 : 1;
}

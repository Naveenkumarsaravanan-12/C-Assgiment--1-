// Task 12 - tests for the revised design
#include <iomanip>
#include <iostream>
#include "metro_v2.hpp"

struct Case {
    const char* name; Zone z; int hour; bool weekend; Category c; long long expect;
};

int main()
{
    const Case cases[] = {
        {"Airport weekday 12:00 adult", Zone::Airport, 12, false, Category::Adult, 6000},
        {"Airport weekday 09:00 adult", Zone::Airport, 9, false, Category::Adult, 7200},
        {"Inner weekend 12:00 adult", Zone::Inner, 12, true, Category::Adult, 900},
        {"Outer weekend 12:00 adult", Zone::Outer, 12, true, Category::Adult, 2700},
        {"Outer weekend 18:00 (peak) adult", Zone::Outer, 18, true, Category::Adult, 3600},
        {"Airport weekend 12:00 adult", Zone::Airport, 12, true, Category::Adult, 5400},
        {"Airport weekend 12:00 student", Zone::Airport, 12, true, Category::Student, 3780},
        {"Airport weekday 22:00 senior", Zone::Airport, 22, false, Category::Senior, 3000},
        // regression: the five journeys from Task 9 must give the same fares as before
        {"R1 Inner 12 adult", Zone::Inner, 12, false, Category::Adult, 1000},
        {"R2 Middle 9 adult", Zone::Middle, 9, false, Category::Adult, 2400},
        {"R3 Outer 22 student", Zone::Outer, 22, false, Category::Student, 2100},
        {"R4 Inner 17 senior", Zone::Inner, 17, false, Category::Senior, 600},
        {"R5 Outer 19 adult", Zone::Outer, 19, false, Category::Adult, 3600},
    };
    int pass = 0, total = 0;
    for (const Case& c : cases) {
        long long f = fare(c.z, c.hour, c.weekend, c.c);
        bool ok = f == c.expect; ++total; if (ok) ++pass;
        std::cout << std::left << std::setw(36) << c.name << std::right << " expected " << std::setw(5) << c.expect
                  << " actual " << std::setw(5) << f << (ok ? " PASS" : " FAIL") << '\n';
    }

    long long charged = 0;
    auto check = [&](const char* name, bool cond) {
        ++total; if (cond) ++pass;
        std::cout << std::left << std::setw(60) << name << (cond ? "PASS" : "FAIL") << '\n';
    };
    std::cout << "\nMonthly pass tests (pass: Inner + Middle)\n";
    SmartCard p(10000);
    p.buyPass(Pass(Zone::Inner, Zone::Middle));
    check("Middle journey is free, balance unchanged", p.travel(Zone::Middle, 9, false, Category::Adult, charged) && charged == 0 && p.balance() == 10000);
    check("Inner journey is free in peak hour", p.travel(Zone::Inner, 18, false, Category::Adult, charged) && charged == 0);
    check("Outer journey is NOT covered: Rs 30 charged", p.travel(Zone::Outer, 12, false, Category::Adult, charged) && charged == 3000 && p.balance() == 7000);
    check("Airport journey denied: Rs 60 would leave Rs 10", !p.travel(Zone::Airport, 12, false, Category::Adult, charged) && p.balance() == 7000);

    SmartCard q(10000);
    check("Card without a pass pays for Middle", q.travel(Zone::Middle, 12, false, Category::Adult, charged) && charged == 2000);

    // the 5-journey scenario again, now through SmartCard::travel
    SmartCard five(20000);
    struct J { Zone z; int h; Category c; };
    const J js[] = {{Zone::Inner,12,Category::Adult},{Zone::Middle,9,Category::Adult},
                    {Zone::Outer,22,Category::Student},{Zone::Inner,17,Category::Senior},
                    {Zone::Outer,19,Category::Adult}};
    long long sum = 0;
    for (const J& j : js) { five.travel(j.z, j.h, false, j.c, charged); sum += charged; }
    std::cout << "\nFive-journey regression: total " << sum << " (expected 9700), closing balance " << five.balance() << " (expected 10300)\n";
    check("Five-journey total unchanged by the redesign", sum == 9700 && five.balance() == 10300);
    std::cout << "\n" << pass << " of " << total << " tests passed\n";
    return pass == total ? 0 : 1;
}

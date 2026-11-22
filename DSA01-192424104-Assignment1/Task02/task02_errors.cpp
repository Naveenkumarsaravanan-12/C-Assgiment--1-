// Task 2 - compile-time errors that constexpr / enum class catch (and #define / plain enum do not)
#define OLD_SURCHARGE 20
enum class Zone { Inner, Middle, Outer };
int main()
{
int a = Zone::Inner; // ERROR: no implicit conversion from enum class to int
Zone z = 1; // ERROR: int cannot become Zone
int OLD_SURCHARGE = 5; // ERROR: macro silently rewrites this to "int 20 = 5;"
return a + static_cast<int>(z);
}

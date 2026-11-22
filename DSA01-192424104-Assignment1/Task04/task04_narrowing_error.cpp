// Task 4 - brace initialisation refuses narrowing conversions
int main()
{
int x{3.7}; // ERROR: narrowing double -> int
int y = 3.7; // accepted silently, y becomes 3
return x + y;
}

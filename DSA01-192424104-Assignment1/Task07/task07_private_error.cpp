// Task 7 - the compiler refuses direct access to the private balance
class SmartCard {
long long balance_ = 10000;
public:
long long balance() const { return balance_; }
};
int main()
{
SmartCard c;
c.balance_ -= 9999; // ERROR: 'balance_' is private within this context
return 0;
}

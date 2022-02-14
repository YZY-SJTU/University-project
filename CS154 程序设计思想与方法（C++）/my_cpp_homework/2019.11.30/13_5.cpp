#include<iostream>

using namespace std;

class SavingAccount
{
private:
    int AccountNumber;
    char SavingDate[9]; //the form is YYYYMMDD'\0'
    double sum;
    static double rate_month;
    static int NextNumber;
public:
    SavingAccount():AccountNumber(NextNumber),sum(0) {++NextNumber;}
    static void setRate(double newRate) {rate_month = newRate;}
    void SaveMoney(double money){sum += money;}
    void SaveMonthProfitToAccount(){sum += sum*rate_month;}
    void displayMoney(){cout << "Your total saving is "<< sum << endl;}
    void displayAccountNumber(){cout << "Your account number is:"<< AccountNumber<< endl;} 
};

int SavingAccount::NextNumber = 1;
double SavingAccount::rate_month = 0;

int main()
{
    double rate,money;
    int i;
    cout << "Set the rate of each month:";
    cin >>rate;
    SavingAccount::setRate(rate);
    SavingAccount AccountArr[10],account;
    cout << endl;
    for (i=1; i<=10; ++i)
    {
        cout << "No." << i;
        AccountArr[i-1].displayAccountNumber(); 
    }
    cout << endl<< "No." << 11;
    account.displayAccountNumber();
    cout << "Input the sum of money you want to save :";
    cin.get();
    cin >> money;
    account.SaveMoney(money);
    account.displayMoney();
    for (i=1; i<=12; ++i)
    {
        account.SaveMonthProfitToAccount();
        cout << "After "<< i<< " month(at conpound interest),";
        account.displayMoney();
    }

    return 0;
}

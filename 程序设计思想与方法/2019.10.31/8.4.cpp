#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int main()
{
   int num, guess;
   bool flag = false;
   char choice;

   srand(time(NULL));
   num = rand() % 101;

   cout << "I have a number between 1 and 100." << endl << "Please input your guess:";
   while (!flag)
   {   cin >> guess;
       if (num==guess)
       {   cout << "Excellent! You guessed the number!" << endl << "Would you like to play again (y or n)?  ";
           cin >> choice;
           if (choice=='n') flag=true;
           else if (choice=='y')
           {cout << "I have a number between 1 and 100." << endl << "Please input your guess:";
            num = rand() % 101;
           }
            else {cout << "Error! Exit with error"; flag=true;}
       }

       else if (num<guess) cout << "Too high! try again:";
            else cout << "Too low! try again:";
   }

}

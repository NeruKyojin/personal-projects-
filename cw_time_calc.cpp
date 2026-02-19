#include <iostream>
using namespace std;

int tc; // time choice
int tt; // time transfer
double ttf; // time transfer final

void choice() {
    cout << "1.seconds->hours, 2.seconds->minutes, 3 minutes->hours, 4. hours->seconds: ";
    cin >> tc; 
    cout << "input time: ";
    cin >> tt;
    
    if(tc > 4 || tc < 1) {
        cout << "invalid choice " << endl;
    }
    if(tc == 1) {
        double ttf = tt / 3600;
        cout << "your seconds in hours is " << ttf << " hours" << endl;
    }    
    if(tc == 2) {
        double ttf = tt / 60;
        cout << "your seconds in minutes is " << ttf << " minutes" << endl;
    }           
    if(tc == 3) {
        double ttf = tt / 60;
        cout << "your minutes to hours " << ttf << " hours" << endl; 
    }
    if(tc == 4) {
        double ttf = tt * 3600;
        cout << "your hours in seconds " << ttf << " seconds" << endl;
}}

int main () {
    char restart; // restart is unassigned
    do{
      choice();
      cout << "Y to continue N to end program: " << endl;
      cin >> restart;
    } while(restart == 'Y' || restart == 'y');
    cout << "thank you for using the program: " << endl;

    return 0;
}

/*Convert seconds to hours (time must be entered in seconds) (5 marks)
• Convert seconds to minutes (time must be entered in seconds) (5 marks)
• Convert minutes to hours (time must be entered in minutes) (5 marks)
• Convert hours to seconds (time must be entered in hours) (5 marks)
• Permits you to exit the program (5 marks)*/

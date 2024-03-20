#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
//#include conio.h

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

//User Config
float Pin = 0.9; //0.9
float Iin = 0.3; //0.3
float Din = 0.3; //0.2

float SetPoint = 10000; //100

float Resistance = 0;

//Program Values
float Error;
float Integral;
float DerCache;
float PIDout;
int ErrorChangelessCycles;

int main(int argc, char *argv[]) {
    cout << " ___ ___                          _______ ___ ______   \n";
    cout << "|   Y   .-----.-----.-----.______|   _   |   |   _  \\  \n";
    cout << "|.      |  _  |__ --|__ --|______|.  1   |.  |.  |   \\ \n";
    cout << "|. \\_/  |_____|_____|_____|      |.  ____|.  |.  |    \\ \n";
    cout << "|:  |   |                        |:  |   |:  |:  1    /\n";
    cout << "|::.|:. |                        |::.|   |::.|::.. . / \n";
    cout << "`--- ---'                        `---'   `---`------'\n";
    if (argc != 5) {
        cout << "Usage: PID [P] [I] [D] [Setpoint]\n";
        return -1;
    }
    Pin = atof(argv[1]); //0.9
    Iin = atof(argv[2]); //0.3
    Din = atof(argv[3]); //0.2
    SetPoint = atof(argv[4]); //100
    sleep_for(2.5s);
    while (true) {
        Error = SetPoint - PIDout;
        if (Error == DerCache) {
            ErrorChangelessCycles += 1;
        } else {
            ErrorChangelessCycles = 0;
        }
        if (ErrorChangelessCycles > 1) {
            break;
        }
        Integral += Error;
        PIDout = ((Pin * Error) + (Iin * Integral) + (Din * (DerCache - Error)));
        PIDout -= PIDout * (Resistance/100);
        DerCache = Error;
        cout << "PID: " << PIDout << "     Error: " << Error << "\n";
        sleep_for(0.15s);
    }
    cout << "Stabilized!\nTerminating...\n";
    return 0;
}
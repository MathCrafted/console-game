#include "dice.h"

class Dice {
    public:
        
        //Bunch o' dice
        //wait() is called to add a slight delay so that the random number will change
        static int d20() {

            wait();
            srand(clock() + (CLOCKS_PER_SEC * time(NULL)));
            return (rand() % 20 + 1);

        }

        static int d12() {

            wait();
            srand(clock() + (CLOCKS_PER_SEC * time(NULL)));
            return (rand() % 12 + 1);

        }

        static int d10() {

            wait();
            srand(clock() + (CLOCKS_PER_SEC * time(NULL)));
            return (rand() % 10 + 1);

        }

        static int d8() {

            wait();
            srand(clock() + (CLOCKS_PER_SEC * time(NULL)));
            return (rand() % 8 + 1);

        }

        static int d6() {

            wait();
            srand(clock() + (CLOCKS_PER_SEC * time(NULL)));
            return (rand() % 6 + 1);

        }

        static int d4() {

            wait();
            srand(clock() + (CLOCKS_PER_SEC * time(NULL)));
            return (rand() % 4 + 1);

        }
    
    private:

        //check to see if a number of milliseconds have past
        static void wait(double seconds = 0.001) {

            clock_t startTime = clock();
            clock_t endTime;
            do {
                endTime = clock();
            } while (endTime < startTime + (seconds * CLOCKS_PER_SEC));

        }
        
};
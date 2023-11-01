#include "gameHeader.h"

//"Roll Initiative"
int rollD20() {

    wait(0.001);
    srand(clock() + (CLOCKS_PER_SEC * time(NULL)));
    return (rand() % 20 + 1);

}

//renders the buffer onto the screen
void render(char screenBuffer[LAYER_COUNT][SCREEN_HEIGHT][SCREEN_WIDTH], int & OS) {

    //check for clear command on system
    if (OS == 0) {
        if (!system("cls")) OS = 1;
        else if (!system("clear")) OS = 2;
        else OS = -1;

        //clear the screen
        if (OS == 1) system("cls");
        else if (OS == 2) system("clear");
    }

    //render the frame
    char frame[SCREEN_HEIGHT][SCREEN_WIDTH];

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {

            frame[i][j] = ' ';  //sets the pixel to empty
            for (int layer = 0; layer < LAYER_COUNT; layer++) {

                if (screenBuffer[layer][i][j] != '\t' && screenBuffer[layer][i][j] != '\x00') {  //tabs are a pain. ASCII nulls are right out

                    frame[i][j] = screenBuffer[layer][i][j];
                    break;

                }

            }

        }
    }

    //clear the screen
    if (OS == 1) system("cls");
    else if (OS == 2) system("clear");

    //print the frame
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            
            cout << frame[i][j];
        }
        cout << '\n';
    }

}

//So the array wouldn't copy nicely...
void copyArray(char screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH], const char sprite[SCREEN_HEIGHT][SCREEN_WIDTH], int y, int x) {

    //copies an array onto another array
    for (int i = y; i < SCREEN_HEIGHT; i++) {
        for (int j = x; j < SCREEN_WIDTH; j++) {

            if (sprite[i-y][j-x] != '\x00') screenBuffer[i][j] = sprite[i-y][j-x];

        }
    }

}

//clear the screenBuffer
void clearBuffer(char screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH]) {

    //iterates over an array, filling it with transparent characters
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            screenBuffer[y][x] = '\x00';
        }
    }

}

//A homage to retro RPGs
void openingCutscene(char screenBuffer[LAYER_COUNT][SCREEN_HEIGHT][SCREEN_WIDTH], int &OS) {

    //TODO
    screenBuffer[BORDER_LAYER][4][7] = 'R';
    render(screenBuffer, OS);
    wait (0.96);
    screenBuffer[BORDER_LAYER][4][8] = 'O';
    render(screenBuffer, OS);
    wait (0.96);
    screenBuffer[BORDER_LAYER][4][9] = 'L';
    render(screenBuffer, OS);
    wait (0.96);
    screenBuffer[BORDER_LAYER][4][10] = 'L';
    render(screenBuffer, OS);
    wait (0.45);
    screenBuffer[BORDER_LAYER][6][4] = 'I';
    render(screenBuffer, OS);
    wait (0.32);
    screenBuffer[BORDER_LAYER][6][5] = 'N';
    render(screenBuffer, OS);
    wait (0.32);
    screenBuffer[BORDER_LAYER][6][6] = 'I';
    render(screenBuffer, OS);
    wait (0.32);
    screenBuffer[BORDER_LAYER][6][7] = 'T';
    render(screenBuffer, OS);
    wait (0.32);
    screenBuffer[BORDER_LAYER][6][8] = 'I';
    render(screenBuffer, OS);
    wait (0.32);
    screenBuffer[BORDER_LAYER][6][9] = 'A';
    render(screenBuffer, OS);
    wait (0.32);
    screenBuffer[BORDER_LAYER][6][10] = 'T';
    render(screenBuffer, OS);
    wait (0.32);
    screenBuffer[BORDER_LAYER][6][11] = 'I';
    render(screenBuffer, OS);
    wait (0.32);
    screenBuffer[BORDER_LAYER][6][12] = 'V';
    render(screenBuffer, OS);
    wait (0.32);
    screenBuffer[BORDER_LAYER][6][13] = 'E';
    render(screenBuffer, OS);

    wait(2.7);
    for (int i = 0; i < 5; i++) {
        clearBuffer(screenBuffer[i]);
    }

}

//delay function (for rendering)
void wait(double seconds) {

    clock_t startTime = clock();
    clock_t endTime;
    do {
        endTime = clock();
    } while (endTime < startTime + (seconds * CLOCKS_PER_SEC));

}

//Automated rolling of initiative
void rollInitiative(int initiativeOrder[6], double initiativeArray[7], int dexArray[6]) {

    for (int i = 0; i < 6; i++) {
        initiativeArray[i] = rollD20() + (dexArray[i] - 10) / 2;  //Basically, gets the 5e Dex modifier and adds it to the score
        wait(0.003);
    }
    initiativeArray[7] = 0;

    //Break initiative ties 
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (j == i) continue;
            if (initiativeArray[j] == initiativeArray[i]) {
                int roll1, roll2;
                do {
                    roll1 = rollD20();
                    roll2 = rollD20();
                    if (roll1 > roll2) initiativeArray[j] += 0.1;
                    else if (roll1 < roll2) initiativeArray[i] += 0.1;
                } while (roll1 == roll2);
                j = 0; //Check for matches again
            }
        }
    }

    //sort out initiative order
    double lastValue = INT_MAX;
    for (int i = 0; i < 6; i++) {
        int highestIndex = 7;
        for (int j = 0; j < 6; j++) {
            if (initiativeArray[j] > initiativeArray[highestIndex] && initiativeArray[j] < lastValue) highestIndex = j;
        }
        initiativeOrder[i] = highestIndex;
        lastValue = initiativeArray[highestIndex];
    }

}

//Automated health bar assembly
string healthBar(string name, int health, int maxHealth) {

    string bar;
    int percentHealth = 3 * health / maxHealth;
    if (health > 0) {
        bar = bar + '\xfe';
    } else {
        bar = bar + ' ';
    }
    for (int i = 0; i < 3; i++) {
        if (i < percentHealth) bar = bar + '\xfe';
        else bar = bar + ' ';
    }
    bar = bar + ' ' + name;
    return bar;

}

//Orc attack AI (I guess)
void orcAttack(string attackerName, int healthArray[6], int armorArray[6]) {

    //For balancing purposes, attack the strongest opposing party member
    int strongIndex = 0;
    for (int i = 1; i < 3; i ++) {
        if (healthArray[strongIndex] < healthArray[i]) strongIndex = i;
    }

    //Roll attack - 1d20 + strMod + proficiency (2)
    if (rollD20() + 5 > armorArray[strongIndex]) {
        //Roll damage
        int damage = (rand() % 12 + 1) + 3;
        if (healthArray[strongIndex] - damage <= 0) healthArray[strongIndex] = 0;
        else healthArray[strongIndex] -= damage;
        cout << attackerName << " hit for " << damage << " damage!" << endl;

    } else {
        cout << attackerName << " missed!" << endl;
    }

}

//Magic Missile
void wizardAttack(int healthArray[6]) {

    int thrown = 0;
    while (thrown < 3) {

        int target;
        cout << "Which Orc is the Wizard throwing dart " << (thrown + 1) << " at?\n> ";
        cin >> target;
        if (!(target >= 1 && target <= 3)) {

            cout << "Please enter a number 1-3\n";
            continue;

        }
        int damage = (rand() % 4 + 1) + 1;
        //shift variable target to index notation
        target += 2;
        if (healthArray[target] - damage <= 0) {

            healthArray[target] = 0;
            cout << "Enemy slain!\n";

        } else {
            healthArray[target] -= damage;
        }
        cout << damage << " damage dealt!\n";
        thrown++;
        wait(0.001);

    }

}

//Greatsword is fun to swing
void fighterAttack(int healthArray[6], int armorArray[6]) {

    //Select target
    int targetIndex;
    do {
        cout << "Which Orc is the fighter attacking?\n> ";
        cin >> targetIndex;
        if (targetIndex >= 1 && targetIndex <= 3) {
            break;
        }
        cout << "Please enter a number 1-3\n";
    } while (targetIndex >= 1 && targetIndex <= 3);

    targetIndex += 2;

    //Roll attack - 1d20 + strMod + proficiency (2)
    if (rollD20() + 5 > armorArray[targetIndex]) {
        //Roll damage
        int damage = (rand() % 6 + 1);
        wait(0.001);
        damage +=(rand() % 6 + 1) + 3;
        if (healthArray[targetIndex] - damage <= 0) {

            healthArray[targetIndex] = 0;
            cout << "Enemy slain!\n";
        }
        else {
            healthArray[targetIndex] -= damage;
        }
        cout << "Fighter hit for " << damage << " damage!" << endl;

    } else {
        cout << "Fighter missed!" << endl;
    }

}

//Pesky Rogue
void rogueAttack(int healthArray[6], int armorArray[6]) {

    //Select target
    int targetIndex = 0;
    do {
        cout << "Which Orc is the rogue attacking with his shortsword?\n> ";
        cin >> targetIndex;
        if (targetIndex >= 1 && targetIndex <= 3) {
            break;
        }
        cout << "Please enter a number 1-3\n";
    } while (targetIndex >= 1 && targetIndex <= 3);

    targetIndex += 2;

    //Roll attack - 1d20 + dexMod + proficiency (2)
    if (rollD20() + 6 > armorArray[targetIndex]) {
        //Roll damage
        int damage = (rand() % 6 + 1) + 4;
        if (healthArray[targetIndex] - damage <= 0) {

            healthArray[targetIndex] = 0;
            cout << "Enemy slain!\n";
        }
        else {
            healthArray[targetIndex] -= damage;
        }
        cout << "Rogue hit for " << damage << " damage!" << endl;

    } else {
        cout << "Rogue missed!" << endl;
    }

    wait(0.2);  //A little delay goes a long way...unless someone is trying to grind

    //Select target
    targetIndex = 0;
    do {
        cout << "Which Orc is the rogue attacking with his dagger?\n> ";
        cin >> targetIndex;
        if (targetIndex >= 1 && targetIndex <= 3) {
            break;
        }
        cout << "Please enter a number 1-3\n";
    } while (targetIndex >= 1 && targetIndex <= 3);

    targetIndex += 2;

    //Roll attack - 1d20 + dexMod + proficiency (2)
    if (rollD20() + 6 > armorArray[targetIndex]) {
        //Roll damage
        int damage = (rand() % 4 + 1) + 4;
        if (healthArray[targetIndex] - damage <= 0) {

            healthArray[targetIndex] = 0;
            cout << "Enemy slain!\n";
        }
        else {
            healthArray[targetIndex] -= damage;
        }
        cout << "Rogue hit for " << damage << " damage!" << endl;

    } else {
        cout << "Rogue missed!" << endl;
    }

}
/*
 * Title:   driver.cpp
 * Author:  Joshua Haley
 * Date:    19 October 2023
 * Purpose: To bring joy to anyone using/learning the console
 */
#include "gameHeader.h"

int main() {

    //render init
    char screenBuffer[LAYER_COUNT][SCREEN_HEIGHT][SCREEN_WIDTH];
    int OS = 0;

    //clear (init) the buffer
    for (int i = 0; i < 5; i++) {
        clearBuffer(screenBuffer[i]);
    }

    //init battle
    int turnCounter = 0;
    string names[6] = {"Wizard", "Fighter", "Rogue", "Orc 1", "Orc 2", "Orc 3"};
    int maxHealthArray[6] = {14, 22, 15, 15, 15, 15};
    int healthArray[6] = {14, 22, 15, 15, 15, 15};
    int armorArray[6] = {10, 16, 16, 13, 13, 13};
    int strArray[6] = {7, 17, 8, 16, 16, 16};
    int dexArray[6] = {11, 12, 18, 12, 12, 12};
    int conArray[6] = {14, 16, 13, 16, 16, 16};
    int intArray[6] = {16, 11, 9, 7, 7, 7};
    int wisArray[6] = {11, 10, 11, 11, 11, 11};
    int chaArray[6] = {10, 10, 19, 10, 10, 10};
    
    double initiativeArray[6];
    int initiativeOrder[6];
    rollInitiative(initiativeOrder, initiativeArray, dexArray);

    openingCutscene(screenBuffer, OS);
    
    //Nice flashing SOUL effect
    wait(0.7);
    copyArray(screenBuffer[CHARACTER_LAYER], fighterSprite, 4, 3);
    render(screenBuffer, OS);
    wait(0.26);
    for (int i = 0; i < 3; i++) {
        clearBuffer(screenBuffer[CHARACTER_LAYER]);
        render(screenBuffer, OS);
        wait(0.12);
        copyArray(screenBuffer[CHARACTER_LAYER], fighterSprite, 4, 3);
        render(screenBuffer, OS);
        wait(0.12);
    }
    clearBuffer(screenBuffer[CHARACTER_LAYER]);
    render(screenBuffer, OS);
    wait(0.15);
    copyArray(screenBuffer[BORDER_LAYER], border);

    //Battle loop - ends on death
    //Render, resolve attack for whomever is next in the initiative order
    do {

        //Render contenders (who happen to still be alive)
        clearBuffer(screenBuffer[CHARACTER_LAYER]);
        if (healthArray[0] > 0) copyArray(screenBuffer[CHARACTER_LAYER], wizardSprite1, 1, 4);
        if (healthArray[1] > 0) copyArray(screenBuffer[CHARACTER_LAYER], fighterSprite, 4, 3);
        if (healthArray[2] > 0) copyArray(screenBuffer[CHARACTER_LAYER], rogueSprite, 7, 2);
        if (healthArray[3] > 0) copyArray(screenBuffer[CHARACTER_LAYER], orcSprite, 2, 13);
        if (healthArray[4] > 0) copyArray(screenBuffer[CHARACTER_LAYER], orcSprite, 5, 12);
        if (healthArray[5] > 0) copyArray(screenBuffer[CHARACTER_LAYER], orcSprite, 8, 11);

        render(screenBuffer, OS);

        //Checks if the character in question is still able to fight
        if (!(healthArray[initiativeOrder[turnCounter%6]] > 0)) {
            turnCounter++;
            continue;
        }

        //Print health
        for (int i = 0; i < 6; i++) {
            cout << healthBar(names[i], healthArray[i], maxHealthArray[i]) << '\n';
        }
        cout << '\n';

        //Get turn and get action (if alive)
        if (initiativeOrder[turnCounter%6] >= 3 && initiativeOrder[turnCounter%6] <=5) {
            
            orcAttack(names[initiativeOrder[turnCounter%6]], healthArray, armorArray);
            
        } else if (initiativeOrder[turnCounter%6] == 0) {
            
            //Magic Missile
            wizardAttack(healthArray);

        } else if (initiativeOrder[turnCounter%6] == 1) {

            //Greatsword
            fighterAttack(healthArray, armorArray);

        } else if (initiativeOrder[turnCounter%6] == 2) {

            //Dual wield time
            rogueAttack(healthArray, armorArray);

        }

        //Delay to allow reading of what happened
        wait(3);

        //increment turn counter
        turnCounter++;
    } while (!(healthArray[0]==0 && healthArray[1]==0 && healthArray[2]==0) && !(healthArray[3]==0 && healthArray[4]==0 && healthArray[5]==0));

    //Win (Orcs are all defeated)
    if (healthArray[3]==0 && healthArray[4]==0 && healthArray[5]==0) {

        clearBuffer(screenBuffer[CHARACTER_LAYER]);
        copyArray(screenBuffer[CHARACTER_LAYER], wizardSprite1, 1, 4);
        copyArray(screenBuffer[CHARACTER_LAYER], fighterSprite, 4, 3);
        copyArray(screenBuffer[CHARACTER_LAYER], rogueSprite, 7, 2);
        char winSprite[SCREEN_HEIGHT][SCREEN_WIDTH] = {
            {'Y', 'O', 'U'},
            {'W', 'I', 'N'}
        };
        copyArray(screenBuffer[1], winSprite, 4, 10);
        render(screenBuffer, OS);

    }

    //Loss (Whole party is defeated)
    if (healthArray[0]==0 && healthArray[1]==0 && healthArray[2]==0) {

        clearBuffer(screenBuffer[CHARACTER_LAYER]);
        if (healthArray[3] > 0) copyArray(screenBuffer[CHARACTER_LAYER], orcSprite, 2, 13);
        if (healthArray[4] > 0) copyArray(screenBuffer[CHARACTER_LAYER], orcSprite, 5, 12);
        if (healthArray[5] > 0) copyArray(screenBuffer[CHARACTER_LAYER], orcSprite, 8, 11);
        char lossSprite[SCREEN_HEIGHT][SCREEN_WIDTH] = {
            {'Y', 'O', 'U'},
            {'L', 'O', 'S', 'E'}
        };
        copyArray(screenBuffer[1], lossSprite, 5, 4);
        render(screenBuffer, OS);

    }

    return 0;

}
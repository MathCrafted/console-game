#ifndef GAMEHEADER_H

#define GAMEHEADER_H

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <limits.h>

using namespace std;

//constants
const int LAYER_COUNT = 5;
const int SCREEN_WIDTH = 18;
const int SCREEN_HEIGHT = 11;
const int BORDER_LAYER = 0;
const int CHARACTER_LAYER = 3;

//Function prototypes
//Rolls a D20
int rollD20();

//Renders the output
void render(char screenBuffer[LAYER_COUNT][SCREEN_HEIGHT][SCREEN_WIDTH], int & OS);

//copies an array of characters
void copyArray(char screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH], const char sprite[SCREEN_HEIGHT][SCREEN_WIDTH], int y = 0, int x = 0);

//clears a screen buffer
void clearBuffer(char screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH]);

//opening cutscene
void openingCutscene(char screenBuffer[LAYER_COUNT][SCREEN_HEIGHT][SCREEN_WIDTH], int &OS);

//delay function (for rendering)
void wait(double seconds = 0.001);

//Automated rolling of initiative
void rollInitiative(int initiativeOrder[6], double initiativeArray[6], int dexArray[6]);

//Automated health bar assembly
string healthBar(string name, int health, int maxHealth);

//Orc attack AI (I guess)
void orcAttack(string attackerName, int healthArray[6], int armorArray[6]);

//I love typing new functions *dies*
//Magic Missile
void wizardAttack(int healthArray[6]);

//Fighter used Greatsword. It's super effective
void fighterAttack(int healthArray[6], int armorArray[6]);

//You're feeling like you're going to have a bad time
void rogueAttack(int healthArray[6], int armorArray[6]);

//sprites aka global constant arrays that I don't feel like copy+pasting
//Fancy border, copied to top layer[0]
const char border[SCREEN_HEIGHT][SCREEN_WIDTH] = {
    {'\xc9', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xbb'},
    {'\xba', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xba'},
    {'\xba', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xba'},
    {'\xba', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xba'},
    {'\xba', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xba'},
    {'\xba', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xba'},
    {'\xba', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xba'},
    {'\xba', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xba'},
    {'\xba', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xba'},
    {'\xba', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xba'},
    {'\xc8', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xcd', '\xbc'},
};

const char wizardSprite0[SCREEN_HEIGHT][SCREEN_WIDTH] = {
    {'\x00', '\x95', '\x00'},
    {'\x00', '\xdb', '\x00'}
};  //was '\xb1'

const char wizardSprite1[SCREEN_HEIGHT][SCREEN_WIDTH] = {
    {'\x00', '\x95', '\x00'},
    {'\xd4', '\xdb', '\xcd', '\x92'}
};  //was '\xb1'

const char fighterSprite[SCREEN_HEIGHT][SCREEN_WIDTH] = {
    {'\x00', '\xef', '\xba'},
    {'\x00', '\xdb', '\xb4'}
};  //was '\xb2'

const char rogueSprite[SCREEN_HEIGHT][SCREEN_WIDTH] = {
    {'\x00', 'o', '\xb3'},
    {'\xd5', '\xdb', '\xbe'}
};  //was '\xb0'

const char orcSprite[SCREEN_HEIGHT][SCREEN_WIDTH] = {
    {'\xd8', '\xea', '\x00'},
    {'\xc3', '\xdb', '\x00'}
};  //was '\xb0'

#endif
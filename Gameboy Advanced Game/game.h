#ifndef GAME_H
#define GAME_H

#include "gba.h"

                    /* TODO: */

            // Create any necessary structs //

/*
* For example, for a Snake game, one could be:
*
* typedef struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* } Snake;
*
*
*
*
*
* Example of a struct to hold state machine data:
*
* typedef struct state {
*   int currentState;
*   int nextState;
* } State
*
*/

    struct object {
        int row;
        int col;
        int rd;
        int cd;
        // unsigned short color;
        const u16 *image;
    };

    struct objectstate {
        int size;
        struct object ball;
    } cs, ps; // current state & previous state

    struct character {
        int row;
        int col;
        int rd;
        int cd;
        // unsigned short color;
        unsigned short color;
    };

    struct characterstate {
        int size;
        struct character ball;
    } ccharacter, pcharacter; // current state & previous state



	

// MY CODE STARTS HERE
// void reset(u32 currentButtons, u32 previousButtons);
void startscreen(void);
void endscreen01(void);
void endscreen02(void);
void movingObject(void);
void backToMainInstruction(void);
void Lives(int);
// void movingCharacter(void);
void movingCharacterRight(void);
void movingCharacterLeft(void);
void movingCharacterUP(void);
void movingCharacterDown(void);
int collision(void);
void reset(void);


#endif

/**
 * @brief Header file for global macros, variables, and function prototypes
 * for the tl04 program.
 *
 * DO NOT MODIFY ANYTHING EXCEPT THE OFFSET MACRO
 */

#ifndef TL4_H
#define TL4_H

#define UNUSED_PARAM(x) ((void) x) // This macro is only used for turning off compiler errors initially
#define UNUSED_FUNC(x) ((void) x)  // This macro is only used for turning off compiler errors initially


// CHEKPOINT 1
// You will implement the OFFSET macro, which allows us to index into the
// videoBuffer to modify a certain pixel value
#define OFFSET(row, col, width) ((col) + (width)*(row))  // TODO: FIXME! implement OFFSET

#define VBUF_WIDTH 200 // the width of the videoBuffer
#define VBUF_HEIGHT 150 // the height of the videoBuffer
#define MAX_DIGITS 5 // maximum number of digits allowed in a number passed in as an argument

extern unsigned short videoBuffer[30000]; // array representing the videoBuffer, with size VBUF_WIDTH*VBUF_HEIGHT

int decimal_string_to_int(char *str);
unsigned short ints_to_rgb(int r, int g, int b);
int my_main(int argc, char const *argv[]);

#endif

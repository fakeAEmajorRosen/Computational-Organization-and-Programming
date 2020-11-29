/**
 * @file tl04.c
 * @author Ting-Ying Yu
 * @brief Command-line argument & string parsing logic
 * @date 2020-11-16
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <string.h>
#include <stdio.h>
#include "tl04.h"

//DO NOT MODIFY THIS VARIABLE



//global array representing the video buffer
unsigned short videoBuffer[30000];
int parsing_xy(char const *str);

/**
 * @brief Convert a string containing ASCII digits (in decimal) to an int.
 *
 * Examples:
 *
 * decimal_string_to_int("2110")
 *   => 2110
 *
 * All inputs to this function will be valid decimal strings
 *
 * @param str A null-terminated C string
 * @return int the corresponding decimal value of the passed in decimal str
 */
int decimal_string_to_int(char *str) {
    //TODO: FIX ME! SEE .pdf FOR DETAILS
    int acc = 0;

    char c;
    while ((c = *str++)) {
        acc *= 10;
        if (c >= '0' && c <= '9') {
            acc += c - '0';
        } else {
            return -1; // something went horribly wrong
        }
    }

    return acc;

    //These are just to turn off compiler errors initially
    //Please delete once you have implemented the function
    // UNUSED_PARAM(str);

    // return 0;
}

/**
 * @brief Takes 3 color values corresponding to red, green, and blue and converts them
 * into a single 16 bit rgb color using the GBA color format
 *
 * Examples:
 *
 * ints_to_rgb(10, 0, 15)
 *   => 15370
 *
 * ints_to_rgb(31, 16, 5)
 *   => 5663
 *
 * Note that this function returns an unsigned short!
 * You may assume any input to this function will be a positive number with no more than 5 bits (less than 32)
 *
 * @param r a 5 bit red color value
 * @param g a 5 bit green color value
 * @param b a 5 bit blue color value
 * @return unsigned short the combined 16 bit rgb color value following the GBA color format
 */
unsigned short ints_to_rgb(int r, int g, int b) {
    //TODO: FIX ME! SEE .pdf FOR DETAILS
    unsigned short color = ((r) | (g)<<5 | (b)<<10);

    //These are just to turn off compiler errors initially
    //Please delete once you have implemented the function
    // UNUSED_PARAM(r);
    // UNUSED_PARAM(g);
    // UNUSED_PARAM(b);

    return color;
}

/**
 * @brief Main function, responsible for parsing command line argument and updating
 * the videoBuffer accordingly
 *
 * @param argc argument count
 * @param argv argument vector (it's an array of strings)
 * @return int status code of the program termination
 */
int my_main(int argc, char const *argv[]) {
    //TODO: FIX ME! SEE .pdf FOR DETAILS
    int x, y, r, g, b = 0;
    
    // If I have more time:
    // I will use arrays
    // int x_ind, y_ind, r_ind, g_ind, b_ind;
    // int x_arr[5];
    // int y_arr[5];
    // int r_arr[5];
    // int g_arr[5];
    // int b_arr[5];
    
    for (int i = 1; i <= argc; i++) {
        char const *str = argv[i];
        while (*str) {
            // char const *start = str;
            // char c = *str;
            // int len = 0;
            if ((*str == 'x') || (*str == 'y') || 
                (*str == 'r') || (*str == 'g') || (*str == 'b')) {
                    // while (c >= '0' && c <= '9') {
                    //         len++;
                    //         str++;
                    //         c = *str;
                    // }
                    // *(start + len) = '\0';
                    if (*str == 'x') {
                        x = parsing_xy(str);
                        // x_arr[x_ind] = x;
                        //xind++;
                    } else if (*str == 'y') {
                        y = parsing_xy(str);
                    }else if (*str == 'r') {
                        r = parsing_xy(str);
                    }else if (*str == 'g') {
                        g = parsing_xy(str);
                    }else if (*str == 'b') {
                        b = parsing_xy(str);
                    }
                    
            } else {
                str++;
            }
        }
        if (!((x <= VBUF_WIDTH) && (y <= VBUF_HEIGHT))) {
            return 1;
        }
        if (!((r < 32) && (g < 32) && (b < 32))) {
            return 1;
        }
    }


    // Check if they are in bounds
    if (!((x <= VBUF_WIDTH) && (y <= VBUF_HEIGHT))) {
        return 1;
    }
    if (!((r < 32) && (g < 32) && (b < 32))) {
        return 1;
    }



    return 0; //do not remove
}

int parsing_xy(char const *str) {
    char *parse_x = "00000";
    char *startx = parse_x;
    int len = 0;
    while (*str >= '0' && *str <= '9') {
        *parse_x = *str;
        len++;
        str++;
        parse_x++;
    }
    *(parse_x) = '\0';
    startx = startx + 2;
    
    int x_cor = decimal_string_to_int(startx);
    return x_cor;

}
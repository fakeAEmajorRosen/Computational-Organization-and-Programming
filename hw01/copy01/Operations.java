/**
 * CS 2110 Fall 2020 HW1
 * Part 3 - Coding with bitwise operators
 *
 * @author Ting-Ying Yu
 *
 * Global rules for this file:
 * - All of these functions must be completed in ONE line. That means they
 *   should be of the form "return [...];". No partial credit will be awarded
 *   for any method that isn't completed in one line.
 *
 * - You may not use conditionals.
 * - You may not declare any variables.
 * - You may not use casting.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - You may not use addition or subtraction
 * - You may not use multiplication, division or modulus
 *
 * - Basically, the global rules are you can only use logical (&&, ||) and
 *   bitwise (&, |, ^, >>, <<) operators. all in one line.
 *
 * Method-specific rules for this file:
 * - You may not use bit shifting or the exclusive OR operator (^) in xor.
 *
 * Some notes:
 *
 * All of these functions accept ints as parameters because if you pass in a
 * number (which is of type int by default) into a Method accepting a byte, then
 * the Java compiler will complain even if the number would fit into that type.
 *
 * Now, keep in mind the return value is also an int. Please read the comments
 * about how many significant bits to return and make sure that the other bits
 * are not set or else you will not get any points for that test case. For
 * example, if we ask you to return 6 bits and you return "0xFFFFFFFF", you will
 * lose points.
 *
 * Definitions of types:
 * nibble - 4 bits
 * byte   - 8 bits
 * short  - 16 bits
 * int    - 32 bits
 */
public class Operations
{
    /**
     * Get an 16-bit short from an int.
     *
     * Ints are made of 2 shorts, numbered like so:
     *   |       B1       |      B0        |
     *
     * For a graphical representation of the bits:
     *
     * bit 31                           bit 0
     *    v                               v
     *    1101100000001100 0001111111011001
     *   +----------------+----------------+
     *   |       B1       |       B0       |
     *
     * Examples:
     *     getShort(0x56781234, 0); // => 0x1234
     *     getShort(0x56781234, 1); // => 0x5678
     *
     * Note: Remember, no multiplication allowed!
     *
     * @param num The int to get a short from.
     * @param which Determines which short gets returned - 0 for
     *              least-significant short.
     *
     * @return A short corresponding to the "which" parameter from num.
     */
    int getShort(int num, int which)
    {
        // digits to move: which << 4: which* 2^4
        // move num with the num above
        //

        return ((num >> (which << 4)) & (0xFFFF));
    }

    /**
     * Set a 4-bit nibble in an int.
     *
     * Ints are made of 8 nibbles, numbered like so:
     *   | N7 | N6 | N5 | N4 | N3 | N2 | N1 | N0 |
     *
     * For a graphical representation of the bits:
     *
     * bit 31                                bit 0
     *    v                                     v
     *    1101 1000 0000 1100 0001 1111 1101 1001
     *   +-------------------+-------------------+
     *   | N7 | N6 | N5 | N4 | N3 | N2 | N1 | N0 |
     *
     * Examples:
     *     setNibble(0x56781235, 0x4, 0); // => 0x56781234
     *     setNibble(0x56781134, 0x2, 2); // => 0x56781234
     *
     * Note: Remember, no multiplication allowed!
     *
     * @param num The int that will be modified.
     * @param a_nibble The nibble to insert into the integer.
     * @param which Selects which nibble to modify - 0 for least-significant
     * nibble.
     *
     * @return The modified int.
     */
    int setNibble(int num, int a_nibble, int which)
    {
        return (num & (~(0x000F << (which << 2)))) | (a_nibble << (which << 2));
    }

    /**
     * Pack a short and 2 bytes into an int.
     *
     * The short and 2 bytes should be placed consecutively in the 32-bit int in
     * the order that they appear in the parameters
     *
     * Example:
     *     pack(0x1234, 0x56, 0x78); // => 0x12345678
     *     pack(0xCOFF, 0xEE, 0x10); // => 0xCOFFEE10
     *
     * @param s2 Most significant short (will always be a 16-bit number).
     * @param b1 2nd least significant byte (will always be a 8-bit number).
     * @param b0 Least Significant byte (will always be a 8-bit number).
     *
     * @return a 32-bit value formatted like so: s2b1b0
     */
    int pack(int s2, int b1, int b0)
    {
        return ((s2 << 16) | (b1 << 8)) | b0;
    }

    /**
     * Extract a range of bits from a number.
     *
     * Examples:
     *     bitRange(0x00001234, 0, 4);  // => 0x00000004
     *     bitRange(0x00001234, 4, 8);  // => 0x00000023
     *     bitRange(0x12345678, 0, 28); // => 0x02345678
     *     bitRange(0x55555555, 5, 7);  // => 0x0000002A
     *
     * Note: We will only pass in values 1 to 32 for n.
     *
     * @param num An n-bit 2's complement number.
     * @param s The starting bit to grab
     * @param n The number of bits to return.
     * @return The n-bit number num[s:s+n-1].
     */
    int bitRange(int num, int s, int n)
    {
        // # of ones: (0x1 << ())
        // 11...1: 0xFFFF
        // 111...000n: 0xFFFF << n

        return (num >> s) & (~(0xFFFFFFFF << n));
    }

    /**
     * NOTE: For this method, you may only use &, |, and ~.
     *
     * Perform an exclusive-or on two 32-bit ints.
     *
     * Examples:
     *     xor(0xFF00FF00, 0x00FF00FF); // => 0xFFFFFFFF
     *     xor(0x12345678, 0x87654321); // => 0x95511559
     *
     * @param num1 An int
     * @param num2 Another int
     *
     * @return num1 XOR num2
     */
    int xor(int num1, int num2)
    {
        return (num1 | num2) & (~(num1 & num2));
    }

    /**
     * Return true if the given number is multiple of 2.
     *
     * You may use addition, subtraction, and conditionals in this method.
     *
     * Examples:
     *     multipleOf2(32);   // => true
     *     multipleOf2(13);   // => false
     *
     * Note: Make sure you handle ALL the cases!
     *
     * @param num a 32-bit int. Since this is an int, it is SIGNED!
     * @return true if num is a multiple of 2 else false.
     */

    boolean multipleOf2(int num)
    {
        
        return (num | 0xFFFFFFFE) == 0xFFFFFFFE;
    }

    /**
     * Return true if the given number is multiple of 32.
     *
     * You may use addition, subtraction, and conditionals in this method.
     *
     * Examples:
     *     multipleOf32(256); // => true
     *     multipleOf32(135); // => false
     *
     * Note: Make sure you handle ALL the cases!
     *
     * @param num a 32-bit int. Since this is an int, it is SIGNED!
     * @return true if num is a multiple of 32 else false.
     */

    boolean multipleOf32(int num)
    {
        return (num | 0xFFFFFFE0) == 0xFFFFFFE0;
    }
}

/**
 * CS 2110 Fall 2020 HW1
 * Part 2 - Coding with bases
 *
 * @author Ting-Ying Yu
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may declare exactly one String variable each in intToHexString and
 *   and octalStringToBinaryString.
 */
public class Bases
{
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in
     * will be valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary)
    {
        int intNum = 0;
        for (int i = 0; i < binary.length() ; i++) {
            if (binary.charAt(i) == '1') {
                intNum = intNum + (0x1 << (binary.length() - i - 1));
            }
        }

        return intNum;
    }

    /**
     * Convert a string containing ASCII characters (in octal) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in
     * will be valid octal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: octalStringToInt("46"); // => 38
     */
    public static int octalStringToInt(String octal)
    {
        int intNum = 0;
        int counter = 0;
        for (int i = octal.length() - 1; i >= 0 ; i--) {
            intNum = intNum + ((octal.charAt(i) & ~('0')) << counter);
            counter = counter + ((0x1 << 2) - 1);
        }

        return intNum;
    }

    /**
     * Convert a int into a String containing ASCII characters (in hex).
     *
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters
     * necessary to represent the number that was passed in.
     *
     * Example: intToHexString(166); // => "A6"
     *
     * You may declare one String variable in this method.
     */
    public static String intToHexString(int hex)
    {
        String output = "";
        int modulus = 0;
        int mul = 1;

        while ((mul) != 0) {
            modulus = (hex & ((0x1 << 4) - 1));
            mul = hex >> 4;

            if (modulus >= 10) {
                modulus = modulus + 55;
                output = (char) modulus + output;
            } else {
                output = modulus + output;
            }
            hex = mul;
        }

        return output;
    }

    /**
     * Convert a String containing ASCII characters representing a number in
     * octal into a String containing ASCII characters that represent that same
     * value in binary.
     *
     * The output string should only contain numbers.
     * You do not need to handle negative numbers.
     * The length of all the octal strings passed in will be of size 10.
     * The binary string returned should contain 32 characters.
     *
     * Example: octalStringToBinaryString("0276415470"); // => 00000010111110100001101100111000
     *
     * You may declare one String variable in this method.
     */
    public static String octalStringToBinaryString(String octal)
    {
        String output = "";


        for (int i = octal.length() - 1; i >= 0; i--) {
            // Get the char
            char currentChar = octal.charAt(i);

            // First bit
            // Parse it to an int
            int curr = ((int) currentChar) - 48;

            // Masked it
            int masked = curr & 0x1;

            // Parse it to a char
            char first = (char) (masked + 48);

            output = first + output;

            // Shit it right for one bit
            curr = curr >> 1;

            // Second bit
            // Masked it
            masked = curr & 0x1;

            // Parse it to a char
            char second = (char) (masked + 48);

            output = second + output;

            // Shit it right for one bit
            curr = curr >> 1;

            // Masked it
            masked = curr & 0x1;

            // Parse it to a char
            char third = (char) (masked + 48);

            output = third + output;

        }


        return "00" + output;
    }
}

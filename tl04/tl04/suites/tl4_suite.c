/**
 * @file tl4_suite.c
 * @author David, Dillon
 * @brief Testing Suites to TL4 - Summer2020
 * @date 07-12-2020
 */

// Check Docs
// Tutorial : https://libcheck.github.io/check/doc/check_html/check_3.html
// Check API: https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

// System Headers
#include <string.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/wait.h> // For grabbing return value of system call

// TA Headers
#include "test_utils.h"

/* OFFSET macro tests */

START_TEST(test_macro_offset_1) {
    int result = OFFSET(2, 3, 4);
    int expected_result = 11;
    ck_assert_msg(expected_result == result, "Expected 'OFFSET(2, 3, 4)' to be %d, but code returned %d", expected_result, result);
}
END_TEST

START_TEST(test_macro_offset_2) {
    int result, expected_result;

    result = OFFSET(8, 5 + 3, 6);
    expected_result = 56;
    ck_assert_msg(expected_result == result, "Expected 'OFFSET(8, 5 + 3, 5)' to be %d, but code returned %d", expected_result, result);

    result = OFFSET(8, 5, 6 + 4);
    expected_result = 8 * (6 + 4) + 5;
    ck_assert_msg(expected_result == result, "Expected 'OFFSET(8, 5, 6 + 4)' to be %d, but code returned %d", expected_result, result);

    result = OFFSET(7 + 1, 5 + 2, 6 + 4);
    expected_result = 87;
    ck_assert_msg(expected_result == result, "Expected 'OFFSET(7 + 1, 5 + 3, 6 + 4)' to be %d, but code returned %d", expected_result, result);
}
END_TEST

START_TEST(test_macro_offset_3) {
    int result, expected_result;

    result = 2 * OFFSET(8, 5, 3);
    expected_result = 58;
    ck_assert_msg(expected_result == result, "Expected '2 * OFFSET(8, 5, 3)' to be %d, but code returned %d", expected_result, result);

    result = OFFSET(8, 5, 3) * 2;
    expected_result = 58;
    ck_assert_msg(expected_result == result, "Expected 'OFFSET(8, 5, 3) * 2' to be %d, but code returned %d", expected_result, result);
}
END_TEST

/* decimal_string_to_int tests */

void test_decimal_string_to_int(char *input, int expected) {
    int result = decimal_string_to_int(input);
    ck_assert_msg(result == expected, "Expected 'decimal_string_to_int(\"%s\")' to be %d, but code returned %d", input, expected, result);
}

START_TEST(test_decimal_string_to_int_single_digit) {
    test_decimal_string_to_int("0", 0);
    test_decimal_string_to_int("1", 1);
    test_decimal_string_to_int("5", 5);
    test_decimal_string_to_int("9", 9);
}
END_TEST

START_TEST(test_decimal_string_to_palindrome) {
    test_decimal_string_to_int("11", 11);
    test_decimal_string_to_int("55", 55);
    test_decimal_string_to_int("99", 99);
    test_decimal_string_to_int("121", 121);
    test_decimal_string_to_int("898", 898);
    test_decimal_string_to_int("999", 999);
}
END_TEST

START_TEST(test_decimal_string_to_int_basic) {
    test_decimal_string_to_int("10", 10);
    test_decimal_string_to_int("57", 57);
    test_decimal_string_to_int("100", 100);
    test_decimal_string_to_int("462", 462);
    test_decimal_string_to_int("512", 512);
    test_decimal_string_to_int("2110", 2110);
    test_decimal_string_to_int("12345678", 12345678);
}
END_TEST

START_TEST(test_decimal_string_to_int_leading_zeros) {
    test_decimal_string_to_int("01", 1);
    test_decimal_string_to_int("04", 4);
    test_decimal_string_to_int("000002110194", 2110194);
}
END_TEST

/* ints_to_rgb tests */

void test_ints_to_rgb(int r, int g, int b, unsigned short expected) {
    int result = ints_to_rgb(r, g, b);
    ck_assert_msg(result == expected, "Expected 'ints_to_rgb(%d, %d, %d)' to be %d (hex: 0x%04X), but code returned %d (hex: 0x%04X)", r, g, b, expected, expected, result, result);
}

START_TEST(test_ints_to_rgb_single_bit) {
    test_ints_to_rgb(0x0, 0x0, 0x0, 0x0000);
    test_ints_to_rgb(0x1, 0x0, 0x0, 0x0001);
    test_ints_to_rgb(0x0, 0x1, 0x0, 0x0020);
    test_ints_to_rgb(0x0, 0x0, 0x1, 0x0400);
}
END_TEST

START_TEST(test_ints_to_rgb_single_color) {
    test_ints_to_rgb(0x1A, 0x0,  0x0,  0x001A);
    test_ints_to_rgb(0x0,  0x1A, 0x0,  0x0340);
    test_ints_to_rgb(0x0,  0x0,  0x1A, 0x6800);
}
END_TEST

START_TEST(test_ints_to_rgb_multiple_colors) {
    test_ints_to_rgb(0x01, 0x01, 0x01, 0x0421);
    test_ints_to_rgb(0x1B, 0x0E, 0x10, 0x41DB);
    test_ints_to_rgb(0x02, 0x16, 0x19, 0x66C2);
    test_ints_to_rgb(0x1F, 0x1F, 0x1F, 0x7FFF);
}
END_TEST

START_TEST(test_ints_to_rgb_comprehensive) {
    test_ints_to_rgb(0x0A, 0x15, 0x0A, 0x2AAA);
    test_ints_to_rgb(0x15, 0x0A, 0x15, 0x5555);
    test_ints_to_rgb(0x0D, 0x1B, 0x16, 0x5B6D);
}
END_TEST

/* my_main tests */

void init_videobuffer(unsigned char c) {
    memset(videoBuffer, c, VBUF_WIDTH * VBUF_HEIGHT * sizeof(unsigned short));
}

void run_my_main(int argc, const char *argv[], int return_val, int row, int col, const unsigned short colors[]) {
    int total = 0;
    for (int i = 1; i < argc; i++) {
        total += strlen(argv[i]) + 4;
    }
    total -= 2;
    char *arg_list = malloc(sizeof(char) * (total + 1));
    int j = 0;
    for (int i = 1; i < argc; i++) {
        int len = strlen(argv[i]);
        arg_list[j++] = '"';
        strncpy(&arg_list[j], argv[i], len);
        j += len;
        arg_list[j++] = '"';
        if (i == argc - 1) {
            arg_list[j++] = '\0';
        } else {
            arg_list[j++] = ',';
            arg_list[j++] = ' ';
        }
    }

    int result = my_main(argc, argv);
    ck_assert_msg(result == return_val, "Expected my_main to return %d. argc = %d, argv = {%s}", return_val, argc, arg_list);

    int num_pixels = argc - 2;
    for (int i = 0; i < num_pixels; i++) {
        int target_row = (row * 200 + col + i) / 200;
        int target_col = (row * 200 + col + i) % 200;
        unsigned short color = videoBuffer[target_row * 200 + target_col];
        ck_assert_msg(color == colors[i], "Expected videoBuffer at row %d, column %d to be color %d (hex: 0x%04X), but got color %d (hex: 0x%04X)", target_row, target_col, colors[i], colors[i], color, color);
    }

    free(arg_list);
}

START_TEST(test_my_main_basic) {
    init_videobuffer(0xFF);
    const char *argv[] = {"./tl04", "x:0 y:0", "r:0 g:0 b:0"};
    int argc = sizeof(argv) / sizeof(*argv);
    const unsigned short colors[] = {0x0000};
    run_my_main(argc, argv, 0, 0, 0, colors);
}
END_TEST

START_TEST(test_my_main_many_colors) {
    init_videobuffer(0x00);
    const char *argv[] = {"./tl04", "x:10 y:10", "r:1 g:2 b:3", "r:4 g:5 b:6", "r:7 g:8 b:9"};
    int argc = sizeof(argv) / sizeof(*argv);
    const unsigned short colors[] = {0x0C41, 0x18A4, 0x2507};
    run_my_main(argc, argv, 0, 10, 10, colors);
}
END_TEST

START_TEST(test_my_main_wrap_around) {
    init_videobuffer(0x00);
    const char *argv[] = {"./tl04", "x:198 y:20", "r:10 g:10 b:10", "r:10 g:10 b:10", "r:10 g:10 b:10"};
    int argc = sizeof(argv) / sizeof(*argv);
    const unsigned short colors[] = {0x294A, 0x294A, 0x294A};
    run_my_main(argc, argv, 0, 20, 198, colors);
}
END_TEST

START_TEST(test_my_main_spaces) {
    init_videobuffer(0xFF);
    const char *argv[] = {"./tl04", "   x:0 y:0     ", "   r:0 g:0    b:0  "};
    int argc = sizeof(argv) / sizeof(*argv);
    const unsigned short colors[] = {0x0000};
    run_my_main(argc, argv, 0, 0, 0, colors);
}
END_TEST

START_TEST(test_my_main_no_spaces_coords) {
    init_videobuffer(0xFF);
    const char *argv[] = {"./tl04", "x:0y:0", "r:0 g:0 b:0"};
    int argc = sizeof(argv) / sizeof(*argv);
    const unsigned short colors[] = {0x0000};
    run_my_main(argc, argv, 0, 0, 0, colors);
}
END_TEST

START_TEST(test_my_main_no_spaces_colors) {
    init_videobuffer(0xFF);
    const char *argv[] = {"./tl04", "x:0 y:0", "r:0g:0b:0"};
    int argc = sizeof(argv) / sizeof(*argv);
    const unsigned short colors[] = {0x0000};
    run_my_main(argc, argv, 0, 0, 0, colors);
}
END_TEST

START_TEST(test_my_main_bad_colors) {
    init_videobuffer(0x00);
    const char *argv[] = {"./tl04", "x:100 y:100", "r:32 g:13 b:100"};
    int argc = sizeof(argv) / sizeof(*argv);
    const unsigned short colors[] = {0x0000};
    run_my_main(argc, argv, 1, 0, 0, colors);
}
END_TEST

START_TEST(test_my_main_bad_coords) {
    init_videobuffer(0x00);
    const char *argv[] = {"./tl04", "x:199 y:201", "r:1 g:1 b:1"};
    int argc = sizeof(argv) / sizeof(*argv);
    const unsigned short colors[] = {0x0000};
    run_my_main(argc, argv, 1, 0, 0, colors);
}
END_TEST

Suite *tl4_suite(void)
{
    Suite *s = suite_create("tl4_suite");

    // macro tests
    tcase_hack(s, NULL, NULL, test_macro_offset_1);
    tcase_hack(s, NULL, NULL, test_macro_offset_2);
    tcase_hack(s, NULL, NULL, test_macro_offset_3);

    // decimal_string_to_int tests
    tcase_hack(s, NULL, NULL, test_decimal_string_to_int_single_digit);
    tcase_hack(s, NULL, NULL, test_decimal_string_to_palindrome);
    tcase_hack(s, NULL, NULL, test_decimal_string_to_int_basic);
    tcase_hack(s, NULL, NULL, test_decimal_string_to_int_leading_zeros);

    // ints_to_rgb tests
    tcase_hack(s, NULL, NULL, test_ints_to_rgb_single_bit);
    tcase_hack(s, NULL, NULL, test_ints_to_rgb_single_color);
    tcase_hack(s, NULL, NULL, test_ints_to_rgb_multiple_colors);
    tcase_hack(s, NULL, NULL, test_ints_to_rgb_comprehensive);

    // my_main tests
    tcase_hack(s, NULL, NULL, test_my_main_basic);
    tcase_hack(s, NULL, NULL, test_my_main_many_colors);
    tcase_hack(s, NULL, NULL, test_my_main_wrap_around);
    tcase_hack(s, NULL, NULL, test_my_main_spaces);
    tcase_hack(s, NULL, NULL, test_my_main_no_spaces_coords);
    tcase_hack(s, NULL, NULL, test_my_main_no_spaces_colors);
    tcase_hack(s, NULL, NULL, test_my_main_bad_colors);
    tcase_hack(s, NULL, NULL, test_my_main_bad_coords);

    // Return Testing Suite
    return s;
}

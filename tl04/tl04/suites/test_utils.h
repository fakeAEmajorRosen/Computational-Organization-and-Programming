
#include <stdio.h>
#include <check.h>
#include <stddef.h>
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define RETURN_ERROR_VALUE -100

// Suites
extern Suite *tl4_suite(void);

#define tcase_hack(suite, setup_fixture, teardown_fixture, func)        \
    {                                                                   \
        TCase *tc = tcase_create(STRINGIFY(func));                      \
        tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
        tcase_add_test(tc, func);                                       \
        suite_add_tcase(s, tc);                                         \
    }

/******************************************************************************/
/**************************** tl4 Header Info *********************************/
/******************************************************************************/

// #define UNUSED_PARAM(x) ((void)x) // This macro is only used for turning off compiler errors initially
// #define UNUSED_FUNC(x) ((void)x)  // This macro is only used for turning off compiler errors initially

#define DEBUG_FLAG "-d"

#include "../tl04.h"

void init_neighborhood(void);

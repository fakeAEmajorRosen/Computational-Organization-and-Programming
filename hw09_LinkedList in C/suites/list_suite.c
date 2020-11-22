#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "test_utils.h"

// The number of mallocs in user code until the next one fails, or -1 for
// successful mallocs
int mallocs_until_fail = -1;

static void reset_mallocs_until_fail(void) {
    mallocs_until_fail = -1;
}

static double sample_grades_1[] = { 83.4, 89.5, 92.3 };
static double sample_grades_2[] = { 93.7, 89.4, 58.4, 92.5 };
static User sample_user = { "Reemas", STUDENT, { .student = { 3, sample_grades_1 }}};
static LinkedList *_create_length_1_list(void) {
    LinkedList *shortList = _create_list();
    _push_front(shortList, _create_student_user("Reemas", 3, sample_grades_1));
    return shortList;
}

static User sample_users[] = {
    { "Nrehtous", INSTRUCTOR, { .instructor = { 83485.6 }}},
    { "Reemas", STUDENT, { .student = { 3, sample_grades_1 }}},
    { "Timud", STUDENT, { .student = { 4, sample_grades_2 }}},
    { "Balec", INSTRUCTOR, { .instructor = { 98234.1 }}}
};

static LinkedList *_create_longer_list(void) {
    LinkedList *longerList = _create_list();
    // Push in reverse order
    _push_front(longerList, _create_instructor_user("Balec", 98234.1));
    _push_front(longerList, _create_student_user("Timud", 4, sample_grades_2));
    _push_front(longerList, _create_student_user("Reemas", 3, sample_grades_1));
    _push_front(longerList, _create_instructor_user("Nrehtous", 83485.6));
    return longerList;
}

/******************************************************************************/
/************************** create_list() tests *******************************/
/******************************************************************************/


START_TEST(test_list_create_list_basic) {
    LinkedList *l = create_list();
    ck_assert_msg(l, "create_list should not return NULL");
    ck_assert_msg(!l->size, "create_list should return a list of size 0");
    ck_assert_msg(!l->head, "create_list should return a list with no head");
    free(l);
}
END_TEST


START_TEST(test_list_create_list_malloc_failure) {
    mallocs_until_fail = 0;
    LinkedList *l = create_list();
    ck_assert_msg(!l, "create_list improperly handles malloc failure");
}
END_TEST


/******************************************************************************/
/************************** push_front() tests ********************************/
/******************************************************************************/

START_TEST(test_list_push_front_NULL_list) {
    double grades[] = { 80, 90, 100 };
    UserUnion uu = { .student = { 3, grades } };
    ck_assert_msg(push_front(NULL, "Reemas", STUDENT, uu) != 0, "should not be able to push to a NULL list");
}
END_TEST

START_TEST(test_list_push_front_malloc_failure) {
    LinkedList *l = _create_list();
    UserUnion uu = { .instructor = { 2110 } };
    mallocs_until_fail = 0;
    
    int result = push_front(l, "Mr. Malloc", INSTRUCTOR, uu);
    ck_assert_msg(result == 1, "push_front should return 1 on malloc failure");
    
    _free_list(l);
}
END_TEST

START_TEST(test_list_push_front_NULL_name) {
    LinkedList *l = _create_list();
    
    User *user = _create_instructor_user(NULL, 100000);
    UserUnion uu = { .instructor = { 100000 } };

    ck_assert_msg(push_front(l, NULL, INSTRUCTOR, uu) == 0, "successful push_front should return 0");
    ck_assert_msg(l->size == 1, "push_front should increment size");
    ck_assert_msg(l->head, "push_front should add a node");
    ck_assert_msg(!l->head->next, "you may be adding extra nodes somehow");
    ck_assert_msg(l->head->data, "push_front adds NULL data (double-check your create methods as well!)");
    ck_assert_msg(user_equal(l->head->data, user), "push_front adds wrong data (double-check your create methods as well!)");
    
    _free_user(user);
    _free_list(l);
}
END_TEST

START_TEST(test_list_push_front_empty) {
    LinkedList *l = _create_list();

    char *name = "Tidum";
    double grades[] = { 75, 85, 95, 100 };
    UserUnion uu = { .student = { 4, grades } };
    User *user = _create_student_user(name, 4, grades);
    ck_assert_msg(push_front(l, name, STUDENT, uu) == 0, "push_front should succeed on an empty list");
    ck_assert_msg(l->size == 1, "push_front should increment size");
    ck_assert_msg(l->head, "push_front should should add a node to list");
    ck_assert_msg(!l->head->next, "push_front should only add one node");
    ck_assert_msg(l->head->data, "push_front adds NULL data (double-check your create methods as well!)");
    ck_assert_msg(user_equal(l->head->data, user), "push_front adds wrong data (double-check your create methods as well!)");

    _free_user(user);
    _free_list(l);
}
END_TEST

START_TEST(test_list_push_front_nonempty) {
    LinkedList *l = _create_list();

    // Put some stuff in the struct linked_list
    double grades1[] = { 95.3, 88.7, 91.2 };
    double grades2[] = { 86.6, 95.3, 94.2, 76.4 };
    double grades3[] = { 77.7, 98.3, 92.2 };
    _push_front(l, _create_student_user("Divad", 3, grades1));
    _push_front(l, _create_student_user("Elocin", 4, grades2));
    _push_front(l,  _create_instructor_user("Nrehtous", 85000));
    _push_front(l, _create_student_user("Hsimin", 3, grades3));

    char *name = "Naiviv";
    double grades[] = { 89.3, 85.6, 93.3, 100, 84.5 };
    UserUnion uu = { .student = { 5, grades } };
    User *user = _create_student_user(name, 5, grades);
    ck_assert_msg(push_front(l, name, STUDENT, uu) == 0, "push_front should return 0 on success");
    ck_assert_msg(l->size == 5, "push_front should increment size");
    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert_msg(user_equal(l->head->data, user), "push_front adds wrong data (double-check your create methods as well!)");

    _free_user(user);
    _free_list(l);
}
END_TEST

/******************************************************************************/
/************************** push_back() tests *********************************/
/******************************************************************************/
START_TEST(test_list_push_back_empty) {
    LinkedList *l = _create_list();
    
    char *name = "Ailuj";
    double grades[] = { 80, 90, 100 };
    UserUnion uu = { .student = { 3, grades } };
    User *user = _create_student_user(name, 3, grades);

    ck_assert_msg(push_back(l, name, STUDENT, uu) == 0, "push_back should succeed on an empty list");
    ck_assert(l->head);
    ck_assert_msg(l->head->data, "push_back should add a node with non-NULL data (double-check your create methods as well!)");
    ck_assert_msg(user_equal(l->head->data, user), "push_back should add a node with correct data (double-check your create methods as well!)");
    ck_assert_msg(l->size == 1, "push_back should increment size");
    
    _free_user(user);
    _free_list(l);
}
END_TEST

START_TEST(test_list_push_back_malloc_failure) {
    LinkedList *l = _create_longer_list();
    UserUnion uu = { .instructor = { 0.112 } };
    mallocs_until_fail = 0;
    
    int result = push_back(l, "Callom", INSTRUCTOR, uu);
    ck_assert_msg(result == 1, "push_back should return 1 on malloc failure");
    
    _free_list(l);
}
END_TEST

START_TEST(test_list_push_back_non_empty) {
    LinkedList *l = _create_list();
    ck_assert(l);

    double grades[] = { 89.9, 98.7 };
    User *user1 = _create_student_user("Ahos", 2, grades);
    _push_front(l, user1);

    char *name = "Etnoc";
    UserUnion uu = { .instructor = { 150000 } };
    User *user2 = _create_instructor_user(name, 150000);

    ck_assert_msg(push_back(l, name, INSTRUCTOR, uu) == 0, "push_back should return 0 on success");
    ck_assert_msg(l->head->data, "push_back should not change front of list");
    ck_assert_msg(user_equal(l->head->data, user1), "push_back should not change front of list");
    ck_assert_msg(user_equal(l->head->next->data, user2), "push_back should add a node with correct data (double-check your create methods as well!)");
    ck_assert_msg(l->size == 2, "push_back should increment size");

    _free_user(user2);
    _free_list(l); // will free user1
}
END_TEST

START_TEST(test_list_push_back_NULL) {
    LinkedList *l = _create_list();

    char *name = "Akinrav";
    double grades[] = { 78.4, 96.6, 83.5 };
    UserUnion uu = { .student = { 3, grades } };
    User *user = _create_student_user(NULL, 3, grades);

    ck_assert_msg(push_back(NULL, name, STUDENT, uu) != 0, "push_back shouldn't return 0 with NULL list");
    ck_assert_msg(push_back(l, NULL, STUDENT, uu) == 0, "push_back should return 0 with NULL data and non-NULL list");
    ck_assert_msg(l->size == 1, "push_back should increase size");
    ck_assert_msg(l->head->data, "adding NULL name should add non-NULL User with NULL name (double-check your create methods as well!)");
    ck_assert_msg(user_equal(l->head->data, user), "adding NULL name should add User with NULL name (double-check your create methods as well!)");

    _free_user(user);
    _free_list(l);
}
END_TEST

/******************************************************************************/
/**************************** remove_at_index() tests *************************/
/******************************************************************************/
START_TEST(test_list_remove_at_index_NULL_list) {
    User *dataOut = (User*) 0xDEADBEEFU;
    ck_assert_msg(remove_at_index(NULL, &dataOut, 0) != 0, "remove_at_index shouldn't return 0 with NULL list");
}
END_TEST

START_TEST(test_list_remove_at_index_NULL_dataOut) {
    LinkedList *l = _create_length_1_list();
    ck_assert_msg(remove_at_index(l, NULL, 0) != 0, "remove_at_index shouldn't return 0 with NULL dataOut");
    _free_list(l);
}
END_TEST

START_TEST(test_list_remove_at_index_out_of_bounds) {
    LinkedList *l = _create_length_1_list();
    ck_assert_msg(remove_at_index(l, NULL, -1) != 0, "remove_at_index shouldn't return 0 when out of bounds");
    _free_list(l);
}
END_TEST

START_TEST(test_list_remove_at_index_front) {
    LinkedList *l = _create_longer_list();
    User *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 0);
    ck_assert_msg(dataOut, "remove_at_index does not set the value of dataOut");
    int userCheck = user_equal(dataOut, &sample_users[0]);
    _free_user(dataOut);
    ck_assert_msg(result == 0, "remove_at_index should return 0 when successful");
    ck_assert_msg(userCheck, "remove_at_index sets incorrect value for dataOut");
    ck_assert_int_eq(l->size, 3);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[1]));

    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[2]));

    _free_list(l);
}
END_TEST

START_TEST(test_list_remove_at_index_middle) {
    LinkedList *l = _create_longer_list();
    User *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 1);
    ck_assert_msg(dataOut, "remove_at_index does not set the value of dataOut");
    int userCheck = user_equal(dataOut, &sample_users[1]);
    _free_user(dataOut);
    ck_assert_msg(result == 0, "remove_at_index should return 0 when successful");
    ck_assert_msg(userCheck, "remove_at_index sets incorrect value for dataOut");
    ck_assert_int_eq(l->size, 3);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[0]));

    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[2]));

    ck_assert(l->head->next->next);
    ck_assert(l->head->next->next->data);
    ck_assert(user_equal(l->head->next->next->data, &sample_users[3]));

    ck_assert(!l->head->next->next->next);

    _free_list(l);
}
END_TEST

START_TEST(test_list_remove_at_index_back) {
    LinkedList *l = _create_longer_list();
    User *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 3);
    ck_assert_msg(dataOut, "remove_at_index does not set the value of dataOut");
    int userCheck = user_equal(dataOut, &sample_users[3]);
    _free_user(dataOut);
    ck_assert_msg(result == 0, "remove_at_index should return 0 when successful");
    ck_assert_msg(userCheck, "remove_at_index sets incorrect value for dataOut");
    ck_assert_int_eq(l->size, 3);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[0]));

    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[1]));

    ck_assert(l->head->next->next);
    ck_assert(l->head->next->next->data);
    ck_assert(user_equal(l->head->next->next->data, &sample_users[2]));

    ck_assert(!l->head->next->next->next);

    _free_list(l);
}
END_TEST

START_TEST(test_list_remove_at_index_length_1) {
    LinkedList *l = _create_length_1_list();
    User *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 0);
    ck_assert_msg(dataOut, "remove_at_index does not set the value of dataOut");
    int userCheck = user_equal(dataOut, &sample_user);
    _free_user(dataOut);
    ck_assert_msg(result == 0, "remove_at_index should return 0 when successful");
    ck_assert_msg(userCheck, "remove_at_index sets incorrect value for dataOut");
    ck_assert_int_eq(l->size, 0);
    ck_assert(!l->head);

    _free_list(l);
}
END_TEST

/******************************************************************************/
/************************** add_at_index() tests ***************************************/
/******************************************************************************/
START_TEST(test_list_add_at_index_out_of_bounds) {
    LinkedList *l = _create_list();

    char *name = "Wehttam";
    double grades[] = { 88.9, 92.4 };
    UserUnion uu = { .student = { 2, grades } };

    ck_assert_msg(add_at_index(l, -1, name, STUDENT, uu) != 0, "add_at_index shouldn't return 0 for index < 0");
    _push_front(l, _create_student_user(name, 2, grades));
    ck_assert_msg(add_at_index(l, 2, name, STUDENT, uu) != 0, "add_at_index shouldn't return 0 for index >= size");

    // free_list will free the rest of the data since we manually inserted it at the head
    _free_list(l);

}
END_TEST

START_TEST(test_list_add_at_index_empty_list) {
    LinkedList *l = _create_list();

    char *name1 = "Kcirtap";
    double grades[] = { 96.4, 82.4, 88.8 };
    UserUnion uu1 = { .student = { 3, grades } };
    User *user1 = _create_student_user(name1, 3, grades);

    char *name2 = "Tsugua";
    UserUnion uu2 = { .instructor = { 125000 } };

    ck_assert(add_at_index(l, 0, name1, STUDENT, uu1) == 0);
    ck_assert_int_eq(l->size, 1);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, user1));

    ck_assert_msg(add_at_index(l, 2, name2, INSTRUCTOR, uu2) != 0, "add_at_index shouldn't return 0 for index >= size");
    ck_assert_msg(add_at_index(l, 1, name2, INSTRUCTOR, uu2) == 0, "add_at_index should return 0 when successful");

    ck_assert_int_eq(l->size, 2);

    _free_user(user1);
    _free_list(l);
}
END_TEST

START_TEST(test_list_add_at_index_non_empty_list) {
    LinkedList *l = _create_longer_list();

    char *name = "Ellebasi";
    double grades[] = { 87.4, 93.2, 78.6, 90.0 };
    UserUnion uu = { .student = { 4, grades } };
    User *user = _create_student_user(name, 4, grades);

    ck_assert_msg(add_at_index(l, 1, name, STUDENT, uu) == 0, "add_at_index should return 0 when successful");

    ck_assert(l->head);
    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, user));

    ck_assert_int_eq(l->size, 5);

    _free_user(user);
    _free_list(l);
}
END_TEST

START_TEST(test_list_add_at_index_NULL) {
    LinkedList *l = _create_list();
    
    double grades[] = { 77.7, 88.8, 99.9 };
    UserUnion uu = { .student = { 3, grades } };
    User *user = _create_student_user(NULL, 3, grades);

    ck_assert_msg(add_at_index(NULL, 0, NULL, STUDENT, uu) != 0, "add_at_index shouldn't return 0 for NULL list");
    ck_assert_msg(add_at_index(NULL, 0, "Yeroc", STUDENT, uu) != 0, "add_at_index shouldn't return 0 for NULL list");

    ck_assert_msg(add_at_index(l, 0, NULL, STUDENT, uu) == 0, "add_at_index shouldn't fail with NULL name");
    ck_assert_int_eq(l->size, 1);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, user));

    _free_user(user);
    _free_list(l);
}
END_TEST

/******************************************************************************/
/*************************** pop_front() tests ********************************/
/******************************************************************************/
START_TEST(test_list_pop_front_NULL_list) {
    User *dataOut = (User*) 0xDEADBEEFU;
    ck_assert_msg(pop_front(NULL, &dataOut) != 0, "pop_front shouldn't return 0 with NULL list");
}
END_TEST

START_TEST(test_list_pop_front_NULL_dataOut) {
    LinkedList *l = _create_list();
    ck_assert_msg(pop_front(l, NULL) != 0, "pop_front shouldn't return 0 with NULL dataOut");
    _free_list(l);
}
END_TEST

START_TEST(test_list_pop_front_empty) {
    LinkedList *l = _create_list();
    User *dataOut = (User*) 0xDEADBEEFU;
    ck_assert_msg(pop_front(l, &dataOut) != 0, "pop_front shouldn't return 0 when called with empty list");
    _free_list(l);
}
END_TEST

START_TEST(test_list_pop_front_nonempty) {
    LinkedList *l = _create_length_1_list();
    User *user = NULL;
    int result = pop_front(l, &user);
    ck_assert_msg(user, "pop_front should set dataOut on success");
    int userCheck = user_equal(user, &sample_user);
    _free_user(user);
    ck_assert_msg(result == 0, "pop_front should return 0 on success");
    ck_assert_msg(userCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 0);

    _free_list(l);
}
END_TEST

START_TEST(test_list_pop_front_longer_list) {
    LinkedList *l = _create_longer_list();
    User *data = NULL;
    int result = pop_front(l, &data);
    ck_assert_msg(data, "pop_front should set dataOut on success");
    int userCheck = user_equal(data, &sample_users[0]);
    _free_user(data);
    ck_assert_msg(result == 0, "pop_front should return 0 on success");
    ck_assert_msg(userCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 3);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert_msg(user_equal(l->head->data, &sample_users[1]));

    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert_msg(user_equal(l->head->next->data, &sample_users[2]));

    ck_assert(l->head->next->next);
    ck_assert(l->head->next->next->data);
    ck_assert_msg(user_equal(l->head->next->next->data, &sample_users[3]));

    ck_assert(!l->head->next->next->next);

    result = pop_front(l, &data);
    ck_assert(data);
    userCheck = user_equal(data, &sample_users[1]);
    _free_user(data);

    ck_assert_msg(result == 0, "pop_front should return 0 on success");
    ck_assert_msg(userCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 2);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[2]));

    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[3]));

    ck_assert(!l->head->next->next);

    _free_list(l);
}
END_TEST

/******************************************************************************/
/**************************** pop_back() tests ********************************/
/******************************************************************************/
START_TEST(test_list_pop_back_NULL_list) {
    User *dataOut = (User*) 0xDEADBEEFU;
    ck_assert_msg(pop_back(NULL, &dataOut) != 0, "pop_back shouldn't return 0 with NULL list");
}
END_TEST

START_TEST(test_list_pop_back_NULL_dataOut) {
    LinkedList *l = _create_list();
    ck_assert_msg(pop_back(l, NULL) != 0, "pop_back shouldn't return 0 with NULL dataOut");
    _free_list(l);
}
END_TEST

START_TEST(test_list_pop_back_empty) {
    LinkedList *l = _create_list();
    User *dataOut = (User*) 0xDEADBEEFU;
    ck_assert_msg(pop_back(l, &dataOut) != 0, "pop_back shouldn't return 0 when called with empty list");
    _free_list(l);
}
END_TEST

START_TEST(test_list_pop_back_nonempty) {
    LinkedList *l = _create_length_1_list();
    User *user = NULL;
    int result = pop_back(l, &user);
    ck_assert_msg(user, "pop_back should set dataOut on success");

    int userCheck = user_equal(user, &sample_user);
    _free_user(user);

    ck_assert_msg(result == 0, "pop_back should return 0 on success");
    ck_assert_msg(userCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 0);

    _free_list(l);
}
END_TEST

START_TEST(test_list_pop_back_longer_list) {
    LinkedList *l = _create_longer_list();
    User *data = NULL;
    int result = pop_back(l, &data);
    ck_assert(data);

    int userCheck = user_equal(data, &sample_users[3]);
    _free_user(data);

    ck_assert_msg(result == 0, "pop_back should return 0 on success");
    ck_assert_msg(userCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 3);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[0]));
    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[1]));
    ck_assert(l->head->next->next);
    ck_assert(l->head->next->next->data);
    ck_assert(user_equal(l->head->next->next->data, &sample_users[2]));

    ck_assert(!l->head->next->next->next);

    result = pop_back(l, &data);
    userCheck = user_equal(data, &sample_users[2]);
    _free_user(data);

    ck_assert_msg(result == 0, "pop_back should return 0 on success");
    ck_assert_msg(userCheck, "removed node has incorrect value");
    ck_assert_int_eq(l->size, 2);

    ck_assert(l->head);
    ck_assert(l->head->data);
    ck_assert(user_equal(l->head->data, &sample_users[0]));

    ck_assert(l->head->next);
    ck_assert(l->head->next->data);
    ck_assert(user_equal(l->head->next->data, &sample_users[1]));

    ck_assert(!l->head->next->next);

    _free_list(l);
}
END_TEST

/******************************************************************************/
/******************************* get() tests **********************************/
/******************************************************************************/
// helper method for get() tests
void checkLongerListUnchanged(LinkedList *l, char *msg) {
    ck_assert_msg(user_equal(l->head->data, &sample_users[0]), msg);
    ck_assert_msg(user_equal(l->head->next->data, &sample_users[1]), msg);
    ck_assert_msg(user_equal(l->head->next->next->data, &sample_users[2]), msg);
    ck_assert_msg(user_equal(l->head->next->next->next->data, &sample_users[3]), msg);
    ck_assert_msg(!l->head->next->next->next->next, msg);
}

START_TEST(test_list_get_NULL_list) {
    User *u = (User*) 0xDEADBEEFU;
    ck_assert_msg(get(NULL, 0, &u) != 0, "get shouldn't return 0 when called with NULL list");
}
END_TEST

START_TEST(test_list_get_NULL_dataOut) {
    LinkedList *l = _create_longer_list();
    ck_assert_msg(get(l, 0, NULL) != 0, "get shouldn't return 0 when called with NULL dataOut");
    checkLongerListUnchanged(l, "list was changed by get method");
    _free_list(l);
}
END_TEST

START_TEST(test_list_get_negative_index) {
    LinkedList *l = _create_longer_list();
    User *u = (User*) 0xDEADBEEFU;
    ck_assert_msg(get(l, -1, &u) != 0, "get shouldn't return 0 when called with index < 0");
    checkLongerListUnchanged(l, "list was changed by get method");
    _free_list(l);
}
END_TEST

START_TEST(test_list_get_front) {
    LinkedList *l = _create_longer_list();
    User *u = (User*) 0xDEADBEEFU;
    ck_assert_msg(get(l, 0, &u) == 0, "get should return 0 on success");
    ck_assert_msg(user_equal(u, &sample_users[0]), "get assigns incorrect result to dataOut");
    checkLongerListUnchanged(l, "list was changed by get method");
    _free_list(l);
}
END_TEST

START_TEST(test_list_get_middle) {
    LinkedList *l = _create_longer_list();
    User *u = (User*) 0xDEADBEEFU;
    ck_assert_msg(get(l, 1, &u) == 0, "get should return 0 on success");
    ck_assert_msg(user_equal(u, &sample_users[1]), "get assigns incorrect result to dataOut");
    checkLongerListUnchanged(l, "list was changed by get method");
    _free_list(l);
}
END_TEST

START_TEST(test_list_get_back) {
    LinkedList *l = _create_longer_list();
    User *u = (User*) 0xDEADBEEFU;
    ck_assert_msg(get(l, 2, &u) == 0, "get should return 0 on success");
    ck_assert_msg(user_equal(u, &sample_users[2]), "get assigns incorrect result to dataOut");
    checkLongerListUnchanged(l, "list was changed by get method");
    _free_list(l);
}
END_TEST

START_TEST(test_list_get_out_of_bounds_index) {
    LinkedList *l = _create_longer_list();
    User *u = (User*) 0xDEADBEEFU;
    ck_assert_msg(get(l, 4, &u) != 0, "get shouldn't return 0 when called with index >= size");
    checkLongerListUnchanged(l, "list was changed by get method");
    _free_list(l);
}
END_TEST

/******************************************************************************/
/**************************** contains() tests ********************************/
/******************************************************************************/

START_TEST(test_list_contains_NULL_list) {
    double grades[] = { 80.8, 90.9, 70.7 };
    User *user = _create_student_user("Draheraseman", 3, grades);

    User *dataOut = (User*) 0xDEADBEEFU;
    int result = contains(NULL, user, &dataOut);

    _free_user(user);
    ck_assert_msg(!result, "contains should return 0 (FALSE) when called with NULL list");
}
END_TEST

START_TEST(test_list_contains_NULL_dataOut) {
    LinkedList *l = _create_longer_list();

    User *user = _create_instructor_user("Dr. LC-3, Human-Cyborg Relations", 10000000);

    int result = contains(l, user, NULL);

    _free_user(user);
    ck_assert_msg(!result, "contains should return 0 (FALSE) when called with NULL dataOut");
    checkLongerListUnchanged(l, "list was changed by contains method");
    
    _free_list(l);
}
END_TEST

START_TEST(test_list_contains_empty) {
    LinkedList *l = _create_list();

    User *user = _create_instructor_user("Dr. Seuss", 200000);

    User *dataOut = (User*) 0xDEADBEEFU;
    int result = contains(l, user, &dataOut);

    _free_user(user);
    ck_assert_msg(!result, "contains should return 0 (FALSE) when data not found");
    ck_assert_msg(!dataOut, "contains should set dataOut=NULL when data not found");

    _free_list(l);
}
END_TEST

START_TEST(test_list_contains_not_contained) {
    LinkedList *l = _create_longer_list();

    double grades[] = { 100, 100, 100, 100, 100, 100, 100, 100 };
    User *user = _create_student_user("Mr. Excellent Student", 8, grades);

    User *dataOut = (User*) 0xDEADBEEFU;
    int result = contains(l, user, &dataOut);

    _free_user(user);
    ck_assert_msg(!result, "contains should return 0 (FALSE) when data not found");
    ck_assert_msg(!dataOut, "contains should set dataOut=NULL when data not found");
    checkLongerListUnchanged(l, "list was changed by contains method");

    _free_list(l);
}
END_TEST

START_TEST(test_list_contains_NULL_name) {
    LinkedList *l = _create_longer_list();

    double grades[] = { 91.9, 71.4, 82.6, 82.7 };
    User *user = _create_student_user(NULL, 4, grades);

    _push_front(l, _create_student_user(NULL, 4, grades));

    User *dataOut = (User*) 0xDEADBEEFU;
    int result = contains(l, user, &dataOut);

    ck_assert_msg(result, "contains should return 1 (TRUE) when data is found");
    ck_assert_msg(dataOut != user, "contains should set dataOut to the value in the list, not the one passed in");
    ck_assert_msg(user_equal(dataOut, user), "contains should set dataOut to the value in the list that matches the value passed in");

    dataOut = _pop_front(l);
    _free_user(dataOut);
    _free_user(user);

    checkLongerListUnchanged(l, "list was changed by contains method");
    _free_list(l);
}
END_TEST

START_TEST(test_list_contains_is_contained) {
    LinkedList *l = _create_longer_list();

    User *dataOut = (User*) 0xDEADBEEFU;
    int result = contains(l, &sample_users[1], &dataOut);

    ck_assert_msg(result, "contains should return 1 (TRUE) when data is found");
    ck_assert_msg(dataOut != &sample_users[1], "contains should set dataOut to the value in the list, not the one passed in");
    ck_assert_msg(user_equal(dataOut, &sample_users[1]), "contains should set dataOut to the value in the list that matches the value passed in");

    checkLongerListUnchanged(l, "list was changed by contains method");
    _free_list(l);
}
END_TEST

/******************************************************************************/
/************************** empty_list() tests ********************************/
/******************************************************************************/

/* NOTE: passing these tests does not mean that there are no memory leaks!
This is an easy method to accidentally cause memory leaks on, so be sure to run Valgrind! */

START_TEST(test_list_empty_list_NULL_list) {
    // Success if there is no error
    empty_list(NULL);
}
END_TEST

START_TEST(test_list_empty_list_empty) {
    LinkedList *l = _create_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
    ck_assert_msg(!l->head, "head should point to NULL after empty_list");
    _free_list(l);
}
END_TEST

START_TEST(test_list_empty_list_length_1) {
    LinkedList *l = _create_length_1_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
    ck_assert_msg(!l->head, "head should point to NULL after empty_list");
    _free_list(l);
}
END_TEST

START_TEST(test_list_empty_list_longer_list) {
    LinkedList *l = _create_longer_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
    ck_assert_msg(!l->head, "head should point to NULL after empty_list");
    _free_list(l);
}
END_TEST

/******************************************************************************/
/********************** num_passing_all_classes() tests ***********************/
/******************************************************************************/

START_TEST(test_num_passing_all_classes_empty_NULL) {
    LinkedList *l = _create_list();
    int dataOut = 42; // initialize it to a value we don't expect it to return
    int result = num_passing_all_classes(l, &dataOut);
    ck_assert_int_eq(l->size, 0);

    ck_assert_msg(result == 1, "num_passing_all_classes should return 1 for empty list");
    ck_assert_msg(dataOut == -1, "num_passing_all_classes should store -1 in dataOut for empty list");

    dataOut = 42;
    result = num_passing_all_classes(NULL, &dataOut);
    ck_assert_int_eq(l->size, 0);
    ck_assert_msg(result == 1, "num_passing_all_classes should return 1 for NULL list");
    ck_assert_msg(dataOut == -1, "num_passing_all_classes should store -1 in dataOut for NULL list");

    _free_list(l);
}
END_TEST

START_TEST(test_num_passing_all_classes_length_1) {
    LinkedList *l = _create_length_1_list();
    int dataOut = -1;
    int result = num_passing_all_classes(l, &dataOut);

    ck_assert_int_eq(l->size, 1);
    ck_assert(l->head);
    ck_assert(user_equal(l->head->data, &sample_user));
    ck_assert(!l->head->next);

    ck_assert_msg(result == 0, "num_passing_all_classes should return 0 on success");
    ck_assert_msg(dataOut == 1, "num_passing_all_classes setting incorrect dataOut value");

    _free_list(l);
}
END_TEST

START_TEST(test_num_passing_all_classes_longer_list) {
    LinkedList *l = _create_longer_list();
    int dataOut = -1;
    int result = num_passing_all_classes(l, &dataOut);

    checkLongerListUnchanged(l, "list was changed by num_passing_all_classes method");

    ck_assert_msg(result == 0, "num_passing_all_classes should return 0 on success");
    ck_assert_msg(dataOut == 1, "num_passing_all_classes setting incorrect dataOut value");

    _free_list(l);
}
END_TEST

START_TEST(test_num_passing_all_classes_longer_list_2) {
    LinkedList *l = _create_longer_list();
    double grades1[] = { 60.0, 87.3, 59.9 };
    double grades2[] = { 60.0, 70.0 };
    double grades3[] = { 98.4, 89.9, 107.6 };
    _push_front(l, _create_student_user("Gnissap", 3, grades1));
    _push_front(l, _create_student_user("Gnissapton", 2, grades2));
    _push_front(l, _create_student_user("Tnellecxe", 3, grades3));

    int dataOut = -1;
    int result = num_passing_all_classes(l, &dataOut);

    ck_assert_int_eq(l->size, 7);

    ck_assert_msg(result == 0, "num_passing_all_classes should return 0 on success");
    ck_assert_msg(dataOut == 3, "num_passing_all_classes setting incorrect dataOut value");

    _free_list(l);
}
END_TEST

START_TEST(test_num_passing_all_classes_instructors_only) {
    LinkedList *l = create_list();
    _push_front(l, _create_instructor_user("Nrehtous", 80000));
    _push_front(l, _create_instructor_user("Balec", 90000));
    _push_front(l, _create_instructor_user("Dr. Mario", 1530));
    
    int dataOut = -1;
    int result = num_passing_all_classes(l, &dataOut);

    ck_assert_int_eq(l->size, 3);
    
    ck_assert_msg(result == 0, "num_passing_all_classes should return 0 on success");
    ck_assert_msg(dataOut == 0, "num_passing_all_classes setting incorrect dataOut value");

    _free_list(l);
}
END_TEST

/******************************************************************************/
/************************* get_average_salary() tests *************************/
/******************************************************************************/
START_TEST(test_get_average_salary_empty_NULL_list) {
    LinkedList *l = _create_list();

    double dataOut = 42; // initialize it to a value we don't expect it to return
    int result = get_average_salary(l, &dataOut);
    ck_assert_int_eq(l->size, 0);
    ck_assert_msg(result == 1, "get_average_salary should return 1 for empty list");
    ck_assert_msg(dataOut == -1, "get_average_salary should store -1 in dataOut for empty list");

    dataOut = 42;
    result = get_average_salary(NULL, &dataOut);
    ck_assert_int_eq(l->size, 0);
    ck_assert_msg(result == 1, "get_average_salary should return 1 for NULL list");
    ck_assert_msg(dataOut == -1, "get_average_salary should store -1 in dataOut for NULL list");

    _free_list(l);
}
END_TEST

START_TEST(test_get_average_salary_length_1) {
    LinkedList *l = _create_list();
    _push_front(l, _create_instructor_user("Dr. 10000000000000.01", 8192.25));

    double dataOut = 42;
    int result = get_average_salary(l, &dataOut);

    ck_assert_int_eq(l->size, 1);
    ck_assert(l->head);
    ck_assert(!l->head->next);

    ck_assert_msg(result == 0, "get_average_salary should return 0 on success");
    ck_assert_msg(dataOut - 8192.25 < 10e-5, "get_average_salary setting incorrect dataOut value");

    _free_list(l);
}
END_TEST

START_TEST(test_get_average_salary_longer_list) {
    LinkedList *l = _create_longer_list();
    double dataOut = 42;
    int result = get_average_salary(l, &dataOut);

    checkLongerListUnchanged(l, "list was changed by get_average_salary method");

    ck_assert_msg(result == 0, "get_average_salary should return 0 on success");
    ck_assert_msg(dataOut - 90859.85 < 10e-5, "get_average_salary setting incorrect dataOut value");

    _free_list(l);
}
END_TEST

START_TEST(test_get_average_salary_students_only) {
    LinkedList *l = create_list();
    double grades[] = { 89.3, 85.6, 93.3, 100, 84.5 };
    _push_front(l, _create_student_user("Naiviv", 5, grades));
    _push_front(l, _create_student_user("Timud", 4, sample_grades_2));
    _push_front(l, _create_student_user("Reemas", 3, sample_grades_1));

    double dataOut = -1;
    int result = get_average_salary(l, &dataOut);

    ck_assert_int_eq(l->size, 3);
    
    ck_assert_msg(result == 0, "get_average_salary should return 0 on success");
    ck_assert_msg(dataOut == 0, "get_average_salary setting incorrect dataOut value");

    _free_list(l);
}
END_TEST


Suite *list_suite(void) {
    Suite *s = suite_create("struct linked_list");

    // create_list() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_create_list_basic);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_create_list_malloc_failure);

    // push_front() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_front_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_front_malloc_failure);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_front_NULL_name);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_front_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_front_nonempty);


    // push_back() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_back_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_back_malloc_failure);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_back_non_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_push_back_NULL);

    // remove_at_index() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_out_of_bounds);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_front);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_middle);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_back);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_remove_at_index_length_1);

    // pop_front() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_front_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_front_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_front_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_front_nonempty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_front_longer_list);

    // pop_back() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_back_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_back_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_back_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_back_nonempty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_pop_back_longer_list);

    // add_at_index() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_add_at_index_out_of_bounds);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_add_at_index_empty_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_add_at_index_non_empty_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_add_at_index_NULL);

    // get() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_negative_index);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_front);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_middle);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_back);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_get_out_of_bounds_index);

    // contains() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_contains_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_contains_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_contains_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_contains_not_contained);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_contains_NULL_name);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_contains_is_contained);

    // empty_list() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_empty_list_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_empty_list_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_empty_list_length_1);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_empty_list_longer_list);
    
    // num_passing_all_classes() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_num_passing_all_classes_empty_NULL);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_num_passing_all_classes_length_1);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_num_passing_all_classes_longer_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_num_passing_all_classes_longer_list_2);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_num_passing_all_classes_instructors_only);

    // get_average_salary() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_get_average_salary_empty_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_get_average_salary_length_1);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_get_average_salary_longer_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_get_average_salary_students_only);
  
    return s;
}

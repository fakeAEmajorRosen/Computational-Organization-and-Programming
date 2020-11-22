/**
 * CS 2110 - Summer 2020 - Homework #9
 *
 * @author Ting-Ying Yu
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return 1 if
 * the function returns a int).
 */

// Do not add ANY additional includes!!!
#include "list.h"

/* You should NOT have any global variables. */

/* The create_node function is static because this is the only file that should
   have knowledge about the nodes backing the linked List. */
static User *create_user(char *name, UserType type, UserUnion data);
static int create_student(int num_classes, double *grades, Student *dataOut); //completed for you
static int create_instructor(double salary, Instructor *dataOut); //completed for you
static Node *create_node(char *name, UserType type, UserUnion data);
static int user_equal(const User *user1, const User *user2);

/** create_user
 *
 * Helper function that creates a User by allocating memory for it on the heap
 * and initializing with the passed in data. You MUST create a deep copy of
 * the data union. This means malloc'ing space for copies of each field in
 * UserUnion data.
 *
 * If malloc returns NULL, you should return NULL as well.
 *
 * If creating a student/instructor fails, you must free everything you've allocated
 * and return NULL
 *
 * You should call create_student() or create_instructor() in this function
 * to create a deep copy of the UserUnion depending on the UserType
 *
 * (hint: you cannot just assign UserUnion data to the data part of user)
 *
 * @param the fields of the User struct
 * @return a User, return NULL if malloc fails
 */
static User *create_user(char *name, UserType type, UserUnion data)
{
    // UNUSED(name);
    // UNUSED(type);
    // UNUSED(data);
    // UNUSED(create_student);
    // UNUSED(create_instructor);

    // Allocate space for user:
    User *user_ptr = (User *) malloc(sizeof(User));
    if (user_ptr == NULL) {
        return NULL;
    }
    char *name_ptr = NULL;

    // Allocate space for name in user:
    if (name == NULL) {
        user_ptr->name = NULL;
    } else {
        name_ptr = (char *) malloc(sizeof(char) * (strlen(name) + 1));
        if (name_ptr == NULL) {
            // free(name_ptr);
            free(user_ptr);
            return NULL;
        } else {
            strcpy(name_ptr, name);
        }
        name_ptr[strlen(name)] = '\0';
        // Set the name in the user:
        user_ptr -> name = name_ptr;
    }
    
    // Set the UserType in user:
    user_ptr -> type = type;

    // Allocate space for UserUnion in data:
    // UserUnion *data_ptr = (UserUnion *) malloc(sizeof(UserUnion));
    // if (data_ptr == NULL) {
    //     free(user_ptr);
    //     free(name_ptr);
    //     return NULL;
    // }

    UserUnion *data_ptr = &user_ptr->data;

    // Set the data (UserUnion):
    // If creating a student/instructor fails, you must free everything you've allocated and return NULL
    
    if (type == STUDENT) {
        Student *student_ptr = &(data_ptr->student);

        if ((create_student(data.student.num_classes, data.student.grades, student_ptr))) {
            //free(data_ptr);
            free(user_ptr);
            if (name_ptr != NULL) {
                free(name_ptr);
            }
            
            return NULL;
        }

        // data_ptr -> student = *student_ptr;

    } else if (type == INSTRUCTOR) {
        Instructor *instructor_ptr = &(data_ptr->instructor);

        if ((create_instructor(data.instructor.salary, instructor_ptr))) {
            //free(data_ptr);
            free(user_ptr);
            if (name_ptr != NULL) {
                free(name_ptr);
            }
            return NULL;
        }

        // data_ptr -> instructor = *instructor_ptr;

    }

    // user_ptr -> data = *data_ptr;
    // free(data_ptr);

    return user_ptr;
    // return NULL;
}

/** create_student
 *
 * Helper function that creates a Student and allocates memory for the grade array on the heap.
 *
 * THIS FUNCTION IS IMPLEMENTED FOR YOU
 *
 * @param the fields of the Student struct, and an existing pointer to a student
 * @return 1 if malloc fails, 0 otherwise.
 */
static int create_student(int num_classes, double *grades, Student *dataOut)
{
    /***do not change anything in this function***/
    dataOut->num_classes = num_classes;
    dataOut->grades = NULL;
    if (grades != NULL) {
        if (!(dataOut->grades = (double *) malloc(sizeof(double)*num_classes))) return 1;
        memcpy(dataOut->grades, grades, sizeof(double)*num_classes);
    }
    return 0;
}

/** create_instructor
 *
 * Helper function that creates an Instructor.
 *
 * THIS FUNCTION IS IMPLEMENTED FOR YOU
 *
 * @param the fields of the Instructor struct, and an existing pointer to an instructor
 * @return 1 if malloc fails, 0 otherwise. (this function should always return 0 since
 * you won't need to malloc anything)
 */
static int create_instructor(double salary, Instructor *dataOut)
{
    /***do not edit anything in this function***/
    dataOut->salary = salary; //yes that's all this function does
    return 0;
}

/** create_node
  *
  * Helper function that creates a Node by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * Remember that you need to malloc both the node itself and the User
  * that's contained in the struct. You might want to call create_user instead of
  * malloc'ing again.
  *
  * If malloc returns NULL for either of them, you should return NULL to indicate failure.
  * In the case that you successfully malloc one of them but fail to malloc the other one,
  * you should free the one you successfully malloc'd.
  *
  * @param the fields of the User struct
  * @return a Node
  */
static Node* create_node(char *name, UserType type, UserUnion data)
{
    // UNUSED(name);
    // UNUSED(type);
    // UNUSED(data);
    // UNUSED(create_user);

    // Allocate space for a new node using malloc
    Node *node_ptr = (Node *) malloc(sizeof(Node));
    if (node_ptr == NULL) {
        return NULL;
    }

    // Allocate space for a new user using creat_user
    User *user_ptr = create_user(name, type, data);
    if (user_ptr == NULL) {
        free(node_ptr);
        return NULL;
    }

    // Set the next to NULL
    node_ptr -> next = NULL;

    // Set the data in this node
    node_ptr -> data = user_ptr;

    return node_ptr;
    // return NULL;
}

/** student_equal
 *
 * Helper function to compare two Student structs. You may find it ueful to call this helper
 * function from the user_equal function that you have to implement.
 *
 * @param the two Student structs to be compared
 * @return 1 if equal, 0 otherwise
 */
static int student_equal(const Student *student1, const Student *student2)
{
    if (student1->num_classes != student2->num_classes) return 0;
    if (student1->grades != student2->grades)
    {
        if (student1->grades == NULL || student2->grades == NULL) return 0;
        if (memcmp(student1->grades, student2->grades,
                student1->num_classes * sizeof(double)))
        {
            return 0;
        }
    }
    return 1;
}

/** user_equal
 * Helper function to help you compare two user structs.
 *
 * If the name, type, and union fields are all equal, you should return 1.
 * Otherwise, return 0.
 *
 * NOTE: struct members that are pointers may be null!
 * If two users both have null for a certain pointer, the pointers are
 * considered equal.
 * However, if either of the input users is NULL, you should return 0.
 *
 * You may find it useful to call the student_equal function defined above.
 *
 * Make sure you're using the right function when comparing the name.
 * Remember that you are allowed to use functions from string.h
 *
 * This is meant to be used as a helper function in 'contains'; it is not tested
 * by the autograder.
 *
 * @param the two User structs to be compared
 * @return 1 if equal, 0 otherwise
 */
static int user_equal(const User *user1, const User *user2)
{
    // UNUSED(user1);
    // UNUSED(user2);
    // UNUSED(student_equal);

    // Comapre "names":
    if (user1 -> name != user2 -> name) {
        if (strcmp(user1 -> name, user2 -> name) != 0) {
            return 0;
        }
    }
    
    // Comapre "type":
    if (user1->type != user2->type) {
        return 0;
    }

    // Compare data for each type
    if (user1->type == STUDENT && user2->type == STUDENT) {
        if (!student_equal(&(user1->data.student), &(user2->data.student))) {
            return 0;
        }
    } else if (user1->type == INSTRUCTOR && user2->type == INSTRUCTOR) {
        if (user1->data.instructor.salary != user2->data.instructor.salary) {
            return 0;
        }
    }

    return 1;
}

/** create_list
 *
 * Creates a LinkedList by allocating memory for it on the heap.
 * Be sure to initialize size to zero and head to NULL.
 *
 * If malloc returns NULL, you should return NULL to indicate failure.
 *
 * @return a pointer to a new struct list or NULL on failure
 */
LinkedList *create_list(void)
{
    LinkedList *linkedlist_ptr = (LinkedList *) malloc(sizeof(LinkedList));
    if (linkedlist_ptr == NULL) {
        return NULL;
    }
    linkedlist_ptr -> head = NULL;
    linkedlist_ptr -> size = 0;

    return linkedlist_ptr;
}

/** push_front
 *
 * Adds the element at the front of the LinkedList.
 *
 * @param list a pointer to the LinkedList structure.
 * @param      the fields of the User struct
 * @return 1 if the LinkedList is NULL or if allocating the new node fails, 0 if
 * successful.
 */
int push_front(LinkedList *list, char *name, UserType type, UserUnion data)
{
    // UNUSED(list);
    // UNUSED(name);
    // UNUSED(type);
    // UNUSED(data);
    // UNUSED(create_node);
    if (list == NULL) {
        return 1;
    }
    Node *new_node = create_node(name, type, data);
    if (new_node == NULL) {
        return 1;
    }

    if (list->size == 0) {
        list -> head = new_node;
    } else {
        Node *old_head = list->head;
        new_node -> next = old_head;
        list->head = new_node;
    }
    list->size = (list->size) + 1;


    return 0;
}

/** push_back
 *
 * Adds the element to the back of the LinkedList.
 *
 * @param list a pointer to the LinkedList structure.
 * @param      the fields of the User struct
 * @return 1 if the LinkedList is NULL or if allocating the new node fails, 0 if
 * successful.
 */
int push_back(LinkedList *list, char *name, UserType type, UserUnion data)
{
    // UNUSED(list);
    // UNUSED(name);
    // UNUSED(type);
    // UNUSED(data);
    // UNUSED(create_node);

    // if the LinkedList is NULL
    if (list == NULL) {
        return 1;
    }

    // if allocating the new node fails
    Node *new_node = create_node(name, type, data);
    if (new_node == NULL) {
        return 1;
    }

    if (list->size == 0) {
        list -> head = new_node;
        list->size = (list->size) + 1;
    } else {
        Node *ptr = list->head;

        while (ptr->next != NULL) {
            ptr = ptr->next;
        }

        ptr->next = new_node;

        // increment size
        list->size = (list->size) + 1;
    }

    
    return 0;
}

/** add_at_index
 *
 * Add the element at the specified index in the LinkedList. This index must lie in
 * the inclusive range [0,size].
 * For example, if you have no elements in the LinkedList,
 * you should be able to add to index 0 but no further.
 * If you have two elements in the LinkedList,
 * you should be able to add to index 2 but no further.
 *
 * @param list a pointer to the LinkedList structure
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size]
 * @param the fields of the User struct
 * @return 1 if the index is out of bounds or the LinkedList is NULL or malloc fails
 *         (do not add the data in this case)
 *         otherwise (on success) return 0
 */
int add_at_index(LinkedList *list, int index, char *name, UserType type, UserUnion data)
{
    // UNUSED(list);
    // UNUSED(index);
    // UNUSED(name);
    // UNUSED(type);
    // UNUSED(data);
    // UNUSED(create_node);

    // 1 if the index is out of bounds or the LinkedList is NULL
    if (list == NULL || (index > list->size) || (index < 0)) {
        return 1;
    }

    if ((index == 0)) {
        return push_front(list, name, type, data);
    }

    if (index == list->size) {
        return push_back(list, name, type, data);
    }

    // 1 if allocating the new node fails
    Node *new_node = create_node(name, type, data);
    if (new_node == NULL) {
        return 1;
    }

    Node *ptr = list->head;
    for (int i = 0; i <= index - 2; i++) {
        ptr = ptr->next;
    }

    new_node->next = ptr->next;
    ptr->next = new_node;
    
    // increment size
    list->size = (list->size) + 1;

    return 0;
}

/** get
 *
 * Gets the data at the specified index in the LinkedList
 *
 * @param list a pointer to the LinkedList structure
 * @param index 0-based, starting from the head.
 * @param dataOut A pointer to a pointer used to return the data from the
 *        specified index in the LinkedList or NULL on failure.
 * @return 1 if dataOut is NULL or index is out of range of the LinkedList or
 *         the LinkedList is NULL, 0 (on success) otherwise
 */
int get(LinkedList *list, int index, User **dataOut)
{
    // UNUSED(list);
    // UNUSED(index);
    // UNUSED(dataOut);

    if (dataOut == NULL) {
        return 1;
    }

    if (list == NULL) {
        return 1;
    } else if (index > list->size - 1) {
        return 1;
    } else if (index < 0) {
        return 1;
    }

    if (index == 0) {
        *dataOut = list->head->data;
        return 0;
    }

    Node *ptr = list->head;
    int if_suc = 0;
    for (int i = 0; i < index; i++) {
        ptr = ptr->next;
    }
    *dataOut = ptr->data;
    if_suc = 1;

    if (if_suc == 0) {
        *dataOut = NULL;
        return 1;
    }

    return 0;
}

/** contains
  *
  * Traverses the LinkedList, trying to see if the LinkedList contains some
  * data. We say the list contains some input if there exists some node with
  * equal data as the input.
  *
  * You should use 'user_equal' here to compare the data. Note that pointers are
  * allowed to be null!
  *
  * If there are multiple pieces of data in the LinkedList which are equal to
  * the "data" parameter, return the one at the lowest index.
  *
  *
  * @param list a pointer to the LinkedList structure
  * @param data The data, to see if it exists in the LinkedList
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the LinkedList or NULL on failure
  * @return int    0 if dataOut is NULL, the list is NULL, or the list
  *                does not contain data, else 1
  */
int contains(LinkedList *list, User *data, User **dataOut)
{
    // UNUSED(list);
    // UNUSED(data);
    // UNUSED(dataOut);
    // UNUSED(user_equal);

    if (dataOut == NULL) {
        return 0;
    }

    if (list == NULL || (list->size == 0)) {
        *dataOut = NULL;
        return 0;
    }
    if (list->size == 0) {
        *dataOut = NULL;
        return 0;
    }

    Node *ptr = list->head;
    //*dataOut = NULL;
    int if_contain = 0;

    while (ptr != NULL) {
        if (user_equal(data, ptr->data) != 0) {
            *dataOut = ptr->data;
            if_contain =  1;
            return if_contain;
        }

        ptr = ptr->next;
        
    }

    if (if_contain == 0) {
        *dataOut = NULL;
    }
    

    // if (dataOut == NULL) {
    //     return 0;
    // }
    
    return 0;
}

/** pop_front
  *
  * Removes the Node at the front of the LinkedList, and returns its data to the program user.
  *
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                Node or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_front(LinkedList *list, User **dataOut)
{
    // UNUSED(list);
    // UNUSED(dataOut);
    if (list == NULL || (list->size == 0)) {
        return 1;
    }

    *dataOut = list->head->data;
    Node *old_head = list -> head;
    list->head = old_head->next;

    //free(old_head->data);
    free(old_head);

    list->size = (list->size) - 1;

    return 0;
}

/** pop_back
  *
  * Removes the Node at the back of the LinkedList, and returns its data to the program user.
  *
  * @param list a pointer to the LinkedList.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                Node or NULL if the LinkedList is NULL or empty
  * @return 1 if dataOut is NULL (the LinkedList is NULL or empty), else (on success) 0
  */
int pop_back(LinkedList *list, User **dataOut)
{
    // UNUSED(list);
    // UNUSED(dataOut);

    if (list == NULL || (list->size == 0)) {
        return 1;
    }
    Node *ptr = list->head;

    if (list->size == 1) {
        *dataOut = list->head->data;
        Node *old_head = list -> head;
        list->head = old_head->next;
        free(old_head);
        list->size = (list->size) - 1;
        return 0;
    }

    while (ptr->next->next != NULL) {
        ptr = ptr->next;
    }

    *dataOut = ptr->next->data;
    Node *ptr_trash = ptr->next;
    ptr->next = NULL;

    list->size = (list->size) - 1;
    free(ptr_trash);


    return 0;
}


/** remove_at_index
 *
 * Remove the element at the specified index in the LinkedList.
 *
 * @param list a pointer to the LinkedList structure
 * @param dataOut A pointer to a pointer used to return the data in the last
 *                Node or NULL if the LinkedList is NULL or empty
 * @param index 0-based, starting from the head in the inclusive range
 *              [0,size-1]
 * @return 1 if the index is out of bounds, the LinkedList is NULL or
 *         the dataOut is NULL
 *         otherwise return 0
 */
int remove_at_index(LinkedList *list, User **dataOut, int index)
{
    // UNUSED(list);
    // UNUSED(index);
    // UNUSED(dataOut);

    if (dataOut == NULL) {
        return 1;
    }

    // 1 if the index is out of bounds or the LinkedList is NULL
    if ((list == NULL) || (list->size == 0)) {
        *dataOut = NULL;
        return 1;
    }
    if ((index > list->size) || (index < 0)) {
        return 1;
    }



    // If there is only one node:
    if (index == 0) {
        *dataOut = list->head->data;
        Node *old_head = list -> head;
        list->head = old_head->next;
        free(old_head);
        list->size = (list->size) - 1;
        return 0;
    }

    // pop-back
    if (index == list->size) {
        return pop_back(list, dataOut);
    }

    Node *ptr = list->head;
    for (int i = 0; i <= index - 2; i++) {
        ptr = ptr->next;
    }

    *dataOut = ptr->next->data;

    Node *ptr_trash = ptr->next;

    ptr->next = ptr->next->next;

    free(ptr_trash);
    list->size = (list->size) - 1;


    return 0;
}

/** empty_list
 *
 * Empties the LinkedList. After this is called, the LinkedList should be
 * empty. This does NOT free the LinkedList struct itself, just all nodes and
 * data within. Make sure to check that the list is not NULL before
 * using it.
 *
 * Once again, the things that need to be freed after this function are:
 * - the nodes
 * - the user structs within the nodes
 * - all pointers in the user struct (and the union within)
 *
 * However, if you're using other functions you've written (which you should be),
 * those functions might take care of some of the freeing for you.
 *
 * You may call free on a char pointer as well as a struct pointer.
 *
 * If 'list' is NULL, simply return.
 *
 * @param list a pointer to the LinkedList structure
 */
void empty_list(LinkedList *list)
{
    // UNUSED(list);

    if (list == NULL) {
        return;
    }

    Node *ptr = list->head;

    while (ptr != NULL) {
        if (ptr->data->type == STUDENT) {
            free(ptr->data->data.student.grades);
        }
        free(ptr->data->name);
        free(ptr -> data);
        Node *curr = ptr;
        ptr = ptr -> next;
        free(curr);
        
    }
    // free(list->head);
    list->head = NULL;
    list->size = 0;
    

    
}

/** num_passing_all_classes
 *
 * Traverses the LinkedList, counting the number of Students that are passing
 * all of their classes. We say a student is passing if their grade is greater
 * than or equal to 60.
 *
 * You should make sure your code only counts students, as instructors cannot be
 * passing or failing a class!
 *
 * If a student is not taking any classes, they are NOT considered to be passing
 * all their classes.
 *
 * @param list a pointer to the LinkedList structure
 * @param dataOut A pointer to int used to return the count of students passing all
 *                of their classes
 *                or -1 if the LinkedList is NULL or empty
 * @return 1 if the LinkedList is NULL or empty, else (on success) 0
 */
int num_passing_all_classes(LinkedList *list, int *dataOut)
{
    // UNUSED(list);
    // UNUSED(dataOut);

    if (list == NULL || (list->size == 0)) {
        *dataOut = -1;
        return 1;
    }
    Node *ptr = list->head;

    int if_pass_all = 0;
    double count = 0;

    while (ptr != NULL) {
        if (ptr->data->type == STUDENT) {

            if_pass_all = 1;
            for (int i = 0; i < ptr->data->data.student.num_classes; i++) {
                if ((ptr->data->data.student.grades[i]) < 60) {
                    if_pass_all = 0;
                }
            }
            if (if_pass_all == 1) {
                count ++;
            }
        }
        ptr = ptr -> next;
    }

    *dataOut = count;

    return 0;
}

/** get_average_salary
 *
 * Traverses the LinkedList, computing the average of all instructor salaries.
 *
 * You should make sure your code only looks at instructors, as students do not have salaries!
 *
 * If there are no instructors in the list, place a 0 at dataOut.
 *
 * @param list a pointer to the LinkedList structure
 * @param dataOut A pointer to double used to return the average salary of the instructors
 *                or -1 if the LinkedList is NULL or empty
 * @return 1 if the LinkedList is NULL or empty, else (on success) 0
 */
int get_average_salary(LinkedList *list, double *dataOut)
{
    // UNUSED(list);
    // UNUSED(dataOut);
    if (list == NULL || (list->size == 0)) {
        *dataOut = -1;
        return 1;
    }
    Node *ptr = list->head;
    double sum = 0;
    double count = 0;
    while (ptr != NULL) {
        if (ptr->data->type == INSTRUCTOR) {
            sum += ptr->data->data.instructor.salary;
            count ++;
        }
        ptr = ptr -> next;
    }
    if (count == 0) {
        *dataOut = 0;
    } else {
        *dataOut = sum/count;
    }


    return 0;
}

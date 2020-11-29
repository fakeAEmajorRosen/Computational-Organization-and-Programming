;;=======================================
;; CS 2110 - Fall 2020
;; HW6 - Map Function to Linked List
;;=======================================
;; Name: dwight schrute
;;=======================================

;; In this file, you must implement the 'map' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in Complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'map' label.


.orig x3000

map
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of map: Node 'head', function 'func'
;; - Node head is the head node of a linked list. If the head node is at x4000,
;;   then head will be the number x4000. The value at this address is the
;;   address of the next node in the list, and the value of the node itself is
;;   at the address proceeding the head node address.
;; - function func is the address of the function you should call. What
;;   instruction can you use to jump to a subroutine at this address?
;;
;; Pseudocode:
;; map(Node head, function func) {
;;     if (head == null) { // head == 0
;;         return head;
;;     }
;;     head.value = func(head.value);
;;     map(head.next, func);
;;     return head;
;; }

    ;; stack setup
    ADD R6, R6, #-4
    STR R7, R6, #2
    STR R5, R6, #1

    ADD R5, R6, #0

    ADD R6, R6, #-5
    STR R0, R6, #4
    STR R1, R6, #3
    STR R2, R6, #2
    STR R3, R6, #1
    STR R4, R6, #0

    LDR R0, R5, #4  ;; R0 <- head
    STR R0, R5, #3  ;; store head as return value
    LDR R1, R5, #5  ;; R1 <- func

    ADD R2, R0, #0  ;; R2 = curr
    BRZ TEARDOWN

    LDR R3, R2, #1  ;; R3 <- curr.data
    ADD R6, R6, #-1 ;; move stack pointer
    STR R3, R6, #0  ;; push function arg onto stack
    JSRR R1
    LDR R3, R6, #0  ;; return value from function call
    STR R3, R2, #1  ;; curr.data = return value
    ADD R6, R6, #2  ;; move stack pointer down

    LDR R2, R2, #0  ;; curr = curr.next
    ADD R6, R6, #-2 ;; push curr and func
    STR R2, R6, #0  ;; R2 = head.next
    STR R1, R6, #1  ;; R1 = func
    JSR map
    ADD R6, R6, #3  ;; pop tail, head.next, func

    TEARDOWN
        LDR R0, R6, #4
        LDR R1, R6, #3
        LDR R2, R6, #2
        LDR R3, R6, #1
        LDR R4, R6, #0
        ADD R6, R5, #0
        LDR R5, R6, #1
        LDR R7, R6, #2
        ADD R6, R6, #3

RET



; Needed by Simulate Subroutine Call in Complx
STACK .fill xF000
.end

;; The following is an example of a small linked list that starts at x4000.
;; - The first number (offset 0) contains the address of the next node in the
;;   linked list, or null (0) if this is the last node
;; - The second number (offset 1) contains the data of this node

.orig x4000
.fill x4030
.fill 1
.end

.orig x4030
.fill x4015
.fill 3
.end

.orig x4015
.fill x4050
.fill 5
.end

.orig x4050
.fill x4100
.fill 7
.end

.orig x4100
.fill 0
.fill 1
.end

;; The following functions are possible functions that may be called by the map
;; function. Note that these functions do not do the full calling convention on
;; the callee's side. However, they will work perfectly fine as long as you
;; follow the convention on the caller's side.
;; Do not edit these functions; they will be used by the autograder.
.orig x5000
    double
    ADD R6, R6, -2
    STR R0, R6, 0
    LDR R0, R6, 2
    ADD R0, R0, R0
    STR R0, R6, 1
    LDR R0, R6, 0
    ADD R6, R6, 1
    RET
.end
.orig x5100
    negate
    ADD R6, R6, -2
    STR R0, R6, 0
    LDR R0, R6, 2
    NOT R0, R0
    ADD R0, R0, 1
    STR R0, R6, 1
    LDR R0, R6, 0
    ADD R6, R6, 1
    RET
.end
.orig x5200
    increment
    ADD R6, R6, -2
    STR R0, R6, 0
    LDR R0, R6, 2
    ADD R0, R0, 1
    STR R0, R6, 1
    LDR R0, R6, 0
    ADD R6, R6, 1
    RET
.end
.orig x5300
    isOdd
    ADD R6, R6, -2
    STR R0, R6, 0
    LDR R0, R6, 2
    AND R0, R0, 1
    STR R0, R6, 1
    LDR R0, R6, 0
    ADD R6, R6, 1
    RET
.end
.orig x5400
    decrement
    ADD R6, R6, -2
    STR R0, R6, 0
    LDR R0, R6, 2
    ADD R0, R0, -1
    STR R0, R6, 1
    LDR R0, R6, 0
    ADD R6, R6, 1
    RET
.end

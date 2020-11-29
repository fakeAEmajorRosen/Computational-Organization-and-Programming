;;=======================================
;; CS 2110 - Fall 2020
;; HW6 - Recursive Binary Tree Max
;;=======================================
;; Name:
;;=======================================

;; In this file, you must implement the 'max' and 'treemax' subroutines.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in Complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'map' label.

.orig x3000

max
;; This subroutine is a helper subroutine that returns the maximum of its three
;; arguments.
;;
;; max(leftval,headval,rightval) {
;;     if (leftval > headval) {
;;         if (leftval > rightval) {
;;             return leftval;
;;         } else {
;;             return rightval;
;;         }
;;     } else {
;;         if (headval > rightval) {
;;             return headval;
;;         } else {
;;             return rightval;
;;         }
;;     }
;; }

;; buildup
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

;; function
LDR R0, R5, 4
LDR R1, R5, 5
LDR R2, R5, 6
NOT R3, R0
ADD R3, R3, 1
ADD R3, R1, R3  ; headval - leftval
BRn LEFTLARGER
HEADLARGER
NOT R3, R2
ADD R3, R3, 1
ADD R3, R1, R3  ; headval - rightval
BRp HEADLARGEST
RIGHTLARGEST
STR R2, R5, 3
BR MAXTEARDOWN
HEADLARGEST
STR R1, R5, 3
BR MAXTEARDOWN
LEFTLARGER
NOT R3, R0
ADD R3, R3, 1
ADD R3, R2, R3  ; rightval - leftval
BRp RIGHTLARGEST
LEFTLARGEST
STR R0, R5, 3
BR MAXTEARDOWN

;; teardown
MAXTEARDOWN
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



treemax
;; See the PDF for more information on what this subroutine should do.
;;
;; treemax(root) {
;;     if (root == null) {
;;         return 0;
;;     }
;;     leftval = treemax(root.left);
;;     rightval = treemax(root.right);
;;     return max(leftval, root.data, rightval);
;; }

;; buildup
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

    ;; function

    LDR R0, R5, 4   ; obtain root
    BRz RETURN

    LDR R1, R0, 0   ; obtain left
    ADD R6, R6, -1  ; push left
    STR R1, R6, 0
    JSR treemax     ; recurse
    LDR R1, R6, 0   ; pop leftval
    ADD R6, R6, 2

    LDR R2, R0, 2   ; obtain headval

    LDR R3, R0, 1   ; obtain right
    ADD R6, R6, -1  ; push right
    STR R3, R6, 0
    JSR treemax     ; recurse
    LDR R3, R6, 0   ; pop rightval
    ADD R6, R6, 2

    ADD R6, R6, -3  ; push leftval, headval, rightval
    STR R1, R6, 0
    STR R2, R6, 1
    STR R3, R6, 2
    JSR max         ; get max
    LDR R0, R6, 0   ; pop max
    ADD R6, R6, 4

    RETURN
    STR R0, R5, 3   ; R0 either contains zero (null case) or the max returned from JSR max

    ;; teardown
    TREEMAXTEARDOWN
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

;; IMPORTANT NOTE: we recommend following the pseudocode exactly. Part of the
;; autograder checks that your implementation is recursive. This means that your
;; implementation might fail this test if, when calculating treemax(x4000), you
;; recursively calculated treemax(x5000) first instead of treemax(x4008).

;; The following is an example of a small binary tree that starts at x4000.
;; - The first number (offset 0) contains the address of the left node in the tree
;; - The second number (offset 1) contains the address of the right node in the tree
;; - The third number (offset 2) contains the data of this node
;; - A null (0) address indicates that there is no left/right node
.orig x4000
.fill x4008
.fill x5000
.fill 5
.end

.orig x4008
.fill 0
.fill 0
.fill 12
.end

.orig x5000
.fill 0
.fill 0
.fill 15
.end



;; Another example you can test with
;; .orig x4000
;; .fill x6003
;; .fill x6006
;; .fill 10
;; .end
;; .orig x6003
;; .fill x6010
;; .fill x0
;; .fill 3
;; .fill x0
;; .fill x6009
;; .fill 9
;; .fill x0
;; .fill x0
;; .fill 8
;; .fill x0
;; .fill x0
;; .fill x0
;; .fill x0
;; .fill x6016
;; .fill x6013
;; .fill 42
;; .fill x0
;; .fill x0
;; .fill 5
;; .fill x0
;; .fill x0
;; .fill 12
;; .end

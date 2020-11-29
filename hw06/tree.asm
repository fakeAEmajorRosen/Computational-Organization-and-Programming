;;=======================================
;; CS 2110 - Fall 2020
;; HW6 - Recursive Binary Tree Max
;;=======================================
;; Name: Ting-Ying Yu
;;=======================================

;; In this file, you must implement the 'max' and 'treemax' subroutines.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in Complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'map' label.

.orig x3000
HALT

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

;; YOUR CODE HERE
;; INITIALIZATION
    ;; INITIALIZATION1
    ADD R6, R6, -4   ;; Allocate space
    STR R7, R6, 2    ;; Save return address(R7) to (R6 + 2)
    STR R5, R6, 1    ;; Save old FP to (R6 + 1)
    ADD R5, R6, 0    ;; Copy SP to FP
    ADD R6, R6, -5   
    ;; save Room for 4 registers
    STR R0, R6, 0  ;; save R0
    STR R1, R6, 1   ;; save R1
    STR R2, R6, 2   ;; save R2
    STR R3, R6, 3   ;; save R3
    ;; STR R4, R6, 4



;; max meat
    ;; MAXMEAT
    ;; max meat
    LDR R0, R5, 4  ;; R0 = leftval
    LDR R1, R5, 5  ;; R1 = headval
    LDR R2, R5, 6  ;; R2 = rightval
    NOT R3, R1     
    ADD R3, R3, 1 ;; R3 = -headval


    BIGIF
    ADD R3, R3, R0       ;; R3 = leftval - headval
    BRnz BIGELSE
        LDR R2, R5, 6    ;; R2 = rightval
        NOT R3, R2
        ADD R3, R3, 1    ;; R3 = -rightval
        LDR R0, R5, 4    ;; R0 = leftval
        ADD R3, R3, R0   ;; if (leftval > rightval) {
        BRnz FIRSTELSE
            LDR R0, R5, 4  ;; R0 = leftval
            STR R0, R5, 0  ;; save the return value ("answer") at R5 (FP)
            BR ENDBIGIF
        FIRSTELSE
            LDR R0, R5, 6  ;; R0 = rightval
            STR R0, R5, 0  ;; save the return value ("answer") at R5 (FP)
            BR ENDBIGIF
    
    BIGELSE
        LDR R1, R5, 5   ;; R1 = headval
        LDR R2, R5, 6   ;; R2 = rightval
        NOT R3, R2
        ADD R3, R3, 1   ;; R3 = -rightval
        ADD R3, R3, R1  ;; if (headval > rightval) {
        BRnz SECONDELSE
            LDR R0, R5, 5   ;; R0 = headval
            STR R0, R5, 0  ;; save the return value ("answer") at R5 (FP)
            BR ENDBIGIF
        SECONDELSE
            LDR R0, R5, 6   ;; R0 = rightval
            STR R0, R5, 0  ;; save the return value ("answer") at R5 (FP)
            BR ENDBIGIF
    ENDBIGIF

;; Tear down ending
    ;; TREARDOWN1
    LDR R0, R5, 0    ;;;; (store RV at R0) Return value = anser (FP)
    STR R0, R5, 3    ;;;; store RV at R5 + 3
    ;; Restore registers
    LDR R0, R6, 0    ;; Restore R0
    LDR R1, R6, 1    ;; Restore R1
    LDR R2, R6, 2    ;; Restore R2
    LDR R3, R6, 3    ;; Restore R3
    ;; LDR R4, R6, 4    ;; Restore R4

    ADD R6, R5, 0     ;; Restore SP
    LDR R5, R6, 1     ;; Restore FP
    LDR R7, R6, 2     ;; Restore RA
    ADD R6, R6, 3     ;; POP RA, FP, LV1
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

;; YOUR CODE HERE

;; INITIALIZATION
    ;; INITIALIZATION2
    ADD R6, R6, -4   ;; Allocate space
    STR R7, R6, 2    ;; Save return address(R7) to (R6 + 2)
    STR R5, R6, 1    ;; Save old FP to (R6 + 1)
    ADD R5, R6, 0    ;; Copy SP to FP
    ADD R6, R6, -6   ;; 4 register and 2 local val   
    ;; save Room for 4 registers
    STR R0, R6, 0  ;; save R0
    STR R1, R6, 1   ;; save R1
    STR R2, R6, 2   ;; save R2
    STR R3, R6, 3   ;; save R3
    ;; STR R4, R6, 4

;; tree function start here
    ;; TREEMEAT
    LDR R0, R5, 4  ;; R0 = root
;; if (root == null) {  return 0;
    BRnp ELSE
    ;; return head
        AND R0, R0, 0  ;; R0 = 0
        STR R0, R5, 0  ;; save the return value ("answer") at R5 (FP)
        BR IFEND
    ELSE

;;     leftval = treemax(root.left);
    LDR R0, R5, 4     ;; R0 = root
    LDR R2, R0, 0     ;; R2 = root.left
    ADD R6, R6, -1    ;; Push up 1 for arg
    STR R2, R6, 0     ;; Store R2 = root.left it in to be the arg for func
    JSR treemax           ;; treemax(root.left)
    LDR R3, R6, 0     ;; R3 = rv = treemax(root.left)
    ADD R6, R6, 2     ;; pop rv and arg1
    STR R3, R5, 0     ;; store R3 = leftval to where FP is pointing

;;     rightval = treemax(root.right);
    LDR R0, R5, 4     ;; R0 = root
    LDR R2, R0, 1     ;; R2 = root.right
    ADD R6, R6, -1    ;; Push up 1 for arg
    STR R2, R6, 0     ;; Store R2 = root.right it in to be the arg for func
    JSR treemax           ;; treemax(root.right)
    LDR R3, R6, 0     ;; R3 = rv = treemax(root.right)
    ADD R6, R6, 2     ;; pop rv and arg1
    STR R3, R5, -1     ;; store R3 = rightval to where FP is pointing -1

;; return max(leftval, root.data, rightval);
    LDR R0, R5, 4     ;; R0 = root
    LDR R0, R0, 2     ;; R0 = root.data
    LDR R1, R5, 0     ;; R1 = leftval
    LDR R2, R5, -1    ;; R2 = rightval
    
    ADD R6, R6, -1    ;; Push up 1 for arg
    STR R2, R6, 0     ;; Store R2 = rightval it in to be the arg for func

    ADD R6, R6, -1    ;; Push up 1 for arg
    STR R0, R6, 0     ;; Store R0 = root.data it in to be the arg for func
    
    ADD R6, R6, -1    ;; Push up 1 for arg
    STR R1, R6, 0     ;; Store R1 = leftval it in to be the arg for func
    JSR max           ;; max(leftval, root.data, rightval);

    LDR R0, R6, 0     ;; R0 = max(leftval, root.data, rightval)
    ADD R6, R6, 4     ;; pop rv and args
    ;; retrun
    STR R0, R5, 0  ;; save the return value ("answer") at R5 (FP)

    IFEND



;; Tear down ending
    ;; TREARDOWN2
    LDR R0, R5, 0    ;;;; (store RV at R0) Return value = anser (FP)
    STR R0, R5, 3    ;;;; store RV at R5 + 3
    ;; Restore registers
    LDR R0, R6, 0    ;; Restore R0
    LDR R1, R6, 1    ;; Restore R1
    LDR R2, R6, 2    ;; Restore R2
    LDR R3, R6, 3    ;; Restore R3
    ;; LDR R4, R6, 4    ;; Restore R4

    ADD R6, R5, 0     ;; Restore SP
    LDR R5, R6, 1     ;; Restore FP
    LDR R7, R6, 2     ;; Restore RA
    ADD R6, R6, 3     ;; POP RA, FP, LV1
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

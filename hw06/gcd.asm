;;=======================================
;; CS 2110 - Fall 2020
;; HW6 - Recursive Greatest Common Denominator
;;=======================================
;; Name: Ting-Ying Yu
;;=======================================

;; In this file, you must implement the 'gcd' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in Complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'map' label.


.orig x3000
HALT

gcd
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of GCD: integer a, integer b
;;
;; Pseudocode:
;; gcd(int a, int b) {
;;     if (a == b) {
;;         return a;
;;     } else if (a < b) {
;;         return gcd(b, a);
;;     } else {
;;         return gcd(a - b, b);
;;     }
;; }


;; YOUR CODE HERE

;; initial code
    ADD R6, R6, -4   ;; Allocate space
    STR R7, R6, 2    ;; Save return address(R7) to (R6 + 2)
    STR R5, R6, 1    ;; Save old FP to (R6 + 1)
    ADD R5, R6, 0    ;; Copy SP to FP
    ADD R6, R6, -4   
    ;; save Room for 4 registers
    STR R0, R6, 0  ;; save R0
    STR R1, R6, 1   ;; save R1
    STR R2, R6, 2   ;; save R2
    STR R3, R6, 3   ;; save R3

;; gcd meat
    
    LDR R0, R5, 4  ;; R0 = a
    LDR R1, R5, 5  ;; R0 = b
    NOT R1, R1
    ADD R1, R1, 1  ;; R1 = -b
    ADD R2, R1, R0 ;; R2 = a-b

;; if (a == b)
    BRz IFEND      ;; Brach to the IFEND 

;; if (a-b > 0)
    ADD R2, R2, 0  ;; branch to ELSE
    BRp ELSE

;; else if (a < b) { return gcd(b, a);
IFELSE1
    LDR R1, R5, 5  ;; R1 = b
    ADD R6, R6, -1 ;; Move R6 up one for space
    STR R0, R6, 0  ;; store R0 = a at the position of 2nd arg
    ADD R6, R6, -1 ;; Move R6 up again
    STR R1, R6, 0  ;; store R1 = b at the position of 1st arg
    JSR gcd        ;; gcd(b, a);
    LDR R0, R6, 0  ;; R0 = rv
    ADD R6, R6, 3  ;; pop rv and arg1
    STR R0, R5, 0  ;; store R0 back to the "answer" position
    BR END

;; else { return gcd(a - b, b);
ELSE
    LDR R1, R5, 5  ;; R1 = b
    ADD R6, R6, -1 ;; Move R6 up one for space
    STR R1, R6, 0  ;; store R1 = b at the position of 2nd arg
    ADD R6, R6, -1 ;; Move R6 up again
    STR R2, R6, 0  ;; store R2 = a - b at the position of 1st arg
    JSR gcd        ;; gcd(a - b, b);
    LDR R0, R6, 0  ;; R0 = rv
    ADD R6, R6, 3  ;; pop rv and arg1 and arg2
    STR R0, R5, 0  ;; store R0 back to the "answer" position
    BR END

;; if (a==b) { return a;
IFEND
    LDR R0, R5, 4  ;; R0 = a
    STR R0, R5, 0  ;; save the return value ("answer") at R5 (FP)
END

    ;; Tear down ending
    LDR R0, R5, 0    ;;;; (store RV at R0) Return value = anser (FP)
    STR R0, R5, 3    ;;;; store RV at R5 + 3
    ;; Restore registers
    LDR R0, R6, 0    ;; Restore R0
    LDR R1, R6, 1    ;; Restore R1
    LDR R2, R6, 2    ;; Restore R2
    LDR R3, R6, 3    ;; Restore R3

    ADD R6, R5, 0     ;; Restore SP
    LDR R5, R6, 1     ;; Restore FP
    LDR R7, R6, 2     ;; Restore RA
    ADD R6, R6, 3     ;; POP RA, FP, LV1



RET

; Needed by Simulate Subroutine Call in Complx
STACK .fill xF000
.end

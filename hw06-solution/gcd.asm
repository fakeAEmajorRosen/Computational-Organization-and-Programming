;;=======================================
;; CS 2110 - Fall 2020
;; HW6 - Recursive Greatest Common Denominator
;;=======================================
;; Name: Captain Price
;;=======================================

;; In this file, you must implement the 'gcd' subroutine.

;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in Complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'map' label.


.orig x3000

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

    ;; stack setup
    ADD R6, R6, #-3
    STR R7, R6, #1 ;; store prev return address
    STR R5, R6, #0 ;; store prev frame pointer

    ADD R5, R6, #0 ;; R5 <- R6 setting new frame pointer

    ;; store registers that are used in the func
    ADD R6, R6, #-4
    STR R0, R6, #3
    STR R1, R6, #2
    STR R2, R6, #1
    STR R3, R6, #0

    ;; load parameters into registers
    LDR R0, R5, #3 ;; R0 <- a
    LDR R1, R5, #4 ;; R1 <- b

    ;; R2 <- -b
    NOT R2, R1
    ADD R2, R2, #1

    ADD R3, R0, R2 ;; R3 <- a - b

    BRp MORE
    BRn LESS

    ;; a == b
    STR R0, R5, #2 ;; store return value
    BR TEARDOWN

    ;; a > b
    MORE
            ADD R6, R6, #-2
            STR R1, R6, #1 ;; push b onto stack
            STR R3, R6, #0 ;; push a - b onto stack

            JSR gcd
            BR RETURN_VAL

    ;; a < b
    LESS
            ADD R6, R6, #-2
            STR R0, R6, #1 ;; push a onto stack
            STR R1, R6, #0 ;; push b onto stack

            JSR gcd
            BR RETURN_VAL

    RETURN_VAL
            ;; store return value
            LDR R0, R6, #0
            ADD R6, R6, #1
            STR R0, R5, #2
            ;; remove the paramters
            ADD R6, R6, #2
            BR TEARDOWN

    TEARDOWN
            LDR R0, R6, #3
            LDR R1, R6, #2
            LDR R2, R6, #1
            LDR R3, R6, #0
            ADD R6, R5, #0
            LDR R5, R6, #0
            LDR R7, R6, #1
            ADD R6, R6, #2

    RET

; Needed by Simulate Subroutine Call in Complx
STACK .fill xF000
.end

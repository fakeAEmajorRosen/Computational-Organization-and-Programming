;; Timed Lab 3
;; Student Name: Ting-Ying Yu

;; Please read the PDF for full directions.
;; The pseudocode for the program you must implement is listed below; it is also listed in the PDF.
;; If there are any discrepancies between the PDF's pseudocode and the pseudocode below, notify a TA on Piazza quickly.
;; However, in the end, the pseudocode is just an example of a program that would fulfill the requirements specified in the PDF.

;; Pseudocode:
;;
;; int A;
;; int B;
;;
;;
;; int MOD(int a, int b) {
;      // CHECKPOINT 1
;;     A = a;
;;     B = b;
;;
;;     // CHECKPOINT 2
;;     while(a >= b) {
;;         a = a - b;
;;     }
;;
;;     return a;
;; }
;;
;;
;;
;; int SUM(Node node) {
;;     // CHECKPOINT 3
;;     if (node == null) {
;;         return 0;
;;     }
;;
;;     // CHECKPOINT 4
;;     int data1 = node.data1;
;;     int data2 = node.data2;
;;     int result;
;;
;;     if (data1 > data2) {
;;         result = MOD(data1, data2);
;;     } else {
;;         result = MOD(data2, data1);
;;     }
;;
;;     int sum = SUM(node.next);
;;     return result + sum;
;; }

.orig x3000

STACK .fill xF000 ; NEEDED BY COMPLX, DO NOT REMOVE

; Labels for checkpoints
A .blkw 1 ; Checkpoint 1
B .blkw 1 ; Checkpoint 1

;; DO NOT MODIFY ANYTHING ABOVE




; START MOD SUBROUTINE
MOD
;; STACK SETUP
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

    ;;FUNCTION HERE

    LDR R0, R5, #4  ;; R0: a
    LDR R1, R5, #5  ;; R1: b

    ST R0, A ;; A = a
    ST R1, B ;; B = b
    
    LDR R0, R5, #4  ;; R0: a
    LDR R1, R5, #5  ;; R1: b
    AND R3, R3, 0
    NOT R3, R1
    ADD R3, R3, 1   ;; R3 = -b
    ADD R4, R3, R0  ;; R4 = a - b
    
    WHILELOOP
    ADD R4, R4, 0
    BRn ENDLOOP
    ADD R0, R4, 0
    ADD R4, R4, R3  ;; R4 = R4 - b
    
    BR WHILELOOP

    ENDLOOP
    

    ;; return a
    ;; MAKE SURE TO DO THIS
    STR R0, R5, 0  ;; store R0(YOUR RV) back to the "answer" position
    ;; MOVE IT TO RV POSITION
    LDR R0, R5, 0    ;;;; (store RV at R0) Return value = anser (FP)
    STR R0, R5, 3    ;;;; !!! MOST IMPORTANT!!! store RV at R5 + 3 (RV position)


;; Stack tear down
    TEARDOWN
        ;; Restore registers
        LDR R0, R6, #4
        LDR R1, R6, #3
        LDR R2, R6, #2
        LDR R3, R6, #1
        LDR R4, R6, #0


        ADD R6, R5, #0  ;; Restore SP
        LDR R5, R6, #1  ;; Restore FP
        LDR R7, R6, #2
        ADD R6, R6, #3


    ; !!!!! WRITE YOUR CODE HERE !!!!!



RET
; END MOD SUBROUTINE




; START SUM SUBROUTINE
SUM
;; STACK SETUP
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


    ;; FUNCTION HERE
    LDR R0, R5, 4   ; R0: node
    BRz RETURN      ;; if node == null

    LDR R1, R0, 1   ; R1: node.data1
    LDR R2, R0, 2   ; R2: node.data2
    AND R3, R3, 0   ; R3 = 0

    NOT R4, R2
    ADD R4, R4, 1  ; R4 = -DATA2
    ADD R4, R4, R1 ; R4 = DATA1 - DATA2
    ADD R4, R4, 0  ; CONDITION
    BRnz ELSEBLOCK

    IFBLOCK
    LDR R0, R5, 4   ; R0: node
    LDR R1, R0, 1   ; R1: node.data1
    LDR R2, R0, 2   ; R2: node.data2
    ADD R6, R6, #-1
    STR R2, R6, #0   ;; push R2 (data2)
    ADD R6, R6, #-1  ;; push R1 (data1)
    STR R1, R6, #0 
    JSR MOD
    LDR R0, R6, #0   ;; result: R0
    ADD R6, R6, #3   ;; pop
    BR ENDIFBLOCK


    ELSEBLOCK
    LDR R0, R5, 4   ; R0: node
    LDR R1, R0, 1   ; R1: node.data1
    LDR R2, R0, 2   ; R2: node.data2
    ADD R6, R6, #-1
    STR R1, R6, #0   ;; push R1 (data1)
    ADD R6, R6, #-1  ;; push R2 (data2)
    STR R2, R6, #0 
    JSR MOD
    LDR R0, R6, #0   ;; result: R0
    ADD R6, R6, #3   ;; pop
    BR ENDIFBLOCK


    ENDIFBLOCK
    LDR R3, R5, 4   ; R3: the address of node.next
    LDR R3, R3, 0   ; R3: node.next
    ADD R6, R6, #-1
    STR R3, R6, #0   ;; push node.next
    JSR SUM
    LDR R4, R6, #0   ;; sum: R4
    ADD R6, R6, #2   ;; pop

    ;; result + sum
    ADD R0, R4, R0
    STR R0, R5, 0
    BR TEARDOWN2


    RETURN
    AND R0, R0, 0 ;; R0 = 0
    STR R0, R5, 0  ;; store R0(YOUR RV) back to the "answer" position
    BR TEARDOWN2

    TEARDOWN2
;; MOVE IT TO RV POSITION
    LDR R0, R5, 0    ;;;; (store RV at R0) Return value = anser (FP)
    STR R0, R5, 3    ;;;; !!! MOST IMPORTANT!!! store RV at R5 + 3 (RV position)
;; Stack tear down
        ;; Restore registers
        LDR R0, R6, #4
        LDR R1, R6, #3
        LDR R2, R6, #2
        LDR R3, R6, #1
        LDR R4, R6, #0


        ADD R6, R5, #0  ;; Restore SP
        LDR R5, R6, #1  ;; Restore FP
        LDR R7, R6, #2
        ADD R6, R6, #3
    ; !!!!! WRITE YOUR CODE HERE !!!!!
RET
; END SUM SUBROUTINE

.end



; LL NODES FOR TESTING
; EXPECTED SUM RESULT: (5 % 2) + (7 % 4) + (3 % 3) = 4
.orig x4000
.fill x400A
.fill 2
.fill 5
.end

.orig x400A
.fill x4010
.fill 7
.fill 4
.end

.orig x4010
.fill x0000
.fill 3
.fill 3
.end

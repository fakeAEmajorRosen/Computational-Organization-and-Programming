;;=============================================================
;;CS 2110 - Fall 2020
;;Homework 5 - Iterative Division
;;=============================================================
;;Name: Ting-Ying Yu
;;=============================================================

;;Pseudocode (see PDF for explanation)
;;a = (argument 1);
;;b = (argument 2);
;;ANSWER = 0;
;;while (a > 0) {
;;  a = a - b;
;;  ANSWER = ANSWER + 1;
;; }
;;note: when the while-loop ends, the value stored at ANSWER is a divided by b.


.orig x3000
	;;PUT YOUR CODE HERE

	LD R0, A         ;;a = (argument 1);
	LD R1, B         ;;b = (argument 2);
	NOT R1, R1       ;; b = -b
	ADD R1, R1, 1    ;; b = b + 1
	AND R2, R2, 0    ;;ANSWER = 0;  (R2 is ANSWER)

	LOOP
	ADD R0, R0, 0    ;; sets Condition code with the value of A
	BRnz END
	ADD R0, R0, R1   ;; a = a - b
	ADD R2, R2, 1    ;; ANSWER = ANSWER + 1;
	BR LOOP
	END

	ST R2, ANSWER    ; store R2 to ANSWER


HALT

A   .fill 24
B   .fill 4

ANSWER .blkw 1

.end
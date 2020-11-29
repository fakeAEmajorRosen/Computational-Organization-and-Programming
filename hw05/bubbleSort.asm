;;=============================================================
;;CS 2110 - Fall 2020
;;Homework 5 - Bubble Sort
;;=============================================================
;;Name: Ting-Ying Yu
;;=============================================================

;;Pseudocode (see PDF for explanation)
;;x = 0; 								//index of the array
;;len = LENGTH;
;;y = len - 1;							//last index of the array
;;while(y > 0) {
;;  x = 0;
;;  while(x < y) {
;;    if (array[x] > array[x+1]) {
;;      temp = ARRAY[x];
;;      ARRAY[x] = ARRAY[x+1];
;;      ARRAY[x+1] = temp;
;;    }
;;    x++;
;;  }
;;  y--;
;;}

.orig x3000
	;;PUT YOUR CODE HERE
	AND R0, R0, 0     ;; R0 = 0 (R0 is x)
	LD R1, LENGTH     ;; R1 = length
	AND R2, R2, 0     ;; R2 = 0 
	ADD R2, R2, 1     ;; R2 = 1 (R2 is y)
	NOT R2, R2        ;; R2 = -R2
	ADD R2, R2, 1     ;; R2 = R2 + 1 (R2 = -1)
	ADD R2, R2, R1    ;; y = len - 1;	

	LOOP              ;; while(y > 0) {
		ADD R2, R2, 0     ;; sets Condition code with the value of y
		BRnz END

		AND R0, R0, 0     ;;  x = 0;

		LOOP2             ;;  while(x < y) {
			NOT R7, R2        ;; R7 = -R2(y)
			ADD R7, R7, 1     ;; R7 = -R2 + 1 (= -y)
			ADD R7, R7, R0    ;; R7 = R1 + R0 (x-y)
			BRzp END2         ;; sets Condition code with the value of x-y < 0

			LD R1, ARRAY      ;; R1 = x
			ADD R1, R1, R0    ;; R1 = x
			LDR R3, R1, 0     ;; R3 = ARRAY[x]
			ADD R6, R1, 1     ;; R6 = x+1
			LDR R4, R6, 0     ;; R4 = ARRAY[x+1]
			NOT R5, R4        ;; R5 = -ARRAY[x+1]
			ADD R5, R5, 1     ;; R5 = -ARRAY[x+1] + 1
			ADD R5, R5, R3    ;; R5 = array[x] - array[x+1]

			BRnz IFSKIP       ;; if (array[x] > array[x+1]) {
				STR R4, R1, 0     ;;     ARRAY[x] = R4
				STR R3, R6, 0     ;;     ARRAY[x+1] = R2 }
			IFSKIP

			ADD R0, R0, 1     ;; x++
			BR LOOP2
		END2

		AND R1, R1, 0    ;;R1 =0
		ADD R1, R1, 1    ;;R1 =1
		NOT R1, R1
		ADD R1, R1, 1    ;;R1 =-1
		ADD R2, R2, R1   ;;R2 = y-1
		BR LOOP
	END




HALT

ARRAY .fill x4000
LENGTH .fill 7
.end

.orig x4000
.fill 4
.fill 9
.fill 0
.fill 2
.fill 9
.fill 3
.fill 10
.end
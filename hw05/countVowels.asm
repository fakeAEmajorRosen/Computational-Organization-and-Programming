;;=============================================================
;;CS 2110 - Fall 2020
;;Homework 5 - Count the Vowels in a String
;;=============================================================
;;Name: Ting-Ying Yu
;;=============================================================

;;Pseudocode (see PDF for explanation)
;;string = "TWENTY ONE TEN";
;;vcount = 0;
;;i = 0;
;;while(string[i] != ’\0’){
;;  if(string[i] == ’A’ || string[i] == ’E’ ||
;;    string[i] == ’I’ || string[i] == ’O’ ||
;;    string[i] == ’U’){
;;      vcount += 1;
;;  }
;;  i += 1;
;;}
;;ANSWER = vcount;

.orig x3000
	;;PUT YOUR CODE HERE
	LD R0, STRING ;; R0 = x4000
	AND R1, R1, 0 ;; vcount = 0
	AND R2, R2, 0 ;; i = 0

	LOOP
	ADD R3, R0, R2
	LDR R3, R3, 0  ;; R3 = string[i]
	ADD R3, R3, 0
	BRz END
		;; 'A'
		LD R4, A
		NOT R4, R4
		ADD R4, R4, 1        ;; R4 = -R4
		ADD R5, R3, R4   ;; R5 = R3 - R4
		BRz IFSKIP

		;; 'E'
		LD R4, E
		NOT R4, R4
		ADD R4, R4, 1
		ADD R5, R3, R4
		BRz IFSKIP

		;; 'I'
		LD R4, I
		NOT R4, R4
		ADD R4, R4, 1
		ADD R5, R3, R4
		BRz IFSKIP

		;; 'O'
		LD R4, B
		NOT R4, R4
		ADD R4, R4, 1
		ADD R5, R3, R4
		BRz IFSKIP

		;; 'U'
		LD R4, C
		NOT R4, R4
		ADD R4, R4, 1
		ADD R5, R3, R4
		BRz IFSKIP

		BR ELSE
		IFSKIP
		ADD R1, R1, 1  ;;      vcount += 1;
		ELSE

		ADD R2, R2, 1 ;;      i += 1;
	BR LOOP
	END

	ST R1, ANSWER   ;;ANSWER = vcount;
HALT

A .fill x41    ;; A in ASII
E .fill x45
I .fill x49
B .fill x4f
C .fill x55


;;NOTE: Make sure to fill in the ASCII values
;;for the rest of the vowels here!!

STRING .fill x4000
ANSWER .blkw 1
.end

.orig x4000
.stringz "TWENTY ONE TEN"
.end

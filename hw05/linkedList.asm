;;=============================================================
;;CS 2110 - Fall 2020
;;Homework 5 - Linked List
;;=============================================================
;;Name: Ting-Ying Yu
;;=============================================================

;;Pseudocode (see PDF for explanation)
;;targetData = DATA
;;newData = NEWDATA
;;curr = LL.head //HINT: What can an LDI instruction be used for?
;;while (curr != null) {
;;   if (curr.value == targetData) {
;;     curr.value = newData;
;;     break;
;;   } else {
;;     curr = curr.next
;;   }
;;}

.orig x3000
	;;PUT YOUR CODE HERE
	LD R0, DATA       ;;targetData = DATA
	LD R1, NEWDATA    ;;newData = NEWDATA
	LDI R2, LL        ;;curr = LL.head  (THE ADDRESS OF THE CURRENT NODE)

	LOOP 
	ADD R2, R2, 0    ; sets Condition code with the value of the current node
	BRz END
		NOT R3, R0    ;; R3 = ~R0
		ADD R3, R3, 1 ;; R3 = ~R0+1
		LDR R4, R2, 1 ;; R4 = curr.value
		ADD R3, R3, R4 ;; R3 = curr.value - targetData
		BRnp SKIP
			ADD R5, R2, 1 ;; R5:THE ADDRESS POF CURR.VALUE
			STR R1, R5, 0 ;; curr.value = newData; Store R1 to R5
			BR END
		SKIP
			LDR R2, R2, 0    ; curr = curr.next
	BR LOOP
	END


HALT


DATA .fill 10
NEWDATA .fill 15
LL .fill x6000
.end

.orig x4000
.fill x4008
.fill 5
.fill x400A
.fill 2
.fill x4002
.fill 9
.fill x0000 
.fill 3
.fill x4004
.fill 10
.fill x4006
.fill 7
.end

.orig x6000
.fill x4000
.end
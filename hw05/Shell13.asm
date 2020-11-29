.orig x3000
;; YOUR CODE HERE
    LD R0, E
    ADD R0, R0, #0
    BRzp ELSE
    LD R1, F
    LEA R2, E
    STR R1, R2, #0
    STR R0, R2, #1
    ELSE
HALT

E .fill 0
F .fill 5
.end
push            ;this operator is orphaned because the token after it is a push
push int8(1)    ;newline here does not matter but it's included for readability
int8(1)         ;int8(1) is orphaned as well because the token before is an int8

;; this is a comment unless read from stdin

assert
assert int8(1)  ;the same logic applies here as it does on lines 1,4.
int8(1)
pop

push int8(-255) ;underflow
push int8(256)  ;overflow
div             ;div by 0
pop             ;empty stack


exit
;; exit is not the last instruction
pop

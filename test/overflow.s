;; overflows
push int8(255)
push int8(1)
add             ; stack-1 overflows and resets to 0, then adds 1
print
pop


push int8(-254)
push int8(-1)
add             ;again, underflow and add -1
print
pop


push int8(256)  ;pushing overflows is also an error and results in a 0
print
pop

push int8(-255) ;same with underflows
print
pop


exit

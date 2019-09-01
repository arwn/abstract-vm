;; this is a comment not an exit.
;; this is a big test file with lots of valid tests, this shouldn't fail.
;add int8
push int8(12)
push int8(12)
add
assert int8(24)
pop

push int8(12)
push int32(900)
add
assert int32(912)
pop

push int8(12)
push float(12.12)
add
assert float(24.120000)
pop

push int8(12)
push double(1.1111111)
add
assert double(13.111111)
pop

;add int16
push int16(12)
push int8(12)
add
assert int16(24)
pop

push int16(12)
push int32(900)
add
assert int32(912)
pop

push int16(12)
push float(12.12)
add
assert float(24.120000)
pop

push int16(12)
push double(1.1111111)
add
assert double(13.111111)
pop

;add int32
push int32(12)
push int8(12)
add
assert int32(24)
pop

push int32(12)
push int32(900)
add
assert int32(912)
pop

push int32(12)
push float(12.12)
add
assert float(24.120000)
pop

push int32(12)
push double(1.1111111)
add
assert double(13.111111)
pop

;add float
push float(12.0)
push int8(12)
add
assert float(24.000000)
pop

push float(12.0)
push int32(900)
add
assert float(912.000000)
pop

push float(12.0)
push float(12.12)
add
assert float(24.120000)
pop

push float(12.0)
push double(1.1111111)
add
assert double(13.111111)
pop

;add double
push double(12)
push int8(12)
add
assert double(24.000000)
pop

push double(12.0)
push int32(900)
add
assert double(912.000000)
pop

push double(12.0)
push float(12.12)
add
assert double(24.120000)
pop

push double(12.0)
push double(1.1111111)
add
assert double(13.111111)
pop

; sub div mul mod
push int8(10)
push int32(2)
sub
push int16(2)
div
push float(3.3)
mul
push double(5)
mod
assert double(3.200000)

;dump
push int8(1)
push int16(213)
push int32(222222)
push float(3.3)
push float(1489.589e+1)
push double(1e1)
add
dump
pop pop pop pop pop pop
dump

push int8(64)
emit
print
pop
push int16(3232)
print
emit ;3232 > 255

exit
;; anything after the exit will not be executed
dump
exit

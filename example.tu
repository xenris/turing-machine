// Example turing machine program.

// If any bit is a 1 then replace all bits with 1s, otherwise replace all with 0s.

alphabet = 01
blank = .
initial = F

F 0 0 r F
F 1 1 r T
F . . l BF

T 0 0 r T
T 1 1 r T
T . . l BT

BF 0 0 l BF
BF 1 0 l BF
BF . . r End

BT 0 1 l BT
BT 1 1 l BT
BT . . r End

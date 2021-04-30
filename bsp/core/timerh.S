.global timer_handler
.align 8
nop
nop
nop
nop
nop
nop
nop
timer_handler:

li s0 , 0x40000000
li x5 , 0
sw x0 , 0x110(s0)
sw x11, 0x100(s0)
sw x5 , 0x114(s0)
sw x5 , 0x0(s0)
csrrw x0 , 0x300, x5
csrrw x0 , 0x304, x5
mret


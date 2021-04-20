
//__asm__(
//"li x6 , 8;"
//"csrrw x0 , 0x300 , x6;"

//"li x5 , 80;"
//"csrrw x0 , 0x304 , x5;"

//interrupt enable
//"li s0 , 40000000;"
//"li x5, 1;"
//"sw x5 , 0x114(s0);"

//control register
//"sw x5 , 0x0(s0);"
//);

void delay(int a);
//__asm__(
//"WFI;"
//);





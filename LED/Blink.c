void delay(long Mseconds)
{
    while(Mseconds--);
}


int main()
{
    // pointers to registers in memory
    unsigned int* RCGCGPIO = (unsigned int*)0x400FE608;
    unsigned int* GPIOFDEN = (unsigned int*)0x4002551C;
    unsigned int* GPIOFDIR = (unsigned int*)0x40025400;
    unsigned int* GPIOFDATA = (unsigned int*)0x400253FC;  // offset is added for WRITE
    
    // configure registers to set value at that location in memory
    *RCGCGPIO = 0x20U;     // bit 5 set to 1
    *GPIOFDIR = 0x0EU;     // PF1, PF2, PF3  as output
    *GPIOFDEN = 0x0EU;     // PF1, PF2, PF3 are digitalized
    
    // *GPIOFDATA = 0x02U;    // glow RED LED by setting bit PF1 to 1
    // *GPIOFDATA = 0x04U;   // BLUE
    // *GPIOFDATA = 0x08U;   // GREEN
    // 0E for white light
    
    while(1)
    {
        *GPIOFDATA = 0x02U;
        delay(10000000);
        *GPIOFDATA = 0x00U;
        delay(10000000);
    }
    
}

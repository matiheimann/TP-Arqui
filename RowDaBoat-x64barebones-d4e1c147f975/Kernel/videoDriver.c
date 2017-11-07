
#include <videoDriver.h>
#include <textDriver.h>

static const VBEModeInfoBlock * vesaInfo =  (uint64_t*)0x0000000000005C00;


void putpixel(int x,int y) {
    uint8_t * position = vesaInfo->PhysBasePtr + ( x + y* vesaInfo->XResolution)*3;
    position[0] = 0xFF;          
    position[1] = 0xFF; 
    position[2] = 0xFF; 
}


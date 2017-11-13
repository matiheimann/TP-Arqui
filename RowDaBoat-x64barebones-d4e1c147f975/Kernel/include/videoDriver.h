#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H
#include <stdint.h>
#include <font.h>

void putpixel(int x,int y);
int validCharPosition(int x, int y);
int validPixelPosition(int x, int y);
void printChar(char c);
void printCharLine(unsigned char line, int x, int y);
int countHexDigits(uint64_t n);
int countAllDigits(uint64_t n);
void printHex(uint64_t n);
void printInt(uint64_t n);
uint16_t getXres();
uint16_t getYres();
void endScreen();
void nLine();
void erase();
void printString(char*  s);
void blackOut();

#pragma pack(push)    /* Push de la alineación actual */
#pragma pack (1)    /* Alinear las siguiente estructuras a 1 byte */

typedef struct VBEModeInfoBlock
{
  uint16_t ModeAttributes;       
  uint8_t  WinAAttributes;       
  uint8_t  WinBAttributes;       
  uint16_t WinGranularity;       
  uint16_t WinSize;             
  uint16_t WinASegment;         
  uint16_t WinBSegment;        
  uint32_t  WinFuncPtr;         
  uint16_t BytesPerScanLine;    
  uint16_t XResolution;        
  uint16_t YResolution;         
  uint8_t XCharSize;        
  uint8_t  YCharSize;         
  uint8_t  NumberOfPlanes;     
  uint8_t  BitsPerPixel;
  uint8_t  NumberOfBanks;
  uint8_t  MemoryModel;
  uint8_t BankSize;
  uint8_t  NumberOfImagePages;
  uint8_t  Reserved_page;
  uint8_t  RedMaskSize;
  uint8_t  RedMaskPos;
  uint8_t  GreenMaskSize;
  uint8_t  GreenMaskPos;
  uint8_t  BlueMaskSize;
  uint8_t  BlueMaskPos;
  uint8_t  ReservedMaskSize;
  uint8_t  ReservedMaskPos;
  uint8_t  DirectColorModeInfo;
  uint32_t  PhysBasePtr;
} VBEModeInfoBlock;

#pragma pack(pop)   /* Reestablece la alinceación actual */


#define charsPerLine (vesaInfo->XResolution / CHAR_WIDTH)
#define charsPerHeight (vesaInfo->YResolution / CHAR_HEIGHT)
#endif
#include <stdint.h>

void putpixel(int x,int y);

typedef struct VBEModeInfoBlock
{
  uint16_t ModeAttributes       __attribute__ ((packed));
  uint8_t  WinAAttributes       __attribute__ ((packed));
  uint8_t  WinBAttributes       __attribute__ ((packed));
  uint16_t WinGranularity       __attribute__ ((packed));
  uint16_t WinSize              __attribute__ ((packed));
  uint16_t WinASegment          __attribute__ ((packed));
  uint16_t WinBSegment          __attribute__ ((packed));
  uint32_t  WinFuncPtr           __attribute__ ((packed));
  uint16_t BytesPerScanLine     __attribute__ ((packed));
  uint16_t XResolution          __attribute__ ((packed));
  uint16_t YResolution          __attribute__ ((packed));
  uint8_t XCharSize            __attribute__ ((packed));
  uint8_t  YCharSize            __attribute__ ((packed));
  uint8_t  NumberOfPlanes       __attribute__ ((packed));
  uint8_t  BitsPerPixel         __attribute__ ((packed));
  uint8_t  NumberOfBanks        __attribute__ ((packed));
  uint8_t  MemoryModel          __attribute__ ((packed));
  uint8_t BankSize             __attribute__ ((packed));
  uint8_t  NumberOfImagePages   __attribute__ ((packed));
  uint8_t  Reserved_page        __attribute__ ((packed));
  uint8_t  RedMaskSize          __attribute__ ((packed));
  uint8_t  RedMaskPos           __attribute__ ((packed));
  uint8_t  GreenMaskSize        __attribute__ ((packed));
  uint8_t  GreenMaskPos         __attribute__ ((packed));
  uint8_t  BlueMaskSize         __attribute__ ((packed));
  uint8_t  BlueMaskPos          __attribute__ ((packed));
  uint8_t  ReservedMaskSize     __attribute__ ((packed));
  uint8_t  ReservedMaskPos      __attribute__ ((packed));
  uint8_t  DirectColorModeInfo  __attribute__ ((packed));
  uint32_t  PhysBasePtr          __attribute__ ((packed));
} VBEModeInfoBlock;
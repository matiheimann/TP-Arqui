extern void paintPixelAt(int x, int y);
extern int XResolution();
extern int YResolution();

void paintPixel(int x, int y) { paintPixelAt(x, y); }

int xres() { return XResolution(); }

int yres() { return YResolution(); }
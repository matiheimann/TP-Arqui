#include <graphiclib.h>
#include <plotter.h>

void cuadratic(double grade0, double grade1, double grade2){
	paintAxis();
	for(double x = -300; x <= 300; x += 0.01){
		double y =grade2* x*x + grade1 * x + grade0;
		int xPainted = x * 100;
		int yPainted = y * 100;
		paintPixelAt(xres()/2 + xPainted, yres()/2 - yPainted);
	}
}

void paintAxis(){
	for(int i = 0; i < yres() ; i++)
		paintPixelAt(xres()/2,i);
	for(int i = 0; i < xres() ; i++)
		paintPixelAt(i,yres()/2);

}

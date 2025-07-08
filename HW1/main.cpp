#include <iostream>
#include "BMP.h"
#include <cmath>
using namespace std;

//duplicates arc using symetry
void writeEllipse(int x, int y, int xc, int yc, struct BMP *bmpNew) {
    //midpoint ellipse algorithm uses 4-way symmentry
    bmpNew->set_pixel(xc - x, yc - y, 255, 255, 255, 0); // quadrant 3 (-x, -y)
    bmpNew->set_pixel(xc + x, yc - y, 255, 255, 255, 0); // quadrant 4 (+x, -y)
}
//calculates ellipse
void midpointEllipse(int a, int b, struct BMP *bmpNew) {
    long int x = 0;
    long int y = b;

    //Region 1 init val dStart = f(x0+1, y0-0.5) = (b^2*1^2) + a^2(b - 0.5) - (a^2*b^2) => b^2 + a^2/4 - a^2*b
    long int a2 = pow(a, 2);
    long int b2 = pow(b, 2);
    // gradient f(x,y) =(∂f/∂x)i + (∂f/∂y)j  => 2*b^2*x*î + 2*a^2*y*ĵ
    long int dx = 2 * b2 * x;
    long int dy = 2 * a2 * y;
    long int d = b2 - a2 * b + a2 / 4;
    int xc = 400;
    int yc = 400;
    //tangleine line slope at curve = -1, region 1 if m > -1 else region 2 if m < -1
    // Region 1:  î < ĵ
    while (dx <= dy){
        writeEllipse(x, y, xc, yc, bmpNew);

        // midpoint = (xp+1, yp-0.5)
        // if d < 0, you will choose 'E', else choose 'SE' & ΔE/ΔSE = dNew - dOld
        x++;
        dx += 2 * b2;
        if(d < 0){
            d += dx + b2; // ΔE = b^2 (2xp + 3)
        }else{
            y--;
            dy -= 2 * a2; // ΔSE = b^2 (2xp + 3) + a^2(-2yp + 2)
            d += dx - dy + b2;
        }  
    }

    // Region 2: if 2*b^2(xp+1) >= 2*a^2(yp-0.5) True
     // dOld = f(xi+0.5, yi-1) = b^2(xi+0.5)^2 + a^2(yi-1)^2 - a^2*b^2
    long int d_Old = b2 * pow(x + 0.5,2) + a2 * pow(y - 1,2) - a2 * b2;
    
    while(y >= 0){
        writeEllipse(x, y, xc, yc, bmpNew);
    //midpoint = f(xi + 0.5, yi - 1)
    // if d < 0 choose 'SE', else if d >= 0 choose 'S' & ΔS/ΔSE = dNew - dOld
        y--;
        dy -= 2 * a2;
        if (d_Old >= 0){
            d_Old += a2 - dy; //ΔS = a^2(-2y + 3)
        } else{ 
            x++;
            dx += 2 * b2; //ΔSE = b^2(2x + 2) + a^2(-2y + 3)
            d_Old += dx + a2 - dy;
        }
    }
}
    

int main() {
    int a = 800;
    int b = 800;
    BMP bmpNew(a,b,false);
    bmpNew.fill_region(0, 0, a, b, 0, 0, 0, 0);
    // for(int i=0;i<bmpNew.bmp_info_header.width;i++)
    // {
    //     bmpNew.set_pixel(i, b/2+1, 255, 255, 255, 0);
    // }

    //midpointEllipse(a, b, &bmpNew);
    midpointEllipse(216, 384, &bmpNew);

    bmpNew.write("output.bmp");


}

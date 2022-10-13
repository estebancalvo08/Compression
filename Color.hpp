#pragma once

class Color
{
    private:
    int R, G, B, RGB;
    int Y, Cb, Cr, YCbCr;

    public:
    void setR(int r);
    void setG(int g);
    void setB(int b);
    int getR() {return R;}
    int getG() {return G;}
    int getB() {return B;}
    int getRGB(){return RGB;};
    void setRGB(int r, int g, int b);
    void setRGB(int RGB);


    void setY(int Y);
    void setCb(int Cb);
    void setCr(int Cr);
    void setYCbCr(int Y, int Cb, int Cr);
    int getY() {return Y;}
    int getCb() {return Cb;}
    int getCr() {return Cr;}
    int getYCbCr(){return YCbCr;}
    void toYCbCr();
    void RGBtoYCbCr();
    void YCbCrtoRGB();
    Color();
    Color(int r,int g, int b);
    //~Color();

};

Color::Color(int r,int g, int b)
{
    setRGB(r,g,b);
}

Color::Color()
{
    R = 0; G = 0; B = 0; RGB = 0;
}

void Color::setR(int r) 
{
    R = r >= 255 ? 255 : r; 
    RGB = (r << 16) | (getG() << 8) | getB();
};

void Color::setG(int g)
{
    G = g >= 255 ? 255 : g;  
    RGB = (getR() << 16) | (g << 8) | getB();
};
void Color::setB(int b)
{
    B = b >= 255 ? 255 : b; 
    RGB = (getR() << 16) | (getG() << 8) | b;
}
void Color::setRGB(int r, int g, int b)
{
    setR(r); setG(g); setB(b);
}

void Color::setY(int Y)
{
    this->Y = Y >= 255 ? 255 : Y;
    YCbCr = (Y << 16) | (getCb() << 8) | getCr();
}
void Color::setCb(int Cb)
{
    this->Cb = Cb >= 255 ? 255 : Cb;
    YCbCr = (getY() << 16) | (Cb << 8) | getCr();
}
void Color::setCr(int Cr)
{
    this->Cr = Cr >= 255 ? 255 : Cr;
    YCbCr = (Y << 16) | (getCb() << 8) | Cr;
}
void Color::setYCbCr(int Y, int Cb, int Cr)
{
    setY(Y); setCb(Cb); setCr(Cr);
}
void Color::RGBtoYCbCr()
{
    Y = 16 + 65.738*R/256 + 129.057*G/256 + 25.064*B/256;
    Cb = 128 - 37.945*R/256 - 74.494*G/256 + 112.439*B/256;
    Cr = 128 + 112.439*R/256 - 94.154*G/256 - 18.285*B/256;
    setRGB(Y, Cb, Cr);
}
void Color::YCbCrtoRGB()
{
    R = 298.082*Y/256 + 408.583 * Cr/256 - 222.921;
    G = 298.082*Y/256 -100.291*Cb/256 - 208.120*Cr/256 + 135.576;
    B = 298.082*Y/256 + 516.412*Cb/256 - 276.836;
    setRGB(R, G, B);
}
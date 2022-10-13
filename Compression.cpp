#include "Compression.hpp"
int main()
{
    vector<vector<Color>> map;
    vector<string> properties = readImage("apollo.ppm", map);
    vector<vector<vector<int>>> res = toYCbCr(map);
    toDCT(res[0]);
    outputImage("newImage.ppm",map, properties);
}

vector<string> readImage(string name, vector<vector<Color>>& map)
{
    ifstream image;
    image.open(name);
    string type, width, height, RGB;
    image >> type >> width >> height >> RGB;
    vector<string> properties{type, width, height, RGB};
    map.resize(stoi(height), vector<Color>(stoi(width)));
    int r=0,g=0,b=0,i = -1, j = 0, heightI = map.size(), widthI = map[0].size();
    string red = "", green = "", blue = "";
    while(!image.eof())
   {
        if(j % widthI == 0)
        {
            i++;
             if(i >= 480)
                 i = 479;
            j = 0;
        }
        image >> red >> green >> blue;
        stringstream redstream(red);
        stringstream bluestream(blue);
        stringstream greenstream(green);
        redstream >> r;
        greenstream >> g;
        bluestream >> b;
        Color color(r,g,b);
        map[i][j] = color;
        j++;
   }
   image.close();
   return properties;
}
vector<vector<vector<int>>> toYCbCr(vector<vector<Color>>& map)
{
    //Vector of Vectors with Y, Cb and Cr
    vector<vector<vector<int>>> res(3 , vector<vector<int>>(map.size(), vector<int>(map[0].size())));
    for(int i = 0; i < map.size(); i++)
    {
        for(int j = 0; j < map[i].size(); j++)
        {
            map[i][j].RGBtoYCbCr();
            //Vector with Y value matrix
            res[0][i][j] = map[i][j].getR();
            //Vector with Cb value matrix
            res[1][i][j] = map[i][j].getG();
            //Vector with Cr value matrix
            res[2][i][j] = map[i][j].getB();
        }
    }
    return res;
}

void toDCT(vector<vector<int>>& map)
{
     for(int i = 0; i < map.size(); i++)
    {
        for(int j = 0; j < map[i].size(); j++)
        {
            if(i % 8 == 0 && j % 8 == 0 && i + 8 <= map.size() && j +8 <= map[i].size())
            {
                DCTFunction(map, i, j);
            }
        }
    }
}
void DCTFunction(vector<vector<int>>& map, int row, int col)
{
    float ci, cj, dct1, sum;        
    for(int i = row; i < row + 8; i++)
    {
        for(int j = col; j < col + 8; j++)
        {
            map[i][j] -=  128;
            if (i % 8== 0)
                ci = 1 / sqrt(8);
            else
                ci = sqrt(2) / sqrt(8);
            if (j % 8 == 0)
                cj = 1 / sqrt(8);
            else
                cj = sqrt(2) / sqrt(8);
                sum = 0;
            for (int k = 0; k < 8 ; k++) {
                for (int l = 0; l < 8 ; l++) {
                    dct1 = map[k+row][l+col] *
                           cos((2 * k + 1) * i * pi / (2 * 8)) *
                           cos((2 * l + 1) * j * pi / (2 * 8));
                    sum = sum + dct1;
                }
            }
            map[i][j] = ci * cj * sum / Quantization[i % 8][j % 8];
        }
    }
}
void outputImage(string name, vector<vector<Color>>& map, vector<string> properties)
{
    ofstream newImage;
    newImage.open("newImage.ppm");
    newImage << properties[0] << "\n" << properties[1] << " " << properties[2] << endl << properties[3] << endl;
    for(int i = 0; i < map.size(); i++)
    {
        for(int j = 0; j < map[i].size(); j++)
        {
            newImage << (map[i][j].getR()) << " " << (map[i][j].getR()) << " " << (map[i][j].getR()) << endl;
        }
    }
   newImage.close();
}


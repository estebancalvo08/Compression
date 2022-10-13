#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include "Compression.hpp"
#include "Color.hpp"
using namespace std;
#define pi 3.1415
vector<vector<int>> Quantization{
{16,  11,  10,  16,  24,   40,   51,   61},
{12,  12,  14,  19,  26,   58,   60,   55},   
{14,  13,  16,  24,  40,   57,   69,   56},   
{14,  17,  22,  29,  51,   87,   80,   62},   
{18,  22,  37,  56,  68,   109,  103,  77},   
{24,  35,  55,  64,  81,   104,  113,  92}, 
{49,  64,  78,  87,  103,  121,  120,  101}, 
{72,  92,  95,  98,  112,  100,  103,  99}};   
vector<string> readImage(string name, vector<vector<Color>>& map);
vector<vector<vector<int>>> toYCbCr(vector<vector<Color>>& map);
void toDCT(vector<vector<int>>& map, bool Y);
void DCTFunction(vector<vector<int>>& map, int row, int col, bool Y);
void outputImage(string name, vector<vector<Color>>& map, vector<string> properties);
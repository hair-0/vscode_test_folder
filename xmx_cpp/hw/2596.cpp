//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1383&pid=2596&isOOP=false
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdint>
#include <algorithm>

using namespace std;

#pragma pack(push, 1) 
typedef struct {
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t data_offset;
} BMPFileHeader;

typedef struct {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMPInfoHeader;
#pragma pack(pop)

int main() {
    ifstream file("image.bmp", ios::binary);
    if (!file) {
        cerr << "Error: 无法打开 image.bmp" << endl;
        return 1;
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    file.read((char*)&fileHeader, sizeof(BMPFileHeader));
    file.read((char*)&infoHeader, sizeof(BMPInfoHeader));

    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    int dataSize = width * height * 3;

    vector<uint8_t> pixelData(dataSize);
    
    file.seekg(fileHeader.data_offset, ios::beg);
    file.read((char*)pixelData.data(), dataSize);
    file.close();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            
            int index = (y * width + x) * 3;
            bool keepPixel = false; 

            if (height == 100) {
                double cx = width / 2.0;
                double cy = height / 2.0;
                double r = min(width, height) / 2.0;
                double distSq = pow(x - cx, 2) + pow(y - cy, 2);
                
                if (distSq <= r * r) keepPixel = true;

            } else if (height == 200) {
                double cx = width / 2.0;
                double cy = height / 2.0;
                double r = min(width, height) / 2.0;
                double distSq = pow(x - cx, 2) + pow(y - cy, 2);
                
                if (distSq > r * r) keepPixel = true;

            } else if (height == 300) {
                if (x >= width / 2 && x <= width && y >= height / 2 && y <= height) {
                    keepPixel = true;
                }

            } else if (height == 400) {
                if (x >= width / 4 && x <= 3 * width / 4 && 
                    y >= height / 4 && y <= 3 * height / 4) {
                    keepPixel = true;
                }

            } else if (height == 500) {
                double k = (double)height / width;
                double D = min(width, height) / 10.0;
                
                double d_val = abs(k * x - y) / sqrt(k * k + 1.0);
                
                if (d_val <= D / 2.0) {
                    keepPixel = true;
                }
            }

            if (!keepPixel) {
                pixelData[index]     = 0; 
                pixelData[index + 1] = 0;
                pixelData[index + 2] = 0;
            }
        }
    }

    ofstream outFile("output.bmp", ios::binary);
    if (!outFile) {
        cerr << "Error" << endl;
        return 1;
    }

    outFile.write((char*)&fileHeader, sizeof(BMPFileHeader));
    outFile.write((char*)&infoHeader, sizeof(BMPInfoHeader));
    outFile.write((char*)pixelData.data(), dataSize);

    outFile.close();


    return 0;
}
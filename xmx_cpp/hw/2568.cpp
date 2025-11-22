#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;

#pragma pack(push, 1)
typedef struct {
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t data_offset;
} BMPFileHeader;
#pragma pack(pop)

typedef struct {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMPInfoHeader;

int main() {
    ifstream fin("image.bmp", ios::binary);
    if (!fin) return 0;

    BMPFileHeader fileHeader;
    fin.read((char*)&fileHeader, sizeof(fileHeader));

    if (fileHeader.signature == 0x4D42) {
        BMPInfoHeader infoHeader;
        fin.read((char*)&infoHeader, sizeof(infoHeader));

        ofstream fout("image_info.txt");
        fout << "image size " << infoHeader.biWidth << " * " << infoHeader.biHeight << " pixels" << endl;
        fout << "data size " << infoHeader.biSizeImage << " bytes" << endl;
        fout << "file size " << fileHeader.file_size << " bytes" << endl;
        fout.close();
    }

    fin.close();
    return 0;
}
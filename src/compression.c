#include "compression.h"

//Compress from binary image stores as chars to packes bits
void compressBinaryImage(
    unsigned char (*in_image_buffer)[BMP_HEIGTH],
    unsigned char (*out_image_buffer)[BMP_HEIGTH / 8 + 1])
{
    for (unsigned short i = 0; i < BMP_HEIGTH; i++)
    {   
        for (unsigned short j = 0; j < BMP_HEIGTH; j++)
        {
            if (in_image_buffer[i][j])
            {
                out_image_buffer[i][j / 8] |= (0x01 << j%8);
            }
        }
    }
}

unsigned char getValue(
    unsigned char (*compressedImage)[BMP_HEIGTH / 8 + 1],
    unsigned short index1,
    unsigned short index2)
{
    return (compressedImage[index1][index2 / 8] >> index2%8) & 0x01;
}

void setValue(
    unsigned char (*compressedImage)[BMP_HEIGTH / 8 + 1],
    unsigned short index1,
    unsigned short index2,
    unsigned char value)

{
    //1 to start with the byte 00000001
    //(1 << index%8 shifts the 1 in 00000001 to desired position for masking
    if (value)
    {                                                             //if we want to set the pixel to 1
        compressedImage[index1][index2 / 8] |= (0x01 << index2 % 8); //set nth bit with | mask
    }
    else
    {
        compressedImage[index1][index2 / 8] &= ~(0x01 << index2 % 8); //negates the mask, so we set only the selected to 0
    }
}

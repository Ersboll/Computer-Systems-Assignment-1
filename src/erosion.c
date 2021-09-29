#include "erosion.h"

int erosion(unsigned char (*in_image_buffer)[BMP_HEIGTH / 8 + 1],
            unsigned char (*out_image_buffer)[BMP_HEIGTH / 8 + 1])
{
  unsigned int erosionCount = 0;

  for (int i = 0; i < BMP_WIDTH; i++)
  {
    for (int j = 0; j < BMP_HEIGTH; j++)
    {
      if (!getValue(in_image_buffer, i, j))
      { // == 0'
        setValue(out_image_buffer, i, j, 0);
      }
      else
      { // != 
        if (i == 0 || i == BMP_WIDTH - 1 || j == 0 ||
            j == BMP_HEIGTH - 1)
        { // are we on the edge?
          setValue(out_image_buffer, i, j, 0);
          erosionCount++;
        }
        else if (getValue(in_image_buffer, i - 1, j) && getValue(in_image_buffer, i + 1, j) &&
                 getValue(in_image_buffer, i, j - 1) && getValue(in_image_buffer, i, j + 1))
        {
          setValue(out_image_buffer, i, j, 1);
        }
        else
        {
          setValue(out_image_buffer, i, j, 0);
          erosionCount++;
        }
      }
    }
  }

  return erosionCount;
}
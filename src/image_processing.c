#include "image_processing.h"
#include "compression.h"
#include <stdio.h>

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

// Returns 1 if white pixel is detected in the exclusion frame else 0
int _exclusion(short int x, short int y,
               unsigned char (*in_image_buffer)[BMP_HEIGTH / 8 + 1])
{
  int exclude = 0;
  short int xmin, xmax, ymin, ymax;
  _getXandYmaxmin(x, y, &xmin, &xmax, &ymin, &ymax);

  for (int i = xmin; i <= xmax; i++)
  {
    if (exclude)
      break;

    exclude = exclude || getValue(in_image_buffer,x + i, y + ymax) ||
              getValue(in_image_buffer, x + i, y + ymin);
  }

  for (int i = ymin; i <= ymax; i++)
  {
    if (exclude)
      break;

    exclude = exclude || getValue(in_image_buffer, x + xmax, y + i) ||
              getValue(in_image_buffer, x + xmin, y + i);
  }

  return exclude;
}

// Returns 1 if a white pixel is found in the detection area else 0
int _detection(short int x, short int y,
               unsigned char (*in_image_buffer)[BMP_HEIGTH / 8 + 1])
{
  int detected = 0;

  short int xmin, xmax, ymin, ymax;
  _getXandYmaxmin(x, y, &xmin, &xmax, &ymin, &ymax);

  xmin++;
  ymin++;
  xmax--;
  ymax--;

  for (int i = xmin; i <= xmax; i++)
  {
    for (int j = ymin; j <= ymax; j++)
    {
      if (getValue(in_image_buffer, i + x, j + y))
      {
        detected = 1;
        break;
      }
    }
    if (detected)
      break;
  }
  return detected;
}

void _whipeCell(short int x, short int y,
                unsigned char (*out_image_buffer)[BMP_HEIGTH / 8 + 1])
{
  short int xmin, xmax, ymin, ymax;
  _getXandYmaxmin(x, y, &xmin, &xmax, &ymin, &ymax);
  xmin++;
  ymin++;
  xmax--;
  ymax--;
  for (short int i = xmin; i <= xmax; i++)
  {
    for (short int j = ymin; j <= ymax; j++)
    {
      setValue(out_image_buffer, x + i, y + j, 0);
    }
  }
}

void _getXandYmaxmin(short int x, short int y, short int *xmin, short int *xmax,
                     short int *ymin, short int *ymax)
{
  *xmin = -6;
  *xmax = 7;
  *ymin = -6;
  *ymax = 7;

  if (x < 6)
  {
    *xmin = -x;
  }
  if (x > BMP_WIDTH - 1 - *xmax)
  {
    *xmax = BMP_WIDTH - 1 - x;
  }

  if (y < 6)
  {
    *ymin = -y;
  }
  if (y > BMP_HEIGTH - 1 - *ymax)
  {
    *ymax = BMP_HEIGTH - 1 - y;
  }
}
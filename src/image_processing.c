#include "image_processing.h"
#include "compression.h"


// Returns 1 if white pixel is detected in the exclusion frame else 0
int _exclusion(short x, short y,
               unsigned char (*in_image_buffer)[BMP_HEIGTH / 8 + 1])
{
  int exclude = 0;
  short xmin, xmax, ymin, ymax;
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
int _detection(short x, short y,
               unsigned char (*in_image_buffer)[BMP_HEIGTH / 8 + 1])
{
  int detected = 0;

  short xmin, xmax, ymin, ymax;
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

void _whipeCell(short x, short y,
                unsigned char (*out_image_buffer)[BMP_HEIGTH / 8 + 1])
{
  short xmin, xmax, ymin, ymax;
  _getXandYmaxmin(x, y, &xmin, &xmax, &ymin, &ymax);
  xmin++;
  ymin++;
  xmax--;
  ymax--;
  for (short i = xmin; i <= xmax; i++)
  {
    for (short j = ymin; j <= ymax; j++)
    {
      setValue(out_image_buffer, x + i, y + j, 0);
    }
  }
}

void _getXandYmaxmin(short x, short y, short *xmin, short *xmax,
                     short *ymin, short *ymax)
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
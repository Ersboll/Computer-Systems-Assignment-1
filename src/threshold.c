#include "threshold.h"

// Does binary thresholding on the input image, writes to the output image
// buffer
// The method used (either OTSU or just a constant) is defined in env.h
void binary_threshold(unsigned char (*image_buffer)[BMP_HEIGTH]) {

#if THRESHOLDING_METHOD == OTSU
  unsigned char threshold = _otsu(in_image_buffer);
#else
  unsigned char threshold = BINARY_THRESHOLD_VALUE;
#endif

#if DEBUGGING
  printf("Threshold: %d\n", threshold);
#endif

  for (int i = 0; i < BMP_WIDTH; i++) {
    for (int j = 0; j < BMP_HEIGTH; j++) {
      image_buffer[i][j] = image_buffer[i][j] > threshold ? 255 : 0;
    }
  }
}

#if THRESHOLDING_METHOD == OTSU

// Compute the histogram used in the otsu method
// Write the histogram in the histogram array
// Takes also the image buffer to create the histogram from
void _compute_histogram(unsigned int *histogram,
                        unsigned char (*image_buffer)[BMP_HEIGTH]) {
  memset(histogram, 0, HISTOGRAM_SIZE);

#if DEBUGGING
  printf("creating histogram\n");
#endif
  for (unsigned short i = 0; i < HISTOGRAM_SIZE; i++) {
    histogram[i] = 0;
  }

  for (unsigned short i = 0; i < BMP_WIDTH; i++) {
    for (unsigned short j = 0; j < BMP_HEIGTH; j++) {
      histogram[image_buffer[i][j]]++;
    }
  }
}

#endif // THRESHOLDING_METHOD == OTSU || THRESHOLDING_METHOD ==
       // MAXIMUM_DEVIATION

#if THRESHOLDING_METHOD == OTSU

// Otsu's method
// Input argument is a 256x256 grayscale image
// output is the threshold in range [0;255]
// Based on the java implementation:
// http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
unsigned char _otsu(unsigned char (*image_buffer)[BMP_HEIGTH]) {
  unsigned int histogram[HISTOGRAM_SIZE];
  // bzero(histogram, HISTOGRAM_SIZE);
  _compute_histogram(histogram, image_buffer);

  double sum = 0.0;

  // Auxilary value for computing m2
  for (unsigned short i = 0; i < HISTOGRAM_SIZE; i++) {
    sum += i * histogram[i];
  }

  float sum_b = 0.0;
  long q1 = 0;
  long q2 = 0;
  float var_max = 0;
  unsigned char threshold = 0;
  for (unsigned short i = 0; i < HISTOGRAM_SIZE; i++) {
    q1 += histogram[i];
    if (q1 == 0)
      continue;
    q2 = BMP_WIDTH * BMP_HEIGTH - q1;

    if (q2 == 0)
      break;

    // update m1 and m2
    sum_b += (float)(i * (int)histogram[i]);
    float m1 = sum_b / q1;
    float m2 = (sum - sum_b) / q2;

    float var_between = (float)q1 * (float)q2 * (m1 - m2) * (m1 - m2);

    if (var_between > var_max) {
      var_max = var_between;
      threshold = i;
    }
  }

  return threshold;
}

#endif // THRESHOLDING_METHOD == OTSU
#include "threshold.h"

void binary_threshold(unsigned char (*in_image_buffer)[BMP_HEIGTH],
                      unsigned char (*out_image_buffer)[BMP_HEIGTH]) {

#if THRESHOLDING_METHOD == OTSU
  unsigned char threshold = _otsu(in_image_buffer);
#elif THRESHOLDING_METHOD == MAXIMUM_DEVIATION
  unsigned char threshold = _maximum_deviation(in_image_buffer);
#else
  unsigned char threshold = BINARY_THRESHOLD_VALUE;
#endif

#if DEBUGGING
  printf("Threshold: %d\n", threshold);
#endif

  for (int i = 0; i < BMP_WIDTH; i++) {
    for (int j = 0; j < BMP_HEIGTH; j++) {
      out_image_buffer[i][j] = in_image_buffer[i][j] > threshold ? 255 : 0;
    }
  }
}

#if THRESHOLDING_METHOD == OTSU || THRESHOLDING_METHOD == MAXIMUM_DEVIATION

void _compute_histogram(unsigned short *histogram,
                        unsigned char (*in_image_buffer)[BMP_HEIGTH]) {
  memset(histogram, 0, HISTOGRAM_SIZE);

#if DEBUGGING
  printf("creating histogram\n");
#endif
  for (unsigned short i = 0; i < BMP_WIDTH; i++) {
    for (unsigned short j = 0; j < BMP_HEIGTH; j++) {
      histogram[in_image_buffer[i][j]]++;
    }
  }
}

#endif // THRESHOLDING_METHOD == OTSU || THRESHOLDING_METHOD ==
       // MAXIMUM_DEVIATION

#if THRESHOLDING_METHOD == OTSU
// Otsu's method
// Input argument is a 256x256 grayscale image
// output is the threshold in range [0;255]

unsigned char _otsu(unsigned char (*in_image_buffer)[BMP_HEIGTH]) {
  unsigned short histogram[HISTOGRAM_SIZE];
  _compute_histogram(histogram, in_image_buffer);
  unsigned char threshold;

  float sum = 0.0;
  float sum_b = 0.0;
  unsigned short q1 = 0;
  unsigned short q2 = 0;
  float var_max = 0;
  float m1, m2, var_between;

  // Auxilary value for computing m2
  for (unsigned short i = 0; i < HISTOGRAM_SIZE; i++) {
    sum += i * (int)histogram[i];
  }

  for (unsigned short i = 0; i < HISTOGRAM_SIZE; i++) {
    q1 += histogram[i];
    if (q1 == 0)
      continue;
    q2 = BMP_WIDTH * BMP_HEIGTH - q1;

    if (q2 == 0)
      break;

    // update m1 and m2
    sum_b += (float)(i * (int)histogram[i]);
    m1 = sum_b / q1;
    m2 = (sum - sum_b) / q2;

    var_between = (float)q1 * (float)q2 * (m1 - m2) * (m1 - m2);

    if (var_between > var_max) {
      var_max = var_between;
      threshold = i;
    }
  }

  return threshold;
}
#endif // THRESHOLDING_METHOD == OTSU

#if THRESHOLDING_METHOD == MAXIMUM_DEVIATION
unsigned char _maximum_deviation(unsigned char (*in_image_buffer)[BMP_HEIGTH]) {

  unsigned short histogram[HISTOGRAM_SIZE];
  unsigned char threshold;

  _compute_histogram(histogram, in_image_buffer);

  unsigned char peak_location = 0;
  unsigned long peak_value = 0;

  for (unsigned short i = 0; i < HISTOGRAM_SIZE; i++) {
    if (histogram[i] >= peak_value) {
      peak_location = i;
      peak_value = histogram[i];
    }
  }

  // maximum deviation
  float maximum_deviation, val;
  for (unsigned short i = peak_location + 1; i < HISTOGRAM_SIZE; i++) {
    val = (float)(HISTOGRAM_SIZE - i) / (HISTOGRAM_SIZE - peak_location) *
              peak_value -
          histogram[i];
    if (val > maximum_deviation) {
      maximum_deviation = val;
      threshold = i;
    }
  }

  return threshold;
}
#endif
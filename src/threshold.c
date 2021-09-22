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

#if THRESHOLDING_METHOD == OTSU

// Otsu's method
// Input argument is a 256x256 grayscale image
// output is the threshold in range [0;255]
unsigned char _otsu(unsigned char (*in_image_buffer)[BMP_HEIGTH]) {

  unsigned short histogram[HISTOGRAM_SIZE];
  unsigned char threshold;

  memset(histogram, 0, sizeof(histogram));

#if DEBUGGING
  printf("creating histogram\n");
#endif
  for (unsigned short i = 0; i < BMP_WIDTH; i++) {
    for (unsigned short j = 0; j < BMP_HEIGTH; j++) {
      histogram[in_image_buffer[i][j]]++;
    }
  }

#if DEBUGGING
  printf("calculating sum1\n");
#endif

  double sum1 = 0;
  for (unsigned short i = 0; i < HISTOGRAM_SIZE; i++) {
    sum1 += i * histogram[i];
  }

  double sumB = 0.0;
  long wB = 0;
  long wF = 0;

#if DEBUGGING
  printf("otsu\n");
#endif
  double mF, mB, val, maximum;
  for (unsigned short i = 0; i < HISTOGRAM_SIZE; i++) {
    // Background weight
    wB += histogram[i];
    if (wB == 0)
      continue;

    // Forground weight
    wF = BMP_WIDTH * BMP_HEIGTH - wB;
    if (wF == 0)
      break;

    sumB += i * histogram[i];

    if (wB > 0 && wF > 0) {
      mF = (sum1 - sumB) / wF;
      mB = sumB / wB;
      val = wB * wF * (mB - mF) * (mB - mF);

      if (val > maximum) {
        maximum = val;
        threshold = i;
      }
    }
  }

  return threshold;
}

#endif // THRESHOLDING_METHOD == OTSU

#if THRESHOLDING_METHOD == MAXIMUM_DEVIATION
unsigned char _maximum_deviation(unsigned char (*in_image_buffer)[BMP_HEIGTH]) {

  unsigned short histogram[HISTOGRAM_SIZE];
  unsigned char threshold;

  memset(histogram, 0, sizeof(histogram));

#if DEBUGGING
  printf("creating histogram\n");
#endif
  for (unsigned short i = 0; i < BMP_WIDTH; i++) {
    for (unsigned short j = 0; j < BMP_HEIGTH; j++) {
      histogram[in_image_buffer[i][j]]++;
    }
  }

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
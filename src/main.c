#include "main.h"

// Function to swap two numbers
void swap(char *x, char *y) {
  char t = *x;
  *x = *y;
  *y = t;
}

// Function to reverse `buffer[i…j]`
char *reverse(char *buffer, int i, int j) {
  while (i < j) {
    swap(&buffer[i++], &buffer[j--]);
  }

  return buffer;
}

// Iterative function to implement `itoa()` function in C
char *itoa(int value, char *buffer, int base) {
  // invalid input
  if (base < 2 || base > 32) {
    return buffer;
  }

  // consider the absolute value of the number
  int n = abs(value);

  int i = 0;
  while (n) {
    int r = n % base;

    if (r >= 10) {
      buffer[i++] = 65 + (r - 10);
    } else {
      buffer[i++] = 48 + r;
    }

    n = n / base;
  }

  // if the number is 0
  if (i == 0) {
    buffer[i++] = '0';
  }

  // If the base is 10 and the value is negative, the resulting string
  // is preceded with a minus sign (-)
  // With any other base, value is always considered unsigned
  if (value < 0 && base == 10) {
    buffer[i++] = '-';
  }

  buffer[i] = '\0'; // null terminate string

  // reverse the string and return it
  return reverse(buffer, 0, i - 1);
}

// Main function
int main(int argc, char **argv) {
  // Declaring the array to store the image (unsigned char = unsigned 8 bit)
  unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
  unsigned char binary_image_0[BMP_WIDTH][BMP_HEIGTH];
  unsigned char binary_image_1[BMP_WIDTH][BMP_HEIGTH];
  unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
  unsigned short int detected_cells[MAX_CELL_COUNT][2];
  unsigned short int buffer_list_cells[MAX_CELL_COUNT][2];

  unsigned short int(*buffer_list_cells_buffer)[2] = buffer_list_cells;
  unsigned char(*in_image_buffer)[BMP_HEIGTH] = binary_image_0;
  unsigned char(*out_image_buffer)[BMP_HEIGTH] = binary_image_1;
  unsigned char(*temp_buffer)[BMP_HEIGTH] = NULL;

  // argc counts how may arguments are passed
  // argv[0] is a string with the name of the program
  // argv[1] is the first command line argument (input image)
  // argv[2] is the second command line argument (output image)

  // Checking that 2 arguments are passed
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <output file path> <output file path>\n",
            argv[0]);
    exit(1);
  }

  // Load image from file
  printf("reading image\n");
  read_bitmap(argv[1], input_image);

  // printf("RGB 2 gray\n");
  rgb2gray(input_image, out_image_buffer);

  temp_buffer = in_image_buffer;
  in_image_buffer = out_image_buffer;
  out_image_buffer = temp_buffer;

  binaryThreshold(in_image_buffer, out_image_buffer);

  temp_buffer = in_image_buffer;
  in_image_buffer = out_image_buffer;
  out_image_buffer = temp_buffer;

  int i = 0;
  unsigned int detection_count = 0;
  int n = 0;
  while (erosion(in_image_buffer, out_image_buffer)) {
    printf("erosion: %d\n", ++i);
    temp_buffer = in_image_buffer;
    in_image_buffer = out_image_buffer;
    out_image_buffer = temp_buffer;
    n = detectCells(in_image_buffer, out_image_buffer,
                    buffer_list_cells_buffer);
    memcpy(detected_cells + detection_count, buffer_list_cells_buffer, n);
    detection_count += n;
    temp_buffer = in_image_buffer;
    in_image_buffer = out_image_buffer;
    out_image_buffer = temp_buffer;
  }
  printf("Finished detection:%u\n", detection_count);

  // gray2rgb(in_image_buffer, output_image);

  unsigned short int a[103][2] = {
      {9, 915},   {14, 83},   {27, 546},  {29, 430},  {34, 133},  {36, 256},
      {48, 306},  {49, 93},   {49, 273},  {59, 568},  {64, 694},  {72, 295},
      {75, 399},  {78, 757},  {82, 500},  {84, 142},  {86, 606},  {88, 222},
      {95, 32},   {97, 730},  {105, 259}, {123, 411}, {142, 203}, {148, 751},
      {152, 781}, {158, 241}, {176, 144}, {177, 890}, {200, 224}, {206, 426},
      {207, 924}, {210, 14},  {210, 826}, {217, 123}, {227, 896}, {237, 96},
      {237, 197}, {241, 444}, {244, 62},  {246, 602}, {260, 852}, {265, 232},
      {269, 895}, {275, 143}, {275, 808}, {318, 797}, {330, 617}, {333, 583},
      {342, 791}, {352, 16},  {354, 900}, {360, 55},  {374, 938}, {403, 879},
      {411, 25},  {430, 251}, {441, 897}, {459, 744}, {462, 174}, {473, 125},
      {487, 806}, {527, 761}, {543, 401}, {555, 604}, {556, 753}, {576, 774},
      {585, 741}, {610, 808}, {630, 185}, {650, 26},  {658, 706}, {660, 648},
      {689, 72},  {691, 401}, {697, 98},  {712, 861}, {713, 61},  {721, 745},
      {745, 921}, {751, 872}, {752, 704}, {794, 786}, {801, 678}, {808, 700},
      {815, 573}, {821, 516}, {843, 938}, {854, 727}, {860, 555}, {874, 918},
      {876, 111}, {877, 883}, {878, 787}, {879, 722}, {894, 551}, {911, 172},
      {920, 537}, {924, 455}, {924, 782}, {929, 602}, {933, 752}, {938, 73},
      {938, 151}};

  markCells(a, 103, input_image, output_image);

  // markCells(detected_cells, detection_count, input_image, output_image);

  // Save image to file
  write_bitmap(output_image, argv[2]);

  printf("Done!\n");
  return EXIT_SUCCESS;
}

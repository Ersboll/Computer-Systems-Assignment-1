#include "main.h"

// Main function
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char binary_image_0[BMP_WIDTH][BMP_HEIGTH/8];
unsigned char binary_image_1[BMP_WIDTH][BMP_HEIGTH/8];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned short int detected_cells[MAX_CELL_COUNT][2];
unsigned short int buffer_list_cells[MAX_CELL_COUNT][2];

unsigned short int (*buffer_list_cells_buffer)[2] = buffer_list_cells;
unsigned char (*in_image_buffer)[BMP_HEIGTH/8] = binary_image_0;
unsigned char (*out_image_buffer)[BMP_HEIGTH/8] = binary_image_1;
unsigned char (*temp_buffer)[BMP_HEIGTH/8] = NULL;


//Swaps pointers
void pointerSwap()
{
  temp_buffer = in_image_buffer;
  in_image_buffer = out_image_buffer;
  out_image_buffer = temp_buffer;
}

int main(int argc, char **argv)
{
  printf("We starting!");

#if TESTING
  clock_t start, end;
  double cpu_time_used;
  start = clock();
#endif
  // Declaring the array to store the image (unsigned char = unsigned 8 bit)
#if DEBUGGING
#ifdef __linux__
  char *file_names[20] = {
      "out/01.bmp", "out/02.bmp", "out/03.bmp", "out/04.bmp", "out/05.bmp",
      "out/06.bmp", "out/07.bmp", "out/08.bmp", "out/09.bmp", "out/10.bmp",
      "out/11.bmp", "out/12.bmp", "out/13.bmp", "out/14.bmp", "out/15.bmp",
      "out/16.bmp", "out/17.bmp", "out/18.bmp", "out/20.bmp"};
#else
  char *file_names[20] = {
      "out\\01.bmp", "out\\02.bmp", "out\\03.bmp", "out\\04.bmp", "out\\05.bmp",
      "out\\06.bmp", "out\\07.bmp", "out\\08.bmp", "out\\09.bmp", "out\\10.bmp",
      "out\\11.bmp", "out\\12.bmp", "out\\13.bmp", "out\\14.bmp", "out\\15.bmp",
      "out\\16.bmp", "out\\17.bmp", "out\\18.bmp", "out\\20.bmp"};
#endif
#endif
  // argc counts how may arguments are passed
  // argv[0] is a string with the name of the program
  // argv[1] is the first command line argument (input image)
  // argv[2] is the second command line argument (output image)

  // Checking that 2 arguments are passed
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <output file path> <output file path>\n",
            argv[0]);
    exit(1);
  }

// Load image from file
#if DEBUGGING
  printf("reading image\n");
#endif
  read_bitmap(argv[1], input_image);
#if DEBUGGING
  printf("RGB 2 gray\n");
#endif
  //temporary 950*950 array, only used here
  unsigned char rgb2g[BMP_WIDTH][BMP_HEIGTH];
  unsigned char(*big_buffer1)[BMP_HEIGTH] = rgb2g;
  unsigned char(*big_buffer2)[BMP_HEIGTH] = rgb2g;
  rgb2gray(input_image, big_buffer1);

  binaryThreshold(big_buffer1, big_buffer2);
  compressBinaryImage(big_buffer2, out_image_buffer);

  pointerSwap();

#if DEBUGGING
  int i = -1;
#endif

  unsigned int detection_count = 0;
  unsigned int n = 0;
  while (erosion(in_image_buffer, out_image_buffer))
  {
#if DEBUGGING
    printf("erosion: %d\n", ++i);
#endif
    pointerSwap();

#if DEBUGGING
    gray2rgb(in_image_buffer, output_image);
    write_bitmap(output_image, file_names[i]);
#endif

    n = detectCells(in_image_buffer, out_image_buffer,
                    buffer_list_cells_buffer);
    for (unsigned int j = 0; j < n; j++)
    {
      detected_cells[detection_count + j][0] = buffer_list_cells_buffer[j][0];
      detected_cells[detection_count + j][1] = buffer_list_cells_buffer[j][1];
    }
    memset(buffer_list_cells_buffer, 0, MAX_CELL_COUNT * 2);
    detection_count += n;
    pointerSwap();
  }
#if DEBUGGING
  printf("Finished detection:%u\n", detection_count);
#endif
  // gray2rgb(in_image_buffer, output_image);

  markCells(detected_cells, detection_count, input_image, output_image);
  // Save image to file
  write_bitmap(output_image, argv[2]);
#if TESTING
  end = clock();

  cpu_time_used = end - start;
  printf("%f", cpu_time_used * 1000.0 / CLOCKS_PER_SEC);
#endif
#if DEBUGGING
  printf("Done!\n");
#endif
  return EXIT_SUCCESS;
}

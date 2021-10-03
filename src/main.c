#include "main.h"
// gcc src/*.c -o runnable && ./runnable.exe example.bmp output.bmp
// Main function
unsigned char input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
unsigned char binary_image_0[BMP_WIDTH][BMP_HEIGTH / 8 + 1];
unsigned char binary_image_1[BMP_WIDTH][BMP_HEIGTH / 8 + 1];
unsigned char output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
// unsigned short detected_cells[MAX_CELL_COUNT][2];
unsigned char (*in_image_buffer)[BMP_HEIGTH / 8 + 1] = binary_image_0;
unsigned char (*out_image_buffer)[BMP_HEIGTH / 8 + 1] = binary_image_1;
unsigned char (*temp_buffer)[BMP_HEIGTH / 8 + 1] = NULL;

// Swaps pointers
void pointerSwap() {
  temp_buffer = in_image_buffer;
  in_image_buffer = out_image_buffer;
  out_image_buffer = temp_buffer;
}

int main(int argc, char **argv) {
#if DEBUGGING
  printf("We starting!");
#endif
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
  if (argc != 3) {
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

  convert_to_binary(out_image_buffer);

#if DEBUGGING
  printf("Finished compression\n");
#endif
  pointerSwap();

#if DEBUGGING
  int i = 0;
#endif

  cell_list_t *detected_cells = initialize_cell_list();
  if (!detected_cells) {
    printf("Error allocating memory for detected cells list\n");
    exit(EXIT_FAILURE);
  }

  while (erosion(in_image_buffer, out_image_buffer)) {
    pointerSwap();
#if DEBUGGING
    printf("erosion: %d\n", i++);
    gray2rgb(in_image_buffer, output_image);
    write_bitmap(output_image, file_names[i]);
#endif
    int res = detectCells(detected_cells, in_image_buffer, out_image_buffer);
    if (!res) {
      printf("Error adding cells to detected cells list\n");
      exit(EXIT_FAILURE);
    }
    pointerSwap();
  }

#if DEBUGGING
  printf("Finished detection:%u\n", detected_cells->count);
#endif

  markCells(detected_cells, input_image, output_image);

#if PRODUCTION
  // Save image to file
  print_results(detected_cells);
#endif
  write_bitmap(output_image, argv[2]);
#if TESTING
  end = clock();

  cpu_time_used = end - start;
  printf("%f %u\n", cpu_time_used * 1000.0 / CLOCKS_PER_SEC,
         detected_cells->count);
#endif

  destroy_cell_list(detected_cells);
#if DEBUGGING
  printf("Done!\n");
#endif
  return EXIT_SUCCESS;
}

// Used to contain the big buffer variables to a small scope, to minimize space
// used.
void convert_to_binary(unsigned char (*out_image_buffer)[BMP_HEIGTH / 8 + 1]) {

  unsigned char rgb2g[BMP_WIDTH][BMP_HEIGTH];
  unsigned char(*big_buffer1)[BMP_HEIGTH] = rgb2g;
  unsigned char(*big_buffer2)[BMP_HEIGTH] = rgb2g;
  rgb2gray(input_image, big_buffer1);

  binary_threshold(big_buffer1, big_buffer2);

  compressBinaryImage(big_buffer2, out_image_buffer);
}

#if PRODUCTION
void print_results(cell_list_t *cell_list) { //[MAX_CELL_COUNT]
  printf("Detected %u cells at:\n", cell_list->count);
  for (short i = 0; i < cell_list->count; i++) {
    printf("%u,%u\n", cell_list->list[i][0], cell_list->list[i][1]);
  }
}
#endif
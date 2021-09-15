#include "main.h"

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
  char *file_names[20] = {
      "out/1.bmp",  "out/2.bmp",  "out/3.bmp",  "out/4.bmp",  "out/5.bmp",
      "out/6.bmp",  "out/7.bmp",  "out/8.bmp",  "out/9.bmp",  "out/10.bmp",
      "out/11.bmp", "out/12.bmp", "out/13.bmp", "out/14.bmp", "out/15.bmp",
      "out/16.bmp", "out/17.bmp", "out/18.bmp", "out/20.bmp"};

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

  printf("RGB 2 gray\n");
  rgb2gray(input_image, out_image_buffer);

  temp_buffer = in_image_buffer;
  in_image_buffer = out_image_buffer;
  out_image_buffer = temp_buffer;

  binaryThreshold(in_image_buffer, out_image_buffer);

  temp_buffer = in_image_buffer;
  in_image_buffer = out_image_buffer;
  out_image_buffer = temp_buffer;

  int i = -1;
  unsigned int detection_count = 0;
  unsigned int n = 0;
  while (erosion(in_image_buffer, out_image_buffer)) {
    printf("erosion: %d\n", ++i);
    temp_buffer = in_image_buffer;
    in_image_buffer = out_image_buffer;
    out_image_buffer = temp_buffer;

    gray2rgb(in_image_buffer, output_image);
    write_bitmap(output_image, file_names[i]);

    n = detectCells(in_image_buffer, out_image_buffer,
                    buffer_list_cells_buffer);
    for (unsigned int j = 0; j < n; j++) {
      detected_cells[detection_count + j][0] = buffer_list_cells_buffer[j][0];
      detected_cells[detection_count + j][1] = buffer_list_cells_buffer[j][1];
    }
    memset(buffer_list_cells_buffer, 0, sizeof(buffer_list_cells_buffer));
    detection_count += n;
    temp_buffer = in_image_buffer;
    in_image_buffer = out_image_buffer;
    out_image_buffer = temp_buffer;
  }
  printf("Finished detection:%u\n", detection_count);

  // gray2rgb(in_image_buffer, output_image);

  markCells(detected_cells, detection_count, input_image, output_image);

  // for (short int i = 0; i < BMP_WIDTH; i++) {
  //   for (short int j = 0; j < BMP_HEIGTH; j++) {
  //     output_image[i][j][0] = input_image[i][j][0];
  //     output_image[i][j][1] = input_image[i][j][1];
  //     output_image[i][j][2] = input_image[i][j][2];
  //   }
  // }

  // output_image[0][0][0] = 255;
  // output_image[0][0][1] = 0;
  // output_image[0][0][2] = 0;

  // markCells(detected_cells, detection_count, input_image, output_image);

  // Save image to file
  write_bitmap(output_image, argv[2]);

  printf("Done!\n");
  return EXIT_SUCCESS;
}

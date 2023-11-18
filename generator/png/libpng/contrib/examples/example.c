#include <stdio.h>
#include <stdlib.h>
#include <png.h>

void read_png_file(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Could not open file %s for reading\n", filename);
        return;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fclose(fp);
        fprintf(stderr, "png_create_read_struct failed\n");
        return;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        fprintf(stderr, "png_create_info_struct failed\n");
        return;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
        fclose(fp);
        fprintf(stderr, "Error during init_io\n");
        return;
    }

    png_init_io(png_ptr, fp);
    png_read_info(png_ptr, info_ptr);

    int width = png_get_image_width(png_ptr, info_ptr);
    int height = png_get_image_height(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    // Optionally update the info here, if needed

    // Read the file into a PNG buffer
    png_read_update_info(png_ptr, info_ptr);
    png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png_ptr, info_ptr));
    }
    png_read_image(png_ptr, row_pointers);

    fclose(fp);

    // Writing the PNG data to a new file "b.png"
    FILE *fp_out = fopen("b.png", "wb");
    if (!fp_out) {
        fprintf(stderr, "Could not open file b.png for writing\n");
        return;
    }

    png_structp png_ptr_out = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr_out) {
        fclose(fp_out);
        fprintf(stderr, "png_create_write_struct failed\n");
        return;
    }

    png_infop info_ptr_out = png_create_info_struct(png_ptr_out);
    if (!info_ptr_out) {
        png_destroy_write_struct(&png_ptr_out, (png_infopp)NULL);
        fclose(fp_out);
        fprintf(stderr, "png_create_info_struct failed\n");
        return;
    }

    if (setjmp(png_jmpbuf(png_ptr_out))) {
        png_destroy_write_struct(&png_ptr_out, &info_ptr_out);
        fclose(fp_out);
        fprintf(stderr, "Error during init_io_out\n");
        return;
    }

    png_init_io(png_ptr_out, fp_out);
    png_set_IHDR(png_ptr_out, info_ptr_out, width, height, bit_depth, color_type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr_out, info_ptr_out);
    png_write_image(png_ptr_out, row_pointers);
    png_write_end(png_ptr_out, NULL);

    fclose(fp_out);

    // Clean up
    for (int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    png_destroy_write_struct(&png_ptr_out, &info_ptr_out);
}

int main() {
    read_png_file("a.png");
    return 0;
}

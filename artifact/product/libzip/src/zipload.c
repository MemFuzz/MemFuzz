#include <stdio.h>
#include <zip.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if(argc < 2)
    {
        printf("Need input\n");
        return 1;
    }
    // Open the source zip file for reading
    const char *srcZipFileName = argv[1];
    struct zip *srcZip = zip_open(srcZipFileName, ZIP_RDONLY, NULL);
    if (!srcZip) {
        perror("Failed to open source zip file");
        return 1;
    }

    // Create a new zip file for writing
    const char *destZipFileName = "/home/youwei/destination.zip";
    struct zip *destZip = zip_open(destZipFileName, ZIP_CREATE, NULL);
    if (!destZip) {
        perror("Failed to create destination zip file");
        zip_close(srcZip);  // Close the source zip file
        return 1;
    }

    // Get the number of entries in the source zip file
    int numEntries = zip_get_num_entries(srcZip, 0);

    for (int i = 0; i < numEntries; i++) {
        // Get the information about the entry in the source zip file
        struct zip_stat entryStat;
        zip_stat_init(&entryStat);
        zip_stat_index(srcZip, i, 0, &entryStat);

        // Open the entry in the source zip file
        struct zip_file *srcFile = zip_fopen_index(srcZip, i, 0);
        if (!srcFile) {
            perror("Failed to open source zip file entry");
            zip_close(srcZip);
            zip_close(destZip);
            return 1;
        }

        // Read the content of the source entry into a buffer
        char *buffer = NULL;
        buffer = (char *)malloc(entryStat.size);
        if(buffer == NULL)
            continue;
        zip_fread(srcFile, buffer, entryStat.size);

        // Add the entry to the destination zip file
        zip_source_t *source = zip_source_buffer(destZip, buffer, entryStat.size, 0);
        if(source != NULL)
            zip_file_add(destZip, entryStat.name, source, 0);
        // Clean up
        free(buffer);
        zip_fclose(srcFile);
    }

    // Close the zip files
    zip_close(srcZip);
    zip_close(destZip);

    printf("Zip file copied successfully.\n");

    return 0;
}

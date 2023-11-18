#include <stdio.h>
#include <zip.h>

int main(int argc, char** argv) {
    if(argc < 2)
    {
        printf("Need input\n");
        return 1;
    }
    // Open the existing zip file for read-write
    const char *zipFileName = argv[1];
    struct zip *zip = zip_open(zipFileName, ZIP_CREATE | ZIP_EXCL, NULL);
    if (!zip) {
        perror("Failed to open or create the zip file");
        return 1;
    }

    // Add a new entry to the zip file
    // const char *newEntryName = "new_entry.txt";
    // const char *newEntryContent = "This is the content of the new entry.";

    // struct zip_source *src = zip_source_buffer(zip, newEntryContent, strlen(newEntryContent), 0);
    // if (!src) {
    //     perror("Failed to create a zip source for the new entry");
    //     zip_close(zip);
    //     return 1;
    // }

    // int result = zip_file_add(zip, newEntryName, src, 0);
    // if (result < 0) {
    //     perror("Failed to add the new entry to the zip file");
    //     zip_source_free(src);
    //     zip_close(zip);
    //     return 1;
    // }

    // Close the zip file
    // zip_source_free(src);
    zip_close(zip);

    printf("New entry added to the zip file.\n");

    return 0;
}

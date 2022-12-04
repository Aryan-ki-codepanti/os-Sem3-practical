#include <stdio.h>

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("Not enough arguments");
        return -1;
    }

    FILE *source_file, *dest_file;
    char c;

    source_file = fopen(argv[1], "r");
    dest_file = fopen(argv[2], "w");

    if (source_file == NULL || dest_file == NULL)
    {
        printf("Error while processing these files");
        return -1;
    }

    while (!feof(source_file))
    {
        fprintf(dest_file, "%c", c);
        fscanf(source_file, "%c", &c);
    }

    fclose(source_file);
    fclose(dest_file);

    return 0;
}
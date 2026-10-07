#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: generate_dataset.exe <size> <output_file>\n");
        return 1;
    }

    long long n = atoll(argv[1]);
    const char *filename = argv[2];

    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Unable to create output file.\n");
        return 1;
    }

    for (long long i = 0; i < n; i++)
    {
        fprintf(file, "%.2f\n", (double)((i % 100) + 1));
    }

    fclose(file);

    printf("Dataset generated successfully.\n");
    printf("Elements: %lld\n", n);
    printf("File: %s\n", filename);

    return 0;
}

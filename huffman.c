#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FREQUENCY_TABLE_SIZE 128

typedef struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode *left, *right;
} HuffmanNode;

int* read_frequency_table(FILE *file);
int read_bitstream_length(FILE *file);
HuffmanNode* build_huffman_tree(int *freq_table);
void decode_message(FILE *file, HuffmanNode *root, int bitstream_length);

int main()
{
    FILE *file = fopen ("message.bin", "rb");

    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open file: 'message.bin'\n");
        return 1;
    }

    int *frequency_table = read_frequency_table(file);
    int bitstream_length = read_bitstream_length(file);

    free(frequency_table);
    fclose(file);
    return 0;
}

int* read_frequency_table(FILE *file)
{
    int *frequency_table = malloc(FREQUENCY_TABLE_SIZE * sizeof(int));

    if (frequency_table == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < FREQUENCY_TABLE_SIZE; i++)
    {
        if (fread(&frequency_table[i], sizeof(int), 1, file) != 1)
        {
            fprintf(stderr, "Error: Could not read frequency table\n");
            free(frequency_table);
            exit(1);
        }
    }

    return frequency_table;
}

int read_bitstream_length(FILE *file)
{
    int32_t bitstream_length;

    if (fread(&bitstream_length, sizeof(int), 1, file) != 1)
    {
        fprintf(stderr, "Error: Could not read bitstream length\n");
        exit(1);
    }

    printf("Bitstream length: %d\n", bitstream_length);
    return bitstream_length;
}

HuffmanNode* build_huffman_tree(int *frequency_table)
{
    // build the Huffman tree
}

void decode_message(FILE *file, HuffmanNode *root, int bitstream_length)
{
    // decode the message
}
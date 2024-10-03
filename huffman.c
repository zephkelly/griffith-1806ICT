#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FREQUENCY_TABLE_SIZE 128

typedef struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode *left, *right;
} HuffmanNode;

void read_frequency_table(FILE *file, int *freq_table);
int read_bitstream_length(FILE *file);
HuffmanNode* build_huffman_tree(int *freq_table);
void decode_message(FILE *file, HuffmanNode *root, int bitstream_length);

int main()
{
    FILE *file = fopen ("message.bin", "rb");

    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file: 'message.bin'\n");
        return 1;
    }

    int frequency_table[FREQUENCY_TABLE_SIZE];
    read_frequency_table(file, frequency_table);

    return 0;
}

void read_frequency_table(FILE *file, int *frequency_table)
{
    for (int i = 0; i < FREQUENCY_TABLE_SIZE; i++)
    {
        if (fread(&frequency_table[i], sizeof(int), 1, file) != 1)
        {
            fprintf(stderr, "Error: Could not read frequency table\n");
            exit(1);
        }
    }
}

int read_bitstream_length(FILE *file)
{
    // read 1 4-byte integer
}

HuffmanNode* build_huffman_tree(int *frequency_table)
{
    // build the Huffman tree
}

void decode_message(FILE *file, HuffmanNode *root, int bitstream_length)
{
    // decode the message
}
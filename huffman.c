#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define FREQUENCY_TABLE_SIZE 128

typedef struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode *left, *right;
} HuffmanNode;

typedef struct MinHeap {
    unsigned size;
    unsigned max_size;
    HuffmanNode** array;
} MinHeap;

int* read_frequency_table(FILE *file);
int* sort_frequency_table(int *frequency_table);

int read_bitstream_length(FILE *file);

HuffmanNode* new_huffman_node(char character, int frequency);
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
    int *sorted_table = sort_frequency_table(frequency_table);

    //print sorted
    for (int i = 0; i < FREQUENCY_TABLE_SIZE; i++)
    {
        printf("%c: %d\n", i, sorted_table[i]);
    }

    int bitstream_length = read_bitstream_length(file);

    HuffmanNode* root = build_huffman_tree(frequency_table);

    printf("Decoded message:\n");
    decode_message(file, root, bitstream_length);
    printf("\n");

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

    size_t read_count = fread(frequency_table, sizeof(int), FREQUENCY_TABLE_SIZE, file);
    if (read_count != FREQUENCY_TABLE_SIZE)
    {
        fprintf(stderr, "Error: Could not read the entire frequency table\n");
        free(frequency_table);
        exit(1);
    }

    return frequency_table;
}

int* sort_frequency_table(int *frequency_table)
{
    int *sorted_table = malloc(FREQUENCY_TABLE_SIZE * sizeof(int));

    if (sorted_table == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    memcpy(sorted_table, frequency_table, FREQUENCY_TABLE_SIZE * sizeof(int));

    for (int i = 0; i < FREQUENCY_TABLE_SIZE; i++)
    {
        for (int j = i + 1; j < FREQUENCY_TABLE_SIZE; j++)
        {
            if (sorted_table[i] > sorted_table[j])
            {
                int temp = sorted_table[i];
                sorted_table[i] = sorted_table[j];
                sorted_table[j] = temp;
            }
        }
    }

    return sorted_table;
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

HuffmanNode* new_huffman_node(char character, int frequency)
{
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));

    if (node == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    node->character = character;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;

    return node;
}

HuffmanNode* build_huffman_tree(int *frequency_table)
{

    return NULL;
}

void decode_message(FILE *file, HuffmanNode *root, int bitstream_length)
{

}
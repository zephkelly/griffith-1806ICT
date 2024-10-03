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

typedef struct CharacterFrequency {
    char character;
    int frequency;
} CharacterFrequency;

int* read_frequency_table(FILE *file);
CharacterFrequency* sort_frequency_table(int *frequency_table);

int read_bitstream_length(FILE *file);

HuffmanNode* new_huffman_node(char character, int frequency);
HuffmanNode* build_huffman_tree(CharacterFrequency* sorted_table, int size);

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
    CharacterFrequency *sorted_table = sort_frequency_table(frequency_table);

    int bitstream_length = read_bitstream_length(file);

    HuffmanNode* root = build_huffman_tree(sorted_table, FREQUENCY_TABLE_SIZE);

    printf("Decoded message:\n");
    // decode_message(file, root, bitstream_length);
    printf("\n");

    free(frequency_table);
    free(sorted_table);
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

CharacterFrequency* sort_frequency_table(int *frequency_table)
{
    CharacterFrequency* sorted_table = malloc(FREQUENCY_TABLE_SIZE * sizeof(CharacterFrequency));

    if (sorted_table == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < FREQUENCY_TABLE_SIZE; i++)
    {
        sorted_table[i].character = (char)i;
        sorted_table[i].frequency = frequency_table[i];
    }

    // Bubble sort in ascending order
    for (int i = 0; i < FREQUENCY_TABLE_SIZE - 1; i++)
    {
        for (int j = 0; j < FREQUENCY_TABLE_SIZE - i - 1; j++)
        {
            if (sorted_table[j].frequency > sorted_table[j + 1].frequency)
            {
                CharacterFrequency temp = sorted_table[j];
                sorted_table[j] = sorted_table[j + 1];
                sorted_table[j + 1] = temp;
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

MinHeap* create_min_heap(unsigned capacity)
{
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->max_size = capacity;
    minHeap->array = (HuffmanNode**)malloc(minHeap->max_size * sizeof(HuffmanNode*));
    return minHeap;
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

HuffmanNode* build_huffman_tree(CharacterFrequency* sorted_table, int size)
{
    HuffmanNode *left;
    HuffmanNode *right;
    HuffmanNode *top;

    MinHeap *min_heap = create_min_heap(FREQUENCY_TABLE_SIZE);

    // Populate min heap array with huffman nodes
    for (int i = 0; i < size; ++i)
    {
        min_heap->array[i] = new_huffman_node(sorted_table[i].character, sorted_table[i].frequency);
    }

    return NULL;
}

void decode_message(FILE *file, HuffmanNode *root, int bitstream_length)
{

}
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

    //loop and print the sorted table
    for (int i = 0; i < FREQUENCY_TABLE_SIZE; i++)
    {
        printf("Character: %c, Frequency: %d\n", sorted_table[i].character, sorted_table[i].frequency);
    }

    HuffmanNode* root = build_huffman_tree(sorted_table, FREQUENCY_TABLE_SIZE);

    // printf("Decoded message:\n");
    // decode_message(file, root, bitstream_length);

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

void swap_nodes(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* temp = *a;
    *a = *b;
    *b = temp;
}

void insert_min_heap(MinHeap* min_heap, HuffmanNode* node)
{
    if (min_heap->size >= min_heap->max_size)
    {
        fprintf(stderr, "Error: Heap is full, cannot insert more elements\n");
        return;
    }

    unsigned current_index = min_heap->size;
    min_heap->array[current_index] = node;
    min_heap->size++;

    while (current_index > 0)
    {
        unsigned int parent_index = (current_index - 1) / 2;

        HuffmanNode* current_node = min_heap->array[current_index];
        HuffmanNode* parent_node = min_heap->array[parent_index];

        if (current_node->frequency >= parent_node->frequency)
        {
            break;
        }

        swap_nodes(&min_heap->array[current_index], &min_heap->array[parent_index]);
        current_index = parent_index;
    }
}

HuffmanNode* build_huffman_tree(CharacterFrequency* sorted_table, int size)
{
    int non_zero_count = 0;

    for (int i = 0; i < size; i++)
    {
        if (sorted_table[i].frequency > 0)
        {
            non_zero_count++;
        }
    }
    
    MinHeap* min_heap = create_min_heap(non_zero_count);

    // Only add non-zero frequency characters to the min heap
    for (int i = 0, j = 0; i < size; i++)
    {
        if (sorted_table[i].frequency > 0)
        {
            HuffmanNode* new_node = new_huffman_node(sorted_table[i].character, sorted_table[i].frequency);
            insert_min_heap(min_heap, new_node);
            j++;
        }
    }

    return NULL;
}

void decode_message(FILE *file, HuffmanNode *root, int bitstream_length)
{

}
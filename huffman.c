#include <stdio.h>
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
int read_bitstream_length(FILE *file);

HuffmanNode* new_huffman_node(char character, int frequency);
MinHeap* create_min_heap(unsigned capacity);
void swap_nodes(HuffmanNode** a, HuffmanNode** b);
void insert_min_heap_node(MinHeap* min_heap, HuffmanNode* node);
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

    HuffmanNode* root = build_huffman_tree(frequency_table);

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

MinHeap* create_min_heap(unsigned max_size)
{
    MinHeap* min_heap = (MinHeap*)malloc(sizeof(MinHeap));

    if (min_heap == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    min_heap->size = 0;
    min_heap->max_size = max_size;
    min_heap->array = (HuffmanNode**)malloc(min_heap->max_size * sizeof(HuffmanNode*));

    if (min_heap->array == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    return min_heap;
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
    node->left = node->right = NULL;

    return node;
}

void insert_min_heap_node(MinHeap* min_heap, HuffmanNode* node)
{
    if (min_heap->size >= min_heap->max_size)
    {
        fprintf(stderr, "Error: Heap is full\n");
        return;
    }
    
    unsigned i = min_heap->size;
    min_heap->array[i] = node;
    min_heap->size++;
}

HuffmanNode* build_huffman_tree(int *frequency_table)
{
    MinHeap* min_heap = create_min_heap(FREQUENCY_TABLE_SIZE);

    for (int i = 0; i < FREQUENCY_TABLE_SIZE; i++)
    {
        if (frequency_table[i] > 0)
        {
            HuffmanNode* new_node = new_huffman_node(i, frequency_table[i]);
            insert_min_heap_node(min_heap, new_node);
        }
    }

    return NULL;
}

void decode_message(FILE *file, HuffmanNode *root, int bitstream_length)
{
    // decode the message
}
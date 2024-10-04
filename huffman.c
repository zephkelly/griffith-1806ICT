#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define FREQUENCY_TABLE_SIZE 128
#define MAX_QUEUE_SIZE (2 * FREQUENCY_TABLE_SIZE - 1)

typedef struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode *left, *right;
} HuffmanNode;

typedef struct {
    HuffmanNode* nodes[MAX_QUEUE_SIZE];
    int size;
} PriorityQueue;

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

HuffmanNode* create_node(char character, int frequency)
{
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));

    if (node == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed for HuffmanNode\n");
        exit(1);
    }

    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

void insert_node(PriorityQueue* queue, HuffmanNode* node)
{
    if (queue->size >= MAX_QUEUE_SIZE)
    {
        fprintf(stderr, "Error: Queue is full\n");
        exit(1);
    }

    int i = queue->size;
    while (i > 0 && queue->nodes[i - 1]->frequency > node->frequency)
    {
        queue->nodes[i] = queue->nodes[i - 1];
        i--;
    }

    queue->nodes[i] = node;
    queue->size++;
}

HuffmanNode* extract_min(PriorityQueue* queue)
{
    if (queue->size == 0)
    {
        return NULL;
    }

    HuffmanNode* min = queue->nodes[0];
    queue->size--;

    for (int i = 0; i < queue->size; i++)
    {
        queue->nodes[i] = queue->nodes[i + 1];
    }

    return min;
}

HuffmanNode* build_huffman_tree(int* frequency_table, int size)
{
    PriorityQueue queue = {0};
    queue.size = 0;

    for (int i = 0; i < FREQUENCY_TABLE_SIZE; i++)
    {
        if (frequency_table[i] > 0)
        {
            HuffmanNode* node = create_node((char)i, frequency_table[i]);
            insert_node(&queue, node);
        }
    }

    HuffmanNode* left = extract_min(&queue);
    HuffmanNode* right = extract_min(&queue);

    printf("Character: %c, Frequency: %d\n", left->character, left->frequency);
    printf("Character: %c, Frequency: %d\n", right->character, right->frequency);


    return (queue.size > 0) ? queue.nodes[0] : NULL;
}

void decode_message(FILE *file, HuffmanNode *root, int bitstream_length)
{

}

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

    HuffmanNode* root = build_huffman_tree(frequency_table, FREQUENCY_TABLE_SIZE);

    decode_message(file, root, bitstream_length);

    free(frequency_table);
    fclose(file);
    return 0;
}
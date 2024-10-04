#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STATE_ARRAY_SIZE 256

typedef struct {
    unsigned char state[STATE_ARRAY_SIZE];
    int i;
    int j;
} RC4Stream;

void swap_bytes(unsigned char *a, unsigned char *b)
{
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

void key_scheduling(unsigned char *state, const unsigned char *key, int key_length)
{
    int j = 0;
    
    for (int i = 0; i < STATE_ARRAY_SIZE; i++)
    {
        unsigned char current_state_byte = state[i];
        unsigned char current_key_byte = key[i % key_length];

        j = (j + current_state_byte + current_key_byte) % STATE_ARRAY_SIZE;
        
        swap_bytes(&state[i], &state[j]);
    }
}

void populate_state(unsigned char *state)
{
    for (int i = 0; i < STATE_ARRAY_SIZE; i++)
    {
        state[i] = i;
    }
}

void init_stream(RC4Stream *stream, const unsigned char *key, int key_length)
{
    populate_state(stream->state);
    key_scheduling(stream->state, key, key_length);
    stream->i = 0;
    stream->j = 0;
}

unsigned char generate_key_byte(RC4Stream *stream)
{

}

void rc4_process(RC4Stream *stream, const unsigned char *input, int input_length, unsigned char *output)
{
    for (int i = 0; i < input_length; i++)
    {
        unsigned char key_byte = generate_key_byte(stream);

        // XOR Operation
        output[i] = input[i] ^ key_byte;
    }
}

int main()
{
    const char *key = "s5331799";
    const char *message = "A doctor who specializes in skin diseases will dream he has fallen asleep in front of the television. Later, he will wake up in front of the television but not remember his dream. If all the animas along the equator were capable of flattery then Thanksgiving and Halloween would fall on the same date. When I was 4 years old I watched my mother kill a spider with a tea cosy. Years later, I realized it was not a spider. It was my Uncle Harold.";

    size_t key_length = strlen(key);
    size_t message_length = strlen(message);
    unsigned char *encoded_text = malloc(message_length);

    if (encoded_text == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    RC4Stream stream;
    init_stream(&stream, (const unsigned char *)key, key_length);

    rc4_process(&stream, (const unsigned char *)message, message_length, encoded_text);
}
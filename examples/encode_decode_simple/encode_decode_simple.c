// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <kodoc/kodoc.h>

/// @example encode_decode_simple.c
///
/// Simple example showing how to encode and decode a block
/// of memory.

void trace_callback(const char* zone, const char* data, void* context)
{
    (void) context;

    if (strcmp(zone, "decoder_state") == 0)
    {
        printf("%s:\n", zone);
        printf("%s\n", data);
    }
}

int main()
{
    // Seed the random number generator to produce different data every time
    srand(time(NULL));

    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 10;
    uint32_t max_symbol_size = 100;

    // Here we select the codec we wish to use
    int32_t codec = kodoc_full_vector;

    // Here we select the finite field to use.
    // Some common choices are: kodoc_binary, kodoc_binary4, kodoc_binary8
    int32_t finite_field = kodoc_binary;

    // First, we create an encoder & decoder factory.
    // The factories are used to build actual encoders/decoders
    kodoc_factory_t encoder_factory = kodoc_new_encoder_factory(
        codec, finite_field, max_symbols, max_symbol_size);

    kodoc_factory_t decoder_factory = kodoc_new_decoder_factory(
        codec, finite_field, max_symbols, max_symbol_size);

    // If we wanted to build an encoder or decoder with a smaller number of
    // symbols or a different symbol size, then this can be adjusted using the
    // following functions:
    // kodoc_factory_set_symbols(...) and kodoc_factory_set_symbol_size(...)
    // We can however not exceed the maximum values that were used when
    // creating the factory.

    kodoc_coder_t encoder = kodoc_factory_build_coder(encoder_factory);
    kodoc_coder_t decoder = kodoc_factory_build_coder(decoder_factory);

    uint32_t bytes_used;
    uint32_t payload_size = kodoc_payload_size(encoder);
    uint8_t* payload = (uint8_t*) malloc(payload_size);

    uint32_t block_size = kodoc_block_size(encoder);
    uint8_t* data_in = (uint8_t*) malloc(block_size);
    uint8_t* data_out = (uint8_t*) malloc(block_size);

    uint32_t i = 0;
    for (; i < block_size; ++i)
        data_in[i] = rand() % 256;

    kodoc_set_const_symbols(encoder, data_in, block_size);
    kodoc_set_mutable_symbols(decoder, data_out, block_size);

    // Most of the network coding algorithms supports a mode of operation
    // which is known as systematic coding. This basically means that
    // initially all symbols are sent once un-coded. The rational behind this
    // is that if no errors occur during the transmission we will not have
    // performed any unnecessary coding operations. An encoder will exit the
    // systematic phase automatically once all symbols have been sent un-coded
    // once.
    //
    // With Kodo we can ask an encoder whether it supports systematic encoding
    // or not using the following functions:

    if (kodoc_is_systematic_on(encoder))
    {
        printf("Systematic encoding enabled\n");
    }
    else
    {
        printf("Systematic encoding disabled\n");
    }

    // If we do not wish to use systematic encoding, but to do full coding
    // from the beginning we can turn systematic coding off using the following
    // API:
    //
    // if (kodoc_has_set_systematic_off(encoder))
    // {
    //    kodoc_set_systematic_off(encoder);
    // }

    // Install a custom trace function for the decoder
    kodoc_set_trace_callback(decoder, trace_callback, NULL);

    while (!kodoc_is_complete(decoder))
    {
        // The encoder will use a certain amount of bytes of the payload
        // buffer. It will never use more than payload_size, but it might
        // use less.
        bytes_used = kodoc_write_payload(encoder, payload);
        printf("Payload generated by encoder, rank = %d, bytes used = %d\n",
               kodoc_rank(encoder), bytes_used);

        // Pass the generated packet to the decoder
        kodoc_read_payload(decoder, payload);
        printf("Payload processed by decoder, current rank = %d\n",
               kodoc_rank(decoder));
    }

    if (memcmp(data_in, data_out, block_size) == 0)
    {
        printf("Data decoded correctly\n");
    }
    else
    {
        printf("Unexpected failure to decode, please file a bug report :)\n");
    }

    free(data_in);
    free(data_out);
    free(payload);

    kodoc_delete_coder(encoder);
    kodoc_delete_coder(decoder);

    kodoc_delete_factory(encoder_factory);
    kodoc_delete_factory(decoder_factory);

    return 0;
}

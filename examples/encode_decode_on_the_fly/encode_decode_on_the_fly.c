// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <stdint.h>
#include <ckodo/ckodo.h>

/// @example encode_decode_on_the_fly.c
///
/// This example shows how to use a storage aware encoder which will
/// allow you to encode from a block before all symbols have been
/// specified. This can be useful in cases where the symbols that
/// should be encoded are produced on-the-fly. The decoder will also
/// allow you to detect whether the symbols have been partially decoded.

int main()
{
    // Set the number of symbols (i.e. the generation size in RLNC
    // terminology) and the size of a symbol in bytes
    uint32_t max_symbols = 8;
    uint32_t max_symbol_size = 160;

    // Here we select the coding algorithm we wish to use
    size_t algorithm = kodo_on_the_fly;

    // Here we select the finite field to use common choices are
    // kodo_binary, kodo_binary8, kodo_binary16
    size_t finite_field = kodo_binary8;

    kodo_factory_t* encoder_factory =
        kodo_new_encoder_factory(algorithm, finite_field,
                                 max_symbols, max_symbol_size);

    kodo_factory_t* decoder_factory =
        kodo_new_decoder_factory(algorithm, finite_field,
                                 max_symbols, max_symbol_size);

    kodo_coder_t* encoder = kodo_factory_new_encoder(encoder_factory);
    kodo_coder_t* decoder = kodo_factory_new_decoder(decoder_factory);

    uint32_t payload_size = kodo_payload_size(encoder);
    uint8_t* payload = (uint8_t*)malloc(payload_size);

    uint32_t block_size = kodo_block_size(encoder);
    uint8_t* data_in = (uint8_t*)malloc(block_size);
    uint8_t* data_out = (uint8_t*)malloc(block_size);

    // Keeps track of which symbols have been decoded
    uint8_t* decoded = (uint8_t*)malloc(sizeof(uint8_t)*max_symbols);

    uint32_t i = 0;
    for (i = 0; i < block_size; ++i)
        data_in[i] = rand() % 256;

    // Zero initialize the decoded array
    memset(decoded, '\0', sizeof(uint8_t)*max_symbols);

    // We are starting the encoding / decoding loop without having
    // added any data to the encoder - we will add symbols on-the-fly
    while (!kodo_is_complete(decoder))
    {
        uint32_t bytes_used;
        // Randomly choose to add a new symbol (with 50% probability)
        // if the encoder rank is less than the maximum number of symbols
        if ((rand() % 2) && kodo_rank(encoder) < kodo_symbols(encoder))
        {
            // The rank of an encoder indicates how many symbols have been added,
            // i.e. how many symbols are available for encoding
            uint32_t rank = kodo_rank(encoder);

            // Calculate the offset to the next symbol to insert
            uint8_t* symbol = data_in + (rank * kodo_symbol_size(encoder));
            kodo_set_symbol(encoder, rank, symbol, kodo_symbol_size(encoder));
        }

        bytes_used = kodo_encode(encoder, payload);
        printf("Payload generated by encoder, rank = %d, bytes used = %d\n",
               kodo_rank(encoder), bytes_used);

        // Send the data to the decoders, here we just for fun
        // simulate that we are loosing 50% of the packets
        if (rand() % 2)
        {
            printf("packet dropped\n");
            continue;
        }

        // Packet got through - pass that packet to the decoder
        kodo_decode(decoder, payload);

        // The rank of a decoder indicates how many symbols have been
        // decoded or partially decoded
        printf("Payload processed by decoder, current rank = %d\n",
               kodo_rank(decoder));

        // Check the decoder whether it is partially complete
        // For on-the-fly decoding the decoder has to support the partial
        // decoding tracker.

        if (kodo_has_partial_decoding_tracker(decoder) &&
            kodo_is_partial_complete(decoder))
        {
            uint32_t i = 0;
            for (; i < kodo_symbols(decoder); ++i)
            {
                //if (!kodo_is_symbol_decoded(decoder, i))
                //    continue;

                if (!decoded[i])
                {
                    uint32_t size = kodo_symbol_size(encoder);
                    uint8_t* original = data_in + i * size;
                    uint8_t* target = data_out + i * size;

                    // Update that this symbol now has been decoded
                    printf("Symbol %d was decoded\n", i);
                    decoded[i] = 1;
                    // Verify the decoded symbol

                    // Copy out the individual symbol from the decoder
                    kodo_copy_symbol(decoder, i, target, size);
                    // Verify the symbol against the original data
                    if (memcmp(original, target, size) == 0)
                    {
                        printf("Symbol %d decoded correctly\n", i);
                    }
                    else
                    {
                        printf("SYMBOL %d DECODING FAILED.\n", i);
                    }
                }
            }
        }

    }

    kodo_copy_symbols(decoder, data_out, block_size);

    if (memcmp(data_in, data_out, block_size) == 0)
    {
        printf("Data decoded correctly\n");
    }
    else
    {
        printf("Unexpected failure to decode please file a bug report :)\n");
    }

    free(data_in);
    free(data_out);
    free(payload);

    kodo_delete_encoder(encoder);
    kodo_delete_decoder(decoder);

    kodo_delete_encoder_factory(encoder_factory);
    kodo_delete_decoder_factory(decoder_factory);

    return 0;
}

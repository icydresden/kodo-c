// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include "ckodo.h"

#include <cstring>
#include <cstdint>
#include <cassert>

#include <kodo/rlnc/full_vector_codes.hpp>
#include <kodo/rlnc/on_the_fly_codes.hpp>

#include <kodo/rlnc/sliding_window_encoder.hpp>
#include <kodo/rlnc/sliding_window_decoder.hpp>

#include "encoder_factory_wrapper.hpp"
#include "decoder_factory_wrapper.hpp"

//------------------------------------------------------------------
// FACTORY API
//------------------------------------------------------------------

kodo_factory_t*
kodo_new_encoder_factory(int32_t code_type, int32_t finite_field,
                         uint32_t max_symbols, uint32_t max_symbol_size,
                         int32_t trace_mode)
{
    using namespace kodo;
    using namespace kodo::rlnc;

    kodo::factory* factory = 0;

    if (code_type == kodo_full_rlnc)
    {
        if (trace_mode == kodo_trace_disabled)
        {
            if (finite_field == kodo_binary)
            {
                factory = new encoder_factory_wrapper<
                    full_vector_encoder<fifi::binary,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new encoder_factory_wrapper<
                    full_vector_encoder<fifi::binary4,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new encoder_factory_wrapper<
                    full_vector_encoder<fifi::binary8,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new encoder_factory_wrapper<
                    full_vector_encoder<fifi::binary16,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
        }
        else
        {
            if (finite_field == kodo_binary)
            {
                factory = new encoder_factory_wrapper<
                    full_vector_encoder<fifi::binary,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new encoder_factory_wrapper<
                    full_vector_encoder<fifi::binary4,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new encoder_factory_wrapper<
                    full_vector_encoder<fifi::binary8,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new encoder_factory_wrapper<
                    full_vector_encoder<fifi::binary16,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
        }
    }
    else if (code_type == kodo_on_the_fly)
    {
        if (trace_mode == kodo_trace_disabled)
        {
            if (finite_field == kodo_binary)
            {
                factory = new encoder_factory_wrapper<
                    on_the_fly_encoder<fifi::binary,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new encoder_factory_wrapper<
                    on_the_fly_encoder<fifi::binary4,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new encoder_factory_wrapper<
                    on_the_fly_encoder<fifi::binary8,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new encoder_factory_wrapper<
                    on_the_fly_encoder<fifi::binary16,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
        }
        else
        {
            if (finite_field == kodo_binary)
            {
                factory = new encoder_factory_wrapper<
                    on_the_fly_encoder<fifi::binary,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new encoder_factory_wrapper<
                    on_the_fly_encoder<fifi::binary4,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new encoder_factory_wrapper<
                    on_the_fly_encoder<fifi::binary8,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new encoder_factory_wrapper<
                    on_the_fly_encoder<fifi::binary16,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
        }
    }
    else if (code_type == kodo_sliding_window)
    {
        if (trace_mode == kodo_trace_disabled)
        {
            if (finite_field == kodo_binary)
            {
                factory = new encoder_factory_wrapper<
                    sliding_window_encoder<fifi::binary,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new encoder_factory_wrapper<
                    sliding_window_encoder<fifi::binary4,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new encoder_factory_wrapper<
                    sliding_window_encoder<fifi::binary8,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new encoder_factory_wrapper<
                    sliding_window_encoder<fifi::binary16,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
        }
        else
        {
            if (finite_field == kodo_binary)
            {
                factory = new encoder_factory_wrapper<
                    sliding_window_encoder<fifi::binary,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new encoder_factory_wrapper<
                    sliding_window_encoder<fifi::binary4,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new encoder_factory_wrapper<
                    sliding_window_encoder<fifi::binary8,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new encoder_factory_wrapper<
                    sliding_window_encoder<fifi::binary16,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
        }
    }

    // Unknown code type or field type
    assert(factory);

    return (kodo_factory_t*)factory;
}


kodo_factory_t*
kodo_new_decoder_factory(int32_t code_type, int32_t finite_field,
                         uint32_t max_symbols, uint32_t max_symbol_size,
                         int32_t trace_mode)
{
    using namespace kodo;
    using namespace kodo::rlnc;

    kodo::factory* factory = 0;

    if (code_type == kodo_full_rlnc)
    {
        if (trace_mode == kodo_trace_disabled)
        {
            if (finite_field == kodo_binary)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary4,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary8,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary16,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
        }
        else
        {
            if (finite_field == kodo_binary)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary4,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary8,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new decoder_factory_wrapper<
                    full_vector_decoder<fifi::binary16,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
        }
    }
    else if (code_type == kodo_on_the_fly)
    {
        if (trace_mode == kodo_trace_disabled)
        {
            if (finite_field == kodo_binary)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary4,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary8,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary16,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
        }
        else
        {
            if (finite_field == kodo_binary)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary4,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary8,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new decoder_factory_wrapper<
                    on_the_fly_decoder<fifi::binary16,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
        }
    }
    else if (code_type == kodo_sliding_window)
    {
        if (trace_mode == kodo_trace_disabled)
        {
            if (finite_field == kodo_binary)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary4,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary8,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary16,
                        disable_trace>>(max_symbols, max_symbol_size);
            }
        }
        else
        {
            if (finite_field == kodo_binary)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary4)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary4,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary8)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary8,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
            else if (finite_field == kodo_binary16)
            {
                factory = new decoder_factory_wrapper<
                    sliding_window_decoder<fifi::binary16,
                        enable_trace>>(max_symbols, max_symbol_size);
            }
        }
    }

    // Unknown code type or field type
    assert(factory);

    return (kodo_factory_t*)factory;
}

//------------------------------------------------------------------
// FACTORY API
//------------------------------------------------------------------

void kodo_delete_encoder_factory(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    delete the_factory;
}

void kodo_delete_decoder_factory(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    delete the_factory;
}

uint32_t kodo_factory_max_symbols(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->max_symbols();
}

uint32_t kodo_factory_max_symbol_size(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->max_symbol_size();
}

uint32_t kodo_factory_max_block_size(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->max_block_size();
}

uint32_t kodo_factory_max_payload_size(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    return the_factory->max_payload_size();
}

void kodo_factory_set_symbols(kodo_factory_t* factory, uint32_t symbols)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    the_factory->set_symbols(symbols);
}

void kodo_factory_set_symbol_size(kodo_factory_t* factory,
                                  uint32_t symbol_size)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    the_factory->set_symbol_size(symbol_size);
}


kodo_coder_t* kodo_factory_new_encoder(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    void* encoder = the_factory->build();
    return (kodo_coder_t*) encoder;
}

kodo_coder_t* kodo_factory_new_decoder(kodo_factory_t* factory)
{
    assert(factory);

    kodo::factory* the_factory = (kodo::factory*) factory;
    void* decoder = the_factory->build();
    return (kodo_coder_t*) decoder;
}

void kodo_delete_encoder(kodo_coder_t* encoder)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    delete the_encoder;
}

void kodo_delete_decoder(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    delete the_decoder;
}

//------------------------------------------------------------------
// PAYLOAD API
//------------------------------------------------------------------

uint32_t kodo_payload_size(kodo_coder_t* coder)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->payload_size();
}

void kodo_decode(kodo_coder_t* decoder, uint8_t* payload)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    the_decoder->decode(payload);
}

uint32_t kodo_recode(kodo_coder_t* decoder, uint8_t* payload)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return the_decoder->recode(payload);
}

uint32_t kodo_encode(kodo_coder_t* encoder, uint8_t* payload)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    return the_encoder->encode(payload);
}

//------------------------------------------------------------------
// SYMBOL STORAGE API
//------------------------------------------------------------------

uint32_t kodo_block_size(kodo_coder_t* coder)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->block_size();
}

void kodo_set_symbols(kodo_coder_t* encoder, const uint8_t* data,
                      uint32_t size)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    the_encoder->set_symbols(data, size);
}

void kodo_set_symbol(kodo_coder_t* encoder, uint32_t index,
                     const uint8_t* data, uint32_t size)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    the_encoder->set_symbol(index, data, size);
}

void kodo_copy_symbols(kodo_coder_t* decoder, uint8_t* data, uint32_t size)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    the_decoder->copy_symbols(data, size);
}

void kodo_copy_symbol(kodo_coder_t* decoder, uint32_t index,
                      uint8_t* data, uint32_t size)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    the_decoder->copy_symbol(index, data, size);
}

uint32_t kodo_symbol_size(kodo_coder_t* coder)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->symbol_size();
}

uint32_t kodo_symbols(kodo_coder_t* coder)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->symbols();
}


//------------------------------------------------------------------
// CODEC API
//------------------------------------------------------------------

uint8_t kodo_is_complete(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return (uint8_t)the_decoder->is_complete();
}

uint8_t kodo_is_partial_complete(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return (uint8_t)the_decoder->is_partial_complete();
}

uint8_t kodo_has_feedback_size(kodo_coder_t* coder)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return (uint8_t)the_coder->has_feedback_size();
}

uint8_t kodo_feedback_size(kodo_coder_t* coder)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return (uint8_t)the_coder->feedback_size();
}

void kodo_read_feedback(kodo_coder_t* encoder, uint8_t* feedback)
{
    assert(encoder);
    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    the_encoder->read_feedback(feedback);
}

void kodo_write_feedback(kodo_coder_t* decoder, uint8_t* feedback)
{
    assert(decoder);
       kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    the_decoder->write_feedback(feedback);
}

uint32_t kodo_rank(kodo_coder_t* coder)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->rank();
}

uint8_t kodo_symbol_pivot(kodo_coder_t* coder, uint32_t index)
{
    assert(coder);

    kodo::coder* the_coder = (kodo::coder*) coder;
    return the_coder->symbol_pivot(index);
}

uint8_t kodo_is_symbol_uncoded(kodo_coder_t* decoder, uint32_t index)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return the_decoder->is_symbol_uncoded(index);
}

uint32_t kodo_symbols_uncoded(kodo_coder_t* decoder)
{
    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return the_decoder->symbols_uncoded();
}

uint32_t kodo_symbols_seen(kodo_coder_t* decoder)
{
    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return the_decoder->symbols_seen();
}

//------------------------------------------------------------------
// GENERIC API
//------------------------------------------------------------------

uint8_t kodo_has_partial_decoding_tracker(kodo_coder_t* decoder)
{
    assert(decoder);

    kodo::decoder* the_decoder = (kodo::decoder*) decoder;
    return (uint8_t)the_decoder->has_partial_decoding_tracker();
}

uint8_t kodo_has_systematic_encoder(kodo_coder_t* encoder)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    return (uint8_t)the_encoder->has_systematic_encoder();
}

uint8_t kodo_is_systematic_on(kodo_coder_t* encoder)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    return (uint8_t)the_encoder->is_systematic_on();
}

void kodo_set_systematic_on(kodo_coder_t* encoder)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    the_encoder->set_systematic_on();
}

void kodo_set_systematic_off(kodo_coder_t* encoder)
{
    assert(encoder);

    kodo::encoder* the_encoder = (kodo::encoder*) encoder;
    the_encoder->set_systematic_off();
}

//------------------------------------------------------------------
// TRACE API
//------------------------------------------------------------------

uint8_t kodo_has_trace(kodo_coder_t* coder)
{
    assert(coder);
    kodo::coder* the_coder = (kodo::coder*) coder;
    return (uint8_t)the_coder->has_trace();
}

void kodo_trace(kodo_coder_t* coder)
{
    kodo::coder* the_coder = (kodo::coder*) coder;
    the_coder->trace(NULL);
}

void kodo_trace_callback(kodo_coder_t* coder, kodo_trace_callback_t callback)
{
    kodo::coder* the_coder = (kodo::coder*) coder;
    the_coder->trace(callback);
}

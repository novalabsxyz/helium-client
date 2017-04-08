#include "test_am_frame_decode.h"
#include "am_frame_decode.h"
#include "am_frame_common.h"

TEST test_am_frame_decode_init__resets_state(void) {
    struct am_frame_decode_ctx ctx = {
        .state = afd_state_UNINITIALIZED,
    };

    am_frame_decode_init(&ctx);

    ASSERT_EQ(afd_state_SOF, ctx.state);

    PASS();
}

TEST test_am_frame_decode_give__stores_buffer_info(void) {
    uint8_t const data[] = "hello world";
    size_t const LEN = sizeof(data);

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, LEN));

    ASSERT_EQ(data, ctx.given);
    ASSERT_EQ(LEN, ctx.given_len);
    ASSERT_EQ(0, ctx.given_pos);

    PASS();
}

TEST test_am_frame_decode_give__rejects_while_busy(void) {
    uint8_t const data[] = "hello world";
    size_t const LEN = sizeof(data);

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, LEN));

    ASSERT_EQ(
        afdg_status_BUSY,
        am_frame_decode_give(&ctx, data, LEN));

    PASS();
}

TEST test_am_frame_decode_byte__detects_when_out_of_data(void) {
    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    uint8_t byte = 0;
    ASSERT_EQ(
        afdb_status_NEED_INPUT,
        am_frame_decode_byte(&ctx, &byte));

    PASS();
}

TEST test_am_frame_decode_byte__decodes_zero_lengthed_frame(void) {
    uint8_t const data[] = { SOF_CHAR, 0, 0, EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte = 0;
    ASSERT_EQ_FMT(
        afdb_status_DONE,
        am_frame_decode_byte(&ctx, &byte),
        "%d");

    PASS();
}

TEST test_am_frame_decode_byte__retrieves_bytes(void) {
    uint8_t const data[] = { SOF_CHAR, 3, 0, 'A', 'B', 'C', EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte = 0;

    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('A', byte);
    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('B', byte);
    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('C', byte);

    ASSERT_EQ(
        afdb_status_DONE,
        am_frame_decode_byte(&ctx, &byte));

    PASS();
}

TEST test_am_frame_decode_byte__handles_escaped_LSB(void) {
    uint8_t const data[32] = {
        [0] = SOF_CHAR,
        [1] = ESC_CHAR, // 27 == 0x1b,
        [2] = ESC_ESC,
        [3] = 0,
        [4] = 'A',
        [31] = EOF_CHAR,
    };
    uint8_t const expected[ESC_CHAR] = { 'A' };
    uint8_t actual[ESC_CHAR] = { 0 };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    for (size_t i = 0; i < sizeof(actual); i++) {
        ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &actual[i]));
    }

    uint8_t dummy;
    ASSERT_EQ(afdb_status_DONE, am_frame_decode_byte(&ctx, &dummy));

    ASSERT_MEM_EQ(expected, actual, sizeof(expected));

    PASS();
}

TEST test_am_frame_decode_byte__handles_escaped_MSB(void) {
#define PL_LEN (ESC_CHAR << 8)
#define DATA_LEN ((ESC_CHAR << 8) + 4 + 1)
    uint8_t data[DATA_LEN] = { 0 };
    data[0] = SOF_CHAR;
    data[1] = 0;
    data[2] = ESC_CHAR; // 27 == 0x1b,
    data[3] = ESC_ESC;
    data[4] = 'B';
    data[DATA_LEN - 1] = EOF_CHAR;
#undef DATA_LEN

    uint8_t const expected[PL_LEN] = { 'B' };
    uint8_t actual[PL_LEN] = { 0 };
#undef PL_LEN

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    for (size_t i = 0; i < sizeof(actual); i++) {
        ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &actual[i]));
    }

    uint8_t dummy;
    ASSERT_EQ(afdb_status_DONE, am_frame_decode_byte(&ctx, &dummy));

    ASSERT_MEM_EQ(expected, actual, sizeof(expected));

    PASS();
}

TEST test_am_frame_decode_byte__handles_escaped_length(void) {
#define PL_LEN (ESC_CHAR | (ESC_CHAR << 8))
#define DATA_LEN (PL_LEN /* the data */         \
                  + 4 /* the overhead */        \
                  + 2 /* the length escapes */)

    uint8_t data[DATA_LEN] = { 0 };
    data[0] = SOF_CHAR;
    data[1] = ESC_CHAR; // 27 == 0x1b,
    data[2] = ESC_ESC;
    data[3] = ESC_CHAR; // 27 == 0x1b,
    data[4] = ESC_ESC;
    data[5] = 'C';
    data[DATA_LEN - 1] = EOF_CHAR;
#undef DATA_LEN

    uint8_t const expected[PL_LEN] = { 'C' };
    uint8_t actual[PL_LEN] = { 0 };
#undef PL_LEN

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    for (size_t i = 0; i < sizeof(actual); i++) {
        ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &actual[i]));
    }

    uint8_t dummy;
    enum am_frame_decode_byte_status dstat = am_frame_decode_byte(&ctx, &dummy);
    ASSERT_EQ_FMT(
        afd_error_NONE,
        am_frame_decode_get_error(&ctx), "%d");

    ASSERT_EQ_FMT(afdb_status_DONE, dstat, "%d");

    ASSERT_MEM_EQ(expected, actual, sizeof(expected));

    PASS();
}

TEST test_am_frame_decode_byte__handles_escaped_data(void) {
    uint8_t const data[] = { SOF_CHAR, 5, 0,
                             'A',
                             ESC_CHAR, SOF_ESC,
                             ESC_CHAR, ESC_ESC,
                             ESC_CHAR, EOF_ESC,
                             'Z',
                             EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte = 0;

    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('A', byte);
    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ(SOF_CHAR, byte);
    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ(ESC_CHAR, byte);
    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ(EOF_CHAR, byte);
    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('Z', byte);

    ASSERT_EQ(
        afdb_status_DONE,
        am_frame_decode_byte(&ctx, &byte));

    ASSERT_EQ(
        afd_error_NONE,
        am_frame_decode_get_error(&ctx));

    PASS();
}

TEST test_am_frame_decode_byte__handles_leading_data(void) {
    uint8_t const data[] = { 'A', 'B', 'C',
                             SOF_CHAR, 1, 0,
                             'A',
                             EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte = 0;

    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('A', byte);

    ASSERT_EQ(
        afdb_status_DONE,
        am_frame_decode_byte(&ctx, &byte));

    PASS();
}

TEST test_am_frame_decode_byte__handles_repeated_SOF(void) {
    uint8_t const data[] = { SOF_CHAR, SOF_CHAR, SOF_CHAR,
                             SOF_CHAR, 1, 0,
                             'A',
                             EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte = 0;

    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('A', byte);

    ASSERT_EQ(
        afdb_status_DONE,
        am_frame_decode_byte(&ctx, &byte));

    PASS();
}

TEST test_am_frame_decode_byte__handles_out_of_place_EOF(void) {
    /* length indicates two bytes of payload, but only one given. */
    uint8_t const data[] = { SOF_CHAR, 2, 0,
                             'A',
                             EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte = 0;

    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('A', byte);

    ASSERT_EQ_FMT(
        afdb_status_DONE_WITH_ERROR,
        am_frame_decode_byte(&ctx, &byte),
        "%d");

    ASSERT_EQ(
        afd_error_UNDERSIZED_FRAME,
        am_frame_decode_get_error(&ctx));

    PASS();
}

TEST test_am_frame_decode_byte__extra_trailing_data(void) {
    uint8_t const data[] = { SOF_CHAR, 1, 0,
                             'A',
                             EOF_CHAR, 'Z', 'Z' };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte = 0;

    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('A', byte);

    /* Call it twice to make sure the DONE state is sticky. */
    ASSERT_EQ(
        afdb_status_DONE,
        am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ(
        afdb_status_DONE,
        am_frame_decode_byte(&ctx, &byte));

    PASS();
}

TEST test_am_frame_decode_byte__detects_bad_escape(void) {
    uint8_t const data[] = { SOF_CHAR, 1, 0,
                             // 9 is not a valid escape char. Will be
                             // output as 0.
                             ESC_CHAR, 9,
                             EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte = 0;

    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ(afdb_status_DONE_WITH_ERROR, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ(afd_error_BAD_ESCAPE, am_frame_decode_get_error(&ctx));

    PASS();
}

TEST test_am_frame_decode_byte__detects_reset_conditions(void) {
    uint8_t const data[] = { SOF_CHAR, 1, 0,
                             'A',
                             SOF_CHAR, 1, 0, // restart a new frame here
                             'B',
                             EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte = 0;

    /* First we see the start of the first frame. */
    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('A', byte);

    /* However, instead of an EOF, we see a new SOF. */
    ASSERT_EQ(afdb_status_RESTART_FRAME, am_frame_decode_byte(&ctx, &byte));

    /* The correct frame starts and we see the B. */
    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('B', byte);

    /* The second SOF is completed properly. */
    ASSERT_EQ(
        afdb_status_DONE,
        am_frame_decode_byte(&ctx, &byte));

    PASS();
}

TEST test_am_frame_decode_byte__detects_oversized_frames(void) {
    uint8_t const data[] = { SOF_CHAR, 2, 0,
                             'A', 'B',
                             // this byte is not expected since the
                             // length is only 2
                             'C',
                             EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte = 0;

    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('A', byte);
    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('B', byte);

    ASSERT_EQ(afdb_status_DONE_WITH_ERROR, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ(afd_error_OVERSIZED_FRAME, am_frame_decode_get_error(&ctx));

    PASS();
}

TEST test_am_frame_decode_remaining__provides_size_of_remaining_given_data(void) {
    uint8_t const data[] = { SOF_CHAR, 1, 0, 'A', EOF_CHAR,
                             0, 0, // noise
                             SOF_CHAR, 1, 0, 'B', EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte;

    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('A', byte);
    ASSERT_EQ(afdb_status_DONE, am_frame_decode_byte(&ctx, &byte));

    ASSERT_EQ_FMT(7, am_frame_decode_remaining(&ctx), "%u");

    PASS();
}

TEST test_am_frame_decode_begin__resets_position_and_len_to_parse_remaining_given_data(void) {
    uint8_t const data[] = { SOF_CHAR, 1, 0, 'A', EOF_CHAR,
                             0, 0, // noise
                             SOF_CHAR, 1, 0, 'B', EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte;

    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('A', byte);
    ASSERT_EQ(afdb_status_DONE, am_frame_decode_byte(&ctx, &byte));

    ASSERT_EQ(afdr_status_OK, am_frame_decode_reset(&ctx));

    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('B', byte);
    ASSERT_EQ(afdb_status_DONE, am_frame_decode_byte(&ctx, &byte));

    PASS();
}

TEST test_am_frame_decode_begin__only_works_in_initial_or_done_states(void) {
    uint8_t const data[] = { SOF_CHAR, 1, 0, 'A', EOF_CHAR,
                             0, 0, // noise
                             SOF_CHAR, 1, 0, 'B', EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t byte;

    ASSERT_EQ(afdb_status_OUT_VALID, am_frame_decode_byte(&ctx, &byte));
    ASSERT_EQ('A', byte);

    ASSERT_EQ(afdr_status_NOT_DONE, am_frame_decode_reset(&ctx));

    PASS();
}

TEST test_am_frame_decode_buffer__works_for_small_buffers(void) {
    uint8_t const data[] = { SOF_CHAR, 3, 0,
                             'A', 'B', 'C',
                             EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    uint8_t const expected[] = { 'A', 'B', 'C' };
    /* +1 so we don't trigger the out-of-buffer-space condition. */
    uint8_t actual[sizeof(expected) + 1] = { 0 };

    /* Decode as much as our buffer will hold. */
    size_t used = 0;
    enum am_frame_decode_buffer_status afdbu;
    afdbu = am_frame_decode_buffer(&ctx,
                                   actual, sizeof(actual),
                                   &used);
    ASSERT_EQ_FMT(afdbu_status_BUFFER_VALID, afdbu, "%d");

    ASSERT_EQ(sizeof(expected), used);
    ASSERT_MEM_EQ(expected, actual, sizeof(expected));

    /* Try again and see that we're done. */
    ASSERT_EQ(
        afdbu_status_DONE,
        am_frame_decode_buffer(&ctx,
                               actual, sizeof(actual),
                               &used));

    PASS();
}

TEST test_am_frame_decode_buffer__works_for_segmented_buffers(void) {
    uint8_t const data1[] = { SOF_CHAR, 12, 0,
                              'A', 'B', 'C', 'D', 'E', 'F' };
    uint8_t const data2[] = { '1', '2', '3', '4', '5', '6',
                              EOF_CHAR};

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    uint8_t const expected1[] = {
        'A', 'B', 'C', 'D', 'E', 'F',
    };
    uint8_t const expected2[] = {
        '1', '2', '3', '4', '5', '6',
    };
    ASSERT(sizeof(expected1) == sizeof(expected2));
    uint8_t actual[sizeof(expected1) + 1] = { 0 };

    /* Give the first segment of encoded data. */
    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data1, sizeof(data1)));

    /* Decode as much as our buffer will hold. */
    size_t used = 0;
    enum am_frame_decode_buffer_status afdbu;
    afdbu = am_frame_decode_buffer(&ctx,
                                   actual, sizeof(actual),
                                   &used);
    ASSERT_EQ_FMT(afdbu_status_BUFFER_VALID, afdbu, "%d");
    // A - F
    ASSERT_EQ(6, used);
    ASSERT_MEM_EQ(expected1, actual, used);

    afdbu = am_frame_decode_buffer(&ctx,
                                   actual, sizeof(actual),
                                   &used);
    ASSERT_EQ_FMT(afdbu_status_NEED_INPUT, afdbu, "%d");
    ASSERT_EQ(0, used);

    /* Give the second segment of encoded data. */
    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data2, sizeof(data2)));

    /* Try again and see that we're able to get the rest. */
    afdbu = am_frame_decode_buffer(&ctx,
                                   actual, sizeof(actual),
                                   &used);
    ASSERT_EQ_FMT(afdbu_status_BUFFER_VALID, afdbu, "%d");
    // 1 - 6
    ASSERT_EQ(6, used);
    ASSERT_MEM_EQ(expected2, actual, used);

    afdbu = am_frame_decode_buffer(&ctx,
                                   actual, sizeof(actual),
                                   &used);
    ASSERT_EQ_FMT(afdbu_status_DONE, afdbu, "%d");

    PASS();
}

TEST test_am_frame_decode_buffer__short_decode_buffers(void) {
    uint8_t const data[] = { SOF_CHAR, 12, 0,
                             'A', 'B', 'C', 'D', 'E', 'F',
                             '1', '2', '3', '4', '5', '6',
                             EOF_CHAR };

    struct am_frame_decode_ctx ctx;
    am_frame_decode_init(&ctx);

    uint8_t const expected[] = {
        'A', 'B', 'C', 'D', 'E', 'F',
        '1', '2', '3', '4', '5', '6',
    };
    uint8_t actual[sizeof(expected) + 1] = { 0 };

    ASSERT_EQ(
        afdg_status_OK,
        am_frame_decode_give(&ctx, data, sizeof(data)));

    size_t const SPAN = 3;
    uint8_t * b;
    size_t used = 0;
    enum am_frame_decode_buffer_status afdbu;

    /* The first 4 should indicate we ran out of decode buffer
     * space. */
    for (size_t i = 0; i < 4; i++) {
        b = &actual[SPAN * i];
        afdbu = am_frame_decode_buffer(&ctx, b, SPAN, &used);
        ASSERT_EQ_FMT(afdbu_status_BUFFER_FULL, afdbu, "%d");
        ASSERT_EQ(SPAN, used);
    }

    /* Compare data now. */
    ASSERT_MEM_EQ(expected, actual, sizeof(expected));

    /* The 5th will result in a DONE state. */
    afdbu = am_frame_decode_buffer(&ctx, actual, sizeof(actual), &used);
    ASSERT_EQ_FMT(afdbu_status_DONE, afdbu, "%d");
    ASSERT_EQ(0, used);


    PASS();
}

SUITE(suite_am_frame_decode) {
    RUN_TEST(test_am_frame_decode_init__resets_state);

    RUN_TEST(test_am_frame_decode_give__stores_buffer_info);
    RUN_TEST(test_am_frame_decode_give__rejects_while_busy);

    RUN_TEST(test_am_frame_decode_byte__detects_when_out_of_data);
    RUN_TEST(test_am_frame_decode_byte__decodes_zero_lengthed_frame);
    RUN_TEST(test_am_frame_decode_byte__retrieves_bytes);
    RUN_TEST(test_am_frame_decode_byte__handles_escaped_LSB);
    RUN_TEST(test_am_frame_decode_byte__handles_escaped_MSB);
    RUN_TEST(test_am_frame_decode_byte__handles_escaped_length);
    RUN_TEST(test_am_frame_decode_byte__handles_escaped_data);
    RUN_TEST(test_am_frame_decode_byte__handles_leading_data);
    RUN_TEST(test_am_frame_decode_byte__handles_repeated_SOF);
    RUN_TEST(test_am_frame_decode_byte__handles_out_of_place_EOF);
    RUN_TEST(test_am_frame_decode_byte__extra_trailing_data);
    RUN_TEST(test_am_frame_decode_byte__detects_bad_escape);
    RUN_TEST(test_am_frame_decode_byte__detects_reset_conditions);
    RUN_TEST(test_am_frame_decode_byte__detects_oversized_frames);

    RUN_TEST(test_am_frame_decode_remaining__provides_size_of_remaining_given_data);

    RUN_TEST(test_am_frame_decode_begin__resets_position_and_len_to_parse_remaining_given_data);
    RUN_TEST(test_am_frame_decode_begin__only_works_in_initial_or_done_states);

    RUN_TEST(test_am_frame_decode_buffer__works_for_small_buffers);
    RUN_TEST(test_am_frame_decode_buffer__works_for_segmented_buffers);
    RUN_TEST(test_am_frame_decode_buffer__short_decode_buffers);
}

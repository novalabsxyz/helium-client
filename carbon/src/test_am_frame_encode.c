#include "test_am_frame_encode.h"
#include "am_frame_encode.h"
#include "am_frame_common.h"

TEST test_am_frame_encode_init__saves_length(void) {
    size_t const LEN = 500;
    struct am_frame_encode_ctx ctx;

    am_frame_encode_init(&ctx, LEN);

    ASSERT_EQ(LEN, ctx.len);
    ASSERT_EQ(afe_state_SOF, ctx.state);
    ASSERT_EQ(0, ctx.pos);

    PASS();
}

TEST test_am_frame_encode_give__accepts_properly_sized_input(void) {
    size_t const LEN = 4;
    struct am_frame_encode_ctx ctx;
    am_frame_encode_init(&ctx, LEN);

    uint8_t const data[] = {1,2,3,4};

    enum am_frame_encode_give_status stat;
    stat = am_frame_encode_give(&ctx, data, sizeof(data));

    ASSERT_EQ(afeg_status_OK, stat);

    PASS();
}

TEST test_am_frame_encode_give__rejects_too_much_input(void) {
    size_t const LEN = 4;
    struct am_frame_encode_ctx ctx;
    am_frame_encode_init(&ctx, LEN);

    uint8_t const data[] = {1,2,3,4,5};

    enum am_frame_encode_give_status stat;
    stat = am_frame_encode_give(&ctx, data, sizeof(data));

    ASSERT_EQ(afeg_status_OVERFLOW, stat);

    PASS();
}

TEST test_am_frame_encode_give__rejects_before_previous_give_consumed(void) {
    size_t const LEN = 4;
    struct am_frame_encode_ctx ctx;
    am_frame_encode_init(&ctx, LEN);

    enum am_frame_encode_give_status stat;

    uint8_t const data1[] = {1,2};
    stat = am_frame_encode_give(&ctx, data1, sizeof(data1));
    ASSERT_EQ(afeg_status_OK, stat);

    uint8_t const data2[] = {1,2,3};
    stat = am_frame_encode_give(&ctx, data2, sizeof(data2));
    ASSERT_EQ(afeg_status_BUSY, stat);

    PASS();
}

TEST test_am_frame_encode_give__allows_multiple_gives(void) {
    size_t const LEN = 4;
    uint8_t b;
    struct am_frame_encode_ctx ctx;
    am_frame_encode_init(&ctx, LEN);

    /* SOF, LSB, MSB */
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(SOF_CHAR, b);
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(0x04, b);
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(0x00, b);

    /* out of data */
    ASSERT_EQ_FMT(afeb_status_NEED_INPUT, am_frame_encode_byte(&ctx, &b), "%d");

    enum am_frame_encode_give_status stat;

    uint8_t const data1[] = {1,2};
    stat = am_frame_encode_give(&ctx, data1, sizeof(data1));
    ASSERT_EQ(afeg_status_OK, stat);

    /* data1[0], data1[1] */
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(1, b);
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(2, b);

    /* out of data */
    ASSERT_EQ_FMT(afeb_status_NEED_INPUT, am_frame_encode_byte(&ctx, &b), "%d");

    uint8_t const data2[] = {5,6};
    stat = am_frame_encode_give(&ctx, data2, sizeof(data2));
    ASSERT_EQ(afeg_status_OK, stat);

    /* data2[0], data2[1] */
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(5, b);
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(6, b);

    /* EOF */
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(EOF_CHAR, b);

    /* finished */
    ASSERT_EQ_FMT(afeb_status_DONE, am_frame_encode_byte(&ctx, &b), "%d");

    PASS();
}

TEST test_am_frame_encode_give__rejects_overflow_multiple_gives(void) {
    size_t const LEN = 4;
    uint8_t b;
    struct am_frame_encode_ctx ctx;
    am_frame_encode_init(&ctx, LEN);

    enum am_frame_encode_give_status stat;

    uint8_t const data1[] = {1,2};
    stat = am_frame_encode_give(&ctx, data1, sizeof(data1));
    ASSERT_EQ(afeg_status_OK, stat);

    /* SOF, LSB, MSB */
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(SOF_CHAR, b);
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(0x04, b);
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(0x00, b);

    /* data1[0], data1[1] */
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(1, b);
    ASSERT_EQ_FMT(afeb_status_OUT_VALID, am_frame_encode_byte(&ctx, &b), "%d");
    ASSERT_EQ(2, b);

    /* out of data */
    ASSERT_EQ_FMT(afeb_status_NEED_INPUT, am_frame_encode_byte(&ctx, &b), "%d");

    uint8_t const data2[] = {1,2,3};
    stat = am_frame_encode_give(&ctx, data2, sizeof(data2));
    ASSERT_EQ(afeg_status_OVERFLOW, stat);

    PASS();
}

TEST test_am_frame_encode_byte__produces_encoded_string(void) {
    char const data[] = "hi";
    uint8_t const expected[] = {
        SOF_CHAR, 0x02, 0x00, 'h', 'i', EOF_CHAR
    };
    uint8_t actual[sizeof(expected)] = { 0 };

    size_t const LEN = strlen(data);
    struct am_frame_encode_ctx ctx;

    am_frame_encode_init(&ctx, LEN);

    ASSERT_EQ(
        afeg_status_OK,
        am_frame_encode_give(&ctx, data, LEN));

    enum am_frame_encode_byte_status stat;

    for (size_t i = 0; i < sizeof(expected); i++) {
        stat = am_frame_encode_byte(&ctx, &actual[i]);
        ASSERT_EQ_FMT(afeb_status_OUT_VALID, stat, "%d");
    }

    uint8_t dummy;
    stat = am_frame_encode_byte(&ctx, &dummy);
    ASSERT_EQ(stat, afeb_status_DONE);

    ASSERT_MEM_EQ(expected, actual, sizeof(expected));

    PASS();
}

TEST test_am_frame_encode_byte__handles_0_length_messages(void) {
    uint8_t const expected[] = {
        SOF_CHAR, 0x00, 0x00, EOF_CHAR
    };
    uint8_t actual[sizeof(expected)] = { 0 };

    struct am_frame_encode_ctx ctx;
    am_frame_encode_init(&ctx, 0);

    enum am_frame_encode_byte_status stat;

    for (size_t i = 0; i < sizeof(expected); i++) {
        stat = am_frame_encode_byte(&ctx, &actual[i]);
        ASSERT_EQ_FMT(afeb_status_OUT_VALID, stat, "%d");
    }

    uint8_t dummy;
    stat = am_frame_encode_byte(&ctx, &dummy);
    ASSERT_EQ(stat, afeb_status_DONE);

    ASSERT_MEM_EQ(expected, actual, sizeof(expected));

    PASS();
}

TEST test_am_frame_encode_byte__escapes_data(void) {
    uint8_t const data[] = { SOF_CHAR, 'h', EOF_CHAR, 'i', ESC_CHAR };
    uint8_t const expected[] = {
        SOF_CHAR,
        0x05, 0x00,
        ESC_CHAR, SOF_ESC,
        'h',
        ESC_CHAR, EOF_ESC,
        'i',
        ESC_CHAR, ESC_ESC,
        EOF_CHAR,
    };
    uint8_t actual[sizeof(expected)] = { 0 };

    size_t const LEN = sizeof(data);
    struct am_frame_encode_ctx ctx;

    am_frame_encode_init(&ctx, LEN);

    ASSERT_EQ(
        afeg_status_OK,
        am_frame_encode_give(&ctx, data, LEN));

    enum am_frame_encode_byte_status stat;

    for (size_t i = 0; i < sizeof(expected); i++) {
        stat = am_frame_encode_byte(&ctx, &actual[i]);
        ASSERT_EQ_FMT(afeb_status_OUT_VALID, stat, "%d");
    }

    uint8_t dummy;
    stat = am_frame_encode_byte(&ctx, &dummy);
    ASSERT_EQ(stat, afeb_status_DONE);

    ASSERT_MEM_EQ(expected, actual, sizeof(expected));

    PASS();
}

TEST test_am_frame_encode_byte__escapes_len_lsb(void) {
    uint8_t const data[27] = { 0 };
    uint8_t const expected[32] = {
        [0] = SOF_CHAR,
        [1] = ESC_CHAR, // 27 == 0x1b,
        [2] = ESC_ESC,
        [3] = 0,
        [31] = EOF_CHAR,
    };
    uint8_t actual[sizeof(expected)] = { 0 };

    size_t const LEN = sizeof(data);
    struct am_frame_encode_ctx ctx;

    am_frame_encode_init(&ctx, LEN);

    ASSERT_EQ(
        afeg_status_OK,
        am_frame_encode_give(&ctx, data, LEN));

    enum am_frame_encode_byte_status stat;

    for (size_t i = 0; i < sizeof(expected); i++) {
        stat = am_frame_encode_byte(&ctx, &actual[i]);
        ASSERT_EQ_FMT(afeb_status_OUT_VALID, stat, "%d");
    }

    uint8_t dummy;
    stat = am_frame_encode_byte(&ctx, &dummy);
    ASSERT_EQ(stat, afeb_status_DONE);

    ASSERT_MEM_EQ(expected, actual, sizeof(expected));

    PASS();
}

TEST test_am_frame_encode_byte__escapes_len_msb(void) {
    uint8_t const data[0x1B00] = { 0 };
    size_t const LEN = sizeof(data);

#define EXP_LEN (sizeof(data) + 4 + 1)
    uint8_t expected[EXP_LEN] = { 0 };
    expected[0] = SOF_CHAR;
    expected[1] = 0;
    expected[2] = ESC_CHAR; // 27 == 0x1b,
    expected[3] = ESC_ESC;
    expected[EXP_LEN - 1] = EOF_CHAR;
#undef EXP_LEN
    uint8_t actual[sizeof(expected)] = { 0 };


    struct am_frame_encode_ctx ctx;

    am_frame_encode_init(&ctx, LEN);

    ASSERT_EQ(
        afeg_status_OK,
        am_frame_encode_give(&ctx, data, LEN));

    enum am_frame_encode_byte_status stat;

    for (size_t i = 0; i < sizeof(expected); i++) {
        stat = am_frame_encode_byte(&ctx, &actual[i]);
        ASSERT_EQ_FMT(afeb_status_OUT_VALID, stat, "%d");
    }

    uint8_t dummy;
    stat = am_frame_encode_byte(&ctx, &dummy);
    ASSERT_EQ(stat, afeb_status_DONE);

    ASSERT_MEM_EQ(expected, actual, sizeof(expected));

    PASS();
}

TEST test_am_frame_encode_byte__done_is_sticky(void) {
    uint8_t const data[] = {'A'};

    struct am_frame_encode_ctx ctx;
    am_frame_encode_init(&ctx, sizeof(data));

    enum am_frame_encode_give_status const gstat =
        am_frame_encode_give(&ctx, data, sizeof(data));
    ASSERT_EQ_FMT(afeg_status_OK, gstat, "%d");

    uint8_t byte;
    while (afeb_status_OUT_VALID == am_frame_encode_byte(&ctx, &byte)) {
        ;
    }

    // Make sure calling after DONE has occurred still results in DONE.
    ASSERT_EQ(
        afeb_status_DONE,
        am_frame_encode_byte(&ctx, &byte));
    ASSERT_EQ(
        afeb_status_DONE,
        am_frame_encode_byte(&ctx, &byte));

    PASS();

}

TEST test_am_frame_encode_byte__escapes_len(void) {
    uint8_t const data[0x1B1B] = { 'A', SOF_CHAR };
    size_t const LEN = sizeof(data);

#define EXP_LEN (sizeof(data) /* the data */     \
                 + 4 /* the overhead */          \
                 + 2 /* the length escapes */    \
                 + 1 /* the data escape */)
    uint8_t expected[EXP_LEN] = { 0 };
    expected[0] = SOF_CHAR;
    expected[1] = ESC_CHAR; // 27 == 0x1b,
    expected[2] = ESC_ESC;
    expected[3] = ESC_CHAR; // 27 == 0x1b,
    expected[4] = ESC_ESC;
    expected[5] = 'A';
    expected[6] = ESC_CHAR; // data escape
    expected[7] = SOF_ESC;
    expected[EXP_LEN - 1] = EOF_CHAR;
#undef EXP_LEN
    uint8_t actual[sizeof(expected)] = { 0 };


    struct am_frame_encode_ctx ctx;

    am_frame_encode_init(&ctx, LEN);

    ASSERT_EQ(
        afeg_status_OK,
        am_frame_encode_give(&ctx, data, LEN));

    enum am_frame_encode_byte_status stat;

    for (size_t i = 0; i < sizeof(expected); i++) {
        stat = am_frame_encode_byte(&ctx, &actual[i]);
        ASSERT_EQ_FMT(afeb_status_OUT_VALID, stat, "%d");
    }

    uint8_t dummy;
    stat = am_frame_encode_byte(&ctx, &dummy);
    ASSERT_EQ(stat, afeb_status_DONE);

    ASSERT_MEM_EQ(expected, actual, sizeof(expected));

    PASS();
}

TEST test_am_frame_encode_buffer__works_pretty_okay(void) {
    uint8_t const data[0x1B1B] = { 'A', SOF_CHAR };
    size_t const LEN = sizeof(data);

#define EXP_LEN (sizeof(data) /* the data */     \
                 + 4 /* the overhead */          \
                 + 2 /* the length escapes */    \
                 + 1 /* the data escape */)
    uint8_t expected[EXP_LEN] = { 0 };
    expected[0] = SOF_CHAR;
    expected[1] = ESC_CHAR; // 27 == 0x1b,
    expected[2] = ESC_ESC;
    expected[3] = ESC_CHAR; // 27 == 0x1b,
    expected[4] = ESC_ESC;
    expected[5] = 'A';
    expected[6] = ESC_CHAR; // data escape
    expected[7] = SOF_ESC;
    expected[EXP_LEN - 1] = EOF_CHAR;
#undef EXP_LEN
    // TODO: figure out how to not have this trailing byte on the end
    // of the actual to avoid having to call things again.
    uint8_t actual[sizeof(expected) + 1] = { 0 };

    struct am_frame_encode_ctx ctx;
    size_t used = 0;
    enum am_frame_encode_buffer_status stat;

    /*************************/
    /* All-at-once encoding. */
    /*************************/
    am_frame_encode_init(&ctx, LEN);

    ASSERT_EQ(
        afeg_status_OK,
        am_frame_encode_give(&ctx, data, LEN));

    used = 0;
    stat = am_frame_encode_buffer(&ctx,
                                  actual,
                                  sizeof(actual),
                                  &used);

    ASSERT_EQ_FMT(afebu_status_BUFFER_VALID, stat, "%d");
    ASSERT_EQ(sizeof(expected), used);

    ASSERT_MEM_EQ(expected, actual, sizeof(expected));

    stat = am_frame_encode_buffer(&ctx,
                                  actual,
                                  sizeof(expected),
                                  &used);
    ASSERT_EQ(afebu_status_DONE, stat);


    /*************************/
    /* First several bytes   */
    /*************************/
    size_t const SMALL_RUN = 128;
    am_frame_encode_init(&ctx, LEN);

    ASSERT_EQ(
        afeg_status_OK,
        am_frame_encode_give(&ctx, data, LEN));

    used = 0;
    stat = am_frame_encode_buffer(&ctx,
                                  actual,
                                  SMALL_RUN,
                                  &used);

    ASSERT_EQ(afebu_status_BUFFER_FULL, stat);
    ASSERT_EQ(SMALL_RUN, used);

    ASSERT_MEM_EQ(expected, actual, SMALL_RUN);

    /*************************/
    /* Not enough input      */
    /*************************/
    size_t const SMALL_DATA = 128;
    size_t const EXP_SIZE =
        SMALL_DATA +
        3 + // SOF + len
        2 + // len escapes
        1; // data escape

    am_frame_encode_init(&ctx, LEN);

    ASSERT_EQ(
        afeg_status_OK,
        am_frame_encode_give(&ctx, data, SMALL_DATA));

    used = 0;
    stat = am_frame_encode_buffer(&ctx,
                                  actual,
                                  sizeof(expected),
                                  &used);

    ASSERT_EQ(afebu_status_BUFFER_VALID, stat);
    ASSERT_EQ_FMT(EXP_SIZE, used, "%u");

    ASSERT_MEM_EQ(expected, actual, used);

    stat = am_frame_encode_buffer(&ctx,
                                  actual,
                                  sizeof(expected),
                                  &used);
    ASSERT_EQ(afebu_status_NEED_INPUT, stat);

    PASS();
}

SUITE(suite_am_frame_encode) {
    RUN_TEST(test_am_frame_encode_init__saves_length);
    RUN_TEST(test_am_frame_encode_give__accepts_properly_sized_input);
    RUN_TEST(test_am_frame_encode_give__rejects_too_much_input);
    RUN_TEST(test_am_frame_encode_give__rejects_before_previous_give_consumed);
    RUN_TEST(test_am_frame_encode_give__allows_multiple_gives);
    RUN_TEST(test_am_frame_encode_give__rejects_overflow_multiple_gives);
    RUN_TEST(test_am_frame_encode_byte__produces_encoded_string);
    RUN_TEST(test_am_frame_encode_byte__handles_0_length_messages);
    RUN_TEST(test_am_frame_encode_byte__escapes_data);
    RUN_TEST(test_am_frame_encode_byte__escapes_len_lsb);
    RUN_TEST(test_am_frame_encode_byte__escapes_len_msb);
    RUN_TEST(test_am_frame_encode_byte__escapes_len);
    RUN_TEST(test_am_frame_encode_byte__done_is_sticky);
    RUN_TEST(test_am_frame_encode_buffer__works_pretty_okay);
}

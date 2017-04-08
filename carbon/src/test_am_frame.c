#include "test_am_frame.h"
#include "am_frame_encode.h"
#include "am_frame_decode.h"

#include "theft.h"
#include "greatest.h"

static void *buff_alloc(struct theft *t, theft_seed seed, void *udata);
static void buff_free(void *instance, void *env);
static theft_hash buff_hash(void *instance, void *env);
static void *buff_shrink(void *instance, uint32_t tactic, void *penv);
static void buff_print(FILE *f, void *instance, void *env);

static struct theft_type_info const random_buffer_info = {
    .alloc = buff_alloc,
    .free = buff_free,
    .hash = buff_hash,
    .shrink = buff_shrink,
    .print = buff_print,
};

TEST frame_encode_decode_should_round_trip(void) {
    (void)random_buffer_info;
    SKIP();
};

SUITE(suite_am_frame) {
    RUN_TEST(frame_encode_decode_should_round_trip);
};

static void *buff_alloc(struct theft *t, theft_seed seed, void *udata) {
    (void)t;
    (void)seed;
    (void)udata;

    return NULL;
}

static void buff_free(void *instance, void *env) {
    (void)instance;
    (void)env;
}

static theft_hash buff_hash(void *instance, void *env) {
    (void)instance;
    (void)env;

    theft_hash h = 0;

    return h;
}

static void *buff_shrink(void *instance, uint32_t tactic, void *penv) {
    (void)instance;
    (void)tactic;
    (void)penv;

    return NULL;
}

static void buff_print(FILE *f, void *instance, void *env) {
    (void)f;
    (void)instance;
    (void)env;
}

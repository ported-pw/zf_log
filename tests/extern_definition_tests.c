#define ZF_LOG_EXTERN_TAG_PREFIX
#define ZF_LOG_EXTERN_GLOBAL_FORMAT
#define ZF_LOG_EXTERN_GLOBAL_OUTPUT
#define ZF_LOG_EXTERN_GLOBAL_OUTPUT_LEVEL
#include <zf_log.c>
#include "zf_test.h"

enum { MEM_WIDTH = 8 };
static void mock_output_callback(zf_log_output_ctx *ctx);

ZF_LOG_DEFINE_TAG_PREFIX = "MOCK_PREFIX";
ZF_LOG_DEFINE_GLOBAL_FORMAT =
{
	0xc0defade
};
ZF_LOG_DEFINE_GLOBAL_OUTPUT =
{
	0xcafebabe,
	mock_output_callback
};
ZF_LOG_DEFINE_GLOBAL_OUTPUT_LEVEL = 0xdeadbeef;

static void mock_output_callback(zf_log_output_ctx *ctx)
{
	(void)ctx;
}

static void test_static_initialization()
{
	TEST_VERIFY_TRUE(0 == strcmp(_zf_log_tag_prefix, "MOCK_PREFIX"));
	TEST_VERIFY_EQUAL(_zf_log_global_format.mem_width, 0xc0defade);
	TEST_VERIFY_EQUAL(_zf_log_global_output.put_mask, 0xcafebabe);
	TEST_VERIFY_EQUAL(_zf_log_global_output.output_cb, mock_output_callback);
	TEST_VERIFY_EQUAL(_zf_log_global_output_lvl, (int)0xdeadbeef);
}

int main(int argc, char *argv[])
{
	TEST_RUNNER_CREATE(argc, argv);

	TEST_EXECUTE(test_static_initialization());

	return TEST_RUNNER_EXIT_CODE();
}

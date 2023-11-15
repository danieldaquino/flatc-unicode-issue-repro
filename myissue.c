/* Minimal test with all headers generated into a single file. */
#include "build/myissue_generated.h"
#include "flatcc/support/hexdump.h"

int main(int argc, char *argv[])
{
    int ret;
    void *buf;
    size_t size;
    flatcc_builder_t builder, *B;

    (void)argc;
    (void)argv;

    B = &builder;
    flatcc_builder_init(B);

    char* json = "{\"name\":\"ひらがな\",\"height\":2}";
    
    // Parse JSON into a flatbuffer
    Eclectic_FooBar_ref_t ref;
    if (!parse_json(B, json, strlen(json), 0, &ref)) {
        printf("failed to parse json\n");
        return 1;
    }
    
    // Check and print the "name" field of the flatbuffer
    if (Eclectic_FooBar_name_is_present(ref)) {
        printf("name: %s\n", Eclectic_FooBar_name(ref));
    } else {
        printf("name is not present\n");
    }

    flatcc_builder_clear(B);
    return ret;
}

static int parse_json(flatcc_builder_t *B,
        const char *buf, size_t bufsiz, int flags, Eclectic_FooBar_ref_t *profile)
{
	flatcc_json_parser_t parser, *ctx = &parser;
	flatcc_json_parser_init(ctx, B, buf, buf + bufsiz, flags);

	if (flatcc_builder_start_buffer(B, 0, 0, 0))
		return 0;

	Eclectic_FooBar_parse_json_table(ctx, buf, buf + bufsiz, profile);
	if (ctx->error)
		return 0;
 
	if (!flatcc_builder_end_buffer(B, *profile))
		return 0;

	ctx->end_loc = buf;

	return 1;
}

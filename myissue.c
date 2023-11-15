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
    
    /* Parse the JSON into a FlatBuffers table. */
    flatbuffers_parser_t parser;
    flatbuffers_parser_init(&parser);
    if (!flatbuffers_parser_parse(&parser, json, strlen(json), 1)) {
        printf("could not parse JSON: %s\n", flatbuffers_parser_error_string(&parser));
        return 1;
    }
    flatcc_json_parser_t ctx;
    flatcc_json_parser_init(&ctx, flatbuffers_parser_get_buf(&parser), flatbuffers_parser_get_buf_size(&parser));
    flatcc_json_parser_skip_whitespace(&ctx);
    flatbuffers_table_t ref;
    buf = Eclectic_FooBar_parse_json_table(&ctx, buf, end, &ref);
    if (!buf) {
        printf("could not parse JSON as FlatBuffers table: %s\n", flatcc_json_parser_error_string(&ctx));
        return 1;
    }
    
    // Check and print the "name" field of the parsed table.
    if (!Eclectic_FooBar_name_has_value(ref)) {
        printf("name field is missing\n");
        return 1;
    }

    flatcc_builder_clear(B);
    return ret;
}

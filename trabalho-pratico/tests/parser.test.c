#include "parser.h"

#include "../lib/greatest.h"
#include "common.h"

TEST line_parsing(void) {
  char *line = strdup(
      "000000000416;Duarte Ribeiro;06/12/1943;M;premium;91-CD-15;Gonça "
      "City;13/3/2020;active");
  char **tokens = parse_line(line, MAX_DRIVER_TOKENS);

  ASSERT_STR_EQ("000000000416", tokens[0]);
  ASSERT_STR_EQ("Duarte Ribeiro", tokens[1]);
  ASSERT_STR_EQ("06/12/1943", tokens[2]);
  ASSERT_STR_EQ("M", tokens[3]);
  ASSERT_STR_EQ("premium", tokens[4]);
  ASSERT_STR_EQ("91-CD-15", tokens[5]);
  ASSERT_STR_EQ("Gonça City", tokens[6]);
  ASSERT_STR_EQ("13/3/2020", tokens[7]);
  ASSERT_STR_EQ("active", tokens[8]);

  free(tokens);
  free(line);

  PASS();
}

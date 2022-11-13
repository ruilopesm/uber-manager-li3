#include "parser.h"

#include "../lib/greatest.h"
#include "common.h"

TEST parse_line_test(void) {
  char *line = strdup(
      "Margarida-AnMorais133;Margarida-Anita "
      "Morais;F;29/06/1989;31/12/2010;credit_card;active");
  char **tokens = parse_line(line, MAX_USER_TOKENS);

  ASSERT_STR_EQ("Margarida-AnMorais133", tokens[0]);
  ASSERT_STR_EQ("Margarida-Anita Morais", tokens[1]);
  ASSERT_STR_EQ("F", tokens[2]);
  ASSERT_STR_EQ("29/06/1989", tokens[3]);
  ASSERT_STR_EQ("31/12/2010", tokens[4]);
  ASSERT_STR_EQ("credit_card", tokens[5]);
  ASSERT_STR_EQ("active", tokens[6]);

  free(line);
  free(tokens);

  PASS();
}

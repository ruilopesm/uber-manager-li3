#ifndef OUTPUT_H
#define OUTPUT_H

#include <ncurses.h>
#include <stdio.h>

#include "base/interactive.h"

typedef void (*file_output_function_pointer)(FILE *file, void *result);

typedef void (*window_output_function_pointer)(MANAGER manager, WINDOW *win,
                                               char *title, void *result);

void write_query_result(FILE *output_file, void *result, char query_type);

void draw_query_result(MANAGER manager, WINDOW *win, char *title, void *result,
                       char query_type);

void write_query1_result(FILE *output_file, void *result);

void draw_query1_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

void write_query2_result(FILE *output_file, void *result);

void draw_query2_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

void write_query3_result(FILE *output_file, void *result);

void draw_query3_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

void write_query4_result(FILE *output_file, void *result);

void draw_query4_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

void write_query5_result(FILE *output_file, void *result);

void draw_query5_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

void write_query6_result(FILE *output_file, void *result);

void draw_query6_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

void write_query7_result(FILE *output_file, void *result);

void draw_query7_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

void write_query8_result(FILE *output_file, void *result);

void draw_query8_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

void write_query9_result(FILE *output_file, void *result);

void draw_query9_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

#endif

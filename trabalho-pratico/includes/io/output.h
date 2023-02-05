#ifndef OUTPUT_H
#define OUTPUT_H

#include <ncurses.h>
#include <stdio.h>

#include "base/interactive.h"

typedef void (*file_output_function_pointer)(FILE *file, void *result);

typedef void (*window_output_function_pointer)(MANAGER manager, WINDOW *win,
                                               char *title, void *result);

/**
 * @brief Wrapper function that writes the given query result of a query to a
 * file
 *
 * @param output_file - The file of type `FILE *` where the result will be
 * written
 * @param result - The result of type `void *` that will be written to the file
 * @param query_type - The query type of type `char` that will be written to the
 * file
 */
void write_query_result(FILE *output_file, void *result, char query_type);

/**
 * @brief Function that draws the result of a query to a window
 *
 * @param manager - The manager of type `MANAGER`
 * @param win - The window of type `WINDOW *` where the result will be drawn
 * @param title - The title of type `char *` that will be drawn to the window
 * @param result - The result of type `void *` that will be drawn to the window
 * @param query_type - The query type of type `char` that will be drawn to the
 * window
 */
void draw_query_result(MANAGER manager, WINDOW *win, char *title, void *result,
                       char query_type);

/**
 * @brief Function that writes the result of the query one result to a file
 *
 * @param output_file - The file of type `FILE *` where the result will be
 * written
 * @param result - The result of type `void *` that will be written to the file
 */
void write_query1_result(FILE *output_file, void *result);

/**
 * @brief Function that draws the result of the query one result to a window
 *
 * @param manager - The manager of type `MANAGER`
 * @param win - The window of type `WINDOW *` where the result will be drawn
 * @param title - The title of type `char *` that will be drawn to the window
 * @param result - The result of type `void *` that will be drawn to the window
 */
void draw_query1_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

/**
 * @brief Function that writes the result of the query two result to a file
 *
 * @param output_file - The file of type `FILE *` where the result will be
 * written
 * @param result - The result of type `void *` that will be written to the file
 */
void write_query2_result(FILE *output_file, void *result);

/**
 * @brief Function that draws the result of the query two result to a window
 *
 * @param manager - The manager of type `MANAGER`
 * @param win - The window of type `WINDOW *` where the result will be drawn
 * @param title - The title of type `char *` that will be drawn to the window
 * @param result - The result of type `void *` that will be drawn to the window
 */
void draw_query2_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

/**
 * @brief Function that writes the result of the query three result to a file
 *
 * @param output_file - The file of type `FILE *` where the result will be
 * written
 * @param result - The result of type `void *` that will be written to the file
 */
void write_query3_result(FILE *output_file, void *result);

/**
 * @brief Function that draws the result of the query three result to a window
 *
 * @param manager - The manager of type `MANAGER`
 * @param win - The window of type `WINDOW *` where the result will be drawn
 * @param title - The title of type `char *` that will be drawn to the window
 * @param result - The result of type `void *` that will be drawn to the window
 */
void draw_query3_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

/**
 * @brief Function that writes the result of the query four result to a file
 *
 * @param output_file - The file of type `FILE *` where the result will be
 * written
 * @param result - The result of type `void *` that will be written to the file
 */
void write_query4_result(FILE *output_file, void *result);

/**
 * @brief Function that draws the result of the query four result to a window
 *
 * @param manager - The manager of type `MANAGER`
 * @param win - The window of type `WINDOW *` where the result will be drawn
 * @param title - The title of type `char *` that will be drawn to the window
 * @param result - The result of type `void *` that will be drawn to the window
 */
void draw_query4_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

/**
 * @brief Function that writes the result of the query five result to a file
 *
 * @param output_file - The file of type `FILE *` where the result will be
 * written
 * @param result - The result of type `void *` that will be written to the file
 */
void write_query5_result(FILE *output_file, void *result);

/**
 * @brief Function that draws the result of the query five result to a window
 *
 * @param manager - The manager of type `MANAGER`
 * @param win - The window of type `WINDOW *` where the result will be drawn
 * @param title - The title of type `char *` that will be drawn to the window
 * @param result - The result of type `void *` that will be drawn to the window
 */
void draw_query5_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

/**
 * @brief Function that writes the result of the query six result to a file
 *
 * @param output_file - The file of type `FILE *` where the result will be
 * written
 * @param result - The result of type `void *` that will be written to the file
 */
void write_query6_result(FILE *output_file, void *result);

/**
 * @brief Function that draws the result of the query six result to a window
 *
 * @param manager - The manager of type `MANAGER`
 * @param win - The window of type `WINDOW *` where the result will be drawn
 * @param title - The title of type `char *` that will be drawn to the window
 * @param result - The result of type `void *` that will be drawn to the window
 */
void draw_query6_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

/**
 * @brief Function that writes the result of the query six result to a file
 *
 * @param output_file - The file of type `FILE *` where the result will be
 * written
 * @param result - The result of type `void *` that will be written to the file
 */
void write_query7_result(FILE *output_file, void *result);

/**
 * @brief Function that draws the result of the query six result to a window
 *
 * @param manager - The manager of type `MANAGER`
 * @param win - The window of type `WINDOW *` where the result will be drawn
 * @param title - The title of type `char *` that will be drawn to the window
 * @param result - The result of type `void *` that will be drawn to the window
 */
void draw_query7_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

/**
 * @brief Function that writes the result of the query eight result to a file
 *
 * @param output_file - The file of type `FILE *` where the result will be
 * written
 * @param result - The result of type `void *` that will be written to the file
 */
void write_query8_result(FILE *output_file, void *result);

/**
 * @brief Function that draws the result of the query eight result to a window
 *
 * @param manager - The manager of type `MANAGER`
 * @param win - The window of type `WINDOW *` where the result will be drawn
 * @param title - The title of type `char *` that will be drawn to the window
 * @param result - The result of type `void *` that will be drawn to the window
 */
void draw_query8_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

/**
 * @brief Function that writes the result of the query nine result to a file
 *
 * @param output_file - The file of type `FILE *` where the result will be
 * written
 * @param result - The result of type `void *` that will be written to the file
 */
void write_query9_result(FILE *output_file, void *result);

/**
 * @brief Function that draws the result of the query nine result to a window
 *
 * @param manager - The manager of type `MANAGER`
 * @param win - The window of type `WINDOW *` where the result will be drawn
 * @param title - The title of type `char *` that will be drawn to the window
 * @param result - The result of type `void *` that will be drawn to the window
 */
void draw_query9_result(MANAGER manager, WINDOW *win, char *title,
                        void *result);

#endif

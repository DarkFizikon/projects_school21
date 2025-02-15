#ifndef S21_CAT_H
#define S21_CAT_H
#define _GNU_SOURCE

#include <errno.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *short_flags = "beEstTnv";
const struct option long_flags[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                    {"number", no_argument, NULL, 'n'},
                                    {"squeeze-blank", no_argument, NULL, 's'},
                                    {NULL, 0, NULL, 0}};

typedef struct {
  bool number_nonblank;   //-b
  bool show_stroke_ends;  //-e
  bool number;            //-n
  bool squeeze_blank;     //-s
  bool show_tabs;         //-t
  bool show_hiddens;      //-v
} Flags;

int pars_args(int argc, char *argv[], Flags *flags);
void process_file(const char *filename, Flags *flags);
void print_file(Flags *flags, FILE *file);

#endif
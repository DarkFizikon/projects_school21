#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Общая структура для работы с флагами
typedef struct {
  bool use_expression;        // -e
  bool ignore_case;           // -i
  bool invert_match;          // -v
  bool count_matches;         // -c
  bool print_file_names;      // -l
  bool print_line_numbers;    // -n
  bool print_file_name_only;  // -h
  bool suppress_errors;       // -s
  bool pattern_from_file;     // -f
  bool only_matching;         // -o
} Flags;

const char *short_flags = "e:f:ivclnhso";
const struct option long_flags[] = {
    {"regexp", required_argument, NULL, 'e'},
    {"file", required_argument, NULL, 'f'},
    {"ignore-case", no_argument, NULL, 'i'},
    {"invert-match", no_argument, NULL, 'v'},
    {"count", no_argument, NULL, 'c'},
    {"files-with-matches", no_argument, NULL, 'l'},
    {"line-number", no_argument, NULL, 'n'},
    {"no-filename", no_argument, NULL, 'h'},
    {"silent", no_argument, NULL, 's'},
    {"only-matching", no_argument, NULL, 'o'},
    {NULL, 0, NULL, 0}};

void parse_args(int argc, char *argv[], Flags *flags, char *pattern_buffer);
void process_files(int argc, char *argv[], Flags *flags, char *pattern);
void find_matches(FILE *file, Flags *flags, const char *pattern,
                  const char *filename, int file_count);

#endif

#include "s21_grep.h"

void parse_args(int argc, char *argv[], Flags *flags, char *pattern_buffer) {
  int option;
  while ((option = getopt_long(argc, argv, short_flags, long_flags, NULL)) !=
         -1) {
    switch (option) {
      case 'e':
        flags->use_expression = true;
        if (strlen(pattern_buffer) > 0) strcat(pattern_buffer, "|");
        strcat(pattern_buffer, optarg);
        break;
      case 'f':
        flags->pattern_from_file = true;
        FILE *file = fopen(optarg, "r");
        if (!file) {
          if (!flags->suppress_errors) perror("grep");
          exit(1);
        }
        char line[8192];
        while (fgets(line, sizeof(line), file)) {
          line[strcspn(line, "\n")] = '\0';
          if (strlen(pattern_buffer) > 0) strcat(pattern_buffer, "|");
          strcat(pattern_buffer, line);
        }
        fclose(file);
        break;
      case 'i':
        flags->ignore_case = true;
        break;
      case 'v':
        flags->invert_match = true;
        break;
      case 'c':
        flags->count_matches = true;
        break;
      case 'l':
        flags->print_file_names = true;
        break;
      case 'n':
        flags->print_line_numbers = true;
        break;
      case 'h':
        flags->print_file_name_only = true;
        break;
      case 's':
        flags->suppress_errors = true;
        break;
      case 'o':
        flags->only_matching = true;
        break;
      default:
        exit(1);
    }
  }

  if (!flags->use_expression && !flags->pattern_from_file && optind < argc) {
    strcpy(pattern_buffer, argv[optind++]);
  }
}

void process_files(int argc, char *argv[], Flags *flags, char *pattern) {
  int file_count = argc - optind;
  for (int i = optind; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (!file) {
      if (!flags->suppress_errors) perror("grep");
      return;
    }
    find_matches(file, flags, pattern, argv[i], file_count);
    fclose(file);
  }
}

void find_matches(FILE *file, Flags *flags, const char *pattern,
                  const char *filename, int file_count) {
  regex_t regex;
  int cflags = REG_EXTENDED | (flags->ignore_case ? REG_ICASE : 0);
  if (regcomp(&regex, pattern, cflags)) {
    fprintf(stderr, "grep: Invalid regular expression\n");
    exit(1);
  }

  char line[8192];
  int line_number = 1;
  int match_count = 0;

  while (fgets(line, sizeof(line), file)) {
    int matched = !regexec(&regex, line, 0, NULL, 0);
    if (flags->invert_match) matched = !matched;

    if (matched) {
      if (flags->count_matches) {
        match_count++;
      } else if (flags->print_file_names) {
        printf("%s\n", filename);
        break;
      } else {
        if (file_count > 1 && !flags->print_file_name_only)
          printf("%s:", filename);
        if (flags->print_line_numbers) printf("%d:", line_number);
        printf("%s", line);
      }
    }
    line_number++;
  }

  if (flags->count_matches) {
    if (file_count > 1 && !flags->print_file_name_only) printf("%s:", filename);
    printf("%d\n", match_count);
  }

  regfree(&regex);
}

int main(int argc, char *argv[]) {
  Flags flags = {0};
  char pattern[8192] = {0};

  parse_args(argc, argv, &flags, pattern);
  process_files(argc, argv, &flags, pattern);

  return 0;
}

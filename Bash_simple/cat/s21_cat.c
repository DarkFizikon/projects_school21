#include "s21_cat.h"

int pars_args(int argc, char *argv[], Flags *flags) {
  int result;

  while ((result = getopt_long(argc, argv, short_flags, long_flags, NULL)) !=
         -1) {
    switch (result) {
      case 'b':
        flags->number_nonblank = 1;
        flags->number = 0;
        break;
      case 'e':
        flags->show_stroke_ends = 1;
        flags->show_hiddens = 1;
        break;
      case 'E':
        flags->show_stroke_ends = 1;
        break;
      case 'n':
        flags->number = 1;
        flags->number_nonblank = 0;
        break;
      case 's':
        flags->squeeze_blank = 1;
        break;
      case 't':
        flags->show_tabs = 1;
        flags->show_hiddens = 1;
        break;
      case 'T':
        flags->show_tabs = 1;
        break;
      case 'v':
        flags->show_hiddens = 1;
        break;
      default:
        fprintf(stderr, "cat: Unknown flag: -- %c\n", result);
        fprintf(stderr, "Use cat [-beEnstTv] [file ...]\n");
        return 1;
    }
  }
  return 0;
}

void process_file(const char *filename, Flags *flags) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "cat: %s: %s\n", filename, strerror(errno));
  } else {
    print_file(flags, file);
    fclose(file);
  }
}

void print_file(Flags *flags, FILE *file) {
  int current_char, previous_char = '\n', blank_count = 0, line_number = 1;
  bool is_first_line = true;

  while ((current_char = fgetc(file)) != EOF) {
    if (flags->squeeze_blank) {
      if (current_char == 10) blank_count++;
      if (current_char != 10) blank_count = 0;
    }

    if (current_char == 10 && (!(flags->squeeze_blank) || blank_count < 3)) {
      if ((is_first_line && (flags->number)) ||
          ((flags->number) && previous_char == 10)) {
        printf("%6d\t", line_number++);
      }
      if (flags->show_stroke_ends) printf("$");
      putchar(current_char);
    } else if (current_char != 10) {
      if ((previous_char == 10 || is_first_line) &&
          ((flags->number) || (flags->number_nonblank))) {
        printf("%6d\t", line_number++);
      }
      if (current_char < 32 && current_char != 9 && current_char != 10 &&
          (flags->show_hiddens)) {
        printf("^%c", current_char + 64);
      } else if (current_char == 127 && (flags->show_hiddens)) {
        printf("^?");
      } else if (current_char >= 128 && current_char <= 159 &&
                 (flags->show_hiddens)) {
        printf("M-^%c", current_char - 64);
      } else if (current_char >= 160 && current_char < 255 &&
                 (flags->show_hiddens)) {
        printf("M-%c", current_char - 128);
      } else if (current_char == 9 && (flags->show_tabs)) {
        printf("^I");
      } else {
        printf("%c", current_char);
      }
    }
    previous_char = current_char;
    is_first_line = false;
  }
}

int main(int argc, char *argv[]) {
  Flags flags = {0};

  if (pars_args(argc, argv, &flags)) {
    return 1;
  }
  for (int index = optind; index < argc; index++) {
    process_file(argv[index], &flags);
  }

  return 0;
}

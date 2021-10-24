#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
  char *buf = NULL;
  size_t len = 0;
  ssize_t line;
  int color = 31;
  int lines = 0, offset = 0;
  char daymsg[] = "--- Day changed";
  FILE *f;

  if (pledge("stdio wpath cpath", NULL) == -1) {
    fprintf(stderr, "pledge failed\n");
    exit(1);
  }

  if (argc > 1) {
    offset = atoi(argv[1]);
  }

  while ((line = getline(&buf, &len, stdin)) != -1) {
    lines++;
    if (lines < offset)
      continue;

    if (len > 9) {
      if (buf[7] == '!')
        continue;
    }

    if (strncmp(buf, daymsg, sizeof(daymsg) - 1) == 0) {
      if (lines > offset + 1) {
        f = fopen(".talkingoffset", "w");
        if (f == NULL) {
          printf("fopen failed\n");
          exit(1);
        }
        fprintf(f, "%i", lines - 1);
        fprintf(stderr, "Wrote new offset: %i\n", lines - 1);
        fclose(f);
      }
    }

    buf[line - 1] = '\0';

    printf("\x1b[%im%s\x1b[0m\n", color, buf);
    color++;

    if (color == 34) {
      color++;
    } else if (color > 36) {
      color = 31;
    }
  }

  /* unreached - just an annotation in case something changes */
  free(buf);
  return 0;
}

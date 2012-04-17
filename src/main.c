#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

void exec_ccg (char *buffer, char memory[8192], int *i, int readed, int ptr)
{
  int ptr2 = *i + 1;
  int cnt = 0;
  int b = 0;

  if (memory[ptr] == 0)
  {
    while (ptr2 < readed && !b)
    {
      switch (buffer[ptr2])
      {
        case '[':
          cnt++;
          break;
        case ']':
          if (!cnt)
            b = 1;
          else
            cnt--;
          break;
        default:
          break;
      }
      ptr2++;
    }
    *i = ptr2;
  }
}

void exec_ccd (char *buffer, char memory[8192], int *i, int readed, int ptr)
{
  int ptr2 = *i - 1;
  int cnt = 0;
  int b = 0;

  if (memory[ptr] != 0)
  {
    while (ptr2 < readed && !b)
    {
      switch (buffer[ptr2])
      {
        case ']':
          cnt++;
          break;
        case '[':
          if (!cnt)
            b = 1;
          else
            cnt--;
          break;
        default:
          break;
      }
      ptr2--;
    }
    *i = ptr2 + 1;
  }
}

int main (int argc, char** argv)
{
  char        memory[8192];
  char        *buffer;
  int         readed = 0;
  int         ptr = 0;
  int         f = 0;
  struct stat st;

  for (int i = 1; i < argc; i++)
  {
    f = open (argv[i], O_RDONLY);
    if (f == -1)
      return 2;
    if (-1 == fstat (f, &st))
      return 3;
    buffer = malloc (sizeof (char) * st.st_size);
    if (!buffer)
      return 1;
    while ((readed = read (f, buffer, st.st_size)) != 0)
    {
      for (int i = 0; i < readed; i++)
      {
        switch (buffer[i])
        {
          case '<':
            ptr--;
            break;
          case '>':
            ptr++;
            break;
          case '+':
            memory[ptr]++;
            break;
          case '-':
            memory[ptr]--;
            break;
          case '.':
            putchar (memory[ptr]);
            break;
          case ',':
            memory[ptr] = getchar ();
            break;
          case '[':
            exec_ccg (buffer, memory, &i, readed, ptr);
            break;
          case ']':
            exec_ccd (buffer, memory, &i, readed, ptr);
            break;
          default:
            break;
        }
      }
    }
    free (buffer);
    close (f);
  }
  return 0;
}

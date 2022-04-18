#include <stdio.h>

int fileEmpty(FILE *fp)
{
  if (NULL != fp)
  {
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);

    if (size == 0)
    {
      return 1;
    }
    return 0;
  }
}

int fileExists(char *fileName)
{
  FILE *file;
  if ((file = fopen(fileName, "rb")) != NULL)
  {
    fclose(file);
    return 1;
  }
  else
  {
    return 0;
  }
}
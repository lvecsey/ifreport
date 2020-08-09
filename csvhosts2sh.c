
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

  char hostname[240];

  char cmd_str[240];

  char *line;
  size_t len;
  FILE *fp;

  int retval;

  long int counter;
  
  fp = stdin;
  line = NULL;
  len = 0;

  counter = 0;

  printf("#!/bin/bash\n\n");
  
  while ((retval = getline(&line,&len,fp)) != -1) {

    if (len<=0) {
      continue;
    }

    counter++;
    
    if (counter==1) {
      continue;
    }

    retval = sscanf(line, "%[^,], \"%[^\"]\"", hostname, cmd_str);

    if (retval == 2) {
    
      printf("echo '\\section{%s}'\n", hostname);

      printf("ssh %s '%s'\n\n", hostname, cmd_str);

    }
      
  }

  printf("exit 0\n");
  
  return 0;

}

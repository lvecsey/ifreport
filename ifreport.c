
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

  char cmd_str[240];
  
  char *intf;

  int exit_status;

  int retval;

  FILE *fp;
  char *line;
  size_t len;
  
  intf = argc>1 ? argv[1] : NULL;

  if (intf == NULL) {
    fprintf(stderr, "%s: Please specify a valid interface.\n", __FUNCTION__);
    return -1;
  }

  printf("\\begin{verbatim}\n");

  printf("Interface: %s\n", intf);
  
  {
    
    line = NULL;
    len = 0;

    retval = sprintf(cmd_str, "/sbin/ethtool %s | grep -i Speed", intf);
    
    fp = popen(cmd_str, "r");
    if (fp==NULL) {
      perror("fopen");
      return -1;
    }

    while ((retval = getline(&line,&len,fp)) != -1) {
      if (len > 0) {
	printf("ethtool: %s", line);
      }
    }

    free(line);
      
    exit_status = pclose(fp);
    if (exit_status == -1) {
      perror("pclose");
      return -1;
    }

    line = NULL;
    len = 0;
    
    retval = sprintf(cmd_str, "/sbin/ifconfig %s | grep -i dropped", intf);
    
    fp = popen(cmd_str, "r");
    if (fp==NULL) {
      perror("fopen");
      return -1;
    }

    while ((retval = getline(&line,&len,fp)) != -1) {
      if (len > 0) {
	printf("ifconfig: %s", line);
      }
    }

    free(line);
      
    exit_status = pclose(fp);
    if (exit_status == -1) {
      perror("pclose");
      return -1;
    }
    
  }

  printf("\\end{verbatim}\n\n");
  
  return 0;

}

    

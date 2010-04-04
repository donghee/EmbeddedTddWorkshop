#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef MINGW
/* gcc -o watch watch.c -DMINGW */
#include <windows.h>
#define sleep(n) Sleep(1000 * n)
#define EX_USAGE -1
#define EX_SOFTWARE -1
#else
#include <sysexits.h>
#endif

#define MAXFILES 64

usage(argv)
char **argv;
{
  fprintf(stderr, "usage: %s <paths...> - <cmnds...>\n\
   <paths...> is/are the file/s to be monitored\n\
   <cmnds...> is/are the command/s to execute (quoted if arguments required)\n\
          e.g: watch *.tex - 'latex main' 'dvips -o ps main'\n", *argv);
  exit(EX_USAGE);
}

static int qstat(path, buf)
char *path;
struct stat *buf;
{
  if(stat(path, buf) == -1) {
    sleep(1);
    if(stat(path, buf) == -1) {
      fprintf(stderr, "watch: %s: file not found\n", path);
      exit(-1);
    }
  }
}

main(argc, argv)
char **argv;
{
  char cline[1024];
  int first, last, ptr, statp;
  struct stat old[MAXFILES], new[MAXFILES];

  first= last= 1;

  while((last < argc) && strcmp(argv[last], "-")) last++;

  if((ptr= last+1) >= argc) usage(argv);

  if(last > MAXFILES) {
    fprintf(stderr, "%s: too many files to watch\n", *argv);
    fflush(stderr);
    exit(EX_SOFTWARE);
  }

  *cline= '\0';

  while(ptr < argc) {
    strcat(cline, argv[ptr++]);
    strcat(cline, " ");
  }

  cline[strlen(cline)-1]= '\0';

 restart:
  for(ptr= first; ptr < last; ptr++) qstat(argv[ptr], old+ptr);

 retest:
  for(ptr= first; ptr < last; ptr++) {
    qstat(argv[ptr], new+ptr);
    if(old[ptr].st_mtime != new[ptr].st_mtime) {
      old[ptr].st_mtime= new[ptr].st_mtime;
      system(cline);
      goto restart;
    }
  }
  sleep(1);
  goto retest;
}

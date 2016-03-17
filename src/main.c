#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "first.h"

int main (int argc, char **argv)
{
  Arguments args = GetArguments(argc, argv);
  switch (args.mode)
        {           

        case 's':
          printf ("runnning std mode\n");
          RunInStdMode();
          break;  
        case 'c':
          printf ("runnning child mode\n");
          RunInChildMode();
          break;
        case 'o':
          printf ("runnning posix mode\n");
          if (args.amount == 0)
          {
            printf ("usage: --amount=N\n");
            exit(EXIT_FAILURE);
          }
          if (args.amount > 49)
          {
            printf ("more than 50\n");
            exit(EXIT_FAILURE);
          }
           printf ("signals amount : %d\n", args.amount);
           RunInPosixMode(args.amount);
          break;
        case 'k':
          printf ("runnning kill mode\n");
          if (args.signalVal == 0 || args.pidVal == 0)
          {
            printf ("usage: --signal=SIGNO --pid=PID)\n");
            exit(EXIT_FAILURE);
          }
           printf ("signal value : %d\npid : %i\n", args.signalVal, args.pidVal);
           if(kill(args.pidVal, args.signalVal) < 0){
              perror("kill problems");
           }
           
          break;
        case 'i':
          printf ("runnning pipe mode\n");
          RunInPipeMode();
          break;

        default:
          printf ("usage: --mode=(std|child|posix|kill)\n");
        }
 
  exit (EXIT_SUCCESS);
}
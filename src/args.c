#include "first.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>


Arguments GetArguments(int argc, char * const argv[]){
	Arguments args = { .mode = '?', .amount = 0, .signalVal = 0, .pidVal = 0};

	int c;

  	static struct option long_options[] =
    {       
      {"mode",  required_argument, 0, 'm'},
      {"amount",  required_argument, 0, 'a'},
      {"signal",    required_argument, 0, 's'},
      {"pid",    required_argument, 0, 'p'},
      {0, 0, 0, 0}
    };
  	while (1)
    {
      int option_index = 0;

      c = getopt_long (argc, argv, "abc:d:f:",
                       long_options, &option_index);

      if (c == -1)
        break;

      switch (c)
        {        

        case 'm':
          printf ("option --mode with value `%s'\n", optarg);
          if (optarg[0] == 'p')
          {
          	args.mode = optarg[1];
          }
          else
          {
          	args.mode = optarg[0];
          }
          break;       

        case 'a':
          printf ("option --amount with value `%s'\n", optarg);
          args.amount = atoi(optarg);
          break;

        case 's':
          printf ("option --signal with value `%s'\n", optarg);
          args.signalVal = atoi(optarg);
          break;       

        case 'p':
          printf ("option --pid with value `%s'\n", optarg);
          args.pidVal = atoi(optarg);
          break;       

        default:
          abort ();
        }
    } 
    return args;

}

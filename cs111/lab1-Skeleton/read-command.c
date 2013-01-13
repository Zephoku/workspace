// UCLA CS 111 Lab 1 command reading

#include "command.h"
#include "command-internals.h"
#include <stdio.h>
#include <stdlib.h>
#include <error.h>

/* FIXME: You may need to add #include directives, macro definitions,
   static function definitions, etc.  */

/* FIXME: Define the type 'struct command_stream' here.  This should
   complete the incomplete type declaration in command.h.  */

typedef struct command_stream 
{
  // array of pointers pointing to c-strings
  char** command_list;
} command_stream;

command_stream_t
make_command_stream (int (*get_next_byte) (void *),
		     void *get_next_byte_argument)
{
  /* FIXME: Replace this with your implementation.  You may need to
     add auxiliary functions and otherwise modify the source code.
     You can also use external functions defined in the GNU C Library.  */

  // initialize memory allocation
  // count of characters
  int ch_count = 1;
  int pt_count = 1;
  int input_byte = 0;

  int i = 0;
  command_stream test = { NULL };
  command_stream_t result_stream = &test;
  result_stream->command_list = (char**) malloc(pt_count*sizeof(char**));
  for(i=0; i < pt_count; i++) 
  {
    result_stream->command_list[i] = NULL;
  }

  // initialize stream
  input_byte = (int)get_next_byte(get_next_byte_argument);

  while ((int)input_byte > 0)
  {
    // Separate commands by splitters
    /*
    if ((char)input_byte == ' ') 
    {
      ch_count = 1;
      pt_count++;
    }
    */

    // Reallocate memory for stream characters
    
    result_stream->command_list = (char**) realloc(result_stream->command_list, pt_count*sizeof(char**));
    result_stream->command_list[pt_count-1] = (char*) realloc(result_stream->command_list[pt_count-1],
        ch_count*sizeof(char*));
    result_stream->command_list[pt_count-1][ch_count-1] = (char)input_byte;
    input_byte = get_next_byte(get_next_byte_argument);
    ch_count+=1;
  }
  
  //command_stream cmd_stream;

  printf("%s", result_stream->command_list[0]);

  // returns stream as character array
  return result_stream;
}

command_t
read_command_stream (command_stream_t s)
{
  /* FIXME: Replace this with your implementation too.  */

  char* stream = (char*) s;
  int size = sizeof(s);
  int i =0;
  for(i=0; i<size ;i++) {
    printf("%c", stream[i]);
    }
  return 0;
}

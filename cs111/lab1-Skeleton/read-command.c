// UCLA CS 111 Lab 1 command reading

#include "command.h"
#include "command-internals.h"
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <ctype.h>

/* FIXME: You may need to add #include directives, macro definitions,
   static function definitions, etc.  */

/* FIXME: Define the type 'struct command_stream' here.  This should
   complete the incomplete type declaration in command.h.  */

typedef struct command_stream 
{
  // array of pointers pointing to c-strings
  int size;
  int cmd_count;
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
  int pt_count = 0;
  int str_count = 1;
  int i = 0;
  char input_byte;
  char prev_byte;
  char* stream = NULL;
  command_stream t = { 0, 0, NULL };
  command_stream_t result_stream = &t;
  
  // Initalize memory allocation for stream
  result_stream->command_list = (char**) malloc(sizeof(char**));
  result_stream->command_list[0] = NULL;

  // initialize stream
  input_byte = (char)get_next_byte(get_next_byte_argument);

  // Reallocate memory for stream characters
  // Record stream
  while (input_byte != EOF)
  {
    // cases for separate commands
    if (input_byte == '(' || input_byte == ')' || input_byte == ';')
    {
      stream = (char*) realloc(stream,2+str_count*sizeof(char));
      stream[str_count-1] = '\n';
      stream[str_count] = input_byte;
      stream[str_count+1] = '\n';
      str_count += 3;
    }
    else if ((prev_byte == '|' && input_byte == '|') ||
             (prev_byte == '&' && input_byte == '&'))
    {
      stream = (char*) realloc(stream,3+str_count*sizeof(char));
      stream[str_count-1] = '\n';
      stream[str_count] = input_byte;
      stream[str_count+1] = input_byte;
      stream[str_count+2] = '\n';
      str_count += 4;
      input_byte = '&';
    }
    else if (prev_byte == '|' && input_byte != '|') 
    {
      stream = (char*) realloc(stream,3+str_count*sizeof(char));
      stream[str_count-1] = '\n';
      stream[str_count] = prev_byte;
      stream[str_count+1] = input_byte;
      stream[str_count+2] = '\n';
      str_count += 4;
    }
    else if ((prev_byte != '|' && input_byte == '|') || 
             (prev_byte != '&' && input_byte == '&'))
    {
    }
    else
    {
      stream = (char*) realloc(stream,str_count*sizeof(char));
      stream[str_count-1] = input_byte;
      str_count += 1;
    }
    prev_byte = input_byte;
    input_byte = get_next_byte(get_next_byte_argument);
  }


  // Trim whitespace off commands
  char* trim_whitespace(char* str)
  {
    char *end;
    while(isspace(*str)) str++;
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end)) end--;
    *(end+1) = 0;
    return str;
  }

  // Split up stream using delmiter
  char* delim_stream = trim_whitespace(strtok(stream,"\n"));
  while (delim_stream != NULL)
  {
    pt_count++;
    result_stream->command_list = (char**) realloc(result_stream->command_list, 
        pt_count*sizeof(char**));
    result_stream->command_list[pt_count-1] = (char*) malloc(strlen(delim_stream));
    result_stream->command_list[pt_count-1] = trim_whitespace(delim_stream);
    delim_stream = trim(whitespace(strtok(NULL,"\n")));
  }
  result_stream->size = pt_count;

  // Test print
  for (i=0; i < pt_count; i++)
  {
    printf("%s \n", result_stream->command_list[i]);
  }

   printf("pt_count: %d \n", pt_count);
  // Returns stream as character array
  return result_stream;
}

command_t
read_command_stream (command_stream_t s)
{
  /* FIXME: Replace this with your implementation too.  */

  s=s;
  return 0;
}

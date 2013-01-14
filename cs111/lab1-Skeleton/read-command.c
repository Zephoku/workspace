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
int add_command(char*** list, int cur_size, char** cmd, int len)
    {
      if (*cmd == NULL || *list == NULL) 
      {
        return 0;
      }
      printf("cur_size: %d\n", cur_size);
      printf("cmd: %s\n", *cmd);
      // Append null byte
      *cmd = (char*) realloc(*cmd, (len+1)*sizeof(char));
      printf("HI\n");
      (*cmd)[len] = '\0';
      printf("HI\n");
      // Add command to list
      *list = (char**) realloc(*list, (cur_size+1)*sizeof(char**));
      printf("HI\n");
      (*list)[cur_size] = malloc(len);
      printf("HI\n");
      strcpy((*list)[cur_size], *cmd);
      printf("HI\n");
      return 1;
    }
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
  //int str_count = 1;
  int cmd_count = 0;
  int i = 0;
  char input_byte;
  char prev_byte;
  char *tmp_ch = NULL;
  //char* stream = NULL;
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
    if ((input_byte == '\n' || input_byte == ';' || input_byte == '(' || input_byte == ')'))
    {
      // Add command
      if (tmp_ch != NULL) 
      {
        add_command(&(result_stream->command_list), pt_count++, &tmp_ch, cmd_count);
      printf("HI\n");
      }
      else
      {
        // Add operator
        char* tmp = (char*) malloc(sizeof(char));
        tmp[0] = input_byte;
        add_command(&(result_stream->command_list), pt_count++, &tmp, 1);
      }

      printf("HI\n");
      // Reset for next add
      tmp_ch = NULL;
      printf("HII\n");
      cmd_count = 0;
      prev_byte = input_byte;
      printf("HII\n");
      input_byte = get_next_byte(get_next_byte_argument);
      printf("HII\n");
      continue;
    }
    // Allocate for command until delimiter found
    tmp_ch = (char*) realloc(tmp_ch, (cmd_count+1)*sizeof(char));
    tmp_ch[cmd_count] = input_byte;
    cmd_count++;

    prev_byte = input_byte;
    input_byte = get_next_byte(get_next_byte_argument);
  }

  result_stream->size = pt_count;

  // Test print
  for (i=0; i < pt_count; i++)
  {
    printf("%d: %s\n", i, result_stream->command_list[i]);
  }

   printf("\npt_count: %d \n", pt_count);
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

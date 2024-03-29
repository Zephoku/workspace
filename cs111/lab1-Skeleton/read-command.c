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
  // Array of pointers pointing to c-strings
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
  // Append null byte
  *cmd = (char*) realloc(*cmd, (len+1)*sizeof(char));
  (*cmd)[len] = '\0';
  // Trim whitespace
  *cmd = trim_whitespace(*cmd);
  // Add command to list
  *list = (char**) realloc(*list, (cur_size+1)*sizeof(char**));
  (*list)[cur_size] = malloc(strlen(*cmd));
  (*list)[cur_size] = strdup(*cmd);
  free(*cmd);
  *cmd = NULL;
  return 1;
}

int is_valid_op(char op, char last_op) 
{
  return (op == '\n' || op == ';' || op == '#' || op == '(' || op == ')' ||
          op == '&'  || op == '|' || last_op == '&' || last_op == '|');
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
  int cmd_count = 0;
  int i = 0;
  char input_byte;
  char prev_byte;
  char *tmp = NULL;
  char *tmp_ch = NULL;
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
    if (is_valid_op(input_byte, prev_byte))
    {
      // Add command
      if (tmp_ch != NULL) 
      {
        add_command(&(result_stream->command_list), pt_count++, &tmp_ch, cmd_count);
      }
      // Operator Cases
      if (input_byte == '#') 
      {
        // Append # comment to next command
        tmp_ch = (char*) malloc(sizeof(char));
        tmp_ch[0] = input_byte;
      }
      else if (input_byte == '|' && prev_byte != '|')
      {
        printf("hello");
      }
      else if (input_byte != '|' && prev_byte == '|')
      {
        // Add operator 
        tmp = (char*) malloc(sizeof(char));
        tmp[0] = prev_byte;
        add_command(&(result_stream->command_list), pt_count++, &tmp, 1);
      }
      else if (input_byte == '|' && prev_byte == '|')
      {
        // Add operator 
        tmp = (char*) malloc(2*sizeof(char));
        tmp[0] = input_byte;
        tmp[1] = prev_byte;
        add_command(&(result_stream->command_list), pt_count++, &tmp, 2);
        // prevent from being read again
        input_byte = ' ';
      }
      else if (input_byte == '&' && prev_byte != '&')
      {
      }
      else if (input_byte != '&' && prev_byte == '&')
      {
        // Add operator 
        tmp = (char*) malloc(sizeof(char));
        tmp[0] = input_byte;
        add_command(&(result_stream->command_list), pt_count++, &tmp, 1);
      }
      else if (input_byte == '&' && prev_byte == '&')
      {
        // Add operator 
        tmp = (char*) malloc(2*sizeof(char));
        tmp[0] = input_byte;
        tmp[1] = prev_byte;
        add_command(&(result_stream->command_list), pt_count++, &tmp, 2);
        // prevent from being read again
        input_byte = ' ';
      }
      else
      {
        // Add operator 
        tmp = (char*) malloc(sizeof(char));
        tmp[0] = input_byte;
        add_command(&(result_stream->command_list), pt_count++, &tmp, 1);
      }

      // Reset for next add
      if(input_byte == '#')
      {
        cmd_count = 1;
      }
      else
      {
        cmd_count = 0;
      }
      prev_byte = input_byte;
      input_byte = get_next_byte(get_next_byte_argument);
      continue;
    }
    if (input_byte == '#') 
    {
            // Reset
      prev_byte = input_byte;
      input_byte = get_next_byte(get_next_byte_argument);
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

#ifndef _COMMON_PARSER_H_ //include guard
#define _COMMON_PARSER_H_

/**
Functions used across all homeworks to parse command line arguments.
They can obtain from the command line:
- long integers
- ranges of the form "number:number"
- lists of the form "number{,number}"
- the corresponding integer values of key-words
**/

/**
gets a long integer from nptr and store it in result. If no integer is found, then
print err_msg in stderr, and return 1.
If endptr != NULL, then writes in endptr a pointer to the next character in nptr.
**/
int get_lint(char *nptr, char **endptr, long int *result, char *err_msg);

/**
expects nptr to contain two long integers separated by colon: "%ld:%ld", stores the
values in range_min and range_max. Also ensures range_min <= range_max. If error, print err_msg
and return 1. If success, return 0.
 **/
int get_lrange(char *nptr, long int *range_min, long int *range_max, char *err_msg);

/**
expects nptr to have a list of at least one long integer separated by commas: "%ld;,%ld}".
It alloctates memory for llist, and put the values on it.
It stores the length of llist in llist_size.
If success, return 0.
If error, print err_msg on stderr and returns 1.
**/
int get_llist(char *nptr, long int **llist, long int *llist_size, char *err_msg);

/**
the list map_keys maps 1:1 to map_values. If *nptr is found in map_keys, then the
corresponding map_value is placed in result.
If nptr is found, return 0.
If nptr is not found, print err_msg on stderr, and return 1.
**/
int map_keyword(char *nptr, char **map_keys, int *map_values, int map_size, int *result, char *err_msg);

#endif //include guard

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "parser.h" //implementing

//arbitrary (but more than reasonable) maximum size of list of numbers
#define MAX_LLIST_SIZE (512)

int get_lint(char *nptr, char **endptr, long int *result, char *err_msg){
    char *p = NULL;
    *result = strtol(nptr, &p, 10);
    if(endptr != NULL)
        *endptr = p;
    if(nptr == p){
        fprintf(stderr, "Error: There is no number at the beginning "
                "of '%s'\n", nptr);
        goto error;
    }
    if(*result == LONG_MAX){
        fprintf(stderr, "Error: Overflow reading '%s'.\n", nptr);
        goto error;
    }
    if(*result == LONG_MIN){
        fprintf(stderr, "Error: Overflow reading '%s'.\n", nptr);
        goto error;
    }
    return 0;
 error:
    fprintf(stderr, "Error: %s\n", err_msg);
    return 1;
}

int get_lrange(char *nptr, long int *range_min, long int *range_max, char *err_msg){
    char *p;
    // get first number
    if(get_lint(nptr, &p, range_min, "Could not obtain range_min."))
        goto error;
    
    // check separator
    if(*p != ':'){
        fprintf(stderr, "Error: Separator ':' expected in range '%s'.\n", nptr);
        goto error;
    }
    p += 1;
    
    // obtain second number
    if(get_lint(p, &p, range_max, "Could not obtain range_max."))
        goto error;

    // min <= max
    if(*range_max < *range_min){
        fprintf(stderr,"Error: max value is less than min value in range '%s'.\n", nptr);
        goto error;
    }
    
    // check end of string
    if(*p != '\0'){
        fprintf(stderr,"Error: range '%s' does not end with range_max.\n", nptr);
        goto error;
    }
    return 0;
 error:
    fprintf(stderr, "Error: %s\n", err_msg);
    return 1;
}

int get_llist(char *nptr, long int **llist, long int *llist_size, char *err_msg){
    char *p = nptr;
    int i, count = 0;
    long int val = 0;
    //count elements
    for(i=0; i<MAX_LLIST_SIZE+1; i++){
        if(get_lint(p, &p, &val, "Item in list is not a number."))
            goto error;
        count +=1;
        if(*p == ','){
            p += 1;
            continue;
        }
        if(*p == '\0')
            break;
        fprintf(stderr, "Error: Separator after %d-th item in '%s' is not ','\n", count, nptr);
        goto error;
    }

    if(i == MAX_LLIST_SIZE){
        fprintf(stderr, "Error: More items in the list than the maximum (%d) allowed.\n", MAX_LLIST_SIZE);
        goto error;
    }

    //actually store the numbers in the list
    *llist = (long int *)calloc(count, sizeof(long int));
    *llist_size = count;
    p = nptr;
    for(int i=0; i<count; i++){
        get_lint(p, &p, &((*llist)[i]), "BUG: Item in list should have been a number.");
        if(*p == ','){
            p += 1;
            continue;
        }
        if(*p == '\0')
            break;
        fprintf(stderr, "BUG: Separator in '%s' should have been ','\n", p);
        goto error;
    }
    return 0;
 error:
    fprintf(stderr, "Error: %s\n", err_msg);
    return 1;
}

int map_keyword(char *nptr, char **map_keys, int *map_values, int map_size, int *result, char *err_msg){
    for(int i=0; i<map_size; i++){
        if(!strcmp(nptr, map_keys[i])){
            *result = map_values[i];
            return 0;
        }
    }
    fprintf(stderr, "Error: \"%s\" does not match any known value.\n", nptr);
    fprintf(stderr, "Error: %s\n", err_msg);
    return 1;
}

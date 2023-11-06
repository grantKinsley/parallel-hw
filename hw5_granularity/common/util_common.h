#ifndef _UTIL_COMMON_H_ //include guard
#define _UTIL_COMMON_H_


/**
 * @macro Comment this macro to skip compilation of debuging related code
 * 
 * Example:
 * #ifdef DEBUG
 * // put here any code to be compiled ONLY if DEBUG is defined.
 * #endif
 *
 * To measure performance, don't forget to comment the DEBUG definition.
 */
#define DEBUG (1)


/**
 * @type Data Structure containing the parsed elements used by the program.
 */
typedef struct ProgramArgs ProgramArgs;


/**
 * @brief Returns the current time in seconds.
 */
extern double stopwatch(void);


/**
 * @brief Seed random number generators.
 * @param[in] seed Seed given. If it is -1, then current time is used as seed.
 */
extern void seed_rng(long int seed);


/**
 * @brief Modulus operation.
 * Implements n mod div.
 */
extern int mod(int n, int div);


/**
 * @brief prints to stderr help about how to use the executable
 */
extern void print_help(char *bin_name);


/**
 * @brief parses the command line arguments, check correctness, and fill
 * the ProgramArgs data structure with them.
 *
 * If there is a problem with the command-line arguments given to the
 * function, then print error message, print help message, and exit.
 *
 * @param[in]  argv Array of strings with passed command-line arguments
 * @param[in]  argc Size of argv
 * @param[out] args Data structure to be filled with the parsed data.
 */
extern void parse_cmd_line(int argc, char **argv, ProgramArgs *args);


/**
 * @brief Print members of the structure in a pretty manner.
 * Useful just for debugging.
 */
extern void print_arguments(ProgramArgs *args);


/**
 * @brief Creates the name of the log file
 * @param[out] fname sufficiently large buffer to store the name
 * @param[in]  a     structure with the program's arguments
 * @param[in]  id    unique identifier so names do not repeat
 */
extern void create_filename(char *fname, const ProgramArgs *a, long int id);

#endif //include guard

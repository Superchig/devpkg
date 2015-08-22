//! @file
//! @brief Execution functions and structs representing shell commands.

#ifndef _shell_h
#define _shell_h

//! 1 greater than the maximum amount of arguments in a Shell.
#define MAX_COMMAND_ARGS 100

#include <apr-1/apr_thread_proc.h>

//! Represents a shell command.
typedef struct Shell {
	//! Directory to begin execution in.
	const char *dir;
	//! Name of executable.
	const char *exe;

	//! Command's attributes, which mainly contains options for IO.
	apr_procattr_t *attr;
	//! Process to run.
	apr_proc_t proc;
	//! Why the command exited.
	apr_exit_why_e exit_why;
	//! Exit code.
	int exit_code;
	//! Number of arguments that should be replaced.
	int args_repl;

	//! NULL-terminated array of arguments.
	/*!
	  Arguments that should be replaced are in all caps.

	  Example:
	  @code{.c}
	  {"echo", "-e", "MSG", NULL}
	  @endcode
	 */
	const char *args[MAX_COMMAND_ARGS];
} Shell;

//! Runs a Shell command.
/*!
  @param p Apr memory pool to use.
  @param cmd Shell to run.

  @return 0 on successful Shell run. -1 if error occurred.
 */
int Shell_run(apr_pool_t *p, Shell *cmd);
//! Executes one of the extern Shells in shell.h
/*!
  @param template Extern Shell to be executed, probably with ALL-CAPS arguments that are to be replaced.
  @param ...
  @parblock
  Key-value pairs of arguments to be replaced.

  Example:
  @code{.c}
  int rc = Shell_exec(CURL_SH,
                     "TARGET", /tmp/curlable_project,
                     "URL", https://project/that/can/be/curled);

  if(rc == -1) {
      // Handle execution failure...
  }
  @endcode
  @endparblock

  @return 0 on successful Shell run. -1 if error occurred.
 */
int Shell_exec(Shell template, ...);

//! Cleanup command.
extern Shell CLEANUP_SH;
//! Git clone command, for fetching projects.
extern Shell GIT_SH;
//! Untar command, for untarring fetched projects.
extern Shell TAR_SH;
//! Curl, for fetching projects.
extern Shell CURL_SH;
//! Configure, for the configure script in C projects.
extern Shell CONFIGURE_SH;
//! Make, for building the project's source code.
extern Shell MAKE_SH;
//! Make install, for installing the built source code.
extern Shell INSTALL_SH;

#endif

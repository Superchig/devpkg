//! @file
//! @brief Functions and enums for devpkg commands.

#ifndef _commands_h
#define _commands_h

#include <apr-1/apr_pools.h>

//! Path to dependencies file.
/*!
  Must be a series of newline-separated urls.
 */
#define DEPENDS_PATH "/tmp/DEPENDS"
//! Path to package source, with tar.gz extension.
#define TAR_GZ_SRC "/tmp/pkg-src.tar.gz"
//! Path to package source, with tar.bz2 extension.
#define TAR_BZ2_SRC "/tmp/pkg-src.tar.bz2"
//! Directory to build files in.
#define BUILD_DIR "/tmp/pkg-build"
//! Pattern to match against git packages.
#define GIT_PAT "*.git"
//! Pattern that depends file ends in.
#define DEPEND_PAT "*DEPENDS"
//! Pattern for tar.gz files.
#define TAR_GZ_PAT "*.tar.gz"
//! Pattern for tar.bz2 files.
#define TAR_BZ2_PAT "*.tar.bz2"
//! Path for configure script.
#define CONFIG_SCRIPT "/tmp/pkg-build/configure"

//! Represents which command is selected.
enum CommandType {
	COMMAND_NONE, COMMAND_INSTALL, COMMAND_LIST, COMMAND_FETCH,
	COMMAND_INIT, COMMAND_BUILD
};

//! Downloads a project either through git or curl, and then untars it if needed.
/*!
  @param p The apr memory pool to be used.
  @param url The url of the project to be fetched.
  @param fetch_only
  @parblock
  Whether or not to only fetch dependencies.
  0 to fetch dependencies. 1 to _not_ fetch dependencies.
  @endparblock

  @return
  @parblock
  0 if nothing additional should be done.
  1 if the project needs to be installed.
  -1 if an error occurred.
  @endparblock

  Example:
  @code{.c}
  int rc = Command_fetch(p, "https://github.com/foo/bar.git")
  if(rc == -1) {
      // Handle error...
  } else if(rc == 1) {
      Command_install(p, "https://github.com/foo/bar.git", NULL, NULL, NULL);
  } else {
      so_chic();
      freak_out();
  }
  @endcode
 */
int Command_fetch(apr_pool_t *p, const char *url, int fetch_only);

//! Fetches and builds a project, unless the project has already been installed.
/*!
  @param p Memory pool to be used.
  @param url Url of project.
  @param configure_opts Configure options.
  @param make_opts Options to be passed to first make.
  @param install_opts Options to be passed in place of make install.
  
  @return 0 on successful install.
  @return 0 on successful fetch and the project has already been installed.
  @return -1 on error.
 */
int Command_install(apr_pool_t *p, const char *url, const char *configure_opts,
					const char *make_opts, const char *install_opts);

//! Installs all projects in the file pointed to by path.
/*!
  @param p The apr memory pool to be used.
  @param path
  @parblock
  Path to a file containing a series of line-separated urls to
  dependencies to be installed.
  @endparblock

  @return 0 if download successful.
  @return -1 if error occurred.
 */
int Command_depends(apr_pool_t *p, const char *path);

//! Builds the already downloaded C project.
/*!
  @par Warning
  Builds the C project already downloaded, not necessarily url.
  
  @param p The apr memory pool to be used.
  @param url The url to be added to DB_FILE
  @param configure_opts Options to be passed to the configure script.
  @param make_opts Options to be passed to make.
  @param install_opts Options to be passed to make install.

  --------
  Example:
  @code{.c}
  int rc = Command_build(p, "https://foo/bar.git");
  if(rc == -1) {
      // Handle error...
  }
  @endcode

  @return 0 if successful.
  @return -1 on error.
 */
int Command_build(apr_pool_t *p, const char *url, const char *configure_opts,
				  const char *make_opts, const char *install_opts);

#endif

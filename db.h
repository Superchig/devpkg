//! @file
//! @brief "Database" implementation and corresponding functions.

#ifndef _db_h
#define _db_h

//! Path to database file.
/*
  The database file is only a series of newline-separated urls.
 */
#define DB_FILE "/usr/local/.devpkg/db"
//! Path to general files directory.
#define DB_DIR "/usr/local/.devpkg"

/*! Creates database file pointed to by DB_FILE, creating its necessary directories.
  @return 0 if opened successfully. 1 if error occurred.
 */
int DB_init();
/*! Prints every url in DB_FILE.
  @return 0 if successful print. 1 if error occurred.
 */
int DB_list();
/*! Appends url to DB_FILE.
  @param url The url to be appended to DB_FILE.

  @return 0 if successful append. 1 if error occurred.
 */
int DB_update(const char *url);
/*! Finds whether or not DB_FILE has url contained in it.
  @param url The url to search DB_FILE for.

  @return
  @parblock
  0 if url is not contained in DB_FILE.
  1 if url is contained.
  -1 if an error occurred.
  @endparblock

  Example:
  @code
  int rc = DB_update("https://github.com/foo/bar.git")
  if(rc == -1) {
      // Handle error...
  } else if(rc == 0) {
      // Show that url was not found...
  } else if(rc == -1) {
      // Show that url was found...
  }
  @endcode
 */
int DB_find(const char *url);

#endif

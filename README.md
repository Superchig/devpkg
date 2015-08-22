# Devpkg
This is a work in progress. Part of Zed's excellent [Learn C the Hard Way](http://c.learncodethehardway.org/book/ex26.html) book.

## Installation
Git clone the repository.

## Command-line Options

### Key
[argument] => argument is a necessary argument.

{argument1, argument2, argument3, ...} => these arguments are optional.

### Options

- devpkg -S
  - Sets up the database file.
- devpkg -I [url] {-i install\_opts, -m make\_opts, -c config\_opts}
  - Installs a piece of software from a URL.
- devpkg -L
  - Lists all software that's been installed.
- devpkg -F
  - Fetches some source code for manual building
- devpkg -B {-i install\_opts, -m make\_opts, -c config\_opts}
  - Builds fetched source code and installs it, even if already installed.

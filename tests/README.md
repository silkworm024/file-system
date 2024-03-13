# Mock OS Unit Tests
The unit tests of these studios and the lab were created and improved on by students.
This file documents the history of the tests, and what still can be done to improve them.

## History
* 2019: tests created with Microsoft Unit Test Framework by Lindsey Corydon
* 2022: ported to Google Test by Razi Khan, separately ported to Google Test by Danny Horn
* 2023: ported to static library structure by Fisher Sun

## Todo
* fix wrong order of arguments on some tests
* remove unnecessary cin and cout redirections
* rewrite with idiomatic Google Test (see Google Test Primer)
  * use expect where it's appropriate
  * use insertion operator to provide test output 
  * use mocks
* decrease code duplication
  * fixtures
  * modularize tests, reuse them for lab5

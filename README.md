# revlibc

revlibc is C interfaces derived from Rust's [libc](https://github.com/rust-lang/libc) project. Here the 'rev' means either 'revised', 'reversed', 'revolutionized', or any other adjectives with such prefix. Note that revlibc is NOT an implementation of C runtimes and standard library, instead, it just contains declarations of system libc.

## What is this project for?

Almost all platforms have a working C library. When compiling C programs natively on some platform, system C headers work nicely. However, things become painful when compilation is 'crossed'.

- Native C headers have complex macro definitions, which may not be portable.
- Not all targets' system C headers are free (as in freeedom).

## Why choose Rust libc?

Since Rust is a system programming language, it meets the same problem, which is why Rust libc project came into being. After years of development, the project is rather mature today and supports many mainstream targets. Its license part is also clear: MIT and Apache.

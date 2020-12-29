# LZW20 Compression Program

<p>
    <a href="https://github.com/andreiui/lzw-20/blob/main/LICENSE">
        <img src="https://img.shields.io/badge/bin-passing-00000.svg" alt="LZW20 is released under the MIT license." />
    </a>
</p>

LZW20 is an ASCII file compression program based on the [Lempel–Ziv–Welch (LZW)](https://en.wikipedia.org/wiki/Lempel–Ziv–Welch) universal lossless data compression algorithm created by Abraham Lempel, Jacob Ziv, and Terry Welch. The program is developed by Andrei Pascu, an undegraduate student at Yale University (Class of 2023).

The encoding and decoding programs were first written as part of the LZW assignment for the course [CPSC 323: Introduction to Systems Programming and Computer Organization](https://zoo.cs.yale.edu/classes/cs323/), taught by Professor Stan Eisenstat in the fall of 2020.

After completing the course, the code written for the LZW assignment has been reused and further expanded upon in order to develop a more comprehensive and useful piece of software utility for the purpose of data compression.

*In memory of Professor Stan Eisenstat.*

## Contents

The following template is the directory structure for used by this repository:

```bash
.
├── bin
│   ├── lzw20.decode
│   └── lzw20.encode
├── docs
│   └── *.txt
├── include
│   └── *.h
├── src
│   ├── *.c
│   └── *.o
├── Makefile
└── README.md
```

The `./bin` folder contains two binary executables:

- `lzw20.encode [-m MAXBITS] [-p]` reads a stream of characters from the standard input, compresses it using the Lempel–Ziv–Welch algorithm, and writes the stream of codes to the standard output as a stream of bits packed into 8-bit bytes.

  - `lzw20.encode` writes each code using the smallest number of bits required to specify valid codes at the time (e.g., 9 bits when there are 512 valid codes, but 10 bits once the next code is assigned), up to a maximum of 12 bits (or MAXBITS if the `-m MAXBITS` option is specified). This places a limit on the number of codes that can be assigned.

  - `lzw20.encode` begins with a string table that assigns a code to every one-character string and assigns new codes to other strings that it finds during the greedy parse.  Normally it stops assigning codes when the table is full (i.e., there are no unassigned codes). But with the `-p` (pruning) option, it instead creates a new string table that contains:

    - every one-character string; and
    - every string that is a prefix of another code in the old table

    which has the effect of removing codes that were never used.

  - `lzw20.encode` replaces MAXBITS by 12 if MAXBITS is less than or equal to 8 or greater than 20.

  - `lzw20.encode` writes a one-line message to the standard error and exits with status `EXIT_SUCCESS` when an invalid option is specified.

- `lzw20.decode` decode reads from the standard input a byte stream written by `lzw20.encode`, decompresses the stream of codes, and writes the stream of characters to the standard output.

  - `lzw20.decode` writes a message and exits with status `EXIT_SUCCESS` if there is a command-line option or if it detects a file that encode could not have written.

**Note:** `lzw20.encode` and `lzw20.decode` are a single C program (i.e., they are hard links to the same inode) whose behavior is determined by the name under which it is invoked (i.e., the 0-th command-line argument). The `-m MAXBITS` and `-p` options may appear in any order and any number of times, with the last occurrence of each option superseding all earlier ones.

- `lzw20.encode` and `lzw20.decode` handle both ASCII text and binary files.

- Instead of the standard input and output being buffered, `lzw20.encode` and `lzw20.decode` reduce the size of the buffers and allocate them statically.

The `./docs` folder contains all related documentation on the LZW20 program in a `*.txt` format:

- `f20h4.txt`, the specification for the LZW assignment for CPSC 323 during fall of 2020; and

- `lzw.txt`, a concise explanation of the Lempel–Ziv–Welch algorithm in a pseudocode format.

The `./include` folder contains all C header files used in the programs:

- `code.h` is the header file defining the functions that write/read a stream of bits packed in bytes.

- `table.h` is the header file defining the data structures and functions that use the string table storing the (CODE, PREFIX, CHAR) triples.

- `lzw.h` is the header file defining the functions that compress/decompress a stream of ASCII characters or bits packed in bytes.

The `./src` folder contains all C source and object files:

- `code.c` is the source file implementing the functions that write/read a stream of bits packed in bytes, as defined in `code.h`.

- `table.c` is the source file implementing the data structures and functions that use the string table storing the (CODE, PREFIX, CHAR) triples, as defined in `table.h`.

- `lzw.c` is the source file implementing the functions that compress/decompress a stream of ASCII characters or bits packed in bytes, as defined in `lzw.h`.

The root `.` contains three additional files:

- `README.md`, which contains the documentation for this project; and

- `Makefile`, which builds the LZW20 programs.

## Build and execute

While in the root `.` folder:

- Running the `make` command will generate the `lzw20.encode` and `lzw20.encode` binary executables in `./bin`.

- Running the `make clean` command will clean the compiled executables in `./bin` and all object files in `./src`.

## Notes

This project does not contain a license. Consequently, this work is under exclusive copyright by default (with the exception of the files in `./docs` and `./include/code.h`, `./src/code.c`, and `./src/code.o`, which have been openly distributed as CPSC 323 coursework). For more details, see [No License](https://choosealicense.com/no-permission/).

**IMPORTANT: Students taking CPSC 323 cannot copy, distribute, or modify any of the files in this project (except for those listed above), with or without attribution, under any circumstances.**

While the basis of this project is inspired from the programs submitted for the CPSC 323 assignment, all code present in this repository has been rewritten and repurposed for individual purposes. **All code in this project does not represent the work submitted during the taking of CPSC 323.**

## Further readings and resources

- [Terry Welch's paper on LZW data compression](https://www2.cs.duke.edu/courses/spring03/cps296.5/papers/welch_1984_technique_for.pdf)

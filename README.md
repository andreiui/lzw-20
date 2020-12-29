# LZW20 Data Compression

<p>
    <a href="https://github.com/andreiui/lzw-20/blob/main/LICENSE">
        <img src="https://img.shields.io/badge/bin-passing-00000.svg" alt="LZW20 is released under the MIT license." />
    </a>
</p>

LZW20 is an ASCII data compression program based on the [Lempel–Ziv–Welch (LZW)](https://en.wikipedia.org/wiki/Lempel–Ziv–Welch) universal lossless data compression algorithm created by Abraham Lempel, Jacob Ziv, and Terry Welch. The program is developed by Andrei Pascu, an undegraduate student at Yale University (Class of 2023).

The compression and decompression programs were inspired from the LZW assignment for the course [CPSC 323: Introduction to Systems Programming and Computer Organization](https://zoo.cs.yale.edu/classes/cs323/), taught by Professor Stanley Eisenstat in the fall of 2020.

The code used in this project has been rewritten from the ground up and expanded upon in order to develop a more comprehensive and useful piece of software utility for the purpose of data compression.

*In memory of Professor Stanley Eisenstat.*

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

  - `lzw20.encode` writes a one-line message to the standard error and exits with status `EXIT_FAILURE` when an invalid option is specified.

- `lzw20.decode` decode reads from the standard input a byte stream written by `lzw20.encode`, decompresses the stream of codes, and writes the stream of characters to the standard output.

  - `lzw20.decode` writes a message and exits with status `EXIT_FAILURE` if there is a command-line option or if it detects a file that encode could not have written.

**Note:** `lzw20.encode` and `lzw20.decode` are a single C program (i.e., they are hard links to the same inode) whose behavior is determined by the name under which it is invoked (i.e., the 0-th command-line argument). The flag options may appear in any order and any number of times, with the last occurrence of each option superseding all earlier ones.

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

**Note:** `table.c` and `lzw.c` (and all object files) have been hidden from the repository from public viewing.

The root `.` contains three additional files:

- `README.md`, which contains the documentation for this project; and

- `Makefile`, which builds the LZW20 programs.

## Build and execute

While in the root `.` folder:

- Running the `make` command will generate the `lzw20.encode` and `lzw20.encode` binary executables in `./bin`.

- Running the `make clean` command will clean the compiled executables in `./bin` and all object files in `./src`.

## Notes

This project does not contain a license. For more details, see [No License](https://choosealicense.com/no-permission/).

Files `./src/lzw.c` and `./src/table.c` are not publicly available. If you are interested to see these files privately, please contact the author of this project for further information at [me@andreipascu.com](mailto:me@andreipascu.com?subject=[GitHub]%20LZW20%20Data%20Compression%20Source).

## Further readings and resources

- [Terry Welch's paper on LZW data compression](https://www2.cs.duke.edu/courses/spring03/cps296.5/papers/welch_1984_technique_for.pdf)

- [Brief pseudocode explanation of the LZW algorithm](https://github.com/andreiui/lzw-20/blob/main/docs/lzw.txt)

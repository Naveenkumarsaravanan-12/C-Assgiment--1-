# DSA01 - Assignment 1 (CO1): Metro Smart-Card Fare Logic

**Name:** Naveen Kumar Saravanan  
**Register number:** 192424104  
**Compiler stated in assignment:** g++ (GCC) 13.3.0, Ubuntu 24.04  
**Compile command:** `g++ -std=c++17 -Wall -Wextra <file>.cpp -o <name>`

## Contents
- `Assignment1_CO1_Metro_SmartCard_192424104.pdf` — original completed assignment.
- `Task02` to `Task12` — C++ source files and the configuration/input files shown or referenced in the report.
- `Task_alt/alt_bench.cpp` — alternative implementation benchmark from Appendix A.
- `outputs/` — captured output from programs that compiled and ran successfully; compiler diagnostics for intentionally invalid examples are also included.

## Compile and run
Open a terminal in a task folder, then run:

```bash
g++ -std=c++17 -Wall -Wextra task09_tests.cpp -o task09_tests
./task09_tests
```

For Task 8 input validation:

```bash
g++ -std=c++17 -Wall -Wextra task08_input.cpp -o task08_input
./task08_input < task08_input.txt
```

Task 9 and Task 12 tests include their header files (`metro_v1.hpp` and `metro_v2.hpp`). Keep each header in the same folder as its test source.

## Notes
- `task02_errors.cpp`, `task04_narrowing_error.cpp`, and `task07_private_error.cpp` are deliberately invalid examples intended to demonstrate compile-time errors; they are not expected to build.
- `task12_old_switch_fails.cpp` intentionally demonstrates the missing Airport case in the old switch.
- The Task 8 input text files are sample inputs constructed from the invalid/valid cases described in the assignment report. They are not separately labelled source listings in the PDF.
- Some compiler warning wording and benchmark timings vary by compiler and machine.

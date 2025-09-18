# PL0Compiler
This C code implements a complete compiler and virtual machine for a simple, block-structured programming language. The program takes a source code file, processes it through a lexical analyzer and a parser to generate assembly-like instructions, and then executes those instructions on a virtual machine to run the program.

Detailed Description:

The process is managed by driver.c and is broken down into three main phases, each handled by a different part of the codebase. Lexical Analysis (lex.c): The code first reads the source file provided by the user. The lexical analyzer scans this raw text and converts it into a sequence of tokens. A token is a categorized piece of code, such as keyword_while, identifier, number, or plus. This phase also identifies lexical errors, like an identifier name that is too long or an invalid symbol.

Parsing & Code Generation (parser.c): The stream of tokens is then sent to the parser. The parser checks if the tokens follow the grammatical rules of the programming language (syntax analysis). As it validates the syntax, it performs two critical tasks: It builds a symbol table, which keeps track of all identifiers (variables, constants, procedures), their types, and their locations in memory. It generates a simple, low-level intermediate code, often called P-code or assembly code, which can be easily executed by a machine. It reports syntax errors, such as a missing semicolon or using an undeclared variable.

Execution (vm.c): Finally, the generated assembly code is passed to the Virtual Machine (VM) for execution. The VM simulates a simple stack-based computer. It fetches, decodes, and executes each instruction from the parser's output in a loop . It manages a stack for storing values and registers like the program counter (PC), base pointer (BP), and stack pointer (SP) to control the program flow .


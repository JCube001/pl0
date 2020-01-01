# PL/0

The goal of this project is to create an application for executing programs written in [PL/0](https://en.wikipedia.org/wiki/PL/0).

## Grammar

```ebnf
program
    = block ".";

block
    = ["const" identifier "=" number {"," identifier "=" number} ";"]
        ["var" identifier {"," identifier} ";"]
        {"procedure" identifier ";" block ";" } statement
    ;

statement
    =
    [ identifier ":=" expression
    | "call" expression
    | "?" identifier
    | "!" expression
    | "begin" statement {";" statement} "end"
    | "if" condition "then" statement
    | "while" condition "do" statement
    ];

condition
    = "odd" expression
    | expression ("="|"#"|"<"|"<="|">"|">=") expression
    ;

expression
    = ["+"|"-"] term {("+"|"-") term}
    ;

term
    = factor {("*"|"/") factor}
    ;

factor
    = identifier
    | number
    | "(" expression ")"
    ;

number
    = ?[0-9]+?
    ;

identifier
    = ?[A-Za-z_][A-Za-z0-9_]*?
    ;
```

In practice, the keywords are often case-insensitive. Sometimes the identifiers are too. This implementation only treats the keywords as case-insensitive.

## TODO

* Implement better parser error handling.
* Implement a general mechanism for logging diagnostic messages.
* Handle semantic analysis and symbol table creation before evaluation-time.
* Write unit tests for everything.
* Add command line options for fine-tuning how code will be compiled and executed.
* Make compiling dev features such as unit tests and the benchmark application optional in the build scripts.
* Add sections to this README about writing PL/0 programs.
* Write backend components consisting of the following:
    - Semantic analyzer
    - Optimizer
    - Bytecode generator
    - Virtual machine

Ultimately, I'd like to compile PL/0 code to a custom bytecode. The bytecode would then be executed by a simple virtual machine implementation (i.e. not a JIT).

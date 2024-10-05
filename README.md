# Minishell

## About

Minishell is a simple shell implementation, part of the 42 school curriculum. This project aims to create a basic command-line interpreter similar to bash, helping students understand the fundamentals of processes, file descriptors, and command execution in Unix-like operating systems.

## Features

Our minishell implements the following features:

1. **Command Prompt**: Displays a prompt when waiting for a new command.
2. **Command History**: Maintains a working history of commands.
3. **Executable Search and Launch**: 
   - Searches and launches the right executable based on the PATH variable.
   - Supports relative or absolute paths.
4. **Quote Handling**:
   - Handles single quotes (') to prevent interpretation of meta-characters.
   - Handles double quotes (") while still interpreting $ (dollar sign).
5. **Redirections**:
   - < : Input redirection
   - > : Output redirection
   - << : Here document (delimiter-based input)
   - >> : Output redirection in append mode
6. **Pipes**: Implements pipes (|) to connect the output of one command to the input of the next.
7. **Environment Variables**: 
   - Expands environment variables ($ followed by characters).
   - Handles $? to expand to the exit status of the most recently executed foreground pipeline.
8. **Signal Handling**:
   - Ctrl-C: Displays a new prompt on a new line.
   - Ctrl-D: Exits the shell.
   - Ctrl-\: Does nothing.
9. **Built-in Commands**:
   - echo with option -n
   - cd with relative or absolute path
   - pwd with no options
   - export with no options
   - unset with no options
   - env with no options or arguments
   - exit with no options

## Compilation

first install the ```readline``` library:

on fedora based systems:
```sudo yum install readline-devel```

on debian based systems:
```sudo apt-get install lib32readline-dev lib32readline-dev```

you might need to add this include in the readline/rltypedegfs.h file:
```#include <bits/types/FILE.h>```


Use the provided Makefile to compile the project:

```
make
```

This will compile the minishell executable.

## Usage

After compilation, run the minishell:

```
./minishell
```

You can then enter commands as you would in a regular shell.

## Note

This project is part of the 42 school curriculum and adheres to specific guidelines and restrictions. It's designed as a learning exercise and may not include all features of a full-fledged shell.

## Authors

- [**Iyan Nazarian**](https://github.com/FxmousKid)
- [**Theo Polgar**](https://github.com/MonkePlusPlus)

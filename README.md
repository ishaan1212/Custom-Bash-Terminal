# Custom Bash Terminal

This project is a custom Bash terminal implemented in C for Linux. It provides fundamental shell functionalities, such as command parsing, argument validation, and process execution, along with additional features like opening new shells in new terminals and file concatenation.

## Features

- **Command Execution:** Executes user-entered commands using `fork` and `execvp` system calls.
- **New Terminal Shell:** Opens a new shell in a new terminal window using `fork` and `execlp`.
- **File Concatenation:** Concatenates and displays contents of multiple files separated by custom delimiters.
- **Argument Validation:** Ensures the number of arguments is within acceptable limits to prevent errors.
- **Process Synchronization:** Uses `waitpid` to handle process synchronization and ensure robust error handling.

## Usage

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/username/custom-bash-terminal.git
   cd custom-bash-terminal
2. **Compile the Code:**
   ```bash
   gcc -o shell24 shell24.c
3. **Run the shell:**
   ```bash
   ./shell24
   
4. **Use the Shell:**

Enter commands as you would in a typical Bash terminal.
Use newt to open a new terminal with a new shell.
Concatenate files using # as a delimiter, e.g., file1.txt#file2.txt.

## Code Overview
- **main:** The entry point of the program, which reads user input and calls parse_command.
- **parse_command:** Parses the input command, validates arguments, and determines the action to take (e.g., execute a command, open a new terminal, concatenate files).
- **execute_command:** Executes the parsed command using fork and execvp.
- **validate_args:** Validates the number of arguments for a command.

# msh.c
Sure! Here's an example of a README file for the provided code:

# Simple Shell - Socket Programming

This repository contains a simple shell program implemented in C that provides basic command-line interpreter functionalities. It allows users to execute commands, manage command history, change directories, and view process IDs (PIDs) of executed child processes.

## Features

- Execution of commands: Users can enter various commands, which will be executed by the shell. The program supports executing both built-in commands (e.g., `cd`) and external commands.
- Command history: The shell maintains a history of the last 15 commands entered by the user. Users can view the command history using the `history` command.
- Reusing command history: Users can reuse previously entered commands from the history by specifying the index of the command using the `!` symbol.
- Changing directories: The `cd` command allows users to change the current working directory.
- Process ID tracking: The shell keeps track of the PIDs of child processes executed. Users can view the last 15 PIDs using the `pidhistory` command.

## Getting Started

To run the simple shell program, follow these steps:

1. Clone this repository to your local machine or download the source code files.
2. Compile the code using a C compiler (e.g., GCC) by running the following command:
   ```
   gcc shell.c -o shell
   ```
3. Execute the compiled binary:
   ```
   ./shell
   ```
4. You should now see the shell prompt `msh>`. You can start entering commands and exploring the available functionalities.

## Usage

The shell supports the following commands:

- `quit` or `exit`: Terminates the shell program.
- `history`: Displays the last 15 commands entered by the user.
- `![index]`: Reuses a previously entered command from the history, where `[index]` is the index of the command to be reused.
- `cd [directory]`: Changes the current working directory to `[directory]`. If no directory is specified, it changes to the home directory.
- `pidhistory`: Displays the last 15 PIDs of child processes executed.

Note: The shell supports executing external commands as well. Simply enter the desired command, and it will be executed accordingly.

## Contributing

Contributions to this simple shell program are welcome! If you find any issues or have suggestions for improvements, please feel free to open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).

## Acknowledgements

The implementation of this simple shell program is inspired by various Unix shell implementations and aims to provide a basic understanding of shell functionalities.

## Contact

For any inquiries or questions, please contact [Abhyudai Singh](https://github.com/Axs7941).

Enjoy using the Simple Shell!

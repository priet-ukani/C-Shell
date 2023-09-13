
# C Shell 

A fully functional shell implemented in C with numerous features, such as :
- Executing multiple shell commands in one line with foreground and background functionality.
- List all the files in the current directory and change directory with many useful shortcuts.
- Search recursively in any directory for files/directories with flag functionality to filter.
- User defined functions to aid the working of the shell.
- Monitoring and altering currently running background processes initiated by the shell alongwith changing process state.






## Usage

Run the makefile by the command ```make```. The executable file will be formed in the src folder with name ```priet_shell```. Run this by ```./priet_shell```. Alternative is to run directly with the help of ```bash start.sh```

```bash
  make
  cd src/
  ./priet_shell
``` 
```bash
sudo chmod +x start.sh
./start.sh
```

## Assumptions 
- The time interval given in the neonate command is an integer and greater than 0. 
- Execvp may not be able to handle the commands with special characters or quotes which is not handled manually. So piping with sed `'\s \\g'` etc, execvp gives an error.
- iMan response depends on the connection and server. So it may be incomplete sometimes.


# Features
## Display Prompt
The display prompt shows the user's username along with the current working directory, assuming the home location to be where the shell is evecuted from.
```bash
[prietukani@priet-TUF ~/]$ 
```
## Parsing multiple tabs and spaces
The shell can handle arguments with unwanted extra spaces or tabs in between the commands.
```bash
[prietukani@priet-TUF ~/]$      echo            "OSN OP"
"OSN OP"
```

## Handling multiple arguments
Multiple arguments are given in input seperated by `;` and also by `&` (denoting background process for the preceding command).
```bash
[prietukani@priet-TUF ~/]$ echo "OSN OP" ; echo "Shell"
"OSN OP"
"Shell"
```
## User defined change directory
`warp` command is used to change directory. It accepts even relative and absolute paths along with flags such as `..`, `.`, `-`, `.. ..`.
```bash
[prietukani@priet-TUF /home/prietukani/Desktop/Codes]$ warp .. .. 
../home/prietukani/Desktop
../home/prietukani
[prietukani@priet-TUF /home/prietukani]$ warp -
-/home/prietukani/Desktop
[prietukani@priet-TUF /home/prietukani/Desktop]$ warp Codes
Codes/home/prietukani/Desktop/Codes
[prietukani@priet-TUF /home/prietukani/Desktop/Codes]$ 
```

## Multiple commands


## Directory Structure

```bash
├── LISCENCE
├── makefile
├── README.md
└── src
    ├── bg.h
    ├── colours.h
    ├── display_user_prompt.c
    ├── display_user_prompt.h
    ├── execute.c
    ├── execute.h
    ├── extra_functions.c
    ├── extra_functions.h
    ├── main.c
    ├── main.h
    ├── pastevents.c
    ├── pastevents.h
    ├── pastevents.txt
    ├── peek.c
    ├── peek.h
    ├── priet_shell
    ├── proclore.c
    ├── proclore.h
    ├── seek.c
    ├── seek.h
    ├── system_commands.c
    ├── system_commands.h
    ├── warp.c
    └── warp.h
```
## Authors

- [Priet Ukani](https://github.com/priet-ukani)


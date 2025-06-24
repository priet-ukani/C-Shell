
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
- The length of the command given in input is of maximum 1024 characters. Most of the strings are assumed to be of this length.
- The pastevents command assumes that only this shell has access the the history file and shell can only change the file.
- The signal handlers Ctrl+D and Ctrl+Z won't work with neonate command. 

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
## List files
`peek` command is used to list all the files/directories in the current directory. It also supports `-l` and `-a` flags to shows all details and hidden files respectively.
```bash
[prietukani@priet-TUF /home/prietukani/Desktop/Codes/Github/Coding]$ peek 
Arduino
C
Python
README.md
dbg.hpp
```

## Search recursively
`seek` command is used to search recursively for files or directories in the given path. It also accepts flags like `-d`(shows only directories), `-f`(shows only files) and `-e`(views/executes if onyl single result is found).
```bash
[prietukani@priet-TUF ~/]$ seek peek
Found file: /home/prietukani/Desktop/Codes/Github/Coding/Sem 3/Operating Systems and Networks/C Shell/C-Shell/src/peek.c
Found file: /home/prietukani/Desktop/Codes/Github/Coding/Sem 3/Operating Systems and Networks/C Shell/C-Shell/src/peek.h
```


##  System commands
Shell executes the other system commands present in Bash as well like emacs, gedit etc. This should be possible in both foreground and background processes.
```bash
[prietukani@priet-TUF ~/]$ sleep 2
[prietukani@priet-TUF ~/] sleep: 2s $ sleep 2 &
[1] 52886
[prietukani@priet-TUF ~/]$ 
sleep 2 with pid 52886 exited normally.
```


## Get process info
`proclore` command is used to obtain information regarding a process.
```bash
[prietukani@priet-TUF ~/]$ proclore 48121
pid : 48121
Process Status : R+
Process Group : 48082
Virtual Memory : 35086
executable path : ~/priet_shell
```

## I/O Redirection and Piping
I/O Redirection is when you change the default input/output (which is the terminal) to another file. Pipes are used to pass information between commands. 
```bash
[prietukani@priet-TUF ~/]$  cat < a.txt | wc | cat > b.txt               
[prietukani@priet-TUF ~/]$ cat b.txt
      1       3       9
```

## Activities
`activities` command prints a list of all the processes currently running that were spawned by the shell. it gives the information- Command Name, pid and state : running or stopped.
```bash
[prietukani@priet-TUF ~/]$ sleep 10 &
[1] 61588
[prietukani@priet-TUF ~/]$ activities
61588 : sleep 10 - Running
```

## Signals
`ping` command is used to send signals to the processes. Also `Ctrl+D`, `Ctrl+C` and `Ctrl+Z` have been handled to work as they work in the Linux shell.
```bash
[prietukani@priet-TUF ~/]$ sleep 100 &
[1] 63429
[prietukani@priet-TUF ~/]$ ping 63429 9
Sent signal 9 to process with pid 63429.

sleep 100 with pid 63429 failed to exit normally.
```

## Foreground and Background
`fg` command brings the running or stopped background process with corresponding pid to foreground, handing it the control of terminal. `bg` command changes the state of a stopped background process to running (in the background). 
```bash
[prietukani@priet-TUF ~/]$ sleep 14 &
[3] 67929
[prietukani@priet-TUF ~/]$ fg 67929
[prietukani@priet-TUF ~/]$ sleep 100 &
[1] 69148
[prietukani@priet-TUF ~/]$ activities
69148 : sleep 100 - Running
[prietukani@priet-TUF ~/]$ ping 69148 20
Sent signal 20 to process with pid 69148.
[prietukani@priet-TUF ~/]$ bg 69148
[prietukani@priet-TUF ~/]$ activities
69148 : sleep 100 - Running
```

## Neonate
`neonate` prints the Process-ID of the most recently created process on the system until the key 'x' is pressed. It is printed after every t seconds as given in input command. 
```bash
[prietukani@priet-TUF ~/]$ neonate -n 1
71195
71217
71246
71246
71268 #(key x was pressed here)
```

## iMan
`iMan` command fetches man pages from the internet using sockets and outputs it to the terminal (stdout). 
```bash
[prietukani@priet-TUF ~/]$ iMan ls
NAME
       ls - list directory contents

SYNOPSIS
       ls [OPTION]... [FILE]...

DESCRIPTION
       List  information
       
       ...continued
```

## Directory Structure
```bash
.
├── LISCENCE
├── makefile
├── README.md
├── src
│   ├── activities.c
│   ├── activities.h
│   ├── bg.h
│   ├── colours.h
│   ├── display_user_prompt.c
│   ├── display_user_prompt.h
│   ├── execute.c
│   ├── execute.h
│   ├── extra_functions.c
│   ├── extra_functions.h
│   ├── fg_bg.c
│   ├── fg_bg.h
│   ├── iman.c
│   ├── iman.h
│   ├── main.c
│   ├── main.h
│   ├── mantest.c
│   ├── neonate.c
│   ├── neonate.h
│   ├── pastevents.c
│   ├── pastevents.h
│   ├── pastevents.txt
│   ├── peek.c
│   ├── peek.h
│   ├── ping.c
│   ├── ping.h
│   ├── pipe.c
│   ├── pipe.h
│   ├── proclore.c
│   ├── proclore.h
│   ├── redirect.c
│   ├── redirect.h
│   ├── seek.c
│   ├── seek.h
│   ├── system_commands.c
│   ├── system_commands.h
│   ├── testiman.c
│   ├── testpipe.c
│   ├── warp.c
│   └── warp.h
└── start.sh

```


## Authors

- [Priet Ukani](https://github.com/priet-ukani)


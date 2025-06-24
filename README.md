<!--
  README.md for “C Shell” project
  A fully functional Unix-like shell implemented in C
-->

# C Shell

<p align="center">
  <a href="https://github.com/priet-ukani/mini-project-1-priet-ukani-final">
    <img src="https://img.shields.io/badge/language-C-blue.svg" alt="Language: C"/>
    <img src="https://img.shields.io/badge/license-MIT-green.svg" alt="License: MIT"/>
  </a>
</p>

A lightweight Unix-style command-line shell written in C, featuring:

- **Foreground & Background Execution**  
  Run multiple commands in one line; use `&` to send processes to the background.
- **Built-in Commands**  
  `cd`, `pwd`, `echo`, `history`, `neonate`, and more.
- **I/O Redirection & Piping**  
  Support for `>`, `<`, `>>`, and `|` operators.
- **Directory Navigation Shortcuts**  
  `cd ~`, `cd -` (`warp`), home-directory expansion.
- **Job Control**  
  Monitor, list, bring to foreground/background, and kill background jobs.
- **Recursive File Search**  
  `peek` command: list files/dirs; flags `-l`, `-a`.
- **Shell History**  
  Maintains last 15 commands in `pastevents.txt`.
- **System Commands**  
  All standard Unix utilities via `execvp()`.

---


<ol>

<li><a href="#prerequisites">Prerequisites</a></li>
<li><a href="#build--install">Build & Install</a></li>
<li><a href="#assumptions">Assumptions</a></li>
    

  <li><a href="#features">Features</a></li>
  <li><a href="#built-in-commands">Built-in Commands</a></li>
  <li><a href="#installation">Installation</a></li>
  <li><a href="#usage">Usage</a></li>
  <li><a href="#examples">Examples</a></li>
  <li><a href="#directory-structure">Directory Structure</a></li>
  <li><a href="#contributing">Contributing</a></li>
  <li><a href="#license">License</a></li>
</ol>

---

## ⚙️ Prerequisites

- POSIX-compliant OS (Linux/macOS)
- GCC (>= 4.8)
- `make` utility
- Standard C libraries

---

## 🛠️ Build & Install

```bash
# Clone the repo (if not already)
git clone https://github.com/priet-ukani/C-shell
cd C-shell
# Build the shell
make

# Or using the provided script:
chmod +x start.sh
./start.sh
# This produces an executable src/priet_shell (or simply a.out in src/).

```
## Assumptions 
- The time interval given in the neonate command is an integer and greater than 0. 
- Execvp may not be able to handle the commands with special characters or quotes which is not handled manually. So piping with sed `'\s \\g'` etc, execvp gives an error.
- iMan response depends on the connection and server. So it may be incomplete sometimes.
- The length of the command given in input is of maximum 1024 characters. Most of the strings are assumed to be of this length.
- The pastevents command assumes that only this shell has access the the history file and shell can only change the file.
- The signal handlers Ctrl+D and Ctrl+Z won't work with neonate command. 


## Features

* **Command Execution**: Run external programs in the foreground or background (using `&`).
* **Multiple Commands**: Chain commands on one line with `;` timing sequential execution.
* **Directory Navigation**: `cd` with support for:

  * `cd <path>`: Change to `<path>`
  * `cd` or `cd ~`: Return to home directory
  * `cd -`: Toggle to previous directory
* **Custom Prompt**: Displays `username@hostname:cwd$` with colored output.
* **File Listing**: `peek` command (an enhanced `ls`):

  * `peek [path]`: List files/directories
  * Flags: `-l` (long format), `-a` (include hidden)
* **Search**: `seek` command for recursive search:

  * `seek <path> <name>`: Search for `<name>` in `<path>`
  * Flags: `-f` (files), `-d` (directories)
* **Pipes & Redirection**:

  * Pipes: `cmd1 | cmd2 | ...`
  * Redirection: `>`, `>>`, `<`
* **Background Jobs**:

  * `jobs` (via `activities`): List jobs
  * `bg <job_id>`: Resume job in background
  * `fg <job_id>`: Bring job to foreground
* **Process Control**: `proclore`: Display running processes with details.
* **Networking**: Built-in `ping <host>` wrapper.
* **Utility Functions**:

  * Aliases and user-defined functions via parsing utilities.

---

## Built-in Commands

<table>
  <thead>
    <tr><th>Command</th><th>Usage</th><th>Description</th></tr>
  </thead>
  <tbody>
    <tr><td><code>cd</code></td><td><code>cd [dir]</code></td><td>Change directory (see features for flags).</td></tr>
    <tr><td><code>peek</code></td><td><code>peek [path] [-l] [-a]</code></td><td>List files/directories (enhanced <code>ls</code>).</td></tr>
    <tr><td><code>seek</code></td><td><code>seek <path> <name> [-f | -d]</code></td><td>Recursive search for files or dirs.</td></tr>
    <!-- should also have man/iman -->
    <tr><td><code>neonate</code></td><td><code>neonate <time_interval></code></td><td>Run a command after a specified time interval.</td></tr>
    <tr><td><code>pastevents</code></td><td><code>
pastevents</code></td><td>Display last 15 commands from history.</td></tr>
    <tr><td><code>echo</code></td><td><code>echo [text]</code></td><td>Print text to standard output.</td></tr>
    <tr><td><code>pwd</code></td><td><code>pwd</code></td><td>Print current working directory.</td></tr>
    <tr><td><code>history</code></td><td><code>history</code></td><td>Show command history (last 15 commands).</td></tr>
    <tr><td><code>iMan</code></td><td><code>iMan <command></code></td><td>Display manual for a command.</td></tr>
    <tr><td
><code>pipe</code></td><td><code>pipe <cmd1> | <cmd2> | ...</code></td><td>Pipe output from one command to another.</td></tr>
    <tr><td><code>redirect</code></td><td><code>redirect <cmd> > <file></code></td><td>Redirect output to a file.</td></tr>
    <tr><td><code>system</code></td><td><code>system <cmd></code></td><td>Execute a system command.</td>
<!-- signal -->
    </tr>
    <tr><td><code>ping</code></td><td><code>ping [pid] [code] <host></code></td><td> Send signals to the processes.</td></tr>
    <tr><td><code>jobs</code> / <code>activities</code></td><td><code>jobs</code></td><td>List active background jobs.</td></tr>
    <tr><td><code>bg</code></td><td><code>bg <job_id></code></td><td>Resume a stopped job in background.</td></tr>
    <tr><td><code>fg</code></td><td><code>fg <job_id></code></td><td>Bring a background job to foreground.</td></tr>
    <tr><td><code>proclore</code></td><td><code>proclore</code></td><td>Show running processes with details.</td></tr>
    <tr><td><code>warp</code></td><td><code>warp</code></td><td>Custom `cd` shortcuts (`~`, `-`).</td></tr>
    <tr><td><code>exit</code></td><td><code>exit</code></td><td>Terminate the shell and clean up.</td></tr>
  </tbody>
</table>

---

## Installation

```bash
# Clone the repository
git clone https://github.com/priet-ukani/mini-project-1-priet-ukani-final.git
cd mini-project-1-priet-ukani-final

# Build the shell
make
```

## Usage

Start the custom shell using:

```bash
./start.sh
```

You will see a prompt like:

```bash
priet@machine:~/path/to/directory$
```

Enter commands as you would in Bash.

---

## Examples

1. **Listing and filtering files**

   ```bash
   priet@machine:~$ peek . -l -a
   total 40
   drwxr-xr-x  2 user user 4096 Jun 24 15:00 .
   drwxr-xr-x 10 user user 4096 Jun 24 14:00 ..
   -rw-r--r--  1 user user  512 Jun 24 14:50 file.txt
   ```

2. **Recursive search for C files**

   ```bash
   priet@machine:~/src$ seek . *.c -f
   ./main.c
   ./execute.c
   ./peek.c
   ```

3. **Piping and redirection**

   ```bash
   priet@machine:~$ peek . -l | grep ".c" > c_files.txt
   priet@machine:~$ peek c_files.txt
   main.c
   execute.c
   ```

4. **Background job control**

   ```bash
   priet@machine:~$ sleep 100 &
   [1] 2345
   priet@machine:~$ jobs
   1: sleep 100 - Running
   priet@machine:~$ fg 1
   (brings sleep to foreground)
   ```

---

## Directory Structure

<!-- Copy and paste the following directory structure with file descriptions into your README.md -->

## 📂 Project Structure

```bash
.
├── LISCENCE                   # Project license (MIT)
├── README.md                  # This file: project overview & usage
├── makefile                   # Build rules for GCC and clean targets
├── start.sh                   # Convenience script to compile & run shell
├── src                        # Source code directory
│   ├── a.out                  # Compiled binary (ignore in version control)
│   ├── activities.c           # Implements `activities` command: list & sort jobs
│   ├── activities.h           # Header for activities.c
│   ├── bg.h                   # Data structures & declarations for background jobs
│   ├── colours.h              # ANSI color code definitions for prompt/output
│   ├── display_user_prompt.c  # Renders the shell prompt (user@host:cwd)
│   ├── display_user_prompt.h  # Header for display_user_prompt.c
│   ├── execute.c              # Core executor: forks, handles pipes & redirection
│   ├── execute.h              # Header for execute.c
│   ├── extra_functions.c      # Utility functions: string parsing, trimming, etc.
│   ├── extra_functions.h      # Header for extra_functions.c
│   ├── fg_bg.c                # Implements `fg` and `bg` built-ins
│   ├── fg_bg.h                # Header for fg_bg.c
│   ├── iman.c                 # Implements `iman`: fetch and parse WHOIS name records
│   ├── iman.h                 # Header for iman.c
│   ├── main.c                 # Entry point: read line, parse, dispatch commands
│   ├── main.h                 # Global constants, includes, and function prototypes
│   ├── mantest.c              # Manual/test harness for development/debugging
│   ├── neonate.c              # Implements `neonate`: keystroke monitor in raw mode
│   ├── neonate.h              # Header for neonate.c
│   ├── pastevents.c           # Manages shell history: read/write `pastevents.txt`
│   ├── pastevents.h           # Header for pastevents.c
│   ├── pastevents.txt         # Persistent history store (last 15 commands)
│   ├── peek.c                 # Implements `peek`: recursive `ls` clone with flags
│   ├── peek.h                 # Header for peek.c
│   ├── ping.c                 # Implements `ping`: ICMP echo requests
│   ├── ping.h                 # Header for ping.c
│   ├── pipe.c                 # Lower-level pipe setup helpers
│   ├── pipe.h                 # Header for pipe.c
│   ├── proclore.c             # Implements `pinfo` (“proc lore”): display process info
│   ├── proclore.h             # Header for proclore.c
│   ├── redirect.c             # Implements input/output redirection (`<`, `>`, `>>`)
│   ├── redirect.h             # Header for redirect.c
│   ├── seek.c                 # Implements `seek`: recursive file/directory search
│   ├── seek.h                 # Header for seek.c
│   ├── system_commands.c      # Wrappers to invoke external commands via execvp()
│   ├── system_commands.h      # Header for system_commands.c
│   ├── warp.c                 # Implements `warp`: `cd -`, `cd ~`, etc. shortcuts
│   └── warp.h                 # Header for warp.c
└── start.sh                   # Top‐level convenience script to build & launch
```

---

## Contributing

Contributions are welcome! Please fork the repo and open a pull request.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

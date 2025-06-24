#include "neonate.h"
#include "sys/time.h"

void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

/**
 * Enable row mode for the terminal
 * The ECHO feature causes each key you type to be printed to the terminal, so you can see what you’re typing.
 * Terminal attributes can be read into a termios struct by tcgetattr().
 * After modifying them, you can then apply them to the terminal using tcsetattr().
 * The TCSAFLUSH argument specifies when to apply the change: in this case, it waits for all pending output to be written to the terminal, and also discards any input that hasn’t been read.
 * The c_lflag field is for “local flags”
 */
void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

/**
 * stdout and stdin are buffered we disable buffering on that
 * After entering in raw mode we read characters one by one
 * Up arrow keys and down arrow keys are represented by 3 byte escape codes
 * starting with ascii number 27 i.e. ESC key
 * This way we interpret arrow keys
 * Tabs are usually handled by the term, but here we are simulating tabs for the sake of simplicity
 * Backspace move the cursor one control character to the left
 * @return
 */

void neonate(char *command)
{
    char **Command = separate_by_delimeter(command, " ");
    int total_args = 0;
    while (Command[total_args] != NULL)
    {
        total_args++;
    }
    if (total_args != 3)
    {
        fprintf(stderr, "Invalid number of arguments\n");
        return;
    }
    if (strcmp(Command[1], "-n") != 0)
    {
        fprintf(stderr, "Invalid argument\n");
        return;
    }

    char c;
    // Save the original terminal settings
    struct termios original_termios;
    tcgetattr(STDIN_FILENO, &original_termios);

    // Modify the terminal settings for raw mode
    struct termios raw_termios = original_termios;
    raw_termios.c_lflag &= ~(ICANON | ECHO);
    raw_termios.c_cc[VMIN] = 0;
    raw_termios.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios);
    // printf("hi out loop");
    // Read and process input in raw mode
    int counter = 0;
    int breakt = atoi(Command[2]);
    int breakpoint=breakt;
    if (atoi(Command[2]) == 0)
    {
        fprintf(stderr, "time interval cannot be 0 seconds");
        return;
    }
    while (1)
    {
        if (counter == 0)
        {
            // printf("%d %d", counter, breakpoint);
            if (read(STDIN_FILENO, &c, 1) == -1)
            {
                perror("read");
                break;
            }
            if (c == 'x')
            {
                c = ' ';
                break;
            }
            FILE *f = fopen("/proc/loadavg", "r");
            if (f == NULL)
            {
                fprintf(stderr, "Can't open /proc/loadavg file\n");
                break;
            }
            char data[1024];
            fgets(data, 1024, f);
            char *val = strtok(data, " ");
            for (int i = 0; i < 4; i++)
            {
                val = strtok(NULL, " ");
            }
            printf("%s", val);
        }

        counter++;
        // printf("%d\n", counter);
        if (counter==breakpoint)
        {
            counter = 0;
        }
        sleep(1);
    }

    // Restore the original terminal settings
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);

    return;
}

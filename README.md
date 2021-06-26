# minishell

# TODO List
- [ ] Foundation block (Basic loop of a shell)

- [ ] builtins functions like in bash:
    - [ ] "echo" with option ’-n’
    - [ ] "cd" with only a relative or absolute path
    - [ ] "pwd" without any options
    - [ ] "export" without any options
    - [ ] "unset" without any options
    - [ ] "env" without any options and any arguments
    - [ ] "exit" without any options

# Resources
Starting point to learn how the whole process works
- https://brennan.io/2015/01/16/write-a-shell-in-c/

## To make it run
- Install readline library. have brew working on OS 
https://code2care.org/zsh/fix-zsh-command-not-found-brew

# Allowed Function
- `chdir` : `int chdir(const char *path);`
    changes the current working directory of the calling process to the directory specified in path.

- `getcwd` : `char *getcwd(char *buf, size_t size);`
    return a null-terminated string containing an
    absolute pathname that is the current working directory of the
    calling process.  The pathname is returned as the function result
    and via the argument buf, if present.

    If the length of the absolute pathname of the current working
    directory, including the terminating null byte, exceeds size
    bytes, NULL is returned, and errno is set to ERANGE; an
    application should check for this error, and allocate a larger
    buffer if necessary.

- `execve` : `int execve(const char *path, char *const argv[], char *const envp[]);`
    execve() does not return on succes.
    https://jameshfisher.com/2017/02/05/how-do-i-use-execve-in-c/

- `History`
    Everytime bash is called (terminal created), a copy of the ~/.bash_history is created, and is stored as a form of list. As the user type commands, this list keeps track of the history of the commands. When the number of commands exceeds MAX_HISTORY_SIZE, the oldest entry gets overwriten. Note that, while bash shell is alive, the ~/.bash_history remains the same. It is only at the end, when bash shell gets killed, that the ~/.bash_history gets updated.
    Once we have a way of keeping the records, all you need is `add_history`, which works with `readline`.

- `Exit status`:
    Always truncated to 8 bits. Therefore it expects a value between 0 and 255.

- `Handle SIGINT with readline`
    We want to clear the content of the readline buffer after receiving CTRL+C. The combination of `rl_replace_line` and `rl_redisplay` allows this.
    https://stackoverflow.com/questions/53165704/readline-c-force-return-of-certain-text-in-readline
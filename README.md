[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/76mHqLr5)
# Operating Systems and Networks | Mini Project 1
### sheeSH | a C Shell
Nanda Rajiv | 2021115002

### Instructions
- To compile the shell, run the command `make` in the terminal.
- To run the shell, run the command `./a.out` in the terminal.
- To exit the shell, run the command `exit` in the shell, or press `Ctrl + D` in the terminal.

The code has been written for a system running Ubuntu.
<br><br> 
### [Part A]
### Features
- All features as part of the Part A submission have been implemented as of now, including peek, seek, proclore, pastevents, system commands, and foreground/background processes.

### Assumptions

<!-- Assumptions are as follows: -->
- The maximum size of the username and system name as 255 characters each.
- The maximum size of a path is 4095 characters.
- Lexicographical order is the one obtained by strcmp() function.
- No file/directory will have whitespace in the name.
- If I do `<command> ..` at `/` there is no further previous directory to go to, so it will stay at `/`.
- Relative paths will not start with `/` while absolute paths will start with `/`.
- If the command `warp .. xyz` is given, and xyz is not a valid directory, the shell will warp to `..` and diplay an error message.
- Multiple arguments cannot be given as input for peek.
- No file will be name `pastevents.txt` within a `/pastevents` directory, in the directory from which shell is called.
- When 'seek' is called in a folder which has an elaborate tree (for example '/home'), there is a chance of the error 'fopen: too many open files' to occur. Try to ensure not to call seek on a folder with a large tree, unless you know the file is close to the path from where you are calling, to prevent this error. (This is due to a recursive call, and on a deep tree, could result in too many open directories as it recurses)
- Any command contains the string 'pastevents' is not going to be reflected on called 'pastevents'.


### [Part B]
### Features
- Implemented all features part of Part B, inlcuding iMan, signals, neonate, fg, bg, activities, pipes, I/O redirection.
### Assumptions
- Pastevents won't be called with I/O redirection or with pipes.
- The maximum number of piped commands is 100.
- Only valid I/O redirections will be given as input.
- Foreground or background processes will only be normal terminal commands, and not commands implemented by us such as warp, seek, peek, proclore, etc.
- File names will only be alphabets, and will not contain any special characters.

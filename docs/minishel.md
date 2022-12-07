# Minishell:

## Classic:
- printf
- malloc
- free
- write
- exit

## Files:
- access
- open
- read
- close

## Pipex:
- fork
- wait
- waitpid
- wait3, wait4: wait for process to change state, BSD style
	- These functions are nonstandard; in new programs, the use of **waitpid(2)** or waitid(2) is preferable.
- dup
- dup2
- unlink
- execve
- pipe

## Signals:
- signal: ANSI C signal handling
	- **WARNING**: the  behavior  of signal() varies across UNIX versions, and has also varied historically across  different  versions  of Linux.  Avoid its use: use **sigaction(2)** instead.
- sigaction: The sigaction() system call is used to change the action taken by a process on receipt of a specific signal. (See **signal(7)** for an overview of signals.)
- kill: The kill() system call can be used to send any signal to any process group or process.
	- If  pid  is positive, then signal sig is sent to the process with the ID specified by pid.
	- If pid equals 0, then sig is sent to every  process  in  the process group of the calling process.
	- If  pid  equals  -1,  then  sig is sent to every process for which the calling process has permission  to  send  signals, except for process 1 (init), but see below.
	- If pid is less than -1, then sig is sent to every process in the process group whose ID is -pid.

## Terminal cmds:
### Directories:
- getcwd: get current working directory.
	- ``char *getcwd(char *buf, size_t size);``
	- copies an  absolute pathname of the current working directory to the array pointed to by buf, which is of length size.
- chdir: change working directory.
	- changes the current working directory of the calling process to the directory specified in path.
	- On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
- opendir: opens a directory.
- readdir: reads a directory.
- closedir: closes a directory.

### File status:
- stat, lstat, fstat: get file status
```
These functions return information about a file, in the buf‐
fer pointed to by statbuf.  No permissions are  required  on
the  file  itself, but—in the case of stat(), fstatat(), and
lstat()—execute (search) permission is required  on  all  of
the directories in pathname that lead to the file.

stat()  and  fstatat()  retrieve  information about the file
pointed to by pathname; the differences  for  fstatat()  are
described below.

lstat() is identical to stat(), except that if pathname is a
symbolic link, then it returns information  about  the  link
itself, not the file that the link refers to.

fstat()  is  identical to stat(), except that the file about
which information is to be retrieved  is  specified  by  the
file descriptor fd.
```

## History:
- rl_clear_history: Clear the history list by deleting all of the entries
- add_history: Place string at the end of the history list. The associated data field (if any) is set to NULL.


## TUI:
- readline: Reads a line  from STDIN (with editing capabilities) and returns a malloc()-ed string without '\n'.
- rl_on_new_ine: Tell the update functions that we have moved onto a new (empty) line.
- rl_replace_line: Replace the contents of 'rl_line_buffer' with 'text'.
- rl_redisplay: Change what's displayed on the screen to reflect the current contents of 'rl_line_buffer'.
	- If the maximum number of history entries has been set using stifle_history(), and the new number of history entries.
	- would exceed that maximum, the oldest history entry is removed.

## Tools:
- strerror: takes an error code (int) and returns the msg describing the error.
- perror: ft_put_str_fd with fd = 2.
- isatty: tests whether a file descriptor refers to a terminal.
- ttyname: Returns the name of a terminal (fd of the terminal given by input).
- getenv: get an environment variable
	- ``char *getenv(const char *name);``
	- searches the environment list to find the environment variable name, and returns a pointer to the corresponding value string (NULL if not found).
- tcsetattr: sets the parameters associated with the terminal (unless support is required from the underlying hardware that is not available) from the termios structure referred to by termios_p.
- tcgetattr: gets the parameters associated with the object referred by fd and stores them in the termios structure referenced by termios_p. This function may be invoked from a background process; however, the terminal attributes may be subsequently changed by a foreground process.
- tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs: direct curses interface to the terminfo capability database
```
Synopsis
#include <curses.h>
#include <term.h>

extern char PC;
extern char * UP;
extern char * BC;
extern unsigned ospeed;

int tgetent(char *bp, const char *name);
int tgetflag(char *id);
int tgetnum(char *id);
char *tgetstr(char *id, char **area);
char *tgoto(const char *cap, int col, int row);
int tputs(const char *str, int affcnt, int (*putc)(int));

Description
These routines are included as a conversion aid for programs that use the termcap library. Their parameters are the same and the routines are emulated using the terminfo database. Thus, they can only be used to query the capabilities of entries for which a terminfo entry has been compiled.

The tgetent routine loads the entry for name. It returns 1 on success, 0 if there is no such entry, and -1 if the terminfo database could not be found. The emulation ignores the buffer pointer bp.

The tgetflag routine gets the boolean entry for id, or zero if it is not available.

The tgetnum routine gets the numeric entry for id, or -1 if it is not available.

The tgetstr routine returns the string entry for id, or zero if it is not available. Use tputs to output the returned string. The return value will also be copied to the buffer pointed to by area, and the area value will be updated to point past the null ending this value.

Only the first two characters of the id parameter of tgetflag, tgetnum and tgetstr are compared in lookups.

The tgoto routine instantiates the parameters into the given capability. The output from this routine is to be passed to tputs.

The tputs routine is described on the curs_terminfo(3X) manual page. It can retrieve capabilities by either termcap or terminfo name.

The variables PC, UP and BC are set by tgetent to the terminfo entry's data for pad_char, cursor_up and backspace_if_not_bs, respectively. UP is not used by ncurses. PC is used in the tdelay_output function. BC is used in the tgoto emulation. The variable ospeed is set by ncurses in a system-specific coding to reflect the terminal speed.

Return Value
Except where explicitly noted, routines that return an integer return ERR upon failure and OK (SVr4 only specifies "an integer value other than ERR") upon successful completion.

Routines that return pointers return NULL on error.
```


## ??:
- ttyslot: find the slot of the current user's terminal in some file.
```
SYNOPSIS
       #include <unistd.h>       /See NOTES */

       int ttyslot(void);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       ttyslot():
           Since glibc 2.24:
               _DEFAULT_SOURCE
           From glibc 2.20 to 2.23:
               _DEFAULT_SOURCE ||
               _XOPEN_SOURCE && _XOPEN_SOURCE < 500
           Glibc 2.19 and earlier:
               _BSD_SOURCE ||
               _XOPEN_SOURCE && _XOPEN_SOURCE < 500

DESCRIPTION
       The  legacy  function  ttyslot()  returns  the  index of the current
       user's entry in some file.

       Now "What file?" you ask.  Well, let's first look at some history.

   Ancient history
       There used to be a file /etc/ttys in UNIX V6, that was read  by  the
       init(1)  program  to  find  out  what to do with each terminal line.
       Each line consisted of three characters.  The  first  character  was
       either  '0'  or '1', where '0' meant "ignore".  The second character
       denoted the terminal: '8' stood for "/dev/tty8".  The third  charac‐
       ter  was  an  argument  to  getty(8) indicating the sequence of line
       speeds to try ('-' was: start trying 110 baud).  Thus a typical line
       was  "18-".  A hang on some line was solved by changing the '1' to a
       '0', signaling init, changing back again, and signaling init again.

       In UNIX V7 the format was changed: here the second character was the
       argument  to  getty(8) indicating the sequence of line speeds to try
       ('0' was: cycle through 300-1200-150-110 baud; '4' was for  the  on-
       line  console  DECwriter)  while  the rest of the line contained the
       name of the tty.  Thus a typical line was "14console".

       Later systems have more elaborate  syntax.   System  V-like  systems
       have /etc/inittab instead.

   Ancient history (2)
       On  the  other  hand, there is the file /etc/utmp listing the people
       currently logged in.  It is maintained by login(1).  It has a  fixed
       size,  and  the  appropriate index in the file was determined by lo‐
       gin(1) using the ttyslot() call to find the number of  the  line  in
       /etc/ttys (counting from 1).

   The semantics of ttyslot
       Thus,  the  function  ttyslot() returns the index of the controlling
       terminal of the calling process in the file /etc/ttys, and  that  is
       (usually) the same as the index of the entry for the current user in
       the file /etc/utmp.  BSD still has the /etc/ttys file, but System V-
       like  systems  do  not, and hence cannot refer to it.  Thus, on such
       systems the documentation says that ttyslot()  returns  the  current
       user's index in the user accounting data base.

RETURN VALUE
       If  successful,  this  function  returns  the slot number.  On error
       (e.g., if none of the file descriptors 0, 1 or 2 is associated  with
       a  terminal  that  occurs in this data base) it returns 0 on UNIX V6
       and V7 and BSD-like systems, but -1 on System V-like systems.

ATTRIBUTES
       For an explanation of the  terms  used  in  this  section,  see  at‐
       tributes(7).

       ┌──────────┬───────────────┬───────────┐
       │Interface │ Attribute     │ Value     │
       ├──────────┼───────────────┼───────────┤
       │ttyslot() │ Thread safety │ MT-Unsafe │
       └──────────┴───────────────┴───────────┘
CONFORMING TO
       SUSv1;  marked  as  LEGACY in SUSv2; removed in POSIX.1-2001.  SUSv2
       requires -1 on error.

NOTES
       The utmp file is found in various places on various systems, such as
       /etc/utmp, /var/adm/utmp, /var/run/utmp.

       The   glibc2   implementation   of  this  function  reads  the  file
       _PATH_TTYS, defined in <ttyent.h> as "/etc/ttys".  It returns  0  on
       error.  Since Linux systems do not usually have "/etc/ttys", it will
       always return 0.

       On BSD-like systems and Linux, the declaration of ttyslot() is  pro‐
       vided  by  <unistd.h>.  On System V-like systems, the declaration is
       provided by <stdlib.h>.  Since glibc 2.24, <stdlib.h> also  provides
       the declaration with the following feature test macro definitions:

           (_XOPEN_SOURCE >= 500 ||
                   (_XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED))
               && ! (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600)

       Minix also has fttyslot(fd).

SEE ALSO
       getttyent(3), ttyname(3), utmp(5)
```

- ioctl: control device
```
SYNOPSIS
       #include <sys/ioctl.h>

       int ioctl(int fd, unsigned long request, ...);

DESCRIPTION
       The ioctl() system call manipulates the underlying device parameters of special files.  In particular, many operating characteristics of charac‐
       ter special files (e.g., terminals) may be controlled with ioctl() requests.  The argument fd must be an open file descriptor.

       The second argument is a device-dependent request code.  The third argument is an untyped pointer to  memory.   It's  traditionally  char  *argp
       (from the days before void * was valid C), and will be so named for this discussion.

       An  ioctl()  request  has  encoded  in  it whether the argument is an in parameter or out parameter, and the size of the argument argp in bytes.
       Macros and defines used in specifying an ioctl() request are located in the file <sys/ioctl.h>.  See NOTES.

RETURN VALUE
       Usually, on success zero is returned.  A few ioctl() requests use the return value as an output parameter and return a nonnegative value on suc‐
       cess.  On error, -1 is returned, and errno is set appropriately.

ERRORS
       EBADF  fd is not a valid file descriptor.

       EFAULT argp references an inaccessible memory area.

       EINVAL request or argp is not valid.

       ENOTTY fd is not associated with a character special device.

       ENOTTY The specified request does not apply to the kind of object that the file descriptor fd references.

CONFORMING TO
       No  single standard.  Arguments, returns, and semantics of ioctl() vary according to the device driver in question (the call is used as a catch-
       all for operations that don't cleanly fit the UNIX stream I/O model).

       The ioctl() system call appeared in Version 7 AT&T UNIX.

NOTES
       In order to use this call, one needs an open file descriptor.  Often the open(2) call has unwanted side effects, that can be avoided under Linux
       by giving it the O_NONBLOCK flag.

   ioctl structure
       Ioctl command values are 32-bit constants.  In principle these constants are completely arbitrary, but people have tried to build some structure
       into them.

       The old Linux situation was that of mostly 16-bit constants, where the last byte is a serial number, and the preceding byte(s) give a type indi‐
       cating  the  driver.  Sometimes the major number was used: 0x03 for the HDIO_* ioctls, 0x06 for the LP* ioctls.  And sometimes one or more ASCII
       letters were used.  For example, TCGETS has value 0x00005401, with 0x54 = 'T'  indicating  the  terminal  driver,  and  CYGETTIMEOUT  has  value
       0x00435906, with 0x43 0x59 = 'C' 'Y' indicating the cyclades driver.

       Later  (0.98p5)  some more information was built into the number.  One has 2 direction bits (00: none, 01: write, 10: read, 11: read/write) fol‐
       lowed by 14 size bits (giving the size of the argument), followed by an 8-bit type (collecting the ioctls in groups for a common  purpose  or  a
       common driver), and an 8-bit serial number.

       The  macros  describing this structure live in <asm/ioctl.h> and are _IO(type,nr) and {_IOR,_IOW,_IOWR}(type,nr,size).  They use sizeof(size) so
       that size is a misnomer here: this third argument is a data type.

       Note that the size bits are very unreliable: in lots of cases they are wrong, either because of buggy macros  using  sizeof(sizeof(struct)),  or
       because of legacy values.

       Thus, it seems that the new structure only gave disadvantages: it does not help in checking, but it causes varying values for the various archi‐
       tectures.

SEE ALSO
       execve(2),  fcntl(2),  ioctl_console(2),  ioctl_fat(2),  ioctl_ficlonerange(2),  ioctl_fideduperange(2),  ioctl_fslabel(2),   ioctl_getfsmap(2),
       ioctl_iflags(2), ioctl_ns(2), ioctl_tty(2), ioctl_userfaultfd(2), open(2), sd(4), tty(4)
```

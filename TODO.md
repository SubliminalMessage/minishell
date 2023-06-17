- [x] cd ~/ throws no such file or directory

- [x] cd with arg ended in / is detected as not file nor directory

- [ ] expansion of ~ in quotes? Is done but in bash linux it is not done

- [ ] Leaks:
```
jldkasf
```
```
==1531== 4 bytes in 1 blocks are definitely lost in loss record 5 of 61
==1531==    at 0x4C31B0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==1531==    by 0x408667: ft_calloc (in /docker/minishell)
==1531==    by 0x408CC0: ft_substr (in /docker/minishell)
==1531==    by 0x402476: save_and_clear_single_arg (in /docker/minishell)
==1531==    by 0x402414: save_redirection_single_arg (in /docker/minishell)
==1531==    by 0x40231D: fill_redirections (in /docker/minishell)
==1531==    by 0x401374: parse_command (in /docker/minishell)
==1531==    by 0x400E6C: parse_command_node (in /docker/minishell)
==1531==    by 0x400F8B: main (in /docker/minishell)
```

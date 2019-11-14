# 42sh : code your own shell !!
This is a 42 school project.
The purpose is to create our own shell from scratch, using only the really basics fuctions :
  - functions from man 2
  - library Termcaps
  - getpwnam, tcgetpgrp and tcsetpgrp

# Features :
####  Basic features
  - Executing basic commands
  - Show a prompt
  - Error handling

####  21sh features
  - Complete line edition
  - Redirections and aggregations operators : **>, <, >>, <<, >&, <&**
  - Pipes : **|**

#### 42sh Features :
##### Line edition
##### Variable managment
##### Job Control :
   - builtins : `jobs, fg, bg`
##### Signal manager :
##### Posix builtins :
   - cd, echo, exit
   - type, pwd
   - set, unset (not posix, as asked in subject)
##### Quoting :
   - Double quoting : `"`
   - simple quoting `'`
   - backslash : `\`
##### Pattern matching :
   - `*` : match any string (even null string)
   - `?` : match any character
   - `[]` : match any char contained between brace (support interval : [A-z])
   - `[!]` : match any char not contained in braces (support interval too)
##### Tilde and parameter expansions : `~/` and `${}` :
   - ~/ and ~user/
   - ${param:-word} and ${param-word}
   - ${param:=word} and ${param=word}
   - ${param:?word} and ${param?word}
   - ${param:+word} and ${param+word}
   - ${param##word} and ${param#word}
   - ${param%%word} and ${param%word}
##### Grouped commands and subshells : `() and {}`
##### Command subsitution : `$(cmd)` and `` `cmd` ``
##### Processus substitution : `<() and >()`
##### Historique manager :
   - Expansions : `!!, !word, !number, !-number`
   - Save in a file
   - fc builtin
   - Incremental research : `CTRL-R`
##### Dynamic autocompletion :
   - commands
   - builtins
   - variables
##### Vim and Readline modes :
   - Vi shortcuts : `#, ,v,j,k,l,h,w,W,e,E,b,B,ˆ,$,0,|,f,F,t,T,;,,,a,A,i,I,r,R, c, C, S, x, X, d, D, y, Y, p, P, u, U.`
   - Readline shortcuts : `C-b, C-f, A-f, A-b, C-a, C-e, C-x-x, Backspace, C-d, C-u, C-k, A-d, C-w, C-y, C-p, C-n, C-_, C-t, A-t.`
##### Alias manager :
   - Alias expansion
   - Alias and unalias builtins
##### Hash table :
   - Hash table to store apth to binaries used
   - hash builtin
##### Test builtin :
   - options : ` -b, -c, -d, -e, -f, -g, -L, -p, -r, -S, -s, -u, -w, -x, -z, =, !=, -eq, -ne, -ge, -lt, -le, !.`

## Bonuses :
   - Handle utf-8 chars : see 🐑 builtin

# Auteur :
  - jmartel
  - ldedier
  - mdaoud
  - jdugoudr

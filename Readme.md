# My_LS

Given program implements simple version of linux `ls` command. 

## Run:
`./my_ls [path] [flags]`
    
Next flags are implemented:
- `-a`, `--all` show hidden files and directories

- `-l`, `--list` list files and directories showing full info about them
  
- `-R`, `--recursive` run program recursively

## Build:
To build do the following steps:
    
1. `git clone https://github.com/DKay7/MyLs.git && cd MyLS`
2. `mkdir build && cd build`
3. `cmake -DCMAKE_BUILD_TYPE=Release .. && make`
4. `./my_ls`



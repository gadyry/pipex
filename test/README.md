# pipex
House of Hummingbird


The **Pipex** project involves creating a program that mimics Unix shell pipe functionality (`cmd1 | cmd2`), redirecting input/output between commands and files. Here's a concise breakdown:

---

### **Core Objective**  
Create a program `pipex` that behaves like the shell command:  
`< file1 cmd1 | cmd2 > file2`  
Example:  
`./pipex infile "ls -l" "wc -l" outfile` ≈ `< infile ls -l | wc -l > outfile`

---

### **Key Concepts to Master**  
1. **Unix Process Management**  
   - `fork()`: Create child processes for commands.  
   - `execve()`: Execute commands (resolve paths using `PATH` environment variable).  
   - `wait()`/`waitpid()`: Synchronize parent and child processes.  

2. **Pipes and Redirection**  
   - `pipe()`: Create a unidirectional data channel.  
   - `dup2()`: Redirect stdin/stdout to pipe ends or files.  
   - Close unused file descriptors to prevent hangs.  

3. **File Handling**  
   - `open()`: Read input file (`file1`) and write to output file (`file2`).  
   - Handle errors (e.g., invalid files, permissions).  

4. **Command Parsing**  
   - Split commands (e.g., `"ls -l"` → `["ls", "-l", NULL]`).  
   - Use `access()` to check executable paths (resolve via `PATH`).  

5. **Error Handling**  
   - Check system call failures (e.g., `fork()`, `pipe()`, `execve()`).  
   - Use `perror()`/`strerror()` for meaningful error messages.  
   - Avoid leaks: Free memory, close file descriptors, and check `malloc()`.  

6. **Makefile**
   - Compile with `-Wall -Wextra -Werror`.  
   - Include rules: `all`, `clean`, `fclean`, `re`.  

---

### **Mandatory Part Steps**  
1. **Parse Arguments**  
   - Validate 4 arguments: `file1`, `cmd1`, `cmd2`, `file2`.  

2. **Set Up Pipes and Processes**  
   - Create a pipe.  
   - Fork first child to run `cmd1`:  
     - Redirect stdin to `file1` and stdout to the pipe’s write end.  
   - Fork second child to run `cmd2`:  
     - Redirect stdin to the pipe’s read end and stdout to `file2`.  

3. **Execute Commands**  
   - Use `execve()` with the parsed command paths and arguments.  

4. **Cleanup**  
   - Close all file descriptors.  
   - Wait for child processes to exit.  

---

### **Bonus Part (Optional)**  
1. **Multiple Pipes**  
   - Handle `cmd1 | cmd2 | cmd3 | ... | cmdn` using multiple pipes.  
   - Example: `./pipex file1 cmd1 cmd2 cmd3 file2`.  

2. **Here Document (heredoc)**  
   - Support `here_doc` as the first argument to read input until a delimiter.  
   - Example: `./pipex here_doc LIMITER cmd1 cmd2 file2` ≈ `cmd1 << LIMITER | cmd2 >> file2`.  

---

### **Critical Pitfalls to Avoid**  
- Forgetting to close unused pipe ends (causing deadlocks).  
- Incorrectly handling `execve()` failures (e.g., command not found).  
- Memory leaks or file descriptor leaks.  
- Not mimicking shell behavior exactly (e.g., error handling).  

---

### **Quick Implementation Strategy**  
1. **Start Small**  
   - Implement a single pipe with two commands (no files).  
   - Test with simple commands like `ls` and `wc`.  

2. **Add File Redirection**  
   - Open `file1` for reading and `file2` for writing.  

3. **Handle Errors**  
   - Add checks for all system calls and print errors.  

4. **Test Rigorously**  
   - Use edge cases: invalid files, non-existent commands, empty arguments.  

5. **Refactor and Optimize**  
   - Ensure no leaks (use tools like `valgrind`).  
   - Simplify code with helper functions (e.g., `ft_split`, `free_array`).  

---

### **Tools & Functions Allowed**  
- **System Calls**: `open`, `close`, `read`, `write`, `fork`, `pipe`, `dup2`, `execve`, etc.
- **Libft**: Use your own library for parsing (e.g., `ft_split`, `ft_strjoin`).  

By focusing on these steps and concepts, you can build the project efficiently while meeting all requirements.
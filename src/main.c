#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
void print(const char *txt) { write(1, txt, strlen(txt)); }
void printred(const char *txt) { print("\033[31m"); print(txt); print("\033[0m"); }
void printgreen(const char *txt) { print("\033[32m"); print(txt); print("\033[0m"); }
void sigint_func() {} // dont close after sigint
int main() {
	char *token;
	while(1) {
		signal(SIGINT, sigint_func);
		char *prompt = getenv("ZWSH_PROMPT");
		if (!prompt) {
			prompt = "zwsh-1.1.0$ ";
		}
		char *input = readline(prompt);
		add_history(input);
		token = strtok(input, " ");
        if (token == NULL) continue;
        
		if (strcmp(token, "exit") == 0) {
			free(input);
			return 0;
		}
		else if (strcmp(token, "echo") == 0) {
			char *arg = strtok(NULL, " ");
            while (arg != NULL) {
                print(arg);
                arg = strtok(NULL, " ");
                if (arg != NULL) print(" ");
            }
            print("\n");
		}
		else if (strcmp(token, "cd") == 0) {
			char *home = getenv("HOME");
			if (!home) {
				home = "/home";
			}
			char *arg = strtok(NULL, " ");
			if (arg == NULL) {
				arg = home;
			}
			else if (strcmp(arg, "~") == 0) {
				arg = home;
			}
            if (chdir(arg) == 0) {
			}
			else {
				perror("chdir");
			}
            arg = strtok(NULL, " ");
            if (arg != NULL) print("");
		}
		else if (strcmp(token, "ls") == 0) {
			char *arg = strtok(NULL, " ");
			if (arg == NULL) {
				arg = ".";
			}
			struct dirent *entry;
			DIR *dir = opendir(arg);
			if (dir == NULL) {
				perror("opendir");
				continue;
			}
			while ((entry = readdir(dir)) != NULL) {
				printf("%s\n", entry->d_name);
			}
			closedir(dir);
		}
		else if (strcmp(token, "pwd") == 0) {
			char cwd[1024];
			if (getcwd(cwd, sizeof(cwd)) != NULL) {
				print(cwd);
				print("\n");
			}
			else {
				perror("pwd");
			}
		}
		else if (strcmp(token, "help") == 0) {
			print("zwsh built-in commands:\n");
			print("pwd\n");
			print("cat\n");
			print("exit\n");
			print("clear\n");
			print("ls\n");
			print("cd\n");
			print("echo\n");
		}
		else if (strcmp(token, "cat") == 0) {
			char *arg = strtok(NULL, " ");
			if (arg == NULL) {
				perror("readfile");
			}
			ssize_t bytes; 
			int fd = open(arg, O_RDONLY);
			if (fd < 0) {
				perror("readfile");
				continue;
			}
			char buffer[16384]; 
			while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) { 
				write(1, buffer, bytes); 
			} 
			buffer[bytes] = '\0'; 
			print("\n"); 
			close(fd); 	
		}
		else if (strcmp(token, "clear") == 0) { print("\033[2J\033[H"); }
		else {
			pid_t pid = fork();
			char *args[64];
			int i = 0;
			args[i++] = token;
			token = strtok(NULL, " ");
			while (token != NULL && i < 63) {
				args[i++] = token;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;
			if (pid == 0) {
				execvp(args[0], args);
				perror("execvp");
				exit(1);
			}
			else if (pid > 0) {
				int status;
				waitpid(pid, &status, 0);
			}
			else {
				perror("fork");
			}
        }
        free(input);
	}
	return 0;
}

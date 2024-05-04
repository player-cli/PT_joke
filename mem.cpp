#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

long get_process_memory(pid_t pid, long addr) {
    long data;
    ptrace(PTRACE_PEEKDATA, pid, addr, &data);
    return data;
}

void set_process_memory(pid_t pid, long addr, long data) {
    ptrace(PTRACE_POKEDATA, pid, addr, data);
}

int main() {
    pid_t pid = PROCESS_PID; // Replace with the PID of the process you want to attach to
    long addr = BASE_ADRESS + OFFSET ; // Replace with the memory address you want to modify
    long new_value = NEW_VALUE_IN_HEX; // Replace with the new value you want to write to the memory address

    // Attach to the process
    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) < 0) {
        std::cerr << "Error attaching to process" << std::endl;
        return 1;
    }

    // Wait for the process to stop
    int status;
    waitpid(pid, &status, 0);

    // Write the new value to the memory address
    set_process_memory(pid, addr, new_value);

    // Detach from the process
    ptrace(PTRACE_DETACH, pid, NULL, NULL);

    return 0;
}

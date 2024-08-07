#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main() {
    const char *fifo_path = "/tmp/myfifo";
    int fd;
    char buffer[128];
    ssize_t num_bytes;
    // Create the FIFO if it does not exist
    if (mkfifo(fifo_path, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }
    // Open the FIFO with O_RDWR (read and write)
    fd = open(fifo_path, O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    // Write to the FIFO
    const char *message = "Hello from writer!";
    num_bytes = write(fd, message, strlen(message));
    if (num_bytes == -1) {
        perror("write");
        close(fd);
        return 1;
    }
    
    // Read from the FIFO
    num_bytes = read(fd, buffer, sizeof(buffer) - 1);
    if (num_bytes == -1) {
        perror("read");
        close(fd);
        return 1;
    }
    buffer[num_bytes] = '\0';  // Null-terminate the buffer
    printf("Read from FIFO: %s\n", buffer);

    // Close the FIFO
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}

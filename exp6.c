#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char message[] = "Linux System calls";
    char buffer[100];
    int n;

    // Open or create the file
    fd = open("text.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Write to the file
    write(fd, message, sizeof(message) - 1);

    // Move file position back to the beginning
    lseek(fd, 0, SEEK_SET);

    // Read from the file
    n = read(fd, buffer, sizeof(buffer) - 1);

    if (n == -1)
    {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[n] = '\0';
    printf("Data = %s\n", buffer);

    // Close the file
    close(fd);

    return 0;
}
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define DEVICE_FILE_PATH "/sys/bus/i2c/devices/7-0044/iio:device1/in_intensity_input"

int main()
{
    int fd = open(DEVICE_FILE_PATH, O_RDONLY);
    if (fd < 0)
    {
        perror("open() failed");
        exit(EXIT_FAILURE);
    }

    char readBuffer[32];
    ssize_t byteCount = read(fd, readBuffer, sizeof(readBuffer));
    if (byteCount < 0)
    {
        perror("read failed");
        exit(EXIT_FAILURE);
    }
    if (byteCount >= sizeof(readBuffer))
    {
        fprintf(stderr, "read buffer too small!\n");
        exit(EXIT_FAILURE);
    }

    readBuffer[byteCount] = '\0';
    close(fd);

    printf("Sensor says '%s'\n", readBuffer);
    return EXIT_SUCCESS;
}

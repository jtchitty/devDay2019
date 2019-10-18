#include "legato.h"

#define DEVICE_FILE_PATH "/sys/bus/i2c/devices/7-0044/iio:device1/in_intensity_input"

static void ReadSensor()
{
    int fd = open(DEVICE_FILE_PATH, O_RDONLY);
    LE_FATAL_IF(fd < 0, "open() failed: %m");

    char readBuffer[32];
    ssize_t byteCount = read(fd, readBuffer, sizeof(readBuffer));
    LE_FATAL_IF(byteCount < 0, "read failed: %m");
    LE_ASSERT(byteCount < sizeof(readBuffer));

    readBuffer[byteCount] = '\0';
    close(fd);

    printf("Sensor says '%s'\n", readBuffer);
}

COMPONENT_INIT
{
    ReadSensor();
    exit(EXIT_SUCCESS);
}

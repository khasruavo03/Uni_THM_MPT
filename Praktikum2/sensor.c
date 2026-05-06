#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

sensor* sensor_create(char* name, uint8_t busadress, status statuscode, uintegar32 read_value, uintegar32 write_value)
{
    sensor* s = (sensor*) malloc(sizeof(sensor));

    if (s == NULL)
    {
        printf("Error: Kann nicht genügend Speicher für den Sensor reservieren.\n");
        return NULL;
    }

    s->name = name;
    s->busadress = busadress;
    s->statuscode = statuscode;
    s->read_value = read_value;
    s->write_value = write_value;

    return s;
}

void sensor_delete(sensor* s)
{
    if (s == NULL) 
    {
        printf("Error: Sensor pointer ist NULL.\n");
        return;
    }
    free(s);
}

status sensor_read(sensor* s)
{
    if (s == NULL)
    {
        printf("Error: Sensor pointer is NULL\n");
        return READ_ERR;
    }

    printf("Read Value (int): %u\n", s->read_value.value);

    printf("Read Value (bytes): ");
    for (size_t i = 0; i < sizeof(uint32_t); i++)
    {
        printf("%02X ", (unsigned char)s->read_value.bytes[i]);
    }
    printf("\n");

    if (s->read_value.value == 0)
    {
        s->statuscode = READ_ERR;
    }
    else
    {
        s->statuscode = SUCCESS;
    }

    return s->statuscode;
}


status sensor_write(sensor* s)
{
    if (s == NULL)
    {
        printf("Error: Sensor pointer is NULL\n");
        return WRITE_ERR;
    }

    printf("Write Value (int): %u\n", s->write_value.value);

    printf("Write Value (bytes): ");
    for (size_t i = 0; i < sizeof(uint32_t); i++)
    {
        printf("%02X ", (unsigned char)s->write_value.bytes[i]);
    }
    printf("\n");

    if (s->write_value.value == 0)
    {
        s->statuscode = WRITE_ERR;
    }
    else
    {
        s->statuscode = SUCCESS;
    }

    return s->statuscode;
}

int main()
{
    uintegar32 read;
    uintegar32 write;

    read.value = 123;
    write.value = 456;

    sensor* s = sensor_create("Sensor1", 1, SUCCESS, read, write);

    sensor_read(s);
    sensor_write(s);

    sensor_delete(s);

    return 0;
}
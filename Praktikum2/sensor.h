/* @file aufg2.h
@author Khushi Singh
@date 2026-05-01
@brief Header-Datei zur Definition des Datentyps Sensor für einen imiginären Sensorschnittstellen */
#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

typedef enum {
    SUCCESS = 0,
    READ_ERR = 1,
    WRITE_ERR = 2
} status;

typedef union 
{
    uint32_t value;
    char bytes[sizeof(uint32_t)];
} uintegar32;

/* @brief Struktur zur Darstellung eines Sensors */
typedef struct 
{
    char* name;
    uint8_t busadress;
    status statuscode;
    uintegar32 read_value;
    uintegar32 write_value;
} sensor;

/* 
@brief Erstellt einen neuen Sensor
@param name Name des Sensors
@param busadress Busadresse des Sensors
@param statuscode Statuscode des Sensors
@param read_value Lesewert des Sensors
@param write_value Schreibwert des Sensors
@return Zeiger auf den erstellten Sensor 
*/
sensor* sensor_create(
    char* name,
    uint8_t busadress,
    status statuscode,
    uintegar32 read_value,
    uintegar32 write_value
);

/* 
@brief Löscht einen Sensor und gibt den belegten Speicher frei
@param s Zeiger auf den zu löschenden Sensor 
*/
void sensor_delete(sensor* s);


/*
@brief Liest den Wert eines Sensors aus
@param s-Pointer auf den Sensor
@return Statuscode des Lesevorgangs 
*/
status sensor_read(sensor* s);

/* 
@brief Schreibt einen Wert auf den Sensor
@param s-Pointer auf den Sensor
@return Statuscode des Schreibvorgangs 
*/
status sensor_write(sensor* s);

#endif /* SENSOR_H */


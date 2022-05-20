#ifndef RFID_H
#define RFID_H

#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 14 // RFID DATA FRAME FORMAT: 1byte head (value: 2), 10byte data (2byte version + 8byte tag), 2byte checksum, 1byte tail (value: 3)
#define DATA_SIZE 10 // 10byte data (2byte version + 8byte tag)
#define DATA_VERSION_SIZE 2 // 2byte version (actual meaning of these two bytes may vary)
#define DATA_TAG_SIZE 8 // 8byte tag
#define CHECKSUM_SIZE 2 // 2byte checksum

long hexstr_to_value(char *str, unsigned int length);
long extract_tag(char buffer[BUFFER_SIZE]);

#endif

/*
 * rfid.c
 *
 *  Created on: Apr 22, 2022
 *      Author: shiwarai
 */

#include "rfid.h"

long hexstr_to_value(char *str, unsigned int length) { // конвертирует 16-ричное число (строка в кодировки ASCII) в целое число
    char* copy = (char *)malloc((sizeof(char) * length) + 1);

    memcpy(copy, str, sizeof(char) * length);
    copy[length] = '\0';

    long value = strtol(copy, NULL, 16);

    free(copy);
    return value;
}

long extract_tag(char buffer[BUFFER_SIZE]) {
    char msg_head = buffer[0];
    char *msg_data = buffer + 1; // 10 байт = версия (2) + тег (8)
    char *msg_data_version = msg_data;
    char *msg_data_tag = msg_data + 2;
    char  *msg_checksum = buffer + 11; // 2 байта
    char msg_tail = buffer[13];

    long tag = hexstr_to_value((char*)msg_data_tag, DATA_TAG_SIZE);

    #ifdef MBED_DEBUG
    printf("Message-Head: \r\n");
    printf("%с\r\n", msg_head);

    printf("Message-Data (HEX): \r\n");
    for (int i = 0; i < DATA_VERSION_SIZE; ++i) {
      printf("%c\r\n", char(msg_data_version[i]));
    }
    printf("(version)\r\n");

    for (int i = 0; i < DATA_TAG_SIZE; ++i) {
      printf("%c\r\n", char(msg_data_tag[i]));
    }
    printf("(tag)\r\n");

    printf("Message-checksum (HEX): \r\n");
    for (int i = 0; i < CHECKSUM_SIZE; ++i) {
      printf("%c\r\n", char(msg_checksum[i]));
    }
    printf("\r\n");

    printf("Message-tail: \r\n");
    printf("%с\r\n", msg_tail);

    printf("--\r\n");

    printf("Extracted tag: \r\n");
    printf("%ld\r\n", tag);

    long checksum = 0;
    for (int i = 0; i < DATA_SIZE; i+= CHECKSUM_SIZE) {
      long val = hexstr_to_value((char*)msg_data + i, CHECKSUM_SIZE);
      checksum ^= val;
    }

    printf("Extracted checksum (HEX): \r\n");
    printf("%lx\r\n", checksum);

    if (checksum == hexstr_to_value((char*)msg_checksum, CHECKSUM_SIZE)) { // сравнение расчётной чек-суммы с полученной
        printf("OK\r\n"); // совпало
    } else {
        printf("NOT OK\r\n"); // не совпало
    }
    #endif

    return tag;
}


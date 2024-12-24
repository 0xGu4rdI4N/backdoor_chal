// helper.h
#ifndef HELPER_H
#define HELPER_H

#include <stddef.h>

void slice_string(const char *src, size_t start, size_t length, char *dest);
int validate(char* ptr, size_t len);

#endif // HELPER_H

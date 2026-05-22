#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef enum { STRING = 1, INT = 2, FLOAT = 3 } ArraysTypes;

struct Document {
  int size;
  char fileName[100];
  char* data;
};

struct _StringArray {
  int heap_size;
  int size;
  char** data;
};
typedef struct _StringArray StringArray;

struct _IntArray {
  int heap_size;
  int size;
  int* data;
};
typedef struct _IntArray IntArray;

struct _FloatArray {
  int heap_size;
  int size;
  float* data;
};
typedef struct _FloatArray FloatArray;

int strlength(char string[]);
StringArray split(char string[], const char delimiter[]);
void splitTest(char string[], const char delimiter[]);
int stringContains(char* haystack, char* needle);
int stringEquals(char* haystack, char* needle);
void Array_new(StringArray* array, IntArray* intarray, FloatArray* floatarray,
               int num);
void SArray_append(StringArray* array, char* data);
void SArray_remove(StringArray* array, int index);
void IArray_append(IntArray* array, int data);
void Array_free(StringArray* array, IntArray* intarray, FloatArray* floatarray,
                int num);
void remove_spaces_newline(char* s);
void remove_spaces(char* s);
void removeT(char* s);
void removeDashesAndTs(char* s);

struct Document getFile(char* path);

void Array_new(StringArray* array, IntArray* intarray, FloatArray* floatarray,
               int num) {
  switch (num) {
    case 1:
      array->heap_size = 1;
      array->size = 0;
      array->data = malloc(sizeof(char*) * array->heap_size);
      break;
    case 2:
      intarray->heap_size = 1;
      intarray->size = 0;
      intarray->data = malloc(sizeof(int*) * intarray->heap_size);
      break;
    case 3:
      floatarray->heap_size = 1;
      floatarray->size = 0;
      floatarray->data = malloc(sizeof(float*) * floatarray->heap_size);
      break;
  }
}

void SArray_append(StringArray* array, char* data) {
  while (array->size >= array->heap_size) {
    array->heap_size *= 2;

    array->data = realloc(array->data, sizeof(char*) * array->heap_size);
  }
  array->data[array->size] = strdup(data);
  array->size++;
}

void IArray_append(IntArray* array, int data) {
  while (array->size >= array->heap_size) {
    array->heap_size *= 2;

    array->data = realloc(array->data, sizeof(int) * array->heap_size);
  }
  array->data[array->size] = data;
  array->size++;
}

void FArray_append(FloatArray* array, float data) {
  while (array->size >= array->heap_size) {
    array->heap_size *= 2;

    array->data = realloc(array->data, sizeof(float) * array->heap_size);
  }
  array->data[array->size] = data;
  array->size++;
}

void SArray_remove(StringArray* array, int index) {
  if (index < 0 || index >= array->size) {
    return;
  }
  memmove(&array->data[index], &array->data[index + 1],
          (array->size - index - 1) * sizeof(char*));

  array->size--;
  array->heap_size--;

  array->data = realloc(array->data, sizeof(int) * array->heap_size);
}

void Array_free(StringArray* array, IntArray* intarray, FloatArray* floatarray,
                int num) {
  switch (num) {
    case 1:
      if (array != NULL) {
        return;
      }
      for (int i = 0; i <= array->size; i++) {
        free(array->data[i]);
      }
      free(array);
      break;
    case 2:
      if (intarray != NULL) {
        return;
      }
      free(intarray);
      break;
    case 3:
      if (floatarray != NULL) {
        return;
      }
      free(floatarray);
      break;
  }
}

struct Document getFile(char* path) {
  struct Document result;
  strcpy(result.fileName, path);

  FILE* file = fopen(path, "r");

  if (!file) {
    fprintf(stderr, "Could not load file from '%s'\n", path);
  }

  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char* buf = (char*)malloc(sizeof(char) * size + 1);
  fread(buf, 1, size, file);
  fclose(file);
  buf[size] = '\0';

  result.size = size;
  result.data = buf;
  return result;
}

int strlength(char string[]) {
  int length = 0;
  while (string[length] != '\0') {
    length++;
  }
  return length;
}

void splitTest(char string[], const char delimiter[]) {
  // char **string_array = malloc(size * sizeof(char *));
  // if (string_array == NULL) {
  // return NULL;
  // }
  char* copy = malloc(100);
  strcpy(copy, string);

  char* save_pointer;
  char* token;
  token = strtok_r(copy, delimiter, &save_pointer);

  int i = 0;
  while (token != NULL) {
    // strcpy(string_array[k], token);
    printf("%s\n", token);
    i++;
    token = strtok_r(NULL, delimiter, &save_pointer);
  }
  printf("%d\n", i);

  free(copy);
}

StringArray split(char string[], const char delimiter[]) {
  char* copy = malloc(100);
  strcpy(copy, string);

  char* save_pointer;
  char* token;
  token = strtok_r(copy, delimiter, &save_pointer);

  int size = 0;
  while (token != NULL) {
    size++;
    token = strtok_r(NULL, delimiter, &save_pointer);
  }

  free(copy);

  char* copy2 = malloc(100);
  strcpy(copy2, string);

  StringArray string_array;
  Array_new(&string_array, NULL, NULL, STRING);

  char* save_pointer2;
  char* token2 = strtok_r(copy2, delimiter, &save_pointer2);

  while (token2 != NULL) {
    SArray_append(&string_array, token2);
    token2 = strtok_r(NULL, delimiter, &save_pointer2);
  }
  free(copy2);

  return string_array;
}

int stringContains(char* haystack, char* needle) {
  for (int i = 0; haystack[i] != '\0'; i++) {
    int j = 0;
    while (needle[j] != '\0' && haystack[i + j] == needle[j]) {
      j++;
    }
    if (needle[j] == '\0') return 1;
  }
  return 0;
}
// test
int stringEquals(char* haystack, char* needle) {
  int j = 0;
  int i = 0;
  while (haystack[i] != '\0') {
    while (needle[j] != '\0') {
      if (haystack[i++] != needle[j++]) {
        return 0;
      }
    }
    if (needle[j] == '\0' && haystack[i] != '\0') {
      return 0;
    }
    if (needle[j] == '\0' && haystack[i] == '\0') {
      return 1;
    }
  }
  return 0;
}

void remove_spaces_newline(char* s) {
  int i = 0;
  int j = 0;
  while (s[i]) {
    if (s[i] != ' ' && s[i] != '\n') {
      s[j++] = s[i];
    }
    i++;
  }
  s[j] = '\0';
}

void remove_spaces(char* s) {
  int i = 0;
  int j = 0;
  while (s[i]) {
    if (s[i] != ' ') {
      s[j++] = s[i];
    }
    i++;
  }
  s[j] = '\0';
}

char* remove_style(char* part) {
  StringArray partSplit = split(part, "-");

  char* newPart = malloc(100);
  int newPartSize = partSplit.size - 1;

  switch (newPartSize) {
    case 1:
      sprintf(newPart, "%s-?\?", partSplit.data[0]);
      break;
    case 2:
      sprintf(newPart, "%s-?\?-%s", partSplit.data[0], partSplit.data[2]);
      break;
    case 3:
      sprintf(newPart, "%s-?\?-%s-%s", partSplit.data[0], partSplit.data[2],
              partSplit.data[3]);
      break;
    case 4:
      sprintf(newPart, "%s-?\?-%s-%s-%s", partSplit.data[0], partSplit.data[2],
              partSplit.data[3], partSplit.data[4]);
      break;
    case 5:
      sprintf(newPart, "%s-?\?-%s-%s-%s-%s", partSplit.data[0],
              partSplit.data[2], partSplit.data[3], partSplit.data[4],
              partSplit.data[5]);
      break;
  }
  return newPart;
  printf("%s\n", newPart);

  Array_free(&partSplit, NULL, NULL, STRING);
}

void removeT(char* s) {
  int i = 0;
  int j = 0;
  while (s[i]) {
    if (s[i] != 'T') {
      s[j++] = s[i];
    }
    i++;
  }
  s[j] = '\0';
}
void removeDashesAndTs(char* s) {
  int i = 0;
  int j = 0;
  while (s[i]) {
    if (s[i] != 'T' && s[i] != '-') {
      s[j++] = s[i];
    }
    i++;
  }
  s[j] = '\0';
}

#endif  // !FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "function.h"

float doingMath(FloatArray fArrray) {
  float finalNum = fArrray.data[0];
  for (int i = 1; i < fArrray.size; i++) {
    if ((int)fArrray.data[i] == 1) {
      finalNum = finalNum + fArrray.data[i + 1];
    } else if ((int)fArrray.data[i] == 2) {
      finalNum = finalNum - fArrray.data[i + 1];
    } else if ((int)fArrray.data[i] == 3) {
      finalNum = finalNum * fArrray.data[i + 1];
    } else if ((int)fArrray.data[i] == 4) {
      finalNum = finalNum / fArrray.data[i + 1];
    } else if ((int)fArrray.data[i] == 5) {
      break;
    }
    i++;
  }
  return finalNum;
}

void clearScreen() {
  printf("\e[1;1H\e[2J");
  fflush(stdout);
}

int main() {
  clearScreen();

  FloatArray allNumbers;
  Array_new(NULL, NULL, &allNumbers, FLOAT);

  printf("Calculator app\n");
  for (;;) {
    char* buf = (char*)malloc(sizeof(char*));
    printf("Enter Number or press q to quit: ");
    if (scanf(" %s", buf)) {
      if (stringEquals(buf, "q") == 0) {
        float val = atof(buf);

        if ((int)val != 0) {
          FArray_append(&allNumbers, val);
          int val;
          while (true) {
            printf("Choose what operation you like to do: \n");
            printf(
                "1)Add \n2)Subtract \n3)Multiplication \n4)Divide \n5)Equals "
                "\nChoose a "
                "number or press q to quit:");
            char* chosenNum = (char*)malloc(sizeof(char*));
            if (scanf("%s", chosenNum)) {
              if (!stringEquals(chosenNum, "q")) {
                if (sscanf(chosenNum, "%d", &val) == 1) {
                  if (val <= 4 && val > 0) {
                    FArray_append(&allNumbers, val);
                    break;
                  } else if (val == 5) {
                    FArray_append(&allNumbers, val);
                    clearScreen();
                    val = 0;
                    printf("%.2f\n", doingMath(allNumbers));
                    printf("Calculator app\n");
                    break;
                  } else {
                    printf("Must pick an operation\n");
                  }
                } else {
                  printf("Must enter a num to choose operation\n");
                }
                free(chosenNum);
              } else {
                val = 5;
                break;
                free(chosenNum);
              }
            }
          }
          if (val == 5) {
            break;
          }
        } else {
          printf("Number cannot contain characters\n");
        }
        free(buf);
      } else {
        break;
        free(buf);
      }
    }
  }
  Array_free(NULL, NULL, &allNumbers, FLOAT);
  return 0;
}

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"

double doingMath(DoubleArray dArrray) {
  double finalNum = dArrray.data[0];
  for (int i = 1; i < dArrray.size; i++) {
    if ((int)dArrray.data[i] == 1) {
      finalNum = finalNum + dArrray.data[i + 1];
    } else if ((int)dArrray.data[i] == 2) {
      finalNum = finalNum - dArrray.data[i + 1];
    } else if ((int)dArrray.data[i] == 3) {
      finalNum = finalNum * dArrray.data[i + 1];
    } else if ((int)dArrray.data[i] == 4) {
      finalNum = finalNum / dArrray.data[i + 1];
    } else if ((int)dArrray.data[i] == 5) {
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

  DoubleArray allNumbers;
  Array_new(NULL, NULL, &allNumbers, DOUBLE);

  printf("Calculator app\n");
  printf("You Can Always press q to quit\n\n");
  int times = 0;
  for (;;) {
    char* buf = (char*)malloc(sizeof(char*));

    if (times == 0) {
      printf("Enter A Number: ");
    } else {
      printf("\nEnter Another Number: ");
    }

    if (scanf(" %s", buf) != EOF) {
      times++;
      if (stringEquals(buf, "q") == 0) {
        double val = atof(buf);
        if ((int)val != 0) {
          DArray_append(&allNumbers, val);
          int val;
          while (true) {
            printf("\nChoose what operation you like to do: \n\n");
            printf(
                "1)Add 2)Subtract 3)Multiplication 4)Divide 5)Equals "
                "\nChoose a "
                "number:");
            char* chosenNum = (char*)malloc(sizeof(char*));
            if (scanf("%s", chosenNum) != EOF) {
              if (!stringEquals(chosenNum, "q")) {
                if (sscanf(chosenNum, "%d", &val) == 1) {
                  if (val <= 4 && val > 0) {
                    DArray_append(&allNumbers, val);
                    break;
                  } else if (val == 5) {
                    DArray_append(&allNumbers, val);
                    clearScreen();
                    val = 0;
                    double newNum = doingMath(allNumbers);
                    printf(
                        "The answer to your inquiry is..............\n\n\n\n "
                        "              %.2f "
                        "\n\n\n\n",
                        newNum);

                    // Freeing array
                    Array_free(NULL, NULL, &allNumbers, DOUBLE);
                    allNumbers.size = 0;
                    allNumbers.heap_size = 0;
                    allNumbers.data = NULL;
                    Array_new(NULL, NULL, &allNumbers, DOUBLE);

                    times = 0;
                    printf("Calculator app\n");
                    printf("You Can Always press q to quit\n\n");
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
            } else {
              printf("\nExiting program (ctrl+d) was detected\n");
              break;
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
    } else {
      printf("\nExiting program (ctrl+d) was detected\n");
      break;
    }
  }

  Array_free(NULL, NULL, &allNumbers, DOUBLE);
  return 0;
}

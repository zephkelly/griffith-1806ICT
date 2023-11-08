#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool sum(char *commands, int *result) {
  char operators[] = "*/%";
  *result = 0;

  int num1;
  int num2;
  char operator;
  int consumed = 0;
  int localResult = 0;

  const char *current = commands;

  while (sscanf(current, "%d%c%d%n", &num1, &operator, &num2, &consumed) == 3) {
    if (strchr(operators, operator) == NULL) {
      return false;
    }
    
    if (operator == '/' && num2 == 0) {
      return false;
    }

    switch(operator) {
      case '*':
        localResult = num1 * num2;
        break;
      case '/':
        localResult = num1 / num2;
        break;
      case '%':
        localResult = num1 % num2;
        break;
    }

    *result += localResult;
    current += consumed;
  }
  
  return (current == commands) ? false : true;
}

int main()
{
  char *expressions[] = {"1*8 5/4", "6*8 2/0", "9%8 6*4 2/4", "1&3"};
  int result;
  int accumulatedTotal = 0;

  for (int i = 0; i < 4; i++) {
    if (sum(expressions[i], &result)) {
      printf("Result of %s is %d\n", expressions[i], result);
    } else {
      printf("%s Invalid Input\n", expressions[i]);
    }
  }

  return 0;
}
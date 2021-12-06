#include <stdio.h>


int length(char* str) {
  int len = 0;
  for(; str[len] != '\0'; len++);
  return len;
}

void reverse(char* str) {

  int len;
  for(len = 0; str[len] != '\0'; len++);

  for(int i = 0; i < len/2; i++) {
    char temp;
    temp = str[i];
    str[i] = str[len - 1 - i];
    str[len - 1 - i] = temp;
  }
}

int compare(char* str1, char* str2) {
  int str1Len, str2Len;
  for(str1Len = 0; str1[str1Len] != '\0'; str1Len++);
  for(str2Len = 0; str2[str2Len] != '\0'; str2Len++);

  if(str1Len != str2Len) {
    return 0;
  }

  for(int i = 0; i < str1Len; i++) {
    if(str1[i] != str2[i]) {
      return 0;
    }
  }

  return 1;
}

int isPalindrome(char* str) {
  int len = length(str);

  for(int i = 0; i < len/2; i++) {
    if(str[i] != str[len-1-i]) {
      return 0;
    }
  }
  return 1;
}

void substr(char* str, char* subs, int start, int len) {
  for(int i = 0; i < len; i++) {
    subs[i] = str[i+start];
  }
  subs[len] = '\0';
}


int main(void) {
  char str[1000], subs[1000];
  int start, len, operation;

  int allowed_to_continue = 1;
  do {
    printf("\n\nOperation List:\n");
    printf("\t1) *Length* \n");
    printf("\t2) *Reverse* \n");
    printf("\t3) *Compare* \n");
    printf("\t4) *Palindrome* \n");
    printf("\t5) *Substring* \n");
    printf("\t6) *Exit* \n");
    printf("Select Operation: ");

    scanf("%d", &operation);

    switch (operation)
    {
    case 1:
        printf("Enter String: ");
        scanf("%s", str);
        printf("Length: %d\n", length(str));
        break;
    case 2:
        printf("Enter String: ");
        scanf("%s", str);
        reverse(str);
        printf("Reverse of String: %s\n", str);
        break;
    case 3:
        printf("Enter First String: ");
        scanf("%s", str);
        printf("Enter Second String: ");
        scanf("%s", subs);
        int isSame = compare(str, subs);
        if(isSame) {
            printf("Strings are Same!\n");
        } else {
            printf("String are Not Same!\n");
        }
        break;
    case 4:
        printf("Enter String: ");
        scanf("%s", str);
        int isPal = isPalindrome(str);
        if(isPal) {
            printf("String is Palindrome!\n");
        } else {
            printf("String is Not Palindrome!\n");
        }
        break;
    case 5:
        printf("Enter String: ");
        scanf("%s", str);

        printf("Enter Start Index: ");
        scanf("%d", &start);
        printf("Enter Substring Length: ");
        scanf("%d", &len);

        substr(str, subs, start, len);
        printf("Substring: %s", subs);
        break;
    case 6:
        break;
    default:
        printf("Wrong Input!");
        break;
    }
    
  } while (operation != 6);
  return 0;
}
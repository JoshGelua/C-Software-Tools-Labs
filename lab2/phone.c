#include <stdio.h>
#include <stdlib.h>
int phone(){
  char phone[11];
  int num;
  scanf("%s", &phone[0]);
  scanf("%d", &num);
  if (num == -1){
    printf("%s\n", phone);
    return 0;
  }
  else if (num >= 0 && num < 10){
    printf("%c\n", phone[num]);
    return 0;
  }
  else{
    printf("ERROR");
    return 1;
  }
}
int main(int argc, char const *argv[]) {
  phone();
  return 0;
}

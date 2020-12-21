#include <stdio.h>
#include <string.h>
 
int main(void)
{
    char kotae[256];
     
    printf(u8"信号機の一番右は何色？ ");
    scanf("%s", kotae);
     
    if(!strcmp(kotae, "赤")){
        printf("正解！\n");
    }
    else{
        printf("ぶっぶー\n");
    }
     
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int game(){
  puts("In The Midst of your journey lies a beast to be defeated");
  puts("christmas gift for your hardwork!!!");
  
  
  char reward_regular[56]="a regular gift for you,pwnogatchi;goodbye or try again\n";
  char reward_pwner[56]="ppeeww,your flag is waiting at the end of your journey\n";
  char buffer[8];
  memset(buffer,0,8);
  puts("have you defeated the monstrous Beast(yes/no)");
    for(int i=0;i<=sizeof(buffer);i++){
    int ch=getchar();
    if(ch=='\n'){ break;}
    buffer[i]=(char)ch;
  }
  if(!strcmp("no",buffer)){
    printf(reward_regular);
  }
  else printf(reward_pwner);
  return 1;
}

void handler(){
  puts("Timeout");
  exit(1);
}

void init_proc(){

  setbuf(stdout,NULL);
  setbuf(stderr,NULL);

  signal(0xe,handler);
  alarm(0x3c);
}

void main(){
  
  init_proc();
  game();
  char buffer[0x80];
  memset(buffer,0,0x80);
  printf("Input :");
  close(1);
  read(0,buffer,0x80);
  printf(buffer);

  exit(0);
}
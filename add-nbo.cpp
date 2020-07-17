#include <stdio.h>
#include <iostream>
#include <stdint.h>


int main(int argc , char* argv[]){
    FILE *fd1;
    FILE *fd2;

    long fd1Size;
    long fd2Size;
    uint32_t* buffer1[50];
    uint32_t* buffer2[50];
    uint32_t val1;
    uint32_t val2;
    uint32_t val3;
    
    fd1 = fopen(argv[1],"rb") ;
    fd2 = fopen(argv[2],"rb");

    fseek(fd1,0,SEEK_END);
    fseek(fd2,0,SEEK_END);

    fd1Size = ftell(fd1);
    fd2Size = ftell(fd2);

    rewind(fd1);
    rewind(fd2);

    val1 = fread(buffer1,4,fd1Size,fd1);
    printf("val1 : %#x\n",val1);
    val2 = fread(buffer2,sizeof(int),fd2Size,fd2);
    printf("val2 : %#x\n",val2);
    val3 = val1 + val2;
    printf("%d(%#x) + %d(%#x) = %d(%#x)\n",val1,val1,val2,val2,val3,val3);

    fclose(fd2);
    fclose(fd1);
    
    return 0;
}

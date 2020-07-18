#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <stddef.h>


unsigned int my_ntohl(unsigned int n)
{
	unsigned int n1 = (n & 0xFF000000) >> 24;
	unsigned int n2 = (n & 0x00FF0000) >> 8;
	unsigned int n3 = (n & 0x0000FF00) << 8;
	unsigned int n4 = (n & 0x000000FF) << 24;
	
	return n4|n3|n2|n1;
}
unsigned int  write_0x(unsigned int buffer) {
	unsigned int network_buffer[] = { buffer };
	unsigned int* p = reinterpret_cast<unsigned int*>(network_buffer);
	unsigned int n = my_ntohl(*p); 
	//printf("32 bit number=0x%x\n", n);
    return n;
}
int main(int argc , char* argv[]){
    FILE *fd1;
    FILE *fd2;

    long fd1Size;
    long fd2Size;
    unsigned int buffer1[5] = {0,};
    unsigned int buffer2[5] = {0,};

    
    fd1 = fopen(argv[1],"rb") ;
    fd2 = fopen(argv[2],"rb");

    fseek(fd1,0,SEEK_END);
    fseek(fd2,0,SEEK_END);

    fd1Size = ftell(fd1);
    fd2Size = ftell(fd2);

    rewind(fd1);
    rewind(fd2);

    fread(buffer1,1,4,fd1);
    unsigned int a = write_0x(buffer1[0]);

    fread(buffer2,1,4,fd2);
    unsigned int b = write_0x(buffer2[0]);
    unsigned int c = a + b;
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n",a,a,b,b,c,c);
    fclose(fd2);
    fclose(fd1);
    
    return 0;
}
char *mem = (char*)0x0007FFFF;

int strlen(const char *str) {
    int  len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void strcpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}


void *memcpy(void *dest, const void *src, int n) 
{ 
    // Typecast src and dest addresses to (char *) 
    char *csrc = (char *)src; 
    char *cdest = (char *)dest; 
  
    // Copy contents of src[] to dest[] 
    for (int i=0; i<n; i++) 
        cdest[i] = csrc[i]; 
  
    return dest; 
}

char * mmalloc(int s);
void ffree(char * blk);
char * rrealloc(int s,char * blk);


char * mmalloc(int s){
    int i= 0;
    while(
        (char)*(mem+i) == 1 || // 0 means unallocated
        ( (s+5 <= (int)*(mem+i+1))  || // means that the size of current block is this big.
        ((int)*(mem+i+1) != 0)  //heap ender kinda.
        )
    ){
        i+= (int)*(mem+i+1);
    }
    mem[i]  = 1;
    *((int*)(mem+i+1)) = s+5;
    return mem+i+5;
}

void ffree(char * blk){
    *(blk-5) = 0;
    if(*(blk+(int)*(blk-1)) == 0){
        *((int*)(blk-1)) += *(blk+(int)*(blk-1))+5;
    }
}

char * rrealloc(int s,char * blk){
    char * np = mmalloc(s); // new pointer
    memcpy(np,blk,(int)*(blk-4));
    ffree(blk);
    return np;
}

char * isolate_args(char *s,int len ){
    char * ms = mmalloc(len);
    strcpy(ms,s);
    int i =0;
    
    while(ms[i] !=32 ){
        i++;
    }
    ms[i]  = 0;
    ms = ms+i+1;
    i=0;
    while(ms[i] !=32 ){
        i++;
    }
    ms[i]  = 0;
    i=0;
    
    return ms;
}
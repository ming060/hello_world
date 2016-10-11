/* Hello World program */

#include<stdio.h>
/*
void print_bits(unsigned int num)
{
    unsigned int size = sizeof(unsigned int);
    unsigned int maxPow = 1<<(size*8-1);
    int i = 0;
    for(;i<size*8;++i){
        // print last bit and shift left.
        printf("%u ",num&maxPow ? 1 : 0);
        num = num<<1;
    }
}
*/
void print_bits_reverse(unsigned long n)
{
    int i;
    unsigned long m;
    m = 0x8000000000000000;
    for(i = 0; i < 64; i++) {
        
    }
}

void print_bits(unsigned long n)
{
    while (n) {
        if (n & 1)
            printf("1");
        else
            printf("0");

        n >>= 1;
    }
    printf("\n");
}

void get_ports(unsigned long n)
{
    int octet_count, port_number;

    for(octet_count = 1; octet_count < 9;octet_count++)
    {
        for(port_number = octet_count * 8; port_number > (octet_count -1) * 8; port_number--) {
            if(n & 1)
                printf("%d\n", port_number);
            n >>= 1;
        }
    }
}

static int get_shift_bits(int user_port)
{
    return 8 * (user_port / 8) + (8 - (user_port % 8));
}

#define IS_PORTS_OVERLAP(ports_1, ports_2)  (int *)(ports_1 & ports_2)
main()
{



    unsigned long a, b, c, d;

    a = 0x80;
    b = 0x40;

    a |= b;
    c = a ^ b;

    printf("c: %lx, b: %lx\n", c, b);

    //a = 0xFFC0000000000000;

    a = 0x1;
    a <<= get_shift_bits(9);
    printf("%lx\n", a);
    get_ports(a);

    b = 0x1;
    b <<= get_shift_bits(8);

    a |= b;

    printf("%lx\n", a);
    get_ports(a);


    int i;


    //print_bits(a);

/*
    print_bits(n);
    print_bits(0x1234567890ABCDEF);

    unsigned long i = 0xFEDCBA0987654321;
    printf("%lx\n", i);
    printf("%#010x\n", i);
    printf("0x%08x\n", i);  // gives 0x00000007
    printf("%#08x\n", i);   // gives 0x000007
*/
    //print_bits(c);

    //long b = 0xFFFFFFFFFFFFFF;
    //a = a >> 1;

    //printf("size: %d\n", sizeof(unsigned long));
    //printf("%x\n",a<<3);
    //printf("%u\n",a);
/*
    char name[10];
    char scan[10];
    int port = 0;
    int ret = 0;
    ret = sscanf("br40", "swp%d", &port);
    printf("ret: %d, port: %d", ret, port);
*/
}

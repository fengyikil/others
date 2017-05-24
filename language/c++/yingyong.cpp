#include<stdio.h>

class Man
{
public:
    Man(){data =new int(0);}
    ~Man(){delete data;}
    int* data;
};
Man get(Man &m)
{
    return m;
}

int main(int argc, char *argv[])
{
    
    Man m,n;
    *m.data = 5;
    printf("m.data is %d\n",*m.data);
    n = get(m);
    printf("m.data is %d\n",*m.data);
    printf("n.data is %d\n",*n.data);
    
    while(1);  
}
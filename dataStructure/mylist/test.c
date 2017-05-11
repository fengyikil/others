#include "mylist.h"
#include <stdio.h>
#include <malloc.h>
struct mynode
{
struct pn_node node;
int test;
};
int main(int argc, char *argv[])
{
    int i;
    struct mynode* md;
     struct pn_node *pd,*n,*pos;
    struct pn_node eq;
    init_node_head(&eq);
    for(int i =0 ;i<10;i++)
    {
       md = (struct mynode*)malloc(sizeof(struct mynode));
        md->test = i;
        list_add_head(&eq,&md->node);
    }
//    list_for_each_safe(pos, n, &eq)
//    {
//                md =  list_entry(pos, struct mynode,node);
//                printf("md->test is %d\n",md->test);
//    }
    for(int i = 0 ;i<5;i++)
    {
        pd = list_del_tail(&eq);
        md =  list_entry(pd, struct mynode,node);
        printf("md->test is %d\n",md->test);
    }

    for(int i =10;i<15;i++)
    {
       md = (struct mynode*)malloc(sizeof(struct mynode));
        md->test = i;
        list_add_head(&eq,&md->node);
    }

    for(int i = 0 ;i<10;i++)
    {
        pd = list_del_tail(&eq);
        md =  list_entry(pd, struct mynode,node);
        printf("md->test is %d\n",md->test);
    }
    printf("Hello World!\n");
    return 0;
}

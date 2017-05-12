#ifndef _MY_LIST
#define _MY_LIST

#define NULL 0
//取父地址宏
#define container_of(ptr, type, member) ({                      \
         const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
          (type *)( (char *)__mptr - offsetof(type,member) );})
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
//正向遍历宏
#define list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
        pos = n, n = pos->next)

struct pn_node
{
    struct pn_node *prev,*next;
};
inline void  init_node_head(struct pn_node* head)
{
    head->next = head;
    head->prev = head;
}
//通用插入
inline void  __list_add(struct pn_node *nd,struct pn_node *prev,struct pn_node *next)
{
    next->prev = nd;
    nd->next = next;
    nd->prev = prev;
    prev->next = nd;
}
//插入到表头
inline void list_add_head(struct pn_node*head,struct pn_node* nd)
{
    __list_add(nd,head,head->next);
}
//插入到表尾
inline void list_add_tail(struct pn_node*head,struct pn_node* nd)
{
    __list_add(nd,head->prev,head);
}
//通用删除
inline void __list_del(struct pn_node*prev,struct pn_node* next)
{
    next->prev = prev;
    prev->next = next;
}
//封装通用删除 这样做的好处？
inline void  list_del(struct pn_node *nd)
{
    __list_del(nd->prev,nd->next);
}
//从表头删除并返回
inline struct pn_node* list_del_head(struct pn_node *head)
{
    struct pn_node* tmp;

    if(head->next!=head)
     {
         tmp = head->next;
         list_del(tmp);
    }
    else
        tmp = NULL;
    return tmp;
}
//从表尾巴删除并返回
inline struct pn_node* list_del_tail(struct pn_node* head)
{
    struct pn_node* tmp;
    if(head->prev!=head)
    {
        tmp = head->prev;
        list_del(tmp);
    }
    else
        tmp = NULL;
    return tmp;
}

#endif

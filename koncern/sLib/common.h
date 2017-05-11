extern int init_cansocket(struct can_filter* filter,int f_num);
extern void bit_set(unsigned short num,unsigned short* alarm);
extern void bit_clear(unsigned short num,unsigned short* alarm);
extern short bit_get(unsigned short* alarm);

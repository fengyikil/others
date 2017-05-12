
void bit_set(unsigned short num,unsigned short* alarm)
{
	unsigned char i;	
	unsigned char j;
	unsigned short zz;

	zz = 1;
	i= num/16;
	j= num%16;
	zz <<= j;
	alarm[i]= alarm[i] | zz;
}
void bit_clear(unsigned short num,unsigned short* alarm)
{
	unsigned char i;	
	unsigned char j;
	unsigned short zz;

	zz = 1;
	i= num/16;
	j= num%16;
	zz <<= j;
	zz = ~zz;
	alarm[i] = alarm[i] & zz;
}
short bit_get(unsigned short* alarm)
{
	unsigned char i=0;	
	 char j=-1;
	for(i=0;i<16;i++)
	{
		if(alarm[i])
		{
			while(alarm[i])
			{
				alarm[i]>>=1;
				j++;
			}
			printf("j is %d\n",j);
			return (i*16+j);
		}
	}
	return -1;
}
	

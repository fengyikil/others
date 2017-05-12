#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>

struct timeval timeout;
void main()
{
 modbus_t *ctx;
 int rc;
 int mode;
 int erro;
static unsigned char data[22];
static unsigned short sdata[22];
static unsigned short srdata[22];

 ctx = modbus_new_rtu("/dev/ttyS0",115200,'N',8,1);
 modbus_set_debug(ctx,1);
 modbus_set_slave(ctx,1);
 if(modbus_connect(ctx) == -1)
 {
 	fprintf(stderr,"Connection failed:%s\n",modbus_strerror(errno));
	modbus_free(ctx);
	return -1;
 }
 else
	printf("connection ok\n");	 
 /*
 rc = modbus_rtu_set_serial_mode(ctx,MODBUS_RTU_RS232);
 if(rc == -1)
 {
 	printf("%d\n",errno);
 	fprintf(stderr,"set mode failed:%s\n",modbus_strerror(errno));
 }

mode = modbus_rtu_get_serial_mode(ctx);
printf("mode is %d\n",mode);
*/
timeout.tv_sec = 1;
//timeout.tv_usec = 1000*200;
modbus_set_response_timeout(ctx,&timeout); 
 modbus_get_response_timeout(ctx,&timeout);
 printf("erro is %d\n",erro);
 printf("sec is %d\n",timeout.tv_sec);
 printf("usec is %d\n",timeout.tv_usec);


rc == -1;
int i = 0;
while(1)
{
 	//	modbus_set_slave(ctx,i);

/*
	//test  modbus_read_bits
		rc = modbus_read_bits(ctx,0x00,16,data);
		printf("rc is %d\n",rc);
		for(i=0;i<22;i++)
		{
		printf("data[%d] is %d\n",i+1,data[i]);
		}
	//test	modbus_read_input_bits
		modbus_read_input_bits(ctx,0x00,20,data);
		printf("rc is %d\n",rc);
		for(i=0;i<22;i++)
		{
		printf("data[%d] is %d\n",i+1,data[i]);
		}
	//test  modbus_read_register
		modbus_read_registers(ctx,0x00,10,sdata);	
		for(i=0;i<10;i++)
		{
		printf("sdata[%d] is %d\n",i+1,sdata[i]);
		}

	//test	modbus_read_input_registers
		modbus_read_input_registers(ctx,0x00,10,sdata);
		for(i=0;i<10;i++)
		{
		printf("sdata[%d] is %d\n",i+1,sdata[i]);
		}
	//test	modbus_report_slave_id
		modbus_report_slave_id(ctx,data);
		for(i=0;i<10;i++)
		{
		printf("sdata[%d] is %d\n",i+1,data[i]);
		}
	//test  modbus_write_bit
		rc = modbus_write_bit(ctx,0x13,1);
		printf("rc is %d\n",rc);
	//test 	modbus_write_register
	 	modbus_write_register(ctx,0x00,200);
	//test	modbus_write_bits
		data[0] = 1;
		data[1] = 1;
		data[3] = 0;
		data[6] = 1;
		modbus_write_bits(ctx,0x00,8,data);
	//test modbus_write_registers
		sdata[0]=87;
		sdata[1]=98;
	        sdata[8]=987; 	
	 modbus_write_registers(ctx,0x00,10,sdata);
	//test	modbus_write_and_read_registers
		sdata[0] = 89;
		modbus_write_and_read_registers(ctx,0x00,3,sdata,0x08,3,srdata);
		for(i=0;i<5;i++)
		{
			printf("srdata[%d] is %d\n",i,srdata[i]);
		}
	//test	modbus_send_raw_request
		data[0]=0x01;
		data[1]=0x04;
		data[3]=0x05;
		data[4]=0x06;
		modbus_send_raw_request(ctx,data,5);
	//test	modbus_receive_confirmation
		modbus_receive_confirmation(ctx,data);
		
		for(i=0;i<10;i++)
		{
			printf("data[%d] is %d\n",i,data[i]);
		}
		*/
	//test	modbus_reply_exception
	for(i=1;i<12;i++)
	{
		modbus_reply_exception(ctx,data,i);

		printf("%d data[0] is %d\n",i,data[0]);
		sleep(3);
	}
		sleep(5);
}
modbus_close(ctx);
}





#include <stdio.h>
#include <fcntl.h>   	 /* File Control Definitions           */
#include <termios.h>	 /* POSIX Terminal Control Definitions */
#include <unistd.h> 	 /* UNIX Standard Definitions 	       */ 
#include <errno.h>   	 /* ERROR Number Definitions           */
#include <sys/ioctl.h>   /* ioctl()                            */     
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


struct timespec ts;


void sleep_ms(int milliseconds)
{
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}


void sleep_us(int microseconds)
{
    ts.tv_sec = microseconds / 1000000;
    ts.tv_nsec = (microseconds % 1000000) * 1000;
    nanosleep(&ts, NULL);
}


void sleep_ns(int long nanoseconds)
{
  ts.tv_sec = nanoseconds / 1000000;
  ts.tv_nsec = nanoseconds;
  nanosleep(&ts, NULL);
}


void main(void)
{
	int fd;	/*File Descriptor*/


	/*------------------ Opening the Serial port ------------------*/
	/* Change /dev/ttyUSB0 to the one corresponding to your system */
	/* O_RDWR Read/Write access to serial port           */	
	/* O_NOCTTY - No terminal will control the process   */
	/* Blocking Mode  */
	fd = open("/dev/ttyUSB0",O_RDWR | O_NOCTTY );	 

			   						                       
	/* Error Checking */									
	if(fd == -1) {						
    		printf("\n    Error! in Opening ttyUSB0  ");
    	}
    	else {
    		//printf("\n    ttyUSB0 Opened Successfully \n");
	}
		

	/*--------- Controlling the RTS and DTR pins of CP2102 to generate BSL invoke sequence --------*/
	int RTS_flag, DTR_flag;

	RTS_flag = TIOCM_RTS; /* Modem Constant for RTS pin */
	DTR_flag = TIOCM_DTR; /* Modem Constant for DTR pin */
	
	/* Initially making RTS and DTR line HIGH as whenever the /dev/ttyUSB0 port is 
	opened, DTR and RTS becomes LOW by default */	
	ioctl(fd, TIOCMBIC, &RTS_flag); /* TIOCMBIC - Clear the bit corrosponding to  RTS_flag...But actually it does the opposite */
	ioctl(fd, TIOCMBIC, &DTR_flag); /* TIOCMBIS - Set the bit corrosponding to  DTR_flag...But actually it does the opposite */
	sleep_ms(3000);

	/* Genrating the BSL invoke sequence as mentioned in SLAU550(Figure 2, Page No.- 7) */
	
	//making the TEST line LOW before sending the invoke sequence
	ioctl(fd, TIOCMBIS, &RTS_flag); 
	ioctl(fd, TIOCMBIC, &DTR_flag);
	sleep_ms(3000);

	ioctl(fd, TIOCMBIS, &DTR_flag);
	sleep_us(50);
	ioctl(fd, TIOCMBIC, &RTS_flag);
	sleep_us(50);
	ioctl(fd, TIOCMBIS, &RTS_flag);
	sleep_us(50);
	ioctl(fd, TIOCMBIC, &RTS_flag);
	sleep_us(50);
	ioctl(fd, TIOCMBIC, &DTR_flag);
	sleep_us(50);
	ioctl(fd, TIOCMBIS, &RTS_flag);

	/* 
	// old sequence -- maybe wrong

	ioctl(fd,TIOCMBIS,&RTS_flag);
	sleep_ms(10);
	ioctl(fd,TIOCMBIC,&RTS_flag); 
										
	sleep_ms(100);

	ioctl(fd,TIOCMBIS,&RTS_flag);
	sleep_ms(10);
	ioctl(fd,TIOCMBIS,&DTR_flag); 
	sleep_ms(10);
	ioctl(fd,TIOCMBIC,&RTS_flag);
	*/

	sleep_ms(2000);
		
	/* Close the Opened Serial Port */
	close(fd);
}

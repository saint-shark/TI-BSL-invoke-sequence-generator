# TI-BSL-invoke-sequence-generator

--> This application generates the BSL invoke sequence for MSP430 FRAM devices.

--> As TI's BSL scripter application doesn't generate the invoke sequence so 
	this application can be used before running it.

--> It has been tested with the following development environment:
	$ Compiler/IDE  : GCC 8.2.1 20180831 
	$ OS : Manjaro 17.1.12
	$ USB to UART Converter : Siliab's CP2102 

--> Running the executable                                                                             
	1) Compile the  BSL_invoke.c using gcc on the terminal                                                               
		
		gcc -o BSL_invoke BSL_invoke.c                                                                       
	                                                                                                    
    2) You have to be root to run this executable as Linux won't allow you to access the serial port from user space. So use
	   "sudo" command to execute the compiled binary as super user.                                   
                                                                                                           
    	sudo ./BSL_invoke     
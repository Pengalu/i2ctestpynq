// The goal of this program is to pulse the clock pin and properly send/receive I2C data as a master

#include <stdio.h> 
#include <libpynq.h>
int main(void) {
    pynq_init();
    printf("Hello, PYNQ World!\n");
    printf("Initializing the MASTER PYNQ");
    
    

    switchbox_set_pin(IO_PMODA3, SWB_IIC0_SCL); // Set SCL pin for IIC function to Arduino Pin A3
    switchbox_set_pin(IO_PMODA4, SWB_IIC0_SDA); // Set SDA pin to Arduino Pin A4
    // The PMOD pins have 2k2 pull ups built in which is required for the 
    iic_init(IIC0); // Initialize the IIC0 interface (with the pins we set)
    
    
    uint8_t i; // buffer variable 
    uint32_t slave_address = 0x70; // an address must be given for each connected PYNQ board. 
    for (int reg=0; reg <32; reg++) { // IIC works by having x # of "registers" / slave which the master and slave can read/write
        if (iic_read_register(IIC0, slave_address, reg, (uint8_t *)&i, 4)) { // Read 4 bytes from SLAVE board for each register, and check that 4 bytes have been succesfully recieved in tenable language and format.
            // (uint8_t *)&i is a pointer to the buffer variable i, which is where the data read from the slave will be stored. The 4 indicates that we want to read 4 bytes of data from the slave.
            printf("register[%d]=error\n",reg); // If iic_read_register returns 1 (true) it is an error
        } else {
            printf("register[%d]=%d\n",reg,i); // If iic_read_register returns 0 (false) it is a success and the value of the register is printed to the console
            // The i variable is used here as a buffer that iic_read_register outputs to (the value of i is equal to the last register value)
        }
    }
        
    while(1){

        int n;
        printf("Input an integer register number to read from slave");
        scanf("%d", &n);
        printf("Reading contents of %d \n", n);
        uint8_t buffer; // buffer variable 
        iic_read_register(IIC0, slave_address, n, (uint8_t *)&buffer, 4); // Read 4 bytes from the register n

        printf("%d\n", buffer);


    }


    // Cleanup and exit after the MASTER has finished reading from the SLAVE units



    leds_destroy(); // Cleanup
    pynq_destroy();
    return EXIT_SUCCESS;

    
}
#include <stdio.h>
#include <libpynq.h>
void replaceElement(float values[], int i, float v){
    values[i] = v;}

int idx, ri, v, ME, rv;

int main(void) {
    const uint32_t my_slave_address = 0x70;
        // This array contains 32 registers that can be written & read by the master board. The slave can also modify the values of the registers.
        uint32_t my_register_map[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
                                        17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
        const uint32_t my_register_map_length = sizeof(my_register_map) / sizeof(uint32_t);
            
    pynq_init();
        iic_init(IIC0);
        iic_reset(IIC0);
        iic_set_slave_mode(IIC0, my_slave_address, &(my_register_map[0]), my_register_map_length);
    
    while (1){ // Slave mode handler needs to run constantly until program is annihilated 
        iic_slave_mode_handler(IIC0); // This high level function handles sendind data on the SDA lines
        printf("Replace (index): ");
            scanf("%d", &ri);
            if (ri >= 0 && ri <32){
                printf("Replace (value): ");
                scanf(" %d", &rv);
                replaceElement(my_register_map, ri, rv);
                break;
            }
            else {
                printf("Error: index exceeds bound of array.\n");
            }
        sleep_msec(10); // Execute slave mode handler literally constantly 
    }
    iic_destroy(IIC0);
    pynq_destroy();
    return EXIT_SUCCESS;
}
#include "pico/stdlib.h"
#include <stdio.h>

#define HIGH 1
#define LOW 0
#define LED_GREEN 25
#define FREQUENCY 25
#define HIGH_PIN 23
#define TX_PIN 14
#define TX_CLOCK_PIN 15
#define TX_RATE 10

int main(){

    stdio_init_all();
    gpio_init(LED_GREEN);
    gpio_init(HIGH_PIN);
    gpio_init(TX_PIN);
    gpio_init(TX_CLOCK_PIN);

    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(HIGH_PIN, GPIO_OUT);
    gpio_set_dir(TX_PIN, GPIO_OUT);
    gpio_set_dir(TX_CLOCK_PIN, GPIO_OUT);
    gpio_put(TX_CLOCK_PIN, LOW);
    gpio_put(HIGH_PIN, HIGH);
    gpio_put(TX_CLOCK_PIN, HIGH);

/*--------------------------------------------*/
    const char messeage[] = "Hello, World!";

    while(1){ 
        sleep_ms((1000 / TX_RATE) / 2);
        gpio_put(TX_CLOCK_PIN, LOW);
        for(char current_byte : messeage){
            
            char tx_byte = current_byte;
            for(int bit_idx = 0; bit_idx < 8; bit_idx++){
                
                bool tx_bit = tx_byte & (0x80 >> bit_idx);
                gpio_put(TX_PIN, tx_bit);
                gpio_put(LED_GREEN, tx_bit);

                sleep_ms((1000 / TX_RATE) / 2);
                gpio_put(TX_CLOCK_PIN, HIGH);
                sleep_ms((1000 / TX_RATE) / 2);
                gpio_put(TX_CLOCK_PIN, LOW);
            }
        }
        printf("Data Transfer Complete.\n");
        gpio_put(LED_GREEN, HIGH);
        return 0;
    }
}

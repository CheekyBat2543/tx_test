#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

#define HIGH 1
#define LOW 0
#define LED_GREEN 25
#define FREQUENCY 25
#define HIGH_PIN 23
#define TX_PIN 14
#define TX_CLOCK_PIN 15
#define TX_RATE 25

class tx { // class for handling data transfer
public:
    tx(const uint8_t txpin, const uint8_t txclock){ // class constructor
        tx_pin = txpin;
        tx_clock = txclock;
        gpio_init(tx_pin);
        gpio_init(tx_clock);
        gpio_init(LED_GREEN);
        gpio_set_dir(tx_pin, GPIO_OUT);
        gpio_set_dir(tx_clock, GPIO_OUT);
        gpio_set_dir(LED_GREEN, GPIO_OUT);
        gpio_put(tx_clock, LOW);
    }
    bool transfer(const char * data){
        uint16_t data_size = strlen(data)+1;
        for(int16_t i = 0; i < data_size; i++){
            char current_byte = data[i];
            char tx_byte = current_byte;
            for(int bit_idx = 0; bit_idx < 8; bit_idx++){
                 
                bool tx_bit = tx_byte & (0x80 >> bit_idx);
                printf("%u", tx_bit);
                gpio_put(tx_pin, tx_bit);
                gpio_put(LED_GREEN, tx_bit);
                sleep_ms((1000 / TX_RATE) / 2);

                gpio_put(tx_clock, HIGH);
                sleep_ms((1000 / TX_RATE) / 2);
                gpio_put(tx_clock, LOW);
            }
            printf("\n");
        }
        return true;
    }
   ~tx(void){
        printf("Class Destroyed.\n");
   }
private:
    uint8_t tx_pin;
    uint8_t tx_clock;
    char * data;
};

int main(){

    stdio_init_all();
    tx sender(TX_PIN, TX_CLOCK_PIN);
    char messeage[] = "Hello, World!";
    bool tx_state = false;
    while(1){
        sleep_ms(3000);
        while(!tx_state){
            tx_state = sender.transfer(messeage);
        }
        printf("Messeage sent succesfully!\n");
        return 0;
    }
}

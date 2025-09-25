#include "main.h"

void sync_loop(void);
void main_loop(void);
void execute(int executable);
void toggle(void);
void start_sync(void);
void sync_transmitter(void);   
int readBetter();
void sync_find(void);
void transmit(int signal);
void transmit_message(int signal);
int receieve(void);
void writeBetter(int output);
void send(int singal);
void sync_receiver(void);



void app_main(void)
{
    gpio_config(&io_led);
    gpio_config(&io_button);
    gpio_config(&io_led_2);
    gpio_config(&io_button_2);
    gpio_config(&io_input);
    gpio_config(&io_output);
    esp_task_wdt_init(&twdt_config); // only init in main thread

    esp_task_wdt_add(NULL);


    sync_loop();
    gpio_set_level(LED_PIN_2, LOW);
    gpio_set_level(LED_PIN_1, LOW);

    // main_loop();
}

void sync_loop(void){
    while (1) {
        int button1 = gpio_get_level(BUTTON_PIN_1);
        int button2 = gpio_get_level(BUTTON_PIN_2);

        if(button1 == HIGH){
            gpio_set_level(LED_PIN_2, HIGH);
            sync_transmitter();
            return;
        }

        if(button2 == HIGH){
            sync_receiver();
            return;
        }

    }
}

void main_loop(void) {
    while(1) {
        int command = readBetter();
        if(command == TRANSMISSIONSIG){
            int executable = receieve();
            execute(executable);
        }
        if(gpio_get_level(BUTTON_PIN_1) == HIGH){
            transmit(TRANSMISSIONSIG);
            transmit_message(100);
        }
    }
}

void execute(int executable) {
    switch (executable) {
        case 100:
            toggle();
            break;
    }
}

void toggle(){
    int led_state = gpio_get_level(LED_PIN_2);
    if(led_state == HIGH) {
        writeBetter(LOW);
    } else {
        writeBetter(HIGH);
    }
}

void start_sync(void){
    writeBetter(HIGH);
    int inputState;
    do {
        inputState = gpio_get_level(SIGNAL_INPUT_1);
    } while (inputState == LOW);

    //we've read a signal, time to turn off
    writeBetter(LOW);

    while(inputState == HIGH) {
        //pause while they also turn off
        inputState = gpio_get_level(SIGNAL_INPUT_1);
    }
}

void sync_transmitter(void){
    start_sync();
    do {
        transmit(TRANSMISSIONSIG);
        gpio_set_level(LED_PIN_2, LOW);
    } while(gpio_get_level(SIGNAL_INPUT_1) == LOW);
}

int readBetter() {
    int read = 0;
    int read_bits = 8;
    while(read_bits > 0) {
        read_bits -= 1;
        int small_read = gpio_get_level(SIGNAL_INPUT_1);
        read += small_read << read_bits;
        sleep(CLOCKTIME);
    }
    return read;
}

void sync_find(void) {
    // syncs such that terminates just after TRANSMISSIONSIG is read
    //wait for one high and low to beging searching(mini sync)
    
    while(gpio_get_level(SIGNAL_INPUT_1) == HIGH){

    }
    while(gpio_get_level(SIGNAL_INPUT_1) == LOW){

    }

    int reading;
    reading = readBetter();
    while(reading != TRANSMISSIONSIG) {
        //offset by 1 cycle, this can be made smarter later
        sleep(CLOCKTIME);
        reading = readBetter();
    }

}

void transmit(int signal) {
    int send_ints = 8;
    while(send_ints > 0) {
        send(signal & 1);
        signal >>= 1;
        send_ints -= 1;
    }
}

void transmit_message(int signal){
    while(gpio_get_level(SIGNAL_INPUT_1) == LOW) {
        transmit(TRANSMISSIONSIG);
    }
    while(signal > 0){
        transmit(signal);
        signal >>= 8;
    }
    transmit(TRANSMISSIONSIG);
}

int receieve(void){

    int start = readBetter();
    if (start != TRANSMISSIONSIG) {
        sync_find();
    }
    //tell them we're ready
    writeBetter(HIGH);

    int message = 0;
    int message_length = 0;
    int current;
    do {
        current = readBetter();
        if(current == TRANSMISSIONSIG && message_length == 0){
            current = 0;
        }
        message += current << 8 * message_length;
        message_length += 1;

    } while(current != TRANSMISSIONSIG);
    return message;
}

void writeBetter(int output){
    gpio_set_level(SIGNAL_OUTPUT_1, output);
    gpio_set_level(LED_PIN_1, output);
}

void send(int singal) {
    writeBetter(singal);
    sleep(CLOCKTIME);
}

void sync_receiver(void){
    start_sync();
    sync_find();
    writeBetter(HIGH);
    readBetter(); //read and discard extra TRANSMISSIONSIG
    writeBetter(LOW); 
}


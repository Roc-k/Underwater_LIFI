#include "main.h"

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

    int lastButtonState = LOW;
    sync_loop();
    main_loop();
}

void sync_loop(void){
    while (1) {
        int button1 = gpio_get_level(BUTTON_PIN_1);
        int button2 = gpio_get_level(BUTTON_PIN_2);

        if(button1 == HIGH){
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
        int command = read();
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
        write(LOW);
    } else {
        write(HIGH);
    }
}

void start_sync(void){
    write(HIGH);
    int inputState;
    do {
        inputState = gpio_get_level(SIGNAL_INPUT_1);
    } while (inputState == LOW);

    //we've read a signal, time to turn off
    write(LOW);

    while(inputState == HIGH) {
        //pause while they also turn off
    }
}

void sync_transmitter(void){
    start_sync();
    do {
        transmit(TRANSMISSIONSIG);
    } while(gpio_get_level(SIGNAL_INPUT_1) == LOW);
}

int read(void) {
    int read = 0;
    int read_bits = 8;
    while(read_bits > 0) {
        read_bits -= 1;
        int small_read = gpio_get_level(SIGNAL_INPUT_1);
        read += small_read << read_bits;
        sleep(CLOCKTIME);
    }

}

void sync_find(void) {
    // syncs such that terminates just after TRANSMISSIONSIG is read
    int reading;
    //wait for one high and low to beging searching(mini sync)
    
    while(gpio_get_level(SIGNAL_INPUT_1) == HIGH){

    }
    while(gpio_get_level(SIGNAL_INPUT_1) == LOW){

    }

    int reading;
    reading = read();
    while(reading != TRANSMISSIONSIG) {
        //offset by 1 cycle, this can be made smarter later
        sleep(CLOCKTIME);
        reading = read();
    }

}

void transmit(int signal) {
    int send_ints = 8;
    while(send_ints > 0) {
        send(signal & 1);
        signal >> 1;
        send_ints -= 1;
    }
}

void transmit_message(int signal){
    while(gpio_get_level(SIGNAL_INPUT_1) == LOW) {
        transmit(TRANSMISSIONSIG);
    }
    while(signal > 0){
        transmit(signal);
        signal >> 8;
    }
    transmit(TRANSMISSIONSIG);
}

int receieve(){

    int start = read();
    if (start != TRANSMISSIONSIG) {
        sync_find();
    }
    //tell them we're ready
    write(HIGH);

    int message = 0;
    int message_length = 0;
    int current;
    do {
        current = read();
        if(current == TRANSMISSIONSIG && message_length == 0){
            current = 0;
        }
        message += current << 8 * message_length;
        message_length += 1;

    } while(current != TRANSMISSIONSIG);

}

void write(int output){
    digitalWrite(SIGNAL_OUTPUT_1, output);
    digitalWrite(LED_PIN_1, output);
}

void send(int singal) {
    write(signal);
    sleep(CLOCKTIME);
}

void sync_receiver(void){
    start_sync();
    sync_find();
    write(HIGH);
    sleep(CLOCKTIME * 2);
    write(LOW);
}


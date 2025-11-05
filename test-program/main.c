#define uart_base_address (char*)(0x1000000000)

void main() {
    *(uart_base_address) = 'H';
    *(uart_base_address) = 'e';
    *(uart_base_address) = 'l';
    *(uart_base_address) = 'l';
    *(uart_base_address) = 'o';
    *(uart_base_address) = ' ';
    *(uart_base_address) = 'w';
    *(uart_base_address) = 'o';
    *(uart_base_address) = 'r';
    *(uart_base_address) = 'l';
    *(uart_base_address) = 'd';
    *(uart_base_address) = '!';
    *(uart_base_address) = '\n';

    while (1) {
        asm volatile ("wfi");
    }
}
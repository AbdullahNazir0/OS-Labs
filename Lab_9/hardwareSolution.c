#include <stdio.h>

int main()
{
    printf("Hello!, This program is going to clear carry flag.\n");
    asm("clc;");
    printf("Carry flag cleared!\n");
    printf("This program is attempting to disable interrupts using CLI (Clear Interrupt Flag) instruction.\n");
    printf("If you trapped.\n\n\n");
    asm("cli;");
    printf("\nInterrupts disbled!!!");
    return 0;
}
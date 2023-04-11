#include <avr/io.h>
#include <avr/interrupt.h>

// Define global variables for LED and switch
volatile uint8_t led_pin = 5;    // Pin number for LED (Assuming it is connected to Pin 5)
volatile uint8_t switch_pin = 2; // Pin number for Switch (Assuming it is connected to Pin 2)

// Initialize the ports for the LED and switch
void init_ports(void) {
  DDRD = (1 << led_pin);  // Set the LED pin as output
  PORTD = (1 << switch_pin);  // Set the Switch pin as input with pull-up resistor
}

// Enable the interrupt for the switch
void enable_switch_interrupt(void) {
  PCICR |= (1 << PCIE0);  // Enable Pin Change Interrupt for PCINT[7:0]
  PCMSK0 |= (1 << switch_pin);  // Enable the Pin Change Interrupt for the Switch Pin
  sei();  // Enable global interrupts
}

// Interrupt Service Routine (ISR) for the switch
ISR(PCINT0_vect) {
  if (!(PIND & (1 << switch_pin))) {  // If switch is pressed (low logic level)
    PORTD |= (1 << led_pin);  // Turn on the LED
  }
}

// Main function
int main(void) {
  init_ports();  // Initialize the ports
  enable_switch_interrupt();  // Enable the interrupt for the switch

  while(1) {
    // Do nothing here
  }

  return 0;
}

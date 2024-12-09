#include "stm32f10x.h"
#include <stdlib.h>
#include <time.h>

void SysTick_Handler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI15_10_IRQHandler(void); //EXTI15_10 for PB10
void delay_ms(uint32_t ms);
void init_LEDs(void);
void init_buttons(void);
void init_SysTick(void);
void init_EXTI(void);
uint8_t debounce_button(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

static volatile uint32_t msTicks = 0;
static volatile uint8_t buttonPressed = 0;
static volatile uint8_t currentLED = 0;

int main(void) {
    SystemInit();            // Initialize system
    init_LEDs();             // Initialize LEDs
    init_buttons();          // Initialize buttons
    init_SysTick();          // Initialize SysTick Timer
    init_EXTI();             // Initialize External Interrupts

    // Seed the random number generator
    srand(1294890499);

    while (1) {
        // Select a random LED to light up
        currentLED = rand() % 3;  // 0, 1, or 2

        // Turn off all LEDs first to avoid conflicts
        GPIOA->BSRR = GPIO_BSRR_BR0 | GPIO_BSRR_BR5 | GPIO_BSRR_BR6;
        
        // Light up the selected LED
        if (currentLED == 0) {
            GPIOA->BSRR = GPIO_BSRR_BS0;
        } else if (currentLED == 1) {
            GPIOA->BSRR = GPIO_BSRR_BS5;
        } else if (currentLED == 2) {
            GPIOA->BSRR = GPIO_BSRR_BS6;
        }
        buttonPressed = 0;

        for (int i = 0; i < 3; ++i) {
            delay_ms(1000); // Wait for 1 second

            // Check for button press with debounce
            if ((currentLED == 0 && debounce_button(GPIOB, 0x0001)) || 
                (currentLED == 1 && debounce_button(GPIOB, 0x0002)) || 
                (currentLED == 2 && debounce_button(GPIOB, 0x0400))) { // Update to PB10
                buttonPressed = 1;
                break;
            }
        }
				 // Turn off the selected LED
        if (currentLED == 0) {
            GPIOA->BSRR = GPIO_BSRR_BR0; // Reset PA0
        } else if (currentLED == 1) {
            GPIOA->BSRR = GPIO_BSRR_BR5; // Reset PA5
        } else if (currentLED == 2) {
            GPIOA->BSRR = GPIO_BSRR_BR6; // Reset PA6
        }
        if (buttonPressed) {
            // Success - light up Success LED on PA3
            GPIOA->BSRR = GPIO_BSRR_BS3; // Set PA3
            delay_ms(2000);
            GPIOA->BSRR = GPIO_BSRR_BR3; // Reset PA3
        } else {
            // Failure - light up Failure LED on PA4
            GPIOA->BSRR = GPIO_BSRR_BS4; // Set PA4
            delay_ms(2000);
            GPIOA->BSRR = GPIO_BSRR_BR4; // Reset PA4
        }

       
    }
}

void SysTick_Handler(void) {
    msTicks++;
}

void EXTI0_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR0) {
        if (currentLED == 0) {
            buttonPressed = 1;
        }
        EXTI->PR = EXTI_PR_PR0; // Clear the interrupt flag
    }
}

void EXTI1_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR1) {
        if (currentLED == 1) {
            buttonPressed = 1;
        }
        EXTI->PR = EXTI_PR_PR1; // Clear the interrupt flag
    }
}

void EXTI15_10_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR10) { // Change to EXTI15_10 for PB10
        if (currentLED == 2) {
            buttonPressed = 1;
        }
        EXTI->PR = EXTI_PR_PR10; // Clear the interrupt flag
    }
}

void delay_ms(uint32_t ms) {
    uint32_t target = msTicks + ms;
    while (msTicks < target);
}

void init_LEDs(void) {
    // Enable GPIOA clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Configure PA0, PA5, PA6, PA3, PA4 as output push-pull
    GPIOA->CRL &= ~((GPIO_CRL_MODE0 | GPIO_CRL_CNF0) |
                    (GPIO_CRL_MODE5 | GPIO_CRL_CNF5) |
                    (GPIO_CRL_MODE6 | GPIO_CRL_CNF6) |
                    (GPIO_CRL_MODE3 | GPIO_CRL_CNF3) |
                    (GPIO_CRL_MODE4 | GPIO_CRL_CNF4));

    GPIOA->CRL |= (GPIO_CRL_MODE0_1 | GPIO_CRL_MODE5_1 | GPIO_CRL_MODE6_1 |
                   GPIO_CRL_MODE3_1 | GPIO_CRL_MODE4_1); // Output mode, max speed 2 MHz
}

void init_buttons(void) {
    // Enable GPIOB clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // Configure PB0, PB1, PB10 as input with pull-up
    GPIOB->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
    GPIOB->CRL |= GPIO_CRL_CNF0_1; // Input mode, pull-up
    GPIOB->ODR |= GPIO_ODR_ODR0; // Enable pull-up

    GPIOB->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1);
    GPIOB->CRL |= GPIO_CRL_CNF1_1; // Input mode, pull-up
    GPIOB->ODR |= GPIO_ODR_ODR1; // Enable pull-up

    GPIOB->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10); // Change to PB10
    GPIOB->CRH |= GPIO_CRH_CNF10_1; // Input mode, pull-up
    GPIOB->ODR |= GPIO_ODR_ODR10; // Enable pull-up
}

void init_SysTick(void) {
    SysTick_Config(SystemCoreClock / 1000);  // 1 ms tick
}

void init_EXTI(void) {
    // Enable AFIO clock
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // Configure EXTI line 0, 1, and 10 for PB0, PB1, and PB10
    AFIO->EXTICR[0] &= ~(AFIO_EXTICR1_EXTI0 | AFIO_EXTICR1_EXTI1);
    AFIO->EXTICR[0] |= (0x01 << 0) | (0x01 << 4); // Set EXTI0 to PB0, EXTI1 to PB1
    AFIO->EXTICR[2] &= ~(AFIO_EXTICR3_EXTI10); // Clear EXTI10 bits
    AFIO->EXTICR[2] |= (0x01 << 8); // Set EXTI10 to PB10

    EXTI->IMR |= (EXTI_IMR_MR0 | EXTI_IMR_MR1 | EXTI_IMR_MR10); // Unmask EXTI lines
    EXTI->FTSR |= (EXTI_FTSR_TR0 | EXTI_FTSR_TR1 | EXTI_FTSR_TR10); // Trigger on falling edge

    // Enable EXTI0, EXTI1, and EXTI15_10 interrupts in NVIC
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_SetPriority(EXTI0_IRQn, 0);

    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_SetPriority(EXTI1_IRQn, 0);

    NVIC_EnableIRQ(EXTI15_10_IRQn); // Enable interrupt for EXTI lines 10 to 15
    NVIC_SetPriority(EXTI15_10_IRQn, 0);
}

// Debounce function to check if the button is pressed
uint8_t debounce_button(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    if (!(GPIOx->IDR & GPIO_Pin)) { // Check if button is pressed
        delay_ms(50);  // Wait for 50 ms for debounce
        if (!(GPIOx->IDR & GPIO_Pin)) {
            return 1;
        }
    }
    return 0;
}

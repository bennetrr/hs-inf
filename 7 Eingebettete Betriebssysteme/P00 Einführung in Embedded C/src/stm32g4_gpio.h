/* Auszug aus stm32g474xx.h (vgl. Vorlesung Folie 2-21)
 * Hinweis: Im Simulator (STM32F405) liegt an dieser Adresse KEINE
 * Peripherie – siehe Aufgabe 0.3.3 d).                                */
#ifndef STM32G4_GPIO_H
#define STM32G4_GPIO_H

#include <stdint.h>

#define __IO volatile

typedef struct
{
    __IO uint32_t MODER;   /* GPIO port mode register                 */
    __IO uint32_t OTYPER;  /* GPIO port output type register          */
    __IO uint32_t OSPEEDR; /* GPIO port output speed register         */
    __IO uint32_t PUPDR;   /* GPIO port pull-up/pull-down register    */
    __IO uint32_t IDR;     /* GPIO port input data register           */
    __IO uint32_t ODR;     /* GPIO port output data register          */
    __IO uint32_t BSRR;    /* GPIO port bit set/reset register        */
    __IO uint32_t LCKR;    /* GPIO port configuration lock register   */
    __IO uint32_t AFR[2];  /* GPIO alternate function registers       */
    __IO uint32_t BRR;     /* GPIO Bit Reset register                 */
} GPIO_TypeDef;

#define PERIPH_BASE     (0x40000000UL)
#define AHB2PERIPH_BASE (PERIPH_BASE + 0x08000000UL)
#define GPIOA_BASE      (AHB2PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE      (AHB2PERIPH_BASE + 0x0400UL)

#define GPIOA ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef*)GPIOB_BASE)

#endif /* STM32G4_GPIO_H */

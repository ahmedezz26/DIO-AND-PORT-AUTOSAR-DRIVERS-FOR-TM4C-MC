 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Ahmed Ezz
 ******************************************************************************/
#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)


/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif
   
/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif
   

/* PB structure used with Port_Init API */

const Port_ConfigType Port_Configuration = {
  
PORTA_PIN0,PORTA,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTA_PIN1,PORTA,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTA_PIN2,PORTA,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTA_PIN3,PORTA,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTA_PIN4,PORTA,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTA_PIN5,PORTA,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTA_PIN6,PORTA,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT, DigitalAnalog_DEFAULT,

PORTA_PIN7,PORTA,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTB_PIN0,PORTB,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTB_PIN1,PORTB,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTB_PIN2,PORTB,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTB_PIN3,PORTB,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTB_PIN4,PORTB,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTB_PIN5,PORTB,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTB_PIN6,PORTB,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTB_PIN7,PORTB,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTC_PIN0,PORTC,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTC_PIN1,PORTC,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTC_PIN2,PORTC,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTC_PIN3,PORTC,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTC_PIN4,PORTC,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTC_PIN5,PORTC,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTC_PIN6,PORTC,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTC_PIN7,PORTC,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTD_PIN0,PORTD,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTD_PIN1,PORTD,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTD_PIN2,PORTD,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTD_PIN3,PORTD,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTD_PIN4,PORTD,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTD_PIN5,PORTD,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTD_PIN6,PORTD,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTD_PIN7,PORTD,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTE_PIN0,PORTE,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTE_PIN1,PORTE,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTE_PIN2,PORTE,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTE_PIN3,PORTE,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTE_PIN4,PORTE,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTE_PIN5,PORTE,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTF_PIN0,PORTF,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,
/* LED 1 */
PORTF_PIN1,PORTF,ModeType_DEFAULT,LevelType_DEFAULT,PORT_PIN_OUT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTF_PIN2,PORTF,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,

PORTF_PIN3,PORTF,ModeType_DEFAULT,LevelType_DEFAULT,DirectionType_DEFAULT,
InternalResistor_DEFAULT,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,
/* Switch 1 */
PORTF_PIN4,PORTF,ModeType_DEFAULT,LevelType_DEFAULT,PORT_PIN_IN,
PULL_UP,ModeChangeable_DEFAULT,DirectionChangeable_DEFAULT,DigitalAnalog_DEFAULT,
};
     


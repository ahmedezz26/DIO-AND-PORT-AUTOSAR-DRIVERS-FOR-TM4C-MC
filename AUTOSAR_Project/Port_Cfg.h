 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Ahmed Ezz
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)

/* Pre-compile option for Set Pin Direction API */
#define PORT_SET_PIN_DIRECTION_API           (STD_ON)

/* Number of the configured PORT Channels */
#define PORT_CONFIGURED_CHANNELS              (43U)

/* PORT Configured Pin ID's  */
#define PORTA_PIN0             (uint8)0 
#define PORTA_PIN1             (uint8)1 
#define PORTA_PIN2             (uint8)2
#define PORTA_PIN3             (uint8)3
#define PORTA_PIN4             (uint8)4
#define PORTA_PIN5             (uint8)5
#define PORTA_PIN6             (uint8)6
#define PORTA_PIN7             (uint8)7
#define PORTB_PIN0             (uint8)0 
#define PORTB_PIN1             (uint8)1 
#define PORTB_PIN2             (uint8)2
#define PORTB_PIN3             (uint8)3
#define PORTB_PIN4             (uint8)4
#define PORTB_PIN5             (uint8)5
#define PORTB_PIN6             (uint8)6
#define PORTB_PIN7             (uint8)7
#define PORTC_PIN0             (uint8)0 
#define PORTC_PIN1             (uint8)1
#define PORTC_PIN2             (uint8)2
#define PORTC_PIN3             (uint8)3
#define PORTC_PIN4             (uint8)4
#define PORTC_PIN5             (uint8)5
#define PORTC_PIN6             (uint8)6
#define PORTC_PIN7             (uint8)7 
#define PORTD_PIN0             (uint8)0 
#define PORTD_PIN1             (uint8)1 
#define PORTD_PIN2             (uint8)2
#define PORTD_PIN3             (uint8)3
#define PORTD_PIN4             (uint8)4
#define PORTD_PIN5             (uint8)5
#define PORTD_PIN6             (uint8)6
#define PORTD_PIN7             (uint8)7
#define PORTE_PIN0             (uint8)0 
#define PORTE_PIN1             (uint8)1 
#define PORTE_PIN2             (uint8)2
#define PORTE_PIN3             (uint8)3
#define PORTE_PIN4             (uint8)4
#define PORTE_PIN5             (uint8)5
#define PORTF_PIN0             (uint8)0 
#define PORTF_PIN1             (uint8)1 
#define PORTF_PIN2             (uint8)2
#define PORTF_PIN3             (uint8)3
#define PORTF_PIN4             (uint8)4
   

/* PORT Configured Port ID's  */
#define PORTA                             (Port_PortType)0 
#define PORTB                             (Port_PortType)1 
#define PORTC                             (Port_PortType)2 
#define PORTD                             (Port_PortType)3 
#define PORTE                             (Port_PortType)4 
#define PORTF                             (Port_PortType)5 

/* Pin Modes */

#define PIN_MODE_ZERO                  0
#define PIN_MODE_ONE                   1
#define PIN_MODE_TWO                   2
#define PIN_MODE_THREE                 3
#define PIN_MODE_FOUR                  4
#define PIN_MODE_FIVE                  5
#define PIN_MODE_SIX                   6 
#define PIN_MODE_SEVEN                 7
#define PIN_MODE_EIGHT                 8
#define PIN_MODE_NINE                  9
#define PIN_MODE_FOURTEEN              14


/* Default Configurations */   
#define ModeType_DEFAULT               (uint8)0
#define LevelType_DEFAULT              STD_LOW
#define DirectionType_DEFAULT          PORT_PIN_IN
#define InternalResistor_DEFAULT       OFF
#define ModeChangeable_DEFAULT         PORT_PIN_MODE_CHANGEABLE
#define DirectionChangeable_DEFAULT    PORT_PIN_DIR_CHANGEABLE
#define DigitalAnalog_DEFAULT          DIGITAL 

   





#endif /* PORT_CFG_H */
 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Ahmed Ezz
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"
#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif 


STATIC const Port_ConfigChannel * Port_PortChannels = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module:
*              - Setup the pin as Digital GPIO pin
*              - Setup the direction of the GPIO pin
*              - Setup the internal resistor for i/p pin
************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr )
{

#if( PORT_DEV_ERROR_DETECT == STD_ON)
	
    if(ConfigPtr== NULL_PTR)
    {
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		     PORT_E_PARAM_CONFIG);
    }
    else
  
#endif
    {
      /*
       * Set the module state to initialized and point to the PB configuration structure using a global pointer.
       * This global pointer is global to be used by other functions to read the PB configuration structures
       */
      Port_Status = PORT_INITIALIZED;
      Port_PortChannels=ConfigPtr->Channels; /* address of the first Channels structure --> Channels[0] */
    }
     /* Enable clock for PORT and allow time for clock to start*/
    volatile uint32 delay = 0;
    SYSCTL_REGCGC2_REG |= 0x3F;
    delay = SYSCTL_REGCGC2_REG;
    
    volatile uint32 * PortGpio_Ptr = NULL_PTR;
    Port_PinType pin ;
    Port_PortType port;
    Port_LevelType level; 
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;
    Port_Digital_Analog digital_analog;
    Port_PinModeType mode; 
    for(int i=0;i<PORT_CONFIGURED_CHANNELS;i++)
    {
       pin      = (*ConfigPtr).Channels[i].pin_num;
       port     = (*ConfigPtr).Channels[i].port_num;
       level    = (*ConfigPtr).Channels[i].level;
       direction= (*ConfigPtr).Channels[i].direction;
       resistor = (*ConfigPtr).Channels[i].resistor;
       digital_analog = (*ConfigPtr).Channels[i].digital_analog;
       mode = (*ConfigPtr).Channels[i].mode;
           switch(port)
            {
            case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                     break;
            case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                     break;
            case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                     break;
            case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                     break;
            case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                     break;
            case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                     break;
            }
          
            
            if( ( port == 3) && (pin == 7) || (port == 5) && (pin == 0) ) /* PD7 or PF0 */
            {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , pin);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else if( (port == 2) && (pin <= 3) ) /* PC0 to PC3 */
            {
                /* Do Nothing ...  this is the JTAG pins */
                continue;
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }
           
            if(digital_analog == DIGITAL)
            {
               /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pin);
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pin);       
               
            }
           
            else if (digital_analog == ANALOG)
            {
               /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,pin);
               /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) ,pin);
            }
           
            else
              
            {
              /* Do Nothing */
            }
           
            if ( mode == PIN_MODE_ZERO)
            {
              /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pin);
               /* Clear the PMCx bits for this pin */
               *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (pin * 4));    
              
            }
           
            else
            {
              /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pin);
              /* Set Mode in the PMCx bits for this pin */
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (pin * 4));  
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (mode & 0x0F<< (pin * 4));
              
            }
              
              
             
            
             if(direction == PORT_PIN_OUT)
            {
              /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,pin);            
                
                
                if(level == STD_HIGH)
                {
                     /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , pin);       
                }
                else
                {
                  /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , pin);        
                }
            }
            
            else if(direction == PORT_PIN_IN)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                
                if(resistor == PULL_UP)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , pin);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
                else if(resistor == PULL_DOWN)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) ,pin);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , pin);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , pin);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                }
            }
            else
            {
                /* Do Nothing */
            }
            
            
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pin);
    
         
    }
    
   
  
}


#if (PORT_SET_PIN_DIRECTION_API==STD_ON)
/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
************************************************************************************/
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
      boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
	/* Check if the used channel is within the valid range */
	if (PORT_CONFIGURED_CHANNELS <= Pin && !(Pin >=0) )
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        if ( Port_PortChannels[Pin].direction_change==PORT_PIN_DIR_UNCHANGEABLE)
        {
          Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
		error = TRUE;
        }
        else
        {
          /* No Action Required */
        }
        
        
#endif
        if(FALSE == error)
	{
          
          if ( Port_PortChannels[Pin].direction_change==PORT_PIN_DIR_UNCHANGEABLE)
          {
                  return;
                  
          }
          else
          {
          
            volatile uint32 * PortGpio_Ptr = NULL_PTR;
            switch(Port_PortChannels[Pin].port_num)
              {
              case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                       break;
              case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                       break;
              case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                       break;
              case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                       break;
              case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                       break;
              case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                       break;
              }
            
            if(Direction==PORT_PIN_IN)
            {
              /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
              Port_PinType pin = Port_PortChannels[Pin].pin_num;
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin);         
          
              
            }
            else if(Direction==PORT_PIN_OUT)
            {
              /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
              Port_PinType pin = Port_PortChannels[Pin].pin_num;
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin);
              
            }
            else
            {
              /* No Action Required */
            }
          }
        
      }
        
      else
      {
        /* No Action Required */
      }
            
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/

void Port_RefreshPortDirection( void )
{
   boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
        else
        {
          /* No Action Required */
        }  
  
#endif 

  if(FALSE == error)
  {
  
        volatile uint32 * PortGpio_Ptr = NULL_PTR;
        Port_PinType pin ;
        Port_PortType port;
        for(int i=0;i<PORT_CONFIGURED_CHANNELS;i++)
        {
            pin= Port_PortChannels[i].pin_num;
            port=Port_PortChannels[i].port_num;
           if( (port == 2) && (pin <= 3) ) /* PC0 to PC3 */
            {
                /* Do Nothing ...  this is the JTAG pins */
                continue;
            }
           else if (Port_PortChannels[i].direction_change==PORT_PIN_DIR_UNCHANGEABLE)
           {
                  
                  switch(Port_PortChannels[i].port_num)
                  {
                  case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                           break;
                  case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                           break;
                  case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                           break;
                  case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                           break;
                  case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                           break;
                  case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                           break;
                  }
                
                if(Port_PortChannels[i].direction==PORT_PIN_IN)
                {
                  /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
               
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin);         
              
                  
                }
                else if(Port_PortChannels[i].direction==PORT_PIN_OUT)
                {
                  /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                 
                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , pin);
                  
                }
                else
                {
                  /* No Action Required */
                }
                
           }
           else
           {
              /* No Action Required */
           }
            
        }
  }
}

                      
#if (PORT_VERSION_INFO_API==STD_ON)
/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo- Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
  
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
	}
	else
#endif 
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}
  
}
#endif


/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in):  Pin - Port Pin Id Number
                    Mode- New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/


void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
		error = TRUE;
	}
        else
        {
          /* No Action Required */
        }
        /* Check if the used channel is within the valid range */
	if (PORT_CONFIGURED_CHANNELS <= Pin && !(Pin >=0) )
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

        if ( Port_PortChannels[Pin].mode_change==PORT_PIN_MODE_UNCHANGEABLE)
        {
          Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
		error = TRUE;
        }
        else
        {
          /* No Action Required */
        }
        
         /* Check if Mode is invalid */
        if (! ( ( (Mode >= PIN_MODE_ZERO) && (Mode <= PIN_MODE_NINE) ) || (Mode == PIN_MODE_FOURTEEN)  ) )
        {              
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, 
                                PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
                error = TRUE;
        }
        else
        {
              /* Do nothing */
        }  
        
  
#endif 

  if(FALSE == error)
  {
    
      if(Port_PortChannels[Pin].mode_change==PORT_PIN_MODE_UNCHANGEABLE)
      {
         return; 
      }
      else
      {
    
            volatile uint32 * PortGpio_Ptr = NULL_PTR;
            Port_PortType port=Port_PortChannels[Pin].port_num;
            Port_PinType pin=Port_PortChannels[Pin].pin_num;
            switch(port)
            {
            case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                     break;
            case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                     break;
            case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                     break;
            case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                     break;
            case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                     break;
            case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                     break;
            }
             
            if(Mode != PIN_MODE_ZERO)
            {
              
                /* Enable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pin);
              /* Set Mode in the PMCx bits for this pin */
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (pin * 4));  
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Mode & 0x0F<< (pin * 4));
            }
            else
            {
                /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , pin);         
              /* Clear the PMCx bits for this pin */
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (pin * 4));  
            
            }
            
            if( Port_PortChannels[Pin].digital_analog == DIGITAL )
            {
              
              
              /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , pin);
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
               SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , pin);       
              
            }
            else if (Port_PortChannels[Pin].digital_analog== ANALOG)
            {
               /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
                  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,pin);
               /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) ,pin);
              
            }
            else
            {
              
              /* Do nothing */
            }
            
            
            
    
      }
    
    
    
  }
  else
  {
    /* No Action Required */
  }
  
  
  
}





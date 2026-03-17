#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "Driver_CAN.h"                 // CMSIS Driver:CAN
 
  //--------- extern 
	
	extern  ARM_DRIVER_CAN    Driver_CAN1;
	
	
  //--------- ID des Tâches ou autres
 osThreadId_t Tache1;                        // thread id
 
 
  //--------- Prototype des Fonctions 
  void Initialisation_CAN();
 
 //--------- Tâches du code
 	 	void Thread (void *arg) {				
  
	char data_buf[1];
		
  while (1) {
		tx_msg_info.id = ARM_CAN_STANDARD_ID (0x5F8);
		tx_msg_info.rtr = 0; // 0 = trame DATA
		data_buf [0] = 0xFA; // data à envoyer à placer dans un tableau de char
			
		Driver_CAN1.MessageSend(1, &tx_msg_info, data_buf, 1); // 1 data à envoyer  }
	}
	} 
  
//--------- Main code
int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
  // ...
 
  osKernelInitialize();                 // Initialize CMSIS-RTOS
  Initialisation_CAN();
	
	  /* Create thread functions that start executing, 
  Example: osThreadNew(app_main, NULL, NULL); */
  Tache1 = osThreadNew((osThreadFunc_t) Thread, NULL, NULL); // (fonction, arg, configuration)
	
	/* Start thread execution */
  osKernelStart();                      // Start thread execution
  for (;;) {}
}

 
//--------- Defintition des Fonctions
void Initialisation_CAN()
{
	volatile int32_t                  status;
	 
	status=Driver_CAN1.Initialize(NULL, NULL);
	status=Driver_CAN1.PowerControl(ARM_POWER_FULL);
	
	status=Driver_CAN1.SetMode(ARM_CAN_MODE_INITIALIZATION);
	status=Driver_CAN1.SetBitrate(
												ARM_CAN_BITRATE_NOMINAL, // d?bit fixe
												500000, // 500 kbits/s (HS)
												ARM_CAN_BIT_PROP_SEG(3U) | // prop. seg = 3 TQ
												ARM_CAN_BIT_PHASE_SEG1(1U) | // phase seg1 = 1 TQ
												ARM_CAN_BIT_PHASE_SEG2(1U) | // phase seg2 = 1 TQ
												ARM_CAN_BIT_SJW(1U) // Resync. Seg = 1 TQ
										);
	
	status=Driver_CAN1.ObjectConfigure(0,ARM_CAN_OBJ_RX); // Objet 0 pour r?ception
	status=Driver_CAN1.ObjectConfigure(2,ARM_CAN_OBJ_TX); // Objet 2 pour send
	
	status=Driver_CAN1.ObjectSetFilter( 0, ARM_CAN_FILTER_ID_EXACT_ADD , ARM_CAN_STANDARD_ID(0x599),0); // the last arg is Mask or end of ID range (depending on filter type)

	status=Driver_CAN1.SetMode(ARM_CAN_MODE_NORMAL); // fin initialisation
	
}

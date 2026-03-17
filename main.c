#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "Driver_I2C.h"                 // CMSIS Driver:I2C

  //--------- extern 
	
	extern ARM_DRIVER_I2C Driver_I2C1; // “déclaration” structure I2C0
	
	
  //--------- ID des Tâches ou autres
 osThreadId_t Tache1;                        // thread id
 
 
  //--------- Prototype des Fonctions 
  void Initialisation_I2C();
 
 //--------- Tâches du code
 	void Thread (void *arg) {				
 
  while (1) {
    // Insert thread code here...
  }
} 
  
//--------- Main code
int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
  // ...
 
  osKernelInitialize();                 // Initialize CMSIS-RTOS
  Initialisation_I2C();
	
	  /* Create thread functions that start executing, 
  Example: osThreadNew(app_main, NULL, NULL); */
  Tache1 = osThreadNew((osThreadFunc_t) Thread, NULL, NULL); // (fonction, arg, configuration)
	
	/* Start thread execution */
  osKernelStart();                      // Start thread execution
  for (;;) {}
}

 
//--------- Defintition des Fonctions
void Initialisation_I2C()
{
	volatile int32_t                  status;
	 
	status=Driver_I2C1.Initialize(NULL);
	status=Driver_I2C1.PowerControl(ARM_POWER_FULL);
	
	Driver_I2C1.Control( ARM_I2C_BUS_SPEED, // 2nd argument = débit
											 ARM_I2C_BUS_SPEED_STANDARD ); // =100 kHz
	
	Driver_I2C1.Control( ARM_I2C_BUS_CLEAR, // 9 pulses d'horloge
																			0 ); // non utilisé
	
}
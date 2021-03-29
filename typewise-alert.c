#include "typewise-alert.h"
#include <stdio.h>

BatteryLimit_s BatteryLimit[3] = {{0,35},{0,45},{0,40}};
printChargeLevel_Mail_s printChargeLevel_Mail[3] = {charge_Normal,charge_TooLow,charge_TooHigh};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{	
  return inferBreach(temperatureInC, BatteryLimit[coolingType].lowerLimit, BatteryLimit[coolingType].upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) 
{  
  printChargeLevel_Mail[breachType].printChargeLevel();
}

void charge_TooLow(void)
{
	const char* recepient = "a.b@c.com";
	printf("To: %s\n", recepient);
    printf("Hi, the temperature is too low\n");
}

void charge_TooHigh(void)
{
	const char* recepient = "a.b@c.com";
	printf("To: %s\n", recepient);
    printf("Hi, the temperature is too high\n");
}

void charge_Normal(void)
{
	//Do Nothing
}

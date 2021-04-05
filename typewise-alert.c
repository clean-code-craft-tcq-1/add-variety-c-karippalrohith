#include "typewise-alert.h"
#include <stdio.h>

BatteryLimit_s BatteryLimit[3] = {{0,35},{0,45},{0,40}};
printChargeLevel_Mail_s printChargeLevel_Mail[3] = {charge_Normal,charge_TooLow,charge_TooHigh};
alert_Target_s alert_Target[3] = {sendToController,sendToEmail,sendToConsole};

BreachType breachType_Status = DEFAULT;

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

BreachType checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

	alert_Target[alertTarget].alertTargetType(breachType);
	
	return breachType;
}

void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  Alert_Print_Status = PRINTED_IN_CONTROLLER;
  breachType_Status = breachType;
}

void sendToEmail(BreachType breachType) 
{  
  breachType_Status = breachType;
  printChargeLevel_Mail[breachType].printChargeLevel();
  Alert_Print_Status = PRINTED_IN_EMAIL;
}

void sendToConsole(BreachType breachType) 
{
  printf("%x\n", breachType);
  breachType_Status = breachType;
  Alert_Print_Status = PRINTED_IN_CONSOLE;
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

#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH,
  DEFAULT
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  TO_CONSOLE,
  DEFAULT
} AlertTarget;

typedef enum {
	PRINTED_IN_CONTROLLER,
	PRINTED_IN_EMAIL,
	PRINTED_IN_CONSOLE,
	NO_PRINT_DONE
}Alert_Print_Status_t;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef struct {
	int lowerLimit;
	int upperLimit;
}BatteryLimit_s;

typedef struct 
{
   void (*printChargeLevel)();
}printChargeLevel_Mail_s;

typedef struct{
	void (*alertTargetType)(BreachType breachType);
}alert_Target_s;

BreachType checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
Alert_Print_Status_t Alert_Print_Status;

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
void sendToConsole(BreachType breachType);

void charge_TooLow(void);
void charge_TooHigh(void);
void charge_Normal(void);

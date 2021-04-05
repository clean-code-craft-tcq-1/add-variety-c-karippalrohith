#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("Passive Cooling system with Normal temp and O/P fed to controller") {
	
	Alert_Status_s Alert_Status_Output = {NO_PRINT_DONE,DEFAULT_BREACH};
	BatteryCharacter batteryCharacter = {PASSIVE_COOLING,"Brand_TCQ"};
	
	Alert_Status_Output = checkAndAlert(TO_CONTROLLER, batteryCharacter, 20);
	REQUIRE(Alert_Status_Output.Alert_Print_Status == PRINTED_IN_CONTROLLER);
	REQUIRE(Alert_Status_Output.breachType == NORMAL);
}

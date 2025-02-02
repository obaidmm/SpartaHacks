#include <stdint.h>
#include "fwwsam/include/fwwasm.h"

volatile uint8_t exitApp = 0;

void processAccelData(uint8_t *event_data)
{
    int16_t iX, iY, iZ, iTc, iTf;
    bool iMoving, iMovingX, iMovingY, iMovingZ;

    // Read accelerometer values
    iX = event_data[0] | event_data[1] << 8;
    iY = event_data[2] | event_data[3] << 8;
    iZ = event_data[4] | event_data[5] << 8;
    iTc = event_data[6] | event_data[7] << 8;
    iTf = event_data[8] | event_data[9] << 8;
    iMoving = event_data[10] & 0x1;
    iMovingX = event_data[10] & 0x2 ? 1 : 0;
    iMovingY = event_data[10] & 0x4 ? 1 : 0;
    iMovingZ = event_data[10] & 0x8 ? 1 : 0;

    // Print accelerometer values (for debugging)
    printInt("Got accel: X:%d\n", printOutColor::printColorBlue, printOutDataType::printInt16, iX);
    printInt("Got accel: Y:%d\n", printOutColor::printColorBlue, printOutDataType::printInt16, iY);
    printInt("Got accel: Z:%d\n", printOutColor::printColorBlue, printOutDataType::printInt16, iZ);

    // Detect tilt based on X-axis value (tilt left or right)
    if (iY > 10) {
        // Right tilt detected
        printInt("Tilt: Right\n", printOutColor::printColorGreen, printOutDataType::printInt16, 1);
        setBoardLED(1, 0xFF, 0x00, 0x00, 300, LEDManagerLEDMode::ledpulsefade);  // Green LED for right tilt
    } else if (iY < -10) {
        // Left tilt detected
        printInt("Tilt: Left\n", printOutColor::printColorRed, printOutDataType::printInt16, 1);
        setBoardLED(1, 0x00, 0xFF, 0x00, 300, LEDManagerLEDMode::ledpulsefade);  // Red LED for left tilt
    } else if (iZ < 1) {
        // Neutral tilt detected (expanded range)
        printInt("Tilt: Neutral\n", printOutColor::printColorBlue, printOutDataType::printInt16, 1);
        setBoardLED(1, 0x00, 0x00, 0xFF, 300, LEDManagerLEDMode::ledpulsefade);  // Blue LED for neutral tilt
    } 

    // Optionally, print the moving status (not used in tilt detection)
    printInt("Got iMoving: %d\n", printOutColor::printColorBlue, printOutDataType::printInt16, iMoving);
    printInt("Got isMovingX: %d\n", printOutColor::printColorBlue, printOutDataType::printInt16, iMovingX);
    printInt("Got isMovingY: %d\n", printOutColor::printColorBlue, printOutDataType::printInt16, iMovingY);
    printInt("Got isMovingZ: %d\n", printOutColor::printColorBlue, printOutDataType::printInt16, iMovingZ);
}

void loop()
{
    uint8_t event_data[FW_GET_EVENT_DATA_MAX] = {0};
    int last_event;

    printInt("\nloop()\n", printOutColor::printColorBlack, printOutDataType::printUInt32, 0);

    // Check if there is an event, and if so, get the data from it
    last_event = 0;
    if (hasEvent())
    {
        last_event = getEventData(event_data);
        printInt("Last event: %d\n", printOutColor::printColorBlack, printOutDataType::printUInt32, last_event);
    }

    // If the event was SENSOR_DATA, process the accelerometer data
    if (last_event == FWGUI_EVENT_GUI_SENSOR_DATA)
    {
        processAccelData(event_data);
    }

    // Exit condition: red button pressed
#if (true)
    else if (last_event == FWGUI_EVENT_RED_BUTTON)
    {
        printInt("Exit...\n", printOutColor::printColorBlack, printOutDataType::printUInt32, 0);
        exitApp = 1;
    }
#endif
}

int main()
{
    setSensorSettings(1, 0, 1000, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0);  // Set sensor settings (1-second interval for accelerometer data)
    printInt("\nmain()\n", printOutColor::printColorBlack, printOutDataType::printUInt32, 0);
    while (!exitApp)
    {
        loop();
        waitms(1000);  // Wait for 1 second before checking again
    }
    return 0;
}
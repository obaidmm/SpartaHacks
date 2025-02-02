#include "fwwsam/include/fwwasm.h"

// Define the event structure to hold IR event data
typedef struct {
    unsigned int iEvent;        // Event type (e.g., FWGUI_EVENT_IR_CODE)
    unsigned char btData[4];    // Data associated with the event (IR code data)
} IR_Event;

// Example array to hold events (size 10 for this example)
IR_Event stEvents[10];
int iCount = 0;  // Event index to keep track of the current event

// Simulate filling the event array with an IR code for testing purposes
void simulateIRCodeEvent() {
    if (iCount < 10) {
        // For testing: Simulating an IR event with a 4-byte IR code
        stEvents[iCount].iEvent = FWGUI_EVENT_IR_CODE; // Set event type to IR code
        stEvents[iCount].btData[0] = 0xAA; // Set the first byte of IR data (just an example)
        stEvents[iCount].btData[1] = 0xBB; // Set the second byte of IR data
        stEvents[iCount].btData[2] = 0xCC; // Set the third byte of IR data
        stEvents[iCount].btData[3] = 0xDD; // Set the fourth byte of IR data
        iCount++;  // Increment event count (to simulate next event)
    }
}

// Function to send IR data
void sendIRCode(unsigned int data) {
    sendIRData(data);  // Send the IR data using the sendIRData function
    printInt("IR Data Sent: %x", printColorGreen, printInt32, data);  // Log the IR code sent (in hexadecimal format)
}

// Function to handle IR events (received IR data)
void handleIREvents() {
    // Simulate receiving an IR code event (this is where actual events would come in a real system)
    simulateIRCodeEvent();

    // Check if there are any events to process
    if (iCount > 0) {
        // Process the first event in the event array (stEvents[0])
        if (stEvents[0].iEvent == FWGUI_EVENT_IR_CODE) {
            unsigned int iIRCode;
            
            // Decode the received IR code (assumes 4 bytes of data)
            iIRCode = stEvents[0].btData[0];
            iIRCode |= ((unsigned int)stEvents[0].btData[1]) << 8;
            iIRCode |= ((unsigned int)stEvents[0].btData[2]) << 16;
            iIRCode |= ((unsigned int)stEvents[0].btData[3]) << 24;
            
            // Print the decoded IR code (in hexadecimal)
            printInt("Received IR Code: %x", printColorCyan, printInt32, iIRCode);

            // Echo the received IR code back or send a custom response
            sendIRCode(iIRCode);  // Send the same IR code back (as an example)
            
            // Shift remaining events (if any) to the left in the array to process the next event
            for (int i = 1; i < iCount; i++) {
                stEvents[i - 1] = stEvents[i];  // Shift event array
            }
            iCount--;  // Decrease the event count
        }
    }
}

// Main entry point
int main() {
    // Continuous loop to handle IR events
    while (1) {
        handleIREvents();  // Continuously process IR events
    }

    return 0; // This part will likely never be reached
}

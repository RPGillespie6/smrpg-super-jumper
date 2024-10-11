/*
Nintendo Switch Fightstick - Proof-of-Concept

Based on the LUFA library's Low-Level Joystick Demo
    (C) Dean Camera
Based on the HORI's Pokken Tournament Pro Pad design
    (C) HORI

This project implements a modified version of HORI's Pokken Tournament Pro Pad
USB descriptors to allow for the creation of custom controllers for the
Nintendo Switch. This also works to a limited degree on the PS3.

Since System Update v3.0.0, the Nintendo Switch recognizes the Pokken
Tournament Pro Pad as a Pro Controller. Physical design limitations prevent
the Pokken Controller from functioning at the same level as the Pro
Controller. However, by default most of the descriptors are there, with the
exception of Home and Capture. Descriptor modification allows us to unlock
these buttons for our use.
*/

#include "Joystick.h"
#include "millis.h"

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    X,
    Y,
    A,
    B,
    L,
    R,
    THROW,
    NOTHING,
    TRIGGERS
} Buttons_t;

typedef struct
{
    Buttons_t button;
    uint16_t duration; // ticks
    millis_t target_time;
} command;

// According to reddit, we need .8836 seconds between each jump
// https://www.reddit.com/r/MarioRPG/comments/18nyaqq/comment/kt8sno0/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button
const int BUTTON_PRESS_MS = 80; // .08 seconds
const int JUMP_WAIT_MS = 803;   // .8036 seconds

static const command step[] = {
    // Setup controller
    {NOTHING, 250},
    {TRIGGERS, 5},
    {NOTHING, 150},
    {TRIGGERS, 5},
    {NOTHING, 250},
    {A, 5},
    {NOTHING, 250},

    {A, 0, BUTTON_PRESS_MS}, // Select Super Jump
    {NOTHING, 0, 1410},

    {B, 0, BUTTON_PRESS_MS}, // 1
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 2
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 3
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 4
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 5
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 6
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 7
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 8
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 9
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 10
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 11
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 12
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 13
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 14
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 15
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 16
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 17
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 18
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 19
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 20
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 21
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 22
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 23
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 24
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 25
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 26
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 27
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 28
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 29
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 30
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 31
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 32
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 33
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 34
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 35
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 36
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 37
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 38
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 39
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 40
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 41
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 42
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 43
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 44
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 45
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 46
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 47
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 48
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 49
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 50
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 51
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 52
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 53
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 54
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 55
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 56
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 57
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 58
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 59
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 60
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 61
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 62
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 63
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 64
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 65
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 66
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 67
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 68
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 69
    {NOTHING, 0, JUMP_WAIT_MS},

    {B, 0, BUTTON_PRESS_MS},         // 70
    {NOTHING, 0, JUMP_WAIT_MS + 30}, // Offset the .006 that's been accumulating

    {B, 0, BUTTON_PRESS_MS}, // 71
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 72
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 73
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 74
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 75
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 76
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 77
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 78
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 79
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 80
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 81
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 82
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 83
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 84
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 85
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 86
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 87
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 88
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 89
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 90
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 91
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 92
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 93
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 94
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 95
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 96
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 97
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 98
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 99
    {NOTHING, 0, JUMP_WAIT_MS},
    {B, 0, BUTTON_PRESS_MS}, // 100 !!
    {NOTHING, 0, JUMP_WAIT_MS},

    {B, 0, BUTTON_PRESS_MS}, // 101 (for good measure)
    {NOTHING, 0, JUMP_WAIT_MS},
};

int every_nth2 = 0;

// Main entry point.
int main(void)
{
    // We'll start by performing hardware and peripheral setup.
    SetupHardware();
    // We'll then enable global interrupts for our use.
    GlobalInterruptEnable();

    // Once that's done, we'll enter an infinite loop.
    for (;;)
    {
        // We need to run our task to process and deliver data for our IN and OUT endpoints.
        HID_Task();

        // We also need to run the main USB management task, but we can do this less frequently.
        // We'll check the USB management task every 100 loop iterations.
        if (every_nth2 % 100 == 0)
        {
            every_nth2 = 0;
            USB_USBTask();
        }
        else
        {
            every_nth2++;
        }
    }
}

// Configures hardware and peripherals, such as the USB peripherals.
void SetupHardware(void)
{
    // Init the monotonic timer
    millis_init();

    // We need to disable watchdog if enabled by bootloader/fuses.
    MCUSR &= ~(1 << WDRF);
    wdt_disable();

    // We need to disable clock division before initializing the USB hardware.
    clock_prescale_set(clock_div_1);
    // We can then initialize our hardware and peripherals, including the USB stack.

    DDRD = 0xFF; // Teensy uses PORTD
    PORTD = 0x0;
    // We'll just flash all pins on both ports since the UNO R3
    DDRB = 0xFF; // uses PORTB. Micro can use either or, but both give us 2 LEDs
    PORTB = 0x0; // The ATmega328P on the UNO will be resetting, so unplug it?
    // The USB stack should be initialized last.

    USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void)
{
    // We can indicate that we're enumerating here (via status LEDs, sound, etc.).
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void)
{
    // We can indicate that our device is not ready (via status LEDs, sound, etc.).
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void)
{
    bool ConfigSuccess = true;

    // We setup the HID report endpoints.
    ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_OUT_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_IN_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);

    // We can read ConfigSuccess to indicate a success or failure at this point.
}

// Process control requests sent to the device from the USB host.
void EVENT_USB_Device_ControlRequest(void)
{
    // We can handle two control requests: a GetReport and a SetReport.

    // Not used here, it looks like we don't receive control request from the Switch.
}

int every_nth = 0;

// Process and deliver data from IN and OUT endpoints.
void HID_Task(void)
{
    // If the device isn't connected and properly configured, we can't do anything here.
    if (USB_DeviceState != DEVICE_STATE_Configured)
        return;

    // Only check OUT every nth loop to reduce latency for the IN endpoint.
    if (every_nth % 3 == 0)
    {
        every_nth = 0;

        // We'll start with the OUT endpoint.
        Endpoint_SelectEndpoint(JOYSTICK_OUT_EPADDR);
        // We'll check to see if we received something on the OUT endpoint.
        if (Endpoint_IsOUTReceived())
        {
            // If we did, and the packet has data, we'll react to it.
            if (Endpoint_IsReadWriteAllowed())
            {
                // We'll create a place to store our data received from the host.
                USB_JoystickReport_Output_t JoystickOutputData;
                // We'll then take in that data, setting it up in our storage.
                while (Endpoint_Read_Stream_LE(&JoystickOutputData, sizeof(JoystickOutputData), NULL) != ENDPOINT_RWSTREAM_NoError)
                    ;
                // At this point, we can react to this data.

                // However, since we're not doing anything with this data, we abandon it.
            }
            // Regardless of whether we reacted to the data, we acknowledge an OUT packet on this endpoint.
            Endpoint_ClearOUT();
        }
    }
    else
    {
        every_nth++;
    }

    // We'll then move on to the IN endpoint.
    Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);
    // We first check to see if the host is ready to accept data.
    if (Endpoint_IsINReady())
    {
        // We'll create an empty report.
        USB_JoystickReport_Input_t JoystickInputData;
        // We'll then populate this report with what we want to send to the host.
        GetNextReport(&JoystickInputData);
        // Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
        while (Endpoint_Write_Stream_LE(&JoystickInputData, sizeof(JoystickInputData), NULL) != ENDPOINT_RWSTREAM_NoError)
            ;
        // We then send an IN packet on this endpoint.
        Endpoint_ClearIN();
    }
}

typedef enum
{
    SYNC_CONTROLLER,
    SYNC_POSITION,
    BREATHE,
    PROCESS,
    CLEANUP,
    DONE
} State_t;
State_t state = SYNC_CONTROLLER;

#define ECHOES 2
int echoes = 0;
USB_JoystickReport_Input_t last_report;

int report_count = 0;
int xpos = 0;
int ypos = 0;
int bufindex = 0;
int duration_count = 0;
millis_t start_monotonic_time = 0;
millis_t target_monotonic_time = 0;
int portsvaloff = 0x0;
int portsvalon = 0xffff;

// Prepare the next report for the host.
void GetNextReport(USB_JoystickReport_Input_t *const ReportData)
{
    // Prepare an empty report
    memset(ReportData, 0, sizeof(USB_JoystickReport_Input_t));
    ReportData->LX = STICK_CENTER;
    ReportData->LY = STICK_CENTER;
    ReportData->RX = STICK_CENTER;
    ReportData->RY = STICK_CENTER;
    ReportData->HAT = HAT_CENTER;

    // Repeat ECHOES times the last report
    if (echoes > 0)
    {
        memcpy(ReportData, &last_report, sizeof(USB_JoystickReport_Input_t));
        echoes--;
        return;
    }

    // States and moves management
    switch (state)
    {

    case SYNC_CONTROLLER:
        state = BREATHE;
        break;

        // case SYNC_CONTROLLER:
        // 	if (report_count > 550)
        // 	{
        // 		report_count = 0;
        // 		state = SYNC_POSITION;
        // 	}
        // 	else if (report_count == 250 || report_count == 300 || report_count == 325)
        // 	{
        // 		ReportData->Button |= SWITCH_L | SWITCH_R;
        // 	}
        // 	else if (report_count == 350 || report_count == 375 || report_count == 400)
        // 	{
        // 		ReportData->Button |= SWITCH_A;
        // 	}
        // 	else
        // 	{
        // 		ReportData->Button = 0;
        // 		ReportData->LX = STICK_CENTER;
        // 		ReportData->LY = STICK_CENTER;
        // 		ReportData->RX = STICK_CENTER;
        // 		ReportData->RY = STICK_CENTER;
        // 		ReportData->HAT = HAT_CENTER;
        // 	}
        // 	report_count++;
        // 	break;

    case SYNC_POSITION:
        bufindex = 0;

        ReportData->Button = 0;
        ReportData->LX = STICK_CENTER;
        ReportData->LY = STICK_CENTER;
        ReportData->RX = STICK_CENTER;
        ReportData->RY = STICK_CENTER;
        ReportData->HAT = HAT_CENTER;

        state = BREATHE;
        break;

    case BREATHE:
        state = PROCESS;
        break;

    case PROCESS:
        if (step[bufindex].target_time > 0 && target_monotonic_time == 0)
        {
            start_monotonic_time = millis();
            target_monotonic_time = start_monotonic_time + step[bufindex].target_time;
        }

        switch (step[bufindex].button)
        {

        case UP:
            ReportData->LY = STICK_MIN;
            break;

        case LEFT:
            ReportData->LX = STICK_MIN;
            break;

        case DOWN:
            ReportData->LY = STICK_MAX;
            break;

        case RIGHT:
            ReportData->LX = STICK_MAX;
            break;

        case A:
            PORTD = portsvalon;
            ReportData->Button |= SWITCH_A;
            break;

        case B:
            PORTB = portsvalon;
            ReportData->Button |= SWITCH_B;
            break;

        case R:
            ReportData->Button |= SWITCH_R;
            break;

        case THROW:
            ReportData->LY = STICK_MIN;
            ReportData->Button |= SWITCH_R;
            break;

        case TRIGGERS:
            ReportData->Button |= SWITCH_L | SWITCH_R;
            break;

        default:
            PORTD = portsvaloff;
            PORTB = portsvaloff;

            ReportData->LX = STICK_CENTER;
            ReportData->LY = STICK_CENTER;
            ReportData->RX = STICK_CENTER;
            ReportData->RY = STICK_CENTER;
            ReportData->HAT = HAT_CENTER;
            break;
        }

        duration_count++;

        if (step[bufindex].duration > 0 && duration_count > step[bufindex].duration)
        {
            bufindex++;
            duration_count = 0;
            target_monotonic_time = 0;
        }
        else if (step[bufindex].target_time > 0 && millis() > target_monotonic_time)
        {
            bufindex++;
            duration_count = 0;
            target_monotonic_time += step[bufindex].target_time;
        }

        if (bufindex > (int)(sizeof(step) / sizeof(step[0])) - 1)
        {

            // state = CLEANUP;

            bufindex = 9;
            duration_count = 0;

            state = BREATHE;

            ReportData->LX = STICK_CENTER;
            ReportData->LY = STICK_CENTER;
            ReportData->RX = STICK_CENTER;
            ReportData->RY = STICK_CENTER;
            ReportData->HAT = HAT_CENTER;

            // state = DONE;
            //				state = BREATHE;
        }

        break;

    case CLEANUP:
        state = DONE;
        break;

    case DONE:
        _delay_ms(250);
        return;
    }

    // // Inking
    // if (state != SYNC_CONTROLLER && state != SYNC_POSITION)
    // 	if (pgm_read_byte(&(image_data[(xpos / 8) + (ypos * 40)])) & 1 << (xpos % 8))
    // 		ReportData->Button |= SWITCH_A;

    // Prepare to echo this report
    memcpy(&last_report, ReportData, sizeof(USB_JoystickReport_Input_t));
    echoes = ECHOES;
}
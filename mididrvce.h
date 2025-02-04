/**
 * --------------------------------------
 * 
 * MIDIDRVCE Source Code - mididrvce.h
 * By prime17569
 * Based on work by TIny_Hacker and others
 * Copyright 2025
 * License: LGPL-3.0
 * 
 * --------------------------------------
**/

#ifndef MIDIDRVCE_H
#define MIDIDRVCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <math.h>
#include <usbdrvce.h>
#include <ti/info.h>

#define DEFAULT_LANGID 0x0409

typedef struct usb_interface_association_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bFirstInterface;
    uint8_t bInterfaceCount;
    uint8_t bFunctionClass;
    uint8_t bFunctionSubClass;
    uint8_t bFunctionProtocol;
    uint8_t iFunction;
} usb_interface_association_descriptor_t;

typedef struct audio_control_interface_header {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint16_t version; // MIDI version
    uint16_t wTotalLength;
    uint8_t  interfaces;
    uint8_t  interfaceNumber;
} audio_control_interface_header_t;

typedef struct midistreaming_interface_header {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint16_t version; // MIDI version
    uint16_t wTotalLength;
} midistreaming_interface_header_t;

typedef struct midistreaming_in_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bJackType;
    uint8_t bJackID;
    uint8_t iJack;
} midistreaming_in_descriptor_t;

typedef struct midistreaming_out_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bJackType;
    uint8_t bJackID;
    uint8_t bNrInputPins;
    uint8_t baSourceID;
    uint8_t baSourcePin;
    uint8_t iJack;
} midistreaming_out_descriptor_t;

typedef struct midistreaming_endpoint_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bNumEmbMIDIJack;
    uint8_t baAssocJackID;
} midistreaming_endpoint_descriptor_t;

typedef struct state {
    uint8_t root;
    uint8_t bend;
    uint8_t velocity;
    uint8_t voice;
    uint8_t channel;
    bool theme;
    int8_t octave;
    uint16_t pitchbend;
} state_t;

/**
 * @brief MIDI Event Cable Numbers
 * 
 */
enum {
    MIDI_CABLE0,
    MIDI_CABLE1,
    MIDI_CABLE2,
    MIDI_CABLE3,
    MIDI_CABLE4,
    MIDI_CABLE5,
    MIDI_CABLE6,
    MIDI_CABLE7,
    MIDI_CABLE8,
    MIDI_CABLE9,
    MIDI_CABLE10,
    MIDI_CABLE11,
    MIDI_CABLE12,
    MIDI_CABLE13,
    MIDI_CABLE14,
    MIDI_CABLE15
};

/**
 * @brief MIDI Channel Numbers
 * 
 */
enum {
    MIDI_CHANNEL0,
    MIDI_CHANNEL1,
    MIDI_CHANNEL2,
    MIDI_CHANNEL3,
    MIDI_CHANNEL4,
    MIDI_CHANNEL5,
    MIDI_CHANNEL6,
    MIDI_CHANNEL7,
    MIDI_CHANNEL8,
    MIDI_CHANNEL9,
    MIDI_CHANNEL10,
    MIDI_CHANNEL11,
    MIDI_CHANNEL12,
    MIDI_CHANNEL13,
    MIDI_CHANNEL14,
    MIDI_CHANNEL15
};

/**
 * @brief MIDI Event Code Index Numbers
 * 
 */
enum {
    MIDI_MISC_EVENT,
    MIDI_CABLE_EVENT,
    MIDI_SYSTEM_2BYTE,
    MIDI_SYSTEM_3BYTE,
    MIDI_SYSEX_STARTS,
    MIDI_SYSTEM_1BYTE,
    MIDI_SYSEX_ENDS_2BYTE,
    MIDI_SYSEX_ENDS_3BYTE,
    MIDI_NOTE_OFF,
    MIDI_NOTE_ON,
    MIDI_POLY_KEYPRESS,
    MIDI_CONTROL_CHANGE,
    MIDI_PROGRAM_CHANGE,
    MIDI_CHANNEL_PRESSURE,
    MIDI_PITCHBEND_CHANGE,
    MIDI_SINGLE_BYTE
};

static const usb_string_descriptor_t product_name = {
    .bLength = sizeof(product_name) + 20, // 20 includes length of .bString
    .bDescriptorType = USB_STRING_DESCRIPTOR,
    .bString = L"Calculator",
};

static const usb_string_descriptor_t manufacturer = {
    .bLength = sizeof(manufacturer) + 34, // 34 includes length of .bString
    .bDescriptorType = USB_STRING_DESCRIPTOR,
    .bString = L"Texas Instruments",
};

static usb_string_descriptor_t serial = {
    .bLength = sizeof(serial) + 32,
    .bDescriptorType = USB_STRING_DESCRIPTOR,
    .bString = L"0000000000000000",
};

static const usb_string_descriptor_t jack = {
    .bLength = sizeof(manufacturer) + 12,
    .bDescriptorType = USB_STRING_DESCRIPTOR,
    .bString = L"Output",
};

static const usb_string_descriptor_t *strings[] = { &product_name, &manufacturer, &serial, &jack };
static const usb_string_descriptor_t langids = {
    // .bLength = sizeof(langids),
    .bLength = 4,
    .bDescriptorType = USB_STRING_DESCRIPTOR,
    .bString = {
        [0] = DEFAULT_LANGID,
    },
};

static struct {
    usb_configuration_descriptor_t configuration;
    usb_interface_association_descriptor_t interface_association;
    usb_interface_descriptor_t interface0;
    audio_control_interface_header_t audio_header;
    usb_interface_descriptor_t interface1;
    midistreaming_interface_header_t midi_header;
    midistreaming_in_descriptor_t midi_in;
    midistreaming_out_descriptor_t midi_out;
    usb_endpoint_descriptor_t endpoint;
    midistreaming_endpoint_descriptor_t midi_endpoint;
} configuration1 = {
    .configuration = {
        .bLength = sizeof(configuration1.configuration),
        .bDescriptorType = USB_CONFIGURATION_DESCRIPTOR,
        .wTotalLength = sizeof(configuration1),
        .bNumInterfaces = 2,
        .bConfigurationValue = 1,
        .iConfiguration = 1,
        .bmAttributes = USB_BUS_POWERED | USB_NO_REMOTE_WAKEUP,
        .bMaxPower = 500 / 2,
    },
    .interface_association = {
        .bLength = sizeof(configuration1.interface_association),
        .bDescriptorType = 0x0B,
        .bFirstInterface = 0,
        .bInterfaceCount = 2,
        .bFunctionClass = 0x01,
        .bFunctionSubClass = 0x03,
        .bFunctionProtocol = 0,
        .iFunction = 0,
    },
    .interface0 = {
        .bLength = sizeof(configuration1.interface0),
        .bDescriptorType = USB_INTERFACE_DESCRIPTOR,
        .bInterfaceNumber = 0,
        .bAlternateSetting = 0,
        .bNumEndpoints = 0,
        .bInterfaceClass = USB_AUDIO_CLASS,
        .bInterfaceSubClass = 0x01, // Control Device
        .bInterfaceProtocol = 0, // Unused
        .iInterface = 0, // Optional string index
    },
    .audio_header = {
        .bLength = sizeof(configuration1.audio_header),
        .bDescriptorType = 0x24, // audio class interface
        .bDescriptorSubtype = 0x01, // header descriptor
        .version = 0x0100,
        .wTotalLength = sizeof(configuration1.audio_header), // TODO
        .interfaces = 0x01,
        .interfaceNumber = 0x01,
    },
    .interface1 = {
        .bLength = sizeof(configuration1.interface1),
        .bDescriptorType = USB_INTERFACE_DESCRIPTOR,
        .bInterfaceNumber = 1,
        .bAlternateSetting = 0,
        .bNumEndpoints = 1,
        .bInterfaceClass = USB_AUDIO_CLASS,
        .bInterfaceSubClass = 0x03, // MIDI Streaming
        .bInterfaceProtocol = 0, // Unused
        .iInterface = 2, // Optional string index
    },
    .midi_header = {
        .bLength = sizeof(configuration1.midi_header),
        .bDescriptorType = 0x24, // audio class interface
        .bDescriptorSubtype = 0x01, // header descriptor
        .version = 0x0100,
        .wTotalLength = sizeof(configuration1.midi_header) + 
                        sizeof(configuration1.midi_in) +
                        sizeof(configuration1.midi_out),
    },
    .midi_in = {
        .bLength = sizeof(configuration1.midi_in),
        .bDescriptorType = 0x24, // audio class interface
        .bDescriptorSubtype = 0x02, // MIDI IN jack descriptor
        .bJackType = 0x02,
        .bJackID = 0x02,
        .iJack = 0x04, // Optional string index
    },
    .midi_out = {
        .bLength = sizeof(configuration1.midi_out),
        .bDescriptorType = 0x24, // audio class interface
        .bDescriptorSubtype = 0x03, // MIDI OUT jack descriptor
        .bJackType = 0x01,
        .bJackID = 0x12,
        .bNrInputPins = 0x01,
        .baSourceID = 0x12,
        .baSourcePin = 0x01,
        .iJack = 0x04, // Optional string index
    },
    .endpoint = {
        .bLength = sizeof(configuration1.endpoint),
        .bDescriptorType = USB_ENDPOINT_DESCRIPTOR,
        .bEndpointAddress = USB_DEVICE_TO_HOST | 1,
        .bmAttributes = USB_BULK_TRANSFER,
        .wMaxPacketSize = 0x40,
        .bInterval = 0,
    },
    .midi_endpoint = {
        .bLength = sizeof(configuration1.midi_endpoint),
        .bDescriptorType = 0x25, // Audio class endpoint
        .bDescriptorSubtype = 0x01, // General Descriptor
        .bNumEmbMIDIJack = 1,
        .baAssocJackID = 0x12, // midi_out jack
    },
};

static const usb_configuration_descriptor_t *configurations[] = {
    &configuration1.configuration,
};

static const usb_device_descriptor_t device = {
    .bLength = sizeof(device),
    .bDescriptorType = USB_DEVICE_DESCRIPTOR,
    .bcdUSB = 0x0200,
    .bDeviceClass = 0,
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0,
    .bMaxPacketSize0 = 0x40,
    .idVendor = 0x0451, // Texas Instruments
    .idProduct = 0x1337,
    .bcdDevice = 0x0100,
    .iManufacturer = 2,
    .iProduct = 1,
    .iSerialNumber = 3,
    .bNumConfigurations = sizeof(configurations) / sizeof(*configurations),
};

static const usb_standard_descriptors_t midi_StandardUSBDescriptors = {
    .device = &device,
    .configurations = configurations,
    .langids = &langids,
    .numStrings = sizeof(strings) / sizeof(*strings),
    .strings = strings,
};

static usb_error_t midi_handleUsbEvent(usb_event_t event, void *eventData, usb_callback_data_t *callbackData) {
    usb_error_t error = USB_SUCCESS;

    if (event == USB_DEFAULT_SETUP_EVENT) {
        if (((usb_control_setup_t *)eventData)->bRequest == USB_GET_DESCRIPTOR_REQUEST &&
            ((usb_control_setup_t *)eventData)->wValue == 0x0200 &&
            ((usb_control_setup_t *)eventData)->wLength == sizeof(configuration1)) {

            usb_Transfer(usb_GetDeviceEndpoint(usb_FindDevice(NULL, NULL, USB_SKIP_HUBS), 0), &configuration1, sizeof(configuration1), 5, NULL);
            error = USB_IGNORE;
        }
    }

    return error;
}

typedef enum {
    MIDI_SUCCESS = 0,
    MIDI_ERROR_INVALID_PARAM = -1,
    MIDI_ERROR_USB_FAILED = -2,
    MIDI_ERROR_NOT_SUPPORTED = -3,
    MIDI_ERROR_INVALID_DEVICE = -4,
    MIDI_ERROR_INVALID_INTERFACE = -5,
    MIDI_ERROR_NO_MEMORY = -6,
    MIDI_ERROR_DEVICE_DISCONNECTED = -7,
} midi_error_t;

typedef struct {
    usb_error_t usb_error;
    uint8_t reserved[32];
} midi_device_t;

midi_error_t midi_Setup(midi_device_t *mididevice)
{
    const system_info_t *system = os_GetSystemInfo();

    for (uint8_t i = 0; i < 16; i++) {
        serial.bString[i] = 'A' + (system->calcid[i] >> 4);
        i++;
        serial.bString[i] = 'A' + (system->calcid[i] & 0xF);
    };

    if ( (mididevice->usb_error = usb_Init(midi_handleUsbEvent, NULL, &midi_StandardUSBDescriptors, USB_DEFAULT_INIT_FLAGS)) == USB_SUCCESS ) {
        usb_HandleEvents();
        return MIDI_SUCCESS;
    } else {
        usb_Cleanup();
        return MIDI_ERROR_USB_FAILED;
    }
}

midi_error_t midi_Send(midi_device_t *mididevice, void *bytes, size_t length) {

    usb_HandleEvents();

    mididevice->usb_error = usb_InterruptTransfer(usb_GetDeviceEndpoint(usb_FindDevice(NULL, NULL, USB_SKIP_HUBS), USB_DEVICE_TO_HOST | 1), bytes, length, 5, NULL);

    usb_HandleEvents();

    if (mididevice->usb_error == USB_SUCCESS) {
        return MIDI_SUCCESS;
    } else {
        return MIDI_ERROR_USB_FAILED;
    }
}

midi_error_t midi_NoteOn(midi_device_t *mididevice, uint8_t channel, uint8_t note, uint8_t velocity) {
    uint8_t midiEvent[4] = { MIDI_CABLE0 << 4 | MIDI_NOTE_ON, (uint8_t)(MIDI_NOTE_ON << 4 | (channel & 0x0F)), note, velocity }; // Note On
    return midi_Send(mididevice, &midiEvent, sizeof(midiEvent));
}

midi_error_t midi_NoteOff(midi_device_t *mididevice, uint8_t channel, uint8_t note, uint8_t velocity) {
    uint8_t midiEvent[4] = { MIDI_CABLE0 << 4 | MIDI_NOTE_OFF, (uint8_t)(MIDI_NOTE_OFF << 4 | (channel & 0x0F)), note, velocity }; // Note Off
    return midi_Send(mididevice, &midiEvent, sizeof(midiEvent));
}

midi_error_t midi_ProgramChange(midi_device_t *mididevice, uint8_t channel, uint8_t program) {
    uint8_t midiEvent[4] = { MIDI_CABLE0 << 4 | MIDI_PROGRAM_CHANGE, (uint8_t)(MIDI_PROGRAM_CHANGE << 4 | (channel & 0x0F)), program, 0x00 }; // Program Change
    return midi_Send(mididevice, &midiEvent, sizeof(midiEvent));
}

midi_error_t midi_ControlChange(midi_device_t *mididevice, uint8_t channel, uint8_t controller, uint8_t value) {
    uint8_t midiEvent[4] = { MIDI_CABLE0 << 4 | MIDI_CONTROL_CHANGE, (uint8_t)(MIDI_CONTROL_CHANGE << 4 | (channel & 0x0F)), controller, value }; // Control Change
    return midi_Send(mididevice, &midiEvent, sizeof(midiEvent));
}

midi_error_t midi_AllNotesOff(midi_device_t *mididevice, uint8_t channel) {
    return midi_ControlChange(mididevice, channel, 0x7B, 0x00); // All Notes Off
}

midi_error_t midi_Cleanup() {
    usb_Cleanup();
    return MIDI_SUCCESS;
}

#ifdef __cplusplus
}
#endif

#endif
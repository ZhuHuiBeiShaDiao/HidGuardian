/*
* Windows kernel-mode driver for controlling access to various input devices.
* Copyright (C) 2016-2018  Benjamin Höglinger-Stelzer
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once


// {0C320FF7-BD9B-42B6-BDAF-49FEB9C91649}
DEFINE_GUID(GUID_DEVINTERFACE_HIDGUARDIAN,
    0xc320ff7, 0xbd9b, 0x42b6, 0xbd, 0xaf, 0x49, 0xfe, 0xb9, 0xc9, 0x16, 0x49);

#define CONTROL_DEVICE_PATH         "\\\\.\\HidGuardian"
#define NTDEVICE_NAME_STRING        L"\\Device\\HidGuardian"
#define SYMBOLIC_NAME_STRING        L"\\DosDevices\\HidGuardian"

#define IOCTL_INDEX                 0x901
#define FILE_DEVICE_HIDGUARDIAN     32768U
#define MAX_DEVICE_ID_SIZE          0x400
#define MAX_INSTANCE_ID_SIZE        0xFF

//
// Used for inverted calls to get request information
// 
#define IOCTL_HIDGUARDIAN_GET_CREATE_REQUEST        CTL_CODE(FILE_DEVICE_HIDGUARDIAN,   \
                                                                    IOCTL_INDEX + 0x00, \
                                                                    METHOD_BUFFERED,    \
                                                                    FILE_READ_ACCESS | FILE_WRITE_ACCESS)

//
// Used to instruct driver to allow or deny request
// 
#define IOCTL_HIDGUARDIAN_SET_CREATE_REQUEST        CTL_CODE(FILE_DEVICE_HIDGUARDIAN,   \
                                                                    IOCTL_INDEX + 0x01, \
                                                                    METHOD_BUFFERED,    \
                                                                    FILE_WRITE_ACCESS)

#define IOCTL_HIDGUARDIAN_SUBMIT_SYSTEM_PID         CTL_CODE(FILE_DEVICE_HIDGUARDIAN,   \
                                                                    IOCTL_INDEX + 0x02, \
                                                                    METHOD_BUFFERED,    \
                                                                    FILE_WRITE_ACCESS)

#define IOCTL_HIDGUARDIAN_SUBMIT_NOTIFICATION       CTL_CODE(FILE_DEVICE_HIDGUARDIAN,   \
                                                                    IOCTL_INDEX + 0x03, \
                                                                    METHOD_BUFFERED,    \
                                                                    FILE_ANY_ACCESS)

#define IOCTL_HIDGUARDIAN_ARRIVAL_NOTIFICATION      CTL_CODE(FILE_DEVICE_HIDGUARDIAN,   \
                                                                    IOCTL_INDEX + 0x04, \
                                                                    METHOD_BUFFERED,    \
                                                                    FILE_ANY_ACCESS)


#include <pshpack1.h>

#pragma warning(push)
#pragma warning(disable:4200) // disable warnings for structures with zero length arrays.
typedef struct _HIDGUARDIAN_GET_CREATE_REQUEST
{
    //
    // Size of packet
    // 
    IN ULONG Size;

    //
    // Arbitrary value to match request and response
    // 
    IN ULONG RequestId;

    //
    // ID of the process this request is related to
    // 
    OUT ULONG ProcessId;

    //
    // Device ID
    // https://docs.microsoft.com/en-us/windows-hardware/drivers/install/device-ids
    // 
    OUT WCHAR DeviceId[MAX_DEVICE_ID_SIZE];
    
    //
    // Instance ID
    // https://docs.microsoft.com/en-us/windows-hardware/drivers/install/instance-ids
    // 
    OUT WCHAR InstanceId[MAX_INSTANCE_ID_SIZE];

    //
    // Buffer containing Hardware ID string
    // https://docs.microsoft.com/en-us/windows-hardware/drivers/install/hardware-ids
    // 
    OUT WCHAR HardwareIds[];

} HIDGUARDIAN_GET_CREATE_REQUEST, *PHIDGUARDIAN_GET_CREATE_REQUEST;
#pragma warning(pop)

typedef struct _HIDGUARDIAN_SET_CREATE_REQUEST
{
    //
    // Arbitrary value to match request and response
    // 
    IN ULONG RequestId;

    //
    // TRUE if WdfRequestTypeCreate is allowed, FALSE otherwise
    // 
    IN BOOLEAN IsAllowed;

    //
    // If TRUE, the decision will be cached in the driver for the current PID
    // 
    IN BOOLEAN IsSticky;

} HIDGUARDIAN_SET_CREATE_REQUEST, *PHIDGUARDIAN_SET_CREATE_REQUEST;

typedef struct _HIDGUARDIAN_SUBMIT_SYSTEM_PID
{
    // 
    // PID to always whitelist
    // 
    IN ULONG ProcessId;

} HIDGUARDIAN_SUBMIT_SYSTEM_PID, *PHIDGUARDIAN_SUBMIT_SYSTEM_PID;

#include <poppack.h>

/*
MIT License

Copyright (c) 2018 Benjamin "Nefarius" H�glinger

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#pragma once

#define REG_MULTI_SZ_AFFECTED_DEVICES       L"AffectedDevices"
#define REG_DWORD_FORCE                     L"Force"
#define REG_MULTI_SZ_EXCEMPTED_DEVICES      L"ExemptedDevices"
#define HIDGUARDIAN_HARDWARE_ID             L"Root\\HidGuardian"

NTSTATUS AmIAffected(PDEVICE_CONTEXT DeviceContext);
BOOLEAN AmIMaster(PDEVICE_CONTEXT DeviceContext);
VOID GetDefaultAction(PDEVICE_CONTEXT DeviceContext);

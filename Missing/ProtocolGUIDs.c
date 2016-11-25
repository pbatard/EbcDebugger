//
// Defines the GUIDs that are currently missing from gnu-efi.
//

#include <Uefi.h>

#include <Protocol/EbcVmTest.h>
EFI_GUID gEfiEbcVmTestProtocolGuid = EFI_EBC_VM_TEST_PROTOCOL_GUID;

#include <Protocol/ShellParameters.h>
EFI_GUID gEfiShellParametersProtocolGuid = EFI_SHELL_PARAMETERS_PROTOCOL_GUID;

#include <Protocol/DebuggerConfiguration.h>
EFI_GUID gEfiDebuggerConfigurationProtocolGuid = EFI_DEBUGGER_CONFIGURATION_PROTOCOL_GUID;

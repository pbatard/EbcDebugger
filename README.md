EbcDebugger - A standalone EBC Debugger
=======================================

This is a standalone version of the [EDK2's EBC Debugger](https://github.com/tianocore/edk2/tree/master/MdeModulePkg/Universal/EbcDxe/EbcDebugger)
that:
* Can be compiled without the cumbersome annoyance of having to use the EDK2, through the convenience of
  a Visual Studio 2015 project and [gnu-efi](https://sourceforge.net/projects/gnu-efi/)
* Can be compiled for x86_32, x86_64 and ARM targets
* Can be tested on the fly, through a [QEMU](http://www.qemu.org)+[OVMF](http://tianocore.github.io/ovmf/)
  UEFI virtual machine.

## Prerequisites

* [Visual Studio 2015](http://www.visualstudio.com/products/visual-studio-community-vs)
* [QEMU](http://www.qemu.org) __v2.7 or later__
  (NB: You can find QEMU Windows binaries [here](https://qemu.weilnetz.de/w64/))
* git

## Sub-Module initialization

For convenience, the project relies on the gnu-efi library, so you need to initialize the git
submodule either through git commandline with:
```
git submodule init
git submodule update
```
Or, if using a UI client (such as TortoiseGit) by selecting _Submodule Update_ in the context menu.

## Compilation and testing

If using Visual Studio, just press `F5` to have the application compiled and
launched in the QEMU emulator.

## Visual Studio and ARM support

To enable ARM compilation in Visual Studio 2015, you must perform the following:
* Make sure Visual Studio is fully closed.
* Navigate to `C:\Program Files (x86)\MSBuild\Microsoft.Cpp\v4.0\V140\Platforms\ARM` and
  remove the read-only attribute on `Platform.Common.props`.
* With a text editor __running with Administrative privileges__ open:  
  `C:\Program Files (x86)\MSBuild\Microsoft.Cpp\v4.0\V140\Platforms\ARM\Platform.Common.props`.
* Under the `<PropertyGroup>` section add the following:  
  `<WindowsSDKDesktopARMSupport>true</WindowsSDKDesktopARMSupport>`

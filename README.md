# writeable_root – make your Mac *yours* again!

Since macOS Big Sur the root directory is stored on a signed system volume (SSV), which "features a kernel mechanism that verifies the integrity of the system content at runtime, and rejects any data — code and non-code — that doesn’t have a valid cryptographic signature from Apple".
In short, this means that you cannot make changes wherever you want in your file system anymore, which sucks.
While it is still possible to edit the protected directories, the steps required take too long for my taste, so I created a short program that performs the necessary commands automatically.

## prerequisites
There are some things you have to do before you can use this program.
Follow these steps:
* disable FileVault in System Preferences > Security & Privacy > FileVault
* enter the recovery mode by holding command + R during startup
* disable SIP and authenticated root by running `csrutil disable` and `csrutil authenticated-root disable` in the recovery terminal.
* reboot into your normal user

## build & run
Build the program using `clang writeable_root.c -o writeable_root` and run it with `./writeable_root`.
That's it!
The program will create a new directory under ~/temp where the root directory gets temporarily mounted.
Make your desired changes there (shell will spawn in the appropriate folder) and exit the shell when you're done.
The system will reboot, as this is necessary to perform changes to the "actual" root directory.

## info
It's recommended to turn SIP and FileVault back on after performing your changes.
Please be careful when making changes in the root directory!
Use at your own risk.

# Serious Sam Alpha Remake

This is the **official source code** repository for **Serious Sam Alpha Remake** modification. This mod has now been discontinued and the last change to the code has been made on August 20th, 2020.

It is based on the original SDK for **Serious Sam: The First Encounter v1.05** by Croteam.

## What is Serious Sam Alpha Remake?

Alpha Remake is a mod which attempts to recreate the experience of Serious Sam Alpha (known as "Sam2000" or "Evaluation Build") based on code leftovers as well as ported assets from the Alpha build itself.
The mod also includes levels from the aforementioned build with necessary critical fixes and the addition of a campaign mode.

# Building

To build the source code, you need to use **Microsoft Visual C++ 6.0**. You can get an unofficial portable version from here: https://github.com/itsmattkc/MSVC600

1. Clone the repository in any place. For example: `C:\SeriousSamTFE\Mods\AlphaRemake\Sources`.
2. Add a new `ENGINE_DIR` environment variable to your system and specify a directory to your mod folder **without a slash at the end**. For example: `C:\SeriousSamTFE\Mods\AlphaRemake`.
3. Open `Sources.dsw` workspace in the IDE to begin working with the code and building it.

The built DLL files will be automatically copied into `$(ENGINE_DIR)\Bin` (or into `$(ENGINE_DIR)\Bin\Debug` under Debug).

# License

Both **Serious Sam Alpha Remake** source code and [**Serious Engine 1**](https://github.com/Croteam-official/Serious-Engine) are licensed under GNU GPL v2 (see LICENSE file).

# Screenshots
<img src="https://i.imgur.com/CtYbfBH.png">
<img src="https://i.imgur.com/I3R5cWH.pngg">

# Serious Sam Alpha Remake

This is the **official source code** repository for **Serious Sam Alpha Remake** modification. This mod has now been discontinued and the last change to the code has been made on August 20th, 2020.

It is based on the original SDK for **Serious Sam: The First Encounter v1.05** by Croteam.

## What is Serious Sam Alpha Remake?

Alpha Remake is a mod which attempts to recreate the experience of Serious Sam Alpha (known as "Sam2000" or "Evaluation Build") based on code leftovers as well as ported assets from the Alpha build itself.
The mod also includes levels from the aforementioned build with necessary critical fixes and the addition of a campaign mode.


# FAQ
<details>
<summary>Click to show more</summary>
  
## Is the mod really discontinued? No more updates?

Yes, this iteration of AR has been marked as obsolete and discontinued however, this is **NOT** the end of the overall project.
Alpha Remake takes a fresh start on an improved fork of **Serious Engine 1.10** with huge ambitions that are yet to be realized.
A new project title will be announced sometime in the future, to reflect better the taken direction.
Of course, the goal remains - to recreate the experience of the Alpha, with addition of modern enhancements.

## The new Alpha Remake will be open-sourced as well?

Of course! Once the development is declared finished, the new repository will be made public.

## Do you have older versions of Alpha Remake?

This repository has all release versions, starting from GRO sound and model replacement mod through MOD for The Second Encounter, finishing on MOD for The First Encounter. Each release has its changelog, installation guide, and optional patches.

## But wait... I thought there was Alpha Remake's official source code available for a while, right?

Well, it's story-time.

Somewhere in 2021, I've been developing the "1.6" update for the now obsolete AR. I ran into some obstacles that could not figure out by myself, so I sought help from a known Modder of Classic Serious Sam.
We had a good conversation. Modder offered help if I'd share source code to work on. I did that, with a kind request to **NOT LEAK** it anywhere, as it was not ready to be made public.
It looks like the promise has been broken, as in 2022, a Linux port appeared out of nowhere, where after downloading it I could recognize right away my codebase.

The Modder probably shared the source code with several people, including the author of the Linux port. Too bad.
That was when I had personal problems and didn't have time to deal with them. But now I'd like to clarify: the Linux port is **NOT an official source code**.

## Where I can follow the development of new Alpha Remake?

Check out my Itch.io blog for devlogs and additional previews of new project.
</details>

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

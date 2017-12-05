# GameBoi
 GameBoi is a Game Boy emulator made as a personal project during the third semester of the programming track of at the University of Central Florida's (UCF) [Florida Interactive Entertainment Academy (FIEA)](https://fiea.ucf.edu).
 
This is a work in progress. Below is a list of Developer Diaries for each week, a rough schedule that will be updated as I go along, and links to resources that I've been using.

Note that the Dev Diaries are not intended to explain the Game Boy hardware; links for that can be found in the referenes section. This is intended to describe my process for creating the emulator and any obstacles I ran into along the way.

## Notes for Visitors
This is more or less the final version of this project. Anyone should be able to download the source and build it. Here are some notes you might need to follow:
* The solution file is located in [builds/GameBoi.sln](https://github.com/evanbbass/GameBoi/tree/master/builds).
* Project files are located in their respective folders under the source folder.
* Due to SFML version requirements, **this project must be built in Visual Studio 2015**.
* SFML itself does not need to be installed anywhere as NuGet will automatically download it when building.
* Unfortunately the unit test project must be built with Visual Studio 2017, although there isn't really a reason for anyone else to need to build that project.
* I uploaded a [pre-built version](Final Build/Final Build.zip) for anyone who doesn't want to deal with building. Instructions on how to run it are included in the .zip file.

The Dev Diaries below document my process through development of the emulator. Included is a link to my final presentation slides showing the final state of the project.

## Dev Diaries
Check out my Dev Diaries!
* [Week 1](docs/DevDiaries/Week1.md)
* [Week 2](docs/DevDiaries/Week2.md)
* [Week 3](docs/DevDiaries/Week3.md)
* [Week 4](docs/DevDiaries/Week4.md)
* [Week 5](docs/DevDiaries/Week5.md)
* [Week 6](docs/DevDiaries/Week6.md)
* [Week 7](docs/DevDiaries/Week7.md)
* [Week 8](docs/DevDiaries/Week8.md)
* [Week 9](docs/DevDiaries/Week9.md)
* [Final Presentation Slides (.pptx)](docs/Resources/Final.pptx)

## Schedule
This was the final schedule.
* Week 1 - Set up memory map, registers, and basic CPU hardware structures
* Week 2 - Set up opcode interpreter/disassembler
* Week 3 - Implement opcodes
* Week 4 - Create debugger first pass
* Weeks 5-6 - Interrupts, Timers, Input, and first-pass GPU
* Week 7 - Final pass on graphics and GPU
* Week 8 - Hunt down and kill various breaking bugs
* Week 9 - Add full support for MBC cartridges, bug fix, and polish
* Possible future additions (not part of PPP)
  * Audio
  * Game Boy Color support
  * Super Game Boy features if time permits

## References:
* [Cinoop (Article about creating a Game Boy emulator)](https://cturt.github.io/cinoop.html)
* [Game Boy Hardware Documentation](http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf)
* [Opcode Summary](http://gameboy.mongenel.com/dmg/opcodes.html)
* [Alternate Opcode Chart](http://pastraiser.com/cpu/gameboy/gameboy_opcodes.html)
* [Detailed Hardware Descriptions](http://www.codeslinger.co.uk/pages/projects/gameboy.html)

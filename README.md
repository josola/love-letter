# Missive
### A text based card game inspired by the wildly popular card game Love Letter.

Missive is written entirely in the C++ programming language. The developer's intention for this project was to
learn how to write clean, easy to read, and reusable object oriented code using C++, while creating a usable product
in the process.

Development on Missive began purely as a Love Letter clone in text format, this is where branch one comes into play.
Branch one of this repository contains the intial program design and is a 99% working version of the game.
The style used in this branhc is mostly procedural, leaving the developer with a version of the game that worked, but
was difficult to modify due to its design style. When the power of cleanly written object oriented code presented its potential,
a rewrite was immediately started in branch two.

Branch two contains the most current version of the Missive game. Written entirely in object oriented style, with clean and easy to read
design paradigms. This branch is currently in development and does not represent the finished game, for the finished game you can compile
and run branch one.

Developed using Visual Studio, Visual Studio Code, and XCode on the Mac, Windows, and Ubuntu (linux) platforms. The procedural version
"branch 1" was designed primarly to run on Windows based operating systems, as it has elements that clear the terminal screen between
player turns that work on windows.

All instructions on how to play the game are given to players as they play the game, like a texted based adventure game.

To try this program on your own system, clone this repository to your IDE of choice. Then simply compile and run the program.
For branch two "the object oriented rewrite" your include directories should look both in the src folder AND the card folder.
Single use responsibility has increased the number of source files needed to run this project, thus a seperate folder for just the card
classes had been added.

**All code within this program uses the MIT software license. Written by Jordan Sola 2019 - 2020**

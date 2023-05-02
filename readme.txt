Type make to compile all the C files and start the program. An executable named exec will be created.

The librairies SDL2 (and its extension SDL2_image) and FMOD are used. 
FMOD need to be dowloaded from their website, but the files are already included in the fmodex/lib directory of this project. 
What you should do is to copy the content of the folder (.so files) corresponding to your computer into your /usr/lib directory (which permissions are protected by default). We did not find an other way to make this work. Once its done, the makefile correctly links everything.

Our simulation looks better after after a few minutes (a few train passages), once passengers are more dispatched. 

We ran out of time to add passenger quitting the station after going out of the train, which is a pity because it was almost the same process as the one to make them come, even easier, but still we are happy with what we have done. We had some ideas to add improvements so we will certainly complete our work in the future anyway.

Thank you Mr François for giving us this project!


Ozouf Jonathan & DESCHAMPS Aymeric 
ESIEA - Class 30 
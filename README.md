# PKTeach
PKTeach Software for Pro-Arm 2200 Robot (Now with the PKTEACH.exe binary and a PDF documentation file!)

(Source Code now uploaded after almost 3 years!)

The Unintersting History of PKTeach

Back in the 1980s I was working as a software developer and a systems integrator aiding a training company to provide robotics training to automotive employees in the Detroit area. Pro-Arm 2200 robots were purchased, and not being satisifed with the software that came with it (it was pretty ugly!) I spent a long weekend and wrote a program called PKTeach. After several updates and improvements, the software not only looked much better on the screen than the original BASIC program that was originally provided with the robot, but it also functioned better as it tried to account for the inconsistencies that are introduced by the Pro-Arm 2200 robot due to the fact that it lacks a feedback loop. This software worked out quite well and ultimately was used in all of the labs we established that utilized the Pro-Arm robot.  

At one point during the life of PKTeach I mailed a copy of the software to Marcraft International, which was marketing the Pro-Arm 2200 robot world wide. That began a long relationship between myself and the people at Marcraft, starting with the packaging of this software with most (or was it all?) of their sales of the robots and their training modules. 

In August of 2019, a man by the  name of Brent Crump tracked me down on the internet to inquire as to what had happened to the PKTeach software. Well, as luck would have it, I tend to preserve things and digging through my archives I located a number of useful items:

1) The PKTeach binary file
2) The source code to the PKTeach software
3) Many of the libraries used to build the software
4) An old copy of a Borland pascal compiler from which I built the software

Brent was already working on his own python adaptation of the software, but as long as he had found me, and as long as I had located the original files, I decided that I would open source this software under the very permissive MIT license. You need to read the very simple license agreement in order to understand its restrictions, but basically (and what follows here is NOT a contract nor an "overriding" of the MIT license. In the case that anything I say here conflicts with the MIT license, the MIT license takes precedence) you get to do with the software pretty much what you want, so long as you preserve the copyright notices in the files, and agree to hold me personally harmless for any issues arising from the use, misuse or lack of usability of the software. 

Retranslated: Please give attribution to me for writing the software and making it available to you for free, and please don't be so rude as to try to sue me if it doesn't do what you think it ought to do. You use this software at your own risk. Also, I ask that you also give attribution to Marcraft for their central role in the distribution of both the robot and the software. They have also been very kind in making available resources for the robot and the software and fully support the open sourcing of this software.

Please note that while my time is limited, I am happy to help anyone as much as I am able who would like to know more about the software or perhaps are working on their own version of the software. 

I *may* have all of the components to rebuild the software, but at the moment I'm afraid I just don't have the time to embark on such a project. If there is interest I might do so at some point in the future, but for now feel free to use the binaries and peruse the source code, and to make use of the documentation posted here as well. 

Regarding the binaries: 
1) The PKTeach binary posted here is a 16-bit DOS executable and as such, will NOT run under any 64-bit version of windows. 
2) The binary "talks" to the robot via the parallel port. You'll have to figure out the hardware side of things in today's virtualized hardware environment. If anyone comes up with a method to make this work, contact me via isshomefront.com (use the "contact us" feature) and I'll post your solution here for everyone else to see.
3) As I build up this repository, I'll add information about what tools were used to build it, though you probably don't have access to them. Even so, I'll document what I can...you never know what will be useful to somebody. 
4) It appears that at least SOME of the libraries I used to build this software may have been open sourced as well. If I can track that information down and it proves to be true, I'll provide links to that open source software. This all assumes that I am able to get the source code uploaded in a reasonable amount of time.  :)

Please note that all of the source code and related files are Copyright (C) 2022 by Peter S. Lee, all rights reserved, with the only exception being the manual PDF which is copyright by it's respective copyright holder. 

It makes me happy to know that something I wrote over 26 years ago is still found to be useful to a set of people today. I hope this respository ends up being of some use to you. 

Peter S. Lee

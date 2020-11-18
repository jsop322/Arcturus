# Review form for project strategy-3


## 1. Overall design and functionality (0-6p)

  * 1.1: The implementation corresponds to the selected topic and
scope. The extent of project is large enough to accommodate work for
everyone (2p)

The implementation corresponds to the selected topic and scope very well.  
The extent of the project is fairly large and work could be well accommodated for everyone.  
2p.


  * 1.2: The software structure is appropriate, clear and well
documented. e.g. class structure is justified, inheritance used where
appropriate, information hiding is implemented as appropriate. (2p)

Overall the software structure is fairly appropriate and clear as well as documented well with diagrams. The inheritance structure is well justified and used. Some useful comments below.  
The code introduces hard coding in the sense that game parameters are not in a common place where they would be easily adjustable.  
Some of the comments in the code are self-explanatory and thus really unnecessary.  
2p.


  * 1.3: Use of external libraries is justified and well documented. (2p)

The usage of SFML is justified and documented well enough. Also the used SFML AnimatedSprite was clearly justified.  
2p.


## 2. Working practices (0-6p)

  * 2.1: Git is used appropriately (e.g., commits are logical and
frequent enough, commit logs are descriptive). (2p)

Commits are frequent and kind of logical. Some branching with merging strategy is used and merges are done in somewhat appropriate places.  
The commit messages could be generally more informative and the master branch could be cleaner in the sense that manual testing could happen in different branches for example.  
1.5p.


  * 2.2: Work is distributed and organised well. Everyone contributes to
the project and has a relevant role that matches his/her skills. The
distribution of roles is described well enough. (2p)

The distribution of roles is described well in the project plan and documentation. Everyone has been contributing to the project and work is logged very well.  
2p.


  * 2.3: Quality assurance is appropriate. Implementation is tested
comprehensively and those testing principles are well documented. (2p)

Testing is documented to be mainly manual, which is for the most part fair enough for a project like this. However, no testing code exists.  
1p.



## 3. Implementation aspects (0-8p)

  * 3.1: Building the software is easy and well documented. CMake or
such tool is highly recommended. (2p)

A Makefile is used to build the project. This is the most plain approach and works well in most cases. On a side note, a build tool or a robust hierarchy of Makefiles could be preferable when building bigger projects.  
2p.


  * 3.2: Memory management is robust, well-organised and
coherent. E.g., smart pointers are used where appropriate or RO3/5 is
followed. The memory management practices should be documented. (2p)

No obvious memory management issues are present. Fair usage of smart pointers. Of course, R0/3/5 could have been used more thoroughly.  
1.5p.


  * 3.3: C++ standard library is used where appropriate. For example,
containers are used instead of own solutions where it makes sense. (2p)

STL containers and functions are properly used where approrpiate.  
2p.


  * 3.4: Implementation works robustly also in exceptional
situations. E.g., functions can survive invalid inputs and exception
handling is used where appropriate. (2p)

Implementation works robustly in the sense that the program does not crash when it is executed in the way that its documented.  
However, the code does not do error handling in the sense that functions can fail when given invalid input and every exception is not thoroughly thought of.  
1.5p.



## 4. Project extensiveness (0-10p)

  * Project contains features beyond the minimal requirements: Most of
the projects list additional features which can be implemented for
more points. Teams can also suggest their own custom features, though
they have to be in the scope of the project and approved by the course
assistant who is overseeing the project. (0-10p)

Minimum requirements are fulfilled. When evaluationg the additional features, things that are considered in this section are the short time frame of the project and the fact that the additional features can become huge different components in a larger project.  
That is, all the additional and advanced features combined make this project pretty extensive.  
9.5p.




## 5. Project plan (0-3p)

The project plan is good, it explains the game and the motivation of the project well in detail.  
3p.



## Total

30p

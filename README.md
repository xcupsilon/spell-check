## Description
This repository contains my program (dictionary.c) wrote for pset5, cs50x. Presumably, it, together with other programs in the folder, checks for "mispelled" words by iterating through an input of text file and trying to match the words extracted from the input file with a user input of dictionary (optional, if no input then program turns to use the default dictionary). In fact, the main function as described is implemented through speller.c, a program wrote by cs50x staffs and given to me. The program I implemented focuses on loading the dictionary into trie data structure, checking for the dictionary's size, spell checking word(s) by iterating through the tries and checking the bool condition in the bottom trie to see if the word exists in the dictionary or not, and lastly, unloading the tries by freeing the dynamically allocated memories.

This by far the hardest programming task I've been assigned and accomplished, spending about 7 hours to finish. It combined most if not all accumulated tools and theories taught in the online lecture, making people have to understand them beyond a shallow level in order to utilize them to fulfill the pset's requirement. After toils and headaches I eventually pushed through!! Don't give up now.

## Usage
```python
$ make speller
$ ./speller [dictionary] text # dictionary being a line-dilimited file containing words, text being any txt files
```

## What I have learned
* Implementation of data structures: tries and linked lists in C using pointers
* Application of custom types
* Heavy usages of file pointers

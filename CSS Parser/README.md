# CSS Parser
CSS Parser written as an assignment job. It is able to parse CSS, but checks only syntax (Existence of various HTML tags is not checked). It uses hand-written containers, which is generally bad, cause there are some
bugs, which I couldn't track

## Implementation
This algorithm uses classic Token approach which lets us check file very easily and very effectively. It uses 2 parsers: **CSS Parser** and **Selector Parser**. This was made to separate general CSS logic from selector logic
just to make code easier to read and maintain. Program gives you as well command interface to load file and check various things, just type help to check available commands

## Bugs
Program did not pass few stricts test. I don't know why this happened, but i think that list implementation might have a flaw. Also not gonna lie, but all these data structures were written really fast
due to the deadline.

## Further Development
No further development of this code is planned, still this is good foundation if you need something more practical, just use STL containers, not my implementations

# Remorse-Code

## A joke program which can translate to and from multiple iterations of morse code

As an example, the letter 'A' translated to morse code yields the combination: `.-`

Similarly, the very symbols that make up said combination, `.` and `-`, have combinations of their own. 
Thus, translating `.-` to morse code yields `.-.-.- -....-`. 

So "A" translates to `.-` which translates to `.-.-.- -....-`. You can choose to reiterate this process as many times as you like.

This program allows you to translate to and from Remorse Code with any number of iterations. Translating from remorse code automatically translates to the original message, regardless of how many layers of iteration obscure it.

This program is riddled with `system()` calls so probably don't run it on a government PC.

![Output](https://cdn.discordapp.com/attachments/405128309069053957/779100521990324234/unknown.png)

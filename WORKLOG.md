# Work Log

## Jonathan Shavit
[I'll fix capitalization at the end]
### May 17, 2023

- cloned the repo, started filling out the worklog.
- made my branch (JonathanShavit)
- gonna do some research now [links tba]
https://www.techtarget.com/searchsecurity/definition/cipher-block-chaining

### May 18, 2023

- still researching a bit
- ~~i think i can start doing a little coding tonight~~ or maybe not. i ran out of time
https://www.sciencedirect.com/topics/computer-science/cipher-block-chaining
https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation

### May 19, 2023

- couldn't do anything in class, since I had an AP
- besides that, i didn't do much. I'm still trying to make sense of what I found in the last few days

### May 20, 2023

- ok I think CBC makes sense to me now. I'm just unclear on what kind of encryption they use on the blocks themselves
https://www.techtarget.com/searchsecurity/definition/Electronic-Code-Book
https://www.geeksforgeeks.org/block-cipher-modes-of-operation/#

### May 21, 2023

- sunday is the day of rest. plus, i'm pretty sure the "work every day" rule only applies to homework days.
- besides that i read more on cbc (rereading the wikis, etc.)

### May 22, 2023

- ok i can't figure out how the blocks are actually encrypted. none of the cbc tutorials say anything, they just say "aes encryption"
- i found a whole buch of sites but they all say the same thing as the rest. i'll add them here but not below
- well i hit the half hour mark and i got nuthin so i'll call it a day
- i know i should probably ask for help but i can't bring myself to do that
- oops i forgot to add the decoder i started to work on (it's just an outline at this point)

https://www.ibm.com/docs/en/linux-on-systems?topic=operation-cipher-block-chaining-cbc-mode
https://www.sciencedirect.com/topics/computer-science/cipher-block-chaining
https://xilinx.github.io/Vitis_Libraries/security/2020.1/guide_L1/internals/cbc.html
https://www.educative.io/answers/what-is-cbc

### May 23, 2023

- OH, that's what AES meant. I feel silly. The text is kind of dense though, it might take a while to understand it
- I just read through more of the AES wiki
https://en.wikipedia.org/wiki/Advanced_Encryption_Standard

### May 24, 2023

- AES might be too hard to crack. maybe we could do DES instead?
- started learning about DES encryption (a lot of reading to do lol)

https://en.wikipedia.org/wiki/Data_Encryption_Standard
https://en.wikipedia.org/wiki/DES_supplementary_material

### May 25, 2023

- Realized a cracker is not feasible. Mr. K okayed an encoder/decoder
- continued reading up on the algorithm. it kind of makes sense but i can't make sense of the chart.
- Started on the ReadMe and Lesson Slides (Presentation)

### May 26, 2023

- I found some videos that help me understand DES a bit better
- I worked on the presentation a bit more

https://www.youtube.com/watch?v=S918rR4VdqQ&ab_channel=Simplilearn
https://www.youtube.com/watch?v=cVhlCzmb-v0&ab_channel=ChiragBhalodia
https://www.youtube.com/watch?v=FGhj3CGxl8I&ab_channel=Computerphile

### May 27, 2023

- Coding Start!
- Made a version of the expander that works on bytes instead of bits (to help me understand the algo)
- started working on the real expander (not working just yet, might be an issue with my bit shifting, but i'll look at it in the morning)

### May 28, 2023

- fixed expander
- wrote alternate version of expander
- tested expanders and found that they behave funky when printing uless i make them unsigned, and so changed that

### May 29, 2023

- started on the s-boxes (not yet tested)

### May 30, 2023

- added new versions of expander and s-box methods that use bytes (pretending to use bits) instead of actually using bits (why did i even suffer by making them then?)
-  removed old versions to save space (even though it hurts to see them go)
- still need to finish testing tho

### May 31, 2023

- updated s-box so it uses a new s-box for each block (i thought it was per round, but this makes more sense with the literature)

https://csrc.nist.gov/csrc/media/publications/fips/46/3/archive/1999-10-25/documents/fips46-3.pdf

### Jun 1, 2023

- worked on the presentation

https://www.lri.fr/~fmartignon/documenti/systemesecurite/4-DES.pdf

### Jun 2, 2023

- worked more on the presentation

### Jun 3, 2023

- a bit of work on the homework (just setting up a plan) and readme
- more work on the presentation

### Jun 5, 2023

- merge and cleanup


## GROUP MEMBER 2
### May 18th, 2023
Cloned repo
Started research into CBC implementation.
### May 19th, 2023
Research shows that working on CBC implememtation is not feasible.
Began work on ECB encoder.


### May 25th, 2023
Wrote the first part of an DES cipher.

### May 27th, 2023
Created the permutation 1 for the key.

### May 28th, 2023
Created initial permutation table and key permuation table.
Made key compression.
Made ip permuation.
Made method to shift arrays.

### May 29th, 2023
made methods that would divide both the key and the text.
Made a method to expand the right side of cipher

### May 30th, 2023
Created tables.h
Wrote the xoring of key
Rewrote the expansion method using the correct model.

### May 31st, 2023
Wrote the sbox subsitiution.
Made the necessary xor operations

### June 1st, 2023
Finished encryptor

# Sites Consulted

https://www.techtarget.com/searchsecurity/definition/cipher-block-chaining
https://www.sciencedirect.com/topics/computer-science/cipher-block-chaining
https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation
https://www.techtarget.com/searchsecurity/definition/Electronic-Code-Book
https://www.geeksforgeeks.org/block-cipher-modes-of-operation/#
https://en.wikipedia.org/wiki/Advanced_Encryption_Standard
https://en.wikipedia.org/wiki/Data_Encryption_Standard
https://en.wikipedia.org/wiki/DES_supplementary_material
https://www.youtube.com/watch?v=S918rR4VdqQ&ab_channel=Simplilearn
https://www.youtube.com/watch?v=cVhlCzmb-v0&ab_channel=ChiragBhalodia
https://www.youtube.com/watch?v=FGhj3CGxl8I&ab_channel=Computerphile
https://www.lri.fr/~fmartignon/documenti/systemesecurite/4-DES.pdf
https://csrc.nist.gov/csrc/media/publications/fips/46/3/archive/1999-10-25/documents/fips46-3.pdf

# ste2
A **S**imple **T**ext **E**ncoder. Nothing really fancy.
# Compiling
You can use **gcc** to compile the code, to do so simply run:
```sh
g++ -o encode encode.cpp --static && g++ -o decode decode.cpp --static
```
I haven't tested it with other compilers, but it should work (it's a simple 1 file (well 2 technically) project).
# How does it works?
If you know how base64 works, then you'll see some similarities between how both encoders works; in fact, I just learned how base64 worked and then wanted to create my own encoder, so I basically created it using what I knew from base64.

Let's say you have a string, for example: `Hi!`.\
Now, convert it to binary: `01001000 01101001 00100001`.\
Next, remove all of the spaces: `010010000110100100100001`.\
Then, split the string in pairs of 2 characters: `01 00 10 00 01 10 10 01 00 10 00 01` (That's where the "2" in "ste2" comes from).

Then, map each pairs of characters to their corresponding letter with this:
| Pair | Letter |
|:----:|:------:|
| 00 | A |
| 10 | B |
| 01 | C |
| 11 | D |

So:
```
01 = C
00 = A
10 = B
00 = A
01 = C
10 = B
10 = B
01 = C
00 = A
10 = B
00 = A
01 = C
```
Which gives us the following encoded string: `CABACBBCABAC`\
So, `Hi!` turns into `CABACBBCABAC` after being encoded

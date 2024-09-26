# ste2
A **S**imple **T**ext **E**ncoder. Nothing really fancy.
# Compiling
You can use **gcc** to compile the code, to do so simply run:
```sh
g++ -o encode encode.cpp --static && g++ -o decode decode.cpp --static
```
I haven't tested it with other compilers, but it should work (it's a simple 1 file (well 2 technically) project).
# Encode/decode text
Encoding and decoding text is pretty easy: simply use "encode" to encode the text with: 
```sh
./encode Text to encode
```
For decoding a text, you can use "decode":
```sh
./decode CACACBCCCBADCBDDCBCACBCCCBCAABACABAA
```
# Encode/decode files
You'll need to use the "-f" argument to encode and decode a file. To encode a file, use this, where "filename" is the name of the file you want to encode:
```sh
./encode filename
```
This will output the text directly to the terminal, but you can use some bash magic to output it to a file instead, ex: encoded.txt
```sh
./encode filename > encoded.txt
```
Do decode a file, you can use "decode" with the "-f" argument like so, using outputfile as the file that will get written:
```sh
./decode -f CBBACBBCABACABAA outputfile
```
If you do not specify an output file, it will write the output to "decoded.bin" by default.
You can, again, use some bash magic to decode from a file:
```sh
./decode -f "$(cat encoded.txt)" decoded
```

If, for example, you want to encode and decode a program named "hi", you do something like this:
```sh
./encode -f hi > encoded.txt

./decode -f "$(cat encoded.txt)" decodedHi
chmod +x decodedHi
```
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
So, `Hi!` turns into `CABACBBCABAC` after being encoded.
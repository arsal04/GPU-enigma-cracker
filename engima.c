#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Defining rotor wirings
// Citation: German Railway (Rocket) https://en.wikipedia.org/wiki/Enigma_rotor_details
char* ROTORS[27] = {"JGDQOXUSCAMIFRVTPNEWKBLZYH", 
                 "NTZPSFBOKMWRCJDIVLAEYUXHGQ",
                 "JVIUBHTCDYAKEQZPOSGXNRMWFL",
                 "QYHOGNECVPUZTFDJAXWMKISRBL",
                 "QWERTZUIOASDFGHJKPYXCVBNML"};

char* ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Perhaps convert to hashmap

// The rotors are ordered in terms of rotation frequency from fastest to slowest, right to left.
typedef struct settings {
    int rotor_order[3];
    int rotor_offset[3];
} 
settings_t;


char map(char current_char, char* current_rotor) {
    for (int i = 0; i < 26; i++) {
        if (current_char == ALPHABET[i]) {
            return current_rotor[i];
        }
    }

    return '0';
}

char* encrypt(char* text, settings_t* setting) {

    
    // Get length of message
    int text_length = strlen(text);

    int* placed_rotors = setting->rotor_order; 
    int* rotor_offset = setting->rotor_offset;

    // Encrypt each character
    char current_char;
    for (int c = 0; c < text_length; c++) {
        current_char = toupper(text[c]);

        // Increment the rotor
        rotor_offset[0]++;
        if (rotor_offset[0] >= 26) {
            rotor_offset[0] = 0;
            rotor_offset[1]++;
        }
        if (rotor_offset[1] >= 26) {
            rotor_offset[1] = 0;
            rotor_offset[2]++;
        }
        if (rotor_offset[2] >= 26) {
            rotor_offset[0] = 0;
        }

        // Pass through each rotor
        for (int rotor = 0; rotor < 1; rotor++) {
            
            // Pass through rotor
            char* current_rotor = ROTORS[placed_rotors[rotor]];
            current_char += rotor_offset[rotor];
            current_char = map(current_char, current_rotor);

        }


        text[c] = current_char;
    }

    // Return encrypted text
    return text;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Incorrect number of args");
        exit(1);
    }

    // Take input
    char* text = malloc(strlen(argv[1]));
    memcpy(text, argv[1], strlen(argv[1])); 

    // Define rotor settings
    settings_t* setting = malloc(sizeof(settings_t));
    for (int i = 0; i < 3; i++) {
        setting->rotor_order[i] = i;
        setting->rotor_offset[i] = 0;
    }


    char* cipher_text = encrypt(text, setting);

    printf("%s\n", cipher_text);


    free(text);
}
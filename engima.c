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
    // Increasing index ordered slow to fast rotor
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

/**
 * Encrypts each character of a given string using thr provided initial settings
 * Stores the encrypted text back into `text`. 
 * `text` must be dynamically allocated memory
 */
char* encrypt(char* text, settings_t* setting) {

    // Get length of message
    int text_length = strlen(text);

    int* rotor_order = setting->rotor_order; 
    int* rotor_offset = setting->rotor_offset;

    // Encrypt each character
    char current_char;
    for (int c = 0; c < text_length; c++) {
        current_char = toupper(text[c]);


        // Pass through each rotor (slowest to fasted)
        for (int r = 2; r >= 0; r--) {
            
            // Pass through rotor
            char* current_rotor = ROTORS[rotor_order[r]];
            
            // Account for starting offset
            current_char += rotor_offset[r];

            // Pass character through the rotor
            current_char = map(current_char, current_rotor);
        }

        // Increment the first rotor
        rotor_offset[0]++;
        if (rotor_offset[0] >= 26) {
            rotor_offset[0] = 0;
            rotor_offset[1]++;
        }
        // If full rotation increment the second rotor
        if (rotor_offset[1] >= 26) {
            rotor_offset[1] = 0;
            rotor_offset[2]++;
        }

        // If full roation then reset third rotor
        rotor_offset[2] %= 26;

        // Chose to ignore reflector because it dosen't make sense without a plugboard
        // // Pass back through each rotor (fastest to slowest)
        // for (int r = 0; r >= 2; r++) {
            
        //     // Pass through rotor
        //     char* current_rotor = ROTORS[placed_rotors[r]];

        //     // Account for starting offset
        //     current_char += rotor_offset[r];

        //     // Pass character through the rotor
        //     current_char = map(current_char, current_rotor);

        // }


        // Store back into 
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
        setting->rotor_order[i] = 2 - i;
        setting->rotor_offset[i] = 0;
    }


    char* cipher_text = encrypt(text, setting);

    printf("%s\n", cipher_text);

    free(setting);
    free(text);
}
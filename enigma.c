#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Defining rotor wirings
// Citation: German Railway (Rocket) https://en.wikipedia.org/wiki/Enigma_rotor_details
char* ROTORS[26] = {"JGDQOXUSCAMIFRVTPNEWKBLZYH", 
                 "NTZPSFBOKMWRCJDIVLAEYUXHGQ",
                 "JVIUBHTCDYAKEQZPOSGXNRMWFL",
                 "QYHOGNECVPUZTFDJAXWMKISRBL",
                 "QWERTZUIOASDFGHJKPYXCVBNML"};

char* ROTORS_INV[26] = {"JVICSMBZLAUWKREQDNHPGOTFYX", 
                 "SGMOTFYXPNIRJAHDZLEBVQKWUC",
                 "KEHIMYSFCALZWUQPNVRGDBXTJO",
                 "QYHOGNECVPUZTFDJAXWMKISRBL",
                 "JWULCMNOHPQZYXIRADKEGVBTSF"};


char* REFLECTOR = "ZYXWVUTSRQPONMLKJIHGFEDCBA";


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

    int rotor_order[3] = {0,0,0};
    int rotor_offset[3] = {0,0,0};
    for (int i = 0; i < 3; i++) {
        rotor_order[i] = setting->rotor_order[i];
        rotor_offset[i] = setting->rotor_offset[i];
    }

    // NOTE: This must be freed later when calling encrypt from cracker.
    char* result = malloc(sizeof(char) * text_length);
    strcpy(result, text);

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
            if (current_char > 'Z') {
                current_char -= 26;
            }

            // Pass character through the rotor
            current_char = map(current_char, current_rotor);
        }

        // Pass character through the reflector
        current_char = map(current_char, REFLECTOR);

        // Pass back through each rotor (fastest to slowest)
        for (int r = 0; r <= 2; r++) {

            // Pass through rotor
            char* current_rotor = ROTORS_INV[rotor_order[r]];

            // Pass character through the rotor
            current_char = map(current_char, current_rotor);

            // Account for starting offset
            current_char -= rotor_offset[r];
            if (current_char < 'A') {
               current_char += 26;
            }
        }

        // Increment the rotors when reversing through them
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

        // Store back into output string
        result[c] = current_char;
    }

    // Return encrypted text
    return result;
}

// int main(int argc, char* argv[]) {
//     if (argc != 2) {
//         perror("Usage: ./enigma [plain_text]");
//         exit(1);
//     }

//     // Take input
//     char* text = malloc(strlen(argv[1]));
//     memcpy(text, argv[1], strlen(argv[1])); 

//     // Define default rotor settings
//     settings_t* setting = malloc(sizeof(settings_t));
//     for (int i = 0; i < 3; i++) {
//         setting->rotor_order[i] = i;
//         setting->rotor_offset[i] = 10;
//     }


//     char* cipher_text = encrypt(text, setting);

//     printf("%s\n", cipher_text);

//     // char* cipher_dec = decrypt(cipher_text, setting);

//     // printf("%s\n", cipher_dec);

//     free(setting);
//     free(text);
// }
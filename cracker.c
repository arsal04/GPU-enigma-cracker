#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "enigma.c"

// establish a random setting
// run worker threads on various rotor orders
// Choose best five rotor orders (simple version can choose the best)
// Fix rotor order and run worker threads on various rotor configurations
// Choose best five rotor configurations (simple version can choose the best)
// Fix rotor configurations
// Output the resulting plain text on the best settings

// Need to consitent
// Encrypt()
// type Settings

// Need to implement worker to find all permutations of length 3 from the 5 rotors
// Take inspiration from password cracker lab


// Calculates the index of coincidence for a specific value
float index_of_coincidence(char* text) {
    int length = strlen(text);
    int frequency[26];
    // Initialize frequency to 0
    for (int i = 0; i < 26; i++) {
        frequency[i] = 0;
    }


    // Record the frequency of the chracters in the text
    for (int i = 0; i < length; i++) {
        int characterex = toupper(text[i]) - 65;
        frequency[characterex]++;
    }

    float ioc;
    for (int i = 0; i < 26; i++) {;
        ioc += frequency[i] * (frequency[i] - 1);
    }
    ioc /= length*(length-1);

    return ioc;
}

void* worker (void* args) {
    return NULL;

}


// int main(int argc, char* argv[]) { 
//     // Take input
//     char* text = malloc(strlen(argv[1]));
//     memcpy(text, argv[1], strlen(argv[1])); 
//     float IOC_rotors[60];

//     // Initializing the IOCs for each rotor setting possible 
//     for(int i = 0; i < 60; i++){
//         IOC_rotors[i] = 0;
//     }

//     // Initialize a random rotor settings
//     settings_t* setting = malloc(sizeof(settings_t));
//     for (int i = 0; i < 3; i++) {
//         setting->rotor_order[i] = 2 - i;
//         setting->rotor_offset[i] = 0;
//     }

//     // iterate through each permutation of rotors
//     int count = 0;
//     float max1 = 0;
//     float max2 = 0;
//     float max3 = 0;
//     float max4 = 0;
//     float max5 = 0;
//     for (int i = 0; i < 5; i++) {
//         for (int j = 0; j < 5; j++) {
//             if (j == i) {
//                 continue;
//             }        
//             for (int k = 0; k < 5; k++) {
//                 if (k == j || k == i) {
//                     continue;
//                 }

//                 setting->rotor_order[0] = i;
//                 setting->rotor_order[1] = j;
//                 setting->rotor_order[2] = k;

//                 // Encrypt the text
//                 char* cipher_text = decrypt(text, setting);

//                 // Calculate the index of coincidence
//                 float ioc = index_of_coincidence(cipher_text);

//                 // printf("%d) IOC: %f\n", count, ioc);
//                 count++;
//                 if(max1 < ioc){
//                     max1 = ioc;
//                 }
                
//             }   
//         }
//     }
//     printf("Best IOC = %f\n", max1);
    


//     // Free allocated memory
//     free(setting);
//     free(text);

//     return 0;
// }
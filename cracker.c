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

    float ioc = 0.0;
    for (int i = 0; i < 26; i++) {;
        ioc += frequency[i] * (frequency[i] - 1);
    }
    ioc /= length*(length-1);

    return ioc;
}

void* worker (void* args) {
    return NULL;
}


int main(int argc, char* argv[]) { 
    // Take input
    char* text = malloc(strlen(argv[1]) + 1);
    memcpy(text, argv[1], strlen(argv[1])); 

    // Initialize rotor settings
    settings_t* setting = malloc(sizeof(settings_t));
    for (int i = 0; i < 3; i++) {
        setting->rotor_order[i] = i;
        setting->rotor_offset[i] = 0;
    }

    // // iterate through each permutation of rotors

    settings_t* best_rotor_config1 = malloc(sizeof(settings_t));
    settings_t* best_rotor_config2 = malloc(sizeof(settings_t));
    settings_t* best_rotor_config3 = malloc(sizeof(settings_t));
    settings_t* best_rotor_config4 = malloc(sizeof(settings_t));
    settings_t* best_rotor_config5 = malloc(sizeof(settings_t));
    
    float max1 = 0;
    float max2 = 0;
    float max3 = 0;
    float max4 = 0;
    float max5 = 0;

    char* bestText1 = malloc(strlen(argv[1]) + 1);
    char* bestText2 = malloc(strlen(argv[1]) + 1);
    char* bestText3 = malloc(strlen(argv[1]) + 1);
    char* bestText4 = malloc(strlen(argv[1]) + 1);
    char* bestText5 = malloc(strlen(argv[1]) + 1);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (j == i) {
                continue;
            }        
            for (int k = 0; k < 5; k++) {
                if (k == j || k == i) {
                    continue;
                }

                setting->rotor_order[0] = i;
                setting->rotor_order[1] = j;
                setting->rotor_order[2] = k;

                // Brute forcing all rotor offsets

                for (int a = 0; a < 26; a++) {
                    for (int b = 0; b < 26; b++) {
                        for (int c = 0; c < 26; c++) {
                            setting->rotor_offset[0] = a;
                            setting->rotor_offset[1] = b;
                            setting->rotor_offset[2] = c;
                            
                            // Encrypt the text
                            char* cipher_text = encrypt(text, setting);

                            // Calculate the index of coincidence
                            float ioc = index_of_coincidence(cipher_text);

                            if(max1 < ioc){
                                max1 = ioc;
                                strcpy(bestText1, cipher_text);
                                memcpy(best_rotor_config1, setting, sizeof(settings_t));
                            } else if(max2 < ioc){
                                max2 = ioc;
                                strcpy(bestText2, cipher_text);
                                memcpy(best_rotor_config2, setting, sizeof(settings_t));
                            } else if(max3 < ioc){
                                max3 = ioc;
                                strcpy(bestText3, cipher_text);
                                memcpy(best_rotor_config3, setting, sizeof(settings_t));
                            } else if(max4 < ioc){
                                max4 = ioc;
                                memcpy(best_rotor_config4, setting, sizeof(settings_t));
                                strcpy(bestText4, cipher_text);
                            } else if(max5 < ioc){
                                max5 = ioc;
                                strcpy(bestText5, cipher_text);
                                memcpy(best_rotor_config5, setting, sizeof(settings_t));
                            }
                        }
                    }
                }

            }   
        }
    }
    

    printf("%d %d %d\n", best_rotor_config1->rotor_order[0], best_rotor_config1->rotor_order[1], best_rotor_config1->rotor_order[2]);
    printf("%d %d %d\n", best_rotor_config2->rotor_order[0], best_rotor_config2->rotor_order[1], best_rotor_config2->rotor_order[2]);
    printf("%d %d %d\n", best_rotor_config3->rotor_order[0], best_rotor_config3->rotor_order[1], best_rotor_config3->rotor_order[2]);
    printf("%d %d %d\n", best_rotor_config4->rotor_order[0], best_rotor_config4->rotor_order[1], best_rotor_config4->rotor_order[2]);
    printf("%d %d %d\n", best_rotor_config5->rotor_order[0], best_rotor_config5->rotor_order[1], best_rotor_config5->rotor_order[2]);

    // // Finding best rotor offsets
    
    // int rotor1 = best_rotor_config1->rotor_order[0];
    // int rotor2 = best_rotor_config1->rotor_order[1];
    // int rotor3 = best_rotor_config1->rotor_order[2];
    // setting->rotor_order[0] = rotor1;
    // setting->rotor_order[1] = rotor2;
    // setting->rotor_order[2] = rotor3;
    // max1 = 0;
    // max2 = 0;
    // max3 = 0;
    // max4 = 0;
    // max5 = 0;


    // for (int i = 0; i < 26; i++) {
    //     for (int j = 0; j < 26; j++) {
    //         for (int k = 0; k < 26; k++) {
    //             setting->rotor_offset[rotor1] = i;
    //             setting->rotor_offset[rotor2] = j;
    //             setting->rotor_offset[rotor3] = k;
                
    //             // Encrypt the text
    //             char* cipher_text = encrypt(text, setting);

    //             // Calculate the index of coincidence
    //             float ioc = index_of_coincidence(cipher_text);

    //             if(max1 < ioc){
    //                 max1 = ioc;
    //                 strcpy(bestText1, cipher_text);
    //             } else if(max2 < ioc){
    //                 max2 = ioc;
    //                 strcpy(bestText2, cipher_text);
    //             } else if(max3 < ioc){
    //                 max3 = ioc;
    //                 strcpy(bestText3, cipher_text);
    //             } else if(max4 < ioc){
    //                 max4 = ioc;
    //                 strcpy(bestText4, cipher_text);
    //             } else if(max5 < ioc){
    //                 max5 = ioc;
    //                 strcpy(bestText5, cipher_text);
    //             }
    //         }
    //     }
    // }

    printf("%f\n\n", max1);
    printf("%f\n\n", max2);
    printf("%f\n\n", max3);
    printf("%f\n\n", max4);
    printf("%f\n\n", max5);
    printf("%s\n\n", bestText1);
    printf("%s\n\n", bestText2);
    printf("%s\n\n", bestText3);
    printf("%s\n\n", bestText4);
    printf("%s\n\n", bestText5);

    printf("%f\n\n", index_of_coincidence("HELLOTHISISARSALSHAIKHINDASILIAMWORKINGONCSCWITHJAFARANDANSHULHEISHELPINGSOMEONEELSEILOVECOMPUTERSCIENCEANDWANTTOWORKINAMAZONGOOGLENETFLIXMETAFACEBOOKGOLDMANSACHSEPICVERIZONUSAFRANCECHINAJORDAN"));

    // Free allocated memory
    free(setting);
    free(text);

    return 0;
}
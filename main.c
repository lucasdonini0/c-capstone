#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

char username[50] = "Lucas"; // Will make it so the user can change later
int day = 1;
float wallet = 0.0f;
float wallet_day_update = 0.0f;
float crypto = 0.0f;
float funds = 0.0f;
bool canWork = true;
bool canInvestInCrypto = false;
bool canInvestInStocks = false;
bool canGamble = false;
char choice_input[50];

void DisplayMenu(), unlockall();
int workf(), crypto_investment(), stocks_investment(), gamble(), open_shop(), user_assets(), day_history(), day_progress(), loadf();

int main (void){

    DisplayMenu();
    
    while (1){
        int choice_inputnum = 0;
        fgets(choice_input, sizeof(choice_input), stdin);
        if (isdigit(choice_input[0])){
            choice_inputnum = atoi(&choice_input[0]);
        }
        else{
            printf("Please use only numbers: ");
            continue;
        }

        
        switch (choice_inputnum){
            case 1:
                (canWork) ? workf() : printf("You are exhausted! ");
            break;

            case 2:
                (canInvestInCrypto) ? crypto_investment() : printf("You haven't unlocked this option yet. Check the shop for more information. ");
            break;

            case 3:
                (canInvestInStocks) ? stocks_investment() : printf("You haven't unlocked this option yet. Check the shop for more information. ");
            break;

            case 4:
                (canGamble) ? gamble() : printf("You haven't unlocked this option yet. Check the shop for more information. ");
            break;

            case 5:
                open_shop();
            break;

            case 6:
                user_assets();
            break;

            case 7:
                (day > 1) ? day_history() : printf("You haven't written your history yet. ");
            break;

            case 8:
                printf("You went to bed!");
                day_progress();
            break;

            case 9:
                printf("[LOAD SAVE]");
                loadf();
                break;
            
            case 99: // testing purposes [REMOVE]
                unlockall();
                break;
    
            default:
                if (choice_inputnum < 1 || choice_inputnum > 9){
                    printf("Please enter a number from 1-9: ");
                }
                break;
        }
    }
}

int workf(){
    printf("[WORK]");
    canWork = 0;
}
int crypto_investment(){
    printf("[CRYPTO]");
}
int stocks_investment(){
    printf("[STOCKS]");
}
int gamble(){
    printf("[GAMBLE]");
}
int open_shop(){
    printf("[SHOP]");
}
int user_assets(){
    printf("[USER ASSETS]");
}
int day_history(){
    printf("[DAY HISTORY]");
}
int day_progress(){
    day++;
    printf("\n[day++]");
}
int loadf(){ //Error handling: if can't find the file, (later) if the file was modified by other source that was not this program
    printf("[loaded]");
}
void unlockall(){ // testing purposes [REMOVE]
    printf("[UNLOCKEDALL]");
    canGamble = 1;
    canInvestInCrypto = 1;
    canInvestInStocks = 1;
    canWork = 1;
}

void DisplayMenu(){ // make it update in real time
    printf("\r============================================================================================\n");
    printf("\rMoney Game Thing!\n");
    printf("\r============================================================================================\n");
    printf("\rWelcome, %s!  Day %d - $%.2f\n", username, day, wallet_day_update);
    printf("\rWallet: $%.2f - Crypto Portfolio: $%.2f - Investment Portfolio: $%.2f\n", wallet, crypto, funds);
    printf("\r============================================================================================\n");
    printf("\rOptions\n");
    printf("\r1. Work %s\n", (canWork) ? "(Unlocked)" : "(Locked)");
    printf("\r2. Invest in Crypto %s\n", (canInvestInCrypto) ? "(Unlocked)" : "(Locked)");
    printf("\r3. Invest in Funds %s\n", (canInvestInStocks) ? "(Unlocked)" : "(Locked)");
    printf("\r4. Gamble %s\n", (canGamble) ? "(Unlocked)" : "(Locked)");
    printf("\r5. Buy assets\n");
    printf("\r6. View assets\n");
    printf("\r7. Day history\n");
    printf("\r8. Sleep\n");
    printf("\r9. Load game\n\n");
    printf("\rChoose an option: ");
}
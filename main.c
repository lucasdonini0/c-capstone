#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>


typedef struct Game {
    char username[50];
    int day;
    float wallet;
    float wallet_day_update;
    float crypto;
    float stocks;
    bool canWork;
    bool canInvestInCrypto;
    bool canInvestInStocks;
    bool canGamble;
} Game;

Game game = {
    .username = "Player",
    .day = 1,
    .wallet = 0.0f,
    .wallet_day_update = 0.0f,
    .crypto = 0.0f,
    .stocks = 0.0f,
    .canWork = true,
    .canInvestInCrypto = false,
    .canInvestInStocks = false,
    .canGamble = false
};


void DisplayMenu(), unlockall(Game *game);
int workf(Game *game), crypto_investment(Game *game), stocks_investment(Game *game), gamble(Game *game), open_shop(Game *game), user_assets(Game *game), day_history(Game *game), day_progress(Game *game), loadf(Game *game);

int main (void){

    DisplayMenu();
    
    while (1){
        char choice_input[50];
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
                (game.canWork) ? workf(&game) : printf("You are exhausted! ");
            break;

            case 2:
                (game.canInvestInCrypto) ? crypto_investment(&game) : printf("You haven't unlocked this option yet. Check the shop for more information. ");
            break;

            case 3:
                (game.canInvestInStocks) ? stocks_investment(&game) : printf("You haven't unlocked this option yet. Check the shop for more information. ");
            break;

            case 4:
                (game.canGamble) ? gamble(&game) : printf("You haven't unlocked this option yet. Check the shop for more information. ");
            break;

            case 5:
                open_shop(&game);
            break;

            case 6:
                user_assets(&game);
            break;

            case 7:
                (game.day > 1) ? day_history(&game) : printf("You haven't written your history yet. ");
            break;

            case 8:
                printf("You went to bed!");
                day_progress(&game);
            break;

            case 9:
                loadf(&game);
                break;
            case 0:
                return 0;
                break;
            
            case 99: // testing purposes [REMOVE]
                unlockall(&game);
                break;
    
            default:
                if (choice_inputnum < 1 || choice_inputnum > 9){
                    printf("Please enter a number from 1-9: ");
                }
                break;
        }
    }
}
// Don't know when to use void/int - 08/02

int save(){
    FILE *file = fopen("gamesave.tmp", "w");
    fprintf(file, "day: %d\n", game.day);
    fprintf(file, "wallet: %.2f\n", game.wallet);
    fprintf(file, "dayupdate: %.2f\n", game.wallet_day_update);
    fprintf(file, "crypto: %.2f\n", game.crypto);
    fprintf(file, "stocks: %.2f\n", game.stocks);
    fprintf(file, "canwork: %d\n", game.canWork);
    fprintf(file, "cancrypto: %d\n", game.canInvestInCrypto);
    fprintf(file, "canstocks: %d\n", game.canInvestInStocks);
    fprintf(file, "cangamble: %d\n", game.canGamble);
    fclose(file);
    remove("gamesave.txt");
    rename("gamesave.tmp", "gamesave.txt");
}

int load(){
    FILE *file = fopen("gamesave.txt", "r");
    fscanf(file, "day: %d\n", &game.day);
    fscanf(file, "wallet: %f\n", &game.wallet);
    fscanf(file, "dayupdate: %f\n", &game.wallet_day_update);
    fscanf(file, "crypto: %f\n", &game.crypto);
    fscanf(file, "stocks: %f\n", &game.stocks);
    fscanf(file, "canwork: %d\n", &game.canWork);
    fscanf(file, "cancrypto: %d\n", &game.canInvestInCrypto);
    fscanf(file, "canstocks: %d\n", &game.canInvestInStocks);
    fscanf(file, "cangamble: %d\n", &game.canGamble);
    fclose(file);
}

int workf(Game *game){
    printf("[WORK]"); // debug line
    game->canWork = 0;
}
int crypto_investment(Game *game){
    printf("[CRYPTO]"); // debug line
}
int stocks_investment(Game *game){
    printf("[STOCKS]"); // debug line
}
int gamble(Game *game){
    printf("[GAMBLE]"); // debug line
}
int open_shop(Game *game){
    printf("[SHOP]"); // debug line
}
int user_assets(Game *game){
    printf("[USER ASSETS]"); // debug line
}
int day_history(Game *game){
    printf("[DAY HISTORY]"); // debug line
}
int day_progress(Game *game){
    game->day++;
    game->canWork = 1;
    //printf("\n[day++]"); // debug line
    save();
}
int loadf(Game *game){ //Error handling: if can't find the file, (later) if the file was modified by other source that was not this program
    //printf("[loaded]"); // debug line
    load();
}
void unlockall(Game *game){ // testing purposes [REMOVE]
    printf("[UNLOCKEDALL]");
    game->canGamble = 1;
    game->canInvestInCrypto = 1;
    game->canInvestInStocks = 1;
    game->canWork = 1;
}

void DisplayMenu(){ // make it update in real time
    system("cls");
    printf("\r============================================================================================\n");
    printf("\rMoney Game Thing!\n");
    printf("\r============================================================================================\n");
    printf("\rWelcome, %s!  Day %d - $%.2f\n", game.username, game.day, game.wallet_day_update);
    printf("\rWallet: $%.2f - Crypto Portfolio: $%.2f - Stocks Portfolio: $%.2f\n", game.wallet, game.crypto, game.stocks);
    printf("\r============================================================================================\n");
    printf("\rOptions\n");
    printf("\r1. Work %s\n", (game.canWork) ? "(Unlocked)" : "(Locked)");
    printf("\r2. Invest in Crypto %s\n", (game.canInvestInCrypto) ? "(Unlocked)" : "(Locked)");
    printf("\r3. Invest in Funds %s\n", (game.canInvestInStocks) ? "(Unlocked)" : "(Locked)");
    printf("\r4. Gamble %s\n", (game.canGamble) ? "(Unlocked)" : "(Locked)");
    printf("\r5. Buy assets\n");
    printf("\r6. View assets\n");
    printf("\r7. Day history\n");
    printf("\r8. Sleep\n");
    printf("\r9. Load game\n");
    printf("\r0. Close game\n\n");
    printf("\rChoose an option: ");
}
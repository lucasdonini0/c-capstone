#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>


typedef struct Game{
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
}Game;

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

typedef struct assets{
    char asset_name[50];
    float price;
    bool purchased;
    char description[100];
}Assets;

void DisplayMenu(), unlockall(Game *game), allassets(Assets *assets), DisplayAssetShop(Assets *assets);
int workf(Game *game), crypto_investment(Game *game), stocks_investment(Game *game), gamble(Game *game), open_shop(Game *game, Assets *assets), user_assets(Game *game), day_history(Game *game), day_progress(Game *game), loadf(Game *game);

const char *status_message = "";

int main (void){
    char choice_input[10];
    int choice_inputnum = 0;

    while (1){
        system("cls");
        DisplayMenu();
        printf("> %s ", status_message);
        fgets(choice_input, sizeof(choice_input), stdin);
        if (isdigit(choice_input[0])){
            choice_inputnum = atoi(&choice_input[0]);
        }
        else{
            status_message = "Please enter a number from 1-9";
            continue;
        }

        
        switch (choice_inputnum){ // Had to use if/else instead of ternary because the sides are not the same type (CLI update made me change all of this)
            case 1:
                if (game.canWork) {
                    status_message = "";
                    workf(&game);
                } else {
                    status_message = "You are exhausted!";
                }
            break;

            case 2:
                if (game.canInvestInCrypto) {
                    crypto_investment(&game);
                } else {
                    status_message = "You haven't unlocked this option yet. Check the shop for more information.";
                }
            break;

            case 3:
                if (game.canInvestInStocks) {
                    stocks_investment(&game);
                } else {
                    status_message = "You haven't unlocked this option yet. Check the shop for more information.";
                }
            break;

            case 4:
                if (game.canGamble) {
                    gamble(&game);
                } else {
                    status_message = "You haven't unlocked this option yet. Check the shop for more information.";
                }
            break;

            case 5:
                open_shop(&game, NULL);
            break;

            case 6:
                user_assets(&game);
            break;

            case 7:
                if (game.day > 1) {
                    day_history(&game);
                } else {
                    status_message = "You haven't written your history yet.";
                }
            break;

            case 8:
                status_message = "You went to bed!";
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
                    status_message = "Please enter a number from 1-9";
                }
                break;
        }
    }
    return 0;
}

// I Have to call this function multiple times in the code, I don't feel comfortable doing so, but maybe this is normal?
// Will ask people and AI to review my code (Hi :D)
void allassets(Assets *assets){ 
    assets[0] = (Assets){"Phone One", 100.0f, false, "This phone allow you to gamble! How awesome, isn't it?"};
    assets[1] = (Assets){"Phone Two", 350.0f, false, "This phone supports crypto wallets. Be like Daniel Fraga!"};
    assets[2] = (Assets){"Phone Three", 1000.0f, false, "This phone allows you to invest in stocks. The safest way to create wealth!"};
    assets[3] = (Assets){"Descascador de Batata de Luxo", 9999.99f, false, "Buy and find out."};
}

// Don't know when to use void/int - 08/02

int save(){
    FILE *file = fopen("gamesave.tmp", "w");
    fprintf(file, "day: %d\n", game.day);
    fprintf(file, "wallet: %.2f\n", game.wallet);
    fprintf(file, "dayupdate: %.2f\n", game.wallet_day_update);
    fprintf(file, "crypto: %.2f\n", game.crypto);
    fprintf(file, "stocks: %.2f\n", game.stocks);
    fprintf(file, "canwork: %d\n", game.canWork); // Currently it's not needed, but will keep this here in case I add a better autosave in a future version of this project
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
    //printf("[WORK]"); // debug line
    game->canWork = 0;
    float randx = 0.5f;
    float randy = 100.0f;

    srand(time(NULL));
    float random_money_amount = randx + ((float)rand() / (float)RAND_MAX) * (randy + randx);
    
    game->wallet += random_money_amount;
    status_message = "You worked and made $%.2f!";
}
int crypto_investment(Game *game){
    //printf("[CRYPTO]"); // debug line
}
int stocks_investment(Game *game){
    //printf("[STOCKS]"); // debug line
}
int gamble(Game *game){
    //printf("[GAMBLE]"); // debug line
}
int open_gameshop(){
    Assets assets[10];
    allassets(assets);
    open_shop(&game, assets);
}
int open_shop(Game *game, Assets *assets){
    char choice_input[10];
    int choice_inputnum = 0;
    while (1){
        Assets assets[10];
        allassets(assets);

        system("cls");
        DisplayAssetShop(assets);
        printf("> %s ", status_message); 
        fgets(choice_input, sizeof(choice_input), stdin);
        if (isdigit(choice_input[0])){
            choice_inputnum = atoi(&choice_input[0]);
        }
        else{
            status_message = "Please enter a number from 1-9";
            continue;
        }

        switch (choice_inputnum)
        {
        case 1:
            if (game->wallet >= assets[0].price){
                status_message = "Purchased %s!", assets[0].asset_name;
                game->wallet -= assets[0].price;
            }
            else{
                status_message = "You're broke."; 
            }
        break;
        case 2:
            if (game->wallet >= assets[1].price){
                status_message = "Purchased %s!", assets[1].asset_name;
            }
            else{
                status_message = "You're broke.";
            }
        break;
        case 3:
            if (game->wallet >= assets[2].price){
                status_message = "Purchased %s!", assets[2].asset_name;
            }
            else{
                status_message = "You're broke.";
            }
        break;
        case 4:
            if (game->wallet >= assets[3].price){
                status_message = "Purchased %s!", assets[3].asset_name;
            }
            else{
                status_message = "You're broke.";
            }
        break;
        case 0:
            status_message = "";
            return 0; // thought return 0 was used to close the whole program, this is where I learned I was wrong
            break;
        
        default:
        if (choice_inputnum < 1 || choice_inputnum > 9){
            status_message = "Please enter a number from 1-9";
            }
        break;
        }
    }
}
int user_assets(Game *game){

}
int day_history(Game *game){
    //printf("[DAY HISTORY]"); // debug line
}
int day_progress(Game *game){
    game->day++;
    game->canWork = 1;
    save();
}
int loadf(Game *game){ //Error handling: if can't find the file, (later) if the file was modified by other source that was not this program
    //printf("[loaded]"); // debug line
    load();
}
void unlockall(Game *game){ // testing purposes [REMOVE]
    status_message = "Unlocked Everything [ADMIN]";
    game->canGamble = 1;
    game->canInvestInCrypto = 1;
    game->canInvestInStocks = 1;
    game->canWork = 1;
    game->wallet = 999.999;
}

void DisplayMenu(){ // make it update in real time
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
    printf("\rChoose an option: \n");
}

void DisplayAssetShop(Assets *assets){
    printf("\r============================================================================================\n");
    printf("\rAsset Shop!\n");
    printf("\r============================================================================================\n");
    printf("\r%s --- Price: $%.2f --- %s\n %s\n\n", assets[0].asset_name, assets[0].price, assets[0].purchased ? "You own this item" : "You don't own this item", assets[0].description);
    printf("\r%s --- Price: $%.2f --- %s\n %s\n\n", assets[1].asset_name, assets[1].price, assets[1].purchased ? "You own this item" : "You don't own this item", assets[1].description);
    printf("\r%s --- Price: $%.2f --- %s\n %s\n\n", assets[2].asset_name, assets[2].price, assets[2].purchased ? "You own this item" : "You don't own this item", assets[2].description);
    printf("\r%s --- Price: $%.2f --- %s\n %s\n\n", assets[3].asset_name, assets[3].price, assets[3].purchased ? "You own this item" : "You don't own this item", assets[3].description);
    
    printf("\r============================================================================================\n");
    printf("\r1. Buy %s\n", assets[0].asset_name);
    printf("\r2. Buy %s\n", assets[1].asset_name);
    printf("\r3. Buy %s\n", assets[2].asset_name);
    printf("\r4. Buy %s\n", assets[3].asset_name);
    printf("\r0. Close shop\n\n");
    printf("\rChoose an option: \n");
}
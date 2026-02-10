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
    .wallet = 0.00f, 
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
Assets assets[10];

typedef struct Crypto{
    char name[15];
    float price;
    float owned;
}Crypto;
Crypto crypto[3];

typedef struct Stocks{
    char name[15];
    float price;
    float owned;
}Stocks;
Stocks stocks[3];

char status_message[128];

void unlockall(Game *game), set_status(const char *format, ...), DisplayUserAssets(), motherlode(Game *game);
void DisplayStocksOptions(), allstocks(Stocks *stocks), DisplayMenu(), DisplayAssetShop(), allassets(Assets *assets), DisplayCryptoOptions(), allcrypto(Crypto *crypto);
int workf(Game *game), crypto_investment(Game *game), stocks_investment(Game *game), gamble(Game *game), game_shop(Game *game), day_history(Game *game), day_progress(Game *game), loadf(Game *game), user_assets();

int main (void){
    char choice_input[10];
    int choice_inputnum = 0;
    allassets(assets);
    allcrypto(crypto);
    allstocks(stocks);
    srand(time(NULL));
    while (1){
        system("cls");
        DisplayMenu();
        printf("> %s ", status_message);
        fgets(choice_input, sizeof(choice_input), stdin);
        if (isdigit(choice_input[0])){
            choice_inputnum = atoi(&choice_input[0]);
        }
        else{
            set_status("Please enter numbers only!");
            continue;
        }

        
        switch (choice_inputnum){ // Had to use if/else instead of ternary because the sides are not the same type (CLI update made me change all of this)
            case 1:
                if (game.canWork) {
                    set_status("");
                    workf(&game);
                } else {
                    set_status("You are exhausted");
                }
            break;

            case 2:
                if (game.canInvestInCrypto) {
                    set_status("");
                    crypto_investment(&game);
                } else {
                    set_status("You haven't unlocked this option yet. Check the shop for more information.");
                }
            break;

            case 3:
                if (game.canInvestInStocks) {
                    stocks_investment(&game);
                    set_status("");
                } else {
                    set_status("You haven't unlocked this option yet. Check the shop for more information.");
                }
            break;

            case 4:
                if (game.canGamble) {
                    gamble(&game);
                    set_status("");
                } else {
                    set_status("You haven't unlocked this option yet. Check the shop for more information.");
                }
            break;

            case 5:
                game_shop(&game);
                set_status("");
            break;

            case 6:
                user_assets();
                set_status("");
            break;

            case 7:
                if (game.day > 1) {
                    day_history(&game);
                } else {
                    set_status("You haven't written your history yet.");
                }
            break;

            case 8:
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
            case 999:
                motherlode(&game);
                break;
            default:
                if (choice_inputnum < 1 || choice_inputnum > 9){
                    set_status("This number is not an option.");
                }
                break;
        }
    }
    return 0;
}

void set_status(const char *format, ...){ // This was a bit hard to understand
    va_list args;
    va_start(args, format);

    vsnprintf(
        status_message,
        sizeof(status_message),
        format,
        args
    );

    va_end(args);
}

// I Have to call this function multiple times in the code, I don't feel comfortable doing so, but maybe this is normal? (08/02)
// Will ask people and AI to review my code (Hi :D)
// UPDATE: I had to declare Assets as a global variable :D. This also fixed other problems inside the other functions that use assets struct (09/02)
void allassets(Assets *assets){ 
    assets[0] = (Assets){"Phone One", 49.99f, false, "This phone allow you to gamble! How awesome, isn't it?"};
    assets[1] = (Assets){"Phone Two", 699.99f, false, "This phone supports crypto wallets. Be like Daniel Fraga!"};
    assets[2] = (Assets){"Phone Three", 1999.99f, false, "This phone allows you to invest in stocks. The safest way to create wealth!"};
    assets[3] = (Assets){"Descascador de Batata de Luxo", 99999.99f, false, "Buy and find out."};
}

void allcrypto(Crypto *crypto){
    crypto[0] = (Crypto){"BTC", 3000, 0.0f};
    //crypto[1] = (Crypto){"ETH", 200, 0.0f};
    //crypto[2] = (Crypto){"SOL", 50, 0.0f};
}

void allstocks(Stocks *stocks){
    stocks[0] = (Stocks){"WOW", 500.0f, 0.0f};
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
    fprintf(file, "asset1: %d\n", assets[0].purchased);
    fprintf(file, "asset2: %d\n", assets[1].purchased);
    fprintf(file, "asset3: %d\n", assets[2].purchased);
    fprintf(file, "asset4: %d\n", assets[3].purchased);
    fprintf(file, "btcprice: %.2f\n", crypto[0].price);
    fprintf(file, "btcowned: %.1f\n", crypto[0].owned);
    fprintf(file, "wowprice: %.2f\n", stocks[0].price);
    fprintf(file, "wowowned: %.2f\n", stocks[0].owned);
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
    fscanf(file, "asset1: %d\n", &assets[0].purchased);
    fscanf(file, "asset2: %d\n", &assets[1].purchased);
    fscanf(file, "asset3: %d\n", &assets[2].purchased);
    fscanf(file, "asset4: %d\n", &assets[3].purchased);
    fscanf(file, "btcprice: %f\n", &crypto[0].price);
    fscanf(file, "btcowned: %f\n", &crypto[0].owned);
    fscanf(file, "wowprice: %f\n", &stocks[0].price);
    fscanf(file, "wowowned: %f\n", &stocks[0].owned);
    fclose(file);
}

int workf(Game *game){
    game->canWork = 0;
    float randx = 15;
    float randy = 60;

    float random_money_amount = randx + ((float)rand() / (float)RAND_MAX) * (randy - randx);
    
    game->wallet += random_money_amount;
    set_status("You worked and made $%.2f!", random_money_amount);
    game->wallet_day_update += random_money_amount;
}
int crypto_investment(Game *game){
    char choice_input[10];
    int choice_inputnum = 0;
    while (1){
        system("cls");
        DisplayCryptoOptions();
        printf("> %s ", status_message); 
        fgets(choice_input, sizeof(choice_input), stdin);
        if (isdigit(choice_input[0])){
            choice_inputnum = atoi(&choice_input[0]);
        }
        else{
            set_status("Please enter numbers only!");
            continue;
        }

        switch (choice_inputnum){
        case 1:
            if (game->wallet >= crypto[0].price){
                game->wallet  -= crypto[0].price;
                crypto[0].owned += 1.0f;
                game->crypto  += crypto[0].price;
                set_status("Purchased 1 %s for $%.2f!", crypto[0].name, crypto[0].price);
            } else {
                set_status("Not enough money! You need $%.2f but have $%.2f.", crypto[0].price, game->wallet);
            }
        break;
        case 2:
            if (game->wallet < crypto[0].price * 0.0001f){
                set_status("Not enough money to buy any %s!", crypto[0].name);
            } 
            else{
                float maxamount = game->wallet / crypto[0].price;
                float total_cost = maxamount * crypto[0].price;
                game->wallet -= total_cost; 
                crypto[0].owned += maxamount;
                game->crypto += total_cost;
                set_status("Purchased %.1f %s for $%.2f!", maxamount, crypto[0].name, total_cost);
            }
        break;
        case 3:
            if (crypto[0].owned < 1.0f){
                set_status("You don't have 1 full %s to sell! You own %.4f.", crypto[0].name, crypto[0].owned);
            } 
            else{
                crypto[0].owned -= 1.0f;
                game->wallet += crypto[0].price;
                game->crypto -= crypto[0].price;
                if (game->crypto < 0.0f) game->crypto = 0.0f;
                set_status("Sold 1 %s for $%.2f!", crypto[0].name, crypto[0].price);
            }
        break;
        case 4:
            if (crypto[0].owned <= 0.0f){
                set_status("You don't own any %s to sell!", crypto[0].name);
            } 
            else{
                float valor_total = crypto[0].owned * crypto[0].price;
                game->wallet += valor_total;
                game->crypto -= valor_total;
                if (game->crypto < 0.0f) game->crypto = 0.0f;
                set_status("Sold all %.1f %s for $%.2f!", crypto[0].owned, crypto[0].name, valor_total);
                crypto[0].owned = 0.0f;
            }
        break;
        case 0:
            set_status("");
            return 0;
        break;
        default:
        if (choice_inputnum < 1 || choice_inputnum > 9){
            set_status("This number is not an option.");
            }
        break;
        }
        // 
    }
}
int stocks_investment(Game *game){
    char choice_input[10];
    int choice_inputnum = 0;
    while (1){
        system("cls");
        DisplayStocksOptions();
        printf("> %s ", status_message);
        fgets(choice_input, sizeof(choice_input), stdin);
        if (isdigit(choice_input[0])){
            choice_inputnum = atoi(&choice_input[0]);
        } else {
            set_status("Please enter numbers only!");
            continue;
        }

        switch (choice_inputnum){
        case 1: {
            float cost = stocks[0].price * 1;
            if (game->wallet >= cost){
                game->wallet -= cost;
                stocks[0].owned += 1.0f;
                game->stocks += cost;
                set_status("Purchased 1 %s for $%.2f!", stocks[0].name, cost);
            } else {
                set_status("Not enough money! You need $%.2f but have $%.2f.", cost, game->wallet);
            }
        break;
        }
        case 2: {
            float cost = stocks[0].price * 10;
            if (game->wallet >= cost){
                game->wallet -= cost;
                stocks[0].owned += 10.0f;
                game->stocks += cost;
                set_status("Purchased 10 %s for $%.2f!", stocks[0].name, cost);
            } else {
                set_status("Not enough money! You need $%.2f but have $%.2f.", cost, game->wallet);
            }
        break;
        }
        case 3: {
            float cost = stocks[0].price * 100;
            if (game->wallet >= cost){
                game->wallet -= cost;
                stocks[0].owned += 100.0f;
                game->stocks += cost;
                set_status("Purchased 100 %s for $%.2f!", stocks[0].name, cost);
            } else {
                set_status("Not enough money! You need $%.2f but have $%.2f.", cost, game->wallet);
            }
        break;
        }
        case 4:
            if (stocks[0].owned <= 0.0f){
                set_status("You don't own any %s to sell!", stocks[0].name);
            } else {
                float valor_total = stocks[0].owned * stocks[0].price;
                game->wallet += valor_total;
                game->stocks -= valor_total;
                if (game->stocks < 0.0f) game->stocks = 0.0f;
                set_status("Sold all %.2f %s for $%.2f!", stocks[0].owned, stocks[0].name, valor_total);
                stocks[0].owned = 0.0f;
            }
        break;
        case 0:
            set_status("");
            return 0;
        break;
        default:
            if (choice_inputnum < 1 || choice_inputnum > 9){
                set_status("This number is not an option.");
            }
        break;
        }
    }
}
int gamble(Game *game){
    //printf("[GAMBLE]"); // debug line
}
int game_shop(Game *game){
    char choice_input[10];
    int choice_inputnum = 0;
    while (1){
        system("cls");
        DisplayAssetShop();
        printf("> %s ", status_message); 
        fgets(choice_input, sizeof(choice_input), stdin);
        if (isdigit(choice_input[0])){
            choice_inputnum = atoi(&choice_input[0]);
        }
        else{
            set_status("Please enter numbers only!");
            continue;
        }

        switch (choice_inputnum)
        {
        case 1:
            if (game->wallet >= assets[0].price && assets[0].purchased != true){
                set_status("Purchased %s!", assets[0].asset_name);
                game->wallet -= assets[0].price;
                assets[0].purchased = true;
                game->canGamble = true;
            }
            else if (assets[0].purchased == true){
                set_status("You already own this item");
            }
            else{
                set_status("You're broke."); 
            }
        break;
        case 2:
            if (game->wallet >= assets[1].price && assets[1].purchased != true){
                set_status("Purchased %s!", assets[1].asset_name);
                game->wallet = game->wallet - assets[1].price;
                assets[1].purchased = true;
                game->canInvestInCrypto = true;
            }
            else if (assets[1].purchased == true){
                set_status("You already own this item");
            }
            else{
                set_status("You're broke.");
            }
        break;
        case 3:
            if (game->wallet >= assets[2].price && assets[2].purchased != true){
                set_status("Purchased %s!", assets[2].asset_name);
                game->wallet = game->wallet - assets[2].price;
                assets[2].purchased = true;
                game->canInvestInStocks = true;
            }
            else if (assets[2].purchased == true){
                set_status("You already own this item");
            }
            else{
                set_status("You're broke.");
            }
        break;
        case 4:
            if (game->wallet >= assets[3].price && assets[3].purchased != true){
                set_status("Purchased %s!", assets[3].asset_name);
                game->wallet = game->wallet - assets[3].price;
                assets[3].purchased = true;                
            }
            else if (assets[3].purchased == true){
                set_status("You already own this item");
            }
            else{
                set_status("You're broke.");
            }
        break;
        case 0:
            set_status("");
            return 0;
            break;
        
        default:
        if (choice_inputnum < 1 || choice_inputnum > 9){
            set_status("This number is not an option.");
            }
        break;
        }
    }
}
int day_history(Game *game){
    //printf("[DAY HISTORY]"); // debug line
}

int day_progress(Game *game){
    game->day++;
    game->canWork = 1;

    // Crypto fluctuation logic
    int heads = rand() % 2;
    float crypto_percentage, crypto_change;
    char crypto_symbol;
    if (heads){ // If I'm not wrong, 0 = tails, 1 = heads
        crypto_percentage = 0.10f + ((float)rand()) / ((float)RAND_MAX) * (0.80f - 0.10f);
        crypto_change = crypto[0].price * crypto_percentage;
        crypto[0].price += crypto_change;
        crypto_symbol = '+';
    }
    else{
        crypto_percentage = 0.10f + ((float)rand()) / ((float)RAND_MAX) * (0.30f - 0.10f);
        crypto_change = crypto[0].price * crypto_percentage;
        crypto[0].price -= crypto_change;
        if (crypto[0].price < 100.0f) crypto[0].price = 100.0f;
        crypto_symbol = '-';
    }
    if (crypto[0].owned > 0.01f){
        game->crypto = crypto[0].owned * crypto[0].price;
    }

    // Stocks fluctuation logic
    int stocks_roll = rand() % 100;
    float stocks_percentage, stocks_change;
    char stocks_symbol;
    if (stocks_roll < 80){ // cool 80/20 probability logic I saw in a repo
        stocks_percentage = 0.1 + ((float)rand()) / ((float)RAND_MAX) * (0.2 - 0.1f);
        stocks_change = stocks[0].price * stocks_percentage;
        stocks[0].price += stocks_change;
        stocks_symbol = '+';
    } 
    else{
        stocks_percentage = 0.1 + ((float)rand()) / ((float)RAND_MAX) * (0.7 - 0.2f);
        stocks_change = stocks[0].price * stocks_percentage;
        stocks[0].price -= stocks_change;
        if (stocks[0].price < 10.0f) stocks[0].price = 10.0f;
        stocks_symbol = '-';
    }
    if (stocks[0].owned > 0.0f){
        game->stocks = stocks[0].owned * stocks[0].price;
    }

    // Status
    if (crypto[0].owned > 0.01f && stocks[0].owned <= 0.0f){
        set_status("You went to bed! BTC %c%.2f%% (%c$%.2f)", crypto_symbol, crypto_percentage * 100, crypto_symbol, crypto_change);
    } 
    else if (stocks[0].owned > 0.0f && crypto[0].owned <= 0.01f){
        set_status("You went to bed! WOW %c$%.2f%% (%c$%.2f)", stocks_symbol, stocks_percentage * 100, stocks_symbol, stocks_change);
    } 
    else if (crypto[0].owned > 0.01f && stocks[0].owned > 0.0f){
        set_status("You went to bed! BTC %c%.2f%% (%c$%.2f) | WOW %c$%.2f%% (%c$%.2f)", crypto_symbol, crypto_percentage * 100, crypto_symbol, crypto_change, stocks_symbol, stocks_percentage * 100, stocks_symbol, stocks_change);
    } 
    else{
        set_status("You went to bed!");
    }

    save();
}
int user_assets(){
    char choice_input[10];
    int choice_inputnum = 0;
    while (1){
        system("cls");
        DisplayUserAssets();
        printf("> %s ", status_message); 
        fgets(choice_input, sizeof(choice_input), stdin);
        if (isdigit(choice_input[0])){
            choice_inputnum = atoi(&choice_input[0]);
        }
        else{
            set_status("Please enter numbers only!");
            continue;
        }

        switch (choice_inputnum)
        {
        case 0:
            return 0;
            break;
        
        default:
            set_status("You clearly have only one option, what are you doing?");
            break;
        }
    }
}

// I don't think this is useful
int loadf(Game *game){ //Error handling: if can't find the file, (later) if the file was modified by other source that was not this program
    load();
    set_status("Loaded gamesave!");
}
void unlockall(Game *game){ // testing purposes [REMOVE]
    set_status("Unlocked Everything [ADMIN]");
    game->canGamble = 1;
    game->canInvestInCrypto = 1;
    game->canInvestInStocks = 1;
    game->canWork = 1;
    game->wallet += 99999.99;
}
void motherlode(Game *game){
    game->wallet += 99999;
    set_status ("[MOTHERLODE]");
}

void DisplayMenu(){
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
    if (game.day == 1){
        printf("\r8. Sleep (This will automatically save your game)\n");
    }
    else{
        printf("\r8. Sleep\n");
    }
    printf("\r9. Load game\n");
    printf("\r0. Close game\n\n");
    printf("\rChoose an option: \n");
}

void DisplayAssetShop(){
    printf("\r============================================================================================\n");
    printf("\rAsset Shop! --- Wallet: $%.2f\n", game.wallet);
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
    printf("\r0. Go back\n\n");
    printf("\rChoose an option: \n");
}

void DisplayUserAssets(){
    printf("\r============================================================================================\n");
    printf("\rAsset Inventory! --- Wallet: $%.2f\n", game.wallet);
    printf("\r============================================================================================\n");
    if (assets[0].purchased) {
        printf("%s!\n", assets[0].asset_name);
    }
    if (assets[1].purchased) {
        printf("%s!\n", assets[1].asset_name);
    }
    if (assets[2].purchased) {
        printf("%s!\n", assets[2].asset_name);
    }
    if (assets[3].purchased) {
        printf("%s!\n", assets[3].asset_name);
    }
    if (assets[0].purchased == false && assets[1].purchased == false && assets[2].purchased == false && assets[3].purchased == false){
        printf("You don't own any items :(\n");
    }
    printf("\r============================================================================================\n");

    printf("\r0. Go back\n\n");
    printf("\rChoose an option: \n");
}

void DisplayCryptoOptions(){
    float maxamount = game.wallet / crypto[0].price;
    printf("\r============================================================================================\n");
    printf("\rCrypto --- Wallet: $%.2f --- Crypto Portfolio: $%.2f\n", game.wallet, game.crypto);
    printf("\r============================================================================================\n");
    printf("\r%s --- Price: $%.2f --- Amount owned: %.1f\n", crypto[0].name, crypto[0].price, crypto[0].owned);
    printf("\r============================================================================================\n");
    printf("\r1. Purchase 1 %s for $%.2f\n", crypto[0].name, crypto[0].price);
    printf("\r2. Purchase max (%.4f %s) for $%.2f\n", maxamount, crypto[0].name, game.wallet);
    printf("\r3. Sell 1 %s\n", crypto[0].name);
    printf("\r4. Sell all %s\n", crypto[0].name);
    printf("\r0. Go back\n\n");
    printf("\rChoose an option: \n");
}

void DisplayStocksOptions(){
    printf("\r============================================================================================\n");
    printf("\rStocks --- Wallet: $%.2f --- Stocks Portfolio: $%.2f\n", game.wallet, game.stocks);
    printf("\r============================================================================================\n");
    printf("\r%s --- Price: $%.2f --- Amount owned: %.2f\n", stocks[0].name, stocks[0].price, stocks[0].owned);
    printf("\r============================================================================================\n");
    printf("\r1. Buy 1 %s for $%.2f\n", stocks[0].name, stocks[0].price);
    printf("\r2. Buy 10 %s for $%.2f\n", stocks[0].name, stocks[0].price * 10);
    printf("\r3. Buy 100 %s for $%.2f\n", stocks[0].name, stocks[0].price * 100);
    printf("\r4. Sell all %s\n", stocks[0].name);
    printf("\r0. Go back\n\n");
    printf("\rChoose an option: \n");
}
#include <stdio.h>
void displayMenu();
void customerinfo(char customername[], char CNIC[]);
void displayinventory(char productnames[][30], float prices[], int stock[], int productcount);
void addToCart(char productnames[][30], float prices[], int stock[], int productcount, int cartproductIDs[], int cartquantities[], int *cartcount);
void updateInventory(int stock[], int cartproductIDs[], int cartquantities[], int cartcount);
void displayTotalBill(char productnames[][30], float prices[],  int cartproductIDs[], int cartquantities[], int cartcount, float *totalBill);
void showInvoice(char customername[], char CNIC[], char productnames[][30], float prices[], int cartproductIDs[], int cartquantities[], int cartcount, float totalbill);
void removeNewline(char str[]);
int comparePromocode(char input[], char promocode[]);

int main() {
    char productNames[10][30] = {"Rice", "Sugar", "Flour", "Oil", "Tea", "Milk", "Bread", "Eggs", "Butter", "Cheese"};
    float prices[10] = {150.0, 120.0, 80.0, 300.0, 250.0, 180.0, 60.0, 200.0, 350.0, 400.0};
    int stock[10] = {50, 40, 60, 30, 25, 35, 45, 100, 20, 15};
    int productCount = 10;
    char customerName[50] = "";
    char customerCNIC[20] = "";
    int cartProductIDs[10];     
    int cartQuantities[10];      
    int cartCount = 0;           
    float totalBill = 0.0;
    int ch;
    int customerInfoEntered = 0;
    int cartFinalized = 0;
    printf(" SUPERMARKET INVENTORY & BILLING SYSTEM\n");
    
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &ch);
        getchar();  
        
        switch(ch) {
            case 1:
                customerinfo(customerName, customerCNIC);
                customerInfoEntered = 1;
                break;
                
            case 2:

                displayinventory(productNames, prices, stock, productCount);
                break;
                
            case 3:
                if(!customerInfoEntered) {
                    printf("\nPlease enter customer information first (Option 1)!\n");
                } else {
                    addToCart(productNames, prices, stock, productCount, 
                             cartProductIDs, cartQuantities, &cartCount);
                }
                break;
                
            case 4:
                if(cartCount == 0) {
                    printf("\n? Cart is empty! Add items first (Option 3).\n");
                } else {
                    displayTotalBill(productNames, prices, cartProductIDs, 
                                    cartQuantities, cartCount, &totalBill);
                    cartFinalized = 1;
                }
                break;
                
            case 5:
                // Show invoice
                if(!cartFinalized) {
                    printf("\n? Please finalize bill first (Option 4)!\n");
                } else {
                    // Update inventory after checkout
                    updateInventory(stock, cartProductIDs, cartQuantities, cartCount);
                    showInvoice(customerName, customerCNIC, productNames, prices, 
                               cartProductIDs, cartQuantities, cartCount, totalBill);
                    
                    // Reset cart after invoice
                    cartCount = 0;
                    cartFinalized = 0;
                    totalBill = 0.0;
                }
                break;
                
            case 6:
                // Exit
                printf("\nThank you for shopping with us!\n");
                printf("Goodbye!\n");
                break;
                
            default:
                printf("\n*** Invalid choice! Please select 1-6. ***\n");
        }
        
    } while(ch != 6);
    
    return 0;
}

// Display main menu
void displayMenu() {
    printf("\n========== MAIN MENU ==========\n");
    printf("1. Customer Information\n");
    printf("2. Display Inventory\n");
    printf("3. Add Item to Cart\n");
    printf("4. Display Total Bill\n");
    printf("5. Show Invoice\n");
    printf("6. Exit\n");
    printf("================================\n");
}

// Remove newline from fgets input
void removeNewline(char str[]) {
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

int comparePromocode(char input[], char promocode[]) {
    int i = 0;
    while(input[i] != '\0' && promocode[i] != '\0') {
        char c1 = input[i];
        char c2 = promocode[i];
        if(c1 >= 'A' && c1 <= 'Z') {
            c1 = c1 + 32; 
        }
        if(c2 >= 'A' && c2 <= 'Z') {
            c2 = c2 + 32;
        }
        if(c1 != c2) {
            return 0;  
        }
        i++;
    }
    if(input[i] == '\0' && promocode[i] == '\0') {
        return 1; 
    }
    return 0;
}
void customerinfo(char customerName[], char customerCNIC[]) {
    printf("\n=== CUSTOMER INFORMATION ===\n");
    
    printf("Enter Customer Name: ");
    fgets(customerName, 50, stdin);
    removeNewline(customerName);
    
    printf("Enter CNIC Number: ");
    fgets(customerCNIC, 20, stdin);
    removeNewline(customerCNIC);
    
    printf("\n? Customer information saved!\n");
}

void displayinventory(char productNames[][30], float prices[], int stock[], int productCount) {
    printf("\n========== INVENTORY ==========\n");
    printf("ID  Product Name          Price (PKR)  Stock\n");
    printf("-----------------------------------------------\n");
    int i;
    for( i = 0; i < productCount; i++) 
	{
        printf("%-3d %-20s PKR %.2f     %d\n", 
               i+1, productNames[i], prices[i], stock[i]);
    }
}
void addToCart(char productNames[][30], float prices[], int stock[], int productCount,
               int cartProductIDs[], int cartQuantities[], int *cartCount) {
    printf("\n=== ADD ITEM TO CART ===\n");
    
    if(*cartCount >= 10) {
        printf("Error: Cart is full!\n");
        return;
    }
    printf("\nAvailable Products:\n");
    int i;
    for(i = 0; i < productCount; i++) {
        printf("%d. %s (PKR %.2f) - Stock: %d\n", 
               i+1, productNames[i], prices[i], stock[i]);
    }
    
    int productID, quantity;
    
    printf("\nEnter Product ID (1-%d): ", productCount);
    scanf("%d", &productID);
    if(productID < 1 || productID > productCount) 
	{
        printf("Error: Invalid Product ID!\n");
        return;
    }
    int productIndex = productID - 1; 
    if(stock[productIndex] == 0) 
	{
        printf("Error: Product out of stock!\n");
        return;
    }
    printf("Enter Quantity: ");
    scanf("%d", &quantity);
    if(quantity <= 0) {
        printf("Error: Invalid quantity!\n");
        return;
    }
    
    if(quantity > stock[productIndex]) 
	{
        printf("Error: Only %d units available!\n", stock[productIndex]);
        return;
    }
    cartProductIDs[*cartCount] = productIndex;
    cartQuantities[*cartCount] = quantity;
    (*cartCount)++;
    
    printf("\n? %s (x%d) added to cart!\n", productNames[productIndex], quantity);
}

void updateInventory(int stock[], int cartProductIDs[], int cartQuantities[], int cartCount) 
{
	int i;
    for(i = 0; i < cartCount; i++) {
        int productIndex = cartProductIDs[i];
        int quantity = cartQuantities[i];
        stock[productIndex] -= quantity;
    }
    printf("\n? Inventory updated successfully!\n");
}

void displayTotalBill(char productNames[][30], float prices[], 

                      int cartProductIDs[], int cartQuantities[], int cartCount, float *totalBill) 
					  {
    printf("YOUR BILL\n");
    printf("Product Name          Qty   Price    Total\n");
    
    float subtotal = 0.0;
    int i;
    for(i = 0; i < cartCount; i++) {
        int productIndex = cartProductIDs[i];
        int quantity = cartQuantities[i];
        float itemTotal = prices[productIndex] * quantity;
        
        printf("%-20s  %-4d  %.2f   %.2f\n", 
               productNames[productIndex], quantity, prices[productIndex], itemTotal);
        
        subtotal += itemTotal;
    }
    printf("Subtotal:                          PKR %.2f\n", subtotal);
    char hasPromo;
    printf("\nDo you have a promocode? (Y/N): ");
    scanf(" %c", &hasPromo);
    getchar(); 
    
    float discount = 0.0;
    float finalTotal = subtotal;
    
    if(hasPromo == 'Y' || hasPromo == 'y') {
        char promocodeInput[20];
        char validPromocode[20] = "Eid2025";
        printf("Enter promocode: ");
        fgets(promocodeInput, 20, stdin);
        removeNewline(promocodeInput);
        if(comparePromocode(promocodeInput, validPromocode)) 
		{
            discount = subtotal * 0.25;  
            finalTotal = subtotal - discount;
            printf("\n? Promocode applied! 25%% discount: PKR %.2f\n", discount);
        } 
		else
		{
            printf("\n? Invalid promocode! No discount applied.\n");
        }
    }
    printf("Discount:                          PKR %.2f\n", discount);
    printf("FINAL TOTAL:                       PKR %.2f\n", finalTotal);  
    *totalBill = finalTotal;
}
void showInvoice(char customername[], char CNIC[], char productnames[][30],
                 float prices[], int cartproductIDs[], int cartquantities[], int cartcount, float totalbill) {
    printf("\n");
    printf("FINAL INVOICE\n");
    printf("customer Name: %s\n", customername);
    printf("CNIC Number: %s\n", CNIC);
    printf("product Name          Qty   Price    Total\n");
    float subtotal = 0.0;
    int i;
    for(i = 0; i < cartcount; i++) {
        int productIndex = cartproductIDs[i];
        int quantity = cartquantities[i];
        float itemTotal = prices[productIndex] * quantity;
        
        printf("%-20s  %-4d  %.2f   %.2f\n",
               productnames[productIndex], quantity, prices[productIndex], itemTotal);  
        subtotal += itemTotal;
    }
    float discount = subtotal - totalbill;
    printf("Subtotal:                          PKR %.2f\n", subtotal);
    printf("Discount:                          PKR %.2f\n", discount);
    printf("FINAL AMOUNT:                      PKR %.2f\n", totalbill);


}

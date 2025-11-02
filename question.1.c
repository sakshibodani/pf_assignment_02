#include<stdio.h>
void addnewbook(int isbns[], char titles[50][100], float prices[], int quantities[], int*bookcount);
void removeline(char str[]);
void processsale(int isbns[], char titles[50][100], float prices[], int quantities[], int bookcount);
void lowstockreport(int isbns[], char titles[50][100], float prices[], int quantities[], int bookcount);
void displaymenu();
int findBookByISBN(int isbns[], int bookCount, int searchISBN);
int main()
{
	int isbns[50];
	char titles[50][100];
	float prices[50];
	int quantities[50];
	int bookcount=0;
	int ch;
	printf("welcome to liberty books \n");
	do
	{
		displaymenu();
		printf("enter your choice?: ");
		scanf("%d", &ch);
		
		switch(ch)
		{
			case 1:
				 addnewbook(isbns, titles, prices, quantities, &bookcount);
				break;
			case 2:
			     processsale(isbns, titles, prices, quantities, bookcount);
				 break;
			case 3:
			     lowstockreport(isbns, titles, prices, quantities, bookcount);
				 break;	 
			case 4:	 
				 printf("Thankyou for using liberty books!\n");
				 break;	
			default:
			printf("INVALID OPTION!\n");
			     break;	 
		}
	}
	while(ch!=4);
	
}
    void removenewline(char str[])
    {
    	int i;
    	while(str[i]!='\0')
    	{
    		if(str[i]=='\0')
    		{
    			str[i]= '\0';
    			break;
			}
			i++;
		}
	}
    void displaymenu()
	{
		printf("1. Add new book\n");
		printf("2. Process a sale\n");
		printf("3. generate low stock report\n");
		printf("4. exit!\n");
        }
	void addnewbook(int isbns[], char titles[50][100], float prices[], int quantities[], int*bookcount)
	{
		printf("ADD NEW BOOK!\n");
		if(*bookcount>=50)
		{
			printf("inventory full!\n");
		}
		int newisbn;
		printf("enter isbn: ");
		scanf("%d", &newisbn);
		getchar();
		if(findbook(isbns, *bookcount, newisbn)!=-1)
		{
			printf("error! a book with isbn %d alr exists!\n", newisbn);
			return;
		}
		
		int index= *bookcount;
		isbns[index]=newisbn;
		printf("enter title: ");
		fgets(titles[index], 100, stdin);
		removenewline(titles[index]);
		
		printf("enter price: ");
		scanf("%f", &prices[index] );
		
		printf("enter quanity: ");
		scanf("%d", &quantities[index]);
		
		(*bookcount)++;
		printf("book added successfully\n");
		printf("total books now: %d\n", *bookcount);
	 } 
	 int  findbook(int isbns[], int bookcount, int searchisbn)
	 {
	 	int i;
	 	for(i=0; i<bookcount; i++ )
	 	{
	 		if(isbns[i]==searchisbn)
	 		{
	 			return i;
			 }
		 }
		 return -1;
	 }
	 void processsale(int isbns[], char titles[][100], float prices[], int quantities[], int bookcount)
	 {
	 	printf("process sale!\n");
	 	if(bookcount==0)
	 	printf("error! no books in inventory!\n");
	 	int saleisbn, copies;
	 	printf("enter isbn of book to sell!\n");
	 	scanf("%d", &saleisbn);
	 	int index= findbook(isbns, bookcount, saleisbn);
	 	if(index==-1)
	 	{
	 		printf("error! book with %d not found", saleisbn);
	 		return;
		 }
		 printf("\nBook Found:\n");
    printf("  Title: %s\n", titles[index]);
    printf("  Price: PKR %.2f\n", prices[index]);
    printf("  Available: %d copies\n", quantities[index]);
    
    printf("\nEnter number of copies to sell: ");
    scanf("%d", &copies);
    if(copies > quantities[index]) {
        printf("Error: Out of stock! Only %d copies available.\n", quantities[index]);
        return;
    }

    if(copies <= 0) 
	{
        printf("Error: Invalid quantity!\n");
        return;
    }
    quantities[index] -= copies;
    float totalAmount = prices[index] * copies;
    
    printf("\n? Sale processed successfully!\n");
    printf("Copies sold: %d\n", copies);
    printf("Total amount: PKR %.2f\n", totalAmount);
    printf("Remaining stock: %d\n", quantities[index]);

    if(quantities[index] < 5) {
        printf("  ? WARNING: Low stock!\n");
    }
	}
	void lowstockreport(int isbns[], char titles[][100], float prices[], int quantities[], int bookCount) {
    printf("\n=== LOW-STOCK REPORT ===\n");
    printf("Books with less than 5 copies:\n\n");
    
    int lowStockCount = 0;
    int i;
    
    for( i = 0; i < bookCount; i++) {
        if(quantities[i] < 5) {
            lowStockCount++;
            printf("%d. ISBN: %d\n", lowStockCount, isbns[i]);
            printf("   Title: %s\n", titles[i]);
            printf("   Price: PKR %.2f\n", prices[i]);
            printf("   Quantity: %d copies\n", quantities[i]);
            printf("   --------------------------\n");
        }
    }
    
    if(lowStockCount == 0) {
        printf("? All books are well-stocked!\n");
    } else {
        printf("\nTotal low-stock items: %d\n", lowStockCount);
    }
}
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 

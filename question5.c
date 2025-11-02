#include <stdio.h>	
	void displaymenu();	
	void encodemessage(char message[]);
	void decodemessage(char message[]);
	void reversemessage(char message[]);
	int getlength(char message[]);
	char togglebits(char ch);

	int main() {
    char message[500];
    int choice;
    printf("   TCS TRANZUM COURIER SERVICE\n");
    printf("   MESSAGE ENCODER AND DECODER SYSTEM\n");
    
    do
	 {
        displaymenu();
        printf("enter your choice: ");
        scanf("%d", &choice);
        getchar();  
        
        switch(choice) 
		{
            case 1:
                printf("\nENCODE MESSAGE \n");
                printf("enter message to encode: ");
                fgets(message, 500, stdin);
                
                int i = 0;
                while(message[i] != '\0') 
				{
                    if(message[i] == '\n') 
					{
                        message[i] = '\0';
                        break;
                    }
                    i++;
                }
                
                encodemessage(message);
                printf("\nencoded message: %s\n", message);
                break;
                
            case 2:
                printf("\nDECODE MESSAGE\n");
                printf("enter message to decode: ");
                fgets(message, 500, stdin);
            
       				 i = 0;
        				while(message[i] != '\0') 
				{
       				 if(message[i] == '\n') 
							{
               					 message[i] = '\0';
                        break;
                }
                    i++;
                }
                
                decodemessage(message);
                printf("decoded message: %s\n", message);
                break;
                
            case 3:
                printf("\nexiting system...\n");
                printf("thank you for using TCS encoder!\n");
                break;
                
            default:
                printf("\ninvalid choice! please select 1 to 3.\n");
        }
        
    } 
	while(choice != 3);
}

void displaymenu()
 {
    printf("\n MAIN MENu\n");
    printf("1. encode message\n");
    printf("2. decode message\n");
    printf("3. exit\n");

}

int getlength(char message[])
 {
    int length = 0;
    while(message[length] != '\0') 
	{
        length++;
    }
    return length;
}
void reversemessage(char message[]) 
{
    int length = getlength(message);
    int start = 0;
    int end = length - 1;
    

    while(start < end) 
	{
        char temp = message[start];
        message[start] = message[end];
        message[end] = temp;
        start++;
        end--;
    }
}
char togglebits(char ch) 
{
    ch = ch ^ (1 << 1);
    ch = ch ^ (1 << 4);
    
    return ch;
}
void encodemessage(char message[]) 
{
    printf("\n[ENCODING PROCESS]\n");
    printf("step 1: reversing message...\n");
    reversemessage(message);
    printf("reversed: %s\n", message);
    printf("step 2: toggling bits (2nd and 5th)...\n");
    int i = 0;
    while(message[i] != '\0') {
        message[i] = togglebits(message[i]);
        i++;
    }
    printf("encoding complete!\n");
}

void decodemessage(char message[])
 {
    printf("\n[DECODING PROCESS]\n");

    printf("step 1: toggling bits back...\n");
    int i = 0;
    while(message[i] != '\0') 
	{
        message[i] = togglebits(message[i]);
        i++;
    }

    printf("step 2: reversing message back...\n");
    reversemessage(message);
    printf("decoding complete!\n");
}

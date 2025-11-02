#include <stdio.h>
void displaymenu();
void updatesectorstatus(int grid[][5], int rows, int cols);
void querysectorstatus(int grid[][5], int rows, int cols);
void runsystemdiagnostic(int grid[][5], int rows, int cols);
void displaygrid(int grid[][5], int rows, int cols);
int main() {
    int grid[4][5] = {0};  
    int rows = 4;
    int cols = 5;
    int choice; 
    printf("IESCO POWER GRID MONITORING SYSTEM\n");
    printf(" Islamabad Capital Territory\n");
    
    do 
	{
        displaymenu();
        printf("enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice)
		 {
            case 1:
                updatesectorstatus(grid, rows, cols);
                break;
                
            case 2:
                querysectorstatus(grid, rows, cols);
                break;
                
            case 3:
                runsystemdiagnostic(grid, rows, cols);
                break;
                
            case 4:
                displaygrid(grid, rows, cols);
                break;
                
            case 5:
                printf("\nexiting system...\n");
                printf("goodbye!\n");
                break;
                
            default:
                printf("\ninvalid choice! please select 1-5.\n");
        }
        
    } 
	while(choice != 5);

}

void displaymenu() {
    printf("\n MAIN MENU\n");
    printf("1. update sector status\n");
    printf("2. query sector status\n");
    printf("3. run system diagnostic\n");
    printf("4. display grid\n");
    printf("5. exit\n");

}


void updatesectorstatus(int grid[][5], int rows, int cols) {
    int row, col, flag, action;
    
    printf("\nUPDATE SECTOR STATUS \n");
    printf("enter row (0-%d): ", rows-1);
    scanf("%d", &row);
    
    printf("enter column (0-%d): ", cols-1);
    scanf("%d", &col);

    if(row < 0 || row >= rows || col < 0 || col >= cols) 
	{
        printf("error: invalid coordinates!\n");
        return;
    }
    
    printf("\nselect status flag:\n");
    printf("0 - power status (bit 0)\n");
    printf("1 - overload warning (bit 1)\n");
    printf("2 - maintenance required (bit 2)\n");
    printf("enter flag number: ");
    scanf("%d", &flag);
    
    if(flag < 0 || flag > 2) {
        printf("error: invalid flag number!\n");
        return;
    }
    
    printf("select action:\n");
    printf("1 - set flag (turn ON)\n");
    printf("0 - clear flag (turn OFF)\n");
    printf("enter action: ");
    scanf("%d", &action);
    
    if(action == 1)
	 {
        grid[row][col] = grid[row][col] | (1 << flag);
        printf("\nflag set successfully!\n");
    } 
	else if(action == 0)
	 {
        
        grid[row][col] = grid[row][col] & ~(1 << flag);
        printf("\nflag cleared successfully!\n");
    } 
	else
	 {
        printf("error: invalid action!\n");
        return;
    }
    
    printf("sector [%d][%d] status updated to: %d\n", row, col, grid[row][col]);
}
void querysectorstatus(int grid[][5], int rows, int cols) 
{
    int row, col, status;
    
    printf(" QUERY SECTOR STATUS \n");
    printf("enter row (0-%d): ", rows-1);
    scanf("%d", &row);
    printf("enter column (0-%d): ", cols-1);
    scanf("%d", &col);
    if(row < 0 || row >= rows || col < 0 || col >= cols)
	 {
        printf("error: invalid coordinates!\n");
        return;
    }
    
    status = grid[row][col];
    
    printf("\n--- SECTOR [%d][%d] STATUS REPORT ---\n", row, col);
    printf("raw status value: %d (binary: ", status);
    for(int i = 2; i >= 0; i--) 
	{
        if(status & (1 << i)) 
		{
            printf("1");
        } else {
            printf("0");
        }
    }
    printf(")\n\n");
    printf("power status: ");
    if(status & (1 << 0)) {
        printf("ON\n");
    } else {
        printf("OFF\n");
    }
    
    printf("overload warning: ");
    if(status & (1 << 1)) 
	{
        printf("OVERLOADED\n");
    } 
	else {
        printf("NORMAL\n");
    }
    
    printf("maintenance required: ");
    if(status & (1 << 2)) 
	{
        printf("YES\n");
    } 
	else 
	{
        printf("NO\n");
    }
    
}
void runsystemdiagnostic(int grid[][5], int rows, int cols)
 {
    int overloadcount = 0;
    int maintenancecount = 0;
    int poweroncount = 0;
    int totalsectors = rows * cols;
    
    printf("\nSYSTEM DIAGNOSTIC \n");
    printf("scanning %d sectors.....\n\n", totalsectors);
    for(int i = 0; i < rows; i++) 
	{
        for(int j = 0; j < cols; j++)
		 {
            int status = grid[i][j];
        
            if(status & (1 << 0))
			 {
                poweroncount++;
            }
           
            if(status & (1 << 1)) 
			{
                overloadcount++;
                printf("! overload detected at sector [%d][%d]\n", i, j);
            }
        
            if(status & (1 << 2)) {
                maintenancecount++;
                printf("! maintenance required at sector [%d][%d]\n", i, j);
            }
        }
    }
    
    printf("\n--- DIAGNOSTIC SUMMARY ---\n");
    printf("total sectors: %d\n", totalsectors);
    printf("sectors with power ON: %d\n", poweroncount);
    printf("sectors overloaded: %d\n", overloadcount);
    printf("sectors requiring maintenance: %d\n", maintenancecount);
    
    if(overloadcount == 0 && maintenancecount == 0)
	 {
        printf("\nsystem status: ALL CLEAR\n");
    } else {
        printf("\nsystem status: ATTENTION REQUIRED\n");
    }
    
}

void displaygrid(int grid[][5], int rows, int cols) 
{
    printf("\n POWER GRID STATUS\n");
    printf("    ");
    for(int j = 0; j < cols; j++) 
	{
        printf("Col%d ", j);
    }
    printf("\n");
    
    for(int i = 0; i < rows; i++) 
	{
        printf("Row %d ", i);
        for(int j = 0; j < cols; j++) 
		{
            printf(" %d  ", grid[i][j]);
        }
        printf("\n");
    }
    
    printf("\nlegend:\n");
    printf("0 = ALL OFF, no warnings\n");
    printf("1 = power ON (bit 0)\n");
    printf("2 = overload warning (bit 1)\n");
    printf("3 = power ON + overload (bits 0,1)\n");
    printf("4 = maintenance required (bit 2)\n");
    printf("5 = power ON + maintenance (bits 0,2)\n");
    printf("6 = overload + maintenance (bits 1,2)\n");
    printf("7 = all flags set (bits 0,1,2)\n");
}

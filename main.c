#include <stdio.h>
#include <stdlib.h>
#include "function.h"



int main(){
    int input;
    LIST *l = create_list(3);
    do{
        printf("%72s\n","------------------------Menu------------------------");
        printf("%41s\t\t\t\t|\n","| 1. Add a new product");
        printf("%40s\t\t\t\t|\n","| 2. Modify a product");
        printf("%40s\t\t\t\t|\n","| 3. Delete a product");
        printf("%41s\t\t\t\t|\n","| 4. List all products");
        printf("%55s\t\t\t|\n","| 5. Sort products by codes or names");
        printf("%64s\t|\n","| 6. List all products (stock > given number)");
        printf("%52s\t\t\t|\n","| 7. Search for a product by name");
        printf("%45s\t\t\t\t|\n","| 8. Save all data to file");
        printf("%38s\t\t\t\t\t|\n","| 9. Load from file");
        printf("%29s\t\t\t\t\t\t|\n","| 10. Exit");
        printf("%72s\n","----------------------------------------------------");
        printf("Which one do you want to use: ");
        scanf("%d",&input);
        switch(input){
            case 1: system("cls");
                    addProduct(l);
                    break;
            case 2: system("cls");
                    modifyProduct(l);
                    break;
            case 3: system("cls");
                    deleteProduct(l);
                    break;
            case 4: system("cls");
                    printAllProduct(l);
                    break;
            case 5: system("cls");
                    sortProduct(l);
                    break;
            case 6: system("cls");
                    printSpecific(l);
                    break;
            case 7: system("cls");
                    searchProduct(l);
                    break;
            case 8: system("cls");
                    savetoFile(l);
                    break;
            case 9: system("cls");
                    loadfromFile(l);
                    break;
            case 10: printf("Thank you");
                    break;
            default: printf("Please choose the right option\n");
                    break;
        }
    }while(input != 10);


    return 0;
}

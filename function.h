#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sorted_code = 0;
int sorted_name = 0;


typedef struct Node{
    int productCode;
    char name[50];
    char category;
    float unitPrice;
    int quantity;
    struct Node *next;
}NODE;

typedef struct {
    NODE *head;
    int n;
}LIST;

//Create list of size
LIST *create_list(int size){
    LIST *l = (LIST*) malloc(sizeof(LIST)*size);
    for(int i = 0;i<size;i++){
        l[i].head = NULL;
        l[i].n = 0;
    }
    return l;
}

//Reverse a list function
//Example 5->4->3->2->1 to 1->2->3->4->5
void reverse_list(LIST *l){
    NODE *prev = NULL;
    NODE *current = l->head;
    NODE *next = NULL;
    //reverse pointer until Null
    while(current != NULL){
        // Store next
        next = current->next;
        //Reverse current node's pointer
        current->next = prev;
        //Move pointers one position ahead
        prev = current;
        current = next;
    }
    l->head = prev;
}

//Insert data to the front of the List
void insert_front(LIST *l,int productCode,char name[50],char category,float unitPrice,int quantity){
    NODE *tmp = (NODE*) malloc(sizeof(NODE));
    tmp->productCode = productCode;
    strcpy(tmp->name,name);
    tmp->category = category;
    tmp->unitPrice = unitPrice;
    tmp->quantity = quantity;
    if(l->head == NULL) tmp->next = NULL;
    else{
        tmp->next = l->head;
    }
    l->head = tmp;
    l->n += 1;
}

// Remove a node with given position
void remove_pos (LIST *l,int pos){
    if(pos == 0) {
        NODE *tmp = l->head;
        l->head = tmp->next;
        free(tmp);
        l->n -= 1;
    }
    else{
        NODE *tmp,*tmp2;
        //Find the node at position pos-1
        tmp2  = l->head;
        int i;
        for(i = 0; i<pos-1;i++){
            tmp2 = tmp2->next;
        }
        tmp = tmp2->next;
        tmp2->next = tmp->next;
        free(tmp);
        l->n -= 1;
    }
}

// Remove all nodes in the List
void destroy_list(LIST *l){
    NODE *tmp;
    while(l->head != NULL){
        tmp = l->head;
        l->head = tmp->next;
        free(tmp);
        l->n -=1;
    }
}

/*  Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy.
*/
void split(NODE *head,NODE **left,NODE **right){
    if(head == NULL || head->next == NULL){
        *left = head;
        *right = NULL;
        return;
    }
    NODE *slow = head;
    NODE *fast = head->next;
    // Advance 'fast' two nodes,and advance 'slow' one node
    while(fast != NULL){
        fast = fast->next;
        if(fast != NULL){
            slow = slow->next;
            fast = fast->next;
        }
    }
    // 'slow' is before the midpoint in the list,so split it in two at that point
    *left = head;
    *right = slow->next;
    slow->next = NULL;
}

/* Take two node sorted in increasing order,and splices together
   to make one big sorted list which is return */
// This function is to sort by productCode
NODE *sortedCode(NODE *left,NODE *right){
    if(left == NULL) return right;
    else if (right == NULL) return left;
    NODE *tmp = NULL;
    if(left->productCode <= right->productCode){
        tmp = left;
        tmp->next = sortedCode(left->next,right);
    }else{
        tmp = right;
        tmp->next = sortedCode(left,right->next);
    }
    return tmp;
}
// This function is to sort by name
NODE *sortedName(NODE *left,NODE *right){
    if(left == NULL) return right;
    else if (right == NULL) return left;
    NODE *tmp = NULL;
    left->name[0] = toupper(left->name[0]);
    right->name[0] = toupper(right->name[0]);
    if(strcmp(left->name,right->name) <= 0){
        tmp = left;
        tmp->next = sortedName(left->next,right);
    }else{
        tmp = right;
        tmp->next = sortedName(left,right->next);
    }
    return tmp;
}

// sorts the linked list by changing next pointer
void merge_sort(LIST *l,int n){
    // base case length 0 or 1
    if(l->head == NULL || l->head->next == NULL) {
        return;
    }
    NODE *tmp = l->head;
    NODE *left = NULL;
    NODE *right = NULL;
    // split head into 'left' and 'right' sublists
    split(tmp,&left,&right);
    // recursively sort the sublist
    merge_sort(&left,n);
    merge_sort(&right,n);
    // if user input 1 merge two sorted lists by product code
    // else merge two sorted lists by name
    if(n == 1) l->head = sortedCode(left,right);
    else l->head = sortedName(left,right);
}

// Print All existing product
void printAllProduct(LIST *l){
    if(l[0].head == NULL && l[1].head == NULL && l[2].head == NULL){
        printf("----------------------------------------------------------------------------------------\n");
        printf("%-15s %-15s %-15s %-15s %-15s\n","ProductCode","Name","Category","UnitPrice","Quantity");
        printf("----------------------------------------------------------------------------------------\n");
        return;
    }
    NODE *tmp1 = l[0].head;
    NODE *tmp2 = l[1].head;
    NODE *tmp3 = l[2].head;
    if(sorted_code){ // if productCode is sorted
        printSortedCode(l);
        printf("\n");
    }else if(sorted_name){ // if name is sorted
        printSortedName(l);
        printf("\n");
    }else{ // if product haven't sorted
        printf("----------------------------------------------------------------------------------------\n");
        printf("%-15s %-15s %-15s %-15s %-15s\n","ProductCode","Name","Category","UnitPrice","Quantity");
        printf("----------------------------------------------------------------------------------------\n");
        while(tmp1 != NULL){
            printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
            tmp1 = tmp1->next;
        }
        while(tmp2 != NULL){
            printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
            tmp2 = tmp2->next;
        }
        while(tmp3 != NULL){
            printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
            tmp3 = tmp3->next;
        }
        printf("\n");
    }
}

// Add a product function
void addProduct(LIST *l){
    int productCode,quantity,digit;
    char name[50],category;
    float unitPrice;
    //Ask user for category
    printf("Input Category (V = vegetables,F = Fruit,M = Meat): ");
    scanf(" %c",&category);
    checkCategory(&category);
    //Ask user for productCode
    printf("Input productCode (8 digits): ");
    scanf("%d",&productCode);
    checkProductCode(l,&productCode,category);
    //Ask user for their name
    printf("Input your name: ");
    scanf("%s",&name);
    //Ask user for unit Price
    printf("Input Unit Price: ");
    scanf("%f",&unitPrice);
    checkUnitPrice(&unitPrice);
    //Ask use for quantity
    printf("Input Quantity: ");
    scanf("%d",&quantity);
    checkQuantity(&quantity);
    // Check category and add to the specific linked list
    if(toupper(category) == 'F') insert_front(&l[0],productCode,name,toupper(category),unitPrice,quantity);
    else if(toupper(category) == 'V') insert_front(&l[1],productCode,name,toupper(category),unitPrice,quantity);
    else insert_front(&l[2],productCode,name,toupper(category),unitPrice,quantity);
    printf("Your product has been added\n");
}

// Modify or Update Product Function
void modifyProduct(LIST *l){
    if(l[0].head == NULL && l[1].head == NULL && l[2].head == NULL){
        printf("Products are empty\n");
        return;
    }
    char input[10],code[9],category;
    int productCode;
    printf("Input Product Code you want to modify: ");
    scanf("%s",&input);
    // Get category
    category = toupper(input[0]);
    // Get productCode by slice the first letter
    strncpy(code,input+1,8);
    productCode = atoi(code); // convert string to integer
    checkModify(l,&productCode,&category); // Check if product exist or not
    modify(l,&productCode,category); // Modify the product
}

// Delete a product if everything is checked
void deleteP(LIST *l,int productCode,char category){
    NODE *tmp;
    if(toupper(category) == 'F') tmp = l[0].head;
    else if(toupper(category) == 'V') tmp = l[1].head;
    else tmp = l[2].head;
    int pos = 0; // keep track of position
    while(tmp != NULL){
        if(tmp->productCode == productCode){ // if input ProductCode exist in the linked list
            if(toupper(category) == 'F') remove_pos(&l[0],pos);
            else if(toupper(category) == 'V') remove_pos(&l[1],pos);
            else remove_pos(&l[2],pos);
            break;
        }
        pos++;
        tmp = tmp->next;
    }
}

// Delete product function
void deleteProduct(LIST *l){
    if(l[0].head == NULL && l[1].head == NULL && l[2].head == NULL){
        printf("Products are empty\n");
        return;
    }
    char input[10],code[9],category;
    int productCode;
    printf("Input Product Code you want to delete: ");
    scanf("%9s",&input);
    // Get category
    category = toupper(input[0]);
    // Get productCode by slice the first letter
    strncpy(code,input+1,8);
    productCode = atoi(code);
    checkModify(l,&productCode,&category); // Check if product exist or not
    deleteP(l,productCode,category); // Delete a product
    printf("Product has been deleted\n");
}

// Sort product function
void sortProduct(LIST *l){
    int input;
    do{
        printf("1.Sort By productCode\n");
        printf("2.Sort By name\n");
        printf("Which option do you want? : ");
        scanf("%d",&input);
        if(input == 1) {
                merge_sort(&l[0],input);
                merge_sort(&l[1],input);
                merge_sort(&l[2],input);
                sorted_code = 1;
                sorted_name = 0;
                printf("Product has been sorted\n");
        }else if(input == 2){
            merge_sort(&l[0],input);
            merge_sort(&l[1],input);
            merge_sort(&l[2],input);
            sorted_code = 0;
            sorted_name = 1;
            printf("Product has been sorted\n");
        }else printf("Please input correct option\n");
    }while(input != 1 && input != 2);
}

// List a product that (price multiplied by quantity) are greater than input value function
void printSpecific(LIST *l){
    if(l[0].head == NULL && l[1].head == NULL && l[2].head == NULL){
        printf("Products are empty\n");
        return;
    }
    int n;
    printf("Input number: ");
    scanf("%d",&n);
    NODE *tmp = l[0].head;
    NODE *tmp1 = l[1].head;
    NODE *tmp2 = l[2].head;
    if(sorted_code){
        printSortedCodeSpecific(l,n);
        printf("\n");
    }else if(sorted_name){
        printSortedNameSpecific(l,n);
        printf("\n");
    }else{
        printf("----------------------------------------------------------------------------------------\n");
        printf("%-15s %-15s %-15s %-15s %-15s\n","ProductCode","Name","Category","UnitPrice","Quantity");
        printf("----------------------------------------------------------------------------------------\n");
        while(tmp != NULL){
            if((tmp->quantity * tmp->unitPrice) > n) printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp->productCode,tmp->name,tmp->category,tmp->unitPrice,tmp->quantity);
            tmp = tmp->next;
        }
        while(tmp1 != NULL){
            if((tmp1->quantity * tmp1->unitPrice) > n) printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
            tmp1 = tmp1->next;
        }
        while(tmp2 != NULL){
            if((tmp2->quantity * tmp2->unitPrice) > n) printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
            tmp2 = tmp2->next;
        }
    }

}

// get hash key function
int hash(char str[],int M){
    int length = strlen(str);
    int n = 0;
    for(int i = 0;i<length;i++){
        n += (int) str[i];
    }
    return n % M;
}

// Insert into hash table
void insertHash(LIST *l,int M,int productCode,char str[],char category,float UnitPrice,int quantity){
    int index = hash(str,M);
    NODE *tmp = (NODE*) malloc(sizeof(NODE));
    tmp->productCode = productCode;
    strcpy(tmp->name,str);
    tmp->category = category;
    tmp->unitPrice = UnitPrice;
    tmp->quantity = quantity;
    tmp->next = NULL;
    if(l[index].head == NULL){
        l[index].head = tmp;
    }else{
        NODE *tmp1 = l[index].head;
        while(tmp1->next != NULL) tmp1 = tmp1->next;
        tmp1->next = tmp;
    }
    l[index].n += 1;
}

// Search Hash function
int searchHash(LIST *l,int M,char str[]){
    int index = hash(str,M);
    int found = 0;
    if(l[index].head == NULL){
        return 0;
    }else{
        NODE *tmp = l[index].head; // initial node to List head of hash key
        while(tmp != NULL){
            if(strcmp(tmp->name,str) == 0){
                printf("-----------------------------------FOUND------------------------------------------------\n");
                printf("%-15s %-15s %-15s %-15s %-15s\n","ProductCode","Name","Category","UnitPrice","Quantity");
                printf("----------------------------------------------------------------------------------------\n");
                printf("%-15d %-15s %-15c %-15.2f %-15d\n\n",tmp->productCode,tmp->name,tmp->category,tmp->unitPrice,tmp->quantity);
                found = 1;
                break;
            }
            tmp = tmp->next;
        }
    }
    if(found) return 1;
    else return 0;
}

// Search Product Function
void searchProduct(LIST *l){
    if(l[0].head == NULL && l[1].head == NULL && l[2].head == NULL){
        printf("Products are empty\n");
        return;
    }
    int M = l[0].n + l[1].n + l[2].n; // Get Size of List
    char name[50];
    LIST *table = create_list(M);
    NODE *tmp = l[0].head;
    NODE *tmp1 = l[1].head;
    NODE *tmp2 = l[2].head;
    // Insert every product to the hash table
    while(tmp != NULL){
        insertHash(table,M,tmp->productCode,tmp->name,tmp->category,tmp->unitPrice,tmp->quantity);
        tmp = tmp->next;
    }
    while(tmp1 != NULL){
        insertHash(table,M,tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
        tmp1 = tmp1->next;
    }
    while(tmp2 != NULL){
        insertHash(table,M,tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
        tmp2 = tmp2->next;
    }
    printf("Input name: ");
    scanf("%s",&name);
    // Search name in the Hash table
    while(!searchHash(table,M,name)){
        printf("-------------------------------------NOT FOUND-----------------------------------------\n");
        printf("Input name again: ");
        scanf("%s",&name);
    }
}

// Save all product to file
void savetoFile(LIST *l){
    char path[100];
    printf("Input path you want to save: ");
    scanf("%s",&path);
    FILE *f = fopen(path,"w");
    fprintf(f,"%-15s %-15s\n","Sorted Code","Sorted Name");
    fprintf(f,"%-15d %-15d\n",sorted_code,sorted_name);
    fprintf(f,"%-15s %-15s %-15s %-15s %-15s\n","Product Code","Name","Category","Unit Price","Quantity");
    NODE *tmp1 = l[0].head;
    NODE *tmp2 = l[1].head;
    NODE *tmp3 = l[2].head;
    while(tmp1 != NULL){
        fprintf(f,"%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
        tmp1 = tmp1->next;
    }
    while(tmp2 != NULL){
        fprintf(f,"%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
        tmp2 = tmp2->next;
    }
    while(tmp3 != NULL){
        fprintf(f,"%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
        tmp3 = tmp3->next;
    }
    fclose(f);
    printf("Product has been save to file\n");
}

// Load product from file function
void loadfromFile(LIST *l){
    char path[100];
    char ignore[100];
    char sortedcode[2],sortedname[2];
    char productCode[10],Name[50],Category[5],UnitPrice[100],Quantity[100];
    int productcode,quantity;
    float unitprice;
    printf("Input path you want to load: ");
    scanf("%s",&path);
    FILE *f = fopen(path,"r");
    if(f == NULL){
        printf("File not Found");
        return;
    }
    fgets(ignore, 100, f);
    fscanf(f,"%s %s",sortedcode,sortedname);
    sorted_code = atoi(sortedcode);
    sorted_name = atoi(sortedname);
    fgets(ignore, 100, f);
    fgets(ignore, 100, f);
    // Remove all product before load from file
    destroy_list(&l[0]);
    destroy_list(&l[1]);
    destroy_list(&l[2]);
    while(fscanf(f,"%s %s %s %s %s",productCode,Name,Category,UnitPrice,Quantity) != EOF){
        productcode = atoi(productCode);
        unitprice = atof(UnitPrice);
        quantity = atoi(Quantity);
        if(Category[0] == 'F'){
            insert_front(&l[0],productcode,Name,'F',unitprice,quantity);
        }else if(Category[0] == 'V'){
            insert_front(&l[1],productcode,Name,'V',unitprice,quantity);
        }else{
            insert_front(&l[2],productcode,Name,'M',unitprice,quantity);
        }
    }
    reverse_list(&l[0]);
    reverse_list(&l[1]);
    reverse_list(&l[2]);
    fclose(f);
    printf("File Loaded\n");
}

// Find digit of numbers function
int findDigit(int digit){
    int n = 0;
    while(digit != 0){
        digit = digit / 10;
        n++;
    }
    return n;
}

// Check if user input the right category Function
void checkCategory(char *c){
    int ascii = (int) toupper(*c);
    int valid = 0;
    if(ascii != 70 && ascii != 77 && ascii != 86){ // If user input is not F,V,M
        printf("We have only three category (F = Fruit,V = vegetables,M = Meat)\n");
    }else return;
    do{
        printf("Please Input again: ");
        scanf(" %c",c);
        ascii = (int) toupper(*c);
        if(ascii != 70 && ascii != 77 && ascii != 86){
        printf("We have only three category (F = Fruit,V = vegetables,M = Meat)\n");
        }else valid = 1;
    }while(!valid);
}

// Check if the productCode is already exist in the Category Function
int checkExistCode(LIST *l,int productCode,char category){
    NODE *tmp;
    if(toupper(category) == 'F') tmp = l[0].head;
    else if(toupper(category) == 'V') tmp = l[1].head;
    else tmp = l[2].head;
    while(tmp != NULL){
            if(tmp->productCode == productCode) return 1;
            tmp = tmp->next;
    }
    return 0;
}

// Check if the product code is 8 digits or not Function
void checkProductCode(LIST *l,int *productCode,char category){
    int digit = findDigit(*productCode);
    int check;
    int valid = 0;
    if(digit < 8 || digit > 8){
        printf("Product Code must be 8 digits.\n");
    }else{
        check = checkExistCode(l,*productCode,category);
        if(check)printf("This productCode is already exist.\n");
        else return;
    }
    do{
        printf("Please Input Product Code again: ");
        scanf("%d",productCode);
        digit = findDigit(*productCode);
        if(digit < 8 || digit > 8){
            printf("Product Code must be 8 digits.\n");
        }else{
            check = checkExistCode(l,*productCode,category);
            if(check) printf("This productCode is already exist.\n");
            else valid = 1;
        }
    }while(!valid);
}

// Check unitPrice is not 0 Function
void checkUnitPrice(int *uPrice){
    if(*uPrice <= 0){
        printf("Price can not be 0.\n");
    }else return;
    do{
        printf("Please Input Unit Price again: ");
        scanf("%d",uPrice);
        if(*uPrice <= 0){
        printf("Price can not be 0.\n");
        }
    }while(*uPrice <= 0);
}

// Check Quantity is not 0 Function
void checkQuantity(int *quantity){
    if(*quantity <= 0){
        printf("Quantity can not be 0.\n");
    }else return;
    do{
        printf("Please Input Quantity again: ");
        scanf("%d",quantity);
        if(*quantity <= 0){
        printf("Quantity can not be 0.\n");
        }
    }while(*quantity <= 0);
}

//Check if the product is exist to modify Function
void checkModify(LIST *l,int *productCode,char *category){
    int check = checkExistCode(l,*productCode,*category);
    char input[10],code[9];
    if(check == 0){
        printf("This product doesn't exist\n");
    }else return;
    do{
        printf("Input Product Code again: ");
        scanf("%s",&input);
        *category = toupper(input[0]);
        strncpy(code,input+1,8);
        *productCode = atoi(code);
        check = checkExistCode(l,*productCode,*category);
        if(check) return;
    }while(check == 0);

}

// Modify Product Function if everything is checked
void modify(LIST *l,int *productCode,char category){
    NODE *tmp;
    if(toupper(category) == 'F') tmp = l[0].head;
    else if(toupper(category) == 'V') tmp = l[1].head;
    else tmp = l[2].head;
    char name[50],cat;
    float unitPrice;
    int quantity;
    while(tmp != NULL){
        if(tmp->productCode == *productCode){
            printf("Input name: ");
            scanf("%s",&name);
            printf("Input Unit Price: ");
            scanf("%f",&unitPrice);
            checkUnitPrice(&unitPrice);
            printf("Input quantity: ");
            scanf("%d",&quantity);
            checkQuantity(&quantity);
            printf("Input category: ");
            scanf(" %c",&cat);
            checkCategory(&cat);
            // If category is changed
            if(toupper(cat) != tmp->category){
                while(checkExistCode(l,*productCode,cat)){ // Check if the new product is already exist
                    printf("This productCode is already exist\n");
                    printf("Input new productCode: ");
                    scanf("%d",productCode);
                }
                // Delete product in the current category
                deleteP(l,*productCode,toupper(category));
                // Add new product to the new category
                if(toupper(cat) == 'F') insert_front(&l[0],*productCode,name,toupper(cat),unitPrice,quantity);
                else if(toupper(cat) == 'V') insert_front(&l[1],*productCode,name,toupper(cat),unitPrice,quantity);
                else if(toupper(cat) == 'M') insert_front(&l[2],*productCode,name,toupper(cat),unitPrice,quantity);
                printf("Product has been modified\n");
                return;
            }
            // If category is not changed
            strcpy(tmp->name,name);
            tmp->unitPrice = unitPrice;
            tmp->quantity = quantity;
            break;
        }
        tmp = tmp->next;
    }
    printf("Product has been modified\n");
}

// Print the product sort by product code function
void printSortedCode(LIST *l){
    NODE *tmp1 = l[0].head;
    NODE *tmp2 = l[1].head;
    NODE *tmp3 = l[2].head;
    printf("----------------------------------------------------------------------------------------\n");
    printf("%-15s %-15s %-15s %-15s %-15s\n","ProductCode","Name","Category","UnitPrice","Quantity");
    printf("----------------------------------------------------------------------------------------\n");
    while(1){
    if(tmp1 == NULL && tmp2 == NULL && tmp3 == NULL){
        return;
    }
    if(tmp1 != NULL && tmp2 != NULL && tmp3 != NULL){
            if(tmp1->productCode <= tmp2->productCode && tmp1->productCode <= tmp3->productCode){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
                tmp1 = tmp1->next;
            }else if(tmp2->productCode <= tmp1->productCode && tmp2->productCode <= tmp3->productCode){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
                tmp2 = tmp2->next;
            }else if(tmp3->productCode <= tmp1->productCode && tmp3->productCode <= tmp2->productCode){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
                tmp3 = tmp3->next;
            }
    }else if(tmp1 != NULL && tmp2 == NULL && tmp3 != NULL){
            if(tmp1->productCode <= tmp3->productCode){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
                tmp1 = tmp1->next;
            }else if(tmp3->productCode <= tmp1->productCode){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
                tmp3 = tmp3->next;
            }
    }else if(tmp1 == NULL && tmp2 != NULL && tmp3 != NULL){
            if(tmp2->productCode <= tmp3->productCode){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
                tmp2 = tmp2->next;
            }else if(tmp3->productCode <= tmp2->productCode){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
                tmp3 = tmp3->next;
            }
    }else if(tmp1 != NULL && tmp2 != NULL && tmp3 == NULL){
            if(tmp1->productCode <= tmp2->productCode){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
                tmp1 = tmp1->next;
            }else if(tmp2->productCode <= tmp1->productCode){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
                tmp2 = tmp2->next;
            }
    }else if(tmp1 != NULL){
            printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
            tmp1 = tmp1->next;
    }else if(tmp2 != NULL){
            printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
            tmp2 = tmp2->next;
    }else if(tmp3 != NULL){
            printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
            tmp3 = tmp3->next;
    }
    }
}

// Print the product sort by product code function and stock value are greater than given number
void printSortedCodeSpecific(LIST *l,int given){
    NODE *tmp1 = l[0].head;
    NODE *tmp2 = l[1].head;
    NODE *tmp3 = l[2].head;
    printf("----------------------------------------------------------------------------------------\n");
    printf("%-15s %-15s %-15s %-15s %-15s\n","ProductCode","Name","Category","UnitPrice","Quantity");
    printf("----------------------------------------------------------------------------------------\n");
    while(1){
    if(tmp1 == NULL && tmp2 == NULL && tmp3 == NULL){
        return;
    }
    if(tmp1 != NULL && tmp2 != NULL && tmp3 != NULL){
            if(tmp1->productCode <= tmp2->productCode && tmp1->productCode <= tmp3->productCode){
                if((tmp1->quantity * tmp1->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
                tmp1 = tmp1->next;
            }else if(tmp2->productCode <= tmp1->productCode && tmp2->productCode <= tmp3->productCode){
                if((tmp2->quantity * tmp2->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
                tmp2 = tmp2->next;
            }else if(tmp3->productCode <= tmp1->productCode && tmp3->productCode <= tmp2->productCode){
                if((tmp3->quantity * tmp3->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
                tmp3 = tmp3->next;
            }
    }else if(tmp1 != NULL && tmp2 == NULL && tmp3 != NULL){
            if(tmp1->productCode <= tmp3->productCode){
                if((tmp1->quantity * tmp1->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
                tmp1 = tmp1->next;
            }else if(tmp3->productCode <= tmp1->productCode){
                if((tmp3->quantity * tmp3->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
                tmp3 = tmp3->next;
            }
    }else if(tmp1 == NULL && tmp2 != NULL && tmp3 != NULL){
            if(tmp2->productCode <= tmp3->productCode){
                if((tmp2->quantity * tmp2->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
                tmp2 = tmp2->next;
            }else if(tmp3->productCode <= tmp2->productCode){
                if((tmp3->quantity * tmp3->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
                tmp3 = tmp3->next;
            }
    }else if(tmp1 != NULL && tmp2 != NULL && tmp3 == NULL){
            if(tmp1->productCode <= tmp2->productCode){
                if((tmp1->quantity * tmp1->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
                tmp1 = tmp1->next;
            }else if(tmp2->productCode <= tmp1->productCode){
                if((tmp2->quantity * tmp2->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
                tmp2 = tmp2->next;
            }
    }else if(tmp1 != NULL ){
            if((tmp1->quantity * tmp1->unitPrice) > given)
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
            tmp1 = tmp1->next;
    }else if(tmp2 != NULL){
            if((tmp2->quantity * tmp2->unitPrice) > given)
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
            tmp2 = tmp2->next;
    }else if(tmp3 != NULL){
            if((tmp3->quantity * tmp3->unitPrice) > given)
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
            tmp3 = tmp3->next;
    }
    }
}

// Print the product sort by Name function
void printSortedName(LIST *l){
    NODE *tmp1 = l[0].head;
    NODE *tmp2 = l[1].head;
    NODE *tmp3 = l[2].head;
    printf("----------------------------------------------------------------------------------------\n");
    printf("%-15s %-15s %-15s %-15s %-15s\n","ProductCode","Name","Category","UnitPrice","Quantity");
    printf("----------------------------------------------------------------------------------------\n");
    while(1){
    if(tmp1 == NULL && tmp2 == NULL && tmp3 == NULL){
        return;
    }
    if(tmp1 != NULL && tmp2 != NULL && tmp3 != NULL){
            if(strcmp(tmp1->name,tmp2->name) <= 0 && strcmp(tmp1->name,tmp3->name) <= 0){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
                tmp1 = tmp1->next;
            }else if(strcmp(tmp2->name,tmp1->name) <= 0 && strcmp(tmp2->name,tmp1->name) <= 0){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
                tmp2 = tmp2->next;
            }else if(strcmp(tmp3->name,tmp1->name) <= 0 && strcmp(tmp3->name,tmp1->name) <= 0){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
                tmp3 = tmp3->next;
            }
    }else if(tmp1 != NULL && tmp2 == NULL && tmp3 != NULL){
            if(strcmp(tmp1->name,tmp3->name) <= 0){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
                tmp1 = tmp1->next;
            }else if(strcmp(tmp3->name,tmp1->name) <= 0){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
                tmp3 = tmp3->next;
            }
    }else if(tmp1 == NULL && tmp2 != NULL && tmp3 != NULL){
            if(strcmp(tmp2->name,tmp3->name) <= 0){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
                tmp2 = tmp2->next;
            }else if(strcmp(tmp3->name,tmp2->name) <= 0){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
                tmp3 = tmp3->next;
            }
    }else if(tmp1 != NULL && tmp2 != NULL && tmp3 == NULL){
            if(strcmp(tmp1->name,tmp2->name) <= 0){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
                tmp1 = tmp1->next;
            }else if(strcmp(tmp2->name,tmp1->name) <= 0){
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
                tmp2 = tmp2->next;
            }
    }else if(tmp1 != NULL){
            printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
            tmp1 = tmp1->next;
    }else if(tmp2 != NULL){
            printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
            tmp2 = tmp2->next;
    }else if(tmp3 != NULL){
            printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
            tmp3 = tmp3->next;
        }else continue;
    }
}

// Print the product sort by Name function and stock value are greater than given number
void printSortedNameSpecific(LIST *l,int given){
    NODE *tmp1 = l[0].head;
    NODE *tmp2 = l[1].head;
    NODE *tmp3 = l[2].head;
    printf("----------------------------------------------------------------------------------------\n");
    printf("%-15s %-15s %-15s %-15s %-15s\n","ProductCode","Name","Category","UnitPrice","Quantity");
    printf("----------------------------------------------------------------------------------------\n");
    while(1){
    if(tmp1 == NULL && tmp2 == NULL && tmp3 == NULL){
        return;
    }
    if(tmp1 != NULL && tmp2 != NULL && tmp3 != NULL){
            if(strcmp(tmp1->name,tmp2->name) <= 0 && strcmp(tmp1->name,tmp3->name) <= 0){
                if((tmp1->quantity * tmp1->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
                tmp1 = tmp1->next;
            }else if(strcmp(tmp2->name,tmp1->name) <= 0 && strcmp(tmp2->name,tmp1->name) <= 0 ){
                if((tmp2->quantity * tmp2->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
                tmp2 = tmp2->next;
            }else if(strcmp(tmp3->name,tmp1->name) <= 0 && strcmp(tmp3->name,tmp1->name) <= 0){
                if((tmp3->quantity * tmp3->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
                tmp3 = tmp3->next;
            }
    }else if(tmp1 != NULL && tmp2 == NULL && tmp3 != NULL){
            if(strcmp(tmp1->name,tmp3->name) <= 0 ){
                if((tmp1->quantity * tmp1->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
                tmp1 = tmp1->next;
            }else if(strcmp(tmp3->name,tmp1->name) <= 0){
                if((tmp3->quantity * tmp3->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
                tmp3 = tmp3->next;
            }
    }else if(tmp1 == NULL && tmp2 != NULL && tmp3 != NULL){
            if(strcmp(tmp2->name,tmp3->name) <= 0){
                if((tmp2->quantity * tmp2->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
                tmp2 = tmp2->next;
            }else if(strcmp(tmp3->name,tmp2->name) <= 0){
                if((tmp3->quantity * tmp3->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
                tmp3 = tmp3->next;
            }
    }else if(tmp1 != NULL && tmp2 != NULL && tmp3 == NULL){
            if(strcmp(tmp1->name,tmp2->name) <= 0 ){
                if((tmp1->quantity * tmp1->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
                tmp1 = tmp1->next;
            }else if(strcmp(tmp2->name,tmp1->name) <= 0 ){
                if((tmp2->quantity * tmp2->unitPrice) > given)
                    printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
                tmp2 = tmp2->next;
            }
    }else if(tmp1 != NULL){
            if((tmp1->quantity * tmp1->unitPrice) > given)
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp1->productCode,tmp1->name,tmp1->category,tmp1->unitPrice,tmp1->quantity);
            tmp1 = tmp1->next;
    }else if(tmp2 != NULL){
            if((tmp2->quantity * tmp2->unitPrice) > given)
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp2->productCode,tmp2->name,tmp2->category,tmp2->unitPrice,tmp2->quantity);
            tmp2 = tmp2->next;
    }else if(tmp3 != NULL ){
            if((tmp3->quantity * tmp3->unitPrice) > given)
                printf("%-15d %-15s %-15c %-15.2f %-15d\n",tmp3->productCode,tmp3->name,tmp3->category,tmp3->unitPrice,tmp3->quantity);
            tmp3 = tmp3->next;
        }
    }
}


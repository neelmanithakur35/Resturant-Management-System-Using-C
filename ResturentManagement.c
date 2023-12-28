#include<stdio.h>
#include<string.h>
#include<stdlib.h>



// Multiple Items and Prices Related Data Storage
struct items{
    char item[20];
    float price;
    int qty;
};

//Customer And Orders Related Informations Storage
struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50]; // Structure Array variable For n number of Items
};

//functions to generate biils with Bill Body Structures
//1.Bill Header Generation (Upper Part Of Billing)
void generateBillHeader(char name[50],char date[30]){
    printf("\n\n");
        printf("\t    Restaurant Management System");
        printf("\n\t   -----------------");
        printf("\nDate:%s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("---------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n---------------------------------------");
        printf("\n\n");
}

//2. Bill Body/Middle Part Generating Fuction
void generateBillBody(char item[30],int qty, float price){
        printf("%s\t\t",item);
        printf("%d\t\t",qty);
        printf("%.2f\t\t",qty * price);
        printf("\n");
}


//3. Lower Bill Part (Footer) of Billing

void generateBillFooter(float total){
    printf("\n");
         //10% Default Discount
    float dis = 0.1*total;
    //Total Discount Calculation
    float netTotal=total-dis;
           //netTotal + cgst + sgstCalculation
    float cgst=0.09*netTotal,grandTotal=netTotal + 2*cgst;
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n---------------------------------------\n");
}


// Main Function
int main(){

    int opt,n;
    struct orders ord; //Structure Variables
    struct orders order;
    char saveBill = 'y',contFlag = 'y'; //Choice Characters
    char name[50];

    FILE *fp;   //File Pointer to Store File Address

    while(contFlag == 'y'){

      system("cls");// DOS Command

    float total = 0;     //Setting Defaut Values
    int invoiceFound = 0;

    //Resturant Dashboard

    printf("\t|*|****************RESTAURANT MANAGEMENT SYSTEM****************|*|");
    printf("\n\n\tPlease select your prefered operation");
    printf("\n\n\t[1].Generate Invoice");
    printf("\n\t[2].Show all Invoices");
    printf("\n\t[3].Search Invoice");
    printf("\n\t[4].Exit");

    printf("\n\nYour choice:\t");
    scanf("%d",&opt);
    fgetc(stdin); //Clear the Input Buffer

    switch(opt){
    case 1:

        system("cls"); //Clears Console Screen

        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1] = 0;
        // Assigning Today's Date Using --DATE-- MACRO
        strcpy(ord.date,__DATE__);
        printf("\nPlease enter the number of items:\t");
        scanf("%d",&n);
        ord.numOfItems = n;
       //Loop For Item Input
         for(int i=0;i<n;i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d:\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please enter the quantity:\t");
            scanf("%d",&ord.itm[i].qty);
            printf("Please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }
          //Calling or Billing Header Printing
        generateBillHeader(ord.customer,ord.date);


        for(int i=0;i<ord.numOfItems;i++){
            generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        //Bill Footer Printing
        generateBillFooter(total);


        printf("\nDo you want to save the invoice [y/n]:\t");
        scanf("%s",&saveBill);
       //Saving Current Bill Into a File Future Utilization
        if(saveBill == 'y'){
            fp = fopen("RestaurantBill.txt","a+"); //Append Mode File Opening
            fwrite(&ord,sizeof(struct orders),1,fp); //Writing The Structure Data Into File
            if(fwrite != 0) //Checks For Returned Write Value
            printf("\nSuccessfully saved");
            else
            printf("\nError saving");
            fclose(fp);
        }
        break;

    case 2:
        system("cls");
        fp = fopen("RestaurantBill.txt","r");
        printf("\n  ***** *** Previous Invoices *** *****\n");

         // Reading data from Text File
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;


            generateBillHeader(order.customer,order.date); //Header Printing Call

            for(int i=0;i<order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price; //Total Bill Calculation
            }
            generateBillFooter(tot); // Bill Footer Printing Call
        }
        fclose(fp);
        break;

        case 3:
        printf("Enter the name of the customer:\t");
        //fgetc(stdin);     //Flushing Standard input Buffer

        fgets(name,50,stdin);
        name[strlen(name)-1] = 0;
        system("cls");//Clear console Screen
        fp = fopen("RestaurantBill.txt","r");
        printf("\n\t*** ** Invoice of %s ** ***",name);

        //Invoice Generating for the Person from Text File

        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            if(!strcmp(order.customer,name)){
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot);
            invoiceFound = 1;
            }

        }
        if(!invoiceFound){
            printf("\nSorry the invoice for %s does not exists",name);
        }
        fclose(fp);
        break;

    case 4:  //Exits The Application Software
    printf("\n\t\t Thanks For Using :) :)\n\n");
    exit(0);
    break;

    default:
    printf("Sorry invalid option");
    break;
    }
    printf("\nDo you want to perform another operation?[y/n]:\t");
    scanf("%s",&contFlag);
    }
    printf("\n\t\t Bye Bye :)\n\n");
    printf("\n\n");

    return 0;
}


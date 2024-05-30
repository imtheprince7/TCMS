#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include <errno.h>

#define clrscr() system("cls");

struct VehicleRecord
{
    char vehicle_no[10];
    int vehicle_type;
    char owner_name[30];
    long long int phone;
    int seater;
    char fuel_type[10];
    char RTO_no[15];
    char address[50];
    char violated[10];
    int times;
    int fine;
}v;

FILE *fp;

void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void insertRecord()
{
        gotoxy(80,15);
        printf("=======================================");
        gotoxy(88,16);
        printf("INSERT VEHICLE RECORD");
        gotoxy(80,17);
        printf("=======================================");
        gotoxy(70,19);
        printf("Enter vehicle number : ");
        fflush(stdin);
        gets(v.vehicle_no);
        gotoxy(70,20);
        printf("Wheeler : 2/3/4 : ");
        scanf("%d",&v.vehicle_type);
        gotoxy(70,21);
        printf("Enter Owner name : ");
        fflush(stdin);
        gets(v.owner_name);
        gotoxy(70,22);
        printf("Enter mobile number : ");
        scanf("%lld",&v.phone);
        gotoxy(70,23);
        printf("Enter seater : ");
        scanf("%d",&v.seater);
        gotoxy(70,24);
        printf("Enter fuel type : ");
        fflush(stdin);
        gets(v.fuel_type);
        gotoxy(70,25);
        printf("Enter RTO number : ");
        fflush(stdin);
        gets(v.RTO_no);
        gotoxy(70,26);
        printf("Enter Address : ");
        fflush(stdin);
        gets(v.address);
        gotoxy(70,27);
        printf("violated Traffic Rules (yes/no) : ");
        fflush(stdin);
        gets(v.violated);
        char s[10]="yes";
        if(!strcmp(v.violated,s))
        {
            gotoxy(70,28);
            printf("No. of Times violated : ");
            scanf("%d",&v.times);
            gotoxy(70,29);
            printf("Enter amount paid : ");
            scanf("%d",&v.fine);
            gotoxy(70,31);
            printf("==================================================");
            gotoxy(80,32);
            printf("vehicle record successfully added");
            gotoxy(70,33);
            printf("==================================================");    
            gotoxy(80,35);
        }
        else
        {
            v.times=0;
            v.fine=0;
            gotoxy(70,29);
            printf("==================================================");
            gotoxy(80,30);
            printf("vehicle record successfully added");
            gotoxy(70,31);
            printf("==================================================");    
            gotoxy(80,33);
        }
        fp=fopen("database.txt","ab+");
        fwrite(&v,sizeof(v),1,fp);
        fclose(fp);      
}

void deleteRecord()
{
    FILE *fp1;
    int found=0;
    char number[10];
    gotoxy(80,15);
    printf("=======================================");
    gotoxy(85,16);
    printf("DELETE VEHICLE RECORD");
    gotoxy(80,17);
    printf("=======================================");
    gotoxy(85,20);
    fp=fopen("database.txt","rb+");
    if(fp==NULL)
    {
        printf("*** ERROR OPENING FILE ***");
        fclose(fp);
        return;
    }
    if(fp!=NULL)
    {
        fseek(fp,0,SEEK_END);
        int size = ftell(fp);
        if(size == 0)
        {
            printf("***** EMPTY FILE *****");
            fclose(fp);
            return;
        }
        rewind(fp);

    }
    printf("Enter vehicle no : ");
    fflush(stdin);
    gets(number);
    fp1=fopen("temporary.txt","ab+");
    while(fread(&v,sizeof(v),1,fp))
    {
        if((strcmp(v.vehicle_no,number))==0)
        {
            found = 1;
        }
        else
        {
            fwrite(&v,sizeof(v),1,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);
    remove("database.txt");
    rename("temporary.txt","database.txt");
    if(!found)
    {
        gotoxy(85,22);
        printf("**** RECORD NOT FOUND ****");
        return;
    }
    if(found)
    {
        gotoxy(80,22);
        printf("*** VEHICLE RECORD DELETED SUCCESSFULLY ***");
    }
}

void searchRecord()
{
    gotoxy(80,15);
    printf("=======================================");
    gotoxy(88,16);
    printf("SEARCH VEHICLE RECORD");
    gotoxy(80,17);
    printf("=======================================");
    int found=0;
    char number[10];
    fp=fopen("database.txt","rb+");
    if(fp==NULL)
    {
        gotoxy(84,19);
        printf("*** ERROR OPENING FILE ***");
        gotoxy(80,21);
        fclose(fp);
        return;
    }
    if(fp!=NULL)
    {
        fseek(fp,0,SEEK_END);
        int size = ftell(fp);
        if(size == 0)
        {
            gotoxy(84,19);
            printf("***** EMPTY FILE *****");
            gotoxy(80,21);
            fclose(fp);
            return;
        }
        rewind(fp);
    }
    gotoxy(84,19);
    printf("Enter Vehicle number : ");
    fflush(stdin);
    gets(number);
    while(fread(&v,sizeof(v),1,fp))
    {
        if(!strcmp(v.vehicle_no,number))
        {
            found=1;
            gotoxy(80,21);
            printf("vehicle number : %s",v.vehicle_no);
            gotoxy(80,22);
            printf("vehicle type : %d",v.vehicle_type);
            gotoxy(80,23);
            printf("vehicle owner : %s",v.owner_name);
            gotoxy(80,24);
            printf("owner mobile number : %lld",v.phone);
            gotoxy(80,25);
            printf("Seater : %d-seater",v.seater);
            gotoxy(80,26);
            printf("Fuel type : %s",v.fuel_type);
            gotoxy(80,27);
            printf("RTO number : %s",v.RTO_no);
            gotoxy(80,28);
            printf("Address : %s",v.address);
            gotoxy(80,29);
            printf("Ever violated traffic rules ? : %s",v.violated);
            gotoxy(80,30);
            printf("No. of times violated: %d",v.times);
            gotoxy(80,31);
            printf("Total fine paid till now : %d",v.fine);
            gotoxy(80,33);
        }
    }
    if(found==0)
    {
        gotoxy(80,21);
        printf("***** EMPLOYEE RECORD NOT FOUND *****");
        gotoxy(80,23);
    }
    fclose(fp);

}

void updateRecord()
{
    int found=0;
    char number[10];
    gotoxy(80,15);
    printf("=======================================");
    gotoxy(88,16);
    printf("UPDATE VEHICLE RECORD");
    gotoxy(80,17);
    printf("=======================================");
    fp=fopen("database.txt","rb+");
    if(fp==NULL)
    {
        gotoxy(84,19);
        printf("*** ERROR OPENING FILE ***");
        gotoxy(80,21);
        fclose(fp);
        return;
    }
    if(fp!=NULL)
    {
        fseek(fp,0,SEEK_END);
        int size = ftell(fp);
        if(size == 0)
        {
            gotoxy(84,19);
            printf("***** EMPTY FILE *****");
            gotoxy(80,21);
            fclose(fp);
            return;
        }
        rewind(fp);
    }
    gotoxy(80,19);
    printf("Enter Vehicle number you want to modify : ");
    fflush(stdin);
    gets(number);
    while(fread(&v,sizeof(v),1,fp))
    {
        if(!strcmp(v.vehicle_no,number))
        {
            found =1;
            gotoxy(80,23);
            printf("Enter wheeler (2/3/4) : ");
            scanf("%d",&v.vehicle_type);
            gotoxy(80,24);
            printf("Enter new owner name : ");
            fflush(stdin);
            gets(v.owner_name);
            gotoxy(80,25);
            printf("Enter new Phone number : ");
            scanf("%lld",&v.phone);
            gotoxy(80,26);
            printf("Enter new Seater : ");
            scanf("%d",&v.seater);
            gotoxy(80,27);
            printf("Enter new fuel Type : ");
            fflush(stdin);
            gets(v.fuel_type);
            gotoxy(80,28);
            printf("Enter new RTO number : ");
            fflush(stdin);
            gets(v.RTO_no);
            gotoxy(80,29);
            printf("Enter new address : ");
            fflush(stdin);
            gets(v.address);
            gotoxy(80,30);
            printf("violated Traffic Rules (yes/no) : ");
            fflush(stdin);
            gets(v.violated);
            char s[10]="yes";
            if(!strcmp(v.violated,s))
            {
                gotoxy(80,31);
                printf("Enter no. of times violated : ");
                scanf("%d",&v.times);
                gotoxy(80,32);
                printf("Enter Fine paid till now : ");
                scanf("%d",&v.fine);
                gotoxy(80,34);
                printf("*** VEHICLE RECORD SUCCESSFULLY UPDATED ***");
                gotoxy(80,36);
            }
            else
            {
                v.times=0;
                v.fine=0;
                gotoxy(80,32);
                printf("*** VEHICLE RECORD SUCCESSFULLY UPDATED");
                gotoxy(80,34);
            }
            fseek(fp,-sizeof(v),SEEK_CUR);
            fwrite(&v,sizeof(v),1,fp);
            break;
        }
    }
        if(found==0)
        {
            gotoxy(80,21);
            printf("***** EMPLOYEE RECORD NOT FOUND *****");
            gotoxy(80,23);
        }
    fclose(fp);
}

void displayRecord()
{
    gotoxy(80,2);
    printf("=======================================");
    gotoxy(87,3);
    printf("Display VEHICLE RECORD");
    gotoxy(80,4);
    printf("=======================================");
    fp=fopen("database.txt","rb+");
    if(fp==NULL)
    {
        gotoxy(85,7);
        printf("*** ERROR OPENING FILE ***");
        gotoxy(80,10);
        fclose(fp);
        return;
    }
    if(fp!=NULL)
    {
        fseek(fp,0,SEEK_END);
        int size = ftell(fp);
        if(size == 0)
        {
            gotoxy(85,7);
            printf("***** EMPTY FILE *****");
            gotoxy(80,10);
            fclose(fp);
            return;
        }
        rewind(fp);
    }
    gotoxy(2,8);
    printf("Vehicle no    vehicle type  owner name    Mobile number   Seater   Fuel type   RTO Number         Address               Ever violated ?  No.of times violated  Fine paid till now");
    gotoxy(2,10);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    int j=12;
    while(fread(&v,sizeof(v),1,fp))
    {
        gotoxy(2,j);
        printf("%-15s%d-wheeler    %-15s  %-13lld %d-seater   %-11s  %-14s  %-30s %-16s  %-16d %-19d",v.vehicle_no,v.vehicle_type,v.owner_name,v.phone,v.seater,v.fuel_type,v.RTO_no,v.address,v.violated,v.times,v.fine);
        j=j+1;
    }
    fclose(fp);
    gotoxy(70,j+4);
}

void helpline()
{
    fp=fopen("helplines.txt","r");
    if(fp==NULL)
    {
        printf("****** ERROR SHOWING HELPLINE NUMBERS *******");
        return;
    }
    char mystring[200];
    while(fgets(mystring,200,fp))
    {
        printf("%s",mystring);
    }
    fclose(fp);
    printf("\n\n\n\t\t\t\t\t");
}

void trafficRules()
{
fp=fopen("control.txt","r");
    if(fp==NULL)
    {
        printf("****** ERROR SHOWING TRAFFIC RULES *******");
        return;
    }
    char mystring[200];
    while(fgets(mystring,200,fp))
    {
        printf("%s",mystring);
    }
    fclose(fp);
    printf("\n\n\n\t\t\t\t\t");
}

void trafficControlBooth()
{
    fp=fopen("control_booth.txt","r");
    if(fp==NULL)
    {
        printf("****** ERROR SHOWING CONTROL BOOTH DETAILS *******");
        return;
    }
    char mystring[200];
    while(fgets(mystring,200,fp))
    {
        printf("%s",mystring);
    }
    fclose(fp);
    printf("\n\n\n\t\t\t\t\t");
}

void challanDetails()
{
    fp=fopen("challan_Details","r");
    if(fp==NULL)
    {
        printf("****** ERROR SHOWING HELPLINE NUMBERS *******");
        return;
    }
    char mystring[200];
    while(fgets(mystring,200,fp))
    {
        printf("%s",mystring);
    }
    fclose(fp);
    printf("\n\n\n\t\t\t\t\t");
}

void speedLimitDetails()
{
    fp=fopen("speed_details.txt","r");
    if(fp==NULL)
    {
        printf("****** ERROR SHOWING SPEED LIMIT DETAILS *******");
        return;
    }
    char mystring[200];
    while(fgets(mystring,200,fp))
    {
        printf("%s",mystring);
    }
    fclose(fp);
    printf("\n\n\n\t\t\t\t\t");
}

void main()
{
    int choice;
    clrscr();
    do
    {
        gotoxy(70,12);
        printf("=============================================");
        gotoxy(76,13);
        printf("Traffic control Management System");
        gotoxy(70,14);
        printf("=============================================");
        gotoxy(70,17);
        printf("1. Add Vehicle Record\n");
        gotoxy(70,18);
        printf("2. Delete Vehicle Record\n");
        gotoxy(70,19);
        printf("3. Search Vehicle Record\n");
        gotoxy(70,20);
        printf("4. Update Vehicle Record\n");
        gotoxy(70,21);
        printf("5. Display Vehicle Records\n");
        gotoxy(70,22);
        printf("6. Helpline Information\n");
        gotoxy(70,23);
        printf("7. Traffic Rules\n");
        gotoxy(70,24);
        printf("8. Traffic Scheduling and Management\n");
        gotoxy(70,25);
        printf("9. Traffic Challan Details\n");
        gotoxy(70,26);
        printf("10. Speed Limit Details\n");
        gotoxy(70,27);
        printf("11. Exit\n");
        gotoxy(70,29);
        printf("Enter your choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: clrscr();
                    insertRecord();
                    printf("Enter any key to return to main menu : ");
                    getch();
                    clrscr();
                    break;
            case 2: clrscr();
                    deleteRecord();
                    gotoxy(80,24);
                    printf("Enter any key to return to main menu : ");
                    getch();
                    clrscr();
                    break;
            case 3: clrscr();
                    searchRecord();
                    printf("Enter any key to return to main menu : ");
                    getch();
                    clrscr();
                    break;
            case 4: clrscr();
                    updateRecord();
                    printf("Enter any key to return to main menu : ");
                    getch();
                    clrscr();
                    break;
            case 5: clrscr();
                    displayRecord();
                    printf("Enter any key to return to main menu : ");
                    getch();
                    clrscr();
                    break;
            case 6: clrscr();
                    helpline();
                    printf("Enter any key to return to main menu : ");
                    getch();
                    clrscr();
                    break;
            case 7: clrscr();
                    trafficRules();
                    printf("Enter any key to return to main menu : ");
                    getch();
                    clrscr();
                    break;
            case 8: clrscr();
                    trafficControlBooth();
                    printf("Enter any key to return to main menu : ");
                    getch();
                    clrscr();
                    break;
            case 9: clrscr();
                    challanDetails();
                    printf("Enter any key to return to main menu : ");
                    getch();
                    clrscr();
                    break;
            case 10: clrscr();
                     speedLimitDetails();
                     printf("Enter any key to return to main menu : ");
                     getch();
                     clrscr();
                     break;
            case 11: clrscr();
                     gotoxy(90,15);
                     printf("***************");
                     gotoxy(90,16);
                     printf("*             *");
                     gotoxy(90,17);
                     printf("*  THANK YOU  *");
                     gotoxy(90,18);
                     printf("*             *");
                     gotoxy(90,19);
                     printf("***************");
                    printf("\n\n\n\n");
                     exit(0);
        }
    }while(1);
}
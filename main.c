#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include<Windows.h>
//global variables
FILE*f1;
FILE*f2;
char acc_no[11];
char username[100];
char name[100];
char check_name[100];
char check_pass[100];
char pass[100];


typedef struct
{
    int mounth;
    int year;
} date;
typedef struct
{
    char number[11];  //number means account number
    char name[40];
    char add[40]; //add means address
    double balance;
    char mobile[15];
    date doo; //doo means date of opening new account
} acc; //acc means account
acc accounts[100];
void MENU1();
void MENU2();

void LOGIN()
{
    int i;
    f1=fopen("c:\\Project\\users.txt","r");
    if(f1!=NULL)
    {
        printf("Enter user name:");
        gets(username);
        while(!feof(f1))
        {
            fscanf(f1,"%s",check_name);
            if(strcmp(check_name,username)==0)
            {
                printf("Enter your password:");
                fscanf(f1,"%s",pass);
                scanf("%s",check_pass);
                for(i=0; i<2; i++)
                {
                    if(strcmp(check_pass,pass)==0)
                    {
                        printf("Successful login.\n\n");
                        return;

                    }
                    else
                    {
                        printf("Wrong Password.\nEnter correct password:");
                        scanf("%s",check_pass);
                    }
                }
                if(i==0||i==1)
                    return;

                if(strcmp(check_pass,pass)==0 && i==2)
                {
                    printf("Successful login.\n\n");
                    return;

                }
                else
                {
                    printf("Wrong Password.Login again\n\n");
                    MENU1();
                }

            }
        }
        if(strcmp(check_name,username)!=0&&feof(f1))
        {
            printf("User not found.\n");
            MENU1();
        }
    }
    else
        printf("File not opened\n");
    fclose(f1);
}

int countLines()
{
    f1 = fopen("c://project//accounts.txt", "r");
    if (f1 == NULL)
    {
        printf("Error opening file");
        return;
    }

    int count = 0;
    char ch;

    while ((ch = fgetc(f1)) != EOF)
    {
        if (ch == '\n')
        {
            count++;
        }
    }

    fclose(f1);
    return count;
}

void LOAD()
{
    f2 = fopen("c:\\Project\\accounts.txt", "r");
    if (f2 == NULL)
    {
        printf("Cannot open file.\n");
        return;
    }
    char line[256];  // Assuming a line won't exceed 255 characters
    char *token;

    int i = 0;
    while (fgets(line, sizeof(line), f2) != NULL)
    {
        if (line[0] == '\n')
            continue;  // Skip empty lines

        token = strtok(line, ",");
        strcpy(accounts[i].number, token);
        token = strtok(NULL, ",");
        strcpy(accounts[i].name, token);

        token = strtok(NULL, ",");
        strcpy(accounts[i].add, token);

        token = strtok(NULL, ",");
        accounts[i].balance = atof(token); // atof Convert to float

        token = strtok(NULL, ",");
        strcpy(accounts[i].mobile, token);

        token = strtok(NULL, "-");
        accounts[i].doo.mounth = atoi(token);  // atoi Convert to integer
        token = strtok(NULL, "\n");
        accounts[i].doo.year=atoi(token);

        i++;
    }

    fclose(f2);
    return;
}

char* Print_Mounth(int moun)
{
    switch(moun)
    {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    }
}

void SAVE()
{

    int i,x=countLines();

    f1 = fopen("c:\\project\\accounts.txt", "w");
    if (f1 == NULL)
    {
        printf("Error: Unable to access the account file.\n");
        return;
    }

    for (i = 0; i < x; i++)
    {
        fprintf(f1, "%s,%s,%s,%.2lf,%s,%d-%d\n", accounts[i].number, accounts[i].name,accounts[i].add, accounts[i].balance, accounts[i].mobile,accounts[i].doo.mounth,accounts[i].doo.year);
    }

    fclose(f1);
    return;


}

void swapAccounts(acc *a, acc *b)
{
    acc temp = *a;
    *a = *b;
    *b = temp;
}

void sortByDate()
{
    int i, j, numlines = countLines();
    for (i = 0; i < numlines - 1; i++)
    {
        for (j = 0; j < numlines - i - 1; j++)
        {
            char dateStrA[10], dateStrB[10]; // Adjust array size as needed

            // Use sprintf to format strings
            sprintf(dateStrA, "%d%d", accounts[j].doo.year, accounts[j].doo.mounth);
            sprintf(dateStrB, "%d%d", accounts[j + 1].doo.year, accounts[j + 1].doo.mounth);

            // Use strcmp to compare strings
            if (strcmp(dateStrA, dateStrB) > 0)
            {
                swapAccounts(&accounts[j], &accounts[j + 1]);
            }
        }
    }
}

void sortByName()
{
    int i, j,numlines=countLines();
    for (i = 0; i < numlines - 1; ++i)
    {
        for (j = 0; j < numlines - i - 1; ++j)
        {
            if (strcmp(accounts[j].name, accounts[j + 1].name) > 0)
            {
                // Swap accounts if they are in the wrong order
                swapAccounts(&accounts[j], &accounts[j + 1]);
            }
        }
    }
}

void sortByBalance()
{
    int i,j,numlines=countLines();
    for (int i = 0; i < numlines - 1; ++i)
    {
        for (int j = 0; j < numlines - i - 1; ++j)
        {
            if (accounts[j].balance > accounts[j + 1].balance)
            {
                swapAccounts(&accounts[j], &accounts[j + 1]);
            }
        }
    }
}
void printSort()
{
    int sort_option,i,numlines=countLines();
    printf("Please choose from the following list:\n");
    printf("1-Sort by name\n2-Sort by balance\n3-Sort by date\n");
    scanf("%d",&sort_option);
    while(getchar()!='\n');
    switch (sort_option)
    {
    case 1:
        sortByName(); // Sort by name
        break;
    case 2:
        sortByBalance(); // Sort by balance
        break;
    case 3:
        sortByDate(); // Sort by date
        break;
    default:
    {
        printf("Invalid option.Try again.\n");
        return;
    }


    }
    for(i=0; i<numlines; i++)
    {
        printf("Account number: %s\nName: %s\nE-mail: %s\nBalance: %.2lf $\nMobile: %s\n",accounts[i].number,accounts[i].name,accounts[i].add,accounts[i].balance,accounts[i].mobile);
        printf("Date Opened: %s %d\n\n",Print_Mounth(accounts[i].doo.mounth),accounts[i].doo.year);
    }
}

void SEARCH()
{
    int y=countLines();
    char num[11];
    int i;
    printf("Enter account number:");
    scanf("%s",num);
    for(i=0; i<y; i++)
    {
        if(strcmp(num,accounts[i].number)==0)
        {
            printf("Account number: %s\nName: %s\nE-mail: %s\nBalance: %.2lf $\nMobile: %s\n",accounts[i].number,accounts[i].name,accounts[i].add,accounts[i].balance,accounts[i].mobile);
            printf("Date Opened: %s %d\n\n",Print_Mounth(accounts[i].doo.mounth),accounts[i].doo.year);
            return;


        }
    }
    if(i==y)
    {
        printf("This account does not exist.\n\n");
        return;
    }

}

void ADD()
{
    int i,flag=0;
    int y=countLines();
    double balance=0;
    FILE *Ft;
    char *token,acc_no[20],addr[40],mobile[13],name[40],addrcpy[40],addrcpy1[40],fileaccount[40];
    SYSTEMTIME time;//a built-in structure in windows library
    GetSystemTime(&time);//a buit-in function in windows library
    LOAD(); //delete when code is added
    f2=fopen("c:\\Project\\accounts.txt","a+");
    if(f2==NULL)
        printf("file cannot be opened");
    else
    {
        printf("Enter name:");
        gets(name);
        while(1)
        {
            for(i=0; name[i]!='\0'; i++) //makes sure that the name is only alphabets
            {
                if(isalpha(name[i])==0&&name[i]!=' '&&name[0]==' ')
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
                printf("Invalid name\nEnter a valid name: ");
                gets(name);
            }
            else
                break;  // Exit the loop if the name is valid

            flag=0;
        }
        flag=0;
        printf("Enter Account Number that must be 10 digits only and unique:");
        gets(acc_no);
        while(1)
        {
            for (int i = 0; i < 10; i++) // Check if the account number is all digits
            {
                if (!isdigit(acc_no[i]))
                {
                    flag = 1;
                    break;
                }
            }


            if (strlen(acc_no) != 10) // Check if the account number is 10 digits long
                flag = 1;




            for (int i = 0; i< y; i++) // Check if the account number is unique
            {
                if (strcmp(acc_no, accounts[i].number) == 0)
                {
                    flag = 1;
                    break;
                }
            }


            if (flag)  // If any flag is set, ask the user to enter a valid account number
            {
                printf("Invalid account number.\nEnter a valid account number: ");
                gets(acc_no);
            }
            else
                break;  // Exit the loop if the account number is valid

            flag=0;
        }


        flag=0;
        printf("Enter your mobile number:");
        gets(mobile);
        while(1)
        {
            for (int i = 0; i < 11; i++) // Check if the mobile number is all digits
            {
                if (!isdigit(mobile[i]))
                {
                    flag = 1;
                    break;
                }
            }


            if (strlen(mobile) != 11)  // Check if the mobile number is 11 digits long
                flag = 1;



            for (int i = 0; i< y; i++)  // Check if the mobile number is unique
            {
                if (strcmp(mobile, accounts[i].mobile) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if(mobile[0]!='0'||mobile[1]!='1')
                flag=1;
            if(mobile[2]!='0'&&mobile[2]!='1'&&mobile[2]!='2'&&mobile[2]!='5')
                flag=1;


            if (flag)  // If any flag is set, ask the user to enter a valid mobile number
            {
                printf("Invalid mobile\nEnter a valid mobile number: ");
                gets(mobile);
            }
            else
            {
                break;  // Exit the loop if the mobile number is valid
            }
            flag=0;
        }
        printf("Enter your email address(yahoo,gmail or outlook domains):");
        gets(addr);

        while(1)
        {

            strcpy(addrcpy,addr);
            token=strtok(addrcpy,"@");
            strcpy(addrcpy1,token);
            token=strtok(NULL,"\n");
            while(1)
            {
                if(token==NULL)
                {
                    flag=1;

                }
                if(flag)
                {
                    printf("Invalid email address.\nEnter a valid email address: ");
                    gets(addr);
                    strcpy(addrcpy,addr);
                    token=strtok(addrcpy,"@");
                    strcpy(addrcpy1,token);
                    token=strtok(NULL,"\n");
                    flag=0;
                }
                else
                    break;
            }
            flag=0;
            i=0;
            while(isspace(addrcpy1[i])!=0) //check there is no space in email address
            {
                flag=1;
                i++;
            }

            for (int i = 0; i< y; i++) // Check if the address is unique
            {
                if (strcmp(addr, accounts[i].add) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            if(strcmp(token,"yahoo.com")!=0&&strcmp(token,"gmail.com")!=0&&strcmp(token,"outlook.com")!=0) //Check email domain is correct
                flag=1;


            if (flag)  // If any flag is set, ask the user to enter a valid email address
            {
                printf("Invalid email address.\nEnter a valid email address: ");
                gets(addr);
            }
            else
                break;  // Exit the loop if the email address is valid

            flag=0;
        }


        int year=time.wYear;
        int month=time.wMonth;
        fprintf(f2,"%s,%s,%s,%.2lf,%s,%d-%d\n",acc_no,name,addr,balance,mobile,month,year);
        fclose(f2);
        strcpy(fileaccount,"c:\\project\\");
        strcat(fileaccount,acc_no);
        strcat(fileaccount,".txt");
        Ft=fopen(fileaccount,"w");
        fclose(fileaccount);
        printf("Account added successfully.\n\n");
        LOAD();
        return;
    }
}

void ADVANCED_SEARCH()
{
    char keyword[40];
    int y=countLines();
    int i,flag=0 ;
    printf("Enter keyword(You can search by name,mobile,date,address or account number):");
    gets(keyword);
    for(i=0; i<y; i++)
    {
        if(strcmp(keyword,accounts[i].number)==0||strcmp(keyword,accounts[i].mobile)==0||strcmp(keyword,accounts[i].add)==0||strstr(accounts[i].name,keyword)!=NULL) //strstr returns a non null character if keyword substring of the name
        {
            printf("Account number: %s\nName: %s\nE-mail: %s\nBalance: %.2lf $\nMobile: %s\n",accounts[i].number,accounts[i].name,accounts[i].add,accounts[i].balance,accounts[i].mobile);
            printf("Date Opened: %s %d\n\n",Print_Mounth(accounts[i].doo.mounth),accounts[i].doo.year);
            flag=1;

        }
    }
    if(flag==0)
    {
        int key=atoi(keyword);//convert keyword to integer to search for month and year
        for(i=0; i<y; i++)
        {
            if(key==accounts[i].doo.mounth||key==accounts[i].doo.year)
            {
                printf("Account number: %s\nName: %s\nE-mail: %s\nBalance: %.2lf $\nMobile: %s\n",accounts[i].number,accounts[i].name,accounts[i].add,accounts[i].balance,accounts[i].mobile);
                printf("Date Opened: %s %d\n\n",Print_Mounth(accounts[i].doo.mounth),accounts[i].doo.year);
                flag=1;
            }


        }
    }
    if(flag==0)
    {
        printf("No matches found.\n\n");
    }

    return;

}

void WITHDRAW()
{
    int flag=0,y=countLines(),test;
    f2=fopen("c:\\project\\accounts.txt","a+");
    int i;
    double withdraw,amount;
    printf("Enter Account Number(must be 10 digits long):");
    gets(acc_no);
    while(1)
    {
        for(i=0; i<y; i++)
        {
            if(strcmp(acc_no,accounts[i].number)==0)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            printf("Enter amount you want to withdraw it:");
            scanf("%lf",&withdraw);
            amount=withdraw;
            if(withdraw>=10000||withdraw<0)
            {
                printf("Error.\n");
                return;

            }
            else
            {
                accounts[i].balance-=withdraw;
                printf("the new balance is %.2lf\n",accounts[i].balance);
                break;
            }
        }
        else
        {
            printf("Enter valid account number :");
            gets(acc_no);
        }
    }
    if (flag==1)
    {
        printf("Press 1 to save or press 0 to undo: ");
        scanf("%d",&test);
        if(test==1)
        {
            FILE*Ft;// for putting the money into the file that named bank_acc.txt
            char fileaccount[40];
            strcpy(fileaccount,"c:\\project\\");
            strcat(fileaccount,acc_no);
            strcat(fileaccount,".txt");
            Ft=fopen(fileaccount,"a+");
            if (Ft == NULL)
            {
                printf("Error: Unable to access the account file.\n");
                return;
            }
            else
            {
                fprintf(Ft,"The money withdrawed from ur account is %.2lf\n",amount);
                printf("Saved successfully\n\n");
                fclose(Ft);
            }
        }
        else if(test==0)
        {
            return;
        }

    }



    SAVE();
    fclose(f2);


}

void MODIFY()
{
    int test=0,choice,i,j,flag=0,x;
    int y=countLines();
    char*token;
    char addr[40];
    char addrcpy[40];
    char addrcpy1[40];
    char name[40];
    char mobile[11];
    printf("Enter Account Number(must be 10 digits long):");
    gets(acc_no);
    while(1)
    {
        for (i = 0; i < y; i++)
        {
            if (strcmp(acc_no, accounts[i].number) == 0)
            {
                test=1;
                x=i;
                break;
            }
        }
        if(test==1)

            break;

        else
        {
            printf("Invalid account number.\nEnter a valid account number: ");
            gets(acc_no);
        }

    }
    if(test==1)
    {
        printf("Do you want to modify the name.\n1-Yes\n2-No\n");
        scanf("%d",&choice);
        getchar();
        if(choice==1)
        {
            printf("enter the new name:");
            gets(name);
            while(1)
            {
                for(j=0; name[j]!='\0'; j++) //makes sure that the name is only alphabets
                {
                    if(isalpha(name[j])==0&&name[j]!=' ')
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag)
                {
                    printf("Invalid name\nEnter a valid name: ");
                    gets(name);
                }
                else
                    break;  // Exit the loop if the name is valid

                flag=0;
            }
            printf("Are you sure you want to save changes:\n1-Yes\n2-No\n");
            scanf("%d",&choice);
            if (choice==1)
            {
                strcpy(accounts[x].name,name);
                SAVE();
                printf("DONE.\n");
            }
            else
                printf("No changes saved.\n");
        }

        printf("Do you want to modify the mobile number.\n1-Yes\n2-No\n");
        scanf("%d",&choice);
        getchar();
        if(choice==1)
        {
            printf("enter the new mobile number:");
            gets(mobile);
            while(1)
            {
                for (int j = 0; j < 11; j++) // Check if the mobile number is all digits
                {
                    if (!isdigit(mobile[j]))
                    {
                        flag = 1;
                        break;
                    }
                }


                if (strlen(mobile) != 11)  // Check if the mobile number is 11 digits long
                    flag = 1;



                for (int j = 0; j< y; j++)  // Check if the mobile number is unique
                {
                    if (strcmp(mobile, accounts[j].mobile) == 0)
                    {
                        flag = 1;
                        break;
                    }
                }
                if(mobile[0]!='0'||mobile[1]!='1')
                    flag=1;
                if(mobile[2]!='0'&&mobile[2]!='1'&&mobile[2]!='2'&&mobile[2]!='5')
                    flag=1;


                if (flag)  // If any flag is set, ask the user to enter a valid mobile number
                {
                    printf("Invalid mobile\nEnter a valid mobile number: ");
                    gets(mobile);
                }
                else
                {
                    break;  // Exit the loop if the mobile number is valid
                }
                flag=0;
            }
            printf("Are you sure you want to save changes:\n1-Yes\n2-No\n");
            scanf("%d",&choice);
            if (choice==1)
            {
                strcpy(accounts[x].mobile,mobile);
                SAVE();
                printf("DONE.\n");
            }
            else
                printf("No changes saved.\n");
        }


        printf("Do you want to modify the email address.\n1-Yes\n2-No\n");
        scanf("%d",&choice);
        getchar();
        if(choice==1)
        {
            printf("Enter the new email address:");
            gets(addr);

            while(1)
            {
                strcpy(addrcpy,addr);
                token=strtok(addrcpy,"@");
                strcpy(addrcpy1,token);
                token=strtok(NULL,"\n");
                while(1)
                {
                    if(token==NULL)
                    {
                        flag=1;

                    }
                    if(flag)
                    {
                        printf("Invalid email address.\nEnter a valid email address: ");
                        gets(addr);
                        strcpy(addrcpy,addr);
                        token=strtok(addrcpy,"@");
                        strcpy(addrcpy1,token);
                        token=strtok(NULL,"\n");
                        flag=0;
                    }
                    else
                        break;
                }
                flag=0;
                j=0;
                while(isspace(addrcpy1[j])!=0) //check there is no space in email address
                {
                    flag=1;
                    j++;
                }

                for (int j = 0; j< y; j++) // Check if the address is unique
                {
                    if (strcmp(addr, accounts[j].add) == 0)
                    {
                        flag = 1;
                        break;
                    }
                }
                if(strcmp(token,"yahoo.com")!=0&&strcmp(token,"gmail.com")!=0&&strcmp(token,"outlook.com")!=0) //Check email domain is correct
                    flag=1;


                if (flag)  // If any flag is set, ask the user to enter a valid email address
                {
                    printf("Invalid email address.\nEnter a valid email address: ");
                    gets(addr);
                }
                else
                    break;  // Exit the loop if the email address is valid

                flag=0;
            }
            printf("Are you sure you want to save changes:\n1-Yes\n2-No\n");
            scanf("%d",&choice);
            if (choice==1)
            {
                strcpy(accounts[x].add,addr);
                SAVE();
                printf("DONE.\n");
            }
            else
                printf("No changes saved.\n");

        }
    }
    LOAD();
    return;
}

void Quit()
{
    exit(0);
}
void TRANSFER()
{
    int y=countLines();
    printf("Enter the bank account:");
    gets(acc_no);
    int i,j,flag=0,flag2=0;
    char tr_acc[15];
    double tr_money;
    int sure;
    for(i=0; i<y; i++)
    {
        if(strcmp(accounts[i].number,acc_no)==0)
        {
            flag=1;
            printf("\nThe current balance of the bank account (%s) is %.2lf \n",accounts[i].number,accounts[i].balance);
            printf("Enter the number of the bank account that you would like to transfer money into:");
            gets(tr_acc);
            for(int j=0; j<y; j++)
            {
                if(strcmp(tr_acc,acc_no)==0)
                {
                    printf("Sorry you cant transfer money into your own account.\n");
                    return;
                }
                else if(strcmp(accounts[j].number,tr_acc)==0)
                {
                    flag2=1;
                    printf("Enter the amount to be transferred: ");
                    scanf("%lf",&tr_money);
                    if(tr_money<0)
                    {
                        printf("Error.\n");
                        return;
                    }
                    printf("Are you sure about transferring %.2lf from the bank account(%s) \nThe balance will be %.2lf \n",tr_money,accounts[i].number,accounts[i].balance-tr_money);
                    printf("Press 1 to continue,otherwise press any number:");
                    scanf("%d",&sure);
                    if(sure==1)
                    {
                        accounts[i].balance-=tr_money;
                        accounts[j].balance+=tr_money;
                        printf("Your new balance of bank account %s after money been transfered is %.2lf\n\n",accounts[i].number,accounts[i].balance);
                        FILE*Ft;// for putting the money into the file that named bank_acc.txt
                        FILE*Fr;
                        char fileaccount[40],filerecieve[40];
                        strcpy(fileaccount,"c:\\project\\");
                        strcpy(filerecieve,"c:\\project\\");
                        strcat(fileaccount,acc_no);
                        strcat(filerecieve,tr_acc);
                        strcat(fileaccount,".txt");
                        strcat(filerecieve,".txt");
                        Ft=fopen(fileaccount,"a+");
                        if (Ft == NULL)
                        {
                            printf("Error: Unable to access the account file.\n");
                            return;
                        }
                        fprintf(Ft,"The money transferred from ur account is %.2lf.\n",tr_money);
                        fclose(Ft);
                        Fr=fopen(filerecieve,"a+");
                        if (Fr == NULL)
                        {
                            printf("Error: Unable to access the account file.\n");
                            return;
                        }
                        fprintf(Fr,"The money transferred to ur account is %.2lf.\n",tr_money);
                        fclose(Fr);
                        SAVE();
                    }
                    else printf("No operations have been operated.\n");

                }
            }
            if (flag2==0)
            {
                printf("Couldn't find the account.\n");
                return;
            }
        }

    }
    if (flag==0)
    {
        printf("Couldn't find the account\n");
        return;
    }
}

void DEPOSITE()
{
    int y=countLines();
    printf("Enter the bank account:");
    gets(acc_no);
    int i,flag=0,sure;
    char fileaccount[40];
    double deposit;
    for (i = 0; i < y; i++)  // search for the number
    {
        if (strcmp(accounts[i].number, acc_no) == 0)
        {
            flag=1;
            printf("The current balance of the bank account (%s) is %.2lf\n",acc_no, accounts[i].balance);


            printf("Enter the amount to be deposited: ");
            scanf("%lf", &deposit);
            if (deposit >= 10000||deposit<0)
            {
                printf("Error.\n");
                return;
            }
            printf("Are you sure about depositing %.2lf\nThe account balance will be %.2lf\n",deposit,accounts[i].balance+deposit);
            printf("Press 1 to continue, otherwise press any number:");

            scanf("%d",&sure);
            if(sure==1)
            {
                accounts[i].balance += deposit;
                printf("The new balance of bank account %s after money been deposited is %.2lf\n\n",accounts[i].number,accounts[i].balance);
                FILE*FD;// for putting the money into the file that named bank_acc.txt to use for the report

                strcpy(fileaccount,"c:\\Project\\");
                strcat(fileaccount,acc_no);
                strcat(fileaccount,".txt");
                FD=fopen(fileaccount,"a+");
                if (FD == NULL)
                {
                    printf("Error: Unable to access the account file.\n");
                    return;
                }
                fprintf(FD,"The money deposited to your account is %.2lf\n",deposit);
                fclose(FD);
                SAVE();
            }
            else
            {
                printf("No operations have been operated\n");
                return;
            }

        }
    }
    if (flag==0)
    {
        printf("coudnt find the account\n");
        return;
    }
}

int reportcountLines(char*fileaccount)
{

    f1 = fopen(fileaccount, "r");
    if (f1 == NULL)
    {
        printf("Error opening file");
        return;
    }

    int count = 0;
    char ch;

    while ((ch = fgetc(f1)) != EOF)
    {
        if (ch == '\n')
        {
            count++;
        }
    }

    fclose(f1);
    return (count);
}

void REPORT()
{

    printf("Enter your bank account:");
    gets(acc_no);
    char fileaccount[40];
    strcpy(fileaccount,"c:\\project\\");
    strcat(fileaccount,acc_no);
    strcat(fileaccount,".txt");
    FILE* freport = fopen(fileaccount, "r");
    int y=  reportcountLines(fileaccount);
    if (freport == NULL)
    {
        printf("Error: Unable to open your account '%s'.\n", acc_no);//check for the file
        return;
    }

    char lines[5][200];
    int count = 0;

    if(y>=5)
    {
        // Read the last five lines
        while (fgets(lines[count % 5], sizeof(lines[0]), freport) != NULL)
        {
            count++;
        }

        printf("Last five transactions from '%s':\n",acc_no);
        for (int i = 0; i < 5; i++)
        {
            printf("%s", lines[(count + i) % 5]);
        }
    }
    else

    {
        printf("Last transactions from '%s':\n",acc_no);//read any lines for new accounts
        char line[256];
        while (fgets(line, sizeof(lines[0]),freport)!=NULL)
        {
            printf("%s", line);
        }
    }
    fclose(freport);
}

void Delete()
{
    int test=0,i,j,d;
    int y=countLines();
    char acc_no[20];
    char filename[40];

    printf("Enter Account Number(must be 10 digits long):");
    gets(acc_no);

    while(1)
    {
        for (i = 0; i < y; i++)
        {
            if (strcmp(acc_no, accounts[i].number) == 0)
            {
                if(accounts[i].balance==0.00)
                {
                    test =1;
                    d=i;
                    break;
                }
            }
        }
        if (test == 1)
        {

            strcpy(filename,"c://project//");
            strcat(filename,acc_no);
            strcat(filename,".txt");
            if (remove(filename)==0)
            {

                printf("Account deleted successfully.\n");
            }
            else
            {
                printf("Couldn't delete the file.\n");
            }
            break;
        }
        else
        {
            printf("Enter a valid account number:");
            gets(acc_no);
        }
    }
    f1=fopen("c:\\project\\accounts.txt","w");
    if (f1 == NULL)
    {
        printf("Cannot open file.\n");
    }
    else
    {
        for(i=0; i<y; i++)
        {
            if(i!=d)
                fprintf(f1, "%s,%s,%s,%.2lf,%s,%d-%d\n", accounts[i].number, accounts[i].name,accounts[i].add, accounts[i].balance, accounts[i].mobile,accounts[i].doo.mounth,accounts[i].doo.year);
        }
        fclose(f1);
    }
    return;
}



void MENU1()
{
    int x;
    printf("Please choose from the following menu:\n");
    printf("1-Login\n2-Quit\n");
    scanf("%d",&x);
    while(x!=1&&x!=2)
    {
        while(getchar()!='\n');
        printf("Error.\nChoose a valid number from menu:");
        scanf("%d",&x);
    }
    if(x==1)
    {
        getchar();
        LOGIN();
        MENU2();
    }
    else
        Quit();

}
void MENU2()
{
    int menuchoose;
    LOAD();
    printf("Please choose from the following menu:\n");
    printf("1-Add\n2-Delete\n3-Modify\n4-Search\n5-Advanced search\n6-Withdraw\n");
    printf("7-Deposit\n8-Transfer\n9-Report\n10-Print\n11-Quit\n");
    scanf("%d",&menuchoose);
    while(getchar()!='\n');

    switch (menuchoose)
    {
    case 1:
        ADD();
        break;
    case 2:
        Delete();
        break;
    case 3:
        MODIFY();
        break;
    case 4:
        SEARCH();
        break;
    case 5:
        ADVANCED_SEARCH();
        break;
    case 6:
        WITHDRAW();
        break;
    case 7:
        DEPOSITE();
        break;
    case 8:
        TRANSFER();
        break;
    case 9:
        REPORT();
        break;
    case 10:
        printSort();
        break;
    case 11:
        Quit();
    default:
        printf("Error choose a valid number from menu\n");
        MENU2();
    }
    MENU2();
}



int main()
{
    MENU1();
    return 0;
}

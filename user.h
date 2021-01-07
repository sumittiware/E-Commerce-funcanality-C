//STRUCTURE DECLARATION
struct User
{
    int ID;
    char name[100];
    char email[100];
    char password[100];
    struct User*next;
}*user_head=NULL;


//DECLARATION OF FUNCTION
struct User*find_user_by_email(char[100]);
void extract_users_from_file();
void add_user(struct User*);
void sign_up();
struct User*login();
int email_verify(char[100]);
int password_verify(char[100]);
void update_user_file();


//DEFINITION OF FUNCTION
void sign_up()
{
    FILE *user_ptr;
    struct User*u;
    char user_name[100];
    char user_email[100];
    char user_password[100];
    char confirm_password[100];
    int user_ID,i;

    printf("Enter your Details->\n");
    printf("Enter the name:");
    scanf(" %[^\n]",user_name);
    do
    {
        printf("\t\t\tEnter the email: ");
        scanf(" %[^\n]",user_email);
    }
    while(!email_verify(user_email));
    do
    {
        do
        {
            i=0;
            printf("\t\t\tEnter the password: ");
            do
            {
                user_password[i]=getch();
                if(user_password[i]==13)
                {
                    break;
                }
                printf("*");
                i++;
            }
            while(1);
            printf("\n");
            user_password[i]='\0';
        }
        while(!password_verify(user_password));
        i=0;
        printf("\t\t\tEnter password again to confirm: ");
        do
        {
            confirm_password[i]=getch();
            if(confirm_password[i]==13)
            {
                break;
            }
            printf("*");
            i++;
        }
        while(1);
        printf("\n");
        confirm_password[i]='\0';
        if(strcmp(user_password,confirm_password)!=0)
        {
            printf("\t\t\tPassword is not matched, Try again!\n\n");
        }
    }
    while(strcmp(user_password,confirm_password)!=0);
    user_ID=generate_uuid();
    if(find_user_by_email(user_email)==NULL)
    {
        user_ptr=fopen("users.txt","a");
        if(user_ptr==NULL)
        {
            printf("\t\t\tERROR! File opening\n");
            exit(1);
        }
        fprintf(user_ptr,"%d=%s=%s=%s\n",user_ID,user_name,user_email,encrypt(user_password));
        fclose(user_ptr);

        u=(struct User*)malloc(sizeof(struct User));
        if(u==NULL)
        {
            printf("\t\t\tHeap overflow!\n\n");
            exit(1);
        }
        u->ID=user_ID;
        copy_item(u->name,user_name);
        copy_item(u->email,user_email);
        copy_item(u->password,encrypt(user_password));
        u->next=NULL;
        add_user(u);

        printf("\t\t\tUser created successfully, Now you can login\n\n");
    }
    else
    {
        printf("\t\t\tUser with email %s is already sign up, you can login\n\n",user_email);
    }
}


struct User*login()
{
    struct User*u=NULL;
    char user_email[100];
    char user_password[100];
    char confirm_password[100];
    int reset,i;
    printf("\t\t\tEnter the login details->\n\n");
    do
    {
        printf("\t\t\tEnter the email:");
        scanf(" %[^\n]",user_email);
    }
    while(!email_verify(user_email));
    printf("\t\t\tEnter the password:");
    i=0;
    do
    {
        user_password[i]=getch();
        if(user_password[i]==13)
        {
            break;
        }
        printf("*");
        i++;
    }
    while(1);
    printf("\n");
    user_password[i]='\0';
    u=find_user_by_email(user_email);
    if(u!=NULL)
    {
        if(strcmp(decrypt(u->password),user_password)==0)
        {
            return u;
        }
        else
        {
            printf("\t\t\tPassword is wrong\n");
            printf("\t\t\tWant to reset password YES[1]/NO[0]: ");
            scanf("%d",&reset);
            if(reset==1)
            {
                do
                {
                    do
                    {
                        printf("\t\t\tEnter the password: ");
                        i=0;
                        do
                        {
                            user_password[i]=getch();
                            if(user_password[i]==13)
                            {
                                break;
                            }
                            printf("*");
                            i++;
                        }
                        while(1);
                        printf("\n");
                        user_password[i]='\0';
                    }
                    while(!password_verify(user_password));
                    printf("\t\t\tEnter password again to confirm: ");
                    i=0;
                    do
                    {
                        confirm_password[i]=getch();
                        if(confirm_password[i]==13)
                        {
                            break;
                        }
                        printf("*");
                        i++;
                    }
                    while(1);
                    printf("\n");
                    confirm_password[i]='\0';
                    if(strcmp(user_password,confirm_password)!=0)
                    {
                        printf("\t\t\tPassword is not matched, Try again!\n");
                    }
                }
                while(strcmp(user_password,confirm_password)!=0);
                copy_item(u->password,encrypt(user_password));
                update_user_file();
                printf("\t\t\tPassword reset successfully, Now you can login\n");
            }
            return NULL;
        }
    }
    else
    {
        printf("\t\t\temail not registered, first you have to sign up\n");
        return NULL;
    }
}


void extract_users_from_file()
{
    FILE *user_ptr;
    struct User *u=NULL;
    char user_name[100];
    char user_email[100];
    char user_password[100];
    char user_ID[100];
    char read;
    int temp=0;
    user_ptr=fopen("users.txt","r");
    if(user_ptr==NULL)
    {
        printf("\t\t\tERROR! File opening\n");
        exit(1);
    }
    user_ID[0]='\0';
    user_name[0]='\0';
    user_email[0]='\0';
    user_password[0]='\0';
    do
    {
        read=fgetc(user_ptr);
        if(read=='=')
        {
            temp++;
        }
        else
        {
            if(read!='\n')
            {

                if(temp==0)
                {
                    user_ID[strlen(user_ID)+1]='\0';
                    user_ID[strlen(user_ID)]=read;
                }
                else if(temp==1)
                {
                    user_name[strlen(user_name)+1]='\0';
                    user_name[strlen(user_name)]=read;
                }
                else if(temp==2)
                {
                    user_email[strlen(user_email)+1]='\0';
                    user_email[strlen(user_email)]=read;
                }
                else
                {
                    user_password[strlen(user_password)+1]='\0';
                    user_password[strlen(user_password)]=read;
                }
            }
            else
            {
                u=(struct User*)malloc(sizeof(struct User));
                if(u==NULL)
                {
                    printf("\t\t\tHeap overflow!\n\n");
                    exit(1);
                }
                u->ID=atoi(user_ID);
                copy_item(u->name,user_name);
                copy_item(u->email,user_email);
                copy_item(u->password,user_password);
                u->next=NULL;
                add_user(u);
                user_ID[0]='\0';
                user_name[0]='\0';
                user_email[0]='\0';
                user_password[0]='\0';
                temp=0;
            }
        }
    }
    while(!feof(user_ptr));
    fclose(user_ptr);
}


void add_user(struct User *u)
{
    struct User*q=user_head;
    if(user_head==NULL)
    {
        user_head=u;
    }
    else
    {
        while(q->next!=NULL)
        {
            q=q->next;
        }
        q->next=u;
    }
}


struct User*find_user_by_email(char email[100])
{
    struct User*u=user_head;
    if(user_head==NULL)
    {
        return NULL;
    }
    else
    {
        while(u!=NULL)
        {
            if(strcmp(u->email,email)==0)
            {
                return u;
            }
            u=u->next;
        }
        return NULL;
    }
}


int email_verify(char email[100])
{
    int count1=0;
    int count2=0;
    for(int i=0; i<strlen(email); i++)
    {
        if(email[i]=='@')
        {
            count1++;
        }
        else if(email[i]=='.')
        {
            count2++;
        }
    }

    if(count1==1 && count2==1)
    {
        return 1;
    }
    else
    {
        printf("Email is invalid!\n");
        return 0;
    }
}


int password_verify(char password[100])
{
    if(strlen(password)>=6)
    {
        return 1;
    }
    else
    {
        printf("\t\t\tPassword should contain atleast 6 character\n\n");
        return 0;
    }
}


void update_user_file()
{
    FILE *user_ptr;
    struct User*u=user_head;
    user_ptr=fopen("users.txt","w");
    if(user_ptr==NULL)
    {
        printf("ERROR! File opening\n");
        exit(1);
    }
    while(u!=NULL)
    {
        fprintf(user_ptr,"%d=%s=%s=%s\n",u->ID,u->name,u->email,u->password);
        u=u->next;
    }
    fclose(user_ptr);
}



//GLOBALS
char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789@$&";
char* key =      "mnbvcxzas$dfghj@&klpoiuytrewqQW7896541230ERTYUIOPLKJHGFDSAZXCVBNM";


//DECLARATION OF FUNCTION
void copy_item(char[100],char[100]);
int generate_uuid();
int find(char);
int findinKey(char);
char*encrypt(char[100]);
char*decrypt(char[100]);


//DEFINITION OF FUNCTION
void copy_item(char to[100],char from[100])
{
    int i;
    for(i=0; i<strlen(from); i++)
    {
        *(to+i)=from[i];
    }
    *(to+i)='\0';
}


int generate_uuid()
{
    FILE *id_ptr;
    char uuid[100];
    int uuid_int;
    char read;
    id_ptr=fopen("uuid.txt","r");
    if(id_ptr==NULL)
    {
        printf("\t\t\tERROR! File opening\n");
        exit(1);
    }
    uuid[0]='\0';
    do
    {
        read=fgetc(id_ptr);
        uuid[strlen(uuid)+1]='\0';
        uuid[strlen(uuid)]=read;

    }
    while(!feof(id_ptr));
    fclose(id_ptr);

    uuid_int=atoi(uuid);
    uuid_int+=1;

    id_ptr=fopen("uuid.txt","w");
    if(id_ptr==NULL)
    {
        printf("\t\t\tERROR! File opening\n");
        exit(1);
    }

    fprintf(id_ptr,"%d",uuid_int);
    fclose(id_ptr);
    return uuid_int;
}


int find(char character)
{
    for(int i=0; alphabet[i] != '\0'; i++)
    {
        if(character == alphabet[i])
        {
            return i;
        }
    }
    return -1;
}


int findinKey(char character)
{
    for(int i=0; key[i] != '\0'; i++)
    {
        if(character == key[i])
        {
            return i;
        }
    }
    return -1;
}


char*encrypt(char string[100])
{
    char* result = (char*)malloc(strlen(string)*sizeof(char));
    int i;
    for(i=0; i<strlen(string); i++)
    {
        int index = find(string[i]);
        result[i] = key[index];
    }
    result[i]='\0';
    return result;
}


char*decrypt(char string[100])
{
    char* result = (char*)malloc(strlen(string)*sizeof(char));
    int i;
    for(i=0; i<strlen(string); i++)
    {
        int index = findinKey(string[i]);
        result[i] = alphabet[index];
    }
    result[i]='\0';
    return result;
}



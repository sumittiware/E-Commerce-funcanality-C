//DECLARATION OF FUNCTION
int search_category(char[100][100],int,char[100]);
void extract_category_name_from_file(char[100][100],int*);
void add_category(char[100][100],char[100],int*);
void print_categories(char[100][100],int);


//DEFINITION OF FUNCTION
int search_category(char categories_name[100][100],int total_category,char category_name[100])
{
    for(int i=0; i<total_category; i++)
    {
        if(strcmp(categories_name[i],category_name)==0)
        {
            return 1;
        }
    }
    return 0;
}


void print_categories(char categories_name[100][100],int total_category)
{
    for(int i=0; i<total_category; i++)
    {
        printf("\t\t\t-> %s\n",categories_name[i]);
    }
}


void extract_category_name_from_file(char categories_name[100][100],int *total_category)
{
    FILE *category_ptr=fopen("categories.txt","r");
    if(category_ptr==NULL)
    {
        printf("\t\t\tERROR! File opening\n");
        exit(1);
    }
    *total_category=0;
    char name[100];
    char read;
    name[0]='\0';
    do
    {
        read=fgetc(category_ptr);
        if(read!='\n')
        {
            name[strlen(name)+1]='\0';
            name[strlen(name)]=read;
        }
        else
        {
            add_category(categories_name,name,total_category);
            name[0]='\0';
        }
    }
    while(!feof(category_ptr));
    fclose(category_ptr);
}


void add_category(char categories_name[100][100],char name[100],int *total_category)
{
    copy_item(categories_name[*total_category],name);
    *total_category+=1;
}



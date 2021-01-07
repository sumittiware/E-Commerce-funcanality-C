//STRUCTURE DECLARATION
struct Wishlist
{
    int userId;
    int productId;
    struct Wishlist*next;
}*wishlist_head=NULL;



//DECLARATION OF FUNCTION
void wishlist(int,struct Product*,struct User*);
void extract_wishlist_from_file_by_userId(struct User*);
void add_wishlist(struct Wishlist*);
int remove_product_wishlist_by_id(int,struct User*);
void remove_wishlist_all(struct User*);
void update_wishlist_file(char[100],struct Wishlist*);
void create_wishlist(int,struct User*);
char*create_wishlist_file_name(struct User*);
struct Wishlist*wishlist_product_id(int);
void print_wishlist();
int wishlist_count();
void free_wishlist();


//DEFINITION OF FUNCTION
void wishlist(int id,struct Product*p,struct User*customer)
{
    struct Wishlist*wishlist_product=NULL;
    wishlist_product=wishlist_product_id(id);
    if(wishlist_product==NULL)
    {
        create_wishlist(p->ID,customer);
    }
    else
    {
        printf("'\t\t%s' product is already present in the wishlist\n",p->name);
    }
}


void free_wishlist()
{
    struct Wishlist*w=wishlist_head,*prev_w=NULL;
    while(w!=NULL)
    {
        prev_w=w;
        w=w->next;
        free(prev_w);
    }
    wishlist_head=NULL;
}


int wishlist_count()
{
    struct Wishlist*w=wishlist_head;
    int total=0;
    while(w!=NULL)
    {
        total+=1;
        w=w->next;
    }
    return total;
}


void print_wishlist()
{
    struct Wishlist*w=wishlist_head;
    struct Product*p=NULL;
    printf("\t\tWislist is display as [product id=product name=product description=product price]\n\n");
    while(w!=NULL)
    {
        p=find_product_by_id(w->productId);
        printf("\t\t-> %d=%s=%s=%d\n",p->ID,p->name,p->description,p->price);
        w=w->next;
    }
}


struct Wishlist*wishlist_product_id(int product_id)
{
    struct Wishlist*w=wishlist_head;
    while(w!=NULL)
    {
        if(w->productId==product_id)
        {
            return w;
        }
        w=w->next;
    }
    return NULL;
}


char*create_wishlist_file_name(struct User*u)
{
    char *file_name=(char*)malloc(100*sizeof(char));
    char user_id[100];
    sprintf(user_id, "%d", u->ID);
    copy_item(file_name,u->name);
    strcat(file_name,"-");
    strcat(file_name,user_id);
    strcat(file_name,"-wishlist.txt");
    return file_name;
}


void create_wishlist(int product_id,struct User*u)
{
    struct Wishlist*w=NULL;
    FILE *wishlist_ptr;

    wishlist_ptr=fopen(create_wishlist_file_name(u),"a");
    if(wishlist_ptr==NULL)
    {
        printf("\t\t\tERROR! File opening\n");
        exit(1);
    }
    fprintf(wishlist_ptr,"%d=%d\n",u->ID,product_id);
    fclose(wishlist_ptr);

    w=(struct Wishlist*)malloc(sizeof(struct Wishlist));
    if(w==NULL)
    {
        printf("\t\t\tHeap overflow!\n\n");
        exit(1);
    }

    w->productId=product_id;
    w->userId=u->ID;
    w->next=NULL;
    add_wishlist(w);
    printf("\t\t\tProduct added to wishlist successfully\n");
}


void extract_wishlist_from_file_by_userId(struct User*u)
{
    FILE *wishlist_ptr_read,*wishlist_ptr_write;
    struct Wishlist *w=NULL;
    char file_userid[100];
    char file_productid[100];
    char read;
    int temp=0;
    wishlist_ptr_read=fopen(create_wishlist_file_name(u),"r");
    if(wishlist_ptr_read==NULL)
    {
        wishlist_ptr_write=fopen(create_wishlist_file_name(u),"w");
        if(wishlist_ptr_write==NULL)
        {
            printf("\t\t\tFile not created\n");
            exit(1);
        }
        fclose(wishlist_ptr_write);
        wishlist_ptr_read=fopen(create_wishlist_file_name(u),"r");
    }
    file_productid[0]='\0';
    file_userid[0]='\0';
    do
    {
        read=fgetc(wishlist_ptr_read);
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
                    file_userid[strlen(file_userid)+1]='\0';
                    file_userid[strlen(file_userid)]=read;
                }
                else
                {
                    file_productid[strlen(file_productid)+1]='\0';
                    file_productid[strlen(file_productid)]=read;
                }
            }
            else
            {
                w=(struct Wishlist*)malloc(sizeof(struct Wishlist));
                if(w==NULL)
                {
                    printf("\t\t\tHeap overflow!\n");
                    exit(1);
                }
                w->userId=atoi(file_userid);
                w->productId=atoi(file_productid);
                w->next=NULL;
                add_wishlist(w);
                file_userid[0]='\0';
                file_productid[0]='\0';
                temp=0;
            }
        }
    }
    while(!feof(wishlist_ptr_read));
    fclose(wishlist_ptr_read);
}


void add_wishlist(struct Wishlist*w)
{
    w->next=wishlist_head;
    wishlist_head=w;
}


int remove_product_wishlist_by_id(int product_id,struct User*u)
{
    struct Wishlist*w=wishlist_head,*prev_w=NULL;
    int before_count,after_count;
    if(wishlist_head->productId==product_id)
    {
        wishlist_head=wishlist_head->next;
        free(w);
    }
    else
    {
        before_count=wishlist_count();
        prev_w=w;
        w=w->next;
        while(w!=NULL)
        {
            if(w->productId==product_id)
            {
                prev_w->next=w->next;
                free(w);
                break;
            }
            prev_w=w;
            w=w->next;
        }

        after_count=wishlist_count();

        if(before_count==after_count)
        {
            return 0;
        }
    }
    update_wishlist_file(create_wishlist_file_name(u),wishlist_head);
    return 1;
}


void remove_wishlist_all(struct User*u)
{
    struct Wishlist*w=wishlist_head,*prev_w=NULL;
    while(w!=NULL)
    {
        prev_w=w;
        w=w->next;
        free(prev_w);
    }
    wishlist_head=NULL;

    remove(create_wishlist_file_name(u));


}


void update_wishlist_file(char wishlist_file_name[100],struct Wishlist*w)
{
    static FILE *wishlist_ptr;
    if(wishlist_head==NULL)
    {
        wishlist_ptr=fopen(wishlist_file_name,"w");
        if(wishlist_ptr==NULL)
        {
            printf("\t\t\tERROR! File opening\n\n");
        }
        return;
    }
    else
    {

        if(w==NULL)
        {
            return;
        }

        if(w==wishlist_head)
        {
            wishlist_ptr=fopen(wishlist_file_name,"w");
            if(wishlist_ptr==NULL)
            {
                printf("\t\t\tERROR! File opening\n\n");
            }
        }
        update_wishlist_file(wishlist_file_name,w->next);
        fprintf(wishlist_ptr,"%d=%d\n",w->userId,w->productId);
        if(w==wishlist_head)
        {
            fclose(wishlist_ptr);
        }
    }
}

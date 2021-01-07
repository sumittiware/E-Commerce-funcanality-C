//STRUCTURE DECLARATION
struct Cart
{
    int userId;
    int productId;
    int product_quantity;
    struct Cart*next;
}*cart_head=NULL;


//DECLARATION OF FUNCTION
void cart(int,struct Product*,struct User*);
void extract_cart_from_file_by_userId(struct User*);
void add_cart(struct Cart*);
int remove_product_cart_by_id(int,struct User*);
void remove_cart_all(struct User*);
void update_cart_file(char[100],struct Cart*);
void create_cart(int,struct User*);
char*create_cart_file_name(struct User*);
struct Cart*cart_product_id(int);
void print_cart();
int cart_total();
void free_cart();


//DEFINITION OF FUNCTION
void cart(int id,struct Product*p,struct User*customer)
{
    struct Cart*cart_product=NULL;
    int quantity_choice;
    cart_product=cart_product_id(id);
    if(cart_product==NULL)
    {
        create_cart(p->ID,customer);
    }
    else
    {
        printf("'\t\t\t%s' product is already present in the cart\n",p->name);
        printf("\t\t\tThe quantity of the product = %d\n",cart_product->product_quantity);
        printf("\t\t\tyou want to change the quantity of the product YES[1]/NO[0]:");
        scanf("%d",&quantity_choice);
        if(quantity_choice==1)
        {
            printf("\t\t\tEnter the quantity:");
            scanf("%d",&cart_product->product_quantity);
            update_cart_file(create_cart_file_name(customer),cart_head);
            printf("\t\t\tQuantity changes successfully\n");
        }
    }
}


void free_cart()
{
    struct Cart*c=cart_head,*prev_c=NULL;
    while(c!=NULL)
    {
        prev_c=c;
        c=c->next;
        free(prev_c);
    }
    cart_head=NULL;
}

int cart_total()
{
    struct Cart*c=cart_head;
    struct Product*p=NULL;
    int total=0;
    while(c!=NULL)
    {
        p=find_product_by_id(c->productId);
        total+=((p->price)*(c->product_quantity));
        c=c->next;
    }
    return total;
}

void print_cart()
{
    struct Cart*c=cart_head;
    struct Product*p=NULL;
    printf("\t\t\tCart is display as [product id=product name=product description=product price=product quantity]\n");
    while(c!=NULL)
    {
        p=find_product_by_id(c->productId);
        printf("\t\t-> %d=%s=%s=%d=%d\n",p->ID,p->name,p->description,p->price,c->product_quantity);
        c=c->next;
    }
}


struct Cart*cart_product_id(int product_id)
{
    struct Cart*c=cart_head;
    while(c!=NULL)
    {
        if(c->productId==product_id)
        {
            return c;
        }
        c=c->next;
    }
    return NULL;
}


char*create_cart_file_name(struct User*u)
{
    char *file_name=(char*)malloc(100*sizeof(char));
    char user_id[100];
    sprintf(user_id, "%d", u->ID);
    copy_item(file_name,u->name);
    strcat(file_name,"-");
    strcat(file_name,user_id);
    strcat(file_name,"-cart.txt");
    return file_name;
}


void create_cart(int product_id,struct User*u)
{
    struct Cart*c=NULL;
    FILE *cart_ptr;
    int product_quantity;
    printf("\t\t\tEnter the quantity of the product:");
    scanf("%d",&product_quantity);
    cart_ptr=fopen(create_cart_file_name(u),"a");
    if(cart_ptr==NULL)
    {
        printf("\t\t\tERROR! File opening\n");
        exit(1);
    }
    fprintf(cart_ptr,"%d=%d=%d\n",u->ID,product_id,product_quantity);
    fclose(cart_ptr);

    c=(struct Cart*)malloc(sizeof(struct Cart));
    if(c==NULL)
    {
        printf("\t\t\tHeap overflow!\n\n");
        exit(1);
    }

    c->productId=product_id;
    c->userId=u->ID;
    c->product_quantity=product_quantity;
    c->next=NULL;
    add_cart(c);
    printf("\t\t\tProduct added to cart successfully\n\n");
}


void extract_cart_from_file_by_userId(struct User*u)
{
    FILE *cart_ptr_read,*cart_ptr_write;
    struct Cart *c=NULL;
    char file_userid[100];
    char file_productid[100];
    char file_product_quantity[100];
    char read;
    int temp=0;
    cart_ptr_read=fopen(create_cart_file_name(u),"r");
    if(cart_ptr_read==NULL)
    {
        cart_ptr_write=fopen(create_cart_file_name(u),"w");
        if(cart_ptr_write==NULL)
        {
            printf("\t\t\tFile not created\n\n");
            exit(1);
        }
        fclose(cart_ptr_write);
        cart_ptr_read=fopen(create_cart_file_name(u),"r");
    }
    file_productid[0]='\0';
    file_userid[0]='\0';
    file_product_quantity[0]='\0';
    do
    {
        read=fgetc(cart_ptr_read);
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
                else if(temp==1)
                {
                    file_productid[strlen(file_productid)+1]='\0';
                    file_productid[strlen(file_productid)]=read;
                }
                else
                {
                    file_product_quantity[strlen(file_product_quantity)+1]='\0';
                    file_product_quantity[strlen(file_product_quantity)]=read;
                }
            }
            else
            {
                c=(struct Cart*)malloc(sizeof(struct Cart));
                if(c==NULL)
                {
                    printf("\t\t\tHeap overflow!\n");
                    exit(1);
                }
                c->userId=atoi(file_userid);
                c->productId=atoi(file_productid);
                c->product_quantity=atoi(file_product_quantity);
                c->next=NULL;
                add_cart(c);
                file_userid[0]='\0';
                file_productid[0]='\0';
                file_product_quantity[0]='\0';
                temp=0;
            }
        }
    }
    while(!feof(cart_ptr_read));
    fclose(cart_ptr_read);
}


void add_cart(struct Cart*c)
{
    c->next=cart_head;
    cart_head=c;
}


int remove_product_cart_by_id(int product_id,struct User*u)
{
    struct Cart*c=cart_head,*prev_c=NULL;
    if(cart_head->productId==product_id)
    {
        cart_head=cart_head->next;
        free(c);
    }
    else
    {
        prev_c=c;
        c=c->next;
        while(c!=NULL)
        {
            if(c->productId==product_id)
            {
                prev_c->next=c->next;
                free(c);
                break;
            }
            prev_c=c;
            c=c->next;
        }

        if(c==NULL)
        {
            return 0;
        }
    }
    update_cart_file(create_cart_file_name(u),cart_head);
    return 1;
}


void remove_cart_all(struct User*u)
{
    struct Cart*c=cart_head,*prev_c=NULL;
    while(c!=NULL)
    {
        prev_c=c;
        c=c->next;
        free(prev_c);
    }
    cart_head=NULL;

    remove(create_cart_file_name(u));


}


void update_cart_file(char cart_file_name[100],struct Cart*c)
{
    static FILE *cart_ptr;
    if(cart_head==NULL)
    {
        cart_ptr=fopen(cart_file_name,"w");
        if(cart_ptr==NULL)
        {
            printf("\t\t\tERROR! File opening\n\n");
        }
        return;
    }
    else
    {
        if(c==NULL)
        {
            return;
        }
        if(c==cart_head)
        {
            cart_ptr=fopen(cart_file_name,"w");
            if(cart_ptr==NULL)
            {
                printf("\t\t\tERROR! File opening\n\n");
            }
        }
        update_cart_file(cart_file_name,c->next);
        fprintf(cart_ptr,"%d=%d=%d\n",c->userId,c->productId,c->product_quantity);
        if(c==cart_head)
        {
            fclose(cart_ptr);
        }
    }
}

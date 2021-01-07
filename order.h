//STRUCTURE DECLARATION
struct Order
{
    int ID;
    int userId;
    char address[100];
    int total;
    struct Product*order_product;
    struct Order *next;
}*order_head=NULL;


//DECLARATION OF FUNCTION
char*create_order_file_name(struct User*);
void extract_order_from_file(struct User*);
char*create_order_product_file_name(int);
void extract_order_product_from_file(struct Order*);
void add_order_product(struct Order*,struct Product*);
void add_order(struct Order*);
void create_order(struct User*);
void print_order();
struct Order*find_order_by_id(int);
void print_order_product(struct Product*);
void remove_order(int,struct User*);
void update_order_file(int,struct User*);
void free_order();


//DEFINITION OF FUNCTION
void free_order()
{
    struct Order*o=order_head,*prev_o=NULL;
    while(o!=NULL)
    {
        prev_o=o;
        o=o->next;
        free(prev_o);
    }
    order_head=NULL;
}


void remove_order(int id,struct User*u)
{
    struct Order*o=order_head,*q=NULL;
    if(order_head->ID==id)
    {
        order_head=o->next;
        free(o);
    }
    else
    {
        while(o!=NULL)
        {
            if(o->ID==id)
            {
                q->next=o->next;
                free(o);
                break;
            }
            q=o;
            o=o->next;
        }
    }

    update_order_file(id,u);
    printf("\t\t\tOrder remove successfully\n");
}


void update_order_file(int order_id,struct User*u)
{
    FILE *order_ptr;
    struct Order*o=NULL;
    order_ptr=fopen(create_order_file_name(u),"w");
    if(order_ptr==NULL)
    {
        printf("\t\t\tERROR! File opening\n\n");
        exit(1);
    }
    o=order_head;
    while(o!=NULL)
    {
        fprintf(order_ptr,"%d=%d=%s=%d\n",u->ID,o->ID,o->address,o->total);
        o=o->next;
    }
    fclose(order_ptr);

    remove(create_order_product_file_name(order_id));
}


void print_order_product(struct Product*p)
{
    struct Product*q=p;
    while(q!=NULL)
    {
        printf("\t\t-> %s=%s=%d\n",q->name,q->description,q->price);
        q=q->next;
    }
}


struct Order*find_order_by_id(int id)
{
    struct Order*o=order_head;
    while(o!=NULL)
    {
        if(o->ID==id)
        {
            return o;
        }
        o=o->next;
    }
    return NULL;
}


void print_order()
{
    struct Order*o=order_head;
    while(o!=NULL)
    {
        printf("\t\t-> %d=%s=%d\n",o->ID,o->address,o->total);
        o=o->next;
    }
}
void create_order(struct User*u)
{
    struct Order*o=NULL;
    struct Cart*c=cart_head;
    struct Product*p=NULL;
    FILE *order_ptr,*order_product_ptr;
    char address[100];
    int order_id;
    int order_total;
    printf("\t\t\tEnter the address where you want delivery of your order:");
    scanf(" %[^\n]",address);
    order_id=generate_uuid();
    order_total=cart_total();
    order_ptr=fopen(create_order_file_name(u),"a");
    if(order_ptr==NULL)
    {
        printf("\t\t\tERROR! File opening\n\n");
        exit(1);
    }
    fprintf(order_ptr,"%d=%d=%s=%d\n",u->ID,order_id,address,order_total);
    fclose(order_ptr);

    o=(struct Order*)malloc(sizeof(struct Order));
    if(o==NULL)
    {
        printf("\t\t\tHeap overflow!\n\n");
        exit(1);
    }

    o->userId=u->ID;
    o->ID=order_id;
    copy_item(o->address,address);
    o->total=order_total;
    o->order_product=NULL;
    o->next=NULL;

    order_product_ptr=fopen(create_order_product_file_name(order_id),"a");
    if(order_product_ptr==NULL)
    {
        printf("\t\t\tERROR! File opening\n\n");
        exit(1);
    }
    while(c!=NULL)
    {
        p=find_product_by_id(c->productId);
        if(p!=NULL)
        {
            add_order_product(o,p);
            fprintf(order_product_ptr,"%d=%s=%s=%d=%s\n",p->ID,p->name,p->description,p->price,p->category);
        }
        c=c->next;
    }
    fclose(order_product_ptr);

    add_order(o);
    printf("\t\t\tOrder placed successfully\n\n");
}


void add_order(struct Order*o)
{
    struct Order*q=order_head;
    if(order_head==NULL)
    {
        order_head=o;
    }
    else
    {
        while(q->next!=NULL)
        {
            q=q->next;
        }
        q->next=o;
    }
}


void add_order_product(struct Order*o,struct Product*p)
{
    struct Product*q=o->order_product;
    struct Product *temp=(struct Product*)malloc(sizeof(struct Product));
    if(temp==NULL)
    {
        printf("\t\t\tHeap Overflow!\n\n");
        exit(1);
    }
    copy_item(temp->category,p->category);
    copy_item(temp->description,p->description);
    temp->ID=p->ID;
    copy_item(temp->name,p->name);
    temp->price=p->price;
    temp->next=NULL;
    if(o->order_product==NULL)
    {
        o->order_product=temp;
    }
    else
    {
        while(q->next!=NULL)
        {
            q=q->next;
        }
        q->next=temp;
    }
}


void extract_order_product_from_file(struct Order*o)
{
    FILE *order_product_ptr_read,*order_product_ptr_write;
    struct Product *p=NULL;
    char product_name[100];
    char product_description[100];
    char product_category[100];
    char product_price[100];
    char product_ID[100];
    char read;
    int temp=0;
    order_product_ptr_read=fopen(create_order_product_file_name(o->ID),"r");
    if(order_product_ptr_read==NULL)
    {
        order_product_ptr_write=fopen(create_order_product_file_name(o->ID),"w");
        if(order_product_ptr_write==NULL)
        {
            printf("\t\t\tFile not created\n\n");
            exit(1);
        }
        fclose(order_product_ptr_write);
        order_product_ptr_read=fopen(create_order_product_file_name(o->ID),"r");
    }
    product_ID[0]='\0';
    product_name[0]='\0';
    product_description[0]='\0';
    product_price[0]='\0';
    product_category[0]='\0';
    do
    {
        read=fgetc(order_product_ptr_read);
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
                    product_ID[strlen(product_ID)+1]='\0';
                    product_ID[strlen(product_ID)]=read;
                }
                else if(temp==1)
                {
                    product_name[strlen(product_name)+1]='\0';
                    product_name[strlen(product_name)]=read;
                }
                else if(temp==2)
                {
                    product_description[strlen(product_description)+1]='\0';
                    product_description[strlen(product_description)]=read;
                }
                else if(temp==3)
                {
                    product_price[strlen(product_price)+1]='\0';
                    product_price[strlen(product_price)]=read;
                }
                else
                {
                    product_category[strlen(product_category)+1]='\0';
                    product_category[strlen(product_category)]=read;
                }
            }
            else
            {
                p=(struct Product*)malloc(sizeof(struct Product));
                if(p==NULL)
                {
                    printf("\t\t\tHeap overflow!\n\n");
                    exit(1);
                }
                p->ID=atoi(product_ID);
                copy_item(p->name,product_name);
                copy_item(p->description,product_description);
                p->price=atoi(product_price);
                copy_item(p->category,product_category);
                p->next=NULL;

                add_order_product(o,p);

                product_ID[0]='\0';
                product_name[0]='\0';
                product_description[0]='\0';
                product_price[0]='\0';
                product_category[0]='\0';
                temp=0;
            }
        }
    }
    while(!feof(order_product_ptr_read));
    fclose(order_product_ptr_read);
}


char*create_order_file_name(struct User*u)
{
    char *file_name=(char*)malloc(100*sizeof(char));
    char user_id[100];
    sprintf(user_id, "%d", u->ID);
    copy_item(file_name,u->name);
    strcat(file_name,"-");
    strcat(file_name,user_id);
    strcat(file_name,"-order.txt");
    return file_name;
}


char*create_order_product_file_name(int order_id)
{
    char *file_name=(char*)malloc(100*sizeof(char));
    char orderid[100];
    sprintf(orderid, "%d", order_id);
    copy_item(file_name,"order-products-");
    strcat(file_name,orderid);
    strcat(file_name,".txt");
    return file_name;
}


void extract_order_from_file(struct User*u)
{
    FILE *order_ptr_read,*order_ptr_write;
    struct Order *o=NULL;
    char file_user_id[100];
    char file_order_id[100];
    char file_order_address[100];
    char file_order_total[100];
    char read;
    int temp=0;
    order_ptr_read=fopen(create_order_file_name(u),"r");
    if(order_ptr_read==NULL)
    {
        order_ptr_write=fopen(create_order_file_name(u),"w");
        if(order_ptr_write==NULL)
        {
            printf("\t\t\tFile not created\n\n");
            exit(1);
        }
        fclose(order_ptr_write);
        order_ptr_read=fopen(create_order_file_name(u),"r");
    }
    file_user_id[0]='\0';
    file_order_id[0]='\0';
    file_order_address[0]='\0';
    file_order_total[0]='\0';
    do
    {
        read=fgetc(order_ptr_read);
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
                    file_user_id[strlen(file_user_id)+1]='\0';
                    file_user_id[strlen(file_user_id)]=read;
                }
                else if(temp==1)
                {
                    file_order_id[strlen(file_order_id)+1]='\0';
                    file_order_id[strlen(file_order_id)]=read;
                }
                else if(temp==2)
                {
                    file_order_address[strlen(file_order_address)+1]='\0';
                    file_order_address[strlen(file_order_address)]=read;
                }
                else
                {
                    file_order_total[strlen(file_order_total)+1]='\0';
                    file_order_total[strlen(file_order_total)]=read;
                }
            }
            else
            {
                o=(struct Order*)malloc(sizeof(struct Order));
                if(o==NULL)
                {
                    printf("\t\t\tHeap overflow!\n\n");
                    exit(1);
                }
                o->userId=atoi(file_user_id);
                o->ID=atoi(file_order_id);
                copy_item(o->address,file_order_address);
                o->total=atoi(file_order_total);
                o->order_product=NULL;
                o->next=NULL;

                extract_order_product_from_file(o);

                add_order(o);

                file_user_id[0]='\0';
                file_order_id[0]='\0';
                file_order_address[0]='\0';
                file_order_total[0]='\0';
                temp=0;
            }
        }
    }
    while(!feof(order_ptr_read));
    fclose(order_ptr_read);
}

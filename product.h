//STRUCTURE DECLARATION
struct Product
{
    int ID;
    char name[100];
    char description[100];
    int price;
    char category[100];
    struct Product *next;
}*product_head=NULL;


//DECLARATION OF FUNCTION
void extract_product_name_from_file();
void add_product(struct Product*);
void create_product(char[100]);
void print_product_according_category(char[100]);
void remove_product(int);
void update_product(int);
int product_available(char[100]);
struct Product* find_product_by_id(int);
struct Product*find_product_by_id_category(int,char[100]);
void update_product_file();
void remove_product_from_all_cart(int);
void maximum__price_product(char[100],struct User*);
void minimum__price_product(char[100],struct User*);
int total_products();
void product_price_lowest_highest(char[100]);
void product_price_highest_lowest(char[100]);
void insert_max_heap(struct Product*,char[100]);
void insert_min_heap(struct Product*,char[100]);
struct Product*delete_max_heap(struct Product*,char[100]);
struct Product*delete_min_heap(struct Product*,char[100]);
int count_category_products(char[100]);
void print_all_product();
//DEFINITION OF FUNCTION
void print_all_product()
{
    struct Product*p=product_head;
    while(p!=NULL)
    {
        printf("\t\t-> %s=%s=%d\n",p->name,p->description,p->price);
        p=p->next;
    }
}
int count_category_products(char category_name[100])
{
    int total=0;
    struct Product*p=product_head;
    while(p!=NULL)
    {
        if(strcmp(p->category,category_name)==0)
        {
            total+=1;
        }
        p=p->next;
    }
    return total;
}


void insert_max_heap(struct Product*category_products,char category_name[100])
{
    int i,j;
    struct Product temp;
    for(i=2; i<=count_category_products(category_name); i++)
    {
        j=i;
        temp=category_products[i];
        while(j>1 && category_products[j/2].price<temp.price)
        {
            *(category_products+j)=category_products[j/2];
            j=j/2;
        }
        *(category_products+j)=temp;
    }
}

void insert_min_heap(struct Product*category_products,char category_name[100])
{
    int i,j;
    struct Product temp;
    for(i=2; i<=count_category_products(category_name); i++)
    {
        j=i;
        temp=category_products[i];
        while(j>1 && category_products[j/2].price>temp.price)
        {
            *(category_products+j)=category_products[j/2];
            j=j/2;
        }
        *(category_products+j)=temp;
    }
}

struct Product*delete_max_heap(struct Product*category_products,char category_name[100])
{
    struct Product *sort_products=(struct Product*)malloc(count_category_products(category_name)*sizeof(struct Product));
    struct Product temp;
    int i=0,j,k,total;
    total=count_category_products(category_name);
    while(total!=0)
    {
        sort_products[i]=category_products[1];
        i++;
        category_products[1]=category_products[total];
        total--;
        j=1;
        while((2*j)<=total)
        {
            k=j;
            j=2*j;
            if((j+1) <=total)
            {
                if(category_products[j].price>=category_products[j+1].price && category_products[j].price>category_products[k].price)
                {
                    temp=category_products[j];
                    category_products[j]=category_products[k];
                    category_products[k]=temp;
                    j=j;
                }
                else if(category_products[j].price<category_products[j+1].price && category_products[j+1].price>category_products[k].price)
                {
                    temp=category_products[j+1];
                    category_products[j+1]=category_products[k];
                    category_products[k]=temp;
                    j=j+1;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if(category_products[j].price>category_products[k].price)
                {
                    temp=category_products[j];
                    category_products[j]=category_products[k];
                    category_products[k]=temp;
                    j=j;
                }
                else
                {
                    break;
                }
            }

        }

    }

    return sort_products;
}


struct Product*delete_min_heap(struct Product*category_products,char category_name[100])
{
    struct Product *sort_products=(struct Product*)malloc(count_category_products(category_name)*sizeof(struct Product));
    struct Product temp;
    int i=0,j,k,total;
    total=count_category_products(category_name);
    while(total!=0)
    {
        sort_products[i]=category_products[1];
        i++;
        category_products[1]=category_products[total];
        total--;
        j=1;
        while(2*j<=total)
        {
            k=j;
            j=2*j;
            if((j+1) <=total)
            {
                if(category_products[j].price<=category_products[j+1].price && category_products[j].price<category_products[k].price)
                {
                    temp=category_products[j];
                    category_products[j]=category_products[k];
                    category_products[k]=temp;
                    j=j;
                }
                else if(category_products[j].price>category_products[j+1].price && category_products[j+1].price<category_products[k].price)
                {
                    temp=category_products[j+1];
                    category_products[j+1]=category_products[k];
                    category_products[k]=temp;
                    j=j+1;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if(category_products[j].price<category_products[k].price)
                {
                    temp=category_products[j];
                    category_products[j]=category_products[k];
                    category_products[k]=temp;
                    j=j;
                }
                else
                {
                    break;
                }
            }

        }

    }

    return sort_products;
}


void create_product(char category_name[100])
{
    FILE *product_ptr;
    struct Product*p;
    char product_name[100];
    char product_description[100];
    int product_price;
    int product_ID;

    product_ptr=fopen("products.txt","a");
    if(product_ptr==NULL)
    {
        printf("ERROR! File opening\n");
        exit(1);
    }
    printf("\t\t\tEnter the product Detail->\n\n");
    printf("\t\t\tEnter the product name:");
    scanf(" %[^\n]",product_name);
    printf("\t\t\tEnter the product description:");
    scanf(" %[^\n]",product_description);
    printf("\t\t\tEnter the product price:");
    scanf("%d",&product_price);
    product_ID=generate_uuid();
    fprintf(product_ptr,"%d=%s=%s=%d=%s\n",product_ID,product_name,product_description,product_price,category_name);
    fclose(product_ptr);

    p=(struct Product*)malloc(sizeof(struct Product));
    if(p==NULL)
    {
        printf("\t\t\tHeap overflow!\n\n");
        exit(1);
    }
    p->ID=product_ID;
    copy_item(p->name,product_name);
    copy_item(p->description,product_description);
    p->price=product_price;
    copy_item(p->category,category_name);
    p->next=NULL;
    add_product(p);

    printf("\t\t\tProduct created successfully\n\n");


}


void extract_product_name_from_file()
{
    FILE *product_ptr;
    struct Product *p=NULL;
    char product_name[100];
    char product_description[100];
    char product_category[100];
    char product_price[100];
    char product_ID[100];
    char read;
    int temp=0;
    product_ptr=fopen("products.txt","r");
    if(product_ptr==NULL)
    {
        printf("\t\t\tERROR! File opening\n");
        exit(1);
    }
    product_ID[0]='\0';
    product_name[0]='\0';
    product_description[0]='\0';
    product_price[0]='\0';
    product_category[0]='\0';
    do
    {
        read=fgetc(product_ptr);
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
                add_product(p);
                product_ID[0]='\0';
                product_name[0]='\0';
                product_description[0]='\0';
                product_price[0]='\0';
                product_category[0]='\0';
                temp=0;
            }
        }
    }
    while(!feof(product_ptr));
    fclose(product_ptr);
}



void add_product(struct Product *p)
{
    struct Product*q=product_head;
    if(product_head==NULL)
    {
        product_head=p;
    }
    else
    {
        while(q->next!=NULL)
        {
            q=q->next;
        }
        q->next=p;
    }
}


void remove_product(int id)
{
    struct Product*p=product_head,*q=NULL;
    if(product_head==NULL)
    {
        printf("\t\t\tNo product found with that ID\n\n");
        return;
    }
    else if(product_head->ID==id)
    {
        product_head=p->next;
        free(p);
    }
    else
    {
        while(p!=NULL)
        {
            if(p->ID==id)
            {
                q->next=p->next;
                free(p);
                break;
            }
            q=p;
            p=p->next;
        }
        if(p==NULL)
        {
            printf("\t\t\tNo product found with that ID\n\n");
            return;
        }
    }

    update_product_file();
    remove_product_from_all_cart(id);
    printf("\t\t\tProduct remove successfully\n\n");

}

void update_product(int id)
{
    struct Product*p=product_head;
    char product_name[100];
    char product_description[100];
    int product_price;

    while(p!=NULL)
    {
        if(p->ID==id)
        {
            break;
        }
        p=p->next;
    }
    if(p==NULL)
    {
        printf("\t\t\tNo product found with that id\n\n");
        return;
    }

    printf("\t\t\tDetail of the product [Product name=Product description=Product Price]\n");
    printf("\t\t\t-> %s=%s=%d\n\n",p->name,p->description,p->price);
    printf("\t\t\tEnter the update product Detail->\n");
    printf("\t\t\tEnter the product name:");
    scanf(" %[^\n]",product_name);
    printf("\t\t\tEnter the product description:");
    scanf(" %[^\n]",product_description);
    printf("\t\t\tEnter the product price:");
    scanf("%d",&product_price);
    copy_item(p->name,product_name);
    copy_item(p->description,product_description);
    p->price=product_price;
    update_product_file();
    printf("\t\t\tProduct updated successfully\n");
}


void print_product_according_category(char category_name[100])
{
    struct Product*p=product_head;
    while(p!=NULL)
    {
        if(strcmp(p->category,category_name)==0)
        {
            printf("\t\t-> %d=%s=%d\n",p->ID,p->name,p->price);
        }
        p=p->next;
    }

}


int product_available(char category_name[100])
{
    struct Product*p=product_head;
    if(product_head==NULL)
    {
        return 0;
    }
    else
    {
        while(p!=NULL)
        {
            if(strcmp(p->category,category_name)==0)
            {
                return 1;
            }
            p=p->next;
        }
        return 0;
    }
}


struct Product* find_product_by_id(int id)
{
    struct Product*p=product_head;
    if(product_head==NULL)
    {
        return NULL;
    }
    else
    {
        while(p!=NULL)
        {
            if(p->ID==id)
            {
                return p;
            }
            p=p->next;
        }
        return NULL;
    }
}


struct Product*find_product_by_id_category(int id,char category_name[100])
{
    struct Product*p=product_head;
    if(product_head==NULL)
    {
        return NULL;
    }
    else
    {
        while(p!=NULL)
        {
            if(p->ID==id && strcmp(p->category,category_name)==0)
            {
                return p;
            }
            p=p->next;
        }
        return NULL;
    }
}


void update_product_file()
{
    FILE *product_ptr;
    struct Product*p=NULL;
    product_ptr=fopen("products.txt","w");
    if(product_ptr==NULL)
    {
        printf("\t\t\tERROR! File opening\n\n");
        exit(1);
    }
    p=product_head;
    while(p!=NULL)
    {
        fprintf(product_ptr,"%d=%s=%s=%d=%s\n",p->ID,p->name,p->description,p->price,p->category);
        p=p->next;
    }
    fclose(product_ptr);
}


void remove_product_from_all_cart(int product_id)
{
    struct User*u=user_head;
    while(u!=NULL)
    {
        extract_cart_from_file_by_userId(u);
        remove_product_cart_by_id(product_id,u);
        free_cart();
        extract_wishlist_from_file_by_userId(u);
        remove_product_wishlist_by_id(product_id,u);
        free_wishlist();
        u=u->next;
    }
}


void maximum__price_product(char category_name[100],struct User*customer)
{
    struct Product*p=product_head;
    struct Product **max_products=(struct Product**)malloc(total_products()*sizeof(struct Product*));
    int maximum=0,i,choice;
    while(p!=NULL)
    {
        if(strcmp(p->category,category_name)==0)
        {
            maximum=p->price;
            break;
        }
        p=p->next;
    }
    while(p!=NULL)
    {
        if(strcmp(p->category,category_name)==0 && p->price>maximum)
        {
            maximum=p->price;
        }
        p=p->next;
    }

    printf("\t\t\tThe products with maximum price [Product name=Product description=Product price]->\n\n");
    p=product_head;
    i=0;
    while(p!=NULL)
    {
        if(strcmp(p->category,category_name)==0 && maximum==p->price)
        {
            printf("\t\t-> %s=%s=%d\n",p->name,p->description,p->price);
            max_products[i]=p;
            i++;
        }
        p=p->next;
    }
    max_products[i]=NULL;
    printf("\t\t\t1.Want to add to cart\n\n\t\t\t2.Want to add to wishlist\n\n\t\t\t3.BACK\n\n");
    printf("\t\t\tEnter the option:");
    scanf("%d",&choice);
    if(choice==1)
    {
        for(i=0; max_products[i]!=NULL; i++)
        {
            cart(max_products[i]->ID,max_products[i],customer);
        }
    }
    else
    {
        for(i=0; max_products[i]!=NULL; i++)
        {
            wishlist(max_products[i]->ID,max_products[i],customer);
        }
    }


}


void minimum__price_product(char category_name[100],struct User*customer)
{
    struct Product*p=product_head;
    struct Product **min_products=(struct Product**)malloc(total_products()*sizeof(struct Product*));
    int minimum=0,i,choice;
    while(p!=NULL)
    {
        if(strcmp(p->category,category_name)==0)
        {
            minimum=p->price;
            break;
        }
        p=p->next;
    }
    while(p!=NULL)
    {
        if(strcmp(p->category,category_name)==0 && p->price<minimum)
        {
            minimum=p->price;
        }
        p=p->next;
    }

    printf("\tThe products with minimum price [Product name=Product description=Product price]->\n");
    p=product_head;
    i=0;
    while(p!=NULL)
    {
        if(strcmp(p->category,category_name)==0 && minimum==p->price)
        {
            printf("-> %s=%s=%d\n",p->name,p->description,p->price);
            min_products[i]=p;
            i++;
        }
        p=p->next;
    }
    min_products[i]=NULL;
    printf("\t\t\t1.Want to add to cart\n\n\t\t\t2.Want to add to wishlist\n\n\t\t\t3.BACK\n\n");
    printf("\t\t\tEnter the option:");
    scanf("%d",&choice);
    if(choice==1)
    {
        for(i=0; min_products[i]!=NULL; i++)
        {
            cart(min_products[i]->ID,min_products[i],customer);
        }
    }
    else
    {
        for(i=0; min_products[i]!=NULL; i++)
        {
            wishlist(min_products[i]->ID,min_products[i],customer);
        }
    }
}


int total_products()
{
    struct Product*p=product_head;
    int total=0;
    while(p!=NULL)
    {
        total+=1;
        p=p->next;
    }
    return total;
}


void product_price_lowest_highest(char category_name[100])
{
    struct Product*p=product_head;
    struct Product  *category_products=(struct Product*)malloc((count_category_products(category_name)+1)*sizeof(struct Product));
    struct Product *sort_products;
    int i;
    i=1;
    while(p!=NULL)
    {
        if(strcmp(p->category,category_name)==0)
        {
            category_products[i]=*p;
            i++;
        }
        p=p->next;
    }

    insert_min_heap(category_products,category_name);

    sort_products=delete_min_heap(category_products,category_name);

    printf("\t\tProducts according to lowest to highest price [Product name=Product description=Product price]\n\n");
    for(i=0; i<count_category_products(category_name); i++)
    {
        printf("\t\t-> %s=%s=%d\n",sort_products[i].name,sort_products[i].description,sort_products[i].price);
    }


}


void product_price_highest_lowest(char category_name[100])
{
    struct Product*p=product_head;
    struct Product  *category_products=(struct Product*)malloc((count_category_products(category_name)+1)*sizeof(struct Product));
    struct Product *sort_products;
    int i;

    i=1;
    while(p!=NULL)
    {
        if(strcmp(p->category,category_name)==0)
        {
            category_products[i]=*p;
            i++;
        }
        p=p->next;
    }

    insert_max_heap(category_products,category_name);

    sort_products=delete_max_heap(category_products,category_name);

    printf("\t\tProducts according to highest to lowest price [Product name=Product description=Product price]\n\n");
    for(i=0; i<count_category_products(category_name); i++)
    {
        printf("\t\t-> %s=%s=%d\n",sort_products[i].name,sort_products[i].description,sort_products[i].price);
    }
}

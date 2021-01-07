#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<time.h>
#include "helper.h"
#include "user.h"
#include "category.h"
#include "product.h"
#include "cart.h"
#include "wishlist.h"
#include "order.h"

void welcome(){
    printf("                         #######################################\n");
    printf("                         |            APNI DUKAN!!!            |\n");
    printf("                         #######################################\n");
}

void enter(char* s) {
    printf("\t\t-|-|-|-|-|-|-|-|-|%s Section-|-|-|-|-|-|-|-|-|-|-\n",s);
}

void printtab() {

    printf("\t\t");
}

int main()
{
    struct User*customer;
    struct Cart*cart_product;
    struct Product*p;
    struct Order*o;
    char categories_name[100][100];
    int total_category;
    int choice1,choice2,choice3,choice4,choice5,choice6=0,choice7,choice8,choice9,choice10;
    int i,order_choice,inc_quantity,dec_quantity,temp;
    char read;
    char category_name[100];
    char secret[100];
    int id;
    FILE *secret_ptr,*category_ptr;

    extract_category_name_from_file(categories_name,&total_category);
    extract_product_name_from_file();
    extract_users_from_file();

    do
    {
        welcome();
        printtab();
        printf("1.Enter as an admin\n\n");
        printtab();
        printf("2.Enter as a customer\n\n");
        printtab();
        printf("3.EXIT\n\n");
        printtab();
        printf("\t\tEnter the option:");
        scanf("%d",&choice1);
        if(choice1==1)
        {
            enter("Admin");
            printf("\t\tEnter the password to enter:");
            i=0;
            do
            {
                secret[i]=getch();
                if(secret[i]==13)
                {
                    break;
                }
                printf("*");
                i++;
            }
            while(1);
            printf("\n");
            secret[i]='\0';
            secret_ptr=fopen("secret.txt","r");
            if(secret_ptr==NULL)
            {
                printf("\t\t\tERROR! File opening\n\n");
                exit(1);
            }
            i=0;
            do
            {
                read=fgetc(secret_ptr);
                if(read!=secret[i] )
                {
                    break;
                }
                i++;
            }
            while(!feof(secret_ptr) && i<strlen(secret));

            if(feof(secret_ptr)|| i>=strlen(secret))
            {
                fclose(secret_ptr);
                printtab();
                printf("\tHELLO ADMIN!\n\n");
                do
                {
                    printtab();
                    printf("1.Add the product\n\n\t\t2.Remove the product\n\n\t\t3.Update product\n\t\t4.BACK\n\n");
                    printf("\t\t\t\tEnter the option:");
                    if(choice2==1)
                    {
                        do
                        {
                            printf("\t\t1.Add product in the existing category\n\n\t\t2.Add product in the new category\n\n\t\t3.BACK\n");
                            printf("\t\t\t\tEnter the option:");
                            scanf("%d",&choice3);
                            if(choice3==1)
                            {
                                if(total_category!=0)
                                {
                                    printf("Categories->\n");
                                    print_categories(categories_name,total_category);
                                    printf("\t\t\t\tEnter the name of the category:");
                                    scanf(" %[^\n]",category_name);
                                    if(search_category(categories_name,total_category,category_name))
                                    {
                                        create_product(category_name);
                                    }
                                    else
                                    {
                                         printf("\t\t\tNo such category found , create new category\n");
                                    }

                                }
                                else
                                {
                                     printf("\t\t\tNo category available, create a new category\n");
                                }
                            }
                            else if(choice3==2)
                            {
                                printtab();
                                printf("Enter the name of the new category:");
                                scanf(" %[^\n]",category_name);
                                if(!search_category(categories_name,total_category,category_name))
                                {
                                    category_ptr=fopen("categories.txt","a");
                                    if(category_ptr==NULL)
                                    {
                                        printf("\t\t\tERROR! File opening\n\n");
                                        exit(1);
                                    }
                                    fprintf(category_ptr,"%s\n",category_name);
                                    fclose(category_ptr);
                                    add_category(categories_name,category_name,&total_category);
                                    create_product(category_name);
                                }
                                else
                                {
                                    printf("\t\t\tCategory already available\n\n");
                                }
                            }
                            else
                            {
                                if(choice3!=3)
                                {
                                     printf("\t\t\tInvalid operation\n\n");
                                }
                            }
                        }
                        while(choice3!=3);
                    }
                    else if(choice2==2)
                    {


                        printtab();
                        printf("Categories->\n");
                        print_categories(categories_name,total_category);
                        printtab();
                        printf("Enter the name of the category:");
                        scanf(" %[^\n]",category_name);
                        if(search_category(categories_name,total_category,category_name))
                        {
                            if(product_available(category_name))
                            {
                                printtab();
                                printf("Products according to the selected category->\n\n");
                                printtab();
                                printf("Products are display as [ID=name=price]\n");
                                print_product_according_category(category_name);
                                printtab();
                                printf("Enter the ID of the product you want to remove:");
                                scanf("%d",&id);
                                remove_product(id);

                            }
                            else
                            {
                                printf("\t\t\tNo product available of that category\n");
                            }
                        }
                        else
                        {
                            printf("\t\t\tNo such category found , create new category\n");
                        }
                    }
                    else if(choice2==3)
                    {
                        printtab();
                        printf("Categories->\n");
                        print_categories(categories_name,total_category);
                        printtab();
                        printf("Enter the name of the category:");
                        scanf(" %[^\n]",category_name);
                        if(search_category(categories_name,total_category,category_name))
                        {
                            if(product_available(category_name))
                            {
                                printtab();
                                printf("Products according to the selected category->\n\n");
                                printtab();
                                printf("Products are display as [ID=name=price]\n");
                                print_product_according_category(category_name);
                                printtab();
                                printf("Enter the ID of the product you want to update:");
                                scanf("%d",&id);
                                update_product(id);

                            }
                            else
                            {
                                printf("\t\t\tNo product available of that category\n\n");
                            }
                        }
                        else
                        {
                            printf("\t\t\tNo such category found , create new category\n\n");
                        }
                    }
                    else
                    {
                        if(choice2!=4)
                        {
                            printf("\t\t\tInvalid operation\n\n");
                        }
                    }
                }
                while(choice2!=4);
            }
            else
            {
                 printf("\t\t\tIncorrect password\n\n");
            }
        }
        else if(choice1==2)
        {
            do
            {
                enter("Customer");
                printf("\t\t1.Sign Up\n\n\t\t2.Login\n\n\t\t3.Back\n\n");
                printf("\t\t\tEnter the option:");
                scanf("%d",&choice4);
                if(choice4==1)
                {
                    sign_up();
                }
                else if(choice4==2)
                {
                    customer=login();
                    if(customer!=NULL)
                    {
                        extract_cart_from_file_by_userId(customer);
                        extract_wishlist_from_file_by_userId(customer);
                        extract_order_from_file(customer);

                        printf("\t\t\tHELLO %s! WELCOME TO THE APNI DUKAN!\n\n",customer->name);
                        do
                        {
                            printf("\t\t1.Shopping\n\n\t\t2.My carts\n\n\t\t3.My wishlist\n\n\t\t4.My orders\n\n\t\t5.Logout\n\n");
                            printf("\t\t\tEnter the option:");
                            scanf("%d",&choice5);
                            if(choice5==1)
                            {
                                enter("Shopping");
                                if(total_category!=0)
                                {
                                    do
                                    {
                                        printtab();
                                        printf("CATEGORIES->\n\n");

                                        print_categories(categories_name,total_category);
                                        printtab();
                                        printf("Choose the category by entering name of the category or press 'B' to back:");
                                        scanf(" %[^\n]",category_name);
                                        if(category_name[0]!='b' && category_name[0]!='B')
                                        {
                                            if(product_available(category_name))
                                            {

                                                do
                                                {
                                                    if(choice6!=2 && choice6!=3)
                                                    {
                                                        printf("\t\t\tProducts according to category->\n\n");
                                                        print_product_according_category(category_name);
                                                    }
                                                     printf("\t\t1.Get detail of specific product\n\n\t\t2.Display sort product lowest to highest according to price\n\n\t\t3.Display sort product highest to lowest according to price\n\n\t\t4.Minimum price product\n\n\t\t5.Maximum price product\n\n\t\t6.BACK\n\n");
                                                    printf("\t\t\tEnter the option:");
                                                    scanf("%d",&choice6);
                                                    if(choice6==1)
                                                    {
                                                        printf("\t\t\tEnter the id of the product:");
                                                        scanf("%d",&id);
                                                        p=find_product_by_id_category(id,category_name);
                                                        if(p!=NULL)
                                                        {
                                                            printf("\t\t\tProduct detail->\n\n");
                                                            printf("\t\t\t%s=%s=%d\n",p->name,p->description,p->price);
                                                            printf("\t\t1.Add product to cart\n\n\t\t2.Add product to wishlist\n\n\t\t3.BACK\n\n");
                                                            printf("\t\t\tEnter the option:");
                                                            scanf("%d",&choice7);
                                                            if(choice7==1)
                                                            {
                                                                cart(id,p,customer);
                                                            }
                                                            else if(choice7==2)
                                                            {
                                                                wishlist(id,p,customer);
                                                            }
                                                            else
                                                            {
                                                                if(choice7!=3)
                                                                {
                                                                    printf("\t\t\tInvalid operation\n\n");
                                                                }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            printf("\t\t\tNo product is available of that ID in these category\n\n");
                                                        }

                                                    }
                                                    else if(choice6==2)
                                                    {
                                                        product_price_lowest_highest(category_name);
                                                    }
                                                    else if(choice6==3)
                                                    {
                                                        product_price_highest_lowest(category_name);
                                                    }
                                                    else if(choice6==4)
                                                    {
                                                        minimum__price_product(category_name,customer);
                                                    }
                                                    else if(choice6==5)
                                                    {
                                                        maximum__price_product(category_name,customer);
                                                    }
                                                    else
                                                    {
                                                        if(choice6!=6)
                                                        {
                                                            printf("\t\t\tInvalid operation\n\n");
                                                        }
                                                    }
                                                }
                                                while(choice6!=6);

                                            }
                                            else
                                            {
                                                printf("\t\t\tNo product is available in these category\n\n");
                                            }
                                        }
                                    }
                                    while(category_name[0]!='b' && category_name[0]!='B');
                                }
                                else
                                {
                                    printf("\t\t\tNo category available in the shop\n\n");
                                }

                            }
                            else if(choice5==2)
                            {
                                enter("Cart");
                                do
                                {
                                    if(cart_head!=NULL)
                                    {

                                        printf("\t\tYour cart items->\n\n");
                                        print_cart();
                                        printf("\t\t1.Remove the cart item\n\n\t\t2.Increment the quantity of item\n\n\t\t3.decrement the quantity of item\n\n\t\t4.Order the cart items\n\n\t\t5.BACK\n\n");
                                        printf("\t\t\tEnter the option:");
                                        scanf("%d",&choice8);
                                        if(choice8==1)
                                        {
                                            printf("\t\t\tEnter the product id:");
                                            scanf("%d",&id);
                                            if(remove_product_cart_by_id(id,customer))
                                            {
                                                printf("\t\t\tItem remove from cart successfully\n\n");
                                            }
                                            else
                                            {
                                                printf("\t\t\tNo item is present with that ID\n\n");
                                            }

                                        }
                                        else if(choice8==2)
                                        {
                                            printf("\t\t\tEnter the product id:");
                                            scanf("%d",&id);
                                            cart_product=cart_product_id(id);
                                            if(cart_product!=NULL)
                                            {
                                                printf("\t\t\tEnter by which number you want to increment the quantity:");
                                                scanf("%d",&inc_quantity);
                                                cart_product->product_quantity+=inc_quantity;
                                                update_cart_file(create_cart_file_name(customer),cart_head);
                                                printf("\t\t\tItem updated successfully\n\n");
                                            }
                                            else
                                            {
                                                printf("\t\t\tNo such item present in the cart\n\n");
                                            }
                                        }
                                        else if(choice8==3)
                                        {
                                            printf("\t\t\tEnter the product id:");
                                            scanf("%d",&id);
                                            cart_product=cart_product_id(id);
                                            if(cart_product!=NULL)
                                            {
                                                if(cart_product->product_quantity!=1)
                                                {
                                                     printf("\t\t\tEnter by which number you want to decrement the quantity:");
                                                    scanf("%d",&dec_quantity);
                                                    if((cart_product->product_quantity-dec_quantity)>0)
                                                    {
                                                        cart_product->product_quantity-=dec_quantity;
                                                        update_cart_file(create_cart_file_name(customer),cart_head);
                                                        printf("\t\t\tItem updated successfully\n\n");
                                                    }
                                                    else
                                                    {
                                                         printf("\t\t\tWe cannot update, the number you enter is making the quantity zero or negative\n");
                                                        printf("\t\t\tYou want to delete your cart item YES[1]/NO[0]:");
                                                        scanf("%d",&temp);
                                                        if(temp==1)
                                                        {
                                                            if(remove_product_cart_by_id(id,customer))
                                                            {
                                                                printf("\t\t\tCart item remove successfully\n");
                                                            }
                                                            else
                                                            {
                                                                printf("\t\t\tCart item not remove\n");
                                                            }
                                                        }
                                                    }
                                                }
                                                else
                                                {
                                                    if(remove_product_cart_by_id(id,customer))
                                                    {
                                                        printf("\t\tCart item remove successfully as there is only one quantity of the product\n");
                                                    }
                                                    else
                                                    {
                                                        printf("\t\tCart item not deleted try again\n");
                                                    }

                                                }

                                            }
                                            else
                                            {
                                                printf("\t\tNo such item present in the cart\n");
                                            }
                                        }
                                        else if(choice8==4)
                                        {
                                            printf("\t\t\tThe total of you cart items = %d\n",cart_total());
                                            printf("\t\t\tYou want to order cart items YES[1]/NO[0]:");
                                            scanf("%d",&order_choice);
                                            if(order_choice==1)
                                            {
                                                create_order(customer);
                                                remove_cart_all(customer);
                                            }
                                        }
                                        else
                                        {
                                            if(choice8!=5)
                                            {
                                                printf("\t\t\tInvalid option\n");
                                            }
                                        }
                                    }

                                    else
                                    {
                                        printf("\t\t\tNo cart items available\n");
                                    }

                                }
                                while(choice8!=5 && cart_head!=NULL);
                            }
                            else if(choice5==3)
                            {
                                enter("Wishlist");
                                do
                                {
                                    if(wishlist_head!=NULL)
                                    {

                                        printf("\t\t\tYour wishlist items->\n");
                                        print_wishlist();
                                        printf("\t\t\t1.Remove the wishlist item\n\n\t\t\t2.Remove all wishlist items\n\n\t\t\t3.BACK\n\n");
                                        printf("\t\t\tEnter the option:");
                                        scanf("%d",&choice9);
                                        if(choice9==1)
                                        {
                                            printf("\t\t\tEnter the product id:");
                                            scanf("%d",&id);
                                            if(remove_product_wishlist_by_id(id,customer))
                                            {
                                                printf("\t\t\tItem from wishlist remove successfully\n\n");
                                            }
                                            else
                                            {
                                                printf("\t\t\tNo such item is present with that id\n\n");
                                            }

                                        }
                                        else if(choice9==2)
                                        {
                                            remove_wishlist_all(customer);
                                            printf("\t\t\tAll wishlist items deleted\n\n");
                                        }
                                        else
                                        {
                                            if(choice9!=3)
                                            {
                                                printf("\t\t\tInvalid option\n\n");
                                            }
                                        }
                                    }

                                    else
                                    {
                                        printf("\t\t\tNo wishlist items available\n\n");
                                    }

                                }
                                while(choice9!=3 && wishlist_head!=NULL);
                            }
                            else if(choice5==4)
                            {
                               enter("Orders");
                                do
                                {
                                    if(order_head!=NULL)
                                    {

                                        printf("\t\t\tYour orders as [Order id=Order address=Order total]->\n\n");
                                        print_order();
                                        printf("\t\t\t1.Detail of specific order\n\n\t\t\t2.Remove specific order\n\n\t\t\t3.BACK\n\n");
                                        printf("\t\t\tEnter the option:");
                                        scanf("%d",&choice10);
                                        if(choice10==1)
                                        {
                                            printf("\t\t\tEnter the order id:");
                                            scanf("%d",&id);
                                            o=find_order_by_id(id);
                                            if(o!=NULL)
                                            {
                                                printf("\t\t\tyour order contain items as [Product name=Product description=Product price]->\n");
                                                print_order_product(o->order_product);
                                            }
                                            else
                                            {
                                                printf("\t\t\tNo order is present of that id\n");
                                            }

                                        }
                                        else if(choice10==2)
                                        {
                                            printf("\t\t\tEnter the order id:");
                                            scanf("%d",&id);
                                            o=find_order_by_id(id);
                                            if(o!=NULL)
                                            {

                                                remove_order(id,customer);
                                            }
                                            else
                                            {
                                                printf("\t\t\tNo order is present of that id\n\n");
                                            }
                                        }
                                        else
                                        {
                                            if(choice10!=3)
                                            {
                                                printf("\t\t\tInvalid option\n\n");
                                            }
                                        }
                                    }

                                    else
                                    {
                                        printf("\t\t\tNo orders available\n\n");
                                    }

                                }
                                while(choice10!=3 && order_head!=NULL);
                            }
                            else
                            {
                                if(choice5==5)
                                {
                                    free_cart();
                                    free_wishlist();
                                    free_order();
                                }
                                else
                                {
                                    printf("\t\t\tInvalid option\n\n");
                                }
                            }
                        }
                        while(choice5!=5);
                    }
                }
                else
                {
                    if(choice4!=3)
                    {
                        printf("\t\t\tInvalid option\n\n");
                    }
                }
            }
            while(choice4!=3);

        }
        else
        {
            if(choice1!=3)
            {
                printf("\t\t\tInvalid operation\n\n");
            }
        }
    }
    while(choice1!=3);

    printf("\t\t\tGood bye! Have a nice day\n\n");
    return 0;
}

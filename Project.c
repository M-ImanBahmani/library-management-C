#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_USERS 100
#define LINE_SIZE 100
#define MAXMEMBERS 100
#define MAXBOOKS 100

//admin's vars and structs
FILE *afpr;
FILE *afpa;
FILE *lfp;
FILE *lfpw;


typedef struct librarians{
	char name_and_surname[30];
	char username[11];
	char password[30];
	//consider uname as national code
	bool is_active;
	
} librarians;


//librarians vars and struct
typedef struct {
    char name[100];
    char lastname[50];
    char type[30];
    char membercode[30];
    char book_name[100];
    char Borrowing_date [20];
	char Return_date [20];
	int fine;
	int balance;
	
} User;

typedef struct {
    char name[100];
    char lastname[50];
    char id[30];
    char type[30];
    char date[10];
    char password[30];
    int isactive;
    char membercode[30];
} Membership;

typedef struct book {
	char name [100];
	char publication [20];
	char author [20];
	char title [20];
}book;

typedef struct {
    char name[100];
    char writer[100];
    char publicationyear[20];
    char subject[20];
    char bookcode[30];
}Book;
Membership members[MAXMEMBERS];
Book books[MAXBOOKS];

//user vars and struct
int i=0 ;
int temp;
int temp_Return;
int found_Return ;


//signs
librarians *read_librarians(int *size);
void file_write(librarians librs[], int size);
bool pass_req(char pass[]);
void encode(char passwords[]);
void decode(char passwords[]);
void admin_welcome();
void change_admin_password();
void add_librarian();
librarians search_librarian(int *n);
void show_librarians(librarians librarian);
void show_librarians_activity();
void edit_librarians();
void change_librarians_password();
void change_librarians_activity();
void admin_menu();
void admin_login();
void librarian_login();
int login_menu();

void searchmember(char *filename, char *code);
int countlines(const char *filename);
void searchthemembers();
void tmembershipcode(char *code);
void tbookcode(char *code);
void addmember();
void admember();
int readMemberships(const char *filename, Membership members[], int *count);
int writeMemberships(const char *filename, Membership members[], int count);
void readBooks(FILE *file, Book books[], int *bookCount);
void displayBookInfo(Book *book);
void modifyBookInfo(Book *book);
void saveBooksToFile(FILE *file, Book books[], int bookCount);
void changepassword(char *filename, char *code, char *newpass);
void repassword();
void listofactivediactive(char *filename);
void addbook();
void sbooksubject(char *filename, char *searchSubject);
void booksubject();
void searchbook(char *filename, char *code);
void viewbooks();
void parse_file(const char *file_path, User **users, int *user_count);
int search_by_user_id(User *users, int user_count, const char *user_id);
int calculate_fine(User *user);
void display_books_with_fines(User *users, int user_count, int userIndex);
void toLowerCase(char *str);
int readUsersFromFile(const char *filename, User users[], int *userCount);
int writeUsersToFile(const char *filename, User users[], int userCount);
int findUserByCode(User users[], int userCount, const char *membercode);
int main_page_K(int choice); 
int return_back(void);

int main_page(int temp);
int countLines(const char *filename);
int return_back(void);
void parse_file(const char *file_path, User **users, int *user_count);
void display_users(User *users, int user_count);
int searchmember_M(char *filename, char *code, book **books, int temp1, User **users, int *user_count);
int calculate_fine(User *user);
void calculate_and_display_fines(User *users, int user_count);
int search_by_user_id(User *users, int user_count, const char *user_id);
int can_borrow_new_book(User *users, int user_count, int userIndex);
void display_books_with_fines(User *users, int user_count, int userIndex);
int pay_fine(User *users, int user_count, int userIndex, int bookIndex);
User* search_user(User users[], int size, const char* membercode);
int search_user_index(User users[], int size, const char* membercode);


int main()
{
	int ttemp;
	//admin
	afpr = fopen("admin_password.txt", "r+");
	afpa = fopen("admin_password.txt", "a+");
	lfp = fopen("librarians.txt", "a+");
	
	if (lfp==NULL)
	{	
		printf("error opening file!");
		return 1;
	}
	
	
	admin_welcome();
	ttemp=login_menu();
	
	
	fclose(afpr);
	fclose(afpa);
	fclose(lfp);
	
	//librarian
	
	//user
	switch (ttemp) {
		case 2 : {
    int choice;
	while (1)
	{
		choice = main_page_K(temp_Return);
		system("cls");
		if(choice<15){
			
        switch(choice) {
            case 1:
                addmember();
                	found_Return= return_back();
   					if(found_Return==1){
					  continue;
					  break ;	
					}
					else{	
						return 0;
					}
            case 2:
                admember();
                	found_Return= return_back();
   					if(found_Return==1){
					  continue;
				   	  break ;	
					}
					else{	
						return 0;
					}
            case 3: {
                Membership members[MAXMEMBERS];
                int count;

                if (!readMemberships("listofthemembers.txt", members, &count)) {
                  return 1;
                }
                char searchCode[30];
                printf("Enter member code: ");
                scanf("%s", searchCode);
                int found = -1;
                for (int i = 0; i < count; i++) {
                  if (strcmp(members[i].membercode, searchCode) == 0) {
                  found = i;
                  break;
                  }
                }
                if (found == -1) {
                  printf("No member found with this code.\n");
                  return 0;
                }
                printf("Current information:\n");
                printf("Name: %s\n", members[found].name);
                printf("Last Name: %s\n", members[found].lastname);
                printf("ID: %s\n", members[found].id);
                printf("Type: %s\n", members[found].type);
                printf("Date: %s\n", members[found].date);
                printf("Password: %s\n", members[found].password);
                printf("Active: %d\n", members[found].isactive);
                char confirm;
                printf("Are you sure you want to update the information? (y/n): ");
                scanf(" %c", &confirm);
                if (confirm == 'y' || confirm == 'Y') { 
                  printf("Enter new information:\n");
                  printf("Name: ");
                  scanf("%s", members[found].name);
                  printf("Last Name: ");
                  scanf("%s", members[found].lastname);
                  printf("ID: ");
                  scanf("%s", members[found].id);
                  printf("Type: ");
                  scanf("%s", members[found].type);
                  printf("Date: ");
                  scanf("%s", members[found].date);
                  printf("Password: ");
                  scanf("%s", members[found].password);
                  printf("Active (1 or 0): ");
                  scanf("%d", &members[found].isactive);
                if (!writeMemberships("listofthemembers.txt", members, count)) {
                   return 1;
                }
                printf("Information updated successfully.\n");
                } 
				else {
                  printf("No changes were made.\n");
                }
        		found_Return= return_back();
   				if(found_Return==1){
				  continue;
				  break ;	
				}
				else{	
				  return 0;
				}
                }

            case 4:
                repassword("listofthemembers.txt");
               	found_Return= return_back();
   				if(found_Return==1){
				  continue;
				  break ;	
				}
				else{	
				  return 0;
				}
            case 5:
                listofactivediactive("listofthemembers.txt");
           		found_Return= return_back();
   				if(found_Return==1){
				  continue;
				  break ;	
				}
				else{	
			     return 0;
				}
            case 6:
                searchthemembers();
           		found_Return= return_back();
   				if(found_Return==1){
				  continue;
				  break ;	
				}
				else{	
				  return 0;
				}
            case 7:
                addbook();
               	found_Return= return_back();
   				if(found_Return==1){
				  continue;
				  break ;	
				}
				else{	
		   		  return 0;
				}
            case 8: {
                FILE *file = fopen("books.txt", "r+");
                if (!file) {
                    printf("Error opening file.\n");
                    return 1;
                }
                Book books[100];
                int bookCount = 0;
                readBooks(file, books, &bookCount);
                printf("Enter book code to search for: ");
                getchar();
                char searchCode[20];
                fgets(searchCode, sizeof(searchCode), stdin);
                searchCode[strcspn(searchCode, "\n")] = 0;
                int found = 0;
                for (int i = 0; i < bookCount; i++) {
                    if (strcmp(books[i].bookcode, searchCode) == 0) {
                        printf("\nBook found!\n");
                        displayBookInfo(&books[i]);
                        char choice;
                        printf("Do you want to modify this book's information? (y/n): ");
                        scanf(" %c", &choice);
                        getchar();
                        if (choice == 'y' || choice == 'Y') {
                            modifyBookInfo(&books[i]);
                            printf("\nUpdated Book Information:\n");
                            displayBookInfo(&books[i]);
                        }
                        found = 1;
                    found_Return= return_back();
   					if(found_Return==1){
					  continue;
					  break ;	
					}
					else{	
					  return 0;
					}
                    }
                }
            

                if (!found) {
                    printf("Book with code %s not found.\n", searchCode);
                }
                saveBooksToFile(file, books, bookCount);
            }
            case 9:
                viewbooks();
                found_Return= return_back();
   				if(found_Return==1){
			   	  continue;
				  break ;	
				}
				else{	
	    	      return 0;
				}
            case 10:
                booksubject();
           		found_Return= return_back();
   				if(found_Return==1){
				  continue;
				  break ;	
				}
				else{	
					return 0;
				}
            case 11 : {
                int select, temp1 , temp2 , back_case_2=0 , i;
		        char yes_no[5] , search[20];
    	        User *users = NULL;
    	        int user_count = 0;
   		        parse_file("Member Borrowing.txt", &users, &user_count);
	            char user_id_to_search2[50];
    			printf("Enter member code to search : ");
   				scanf("%s",user_id_to_search2);
   				int found , temp3;
    			user_id_to_search2[strcspn(user_id_to_search2, "\n")] = '\0'; 
   				found = search_by_user_id(users, user_count, user_id_to_search2);
   				if(found==0){
   					return 0;
				   }
			  	printf("Choose one of the following books (1_%d) : ",found);
			  	scanf("%d",&temp3);	
   				printf("\nborrowing[%d] . name : %s \n",temp3,users[temp3-1].name);
   				printf("borrowing[%d] . name : %s \n",temp3,users[temp3-1].Borrowing_date);
   				printf("borrowing[%d] . name : %s \n",temp3,users[temp3-1].Return_date);
   				printf("\n Do you approve the return of this book? (yes/no)\n");
   				getchar();
			    scanf("%s",yes_no) ;
			   if(strcmp(yes_no,"yes")==0){
   				  time_t t = time(NULL);
           		  struct tm tm = *localtime(&t);
           		  snprintf(users[temp3-1].Return_date, sizeof(users[temp3-1].Return_date),"%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
   				  printf("The return date of the book was recorded . \n");
        		  printf("\nUpdated borrowing[%d].name: %s\n",temp3, users[temp3-1].name);
        		  printf("Updated borrowing[%d].Borrowing_date: %s\n",temp3, users[temp3-1].Borrowing_date);
       			  printf("Updated borrowing[%d].Return_date: %s\n",temp3, users[temp3-1].Return_date);
       			  FILE *fp = fopen("Member Borrowing.txt", "w"); 
            	    if (fp == NULL) {
                      printf("Unable to open the users Member Borrowing for writing.\n");
                      return 5;
                    }
                  for (i = 0; i < user_count; i++) {
                     fprintf(fp, "%s\n", users[i].name);
                     fprintf(fp, "%s\n", users[i].lastname);
                     fprintf(fp, "%s\n", users[i].type);
                     fprintf(fp, "%s\n", users[i].membercode);
                     fprintf(fp, "%s\n", users[i].book_name);
                     fprintf(fp, "%s\n", users[i].Borrowing_date);
                     fprintf(fp, "%s\n", users[i].Return_date);
                    }
                fclose(fp);
		        }
				else{
        		   printf("The request was not approved.\n");
   			    }
   				found_Return= return_back();
   				if(found_Return==1){
			    	continue;
			    	break ;	
				}
				else{	
				   return 0;
			    }
               	}
		    case 12 : {
				int temp2 , x ;
	            User *users = NULL;
   	            int user_count = 0;
   	            parse_file("Member Borrowing.txt", &users, &user_count);
   	            char yes_no[10];
			    if(user_count>0){
				 printf("user_count : %d",user_count);	
			   	 for(i=0; i<user_count ; i++){		
   					printf("\nborrowing[%d] . name : %s \n",i+1,users[i].name);
   					printf("borrowing[%d] . Borrowing_date : %s \n",i+1,users[i].Borrowing_date);
   					printf("borrowing[%d] . Return_date : %s \n",i+1,users[i].Return_date);
			        }
			  		printf("Choose one of the following books (1_%d) : ",user_count);
			  		scanf("%d",&temp2);
   					printf("\nborrowing[%d] . name : %s \n",temp2,users[temp2-1].name);
   					printf("borrowing[%d] . name : %s \n",temp2,users[temp2-1].Borrowing_date);
   					printf("borrowing[%d] . name : %s \n",temp2,users[temp2-1].Return_date);
   					printf("\n Do you approve of borrowing this book? (yes/no)\n");
			    	scanf("%s",yes_no) ;
			   if(strcmp(yes_no,"yes")==0){
   				time_t t = time(NULL);
           		struct tm tm = *localtime(&t);
           		snprintf(users[temp2-1].Borrowing_date, sizeof(users[temp2-1].Borrowing_date),"%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
           		strcpy(users[temp2-1].Return_date, "0");
   				printf("The request was approved. \n");
        		printf("\nUpdated borrowing[%d].name: %s\n",temp2, users[temp2-1].name);
        		printf("Updated borrowing[%d].Borrowing_date: %s\n",temp2, users[temp2-1].Borrowing_date);
       			printf("Updated borrowing[%d].Return_date: %s\n",temp2, users[temp2-1].Return_date);	
       			FILE *fp = fopen("Member Borrowing.txt", "w"); 
            	if (fp == NULL) {
                  printf("Unable to open the users Member Borrowing for writing.\n");
                  return 5;
                }
                for (i = 0; i < user_count; i++) {
                fprintf(fp, "%s\n", users[i].name);
                fprintf(fp, "%s\n", users[i].lastname);
                fprintf(fp, "%s\n", users[i].type);
                fprintf(fp, "%s\n", users[i].membercode);
                fprintf(fp, "%s\n", users[i].book_name);
                fprintf(fp, "%s\n", users[i].Borrowing_date);
                fprintf(fp, "%s\n", users[i].Return_date);
                }
                fclose(fp);
		        }else{
        		  printf("The request was not approved.\n");
   			    }
	        	}else{
			      printf("There is no request. \n");
		        }
				found_Return= return_back();
   				if(found_Return==1){
				  continue;
				  break ;	
				}
				else{	
					return 0;
				}
		        }
		    case 13 : {
				int temp2 , x ;
	            User *users = NULL;
                int user_count = 0;
   	            parse_file("Member Borrowing.txt", &users, &user_count);
   	            char yes_no[10];
				char user_id_to_search3[50];
    			printf("Enter member code to search : ");
   				scanf("%s",user_id_to_search3);
   				user_id_to_search3[strcspn(user_id_to_search3, "\n")] = '\0'; 
   				search_by_user_id(users, user_count, user_id_to_search3);
   				int userIndex3 = -1;
       		    for (int i = 0; i < user_count; i++) {
           		if (strcmp(users[i].membercode, user_id_to_search3) == 0) {
                  userIndex3 = i;
                  break;
            	}
        		}
    			display_books_with_fines(users, user_count, userIndex3);
				found_Return= return_back();
   				if(found_Return==1){
				  continue;
				  break ;	
				}
				else{	
					return 0;
				}
		        }
		    case 14 : {
			    const char *filename = "chargemember.txt";
                User users[MAX_USERS];
                int userCount = 0;
                if (!readUsersFromFile(filename, users, &userCount)) {
                   return 1;
                }
                char membercode[30];
                printf("Enter member code: ");
                scanf("%s", membercode);
                strtok(membercode, "\n"); 
                int userIndex = findUserByCode(users, userCount, membercode);
                if (userIndex == -1) {
                   printf("Error: Member code not found!\n");
                   return 1;
                }
                printf("Current balance: %d\n", users[userIndex].balance);
                int amount;
                printf("Enter amount to add: ");
                scanf("%d", &amount);
                users[userIndex].balance += amount;
                printf("New balance: %d\n", users[userIndex].balance);
                if (!writeUsersToFile(filename, users, userCount)) {
                   return 1;
                }
                printf("User information updated successfully!\n");
			   	found_Return= return_back();
   				if(found_Return==1){
				  continue;
				  break ;	
				}
				else	
					return 0;
	          	}
            case 0:
                exit(0);
                found_Return= return_back();
   				if(found_Return==1){
			    	continue;
			    	break ;	
				}
				else	
					return 0;
            default:
                printf("invalid!\n");
        }
    }
    	else{
	printf("Please enter one of the available numbers \n");
			found_Return= return_back();
   					if(found_Return==1){
					continue;
					break ;	
					}
					else{	
						return 0;
					}
		}
}
			break;
		}
		case 3 : {

	int select, temp1 , temp2 , back_case_2=0;
	char yes_no[5] , search[20];
	
	FILE *fp = fopen ("listofthebooks_m.txt","r");

	if (fp == NULL)
	{
       printf("Error opening listofthebooks_m.\n");
        return 1;
    }
    
	const char *filename = "listofthebooks_m.txt";
    int lines = countLines(filename);
    if (lines != -1) {
        printf("Number of lines in listofthebooks: %d\n", lines);
    }
    
	int book_count = 0; 
	book *books;
	books=(book *)malloc(lines/4 * sizeof(book));
	
	
      while (book_count <= lines/4 && 
           fscanf(fp, "%99[^\n]\n", books[book_count].name) == 1 &&  
           fscanf(fp, "%19[^\n]\n", books[book_count].publication) == 1 &&  
           fscanf(fp, "%19[^\n]\n", books[book_count].author) == 1 &&  
           fscanf(fp, "%19[^\n]\n", books[book_count].title) == 1)
		    {  
        	book_count++; 
    		}
    	fclose(fp);
    	
    	User *users = NULL;
    	int user_count = 0;
   		parse_file("Member Borrowing.txt", &users, &user_count);
   		//display_users(users, user_count);
    	
	while (1)
	{
		int i;
		char user_id_to_search[50];
		select = main_page(temp_Return);
		system("cls");
	if(select<7){
		switch (select)
		{
			case 1 :
				for (i = 0; i < book_count; i++)
			{
        			printf("Book %d: %s\n", i + 1, books[i].name);
   			}
   					found_Return= return_back();
   					if(found_Return==1){
					continue;
					break ;	
					}
					else{	
						return 0;
					}
			case 2 :
					printf("Please enter the name of the book you are looking for : ");
					getchar();
					fgets(search, sizeof(search), stdin);

					for (i = 0; i < book_count; i++)
				{	
        			if(strstr(search,books[i].name)==search)
					{
        				temp1=i;
        				printf("book : %s \n",books[i].name);
        				printf("publication  : %s \n",books[i].publication);
        				printf("author : %s \n",books[i].author);
        				printf("title : %s \n",books[i].title);
        				back_case_2=1;
        				break;
					}
   				}
   			if (back_case_2==0)
		    {
       			printf("\nThe book you were looking for was not found.\n");
				return_back();
				continue;
				break ;
    		}
    	
   		printf("Are you sure about the registration of your loan? (yes/no) \n");
   		scanf("%s",yes_no) ;
   		
   		if(strcmp(yes_no,"yes")==0)
	{
			char code[50];
			int i;
  			printf("Enter member code to search: ");
    		scanf("%s", code);
    		int found ;
			found=searchmember_M("listofthemembers.txt", code , &books,temp1 , &users , &user_count);
			if (found == 1) {
    		int userIndex = -1;

 		   	for (i = 0; i < user_count; i++)
				{
        			if (strcmp(users[i].membercode, code) == 0) 
					{
            		userIndex = i;
           			break;
       				}		
   			 	}	
   			 	
   			 	if (userIndex != -1)
				{
       				if (can_borrow_new_book(users, user_count, userIndex))
					    {
       						printf("Your request has been successfully registered.\n");
						}
						   
				}
    		}
			else 
			{
    			printf("User not found.\n");
			}
			
		}
			
    found_Return = return_back();
    if (found_Return == 1) {
        continue;
    } else {
        return 0;
    }
    break;
					
			
		case 3 :
    			printf("Enter member code to search : ");
   				scanf("%s",user_id_to_search);
   				
    			user_id_to_search[strcspn(user_id_to_search, "\n")] = '\0'; 
   				search_by_user_id(users, user_count, user_id_to_search);
   				
					found_Return= return_back();
   					if(found_Return==1){
					continue;
					break ;	
					}
					else{	
						return 0;
					}
					
					
		case 4: 
    {
        char user_id[50];
        printf("Enter your member code: ");
        scanf("%s", user_id);
        int userIndex2 = -1;

        for (i = 0; i < user_count; i++) {
            if (strcmp(users[i].membercode, user_id) == 0) {
                userIndex2 = i;
                break;
            }
        }

        if (userIndex2 != -1) {
            display_books_with_fines(users, user_count, userIndex2);
            
            int bookIndex;
            printf("Enter the number of the book you want to pay the fine for (0 to cancel): ");
            scanf("%d", &bookIndex);

            
            if (bookIndex > 0) {
                bookIndex--; 
                if (pay_fine(users, user_count, userIndex2, bookIndex)) {
                
                    FILE *fp = fopen("Member Borrowing_pay_fine.txt", "w");
                    if (fp == NULL) {
                        printf("Unable to open the users Member Borrowing_pay_fine for writing.\n");
                        return 5; 
                    }

                    
                    for (i = 0; i < user_count; i++) {
                        fprintf(fp, "%s\n", users[i].name);
                        fprintf(fp, "%s\n", users[i].lastname);
                        fprintf(fp, "%s\n", users[i].type);
                        fprintf(fp, "%s\n", users[i].membercode);
                        fprintf(fp, "%s\n", users[i].book_name);
                        fprintf(fp, "%s\n", users[i].Borrowing_date);
                        fprintf(fp, "%s\n", users[i].Return_date);
                    }

                    fclose(fp); 
                }
            } else {
                printf("Payment canceled.\n");
            }
        } else {
            printf("User not found.\n");
        }

        
        found_Return = return_back();
        if (found_Return == 1) {
            continue; 
        } else {
            return 0; 
        }
    }
    break; 

		case 6 : 
				calculate_and_display_fines(users, user_count);
				found_Return= return_back();
   					if(found_Return==1){
					continue;
					break ;	
					}
					else{
						return 0;
					}
				
	}
}
	else{
	printf("Please enter one of the available numbers \n");
			found_Return= return_back();
   					if(found_Return==1){
					continue;
					break ;	
					}
					else{	
						return 0;
					}
		}
			
	break ;	
	}	
		break;
	}
}
}


void admin_welcome()
{
	
	if (afpr == NULL)
	{
		char admin_pwd1[40], admin_pwd2[40];
		
		fclose(afpr);
		printf("Hello library admin, welcome to your first login to this app!\n");
		
		while(1)
		{
			printf("please enter your password for saving(must be alphanumeric and more than 8 characters):");
			scanf("%s", &admin_pwd1);
			
			if(pass_req(admin_pwd1)==1)
			{
				printf("please enter your password again:");
				scanf("%s", &admin_pwd2);
			
				if(strcmp(admin_pwd1, admin_pwd2)==0)
					break;
				else
					printf("Your two passwords didn't match, try again.\n");
			}
			
		}

		encode(admin_pwd1);
		fprintf(afpa,admin_pwd1);
		rewind(afpa);
		printf("admin's password saved succesfully.");
		sleep(2);
		system("cls");
	}
	else
		fclose(afpr);
		
}


int login_menu()
{
	while(1)
	{
		int n;
		printf
		(
			"welcome, to login as:\n"
			"1.admin\n"
			"2.librarian\n"
			"3.user\n"
			"4.exit\n"
			"select any item by enter its number:"
		);
		scanf("%d", &n);
	
		if(n==1){
	
			admin_login();
			return 100 ;
		}
		
		if(n==2){
		
			librarian_login();
			return n ;
		}
		
		if(n==3){
	
		//	user_login(temp);
			return n ;
		}
		
		else if(n==4){
			break;
		//	return 100 ;
		}
		
		else
			printf("invalid input, please try again\n");
	}
}


//login section

void admin_login()
{
	char saved_pwd[30];
	char entered_pwd[30];
	
	rewind(afpa);
	fscanf(afpa, "%s", saved_pwd);
	decode(saved_pwd);
	
	while(1)
	{
		printf("please enter admin's password:");
		scanf("%s", entered_pwd);
		
		if(strcmp(saved_pwd, entered_pwd)==0)
		{
			printf("your password is correct, welcome admin...\n");
			sleep(3);
			system("cls");
			admin_menu();
			break;
		}
		else
			printf("your password is incorrect, please try again\n");
	}
}


void librarian_login()
{
	int number;
	
	char name[30];
	char saved_pwd[30];
	char entered_pwd[30];
	
	rewind(lfp);
	
	while(1)
	{	
		librarians found = search_librarian(&number);
		
		if(number==-1)
			return;
		
		strcpy(saved_pwd, found.password);
		
		printf("please enter %s's password:", found.name_and_surname);
		scanf("%s", entered_pwd);
		
		if(strcmp(saved_pwd, entered_pwd)==0)
		{
			printf("your password is correct, welcome %s...\n", found.name_and_surname);
			sleep(3);
			system("cls");
			//librarian_menu();
			break;
		}
		else
			printf("your password is incorrect, please try again\n");
	}
}


//admin section

void admin_menu()
{
	short int n;
	while(1)
	{
		printf
		(
			"\n1.add librarian\n"
			"2.edit librarians\n"
			"3.enable or disable librarians\n"
			"4.change librarian's password\n"
			"5.show list of active and inactive librarians\n"
			"6.change admin's password\n"
			"7.logout\n"
			"To select any item, please enter its number:"
		);
		scanf("%hd", &n);
	
		if(n==1)
			add_librarian();
		
		else if(n==2)
			edit_librarians();
		
		else if(n==3)
			change_librarians_activity();
			
		else if(n==4)
			change_librarians_password();
		
		else if(n==5)
			show_librarians_activity();
		
		else if(n==6)
			change_admin_password();
	
		else if(n==7)
		{
			system("cls");
			break;
		}
		
		else
			printf("invalid input, please try again");
	}
}


void add_librarian()
{
	librarians newlib;
	while(1)
	{
		printf("please enter librarian's name and surname:");
		scanf("%s", &newlib.name_and_surname);
		printf("please enter librarian's national-code as username:");
		scanf("%s", &newlib.username);
		printf("please enter librarian's password(must be alphanumeric and more than 8 characters):");
		scanf("%s", &newlib.password);
		if(pass_req(newlib.password)==1)
			break;
	}
	
	newlib.is_active=true;
	
	size_t result = fwrite(&newlib, sizeof(librarians), 1, lfp);
	if(result==0)
		printf("error writing librarian to file!");
}


void edit_librarians ()
{
	int size;
	short int n;
	char name[30];
	char username[11];
	int number;
	
	librarians found = search_librarian(&number);
	if(number==-1)
		return;
	show_librarians(found);
	
	while(1)
	{
		printf
		(
			"1.edit name and surname\n"
			"2.edit username(national code)\n"
			"3.exit\n"
			"To select any item, please enter its number:"
		);
		scanf("%d", &n);
		
		if(n==1)
		{
			printf("please enter new name and surname:");
			scanf("%s", name);
			librarians *librs=read_librarians(&size);
			strcpy(librs[number].name_and_surname, name);
			file_write(librs, size);
		}
		
		else if(n==2)
		{
			printf("please enter new username(national code):");
			scanf("%s", username);
			librarians *librs=read_librarians(&size);
			strcpy(librs[number].username, username);
			file_write(librs, size);
		}
		
		else if(n==3)
		{
			break;
		}
		
		else
		{
			printf("invalid number, please try again\n");
		}
		
	}
}


void change_librarians_activity()
{
	int size;
	int number;
	int activity=2;
	librarians found=search_librarian(&number);
	if(number==-1)
		return;
	show_librarians(found);
	while(1)
	{
		if(found.is_active==0)
		{
			printf("enter 1 if you want to enable the librarian:\n");
			scanf("%hd", &activity);
		}
		else
		{
			printf("enter 0 if you want to disable the librarian:\n");
			scanf("%hd", &activity);
		}
		
		if(activity!=0 ^ activity!=1)
		{
			librarians *librs=read_librarians(&size);
			librs[number].is_active=activity;
			file_write(librs, size);
			break;
		}
		else
			printf("invalid input, please try again\n");
	}
}


void change_librarians_password()
{
	int number;
	int size;
	char old_saved_pwd[30];
	char old_entered_pwd[30];
	char new_pwd1[30];
	char new_pwd2[30];
	
	librarians found=search_librarian(&number);
	if(number==-1)
		return;
	show_librarians(found);
	strcpy(old_saved_pwd, found.password);
	
	while(1)
	{
		printf("please it's your old password:");
		scanf("%s", &old_entered_pwd);
		if(strcmp(old_saved_pwd, old_entered_pwd)!=0)
		{
			printf("incorrect password, please try again.\n");
			continue;
		}
		printf("please enter it's new password:");
		scanf("%s", &new_pwd1);
		printf("please enter it's new password again:");
		scanf("%s", &new_pwd2);
		if(strcmp(new_pwd1, new_pwd2)==0)
			break;
		else
			printf("it's two passwords didn't match, try again.\n");
	}
	librarians *librs=read_librarians(&size);
	strcpy(librs[number].password, new_pwd1);
	file_write(librs, size);
}


void show_librarians_activity()
{
	int i;
	librarians librarian;
	
	rewind(lfp);
	printf("\n");
	
	while (fread(&librarian, sizeof(librarians), 1, lfp)!=0)
	{
		if(librarian.is_active==1)
			printf("librarian %s: active\n", librarian.name_and_surname);
		else
			printf("librarian %s: inactive\n", librarian.name_and_surname);
	}
}


void change_admin_password()
{
	char old_saved_pwd[30];
	char old_entered_pwd[30];
	char new_pwd1[30];
	char new_pwd2[30];
	
	rewind(afpa);
	fscanf(afpa, "%s", old_saved_pwd);
	decode(old_saved_pwd);
	while(1)
	{
		printf("please enter your old password:");
		scanf("%s", &old_entered_pwd);
		if(strcmp(old_saved_pwd, old_entered_pwd)!=0)
		{
			printf("incorrect password, please try again\n");
			continue;
		}
		printf("please enter your new password:");
		scanf("%s", &new_pwd1);
		printf("please enter your new password again:");
		scanf("%s", &new_pwd2);
		if(strcmp(new_pwd1, new_pwd2)==0)
			break;
		else
			printf("Your two passwords didn't match, try again.\n");
	}
	
	fclose(afpa);
	FILE *afpw = fopen("admin_password.txt", "w");
	if (afpw==NULL)
	{	
		printf("error opening file!");
		return;
	}
	encode(new_pwd1);
	fprintf(afpw,new_pwd1);
	fclose(afpw);
	afpa = fopen("admin_password.txt", "a+");
	if (afpa==NULL)
	{	
		printf("error opening file!");
		return;
	}
}



//auxiliary funcs

void encode(char passwords[])
{
	int i;
	for (i=0; i<strlen(passwords); i++)
		passwords[i] += 12;
}


void decode(char passwords[])
{
	int i;
	for (i=0; i<strlen(passwords); i++)
		passwords[i] -= 12;
}


bool pass_req(char pass[])
{
	int i;
	
	if(strlen(pass)<8)
	{
		printf("password is less than 8 characters, try again.\n\n");
		return false;
	}
	
	for(i=0; pass[i]!='\0'; i++)
	{
		if(isalnum(pass[i])==0)
		{
			printf("password isn't alphanumeric, try again.\n\n");
			return false;
		}
	}
	
	return true;
}


librarians *read_librarians(int *size)
{
	int i=0;
	*size=0;
	rewind(lfp);
	
	librarians *librs=(librarians *)malloc(sizeof(librarians));
	
	for(i=0; fread(&librs[i], sizeof(librarians), 1, lfp)!=0; i++)
	{
		if (librs==NULL)
		{
			printf("error while allocating memory!");
			exit(1);
		}
		
		librs=(librarians *)realloc(librs, (2+i)*sizeof(librarians));
	}
	
	*size=i;
	return librs;
}


librarians search_librarian(int *n)
{	
	int i;	
	char name[30];
	librarians found;
	
	printf("please enter name of librarian exactly:");
	scanf("%s", &name);
	
	rewind(lfp);
	
	for (i=0; fread(&found, sizeof(librarians), 1, lfp)!=0 ; i++)
	{
		if(strcmp(found.name_and_surname, name)==0)
		{
			*n=i;
			return found;
		}
	}
	
	*n=-1;
	printf("librarian doesn't exist\n\n");
}


void show_librarians(librarians librarian)
{
	int i;
	printf("\nname : %s\n", librarian.name_and_surname);
	printf("username(national code) : %s\n", librarian.username);
	printf("is active: %s\n\n", librarian.is_active?"yes":"no");
}


void file_write(librarians librs[], int size)
{
	
			fclose(lfp);
			lfpw = fopen("librarians.txt", "w");
			if (lfpw==NULL)
			{	
				printf("error opening file!");
				return;
			}
			size_t result = fwrite(librs, sizeof(librarians), size, lfpw);
			if(result==0)
				printf("error writing to file!");
				
			fclose(lfpw);
			lfp = fopen("librarians.txt", "a+");
			if (lfp==NULL)
			{	
				printf("error opening file!");
				return;
			}
			free(librs);
}




//librarian section





 
//user section
int main_page (int temp)
{
	printf("\n \t Hi User \n");
	printf("1. List of books in the Library \n");
	printf("2. Borrowing books \n");
	printf("3. List of borrowed Books \n");
	printf("4. Payment of fines for borrowed Books \n");
	printf("5. Change Password \n");
	printf("6. Display fine books \n");
	printf("0. Exit \n");
	scanf("%d",&temp);
	return temp ;
}

int countLines(const char *filename) {
    FILE *file = fopen(filename, "r"); 
    if (file == NULL) {
        printf("Unable to open file: %s\n", filename);
        return -1; 
    }
    int lineCount = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lineCount++;
        }
    }
    fclose(file); 
    return lineCount;
}

int return_back (){
	int found=0 ;
			printf(" \n Please select one of the options below : ");
			printf(" \n 1. return back \n");
			scanf("%d",&temp_Return);
			if(temp_Return==1){
			found=1;
			system("cls");
			return found;
		}
		else{
			return found;
		}
}


void parse_file(const char *file_path, User **users, int *user_count) {
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Unable to open %s !\n",file_path);
        return; 
    }
    *user_count = 0;
    User *temp_users = NULL; 
    while (1) {
        User user;

        if (fscanf(fp, "%s %s %s %s %s %s %s", 
                   user.name, user.lastname, user.type, user.membercode,
                   user.book_name, user.Borrowing_date, user.Return_date) != 7) {
            break; 
        }

        user.name[strcspn(user.name, "\n")] = '\0';
        user.lastname[strcspn(user.lastname, "\n")] = '\0';
        user.type[strcspn(user.type, "\n")] = '\0';
        user.membercode[strcspn(user.membercode, "\n")] = '\0';
        user.book_name[strcspn(user.book_name, "\n")] = '\0';
        user.Borrowing_date[strcspn(user.Borrowing_date, "\n")] = '\0';
        user.Return_date[strcspn(user.Return_date, "\n")] = '\0';

        (*user_count)++;
        //printf("Read user: %s %s\n", user.name, user.lastname);
   		//printf("user_count after reading user: %d\n", *user_count);
      
        temp_users = (User *)realloc(*users, (*user_count) * sizeof(User));
        if (temp_users == NULL) {
            printf("Memory allocation failed!\n");
            fclose(fp);
            return;
        }
        *users = temp_users;

        (*users)[*user_count - 1] = user;
    }

    fclose(fp);
}

void display_users(User *users, int user_count) {
	
	//printf("user_count:%d \n",user_count);   
	 	
    for (i = 0; i < user_count; i++) {	
        printf("name: %s\n", users[i].name);
        printf("lastname: %s\n", users[i].lastname);
        printf("type: %s\n", users[i].type);
        printf("membercode: %s\n", users[i].membercode);
        printf("book_name: %s\n", users[i].book_name);
        printf("Borrowing_date: %s\n", users[i].Borrowing_date);
        printf("Return_date: %s\n\n", users[i].Return_date);
    }
}


int searchmember_M(char *filename, char *code ,book **books, int temp1 , User **users, int *user_count) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Unable to open %s!\n",filename);
        return 5;
    }
    Membership member;
    int found = 0;
    while (!feof(fp)) {
        fgets(member.name, sizeof(member.name), fp);
        fgets(member.lastname, sizeof(member.lastname), fp);
        fgets(member.id, sizeof(member.id), fp);
        fgets(member.type, sizeof(member.type), fp);
        fgets(member.date, sizeof(member.date), fp);
        fgets(member.password, sizeof(member.password), fp);
        fscanf(fp, "%d\n", &member.isactive);
        fgets(member.membercode, sizeof(member.membercode), fp);
        
        member.name[strcspn(member.name, "\n")] = 0;
        member.lastname[strcspn(member.lastname, "\n")] = 0;
        member.id[strcspn(member.id, "\n")] = 0;
        member.type[strcspn(member.type, "\n")] = 0;
        member.date[strcspn(member.date, "\n")] = 0;
        member.password[strcspn(member.password, "\n")] = 0;
        member.membercode[strcspn(member.membercode, "\n")] = 0;
        
        if (strcmp(member.membercode, code) == 0) {
        	
        	//printf("Before adding new user:\n");
    		//printf("user_count: %d\n", *user_count);
   			//printf("New user found: %s %s\n", member.name, member.lastname);

        	FILE *fp2 = fopen("Member Borrowing.txt","a+");
        	if (fp2 == NULL)
		{
        	printf("Unable to open Member Borrowing.txt!\n");
        	return 5;
    	}
    	
        	printf("member found!\n");
            printf("name:%s\n", member.name);
			fprintf(fp2,"%s\n", member.name);
            printf("last Name:%s\n", member.lastname);
            fprintf(fp2,"%s\n", member.lastname);
            printf("membership type:%s\n", member.type);
            fprintf(fp2,"%s\n", member.type);
            printf("member Code:%s\n", member.membercode);
            fprintf(fp2,"%s\n", member.membercode);
            printf("name book :%s\n",(*books)[temp1].name);
            fprintf(fp2,"%s\n",(*books)[temp1].name); 
        	printf("Borrowing_date :%s\n","0");
            fprintf(fp2,"%s\n","0");
            printf("name book :%s\n","0"); 
            fprintf(fp2,"%s\n","0");
            
            User new_user;
            strcpy(new_user.name, member.name);
            strcpy(new_user.lastname, member.lastname);
            strcpy(new_user.type, member.type);
            strcpy(new_user.membercode, member.membercode);
            strcpy(new_user.book_name, (*books)[temp1].name);
            strcpy(new_user.Borrowing_date, "0");
            strcpy(new_user.Return_date, "0");
            
            (*user_count)++;
            //printf("After incrementing user_count:\n");
    		//printf("user_count: %d\n", *user_count);
    		
            User *temp_users = (User *) realloc(*users, (*user_count) * sizeof(User));
            
            if (temp_users == NULL) {
                printf("Memory allocation failed!\n");
                fclose(fp);
                fclose(fp2);
                return 5;
            }
            *users = temp_users;
            (*users)[*user_count - 1] = new_user;
            
            fclose(fp2);
            found = 1;
            break;
        }
    }
    
    fclose(fp);
    return found ;
}

int calculate_fine(User *user) {
    struct tm borrowing_tm = {0}, return_tm = {0};
    time_t borrowing_time, return_time;
    double diff_days;
    int fine = 0;
    
    sscanf(user->Borrowing_date, "%d-%d-%d", &borrowing_tm.tm_year, &borrowing_tm.tm_mon, &borrowing_tm.tm_mday);
    borrowing_tm.tm_year -= 1900; 
    borrowing_tm.tm_mon -= 1; 
    borrowing_time = mktime(&borrowing_tm);
    
   
    sscanf(user->Return_date, "%d-%d-%d", &return_tm.tm_year, &return_tm.tm_mon, &return_tm.tm_mday);
    return_tm.tm_year -= 1900;
    return_tm.tm_mon -= 1;
    return_time = mktime(&return_tm);
    
   
    diff_days = difftime(return_time, borrowing_time) / (60 * 60 * 24);
    
   
    if (diff_days <= 0) {
        return 0;
    }
    
    
    if (strcmp(user->type, "student") == 0) {
       
        if (diff_days <= 14) {
            fine = 0;  
        } else {
            fine = (diff_days - 14) * 1000;
        }
    } else if (strcmp(user->type, "professor") == 0) {
       
        if (diff_days <= 30) {
            fine = 0; 
        } else {
            fine = (diff_days - 30) * 2000;
        }
    } else {
        if (diff_days <= 7) {
            fine = 0;  
        } else {
            fine = (diff_days - 7) * 1000;
        }
    }
    
    return fine;
}

void calculate_and_display_fines(User *users, int user_count) {
    for (i = 0; i < user_count; i++) {
        users[i].fine = calculate_fine(&users[i]);
        printf("User: %s %s\n", users[i].name, users[i].lastname);
        printf("Book: %s\n", users[i].book_name);
        printf("Fine: %d IRR\n\n", users[i].fine);
    }
}

int search_by_user_id(User *users, int user_count, const char *user_id) {
		int found = 0;
		i=0;
		while (i<user_count) {
        	if (strcmp(users[i].membercode, user_id) == 0) {
        		printf("book [%d]:\n",found+1);
            	printf("code user : %s \n", user_id);
            	printf("name : %s \n",users[i].name);
            	printf("last name : %s\n",users[i].lastname);
           	 	printf("book name : %s\n", users[i].book_name);
           	 	printf("Borrowing_date : %s\n", users[i].Borrowing_date);
            	printf("Return_date : %s\n\n", users[i].Return_date);
            	++found ;
        }
        i++;
    }
    if (found==0) { 
        printf("You have not borrowed a book with this username : %s .\n", user_id);
    }
    return found ;
}

int can_borrow_new_book(User *users, int user_count, int userIndex) {
   
    if (strcmp(users[userIndex].Return_date, "0") != 0) {
       
        users[userIndex].fine = calculate_fine(&users[userIndex]); 

        if (users[userIndex].fine > 0) {
            printf("You have an outstanding fine of %d IRR. You cannot borrow new books until the fine is paid.\n", users[userIndex].fine);
            return 0; 
        }
    }

    return 1;
}

void display_books_with_fines(User *users, int user_count, int userIndex) {
    int found = 0;
    printf("Books with fines for %s %s:\n", users[userIndex].name, users[userIndex].lastname);
    for (i = 0; i < user_count; i++) {
        if (strcmp(users[i].membercode, users[userIndex].membercode) == 0 && strcmp(users[i].Return_date, "0") != 0) {
            users[i].fine = calculate_fine(&users[i]);
            if (users[i].fine > 0) {
                printf("%d. %s - Fine: %d IRR\n", i + 1, users[i].book_name, users[i].fine);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("You don't have any books with fines.\n");
    }
}

int pay_fine(User *users, int user_count, int userIndex, int bookIndex) {
    
    char confirmation[10];
    printf("Are you sure you want to pay the fine of %d IRR for the book \"%s\"? (yes/no): ", 
           users[bookIndex].fine, users[bookIndex].book_name);
    scanf("%s", confirmation);

   
    if (strcmp(confirmation, "yes") == 0) {
        printf("The fine of %d IRR for the book \"%s\" has been successfully paid.\n", 
               users[bookIndex].fine, users[bookIndex].book_name);
        
      
        users[bookIndex].fine = 0; 
        strcpy(users[bookIndex].Return_date, "Paid");

        return 1; 
    } else {
        printf("The payment was canceled.\n");
        return 0; 
    }
}

User* search_user(User users[], int size, const char* membercode) {
	int found=0 ;
 for (i = 0; i < size; i++)
  {
   if (strcmp(users[i].membercode, membercode) == 0) 
   { 
   return &users[i];
    }
  } 
   return NULL; 
   }
   
   int search_user_index(User users[], int size, const char* membercode) {
    for (i = 0; i < size; i++) {
        if (strcmp(users[i].membercode, membercode) == 0) {
            return 1; 
        }
    }
    return -1; 
}

int main_page_K (int choice)
{
        printf("1. add new member\n");
        printf("2. active/diactive member\n");
        printf("3. update member info\n");
        printf("4. change pass\n");
        printf("5. list of active and deactive members\n");
        printf("6. search member\n");
        printf("7. add new book\n");
        printf("8. update book info\n");
        printf("9. view books\n");
        printf("10. search subject\n");
        printf("11. Book return\n");
        printf("12. Approval or rejection of books\n");
        printf("13. Display of member along with fines, if any\n");
        printf("14. charge member\n");
        printf("0. exite\n");
        scanf("%d", &choice);
        return choice;
}
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// ???? ???? ?????? ???? ?? ????
int readUsersFromFile(const char *filename, User users[], int *userCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }

    int count = 0;
    while (fgets(users[count].name, LINE_SIZE, file) &&
           fgets(users[count].lastname, LINE_SIZE, file) &&
           fgets(users[count].type, LINE_SIZE, file) &&
           fgets(users[count].membercode, LINE_SIZE, file) &&
           fgets(users[count].book_name, LINE_SIZE, file) &&
           fgets(users[count].Borrowing_date, LINE_SIZE, file) &&
           fgets(users[count].Return_date, LINE_SIZE, file)) {
        char balanceStr[LINE_SIZE];
        if (fgets(balanceStr, LINE_SIZE, file)) {
            strtok(balanceStr, "\n"); // ??? '\n'
            if (strlen(balanceStr) > 0 && strspn(balanceStr, "0123456789") == strlen(balanceStr)) {
                users[count].balance = atoi(balanceStr);
            } else {
                users[count].balance = 0; // ????? ???????
            }
        } else {
            users[count].balance = 0; // ????? ???????
        }
        // ??? '\n' ?? ?????? ????
        strtok(users[count].name, "\n");
        strtok(users[count].lastname, "\n");
        strtok(users[count].type, "\n");
        strtok(users[count].membercode, "\n");
        strtok(users[count].book_name, "\n");
        strtok(users[count].Borrowing_date, "\n");
        strtok(users[count].Return_date, "\n");
        count++;
        if (count >= MAX_USERS) break;
    }

    *userCount = count;
    fclose(file);
    return 1;
}

// ???? ???? ????? ??????? ?? ????
int writeUsersToFile(const char *filename, User users[], int userCount) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%d\n",
                users[i].name,
                users[i].lastname,
                users[i].type,
                users[i].membercode,
                users[i].book_name,
                users[i].Borrowing_date,
                users[i].Return_date,
                users[i].balance);
    }

    fclose(file);
    return 1;
}
int findUserByCode(User users[], int userCount, const char *membercode) {
    char tempCode[30];
    for (int i = 0; i < userCount; i++) {
        // ??? ?? ??? ???? ??????
        strcpy(tempCode, users[i].membercode);
        toLowerCase(tempCode);

        // ????? ?? ????? ?? ???? ????
        char inputCode[30];
        strcpy(inputCode, membercode);
        toLowerCase(inputCode);

        if (strcmp(tempCode, inputCode) == 0) {
            return i;
        }
    }
    return -1; 
}
void searchmember(char *filename, char *code){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Unable to open file!\n");
        return ;
    }
    Membership member;
    int found = 0;
    while (!feof(fp)) {
        fgets(member.name, sizeof(member.name), fp);
        fgets(member.lastname, sizeof(member.lastname), fp);
        fgets(member.id, sizeof(member.id), fp);
        fgets(member.type, sizeof(member.type), fp);
        fgets(member.date, sizeof(member.date), fp);
        fgets(member.password, sizeof(member.password), fp);
        fscanf(fp, "%d\n", &member.isactive);
        fgets(member.membercode, sizeof(member.membercode), fp);
        member.name[strcspn(member.name, "\n")] = 0;
        member.lastname[strcspn(member.lastname, "\n")] = 0;
        member.id[strcspn(member.id, "\n")] = 0;
        member.type[strcspn(member.type, "\n")] = 0;
        member.date[strcspn(member.date, "\n")] = 0;
        member.password[strcspn(member.password, "\n")] = 0;
        member.membercode[strcspn(member.membercode, "\n")] = 0;
        if (strcmp(member.membercode, code) == 0) {
            printf("member found!\n");
            printf("name:%s\n", member.name);
            printf("last Name:%s\n", member.lastname);
            printf("national ID:%s\n", member.id);
            printf("membership type:%s\n", member.type);
            printf("date of membership:%s\n", member.date);
            printf("password:%s\n", member.password);
            printf("active:%d\n", member.isactive);
            printf("member Code:%s\n", member.membercode);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("member not found.\n");
    }
    fclose(fp);
}
int countlines(const char *filename){
    FILE *file=fopen(filename,"r");
    if(file==NULL){
        printf("file not found!");
        return 50;
    }
    int linecount=0;
    char ch;
    while((ch=fgetc(file))!=EOF){
        if(ch=='\n'){
            linecount++;
        }
    }
    fclose(file);
    return linecount;
}
int membercount = 0;
int bookcount = 0;
void searchthemembers(){
    char code[30];
    printf("Enter member code to search: ");
    scanf("%s", code);
    searchmember("listofthemembers.txt", code);
}

void tmembershipcode(char *code) {
    sprintf(code, "M%d", rand() % 10000);
}
void tbookcode(char *code) {
    sprintf(code, "B%d", rand() % 10000);
}
void addmember() {
   FILE *mfp = fopen("listofthemembers.txt", "a+");
    if (mfp == NULL){
        printf("Unable to open file!");
        return ;
    }
    else{
    Membership newmember;
    printf("Enter name:\n");
    getchar();
    fgets(newmember.name, sizeof(newmember.name), stdin);
    printf("last name:\n");
    fgets(newmember.lastname, sizeof(newmember.lastname), stdin);
    printf("national ID:\n");
    fgets(newmember.id, sizeof(newmember.id), stdin);
    printf("membership type(student/professor/ordinary):\n ");
    fgets(newmember.type, sizeof(newmember.type), stdin);
    printf("date of membership:\n");
    fgets(newmember.date, sizeof(newmember.date), stdin);
    printf("enter your password:\n");
    fgets(newmember.password, sizeof(newmember.password), stdin);
    newmember.isactive = 1;
    fprintf(mfp,"%s",newmember.name);
    fprintf(mfp,"%s", newmember.lastname);
    fprintf(mfp,"%s", newmember.id);
    fprintf(mfp,"%s", newmember.type);
    fprintf(mfp,"%s", newmember.date);
    fprintf(mfp,"%s", newmember.password);
    fprintf(mfp,"%d\n", newmember.isactive);
    tmembershipcode(newmember.membercode);
    fprintf(mfp, "%s\n", newmember.membercode);
    members[membercount++] = newmember;
    printf("new member successfully added! %s\n", newmember.membercode);
    fclose(mfp);
    }
}
void admember() {
    Membership members;
    char code[30];
    printf("Enter member code to search: ");
    scanf("%s", code);
    searchmember("listofthemembers.txt", code);
    FILE *adfp=fopen("listofthemembers.txt","a+");
    if (adfp == NULL) {
        printf("Unable to open file!\n");
        return;
    }
    char taiid;
    printf("are you sure?(y/n):");
    scanf(" %c", &taiid);
    if (taiid == 'y'||taiid=='Y') {
    members.isactive = ! (members.isactive);
    printf("status changed !\n");
    }
    fclose(adfp);
}

int readMemberships(const char *filename, Membership members[], int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    *count = 0;
    while (fscanf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n",
                  members[*count].name,
                  members[*count].lastname,
                  members[*count].id,
                  members[*count].type,
                  members[*count].date,
                  members[*count].password,
                  &members[*count].isactive,
                  members[*count].membercode) != EOF) {
        (*count)++;
        if (*count >= MAXMEMBERS) break;
    }

    fclose(file);
    return 1;
}

int writeMemberships(const char *filename, Membership members[], int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n",
                members[i].name,
                members[i].lastname,
                members[i].id,
                members[i].type,
                members[i].date,
                members[i].password,
                members[i].isactive,
                members[i].membercode);
    }

    fclose(file);
    return 1;
}

void readBooks(FILE *file, Book books[], int *bookCount) {
    *bookCount = 0;
    while (fscanf(file, "%s %s %s %s %s\n", books[*bookCount].name, books[*bookCount].writer, books[*bookCount].publicationyear, books[*bookCount].subject, books[*bookCount].bookcode) != EOF) {
        (*bookCount)++;
    }
}

void displayBookInfo(Book *book) {
    printf("Name: %s\n", book->name);
    printf("Writer: %s\n", book->writer);
    printf("Publication Year: %s\n", book->publicationyear);
    printf("Subject: %s\n", book->subject);
    printf("Book Code: %s\n", book->bookcode);
}

void modifyBookInfo(Book *book) {
    printf("Modify information:\n");

    printf("Enter new name (or press enter to keep unchanged): ");
    char temp[50];
    fgets(temp, sizeof(temp), stdin);
    if (strlen(temp) > 1) {
        sscanf(temp, "%s", book->name);
    }

    printf("Enter new writer (or press enter to keep unchanged): ");
    fgets(temp, sizeof(temp), stdin);
    if (strlen(temp) > 1) {
        sscanf(temp, "%s", book->writer);
    }

    printf("Enter new publication year (or press enter to keep unchanged): ");
    fgets(temp, sizeof(temp), stdin);
    if (strlen(temp) > 1) {
        sscanf(temp, "%s", book->publicationyear);
    }

    printf("Enter new subject (or press enter to keep unchanged): ");
    fgets(temp, sizeof(temp), stdin);
    if (strlen(temp) > 1) {
        sscanf(temp, "%s", book->subject);
    }
}

void saveBooksToFile(FILE *file, Book books[], int bookCount) {
    freopen("books.txt", "w", file);

    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%s\n", books[i].name);
        fprintf(file, "%s\n", books[i].writer);
        fprintf(file, "%s\n", books[i].publicationyear);
        fprintf(file, "%s\n", books[i].subject);
        fprintf(file, "%s\n", books[i].bookcode);
    }
}
void changepassword(char *filename, char *code, char *newpass) {
    FILE *fp = fopen(filename, "r+");
    if (fp == NULL) {
        printf("file not opened!\n");
        return;
    }
    Membership temp;
    while (!feof(fp)) {
        long pos = ftell(fp);
        fgets(temp.name, sizeof(temp.name), fp);
        fgets(temp.lastname, sizeof(temp.lastname), fp);
        fgets(temp.id, sizeof(temp.id), fp);
        fgets(temp.type, sizeof(temp.type), fp);
        fgets(temp.date, sizeof(temp.date), fp);
        fgets(temp.password, sizeof(temp.password), fp);
        fscanf(fp, "%d\n", &temp.isactive);
        fgets(temp.membercode, sizeof(temp.membercode), fp);
        temp.name[strcspn(temp.name, "\n")] = 0;
        temp.lastname[strcspn(temp.lastname, "\n")] = 0;
        temp.id[strcspn(temp.id, "\n")] = 0;
        temp.type[strcspn(temp.type, "\n")] = 0;
        temp.date[strcspn(temp.date, "\n")] = 0;
        temp.password[strcspn(temp.password, "\n")] = 0;
        temp.membercode[strcspn(temp.membercode, "\n")] = 0;
        if (strcmp(temp.membercode, code) == 0) {
            strcpy(temp.password, newpass);
            fseek(fp, pos, SEEK_SET);
            fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%s\n%d\n%s\n", temp.name, temp.lastname, temp.id,
                     temp.type, temp.date, temp.password, temp.isactive, temp.membercode);
            break;
        }
    }
    fclose(fp);

}
void repassword(){
    char code[20];
    char newpass[20];
    char taiidpass[20];
    printf("Enter member code: ");
    scanf("%s", code);
    searchmember("listofthemembers.txt", code);
    char taiid;
    printf("Are you sure? (y/n): ");
    scanf(" %c", &taiid);
    if (taiid == 'y' || taiid == 'Y') {
        do {
            printf("new password:");
            scanf("%s", newpass);
            printf("confirm new password:");
            scanf("%s", taiidpass);
            if (strcmp(newpass, taiidpass) != 0) {
                printf("Passwords not match!try again\n");
            }
        } while (strcmp(newpass, taiidpass) != 0);
        changepassword("listofthemembers.txt", code, newpass);
        printf("Password changed successfully!\n");
    }
}
void listofactivediactive(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Unable to open file!\n");
        return;
    }
    Membership member;
    printf("active:\n");
    while (fgets(member.name, sizeof(member.name), fp) != NULL) {
        fgets(member.lastname, sizeof(member.lastname), fp);
        fgets(member.id, sizeof(member.id), fp);
        fgets(member.type, sizeof(member.type), fp);
        fgets(member.date, sizeof(member.date), fp);
        fgets(member.password, sizeof(member.password), fp);
        fscanf(fp, "%d\n", &member.isactive);
        fgets(member.membercode, sizeof(member.membercode), fp);
        member.name[strcspn(member.name, "\n")] = '\0';
        member.lastname[strcspn(member.lastname, "\n")] = '\0';
        member.id[strcspn(member.id, "\n")] = '\0';
        member.type[strcspn(member.type, "\n")] = '\0';
        member.date[strcspn(member.date, "\n")] = '\0';
        member.password[strcspn(member.password, "\n")] = '\0';
        member.membercode[strcspn(member.membercode, "\n")] = '\0';
        if (member.isactive) {
            printf("name:%s %s\n", member.name, member.lastname);
            printf("national id: %s\n", member.id);
            printf("membership type: %s\n", member.type);
            printf("date of membership: %s\n", member.date);
            printf("password: %s\n", member.password);
            printf("member Code: %s\n", member.membercode);
        }
    }
    fseek(fp, 0, SEEK_SET);
    printf("Inactive Members:\n");
    while (fgets(member.name, sizeof(member.name), fp) != NULL) {
        fgets(member.lastname, sizeof(member.lastname), fp);
        fgets(member.id, sizeof(member.id), fp);
        fgets(member.type, sizeof(member.type), fp);
        fgets(member.date, sizeof(member.date), fp);
        fgets(member.password, sizeof(member.password), fp);
        fscanf(fp, "%d\n", &member.isactive);
        fgets(member.membercode, sizeof(member.membercode), fp);
        member.name[strcspn(member.name, "\n")] = '\0';
        member.lastname[strcspn(member.lastname, "\n")] = '\0';
        member.id[strcspn(member.id, "\n")] = '\0';
        member.type[strcspn(member.type, "\n")] = '\0';
        member.date[strcspn(member.date, "\n")] = '\0';
        member.password[strcspn(member.password, "\n")] = '\0';
        member.membercode[strcspn(member.membercode, "\n")] = '\0';
        if (!member.isactive) {
            printf("name: %s %s\n", member.name, member.lastname);
            printf("national id: %s\n", member.id);
            printf("membership Type: %s\n", member.type);
            printf("date of membership: %s\n", member.date);
            printf("password: %s\n", member.password);
            printf("member Code: %s\n", member.membercode);
        }
    }
    fclose(fp);
}
void addbook() {
    Book newbook;
    FILE *fp = fopen("books.txt", "a+");
    if (fp == NULL){
        printf("Unable to open file!");
        return ;
    }
    else{
    printf("Enter name of the book:");
    getchar();
    fgets(newbook.name, sizeof(newbook.name), stdin);
    printf("Enter name of the writer:");
    fgets(newbook.writer, sizeof(newbook.writer), stdin);
    printf("Enter year of publication:");
    fgets(newbook.publicationyear, sizeof(newbook.publicationyear), stdin);
    printf("Enter subject of the book:");
    fgets(newbook.subject, sizeof(newbook.subject), stdin);
    fprintf(fp, "%s", newbook.name);
    fprintf(fp, "%s", newbook.writer);
    fprintf(fp, "%s", newbook.publicationyear);
    fprintf(fp, "%s", newbook.subject);
    sprintf(newbook.bookcode, "B%d", rand() % 10000);
    fprintf(fp, "%s\n", newbook.bookcode);
    books[bookcount++] = newbook;
    printf("new book added code(%s)\n", newbook.bookcode);
    }
fclose(fp);
}
void sbooksubject(char *filename, char *searchSubject) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Unable to open file!\n");
        return;
    }
    Book book;
    int found = 0;
    printf("Books related to subject: %s\n", searchSubject);
    while (fgets(book.name, sizeof(book.name), fp) != NULL) {
        fgets(book.writer, sizeof(book.writer), fp);
        fgets(book.publicationyear, sizeof(book.publicationyear), fp);
        fgets(book.subject, sizeof(book.subject), fp);
        fgets(book.bookcode, sizeof(book.bookcode), fp);
        book.name[strcspn(book.name, "\n")] = '\0';
        book.writer[strcspn(book.writer, "\n")] = '\0';
        book.publicationyear[strcspn(book.publicationyear, "\n")] = '\0';
        book.subject[strcspn(book.subject, "\n")] = '\0';
        book.bookcode[strcspn(book.bookcode, "\n")] = '\0';
        if (strcmp(book.subject, searchSubject) == 0) {
            printf("name: %s\n", book.name);
            printf("writer: %s\n", book.writer);
            printf("publication year: %s\n", book.publicationyear);
            printf("subject: %s\n", book.subject);
            printf("book code: %s\n", book.bookcode);
            found = 1;
        }
    }
    if (!found) {
        printf("not found! \n");
    }
    fclose(fp);
}
void booksubject(){
    getchar();
    char subject[50];
    printf("enter subject:");
    fgets(subject, sizeof(subject), stdin);
    subject[strcspn(subject, "\n")] = '\0';
    sbooksubject("books.txt", subject);
}
void searchbook(char *filename, char *code) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Unable to open file!\n");
        return ;
    }
    Book book;
    int found = 0;
    while (!feof(fp)) {
        fgets(book.name, sizeof(book.name), fp);
        fgets(book.writer, sizeof(book.writer), fp);
        fgets(book.publicationyear, sizeof(book.publicationyear), fp);
        fgets(book.subject, sizeof(book.subject), fp);
        fgets(book.bookcode, sizeof(book.bookcode), fp);
        book.name[strcspn(book.name, "\n")] = 0;
        book.writer[strcspn(book.writer, "\n")] = 0;
        book.publicationyear[strcspn(book.publicationyear, "\n")] = 0;
        book.subject[strcspn(book.subject, "\n")] = 0;
        book.bookcode[strcspn(book.bookcode, "\n")] = 0;
        if (strcmp(book.bookcode, code) == 0) {
            printf("book found!\n");
            printf("name:%s\n", book.name);
            printf("writer:%s\n", book.writer);
            printf("publicationyear of publication:%s\n", book.publicationyear);
            printf("subject:%s\n", book.subject);
            printf("book Code:%s\n", book.bookcode);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("book not found.\n");
        return ;
    }
    fclose(fp);
}
void viewbooks() {
    FILE *fp=fopen("listofthebooks_m.txt","r");
    const char *filename="listofthebooks_m.txt";
    int lines=countlines(filename);
    if (lines != -1){
        printf("number of the lines:%d\n",lines);
    }
    int bookcount=0;
    Book *books;
    books=(Book *)malloc(lines/4 *sizeof(Book));
    while(bookcount<=lines/4 &&
          fscanf(fp, "%99[^\n]\n",books[bookcount].name)==1&&
          fscanf(fp, "%19[^\n]\n",books[bookcount].publicationyear)==1&&
          fscanf(fp, "%19[^\n]\n",books[bookcount].writer)==1&&
          fscanf(fp, "%19[^\n]\n",books[bookcount].subject)==1){
        bookcount++;
          }
    for (int i = 0; i< bookcount; i++) {
        printf("%s\n %s\n %s\n %s\n",books[i].name, books[i].writer, books[i].publicationyear, books[i].subject);
    }
    fclose(fp);
}
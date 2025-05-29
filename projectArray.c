#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_USERS 1000
#define MAX_EXPENSES 1000
#define MAX_FAMILIES 100
#define MAX_USERS_IN_FAMILY 4
#define MAX_EXPENSE_CATEGORY_SIZE 15
#define TOTAL_DAYS 10
#define MAX_NAME_LENGTH 100

typedef enum {SUCCESS, FAILURE} statusCode;
typedef enum {false, true} bool;

typedef struct {
    unsigned int date;
    unsigned int month;
    unsigned int year;
} Date;

typedef struct user {
    int user_ID;//ranges from 1 to 1000
    char user_name[100];
    float income;
} user;

typedef struct expense {
    int expense_ID;
    int user_ID;
    char expense_category[MAX_EXPENSE_CATEGORY_SIZE]; // rent, utility, grocery, stationary, leisure;
    float expense_amount;
    Date date_of_expense;
} expense;

typedef struct family {
    int family_ID;
    char family_name[MAX_NAME_LENGTH];
    int total_members;
    int family_members_user_id[MAX_USERS_IN_FAMILY];
    float total_family_income;
    float total_family_expense;
} family;

typedef struct daily_expense{
    Date date;
    float total_expense;
} dailyExpense;

typedef struct category_expense{
    char category_name[15];
    float expense;
} cat_exp;

typedef struct family_expense_cat_name{
    int user_id;
    float expense;
} familyUserExpense;

void initialize_users(user user_array[]) {
    for (int i = 0; i < MAX_USERS; i++) {
        user_array[i].income = 0;
        user_array[i].user_name[0] = '\0';
        user_array[i].user_ID = 0;
    }
}

void initialize_expenses(expense expense_array[]) {
    for (int i = 0; i < MAX_EXPENSES; i++) {
        expense_array[i].date_of_expense.date = 0;
        expense_array[i].date_of_expense.month = 0;
        expense_array[i].date_of_expense.year = 0;
        expense_array[i].expense_amount = 0;
        expense_array[i].expense_category[0] = '\0';
        expense_array[i].expense_ID = 0;
        expense_array[i].user_ID = 0;
    }
}

void initialize_family(family family_array[]) {
    for (int i = 0; i < MAX_FAMILIES; i++) {
        family_array[i].family_ID = 0;
        family_array[i].family_name[0] = '\0';
        family_array[i].total_family_expense = 0;
        family_array[i].total_family_income = 0;
        family_array[i].total_members = 0;
        for (int j = 0; j < MAX_USERS_IN_FAMILY; j++) {
            family_array[i].family_members_user_id[j] = 0;
        }
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int user_count = 0;
static int expense_count = 0;
static int family_count = 0;

void traverseUserArray(user user_array[]) {
    const int id_width = 10;
    const int name_width = 20;
    const int income_width = 15;
    
    printf("+-%-*s-+-%-*s-+-%-*s-+\n",
           id_width, "----------",
           name_width, "--------------------",
           income_width, "---------------");
    
    printf("| %-*s | %-*s | %-*s |\n",
           id_width, "User ID",
           name_width, "User Name",
           income_width, "Income");
    
    printf("+-%-*s-+-%-*s-+-%-*s-+\n",
           id_width, "----------",
           name_width, "--------------------",
           income_width, "---------------");

    for (int i = 0; i < user_count; i++) {
        printf("| %-*d | %-*s | %-*.2f |\n",
               id_width, user_array[i].user_ID,
               name_width, user_array[i].user_name,
               income_width, user_array[i].income);
    }
    
    printf("+-%-*s-+-%-*s-+-%-*s-+\n",
           id_width, "----------",
           name_width, "--------------------",
           income_width, "---------------");
    printf("\n");
}

void traverseExpenseArray(expense expense_array[]) {
    const int user_id_width = 10;
    const int expense_id_width = 12;
    const int amount_width = 15;
    const int category_width = 15;
    const int date_width = 12;
    
    printf("+-%-*s-+-%-*s-+-%-*s-+-%-*s-+-%-*s-+\n",
           user_id_width, "----------",
           expense_id_width, "------------",
           amount_width, "---------------",
           category_width, "---------------",
           date_width, "------------");
    
    printf("| %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           user_id_width, "User ID",
           expense_id_width, "Expense ID",
           amount_width, "Amount",
           category_width, "Category",
           date_width, "Date");
    
    printf("+-%-*s-+-%-*s-+-%-*s-+-%-*s-+-%-*s-+\n",
           user_id_width, "----------",
           expense_id_width, "------------",
           amount_width, "---------------",
           category_width, "---------------",
           date_width, "------------");

    for (int i = 0; i < expense_count; i++) {
        printf("| %-*d | %-*d | %-*.2f | %-*s | %02u-%02u-%04u |\n",
               user_id_width, expense_array[i].user_ID,
               expense_id_width, expense_array[i].expense_ID,
               amount_width, expense_array[i].expense_amount,
               category_width, expense_array[i].expense_category,
               expense_array[i].date_of_expense.date,
               expense_array[i].date_of_expense.month,
               expense_array[i].date_of_expense.year);
    }
    
    printf("+-%-*s-+-%-*s-+-%-*s-+-%-*s-+-%-*s-+\n",
           user_id_width, "----------",
           expense_id_width, "------------",
           amount_width, "---------------",
           category_width, "---------------",
           date_width, "------------");
    printf("\n");
}

void traverseFamilyArray(family family_array[]) {
    const int id_width = 10;
    const int name_width = 15;
    const int users_width = 20;
    const int expense_width = 15;
    const int income_width = 15;
    
    printf("+-%-*s-+-%-*s-+-%-*s-+-%-*s-+-%-*s-+\n",
           id_width, "----------",
           name_width, "---------------",
           users_width, "--------------------",
           expense_width, "---------------",
           income_width, "---------------");
    
    printf("| %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           id_width, "Family ID",
           name_width, "Family Name",
           users_width, "User IDs",
           expense_width, "Total Expense",
           income_width, "Total Income");
    
    printf("+-%-*s-+-%-*s-+-%-*s-+-%-*s-+-%-*s-+\n",
           id_width, "----------",
           name_width, "---------------",
           users_width, "--------------------",
           expense_width, "---------------",
           income_width, "---------------");

    for (int i = 0; i < family_count; i++) {
        printf("| %-*d | %-*s | ",
               id_width, family_array[i].family_ID,
               name_width, family_array[i].family_name);
        
        char user_ids[100] = "(";
        int pos = 1;
        
        for (int j = 0; j < family_array[i].total_members; j++) {
            if (j > 0) {
                pos += sprintf(user_ids + pos, " %d", family_array[i].family_members_user_id[j]);
            } else {
                pos += sprintf(user_ids + pos, "%d", family_array[i].family_members_user_id[j]);
            }
        }
        strcat(user_ids, ")");
        printf("%-*s | ", users_width, user_ids);
        
        printf("%-*.2f | %-*.2f |\n",
               expense_width, family_array[i].total_family_expense,
               income_width, family_array[i].total_family_income);
    }
    
    printf("+-%-*s-+-%-*s-+-%-*s-+-%-*s-+-%-*s-+\n",
           id_width, "----------",
           name_width, "---------------",
           users_width, "--------------------",
           expense_width, "---------------",
           income_width, "---------------");
    printf("\n");
}

bool does_user_exist(const user user_array[], int user_id) {
    bool found = false;
    for (int i = 0; i < user_count && !found; i++) {
        if (user_array[i].user_ID == user_id) {
            found = true;
        }
    }
    return found;
}

bool does_expense_exist(const expense expense_array[], int expense_id) {
    bool found = false;
    for (int i = 0; i < expense_count && !found; i++) {
        if (expense_array[i].expense_ID == expense_id) {
            found = true;
        }
    }
    return found;
}

bool does_family_exist(const family family_array[], int family_id) {
    bool found = false;
    for (int i = 0; i < family_count && !found; i++) {
        if (family_array[i].family_ID == family_id) {
            found = true;
        }
    }
    return found;
}

int get_user_id_index(const user user_array[], int user_id) {
    int ans = -1;
    for (int i = 0; i < user_count && ans == -1; i++) {
        if (user_array[i].user_ID == user_id) {
            ans = i;
        }
    }
    return ans;
}

int get_expense_id_index(const expense expense_array[], int expense_id) {
    int ans = -1;
    for (int i = 0; i < expense_count && ans == -1; i++) {
        if (expense_array[i].expense_ID == expense_id) {
            ans = i;
        }
    }
    return ans;
}

int get_family_id_index(const family family_array[], int family_id) {
    int ans = -1;
    for (int i = 0; i < family_count && ans == -1; i++) {
        if (family_array[i].family_ID == family_id) {
            ans = i;
        }
    }
    return ans;
}

//users
void addUserToFamily(family family_Array[], int user_id, float income) {
    int fam_id;
    printf("enter family id to which you want to add this user : ");
    scanf("%d", &fam_id);
    bool exist = does_family_exist(family_Array, fam_id);
    if (exist) {
        int index = get_family_id_index(family_Array, fam_id);
        if (family_Array[index].total_members == 4) {
            printf("Max number of users are in family\n");
        } else {
            family_Array[index].total_members  += 1;
            int i = 0;
            while (family_Array[index].family_members_user_id[i]  != 0) {
                i++;
            }
            family_Array[index].family_members_user_id[i] = user_id;
            family_Array[index].total_family_income += income;
        }
    } else {
        printf("family id %d does not exist\n");
    }
}

statusCode AddUser(user user_array[], family family_array[]) {
    statusCode sc = SUCCESS;
    if (user_count >= MAX_USERS || user_count < 0) {
        printf("User list is out of bounds.\n");
        sc = FAILURE;
    } else {
        printf("enter the details\n");
        int user_id;
        float income;
        char name[100];
        printf("enter user_id : ");
        scanf("%d",&user_id);
        while (user_id > MAX_USERS || user_id < 1) {
            printf("wrong input. user id cannot exceed 1000 and cannot be less than 1.\n");
            printf("enter user_id : ");
            scanf("%d",&user_id);
        }
        bool does_exist = does_user_exist(user_array, user_id);
        if (does_exist) {
            printf("user id %d already exists.\n", user_id);
            sc = FAILURE;
        } else {
            printf("enter income of user : ");
            scanf("%f", &income);
            while (income < 0) {
                printf("wrong input. Income is never negative.\n");
                printf("enter income of user : ");
                scanf("%f", &income);
            }
            printf("enter name of individual user : ");
            scanf("%s", name);
            while (name[0] == '\0') {
                printf("wrong input. please enter your name.\n");
                printf("enter name of individual user : ");
                fgets(name, 100, stdin);
            }
            int i = 0;
            while (i < user_count && user_array[i].user_ID < user_id) {
                i++;
            }
            for (int j = user_count; j > i; j--) {
                user_array[j] = user_array[j - 1];
            }
            user_array[i].user_ID = user_id; 
            user_array[i].income = income;
            strcpy(user_array[i].user_name , name);
            user_count++;
            printf("user added successfully.\n");
            sc = SUCCESS;
            char c;
            printf("do you want to add this user to a family? enter y to add, n to continue : ");
            do {
                scanf("%c", &c);
            } while (c != 'y' && c != 'n' && c != 'Y' && c != 'N');
            if (c == 'y' || c == 'Y') {
                addUserToFamily(family_array, user_id, income);
            }
        }
    }
    return sc;
}

void swap_user(user user_array[], int start, int pivot) {
    if(start != pivot) {
        user temp = user_array[start];
        user_array[start] = user_array[pivot];
        user_array[pivot] = temp;
    }
}

int partition_array_of_user(user user_array[], int start, int end) {
    int x = user_array[start].user_ID;
    int i = start + 1;
    int j = end;
    while (i <= j) {
        while (i <= end && user_array[i].user_ID <= x) {
            i++;
        }
        while (j >= start && user_array[j].user_ID > x) {
            j--;
        }
        if(i < j) {
            swap_user(user_array, i, j);
        }
    }
    swap_user(user_array, start, j);
    return j;
}

void sort_users_using_user_id(user user_array[], int start, int end) {
    if(start < end) {
        int pivot = partition_array_of_user(user_array, start, end);
        sort_users_using_user_id(user_array, start, pivot - 1);
        sort_users_using_user_id(user_array, pivot + 1, end);
    }
}

//expenses
void capitalize(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
    }
}

statusCode AddExpense(expense expense_array[], user user_array[]) {
    statusCode sc = SUCCESS;
    if (expense_count >= MAX_EXPENSES) {
        printf("expenses limit reached.\n");
        sc = FAILURE;
    } else {
        int user_id, expense_id;
        float expense_amount;
        char expense_category[MAX_EXPENSE_CATEGORY_SIZE];
        Date date;
        printf("Enter expense ID for expense: ");
        scanf("%d", &expense_id);
        while(expense_id > 1000 || expense_id < 1){
            printf("wrong input. expense id cannot exceed 1000 and cannot be less than 1.\n");
            printf("enter expense_id : ");
            scanf("%d",&expense_id);
        }
        bool does_exist = does_expense_exist(expense_array, expense_id);
        if (does_exist) {
            printf("expense id already exists.\n");
            sc = FAILURE;
        } else {
            printf("Enter user ID for expense: ");
            scanf("%d", &user_id);
            bool is_exist = does_user_exist(user_array, user_id);
            if (!is_exist) {
                sc = FAILURE;
                printf("given user doesnot exist.\n");
            } else {
                printf("Enter expense amount: ");
                scanf("%f", &expense_amount);
                while(expense_amount < 0){
                    printf("wrong input. expense can never be negative.\n");
                    printf("enter income again : ");
                    scanf("%f", &expense_amount);
                }
                printf("Enter expense category: ");
                scanf("%14s", expense_category);
                while(strcmp(expense_category, "rent") != 0 && strcmp(expense_category, "utility") != 0 && strcmp(expense_category, "stationary") != 0 && strcmp(expense_category, "grocery") != 0 && strcmp(expense_category, "leisure") != 0){
                    printf("enter only rent or utility or stationary or grocery or leisure\n");
                    printf("Enter expense category again : ");
                    scanf("%14s", expense_category);         
                }
                capitalize(expense_category);
                printf("Enter date of expense (DD MM YYYY): ");
                scanf("%u", &date.date);
                scanf("%u", &date.month);
                scanf("%u", &date.year);
                while (date.date > 10 || date.date <= 0) {
                    printf("enter only 1 - 10\n");
                    printf("enter date again: ");
                    scanf("%u", &date.date);
                }
                while (date.month > 12 || date.month <= 0) {
                    printf("enter only 1 - 12\n");
                    printf("enter month again: ");
                    scanf("%u", &date.month);
                }
                while (date.year > 2025 || date.year <= 0) {
                    printf("enter only 1 - 12\n");
                    printf("enter year again: ");
                    scanf("%u", &date.year);
                }
                int i = 0;
                while (i < expense_count && expense_array[i].user_ID < user_id) {
                    i++;
                }
                if (i < expense_count && expense_array[i].user_ID == user_id) {
                    while (i < expense_count && expense_array[i].expense_ID < expense_id) {
                        i++;
                    }
                }
                for (int j = expense_count; j > i; j--) {
                    expense_array[j] = expense_array[j - 1];
                }
                expense_array[i].date_of_expense = date;
                expense_array[i].expense_amount = expense_amount;
                strcpy(expense_array[i].expense_category, expense_category);
                expense_array[i].expense_ID = expense_id;
                expense_array[i].user_ID = user_id;
                expense_count++;
            }
        }
    }
    return sc;
}

void merge_expenses(expense expense_array[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    expense L[n1], R[n2];
    
    for (i = 0; i < n1; i++)
        L[i] = expense_array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = expense_array[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    
    while (i < n1 && j < n2) {
        if (L[i].user_ID < R[j].user_ID) {
            expense_array[k] = L[i];
            i++;
        } else if (L[i].user_ID > R[j].user_ID) {
            expense_array[k] = R[j];
            j++;
        } else {
            if (L[i].expense_ID <= R[j].expense_ID) {
                expense_array[k] = L[i];
                i++;
            } else {
                expense_array[k] = R[j];
                j++;
            }
        }
        k++;
    }
    while (i < n1) {
        expense_array[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        expense_array[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort_expenses(expense expense_array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_expenses(expense_array, left, mid);
        merge_sort_expenses(expense_array, mid + 1, right);
        merge_expenses(expense_array, left, mid, right);
    }
}

//family
bool checkifUserInAnotherFamily(family family_array[], int user_id) {   
    bool found = false;
    int i = 0;
    while(i < family_count && !found) {
        int n = family_array[i].total_members;
        for(int j = 0 ; j < n && !found; j++) {
            if(family_array[i].family_members_user_id[j] == user_id) {
                found = true;
            }
        }
        i++;
    }
    return found;
}

float calculate_monthly_expense_of_family(family fam, expense expense_array[]){
    float sum = 0;
    int n = fam.total_members;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < expense_count; j++){
            if(expense_array[j].user_ID == fam.family_members_user_id[i]){
                sum += expense_array[j].expense_amount;
            }
        }
    }
    return sum;
}

float calculate_monthly_income_of_family(family fam, user user_array[]){
    float sum = 0;
    int n = fam.total_members;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < user_count; j++){
            if(user_array[j].user_ID == fam.family_members_user_id[i]){
                sum += user_array[j].income;
            }
        }
    }
    return sum;
}

statusCode CreateFamily(family family_array[], user user_array[], expense expense_array[]) {
    statusCode sc = SUCCESS;
    if (family_count >= MAX_FAMILIES) {
        printf("families count is out of bounds.\n");
        sc = FAILURE;
    } else {
        int family_id;
        int total_members; 
        printf("Enter family id: ");
        scanf("%d", &family_id);
        while (family_id > 100 || family_id < 1) {
            printf("wrong input. family id cannot exceed 100 and cannot be less than 1.\n");
            printf("enter family id : ");
            scanf("%d",&family_id);
        }
        bool does_exist = does_family_exist(family_array, family_id);
        if (does_exist) {
            printf("family with id %d exists already.\n", family_id);
        } else {
            printf("Enter total members in the family: ");
            scanf("%d", &total_members);
            while (total_members > 4 || total_members < 1) {
                printf("wrong input. total members should be between 1 and 4.\n");
                printf("enter total members again :");
                scanf("%d", &total_members);
            }
            int family_user_id[total_members];
            bool can_continue = true;
            for (int i = 0; i < total_members && can_continue; i++) {
                printf("Enter user ID of family member %d: ", i + 1);
                scanf("%d", &family_user_id[i]);
                bool user_exists = does_user_exist(user_array, family_user_id[i]);
                if(user_exists) {
                    bool user_in_other_family = checkifUserInAnotherFamily(family_array, family_user_id[i]);
                    if(user_in_other_family) {
                        printf("User %d exists in another family, Cant add user to this family.\n",family_user_id[i]);
                        can_continue = false;
                    } else {
                        can_continue = true;
                    }
                } else {
                    printf("User %d doesnt exist, cant add user to the family.\n", family_user_id[i]);
                    can_continue = false;
                }
            }
            if(can_continue) {
                char family_name[25]; 
                printf("Enter family name: ");
                fgets(family_name, sizeof(family_name), stdin);
                family_name[strcspn(family_name, "\n")] = 0;

                while (family_name[0] == '\0') {
                    printf("Wrong input. Please enter a valid family name.\n");
                    printf("Enter family name: ");
                    fgets(family_name, sizeof(family_name), stdin);
                    family_name[strcspn(family_name, "\n")] = 0;
                }
                int i = 0;
                while (i < family_count && family_array[i].family_ID < family_id) {
                    i++;
                }
                for (int j = family_count; j > i; j--) {
                    family_array[j] = family_array[j - 1];
                }
                family_array[i].family_ID = family_id;
                strcpy(family_array[i].family_name, family_name); 
                family_array[i].total_members = total_members;
                for (int j = 0; j < total_members; j++) {
                    family_array[i].family_members_user_id[j] = family_user_id[j];
                }
                family_array[i].total_family_expense = calculate_monthly_expense_of_family(family_array[i], expense_array);
                family_array[i].total_family_income = calculate_monthly_income_of_family(family_array[i], user_array);
                family_count++;
            } else {
                sc = FAILURE;
                printf("operation failed.\n");
            }
        }
    }
    return sc;
}

void swap_family(family family_array[], int start, int pivot) {
    if(start != pivot) {
        family temp = family_array[start];
        family_array[start] = family_array[pivot];
        family_array[pivot] = temp;
    }
}

int partition_array_of_family(family family_array[], int start, int end) {
    int x = family_array[start].family_ID;
    int i = start + 1;
    int j = end;
    while (i <= j) {
        while (i <= end && family_array[i].family_ID <= x) {
            i++;
        }
        while (j >= start && family_array[j].family_ID > x) {
            j--;
        }
        if(i < j) {
            swap_family(family_array, i, j);
        }
    }
    swap_family(family_array, start, j);
    return j;
}

void sort_families(family family_array[], int start, int end) {
    if(start < end) {
        int pivot = partition_array_of_family(family_array, start, end);
        sort_families(family_array, start, pivot - 1);
        sort_families(family_array, pivot + 1, end);
    }
}

void updateFamilyUsersIncome (family family_array[], user user_i, user user_array[]) {
    int i = 0;
    int uid = user_i.user_ID;
    while (i < user_count) {
        int size = family_array[i].total_members;
        bool found = false;
        for (int j = 0; j < size && !found; j++) {
            if (family_array[i].family_members_user_id[j] == uid) {
                found = true;
            }
        }
        if (found) {
            family_array[i].total_family_income = calculate_monthly_income_of_family(family_array[i], user_array);
        }
        i++;
    }
    traverseFamilyArray(family_array);
}

statusCode updateUserDetails (user user_array[], family family_array[]) {
    statusCode sc = SUCCESS;
    if (user_count <= 0) {
        printf("user list is empty\n");
        sc = FAILURE;
    } else {
        int user_id;
        printf("enter which user id you want to update :");
        scanf("%d", &user_id);
        bool exist = does_user_exist(user_array, user_id);
        if (!exist) {
            printf("user not found\n");
            sc = FAILURE;
        } else {
            printf("1. enter 1 to change user name.\n");
            printf("2. enter 2 to update user income.\n");
            printf("3. enter 3 to change both user name and user income.\n");
            int option;
            printf("enter your option :");
            scanf("%d", &option);
            int i = get_user_id_index(user_array, user_id);
            if (option == 1) {
                char userName[100];
                printf("enter new user name :");
                scanf("%99s", userName);
                strcpy(user_array[i].user_name, userName);
            } else if (option == 2) {
                float income;
                printf("enter your new income :");
                scanf("%f", &income);
                user_array[i].income = income;
            } else if (option == 3) {
                char userName[100];
                float income;
                printf("enter new user name :");
                scanf("%99s", userName);
                printf("enter your new income :");
                scanf("%f", &income);
                user_array[i].income = income;
                strcpy(user_array[i].user_name, userName);
            } else {
                printf("you have entered a invalid option\n");
                sc = FAILURE;
            }
            if (option == 2 || option == 3) {
                if (family_count <= 0) {
                    printf("family list is empty");
                    sc = FAILURE;
                } else {
                    updateFamilyUsersIncome(family_array, user_array[i], user_array);
                }
            }
            printf("user %d details updated successfully.\n", user_id);
        }
    }
    traverseUserArray(user_array);
    return sc;
}

statusCode updateFamilyDetails (family family_array[], user user_array[], expense expense_array[], int *f_id) {
    statusCode sc = SUCCESS;
    if (family_count <= 0) {
        printf("family list is empty\n");
        sc = FAILURE;
    } else {
        int famId;
        printf("enter family id to update :");
        scanf("%d", &famId);
        bool exist = does_family_exist(family_array, famId);
        if (!exist) {
            printf("family id %d doesnot exist.\n", famId);
            sc = FAILURE;
        } else {
            *f_id = famId;
            char famName[100];
            printf("1. enter 1 to change family name :\n");
            printf("2. enter 2 to update user list.\n");
            printf("3. enter 3 to update family expense.\n");
            printf("4. enter 4 to update family income.\n");

            int option;
            printf("enter your option :");
            scanf("%d", &option);
            int i = get_family_id_index(family_array, famId);
            switch (option) {
                case 1: {
                    printf("enter new family name :");
                    clear_input_buffer();
                    fgets(famName, sizeof(famName), stdin);
                    famName[strcspn(famName, "\n")] = 0;
                    strcpy(family_array[i].family_name, famName);
                    break;
                }
                case 2: {
                    printf("enter 1 : to add a user to family.\n");
                    printf("enter 2 : update existing user ids.\n");
                    int op;
                    printf("enter your option : ");
                    scanf("%d", &op);
                    clear_input_buffer();
                    switch (op) {
                        case 1 : {
                            if (family_array[i].total_members == 4) {
                                printf("Max number of users are in family\n");
                                sc = FAILURE;
                            } else {
                                printf("enter the details\n");
                                int user_id;
                                printf("enter user_id : ");
                                scanf("%d",&user_id);
                                while (user_id > MAX_USERS || user_id < 1) {
                                    printf("wrong input. user id cannot exceed 1000 and cannot be less than 1.\n");
                                    printf("enter user_id : ");
                                    scanf("%d",&user_id);
                                }
                                bool does_exist = does_user_exist(user_array, user_id);
                                if (!does_exist) {
                                    printf("user id %d already exists.\n", user_id);
                                    sc = FAILURE;
                                } else {
                                    family_array[i].total_members += 1;
                                    int j = 0;
                                    while (family_array[i].family_members_user_id[j]  != 0) {
                                        j++;
                                    }
                                    family_array[i].family_members_user_id[j] = user_id;
                                    float income = user_array[get_user_id_index(user_array, user_id)].income;
                                    family_array[i].total_family_income += income;
                                    float expenses = 0;
                                    for (int k = 0; k < expense_count; k++) {
                                        if (expense_array[k].user_ID == user_id) expenses += expense_array[k].expense_amount;
                                    }
                                    family_array[i].total_family_expense += expenses;
                                }
                            }
                            break;
                        }
                        case 2 : {
                            printf("enter which user id of family you want to change : ");
                            int user_id;
                            scanf("%d", &user_id);
                            int ind = -1;
                            for (int j = 0; j < family_array[i].total_members; j++) {
                                if (user_id == family_array[i].family_members_user_id[j]) ind = j;
                            }
                            if (ind != -1) {
                                printf("enter new user id : ");
                                int new_user_id;
                                scanf("%d", &new_user_id);
                                int k = get_user_id_index(user_array, new_user_id);
                                if (k != -1) {
                                    bool check = checkifUserInAnotherFamily(family_array, new_user_id);
                                    if (!check) {
                                        family_array[i].family_members_user_id[ind] = new_user_id;
                                        family_array[i].total_family_income += user_array[k].income;
                                        int r = get_user_id_index(user_array, user_id);
                                        family_array[i].total_family_income -= user_array[r].income;

                                        float k_expenses = 0;
                                        float r_expenses = 0;
                                        for (int e = 0; e < expense_count; e++) {
                                            if (expense_array[e].user_ID == user_id) r_expenses += expense_array[e].expense_amount;
                                            if (expense_array[e].user_ID == new_user_id) k_expenses += expense_array[e].expense_amount;
                                        }
                                        family_array[i].total_family_expense += k_expenses;
                                        family_array[i].total_family_expense -= r_expenses;
                                    } else {
                                        printf("user exists in other family.\n");
                                    }
                                } else {
                                    printf("user not found.\n");
                                }
                            }
                            break;
                        }
                        default : {
                            printf("wrong input.\n");
                            break;
                        }
                    }
                    break;
                }
                case 3: {
                    family_array[i].total_family_expense = calculate_monthly_expense_of_family(family_array[i], expense_array);
                    break;
                }
                case 4: {
                    family_array[i].total_family_income = calculate_monthly_income_of_family(family_array[i], user_array);
                    break;
                }
                default: {
                    printf("you entered a wrong number\n");
                    sc = FAILURE;
                    break;
                }
            }
            traverseUserArray(user_array);
            traverseFamilyArray(family_array);
        }
    }
    return sc;
}

void deleteUserBlock(user user_array[], int i) {
    if (i < user_count && i >= 0) {
        for (int j = i; j < user_count - 1; j++) {
            user_array[j] = user_array[j + 1];
        }
        user_count--;
    }
}

void deleteExpenseBlock(expense expense_array[], int i) {
    if (i < expense_count && i >= 0) {
        for (int j = i; j < expense_count - 1; j++) {
            expense_array[j] = expense_array[j + 1];
        }
        expense_count--;
    }
}

void deleteFamilyBlock(family family_array[], int i) {
    if (i < family_count && i >= 0) {
        for (int j = i; j < family_count - 1; j++) {
            family_array[j] = family_array[j + 1];
        }
        family_count--;
    }
}

void deleteUserFromFamily (family family_array[], user user_array[], expense expense_array[], int i, int user_id, float income) {
    bool found = false;
    int size = family_array[i].total_members;
    int j = 0;
    while (j < size && !found) {
        if (family_array[i].family_members_user_id[j] != user_id) {
            j++;
        } else {
            found = true;
        }
    }
    if (found) {
        if (size == 1) {
            deleteFamilyBlock(family_array, i);
        } else {
            family_array[i].total_family_income -= income;
            family_array[i].family_members_user_id[j] = 0;
            int k = j;
            while (k < 3) { 
                family_array[i].family_members_user_id[k] = family_array[i].family_members_user_id[k + 1];
                k++;
            }
            family_array[i].family_members_user_id[3] = 0;
            family_array[i].total_members -= 1;
            float income = user_array[get_user_id_index(user_array, user_id)].income;
            family_array[i].total_family_income -= income;
            float expenses = 0;
            for (int k = 0; k < expense_count; k++) {
                if (expense_array[k].user_ID == user_id) expenses += expense_array[k].expense_amount;
            }
            family_array[i].total_family_expense -= expenses;
        }  
    }
}

void removeUserExpense(expense expense_array[], int user_id) {
    int i = 0;
    while (i < expense_count && expense_array[i].user_ID != user_id) {
        i++;
    }
    while (i < expense_count && expense_array[i].user_ID == user_id) {
        deleteExpenseBlock(expense_array, i);
    }
}

statusCode deleteUser (user user_array[], family family_array[], expense expense_array[]) {
    statusCode sc = SUCCESS;
    if (user_count <= 0) {
        printf("user list is empty\n");
        sc = FAILURE;
    } else {
        int user_id;
        printf("enter user id to delete :");
        scanf("%d", &user_id);
        bool exist = does_user_exist(user_array, user_id);
        if (!exist) {
            printf("user not found\n");
            sc = FAILURE;
        } else {
            int i = get_user_id_index(user_array, user_id);
            float income = user_array[i].income;
            deleteUserBlock(user_array, i);
            printf("user %d deleted successfully.\n", user_id);
            if (family_count <= 0) {
                printf("family list is empty\n");
                sc = FAILURE;
            } else {
                int j = -1;
                for (int l = 0; l < family_count && j == -1; l++) {
                    int n = family_array[l].total_members;
                    for (int k = 0; k < n && j == -1; k++) {
                        if (family_array[l].family_members_user_id[k] == user_id) j = l;
                    }
                }
                deleteUserFromFamily(family_array, user_array, expense_array, j, user_id, income);
            }
            if (expense_count <= 0) {
                printf("expense list is empty.\n");
                sc = FAILURE;
            } else {
                removeUserExpense(expense_array, user_id);
            }
        }
    }
    traverseUserArray(user_array);
    traverseExpenseArray(expense_array);
    traverseFamilyArray(family_array);
    return sc;
}

void deleteFamilyUsers (user user_array[], int family_user_array[], int total_members) {
    for (int j = 0; j < total_members; j++) {
        for (int i = 0; i < user_count; i++) {
            int index = get_user_id_index(user_array, family_user_array[j]);
            if (index != -1) {
                deleteUserBlock(user_array, index);
            }
        }
    }
}

void Remove_Family_User_Expenses(expense expense_array[], int family_members_user_id[], int total_members) {
    for(int i = 0; i < total_members; i++) {
        removeUserExpense(expense_array, family_members_user_id[i]);
    }
}

//users are not common to families, belongs to only one family one user
statusCode deleteFamily (family family_array[], user user_array[], expense expense_array[]) {
    statusCode sc = SUCCESS;
    if (family_count <= 0) {
        printf("family list is empty\n");
        sc = FAILURE;
    } else {
        int fam_id;
        printf("enter family id to delete :");
        scanf("%d", &fam_id);
        bool exist = does_family_exist(family_array, fam_id);
        if (!exist) {
            printf("family id doesnot exist\n");
            sc = FAILURE;
        } else {
            int i = get_family_id_index(family_array, fam_id);
            if (user_count <= 0) {
                sc = FAILURE;
            } else {
                deleteFamilyUsers(user_array, family_array[i].family_members_user_id, family_array[i].total_members);
            }
            if (expense_count <= 0) {
                printf("expense list is empty.\n");
                sc = FAILURE; 
            } else {
                Remove_Family_User_Expenses(expense_array, family_array[i].family_members_user_id, family_array[i].total_members);
            }
            deleteFamilyBlock(family_array, i);
        }
    }
    traverseUserArray(user_array);
    traverseExpenseArray(expense_array);
    traverseFamilyArray(family_array);
    return sc;
}

void updateFamilyExpense (family family_array[], int user_id, float old_expense_amount, float new_expense_amount) {
    int i = 0;
    bool found = false;
    while (i < family_count && !found) {
        int size = family_array[i].total_members;
        int j = 0;
        while (!found && j < size) {
            if (family_array[i].family_members_user_id[j] == user_id) {
                found = true;
            } else {
                j++;
            }
        }
        if (found) {
            family_array[i].total_family_expense += (new_expense_amount - old_expense_amount); 
        }
        i++;
    }
}

statusCode updateExpense (expense expense_array[], family family_array[]) {
    statusCode sc = SUCCESS;
    if (expense_count <= 0) {
        printf("expense list is empty\n");
        sc = FAILURE;
    } else {
        int expense_id;
        printf("enter expense id to update :");
        scanf("%d", &expense_id);
        bool exist = does_expense_exist(expense_array, expense_id);
        if (!exist) {
            printf("expense id doesnot exist\n");
            sc = FAILURE;
        } else {
            printf("1. enter 1 to update expense category.\n");
            printf("2. enter 2 to update expense amount.\n");
            printf("3. enter 3 to update date of expense.\n");
            printf("4. enter 4 to do update all.\n");
            int option;
            printf("enter your option :");
            scanf("%d", &option);
            float old_expense_amount;
            int index = get_expense_id_index(expense_array, expense_id);
            switch (option) {
                case 1 : {
                    char expense_category[15];
                    printf("enter expense category :");
                    scanf("%14s", expense_category);
                    while(strcmp(expense_category, "rent") != 0 && strcmp(expense_category, "utility") != 0 && strcmp(expense_category, "stationary") != 0 && strcmp(expense_category, "grocery") != 0 && strcmp(expense_category, "leisure") != 0){
                        printf("enter only rent or utility or stationary or grocery or leisure\n");
                        printf("Enter expense category again : ");
                        scanf("%14s", expense_category);         
                    }
                    capitalize(expense_category);
                    strcpy(expense_array[index].expense_category, expense_category);
                    printf("exepnse %d updated successfully.\n", expense_id);
                    break;
                }
                case 2 : {
                    float expense_amount;
                    printf("enter expense amount :");
                    scanf("%f", &expense_amount);
                    while (expense_amount <= 0) {
                        printf("Invalid input. Enter only positive values : \n");
                        scanf("%f", &expense_amount);
                    }
                    old_expense_amount = expense_array[index].expense_amount;
                    expense_array[index].expense_amount = expense_amount;
                    printf("exepnse %d updated successfully.\n", expense_id);
                    break;
                }
                case 3 : {
                    Date d;
                    printf("enter date :");
                    scanf("%u", &d.date);
                    while (d.date > 10 && d.date <= 0) {
                        printf("enter only 1 - 10");
                        scanf("%u", &d.date);
                    }
                    printf("enter month :");
                    scanf("%u", &d.month);
                    while (d.month > 12 && d.month <= 0) {
                        printf("enter only 1 - 12");
                        scanf("%u", &d.month);
                    }
                    printf("enter year :");
                    scanf("%u", &d.year);
                    while (d.year <= 0 || d.year > 2025) {
                        printf("enter only 1 - 2025 : ");
                        scanf("%u", &d.year);
                    }
                    expense_array[index].date_of_expense = d;
                    printf("exepnse %d updated successfully.\n", expense_id);
                    break;
                }
                case 4 : {
                    char* expense_category;
                    printf("enter expense category :");
                    scanf("%s", expense_category);
                    while(strcmp(expense_category, "rent") != 0 && strcmp(expense_category, "utility") != 0 && strcmp(expense_category, "stationary") != 0 && strcmp(expense_category, "grocery") != 0 && strcmp(expense_category, "leisure") != 0){
                        printf("enter only rent or utility or stationary or grocery or leisure\n");
                        printf("Enter expense category again : ");
                        scanf("%14s", expense_category);         
                    }
                    capitalize(expense_category);
                    strcpy(expense_array[index].expense_category, expense_category);
                
                    float expense_amount;
                    printf("enter expense amount :");
                    scanf("%f", &expense_amount);
                    old_expense_amount = expense_array[index].expense_amount;
                    expense_array[index].expense_amount = expense_amount;

                    Date d;
                    printf("enter date :");
                    scanf("%u", &d.date);
                    while (d.date > 10 && d.date <= 0) {
                        printf("enter only 1 - 10");
                        scanf("%u", &d.date);
                    }
                    printf("enter month :");
                    scanf("%u", &d.month);
                    while (d.month > 12 && d.month <= 0) {
                        printf("enter only 1 - 12");
                        scanf("%u", &d.month);
                    }
                    printf("enter year :");
                    scanf("%u", &d.year);
                    while (d.year <= 0 || d.year > 2025) {
                        printf("enter only 1 - 2025 : ");
                        scanf("%u", &d.year);
                    }
                    expense_array[index].date_of_expense = d;
                    printf("exepnse %d updated successfully.\n", expense_id);
                    break;
                }
                default : {
                    printf("you entered a wrong number.\n");
                    sc = FAILURE;
                    break;
                }
            }
            if (option == 2 || option == 4) {
                if (family_count <= 0) {
                    printf("family list is empty\n");
                    sc = FAILURE;
                } else {
                    updateFamilyExpense(family_array, expense_array[index].user_ID, old_expense_amount, expense_array[index].expense_amount);
                }
            }
        }
    }
    traverseExpenseArray(expense_array);
    traverseFamilyArray(family_array);
    return sc;
}

statusCode deleteExpense (expense expense_array[], family family_array[]) {
    statusCode sc = SUCCESS;
    if (expense_count <= 0) {
        printf("expense list is empty\n");
        sc = FAILURE;
    } else {
        int expense_id;
        printf("enter expense id to delete :");
        scanf("%d", &expense_id);
        bool exist = does_expense_exist(expense_array, expense_id);
        if (!exist) {
            printf("expense id doesnot exist\n");
            sc = FAILURE;
        } else {
            int index = get_expense_id_index(expense_array, expense_id);
            if (family_count <= 0) {
                printf("family list is empty\n");
                sc = FAILURE;
            } else {
                updateFamilyExpense(family_array, expense_array[index].user_ID, expense_array[index].expense_amount, 0); 
            }
            deleteExpenseBlock(expense_array, index);
        }
    }
    traverseExpenseArray(expense_array);
    traverseFamilyArray(family_array);
    return sc;
}

statusCode Get_Total_Expense (family family_array[]) {
    int fam_id;
    statusCode sc = SUCCESS;
    printf("enter your family id :");
    scanf("%d", &fam_id);
    if (!does_family_exist(family_array, fam_id)) {
        printf("family id doesnot exist.\n");
        sc = FAILURE;
    } else {
        int index = get_family_id_index(family_array, fam_id);
        printf("total family expense : %f.\n", family_array[index].total_family_expense);
        if (family_array[index].total_family_expense <= family_array[index].total_family_income) {
            printf("family expense per month is within the range of income.\n");
        } else {
            printf("family expense per month surpasses your income by %.2f.\n", family_array[index].total_family_expense - family_array[index].total_family_income);
        }
        printf("if you want to check any particular expense enter 1.\n if not enter any number other than 1.\n");
        int option;
        printf("enter your option :");
        scanf("%d", &option);
        if (option == 1) {
            float expense_amount;
            printf("enter you expense amount :");
            scanf("%f", &expense_amount);
            if (family_array[index].total_family_income >= expense_amount) {
                printf("current expense is within the range of income.\n");
            } else {
                printf("current expense surpasses your income by %.2f.\n", expense_amount - family_array[index].total_family_income);
            }
        }
    }
    return sc;
}

statusCode get_categorical_expense(family family_array[], expense expense_array[]) {
    statusCode sc = SUCCESS;
    int family_ID;
    printf("enter family id :");
    scanf("%d", &family_ID);
    float total_expense = 0;
    int index = get_family_id_index(family_array, family_ID);
    if (index == -1) {
        printf("family %d not found.\n", family_ID);
        sc = FAILURE;
    } else {
        char category_name[15];
        printf("enter category name :");
        scanf("%14s", category_name);
        while(strcmp(category_name, "rent") != 0 && strcmp(category_name, "utility") != 0 && strcmp(category_name, "stationary") != 0 && strcmp(category_name, "grocery") != 0 && strcmp(category_name, "leisure") != 0){
            printf("enter only rent or utility or stationary or grocery or leisure\n");
            printf("Enter category name again : ");
            scanf("%14s", category_name);         
        }
        capitalize(category_name);
        bool found = 0;
        int family_size = family_array[index].total_members;
        familyUserExpense user_expense[family_size];

        for (int i = 0; i < family_size; i++) {
            user_expense[i].user_id = family_array[index].family_members_user_id[i];
            user_expense[i].expense = 0;
        }
        for(int i = 0; i < family_size ; i++) {
            for(int j = 0; j < expense_count; j++) {
                if(family_array[index].family_members_user_id[i] == expense_array[j].user_ID) {
                    user_expense[i].user_id = expense_array[j].user_ID;
                    if(strcmp(expense_array[j].expense_category, category_name) == 0) {
                        found = 1;
                        total_expense = total_expense + expense_array[j].expense_amount;
                        user_expense[i].expense += expense_array[j].expense_amount;
                    }
                }
            }
        }
        if(found) {
            for (int i = 1; i < family_size; i++) {
                familyUserExpense key = user_expense[i];
                int j = i - 1;
                while (j >= 0 && user_expense[j].expense < key.expense) {
                    user_expense[j + 1] = user_expense[j];
                    j = j - 1;
                }
                user_expense[j + 1] = key;
            }
            printf("Family %d expense on the category %s is %.2f\n",family_ID, category_name, total_expense);
            for (int i = 0; i < family_size; i++) {
                printf("user %d : %f\n", user_expense[i].user_id, user_expense[i].expense);
            }
        } else {
            printf("No expense spent by the family %d on category %s\n", family_ID, category_name);
        }
    }
    return sc;
}

statusCode get_highest_expense_day(family family_array[], expense expense_array[]) {
    statusCode sc = SUCCESS;
    if (family_count <= 0 || expense_count <= 0) {
        printf("Empty family or expense list\n");
        sc = FAILURE;
    } else {
        int family_id;
        printf("Enter family ID: ");
        scanf("%d", &family_id);
        int index = get_family_id_index(family_array, family_id);     
        if (index == -1) {
            printf("Family ID %d not found\n", family_id);
            sc = FAILURE;
        } else {
            dailyExpense daily_expenses[MAX_EXPENSES] = {0};
            dailyExpense max_expense_day = {0};
            int unique_days_count = 0;
            bool found_any_expense = false;
            int i = 0;
            while (i < expense_count) {
                bool is_family_member = false;
                int n = family_array[index].total_members;
                for (int j = 0; j < n && !is_family_member; j++) {
                    if (family_array[index].family_members_user_id[j] == expense_array[i].user_ID) {
                        is_family_member = true;
                    }
                }               
                if (is_family_member) {
                    found_any_expense = true;
                    bool date_found = false;
                    for (int i = 0; i < unique_days_count && !date_found; i++) {
                        if (daily_expenses[i].date.date == expense_array[i].date_of_expense.date &&
                            daily_expenses[i].date.month == expense_array[i].date_of_expense.month &&
                            daily_expenses[i].date.year == expense_array[i].date_of_expense.year) {
                            daily_expenses[i].total_expense += expense_array[i].expense_amount;

                            if (daily_expenses[i].total_expense > max_expense_day.total_expense) {
                                max_expense_day = daily_expenses[i];
                            }
                            date_found = true;
                        }
                    }
                    if (!date_found) {
                        if (unique_days_count >= MAX_EXPENSES) {
                            printf("Maximum unique days limit reached\n");
                        } else {
                            daily_expenses[unique_days_count].date = expense_array[i].date_of_expense;
                            daily_expenses[unique_days_count].total_expense = expense_array[i].expense_amount;
                            if (daily_expenses[unique_days_count].total_expense > max_expense_day.total_expense) {
                                max_expense_day = daily_expenses[unique_days_count];
                            }
                            unique_days_count++;
                        }
                    }
                }
                i++;
            }
            if (!found_any_expense) {
                printf("No expenses found for family ID %d\n", family_id);
            } else {
                printf("Highest expense day for family ID %d:\n", family_id);
                printf("Date: %u-%u-%u\n", max_expense_day.date.date, max_expense_day.date.month, max_expense_day.date.year);
                printf("Total expense: %.2f\n", max_expense_day.total_expense);
            }
        }
    }
    return sc;
}

statusCode Get_Individual_Expense (expense expense_array[], user user_array[]) {
    statusCode sc = SUCCESS;
    int user_id;
    printf("enter user id :");
    scanf("%d", &user_id);
    if (!does_user_exist(user_array, user_id)) {
        printf("user %d doesnot exist.\n", user_id);
        sc = FAILURE;
    } else {
        float total_expense = 0;
        int index = -1;
        for (int i = 0; i < expense_count && index == -1; i++) {
            if (expense_array[i].user_ID == user_id) {
                index = i;
            }
        }
        if (index == -1) {
            printf("No expense by user.\n");
            sc = FAILURE;
        } else {
            cat_exp categoryExpense[5] = {
                {"RENT", 0},
                {"UTILITY", 0},
                {"GROCERY", 0},
                {"STATIONARY", 0},
                {"LEISURE", 0}
            };
            while (index < expense_count && expense_array[index].user_ID == user_id) {
                total_expense += expense_array[index].expense_amount;
                bool stop = false;
                for (int i = 0; i < 5 && !stop; i++) {
                    if (strcmp(expense_array[index].expense_category, categoryExpense[i].category_name) == 0) {
                        categoryExpense[i].expense += expense_array[index].expense_amount;
                        stop = true;
                    }
                }
                index++;
            }
            for (int i = 1; i < 5; i++) {
                cat_exp key = categoryExpense[i];
                int j = i - 1;
                while (j >= 0 && categoryExpense[j].expense < key.expense) {
                    categoryExpense[j + 1] = categoryExpense[j];
                    j = j - 1;
                }
                categoryExpense[j + 1] = key;
            }           
            printf("total expense by user %d : is %.2f.\n", user_id, total_expense);
            for (int i = 0; i < 5; i++) {
                if (categoryExpense[i].expense != 0) {
                    printf("%s: %.2f\n", categoryExpense[i].category_name, categoryExpense[i].expense);
                }
            }
        }
    }
    return sc;
}

statusCode readUsersFile(user user_array[]) {
    statusCode sc;
    FILE *file = fopen("users.txt", "r");
    if (!file) { 
        sc = FAILURE;
    } else {
        while (user_count < 25 && 
            fscanf(file, "%d,%99[^,],%f", &user_array[user_count].user_ID, user_array[user_count].user_name, &user_array[user_count].income) == 3) {
            user_count++;
        }
        fclose(file);
        sort_users_using_user_id(user_array, 0, user_count-1);
        sc = SUCCESS;
    }
    return sc;
}

statusCode readExpensesFile(expense expense_array[]) {
    statusCode sc;
    FILE *file = fopen("expenses.txt", "r");
    if (!file) {
        sc = FAILURE;
    } else {
        while (expense_count < 40 && 
            fscanf(file, "%d,%d,%[^,],%f,%u,%u,%u", 
                    &expense_array[expense_count].expense_ID, 
                    &expense_array[expense_count].user_ID, 
                    expense_array[expense_count].expense_category, 
                    &expense_array[expense_count].expense_amount, 
                    &expense_array[expense_count].date_of_expense.date, 
                    &expense_array[expense_count].date_of_expense.month, 
                    &expense_array[expense_count].date_of_expense.year) == 7) {
            expense_count++;
        }
        fclose(file);
        merge_sort_expenses(expense_array, 0, expense_count - 1);
        sc = SUCCESS;
    }
    return sc;
}

statusCode readFamiliesFile(family family_array[], user user_array[], expense expense_array[]) {
    statusCode sc;
    FILE *file = fopen("families.txt", "r");
    if (!file) {
        sc = FAILURE;
    } else {
        while (family_count < 10 && 
            fscanf(file, "%d,%49[^,],%d", &family_array[family_count].family_ID, family_array[family_count].family_name, &family_array[family_count].total_members) == 3) {
            for (int i = 0; i < family_array[family_count].total_members; i++) {
                if (fscanf(file, ",%d", &family_array[family_count].family_members_user_id[i]) != 1) return FAILURE;
            }
            family_count++;
        }
        fclose(file);
        sort_families(family_array, 0, family_count-1);
        for(int i = 0; i < family_count; i++){
            family_array[i].total_family_income = calculate_monthly_income_of_family(family_array[i], user_array);
            family_array[i].total_family_expense = calculate_monthly_expense_of_family(family_array[i], expense_array);
        }
        sc = SUCCESS;
    }
    return sc;
}

int main(){
    user user_array[MAX_USERS];
    expense expense_array[MAX_EXPENSES];
    family family_array[MAX_FAMILIES];
    
    initialize_users(user_array);
    initialize_expenses(expense_array);
    initialize_family(family_array);

    readUsersFile(user_array);
    readExpensesFile(expense_array);
    readFamiliesFile(family_array, user_array, expense_array);

    traverseUserArray(user_array);
    printf("\n");
    traverseExpenseArray(expense_array);
    printf("\n");
    traverseFamilyArray(family_array);
    printf("\n");

    int n = 1;
    while (n < 14 && n != 13 && n > 0) {
        printf("Enter 1  : Add User\n");
        printf("Enter 2  : Add Expense\n");
        printf("Enter 3  : Create Family\n");
        printf("Enter 4  : Update or Delete individual family\n");
        printf("Enter 5  : Update or Delete Expense\n");
        printf("Enter 6  : Get Total Expense\n");
        printf("Enter 7  : Get Categorical Expense\n");
        printf("Enter 8  : Get Highest Expense Day\n");
        printf("Enter 9  : Get Individual Expense\n");
        printf("Enter 10 : print users details\n");
        printf("Enter 11 : print expenses details\n");
        printf("Enter 12 : print families details\n");
        printf("Enter 13 : Exit\n");
        printf("enter n : ");
        scanf("%d", &n);

        switch (n) {
            case 1 :{
                statusCode status = AddUser(user_array, family_array);
                if (status == SUCCESS) {
                    printf("user added successfully.\n");
                    traverseUserArray(user_array);
                    printf("\n");
                    traverseFamilyArray(family_array);
                    printf("\n");
                } else {
                    printf("user adding operation failed.\n");
                }
                break;
            }
            case 2 :{
                statusCode status = AddExpense(expense_array, user_array);
                if (status == SUCCESS) {
                    printf("expense added successfully.\n");
                    traverseExpenseArray(expense_array);
                } else {
                    printf("expense operation failed.\n");
                }
                break;
            }  
            case 3 : {
                statusCode status = CreateFamily(family_array, user_array, expense_array);
                if(status == SUCCESS) {
                    printf("Family Created Successfully.\n");
                    traverseFamilyArray(family_array);
                } else {
                    printf("Error creating family.\n");
                }
                break;
            }
            case 4:{
                int j;
                printf("enter 1 : update_user\n");
                printf("enter 2 : update_family\n");
                printf("enter 3 : delete user\n");
                printf("enter 4 : delete family\n");
                printf("enter j : ");
                scanf("%d", &j);
                switch(j) {
                    case 1: {
                        statusCode status = updateUserDetails(user_array, family_array);
                        if (status == FAILURE) {
                            printf("update user unsuccessful.\n");
                        }
                        break;
                    }
                    case 2:{
                        int fam_id;
                        statusCode status = updateFamilyDetails(family_array, user_array, expense_array, &fam_id);
                        if (status == SUCCESS) {
                            printf("family %d details updated successfully.\n", fam_id);
                        } else {
                            printf("family %d details updated was unsuccessful.\n", fam_id);
                        }
                        break;
                    }
                    case 3:{
                        statusCode status = deleteUser(user_array, family_array, expense_array);
                        break;
                    }
                    case 4:{
                        statusCode status = deleteFamily(family_array, user_array, expense_array);
                        break;
                    }
                    default:{
                        printf("you entered wrong number.\n");
                        break;
                    }
                }
                break;
            }
            case 5:{
                int p;
                printf("enter 1 : update expenses\n");
                printf("enter 2 : delete expenses\n");
                printf("enter your number : ");
                scanf("%d", &p);
                switch(p){
                    case 1: {
                        statusCode status = updateExpense(expense_array, family_array);
                        break;
                    }
                    case 2: {
                        statusCode status = deleteExpense(expense_array, family_array);
                        break;
                    }
                    default: {
                        printf("you entered a wrong number.\n");
                        break;
                    }
                }
                break;
            }
            case 6: {
                if(family_count > 0) {
                    statusCode sc = Get_Total_Expense(family_array);
                }
                break;
            }
            case 7: {
                if(family_count > 0 && expense_count > 0) {
                    statusCode sc = get_categorical_expense(family_array, expense_array);
                }
                break;
            }
            case 8: {
                if (family_count > 0 && expense_count > 0) {
                    statusCode sc = get_highest_expense_day(family_array, expense_array);
                }
                break;
            }
            case 9: {
                if(expense_count > 0 && user_count > 0) {
                    statusCode sc = Get_Individual_Expense(expense_array, user_array);
                }
                break;
            }
            case 10: {
                traverseUserArray(user_array);
                break;
            }
            case 11: {
                traverseExpenseArray(expense_array);
                break;
            }
            case 12: {
                traverseFamilyArray(family_array);
                break;
            }
            case 13: {
                printf("Exiting.....\n");
                break;
            }
            default:{
                printf("you entered a wrong number.\n");
                break;
            }
        }
    }
    return 0;
}
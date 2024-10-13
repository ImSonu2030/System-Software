#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>   
#include <unistd.h>  
#include <sys/stat.h>

#define MAX_LEN 64
#define PATH_LEN 64

struct credential {
    int UID;
    _Bool active;
    char username[MAX_LEN];
    char password[MAX_LEN];
};

struct userDetails{
    int UID;
    char name[MAX_LEN];
    char email[MAX_LEN];
    char phone[MAX_LEN];
    char designation[MAX_LEN];
};

struct acbalance{
    long int balance;
};

struct transHistory{
    int fromID;
    int toID;
    char type[MAX_LEN];
    long int balance;
};

struct feedback{
    int star;
    char fb[256];
};

struct assignedLoan {
    char loanID[MAX_LEN];
    int uid;
    char username[MAX_LEN];
    long int amount;
    char status[MAX_LEN];
};

struct loanApplication{
    char loanID[MAX_LEN];
    int applicationNo;
    long int amount;
    char status[MAX_LEN];
};

void getError(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void printUserdetail(int userID){
    char path[PATH_LEN];
    struct userDetails userstat;

    snprintf(path,PATH_LEN,"%d/userdetail.dat",userID);
    int fd = open(path,O_RDONLY);
    read(fd,&userstat,sizeof(struct userDetails));
    close(fd);
    
    printf("%s Information-----------------------------\n",userstat.designation);
    printf("|Your ID: %d\n|Name: %s\n|Email: %s\n|Phone: %s",userstat.UID,userstat.name,userstat.email,userstat.phone);
    printf("\n-------------------------------------------------\n");
}

void printTransHistory(int userID){
    char path[PATH_LEN];
    struct transHistory userTransHist;

    snprintf(path,PATH_LEN,"%d/transactionHist.dat",userID);
    int fd = open(path,O_RDONLY);

    printf("Transactions---------------------------------\nFrom\t To\tType\t Amount\n");
    while(read(fd,&userTransHist,sizeof(struct transHistory))>0){
        printf("%d\t %d \t%s \t%ld\n",userTransHist.fromID,userTransHist.toID,userTransHist.type,userTransHist.balance);
    }
    close(fd);
    return;

}
void viewUserLoan(int userID){
    struct loanApplication loanEntry;
    char path[MAX_LEN];

    snprintf(path,MAX_LEN,"%d/userloandetail.dat",userID);
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        perror("Error opening the file");
        return;
    }

    printf("LoanID\t#Application\tAmount(\u20B9)\tStatus\n");
    printf("------------------------------------------------\n");
    while (read(fd,&loanEntry,sizeof(struct loanApplication))>0){
        printf("%s\t%d\t\u20B9%ld\t%s\n",loanEntry.loanID,loanEntry.applicationNo,loanEntry.amount,loanEntry.status);
    }
    close(fd);
}
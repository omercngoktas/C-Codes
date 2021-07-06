#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 256

struct users
{
    int id;
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    struct users *left, *right;
};

typedef struct users users;
typedef users usersPtr;
usersPtr *usersNode = NULL;
int openUsersList();
usersPtr *addUser(usersPtr *root, int id, char name[], char surname[]);
usersPtr *findUser(usersPtr *root, int idToFind);
usersPtr *findFirstUser(usersPtr *root);
usersPtr *findLastUser(usersPtr *root);

int openUsersList()
{
    int id;
    char name[MAX_SIZE], surname[MAX_SIZE];
    FILE *usersList = fopen("usersList.txt", "r");

    if(usersList == NULL)
    {
        printf("usersList.txt couldn't find. Please check it first.\n");
        return 0;
    }

    while(!feof(usersList))
    {
        fscanf(usersList, "%d %s %s", &id, name, surname);
        if(feof(usersList))
            break;
        usersNode = addUser(usersNode, id, name, surname);
    }
}

usersPtr *addUser(usersPtr *root, int id, char name[], char surname[])
{
    if(root == NULL)
    {
        root = (usersPtr *) malloc(sizeof(usersPtr));
        root->left = NULL;
        root->right = NULL;
        root->id = id;
        strcpy(root->name, name);
        strcpy(root->surname, surname);
        return root;
    }

    if(root->id < id)
    {
        root->right = addUser(root->right, id, name, surname);
        return root;
    }

    if(root->id > id)
    {
        root->left = addUser(root->left, id, name, surname);
        return root;
    }
}

usersPtr *findUser(usersPtr *root, int idToFind)
{
    if(root == NULL)
    {
        printf("The user that you are looking for is not available in list.\n");
        return NULL;
    }

    if(root->id == idToFind)
    {
        return root;
    }

    if(root->id < idToFind)
        return findUser(root->right, idToFind);

    if(root->id > idToFind)
        return findUser(root->left, idToFind);

}

usersPtr *findFirstUser(usersPtr *root)
{
    while(root->left != NULL)
        root = root->left;
    
    return root;
}

usersPtr *findLastUser(usersPtr *root)
{
    while(root->right != NULL)
        root = root->right;
    
    return root;
}

usersPtr *deleteUser(usersPtr *root, int idToFind)
{
    if(root == NULL)
    {
        printf("There is no user which matches with this id.\n");
        return NULL;
    }

    if(root->id == idToFind)
    {
        if(root->left == NULL && root->right == NULL)
            return NULL;

        if(root->right != NULL)
        {
            root->id = findFirstUser(root->right)->id;
            root->right = deleteUser(root->right, idToFind);
            return root;
        }

        if(root->left != NULL)
        {
            root->id = findLastUser(root->left)->id;
            root->right = deleteUser(root->left, idToFind);
            return root;
        }
        

    }

    if(root->id < idToFind)
        return deleteUser(root->right, idToFind);
    
    if(root->id > idToFind)
        return deleteUser(root->left, idToFind);
}

int main()
{
    openUsersList();
    usersPtr *iter = usersNode;
    printf("%d %s %s\n", iter->id, iter->name, iter->surname);
    iter = findUser(iter, 91);
    printf("%d %s %s\n", iter->id, iter->name, iter->surname);
    iter = usersNode;
    iter = findFirstUser(iter);
    printf("%d %s %s\n", iter->id, iter->name, iter->surname);
    iter = usersNode;
    iter = findLastUser(iter);
    printf("%d %s %s\n", iter->id, iter->name, iter->surname);
    iter = usersNode;
    iter = deleteUser(iter, 20);
    printf("%d %s %s\n", iter->id, iter->name, iter->surname);

    return 0;
}
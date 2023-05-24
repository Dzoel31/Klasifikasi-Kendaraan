#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct nodeTree
{
    char jenis[16];
    struct nodeTree *firstChild, *nextSibling;
    struct nodeLinkedList *linkedListHead;
} nodeTree;

typedef struct nodeLinkedList
{
    int nomorSeri, tahunPembuatan;
    char pemilik[20], merk[20];
    struct nodeLinkedList *next;
} nodeLL;

nodeTree *createTreeNode(char jenis[])
{
    nodeTree *newNode = (nodeTree *)malloc(sizeof(nodeTree));
    strcpy(newNode->jenis, jenis);
    newNode->linkedListHead = NULL;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

nodeTree *addType(nodeTree *parent, char jenis[])
{
    int addStatus = 1;
    nodeTree *newNode = createTreeNode(jenis);
    if (parent->firstChild == NULL)
    {
        parent->firstChild = newNode;
    }
    else
    {
        nodeTree *current = parent->firstChild;
        while (current->nextSibling != NULL)
        {

            current = current->nextSibling;
        }
        if (strcmp(current->jenis, jenis) == 0)
        {
            printf("Jenis sudah ada! Masukkan jenis lain!\n");
            addStatus = 0;
            free(newNode);
        }
        else
        {
            addStatus = 1;
        }
        if (addStatus == 1)
        {
            current->nextSibling = newNode;
        }
    }
    return newNode;
}

nodeTree *findType(nodeTree *root, char jenis[])
{
    if (root == NULL)
    {
        printf("Belum ada jenis kendaraan yang terdaftar!");
        return NULL;
    }
    if (strcmp(jenis, root->jenis) == 0)
    {
        return root;
    }
    nodeTree *current = root->firstChild;
    while (current != NULL)
    {
        nodeTree *result = findType(current, jenis);
        if (result != NULL)
        {
            return result;
        }
        current = current->nextSibling;
    }
    return NULL;
}

nodeLL *createListNode(int nomorSeri, char pemilik[], char merk[], int tahunPembuatan)
{
    nodeLL *newNode = (nodeLL *)malloc(sizeof(nodeLL));
    newNode->nomorSeri = nomorSeri;
    strcpy(newNode->pemilik, pemilik);
    strcpy(newNode->merk, merk);
    newNode->tahunPembuatan = tahunPembuatan;
    newNode->next = NULL;
    return newNode;
}

void addData(nodeLL **head, int nomorSeri, char pemilik[], char merk[], int tahunPembuatan)
{
    nodeLL *newNode = createListNode(nomorSeri, pemilik, merk, tahunPembuatan);

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        nodeLL *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printList(nodeLL *head)
{
    nodeLL *current = head;
    while (current != NULL)
    {
        printf("============\n");
        printf("Nomor Seri : %d \n", current->nomorSeri);
        printf("Pemilik : %s \n", current->pemilik);
        printf("Merk : %s \n", current->merk);
        printf("Tahun Pembuatan : %d \n", current->tahunPembuatan);
        current = current->next;
    }
}

void printAllData(nodeTree *root)
{
    if (root != NULL)
    {
        printf("Jenis Kendaraan: %s\n", root->jenis);
        printf("Data Kendaraan:\n");
        printList(root->linkedListHead);
        printf("\n");

        nodeTree *current = root->firstChild;
        while (current != NULL)
        {
            printAllData(current);
            current = current->nextSibling;
        }
    }
}

void printSpecifiedType(nodeTree *root, char jenis[])
{
    if (root != NULL)
    {
        printf("Jenis Kendaraan: %s\n", root->jenis);
        printf("Data Kendaraan:\n");
        printList(root->linkedListHead);
        printf("\n");

        nodeTree *current = root->firstChild;
        while (current != NULL)
        {
            if (strcmp(current->jenis, jenis) == 0)
            {
                printSpecifiedType(current, jenis);
            }

            current = current->nextSibling;
        }
    }
}
int main(int argc, char const *argv[])
{
    char jenis[20], pemilik[20], merk[20];
    int menu, index = 0, nomorSeri, tahunPembuatan, selectedIndex;
    nodeTree *type[10];
    nodeTree *root = createTreeNode("Kendaraan");
    do
    {
        system("cls");
        printf("-----Menu-----\n");
        printf("[1] Masukkan jenis kendaraan\n");
        printf("[2] Tambah data\n");
        printf("[3] Lihat semua data\n");
        printf("[4] Lihat data tertentu\n");
        printf("[0] Exit\n");
        printf("Pilih menu : ");
        scanf("%d", &menu);
        getchar();
        switch (menu)
        {
        case 1:
            printf("Masukkan jenis kendaraan : ");
            scanf("%s", jenis);
            nodeTree *newNode = addType(root, jenis);
            type[index] = newNode;
            index++;
            break;
        case 2:
            printf("Jenis kendaraan terdaftar : \n");
            for (int i = 0; i < index; i++)
            {
                printf("%d- %s\n", i + 1, type[i]);
            }
            printf("Pilih jenis (angka) : ");
            scanf("%d", &selectedIndex);
            printf("Nomor Seri : ");
            scanf("%d", &nomorSeri);
            printf("Pemilik : ");
            scanf("%s", pemilik);
            printf("Merk : ");
            scanf("%s", merk);
            printf("Tahun Pembuatan : ");
            scanf("%d", &tahunPembuatan);
            addData(&(type[selectedIndex - 1]->linkedListHead), nomorSeri, pemilik, merk, tahunPembuatan);
            break;
        case 3:
            printAllData(root);
            break;
        case 4:
            printf("Jenis kendaraan terdaftar : \n");
            for (int i = 0; i < index; i++)
            {
                printf("%d- %s\n", i + 1, type[i]);
            }
            printf("Pilih jenis (angka) : ");
            scanf("%d", &selectedIndex);
            printSpecifiedType(root, type[selectedIndex - 1]->jenis);
            break;
        case 0:
            exit(1);
            break;
        default:
            printf("Tidak menu yang sesuai!\n");
            break;
        }
        printf("Enter untuk lanjut!\n");
        getch();
    } while (menu != 0);
}

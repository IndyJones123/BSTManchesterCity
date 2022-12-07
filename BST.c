#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
//Insertion and deletion in Binary Search Tree
struct Node
  //membuat structure node yang berisi node kiri, data dan node kanan
{
	struct Node* left;
	int data;
	struct Node* right;
	int height;
};

struct Queue
//membuat strucutre antrian yang menghubungkan antar node
{
	struct Node* data;
	struct Queue* next;
};

struct Queue* front = NULL;
struct Queue* rear = NULL;

int isEmpty()
//sebuah fungsi yang mengindikasikan apakah antrian kosong atau sudah terisi 
{
	if(front==NULL)
		return 1;
	else
		return 0;
}

void Pop()
//fungsi yang digunakan untuk mengeluarkan data
{
	if(isEmpty())
		return;

	struct Queue* temp = front;
	front = front->next;
	free(temp);

	
}

struct Node* Pfront()
//mencari node yang terdepan
{
	struct Node* temp ;
	temp = front->data;
	return temp;
}

void Enqeue(struct Node* data)
//fungsi untuk menambah data pada antrian yang paling belakang
{
	struct Queue* temp;
	temp = (struct Queue*)malloc(sizeof(struct Queue));
	temp->data = data;
	temp->next=NULL;

	if(front==NULL && rear==NULL)
	{
		front = rear = temp;
		return;
	}

	rear->next = temp;
	rear =temp;
}

struct Node* NewNode(int data)
//berfungsi untuk menambahkan node baru pada data yang bergua nani pada fungsi insert
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->left = NULL;
	temp->data = data;
	temp->right = NULL;

	return temp;
}

void PostOrder(struct Node* root)
//output post order traversal BST
{
	if(root==NULL)
		return;

	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ",root->data);
}

struct Node* FindMin(struct Node* root)
//mencari angka minimal pada node 
{
	while(root->left!=NULL)
		root = root->left;

	return root;
}

void LevelOrder(struct Node* root)
//output lever order traversal pada BST
{
	if(root==NULL)
		return;

	Enqeue(root);

	while(!isEmpty())
	{
		struct Node* current = Pfront();
		printf("%d ",current->data);
		if(current->left!=NULL)
			Enqeue(current->left);
		if(current->right!=NULL)
			Enqeue(current->right);

		Pop();
	}
}

struct Node* Delete(struct Node* root,int data)
//fungsi untuk menghapus data yang telah di tulis ke dalam node 
{
	if(root==NULL)
		return root;

	else if(data < root->data)
		root->left = Delete(root->left,data);

	else if(data > root->data)
		root->right = Delete(root->right,data);

	else
	{
		if(root->left==NULL && root->right==NULL)
		{
			free(root);
			root = NULL;
		}

		else if(root->left!=NULL && root->right==NULL)
		{
			struct Node* temp = root->left;
			free(temp);
			root = root->left;
		}
		else if(root->right!=NULL&& root->left==NULL)
		{
			struct Node* temp = root->right;
			free(temp);
			root = root->right;
		}

		else
		{
			struct Node* temp = FindMin(root->right);
			root->data = temp->data;
			root->right = Delete(root->right,temp->data); 
		}

	}
	return root;
}

void InOrder(struct Node* root)
//output in order traversal pada BST
{
	if(root==NULL)
		return;

	InOrder(root->left);
	printf("%d ",root->data);
	InOrder(root->right);
}

void PreOrder(struct Node* root)
//output pre order traversal pada BST
{
	if(root==NULL)
		return;

	printf("%d ",root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}

struct Node* insert(struct Node* root,int data)
//menginput data kedalam node
{
	if(root==NULL)
		root =  NewNode(data);

	else if(data <= root->data)
		root->left = insert(root->left,data);
	
	else root->right = insert(root->right,data);

	return root;

}

void traverse(struct Node* root)
//semua outputan yang ada pada BST yang akan di inisialisasi
{
	printf("  | PreOrder traversal\t\t|\t"); PreOrder(root); printf("|");
	printf("\n  | Inorder traversal\t\t|\t"); InOrder(root); printf("|");
	printf("\n  | PostOrder traversal\t\t|\t"); PostOrder(root); printf("|");
	printf("\n  | Level Order Traversal\t|\t"); LevelOrder(root); printf("|");
}

//AVL

//Insertion and deletion in AVL Tree
struct Node* NewNodeS(int data)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	temp->height = 1;
	return temp;
}

int max(int a,int b)
{
 	return (a>b)?a:b;
}

int height(struct Node* node)
{
	if(node==NULL)
		return 0;

 	return node->height;
}

int Balance(struct Node* node)
{
	if(node==NULL)
		return 0;

 	return height(node->left) - height(node->right);
}

struct Node* LeftRotate(struct Node* z)
{
	struct Node* y = z->right;
	struct Node* t2 = y->left;

	y->left = z;
	z->right = t2;

	z->height = max(height(z->left),height(z->right))+1;
	y->height = max(height(y->left),height(y->right))+1;

	return y;
}

struct Node* RightRotate(struct Node* z)
{
	struct Node* y = z->left;
	struct Node* t3 = y->right;

	y->right = z;
	z->left = t3;

	z->height = max(height(z->left),height(z->right))+1;
	y->height = max(height(y->left),height(y->right))+1;

	return y;
}

void preorder(struct Node* root)
{
	if(root==NULL)
		return;

	printf("%d ",root->data);
	preorder(root->left);
	preorder(root->right);
}

struct Node* FindMinS(struct Node* node)
{
	while(node->left!=NULL)
		node = node->left;

	return node;
}

struct Node* DeleteS(struct Node* root,int data)
{
	if(root==NULL)
		return root;

	if(data < root->data)
		root->left = DeleteS(root->left,data);

	else if(data > root->data)
		root->right = DeleteS(root->right,data);

	else
	{
		if(root->right==NULL && root->left==NULL)
		{
			free(root);
			root = NULL;
		}

		else if(root->left!=NULL && root->right==NULL)
		{
			struct Node* temp = root->left;
			root = root->left;
			free(temp);
		}

		else if(root->right!=NULL && root->left==NULL)
		{
			struct Node* temp = root->right;
			root = root->right;
			free(temp);
		}

		else
		{
			struct Node* temp = FindMin(root->right);
			root->data = temp->data;
			root->right = DeleteS(root->right,temp->data);
		}
	}
	if(root==NULL)
		return root;

	root->height = 1 + max(height(root->left),height(root->right));

	int balance = Balance(root);

	//Left Left Case
	if(balance > 1 && Balance(root->left) >=0)
		return RightRotate(root);

	// Right Right Case
	if(balance < -1 && Balance(root->right) <=0)
		return LeftRotate(root);

	// Left Right Case
	if(balance > 1 && Balance(root->left) < 0)
	{
		root->left = LeftRotate(root->left);
		return RightRotate(root);
	}
	
	//Right Left Case
	if(balance < -1 && Balance(root->right) > 0)
	{
		root->right = RightRotate(root->right);
		return LeftRotate(root);
	}
	return root;
}

struct Node* Insert(struct Node* root,int data)
{
	if(root==NULL)
		return NewNodeS(data);

	if(data < root->data)
		root->left = Insert(root->left,data);

	else if(data > root->data)
		root->right = Insert(root->right,data);

	else
		return root;

	root->height = max(height(root->left),height(root->right))+1;

	int balance = Balance(root);

	// Left Left Case
	if(balance > 1 && data < root->left->data)
		return RightRotate(root);

	// Right Right Case
	if(balance < -1 && data > root->right->data)
		return LeftRotate(root);

	//Left Right Case
	if(balance > 1 && data > root->left->data)
	{
		root->left = LeftRotate(root->left);
		return RightRotate(root);
	}

	// Right Left Case
	if(balance < -1 && data < root->right->data)
	{
		root->right = RightRotate(root->right);
		return LeftRotate(root);
	}

	return root;
}

int insertBST(int a)
{
	struct Node* root = NULL;
	root = insert(root,a);
}
//int insertAVL()
//{
//	struct Node* root = NULL;
//	int testInteger;
//	printf("Enter an integer: ");
//    scanf("%d", &testInteger);
//	root = Insert(root,testInteger);
//	
//}
//int deleteBST()
//{
//	struct Node* root = NULL;
//	int deleteInteger;
//	printf("Enter an integer: ");
//    scanf("%d", &deleteInteger);
//	root = Insert(root,deleteInteger);
//}
//int deleteAVL()
//{
//	struct Node* root = NULL;
//	int deleteInteger;
//	printf("Enter an integer: ");
//    scanf("%d", &deleteInteger);
//	root = Insert(root,deleteInteger);
//}


int main()
{
	int testinteger;
	int choice;
	struct Node* root = NULL;
	
	printf(" ========================================================\n");
	printf(" ||>>>>>>>>>>>>>>>>  UAS STRUKTUR DATA  <<<<<<<<<<<<<<<||\n");
	printf(" ========================================================\n");
	printf(" +------------------------------+-----------------------+\n");
	printf(" |\t\tNPM\t\t|\tNAMA\t\t|\n");
	printf(" +------------------------------+-----------------------+\n");
	printf(" |\tAlfian Dorif Murtadlo\t|\t20081010251\t|\n");
	printf(" |\tDaffa Tungga Wisesa\t|\t21081010243\t|\n");
	printf(" |\tMuhamad Rizal Efendi\t|\t21081010035\t|\n");	
	printf(" +------------------------------+-----------------------+\n\n");
	printf(" ========================================================\n");

	printf("  +========================================================+\n");
	printf("  |>>>>>>>>>>>> DATA STANDING MANCHASTER CITY <<<<<<<<<<<<<|\n");
	printf("  |>>>>>>>>>>>>>>> PREMIER LEAGUE 2021/2022 <<<<<<<<<<<<<<<|\n");
	printf("  +========================================================+\n");
	printf("  +--------------------------------------------------------+\n");
	printf("  |         CLUB          | P  |  W | D | L | GF | GA | Pts|\n");
	printf("  +-----------------------+----+---+---+----+----+----+----+\n");
	printf("  | MANCHASTER CITY       | 38 | 29 | 6 | 3 | 99 | 26 | 93 |\n");
	printf("  +=============================+==========================+\n");
	printf(" ========================================================\n");
	do
    {
    printf(" ||>>>>>>>>>>>>>>>  Pilih Operasi  <<<<<<<<<<<<<<||\n");
    printf(" ========================================================\n");
    printf("\n 1.Insert Score BST \n 2.Insert Score AVL\n 3.Delete Score BST\n 4.Delete Score AVL\n 5.CLEAR\n 6.DISPLAY\n 7.EXIT\n\n");
    printf(" --------------------------------------------------------\n");
    printf(" Masukkan Pilihan : "); scanf("%d",&choice);
    printf(" ========================================================\n");
        switch(choice)
        {
            case 1:
            {
            	printf("Enter an integer: ");
   				scanf("%d", &testinteger);
            	insertBST(testinteger);
                break;
            }
		    case 2:
            {
//				insertAVL();
                break;
            }
		    case 3:
            {

                break;
            }
            case 4:
            {
				
                break;
            }
            case 5:
            {
                		
                break;
            }
            case 6:
            {
            	root = insert(root,38);
				root = insert(root,29);
				root = insert(root,6);
				root = insert(root,3);
				root = insert(root,99);
				root = insert(root,26);
				root = insert(root,93);
                traverse(root);
                getch();system("cls");
                break;
            }
            case 7:
            {
                
                break;
            }
            default:
            {
                printf ("\n Masukkan Pilihan Yang Valid Bu(1/2/3/4/5/6)");
                getch(); system("cls");
            }
                 
        }
	}
    while(choice!=7);

    return 0;
	
}

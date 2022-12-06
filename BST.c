#include <stdio.h>
#include <stdlib.h>
//Insertion and deletion in Binary Search Tree
struct Node
  //membuat structure node yang berisi node kiri, data dan node kanan
{
	struct Node* left;
	int data;
	struct Node* right;
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
	printf("\n\nPreOrder traversal : "); PreOrder(root);
	printf("\nInorder traversal  :   "); InOrder(root);
	printf("\nPostOrder traversal:   "); PostOrder(root);
	printf("\n Level Order Traversal: ");LevelOrder(root);
}

int main()
{
	struct Node* root = NULL;
	//Inisiasi Node kedalam BST
	root = insert(root,38);
	root = insert(root,29);
	root = insert(root,6);
	root = insert(root,3);
	root = insert(root,99);
	root = insert(root,26);
	root = insert(root,73);
	

	traverse(root);


	return 0;
}

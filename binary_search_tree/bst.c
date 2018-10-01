#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } bool;	// ȿ������ ��ó���� ���� bool Ÿ�� ����

typedef int element;

typedef struct _tNode {				// Ʈ���� ��� ����ü
	element data;					// ����� Ű ��
	struct _tNode *left, *right;
} tNode;

typedef struct _Queue {
	tNode *queue[10000];
	int front;
	int rear;
} Queue;

int print_menu();								// ���α׷��� ����� �Ұ��ϴ� �޴��� ���
void create_node(tNode **root, element key);	// Ư�� Ű ���� ���� ��带 Ʈ���� �߰�
void delete_node(tNode **root, element key);	// Ư�� Ű ���� ���� ��带 Ʈ������ ����
void preorder(tNode *root);						// ���� ��ȸ�� ��� ��带 �湮 & ���
void inorder(tNode *root);						// ���� ��ȸ�� ��� ��带 �湮 & ���
void postorder(tNode *root);					// ���� ��ȸ�� ��� ��带 �湮 & ���
void search_node(tNode *root, element key);		// Ʈ������ Ư�� Ű ���� �����ϴ��� ã�´�.

												// �ٽ��� �� ���� �ۼ��� �ʿ䰡 �ִ� �Լ�
int tree_height(tNode *root);					// Ʈ���� ���̸� ��ȯ�Ѵ�.
int node_count(tNode *root);					// Ʈ���� �����ϴ� ����� ������ ��ȯ�Ѵ�.

void delete_tree(tNode *root);					// ���α׷��� �����ϱ� �� �����Ҵ����� ������ ��� ��带 ��ȯ�Ѵ�.
int min_key_value(tNode *root);					// Ʈ������ ���� ���� Ű ���� ã�´�.
int max_key_value(tNode *root);					// Ʈ������ ���� ū Ű ���� ã�´�.

void init(Queue *qu);							// Queue�� �ʱ�ȭ�� �����Ѵ�.
void push(Queue *qu, tNode *node);				// node�� Queue�� ��� �۾�
tNode* pop(Queue *qu);							// tNode* �� ��� �ִ� Queue���� pop


int level_find(tNode *root, element key);		// key ���� ���� �ִ� ������ ����Ѵ�.
void level_print(tNode *root, int level);		// �Է��� level�� �ش��ϴ� ������ ����Ѵ�.

int main()
{
	tNode *root = NULL;
	int userInput;			// UI���� ����ڰ� �Է��� ��
	element data;
	int level;

	printf("************* 1233040 Huynwoo Lee ver. *************\n\n");
	printf("you cannot input minus value and zero in this program\n\n");
	while (TRUE)
	{
		userInput = print_menu();

		switch (userInput)
		{
		case 1:
			printf("key value: ");
			scanf("%d", &data);
			while (getchar() != '\n');
			create_node(&root, data);
			break;
		case 2:
			printf("key value: ");
			scanf("%d", &data);
			while (getchar() != '\n');
			delete_node(&root, data);
			break;
		case 3:
			preorder(root);
			putchar('\n');
			break;
		case 4:
			inorder(root);
			putchar('\n');
			break;
		case 5:
			postorder(root);
			putchar('\n');
			break;
		case 6:
			printf("key value: ");
			scanf("%d", &data);
			while (getchar() != '\n');
			search_node(root, data);
			break;
		case 7:
			if (root == NULL)
			{
				printf("you can use this function at least 1 node\n");
				break;
			}
			printf("hieght of tree is %d\n", tree_height(root));
			break;
		case 8:
			printf("count of node in tree is %d\n", node_count(root));
			break;
		case 9:
			delete_tree(root);
			exit(1);
			break;
		case 49:
			min_key_value(root);
			break;
		case 50:
			max_key_value(root);
			break;
		case 51:
			printf("key value: ");
			scanf("%d", &data);
			while (getchar() != '\n');
			printf("level is %d\n", level_find(root, data));
			break;
		case 52:
			printf("level value: ");
			scanf("%d", &level);
			while (getchar() != '\n');
			level_print(root, level);
			break;
		}
	}
	return 0;
}

// ����ڰ� ����� ������ �� �ִ� �������̽��� �����Ѵ�.
int print_menu()
{
	int select;

	while (TRUE)
	{
		printf("*********************\n");
		printf("1: insert_node\n");
		printf("2: delete_node\n");
		printf("3: preorder\n");
		printf("4: inorder\n");
		printf("5: postorder\n");
		printf("6: search_node\n");
		printf("7: tree_height\n");
		printf("8: node_count\n");
		printf("9: exit_program\n");
		printf("a: min_key_value\n");
		printf("b: max_key_value\n");
		printf("c: level that has node what you input\n");
		printf("d: node's count of level and its elements\n");
		printf("*** Which select? : ");

		select = getchar();

		// �߸� �Է����� ��� �����޽��� ��°� �Բ� �ٽ� �Է��ϰԲ� �������̽� â�� ����.
		if (getchar() != '\n')
		{
			printf("what you input is wrong value. retry input\n");
			while (getchar() != '\n');
		}
		else if ((select < '1' || select > '9') && (select != 'a' && select != 'b' && select != 'c' && select != 'd'))
		{
			printf("what you input is wrong value. retry input\n");
		}
		else
			break;

	}

	// �����Լ����� switch case ���� ���� ü�踦 ��������Ƿ�, ĳ���ͷ� �״�� ��ȯ�ϴ� ���� �ƴ϶� '0'�� �� ���� ��ȯ�Ѵ�.
	return (select - '0');
}

// Ư�� Ű ���� ���� ��带 �������� �����ؼ� ��Ʈ�� ���δ�.
void create_node(tNode **root, element key)
{
	tNode *parent = *root;
	tNode *child = NULL;
	tNode *newNode = (tNode *)malloc(sizeof(tNode));
	newNode->data = key;
	newNode->left = newNode->right = NULL;

	if (parent == NULL)
	{
		*root = newNode;
		return;
	}

	while (parent != NULL)
	{
		if (parent->data < newNode->data)
		{
			if (parent->right == NULL)
			{
				parent->right = newNode;
				return;
			}
			else
				parent = parent->right;
		}
		else if (parent->data == newNode->data)
		{
			fprintf(stderr, "same key value already exists in this tree\n");
			free(newNode);
			return;
		}
		else
		{
			if (parent->left == NULL)
			{
				parent->left = newNode;
				return;
			}
			else
				parent = parent->left;
		}
	}
	return;
}

// Ư�� Ű ���� ���� ��带 �����ϰ�, ������ Ž�� Ʈ���� ������ �� �ְ� �۾��� ���ش�.
void delete_node(tNode **root, element key)
{
	tNode *p, *t, *child, *succ_p, *succ;
	p = NULL;
	t = *root;

	while (t != NULL && t->data != key)
	{
		p = t;
		(t->data > key) ? (t = t->left) : (t = t->right);
	}

	if (t == NULL) {
		fprintf(stderr, "cannot find the value what you want to delete.\n");
		return;
	}

	if (t->left == NULL && t->right == NULL)
	{
		if (p != NULL)
		{
			if (p->left == t)
				p->left = NULL;
			else
				p->right = NULL;
		}
		else
			*root = NULL;

	}

	else if (t->left == NULL || t->right == NULL) {
		child = (t->left != NULL) ? t->left : t->right;
		if (p != NULL)
		{
			if (p->left == t)
				p->left = child;
			else
				p->right = child;
		}
		else
			*root = NULL;
	}

	else {
		succ_p = t;
		succ = t->right;

		while (succ->left != NULL) {
			succ_p = succ;
			succ = succ->left;
		}

		// while ������ ���� �� �� �̻� �������� ������ �� ���� ��
		if (succ_p->left == succ)	// while ������ ���Ҵٸ� �� ������ ������ ���̴�.
			succ_p->left = succ->right;	// ������ ����� ������ ���� succ_p�� ������ ���δ�.
		else // ���� ������� Ʈ���� �ƿ� �� ���� while������ ���� ������ ��
			succ_p->right = succ->right;

		// ������ ����� ������ ���� ����
		t->data = succ->data;
		// ������ ���� �ּҰ� ����
		t = succ;
	}
	// ��� ����
	free(t);
	printf("deleting node is successful.\n");
}

// ������ȸ
void preorder(tNode *root)
{
	if (root != NULL)
	{
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

// ������ȸ
void inorder(tNode *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

// ������ȸ
void postorder(tNode *root)
{
	if (root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

// Ư�� Ű ���� ���� ��带 ã�� �� Ű ���� ������ش�.
void search_node(tNode *root, element key)
{
	printf("path: ");
	while (root != NULL)
	{
		printf("%d ", root->data);
		if (root->data == key)
		{
			printf("\t finally find it %d\n", key);
			return;
		}
		else if (root->data < key)
			root = root->right;
		else
			root = root->left;
	}
	printf("dosen't exist key in this tree\n");
	return;
}

// Ʈ���� ���̸� ���Ͽ� �ܼ�ȭ�鿡 ����Ѵ�.
int tree_height(tNode *root)
{
	int height = 0;
	if (root != NULL)
		height = 1 + max(tree_height(root->left), tree_height(root->right));

	return height;
}

// Ʈ���� ��� ������ ���Ͽ� �ܼ�ȭ�鿡 ����Ѵ�.
int node_count(tNode *root)
{
	int count = 0;
	if (root == NULL)
		return 0;
	count = 1 + node_count(root->left) + node_count(root->right);

	return count;
}

// Ʈ���� �����ϴ� ��� ��带 ��ȯ�Ѵ�. ���α׷� ���Ḧ ������ �� ����ȴ�.
void delete_tree(tNode *root)
{
	if (root == NULL)
		return;
	else if (root->left == NULL && root->right == NULL)
	{
		free(root);
		return;
	}
	delete_tree(root->left);
	delete_tree(root->right);
	free(root);
}

// Ʈ������ �ּҰ��� ã�� ����Ѵ�.
int min_key_value(tNode *root)
{
	tNode *p = NULL;

	// �ƹ� ���� �����Ƿ� �ּ� ���� ã�� �� ����.
	if (root == NULL) {
		fprintf(stderr, "there is no value to find.\n");
		return -1;
	}
	while (root != NULL) {
		p = root;
		root = root->left;
	}
	printf("min_value in this tree is %d\n", p->data);
}

// Ʈ������ �ִ밪�� ã�� ����Ѵ�.
int max_key_value(tNode *root)
{
	tNode *p = NULL;

	// �ƹ� ���� �����Ƿ� �ּ� ���� ã�� �� ����.
	if (root == NULL) {
		fprintf(stderr, "there is no value to find.\n");
		return -1;
	}
	while (root != NULL) {
		p = root;
		root = root->right;
	}
	printf("min_value in this tree is %d\n", p->data);
}

// Queue�� �ʱ�ȭ�� �����Ѵ�.
void init(Queue *qu)
{
	int i;
	qu->front = 1;
	qu->rear = 0;

	for (i = 0; i < 10000; i++)
	{
		qu->queue[i] = NULL;
	}
}

// node�� Queue�� ��� �۾�
void push(Queue *qu, tNode *node)
{
	qu->queue[++(qu->rear)] = node;
}

// tNode* �� ��� �ִ� Queue���� pop
tNode* pop(Queue *qu)
{
	return qu->queue[(qu->front)++];
}

// key ���� ���� �ִ� ������ ����Ѵ�.
int level_find(tNode *root, element key)
{
	int level = 0;
	while (root != NULL)
	{
		level++;
		if (root->data == key)
			return level;

		else if (root->data < key)
			root = root->right;
		else
			root = root->left;
	}
	printf("dosen't exist key in this tree\n");
	return -1;
}

// Ư�� ������ �ִ� ����� �� ������ �����ش�.
void level_print(tNode *root, int level)
{
	// ���� ����̹Ƿ�, ���� ���� ���� ������ �迭�� �����ؼ� ��� ����� ���� �迭�� �����Ѵ�.
	// ��, ������ �� �־��� ������ �ִ� ������ ����� ������ �̸� ����Ͽ�
	// ���� ���� ���� ���� ������ �̷����� �ʰԲ� �����Ѵ�.
	tNode *tmp = NULL;
	element nodeArray[1000] = { 0 };
	int index = 1;
	int i;
	int sIndex = 1;
	int eIndex = 1;
	int maxIndex = 1;
	for (i = 0; i < level; i++)
		maxIndex *= 2;

	int node_cnt = 0;
	
	Queue qu;
	init(&qu);

	// ó���� root ���� �ִ� ������ �Լ� ����
	push(&qu, root);

	while (TRUE)	// �־��� ���� ������ ���� ������ ���� ������ ��� �ݺ��Ѵ�.
	{
		// pop()�� �ߴµ� NULL �̾��ٸ� Queue�� NULL�� �� �� �ִ´�.
		// NULL�� �ƴϰ� �������� ��忴�ٸ�, �� �ؿ� �ڽ� ������ ť�� �ִ´�.
		tmp = pop(&qu);

		if (index >= maxIndex)
			break;

		if (tmp != NULL)
		{
			push(&qu, tmp->left);
			push(&qu, tmp->right);

			nodeArray[index++] = tmp->data;
		}
		// ���� ��������Ͱ� NULL�̶�� �迭���� �״�� 0�� �����ְ� �ȴ�. ���� index�� ������Ų��.
		else
		{
			push(&qu, NULL);
			push(&qu, NULL);
			index++;
		}
	}

	// �־��� ������ ���� startIndex�� �����Ѵ�.
	for (i = 0; i < level - 1; i++)
		sIndex *= 2;

	// �־��� ������ ���� endIndex�� �����Ѵ�.
	for (i = 0; i < level; i++)
		eIndex *= 2;
	eIndex--;
	
	printf("node of this level is ");

	for (i = sIndex; i <= eIndex; i++)
		if (nodeArray[i] != 0)
		{
			printf("%d ", nodeArray[i]);
			node_cnt++;
		}

	printf("\nthe count of node is %d\n", node_cnt);
}
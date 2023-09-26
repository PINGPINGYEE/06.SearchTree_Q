#include <stdio.h>
#include <stdlib.h>

// ���� Ž�� Ʈ�� ��� ����
typedef struct TreeNode {
    int data;
    struct TreeNode* left, *right;
} TreeNode;

// ���� Ž�� Ʈ�� ���� �Լ�
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

// ���� Ž�� Ʈ������ ��� ���� �Լ�
TreeNode* delete(TreeNode* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = delete(root->left, data);
    }
    else if (data > root->data) {
        root->right = delete(root->right, data);
    }
    else {
        // ������ ��带 ã���� ��
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // �� �ڽ� ��� ��� �ִ� ���
        TreeNode* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}



// ���� Ž�� Ʈ������ ��� �˻� �Լ�
TreeNode* searchIterative(TreeNode* root, int data) {
    while (root != NULL && root->data != data) {
        if (data < root->data) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return root;
}


// ���� Ž�� Ʈ�� ���� ��ȸ �Լ�
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// ���� Ž�� Ʈ�� ��� ���� ����ϴ� �Լ�
int countNodes(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// ���� Ʈ�� ��� ���� (�ݺ��� ���)
TreeNode* insertIterative(TreeNode* root, int data) {
    TreeNode* newNode = createNode(data);

    if (root == NULL) {
        return newNode;
    }

    TreeNode* current = root;
    TreeNode* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (data < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    return root;
}

// ���� Ʈ�� ��� ���� (�ݺ��� ���)
TreeNode* deleteIterative(TreeNode* root, int data) {
    if (root == NULL) {
        return root;
    }

    TreeNode* current = root;
    TreeNode* parent = NULL;

    while (current != NULL && current->data != data) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (current == NULL) {
        // ������ ��带 ã�� ���� ���
        return root;
    }

    if (current->left == NULL && current->right == NULL) {
        // ������ ��尡 ���� ����� ���
        if (parent == NULL) {
            free(current);
            return NULL; // ��Ʈ ��� ����
        }

        if (current == parent->left) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
        free(current);
    }

    else if (current->left != NULL && current->right != NULL) {
        // ������ ��尡 �� ���� �ڽ� ��带 ���� ���
        TreeNode* successor = current->right;
        TreeNode* successorParent = current;

        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }

        current->data = successor->data;
        if (successor == successorParent->left) {
            successorParent->left = successor->right;
        }
        else {
            successorParent->right = successor->right;
        }
        free(successor);
    }
    else {
        // ������ ��尡 �ϳ��� �ڽ� ��常 ���� ���
        TreeNode* child = (current->left != NULL) ? current->left : current->right;

        if (parent == NULL) {
            return child; // ��Ʈ ��� ����
        }

        if (current == parent->left) {
            parent->left = child;
        }
        else {
            parent->right = child;
        }
        free(current);
    }

    return root;
}

TreeNode n12 = { 42, NULL, NULL };
TreeNode n13 = { 62, NULL, NULL };
TreeNode n14 = { 64, NULL, NULL };
TreeNode n7 = { 25, NULL, NULL };
TreeNode n8 = { 46, &n12, NULL };
TreeNode n9 = { 55, NULL, NULL };
TreeNode n10 = { 63, &n13, &n14 };
TreeNode n11 = { 70, NULL, NULL };
TreeNode n4 = { 16, NULL, &n7 };
TreeNode n5 = { 53, &n8, &n9 };
TreeNode n6 = { 65, &n10, &n11 };
TreeNode n2 = { 41, &n4, &n5 };
TreeNode n3 = { 74, &n6, NULL };
TreeNode n1 = { 60, &n2, &n3 };
TreeNode* root = &n1;

int main() {
    char choice;
    int data;
    printf("s : �˻� \ni : ��� �߰�\nd : ��� ����\nt : ���� ��ȸ\nI : ��� �߰�(�ݺ�)\nD : ��� ����(�ݺ�)\nc : ����\n");

    while (1) {
        printf("�޴��� �����ϼ��� (s/i/d/t/I/D/q): ");
        scanf_s(" %c", &choice);
        switch (choice) {
        case 's':
            printf("�˻��� ���� �Է��ϼ���: ");
            scanf_s("%d", &data);
            if (searchIterative(root, data) != NULL) {
                printf("��尡 �����մϴ�.\n");
            }
            else {
                printf("��尡 �������� �ʽ��ϴ�.\n");
            }
            inorder(root);
            break;
        case 'i':
            printf("������ ���� �Է��ϼ���: ");
            scanf_s("%d", &data);
            root = insert(root, data);
            printf("������ �Ϸ�Ǿ����ϴ�.\n");
            inorder(root);
            break;
        case 'd':
            printf("������ ���� �Է��ϼ���: ");
            scanf_s("%d", &data);
            root = delete(root, data);
            printf("������ �Ϸ�Ǿ����ϴ�.\n");
            inorder(root);
            break;
        case 't':
            printf("���� ��ȸ ���: ");
            inorder(root);
            printf("\n");
            break;
        case 'I':
            printf("�ݺ��� ������� ������ ���� �Է��ϼ���: ");
            scanf_s("%d", &data);
            root = insertIterative(root, data);
            printf("������ �Ϸ�Ǿ����ϴ�.\n");
            inorder(root);
            break;
        case 'D':
            printf("�ݺ��� ������� ������ ���� �Է��ϼ���: ");
            scanf_s("%d", &data);
            root = deleteIterative(root, data);
            printf("������ �Ϸ�Ǿ����ϴ�.\n");
            inorder(root);
            break;
        case 'q':
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �޴��Դϴ�. �ٽ� �Է��ϼ���.\n");
        }

        printf("���� Ʈ�� ��� ��: %d\n", countNodes(root));
    }

    return 0;
}




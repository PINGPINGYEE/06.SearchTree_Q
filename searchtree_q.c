#include <stdio.h>
#include <stdlib.h>

// 구조체 정의
typedef struct treeNode {
    int data;
    struct treeNode* left, * right;
} TreeNode;

// 노드 생성
TreeNode* newNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// 재귀적 노드 추가
TreeNode* insert(TreeNode* root, int data, int* count) {
    if (root == NULL) return newNode(data);

    (*count)++;
    if (data < root->data)
        root->left = insert(root->left, data, count);
    else if (data > root->data)
        root->right = insert(root->right, data, count);

    return root;
}

// 반복적 노드 추가
TreeNode* insertIteratively(TreeNode* root, int data, int* count) {
    TreeNode* parent = NULL;
    TreeNode* current = root;
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;

    while (current != NULL) {
        (*count)++;
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (parent == NULL)
        root = newNode;
    else if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// 노드 삭제를 위한 최소값 찾는 함수
TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// 재귀적 노드 삭제
TreeNode* deleteNode(TreeNode* root, int data, int* count) {
    if (root == NULL) return root;

    (*count)++;
    if (data < root->data)
        root->left = deleteNode(root->left, data, count);
    else if (data > root->data)
        root->right = deleteNode(root->right, data, count);
    else {
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
        TreeNode* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data, count);
    }
    return root;
}

// 반복적 노드 삭제
TreeNode* deleteNodeIteratively(TreeNode* root, int data, int* count) {
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
        (*count)++;
    }

    // 삭제할 노드를 찾지 못한 경우
    if (current == NULL) {
        
        return root;
    }

    if (current->left == NULL && current->right == NULL) {
        // 삭제할 노드가 리프 노드인 경우
        if (parent == NULL) {
            free(current);
            (*count)++;
            return NULL;
        }

        if (current == parent->left) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
        free(current);
    }
    // 삭제할 노드가 두 개의 자식 노드를 가진 경우
    else if (current->left != NULL && current->right != NULL) {
        
        TreeNode* successor = current->right;
        TreeNode* successorParent = current;

        while (successor->left != NULL) {
            (*count)++;
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
        (*count)++;
        free(successor);
    }
    // 삭제할 노드가 하나의 자식 노드만 가진 경우
    else {
        
        TreeNode* child = (current->left != NULL) ? current->left : current->right;

        if (parent == NULL) {
            return child; // 루트 노드 삭제
        }

        if (current == parent->left) {
            parent->left = child;
        }
        else {
            parent->right = child;
        }
        free(current);
    }
    (*count)++;
    return root;
}

// 재귀적 중위 순회 함수
void inorder(TreeNode* root, int* count) {
  
    if (root != NULL) {
        inorder(root->left, count);
        (*count)++;
        printf("%d ", root->data);
        inorder(root->right, count);
    }
}

// 노드 검색 함수
TreeNode* search(TreeNode* root, int data) {
    int cnt = 0;
    while (root != NULL && root->data != data) {
        if (data < root->data) {
            root = root->left;
        }
        else {
            root = root->right;
        }
        cnt++;
    }
    printf("방문한 노드 수:%d\n", cnt + 1);
    return root;
}

int main() {
    TreeNode* root = NULL;
    root = insert(root, 60, &(int){0});
    root = insert(root, 41, &(int){0});
    root = insert(root, 74, &(int){0});
    root = insert(root, 16, &(int){0});
    root = insert(root, 53, &(int){0});
    root = insert(root, 65, &(int){0});
    root = insert(root, 25, &(int){0});
    root = insert(root, 46, &(int){0});
    root = insert(root, 55, &(int){0});
    root = insert(root, 63, &(int){0});
    root = insert(root, 70, &(int){0});
    root = insert(root, 42, &(int){0});
    root = insert(root, 62, &(int){0});
    root = insert(root, 64, &(int){0});

    printf("---------------------------\n");
    printf(" s : 검색\n i : 노드 추가\n d : 노드 삭제\n t : 중위 순회\n I : 노드 추가(반복)\n D : 노드 삭제(반복)\n c : 종료\n");
    printf("---------------------------\n\n");

    while (1) {
        
        printf("메뉴입력:");
        char menu;
        scanf_s(" %c", &menu);
        if (menu == 'C') break;

        int value, count = 0;
        

        switch (menu) {
        case 's':
            printf("값 입력:");
            scanf_s("%d", &value);
            if (search(root, value))
                printf("검색 성공:%d\n", value);
            else
                printf("검색 실패:%d\n", value);
            inorder(root, &count);
            printf("\n");
            break;
        case 'i':
            printf("값 입력:");
            scanf_s("%d", &value);
            root = insert(root, value, &count);
            printf("방문한 노드 수:%d\n", count);
            inorder(root, &count);
            printf("\n");
            break;
        case 'I':
            printf("값 입력:");
            scanf_s("%d", &value);
            root = insertIteratively(root, value, &count);
            printf("방문한 노드 수:%d\n", count);
            inorder(root, &count);
            printf("\n");
            break;
        case 'd':
            printf("값 입력:");
            scanf_s("%d", &value);
            root = deleteNode(root, value, &count);
            printf("방문한 노드 수:%d\n", count);
            inorder(root, &count);
            printf("\n");
            break;
        case 'D':
            printf("값 입력:");
            scanf_s("%d", &value);
            root = deleteNodeIteratively(root, value, &count);
            printf("방문한 노드 수:%d\n", count);
            inorder(root, &count);
            printf("\n");
            break;
        case 't':
            inorder(root, &count);
            printf("\n방문한 노드 수:%d\n", count);
            printf("\n");
            break;
        case 'c':
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 메뉴 입력\n");
            continue;
        }
        
        
        printf("\n");
    }

    return 0;
}

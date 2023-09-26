#include <stdio.h>
#include <stdlib.h>


// 이진 탐색 트리 노드 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;
// 이진 탐색 트리 삽입 함수
TreeNode* insert(TreeNode* root, int data, int* visitedNodes) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        (*visitedNodes)++;
        return newNode;
    }

    if (data < root->data) {
        root->left = insert(root->left, data, visitedNodes);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data, visitedNodes);
    }
    (*visitedNodes)++;
    return root;
}

// 이진 탐색 트리에서 노드 삭제 함수
TreeNode* delete(TreeNode* root, int data, int* visitedNodes) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = delete(root->left, data, visitedNodes);
    }
    else if (data > root->data) {
        root->right = delete(root->right, data, visitedNodes);
    }
    else {
        // 삭제할 노드를 찾았을 때
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            (*visitedNodes)++;
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            (*visitedNodes)++;
            return temp;
        }

        // 두 자식 노드 모두 있는 경우
        TreeNode* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->data = temp->data;
        root->right = delete(root->right, temp->data, visitedNodes);
    }
    (*visitedNodes)++;
    return root;
}
// 이진 탐색 트리에서 노드 검색 함수
TreeNode* searchIterative(TreeNode* root, int data) {
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
    printf("방문한 노드 수 : %d\n", cnt + 1);
    return root;
}


// 이진 탐색 트리 중위 순회 함수
void inorder(TreeNode* root, int* visitedNodes) {
    if (root != NULL) {
        inorder(root->left, visitedNodes);
        printf("%d ", root->data);
        inorder(root->right, visitedNodes);
        (*visitedNodes)++;
    }
}

// 이진 트리 노드 삽입 (반복적 방법)
TreeNode* insertIterative(TreeNode* root, int data, int* visitedNodes) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    (*visitedNodes)++;

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
        (*visitedNodes)++;
    }

    if (data < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    return root;
}

// 이진 트리 노드 삭제 (반복적 방법)
TreeNode* deleteIterative(TreeNode* root, int data, int* visitedNodes) {
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
        (*visitedNodes)++;
    }

    if (current == NULL) {
        // 삭제할 노드를 찾지 못한 경우
        return root;
    }

    if (current->left == NULL && current->right == NULL) {
        // 삭제할 노드가 리프 노드인 경우
        if (parent == NULL) {
            free(current);
            (*visitedNodes)++;
            return NULL; // 루트 노드 삭제
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
        // 삭제할 노드가 두 개의 자식 노드를 가진 경우
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
        // 삭제할 노드가 하나의 자식 노드만 가진 경우
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

    return root;
}

int countNodes(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("메모리 할당 오류\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int main() {
    char choice;
    int data;
    int visitedNodes; // 방문한 노드 수

    TreeNode* n12 = createNode(42);
    TreeNode* n13 = createNode(62);
    TreeNode* n14 = createNode(64);
    TreeNode* n7 = createNode(25);
    TreeNode* n8 = createNode(46);
    TreeNode* n9 = createNode(55);
    TreeNode* n10 = createNode(63);
    TreeNode* n11 = createNode(70);
    TreeNode* n4 = createNode(16);
    TreeNode* n5 = createNode(53);
    TreeNode* n6 = createNode(65);
    TreeNode* n2 = createNode(41);
    TreeNode* n3 = createNode(74);
    TreeNode* n1 = createNode(60);

    // 노드들을 연결
    n8->left = n12;
    n5->left = n8;
    n5->right = n9;
    n10->left = n13;
    n10->right = n14;
    n6->left = n10;
    n6->right = n11;
    n2->left = n4;
    n2->right = n5;
    n3->left = n6;
    n1->left = n2;
    n1->right = n3;
    n4->right = n7;

    // 루트 노드 설정
    TreeNode* root = n1;

    printf("s : 검색 \ni : 노드 추가\nd : 노드 삭제\nt : 중위 순회\nI : 노드 추가(반복)\nD : 노드 삭제(반복)\nq : 종료\n");

    while (1) {
        visitedNodes = 0; // 방문한 노드 수 초기화

        printf("메뉴를 선택하세요 (s/i/d/t/I/D/q): ");
        scanf_s(" %c", &choice);
        switch (choice) {
        case 's':
            printf("검색할 값을 입력하세요: ");
            scanf_s("%d", &data);
            if (searchIterative(root, data, &visitedNodes) != NULL) {
                printf("노드가 존재합니다.\n");
            }
            else {
                printf("노드가 존재하지 않습니다.\n");
            }
            inorder(root, &visitedNodes);
            break;
        case 'i':
            printf("삽입할 값을 입력하세요: ");
            scanf_s("%d", &data);
            root = insert(root, data, &visitedNodes);
            printf("삽입이 완료되었습니다.\n");
           
            inorder(root, &visitedNodes);
            printf("방문한 노드 수: %d\n", visitedNodes - 1);
            break;
        case 'd':
            printf("삭제할 값을 입력하세요: ");
            scanf_s("%d", &data);
            root = delete(root, data, &visitedNodes);
            printf("삭제가 완료되었습니다.\n");
            printf("방문한 노드 수: %d\n", visitedNodes);
            inorder(root, &visitedNodes);
            
            break;
        case 't':
            printf("중위 순회 결과: ");
            inorder(root, &visitedNodes);
            printf("방문한 노드 수: %d\n", visitedNodes);
            printf("\n");
            break;
        case 'I':
            printf("반복적 방법으로 삽입할 값을 입력하세요: ");
            scanf_s("%d", &data);
            root = insertIterative(root, data, &visitedNodes);
            printf("삽입이 완료되었습니다.\n");
            printf("방문한 노드 수: %d\n", visitedNodes - 1);
            inorder(root, &visitedNodes);
            break;
        case 'D':
            printf("반복적 방법으로 삭제할 값을 입력하세요: ");
            scanf_s("%d", &data);
            root = deleteIterative(root, data, &visitedNodes);
            printf("삭제가 완료되었습니다.\n");
            printf("방문한 노드 수: %d\n", visitedNodes);
            inorder(root, &visitedNodes);
            break;
        case 'c':
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 메뉴입니다. 다시 입력하세요.\n");
        }

        
    }

    return 0;
}

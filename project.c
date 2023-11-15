/* STUDENT GRADEBOOK MANAGER FOR PLACEMENTS IMPLEMENTED USING BINARY SEARCH TREES */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
    int id;
    char name[50];
    float cgpa;
} Student;

typedef struct NODE {
    Student data;
    struct NODE* left;
    struct NODE* right;
} NODE;

NODE* createNODE(Student data) {
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

NODE* insertNODE(NODE* root, Student data) {
    if (root == NULL) {
        return createNODE(data);
    }
    if (data.id < root->data.id) {
        root->left = insertNODE(root->left, data);
    } else if (data.id > root->data.id) {
        root->right = insertNODE(root->right, data);
    }
    return root;
}

NODE* buildBSTFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    NODE* root = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        Student s;
        sscanf(line, "%d,%49[^,],%f", &s.id, s.name, &s.cgpa);
        root = insertNODE(root, s);
    }
    fclose(file);
    return root;
}


NODE* findMinNode(NODE* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

NODE* deleteNode(NODE* root, int id) {
    if (root == NULL) {
        return root;
    }

    if (id < root->data.id) {
        root->left = deleteNode(root->left, id);
    } else if (id > root->data.id) {
        root->right = deleteNode(root->right, id);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            NODE* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            NODE* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest
        // in the right subtree)
        NODE* temp = findMinNode(root->right);

        // Copy the inorder successor's data to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data.id);
    }
    return root;
}


NODE* search(NODE *root, int id)
{
    if (root == NULL || root->data.id == id)
        return root;
    if (id < root->data.id)
        return search(root->left, id);
    if (id > root->data.id)
        return search(root->right, id);
}


void update(NODE *root, int id)
{
    NODE *temp = search(root, id);
    if (temp == NULL)
        printf("Student not found\n");
    else
    {
        printf("Enter new cgpa: ");
        scanf("%f", &temp->data.cgpa);
        printf("New cgpa of student %d = %f\n", temp->data.id, temp->data.cgpa);
    }
}


void inOrderTraversalWithCondition(NODE* root, float lowerBound, float upperBound, float targetCGPA, int operation) {
    if (root != NULL) {
        inOrderTraversalWithCondition(root->left, lowerBound, upperBound, targetCGPA, operation);

        switch (operation) {
            case 4: // cutoff cgpa
                if (root->data.cgpa >= lowerBound) {
                    printf("ID: %d, Name: %s, CGPA: %.2f\n", root->data.id, root->data.name, root->data.cgpa);
                }
                break;

            case 3: // CGPA range
                if (root->data.cgpa >= lowerBound && root->data.cgpa <= upperBound) {
                    printf("ID: %d, Name: %s, CGPA: %.2f\n", root->data.id, root->data.name, root->data.cgpa);
                }
                break;

            case 2: // Specific CGPA
                if (root->data.cgpa == targetCGPA) {
                    printf("ID: %d, Name: %s, CGPA: %.2f\n", root->data.id, root->data.name, root->data.cgpa);
                }
                break;

            case 1: // Regular traversal
                printf("ID: %d, Name: %s, CGPA: %.2f\n", root->data.id, root->data.name, root->data.cgpa);
        }

        inOrderTraversalWithCondition(root->right, lowerBound, upperBound, targetCGPA, operation);
    }
}


int main() {
    const char* filename = "data.csv";
    NODE* root = buildBSTFromFile(filename);

    int ch,ch1,id;
    float lower,upper,above,target;
    while(1)
    {
        printf("\n1.Display students records\n");
        printf("2.Delete student\n");
        printf("3.Search student record\n");
        printf("4.Update student record\n");
        printf("5.Exit\n");
        
        printf("Enter your choice: ");
        scanf("%d",&ch);
        switch (ch)
        {
        case 1: //display students
            printf("1. All students\n2. Specific CGPA\n3. CGPA Range\n4.Cutoff CGPA\n");
            printf("enter your choice: ");
            scanf("%d",&ch1);
            switch(ch1)
            {
                case 1: //all students
                    printf("\nList of all students:\n");
                    inOrderTraversalWithCondition(root,0,0,0,1);
                    break;

                case 2: //specific cgpa
                    printf("Enter required cgpa: ");
                    scanf("%f",&target);
                    inOrderTraversalWithCondition(root,0,0,target,2);
                    break;
                    
                case 3: //cgpa range
                    printf("Enter lower bound and upper bound\n");
                    scanf("%f%f",&lower,&upper);
                    inOrderTraversalWithCondition(root,lower,upper,0,3);
                    break;

                case 4: //cutoff cgpa
                    printf("Enter cutoff cgpa: ");
                    scanf("%f",&above);
                    inOrderTraversalWithCondition(root,above,0,0,4);
                    break;

                default:
                printf("Invalid case\n");
                    break;
            }
            break;
        
        case 2://delete student
        printf("Enter student ID: ");
        scanf("%d",&id);
        deleteNode(root,id);
        break;

        case 3://search student 
            printf("Enter student ID: ");
            scanf("%d", &id);
            NODE* temp = search(root,id);
            if (temp == NULL)
                printf("Student Not Found\n");
            else
                printf("Student details:\nID: %d\nName: %s\nCGPA: %f\n", temp->data.id, temp->data.name, temp->data.cgpa);
            break;

        case 4: // update student record
            printf("Enter student ID to update: ");
            scanf("%d", &id);
            update(root,id);
            break;

        case 5: //exit program
        exit(0);

        default: //invalid case
        printf("Invalid case\n");
            break;
        }
    }
    return 0;
}

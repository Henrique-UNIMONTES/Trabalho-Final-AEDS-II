#include "Quicksort.h"

// Stores the current index method of the Quick Sort algorithm
int searchMode = 0;

// Stores the memory accesses count of the ABB algorithm
int quickAccess = 0;

// Stores the search stack path of the ABB algorithm
String *quickSearchStackTree;

int parseIdNumber(char *id) {
    int ans = 0;
    for (int i = 1; i < strlen(id); i++) {
        ans *= 10;
        ans += '0' + id[i];
    }

    return ans;
}

int partition(ResumedTitle *arr, int low, int high) {
    ResumedTitle pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (searchMode == 1) {
            int id1 = parseIdNumber(arr[j].id), id2 = parseIdNumber(pivot.id);

            // arr[j] < pivot
            if (id1 < id2) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }

        else if (searchMode == 2) {
            int len1 = strlen(arr[j].title), len2 = strlen(pivot.title);
            int cmp = strncmp(arr[j].title, pivot.title, len1 > len2 ? len2 : len1);

            if (cmp == 0 && len1 < len2) cmp = -1;

            if (cmp < 0) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }

        else {
            printf("Search mode not supported.");
            exit(1);
        }
    }
    
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(ResumedTitle *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void swap(ResumedTitle* a, ResumedTitle* b) {
    ResumedTitle t = *a;
    *a = *b;
    *b = t;
}

int binarySearch(ResumedTitle *arr, int low, int high, char *id) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        quickAccess++;
        pushString(quickSearchStackTree, '[');

        if (searchMode == 1) {
            for (int i = 0; i < strlen(arr[mid].id); i++) {
                pushString(quickSearchStackTree, arr[mid].id[i]);
            }

            pushString(quickSearchStackTree, ']');
            pushString(quickSearchStackTree, ' ');
            pushString(quickSearchStackTree, '-');
            pushString(quickSearchStackTree, '>');
            pushString(quickSearchStackTree, ' ');

            int id1 = parseIdNumber(arr[mid].id), id2 = parseIdNumber(id);

            if (id1 == id2) return arr[mid].index;

            if (id1 < id2) low = mid + 1;

            else high = mid - 1;
        }

        else {
            for (int i = 0; i < strlen(arr[mid].title); i++) {
                pushString(quickSearchStackTree, arr[mid].title[i]);
            }

            pushString(quickSearchStackTree, ']');
            pushString(quickSearchStackTree, ' ');
            pushString(quickSearchStackTree, '-');
            pushString(quickSearchStackTree, '>');
            pushString(quickSearchStackTree, ' ');

            int len1 = strlen(arr[mid].title), len2 = strlen(id);
            int cmp = strncmp(arr[mid].title, id, len1 > len2 ? len2 : len1);

            if (cmp == 0 && len1 < len2) cmp = -1;

            if (cmp == 0) return arr[mid].index;

            if (cmp < 0) low = mid + 1;

            else high = mid - 1;
        }
    }

    return -1;
}

int initializeQuickSort() {
    int op;

    do {
        printf("What kind of search you would like do perform?\n");
        printf("[1] - By ID\n");
        printf("[2] - By Title\n");
        printf("[3] - Perform the default search\n");
        printf("[4] - None (Back to main menu)\n");
        scanf("%d", &op);
        clearBuffer();

        if (op < 1 || op > 4) {
            printf("\nInvalid option\n\n");
        }

        else break;
    } while (TRUE);

    if (op == 4) {
        printf("\n");
        return FALSE;
    }

    searchMode = op;
    if (searchMode == 3) searchMode = 1;

    printf("Sorting the data...\n");
    quickSort(quick_sort_vector, 0, titles_size - 1);
    printf("Data sorted.\n\n");

    char op2;

    if (op == 3) {
        int ids[4] = { 1, titles_size - 1, (titles_size - 1) / 2, titles_size - 2 };

        for (int i = 0; i < 4; i++) {
            quickSearchStackTree = createString();

            char id[6];
            sprintf(id, "s%d", ids[i]);

            printf("\nStarting search for the node with ID: %s\n\n", id);
            printf("Initial time : ");
            time_t initialTime = showTime();

            int index = binarySearch(quick_sort_vector, 0, titles_size - 1, id);

            printf("Final time   : ");
            time_t finalTime = showTime();

            printf("Total time   : %ld second(s)\n\n", finalTime - initialTime);

            printf("Total memory accesses: %d\n\n", quickAccess);

            printf("Search stack path:\n");
            printf("[BEGIN] -> ");
            printString(quickSearchStackTree);
            printf("[END]\n\n");

            printLine();

            clearString(quickSearchStackTree);
        }
    }

    else {
        do {
            quickSearchStackTree = createString();

            if (searchMode == 1) {
                int id;

                while (TRUE) {
                    printf("Informe o ID para realizar a busca: [1 - 8807]\ns");
                    scanf("%d", &id);
                    clearBuffer();

                    if (id < 1 || id > 8807) {
                        printf("ID inválido\n\n");
                    }

                    else {
                        break;
                    }
                }

                char ans[6];
                ans[0] = 's';

                if (id < 10) {
                    ans[1] = '0' + id;
                    ans[2] = '\0';
                }

                else if (id < 100) {
                    ans[1] = '0' + id / 10;
                    ans[2] = '0' + id % 10;
                    ans[3] = '\0';
                }

                else if (id < 1000) {
                    ans[1] = '0' + id / 100;
                    ans[2] = '0' + (id % 100) / 10;
                    ans[3] = '0' + (id % 100) % 10;
                    ans[4] = '\0';
                }

                else {
                    ans[1] = '0' + id / 1000;
                    ans[2] = '0' + (id % 1000) / 100;
                    ans[3] = '0' + ((id % 1000) % 100) / 10;
                    ans[4] = '0' + ((id % 1000) % 100) % 10;
                    ans[5] = '\0';
                }

                printf("\nStarting search for the node with ID: %s\n\n", ans);
                printf("Initial time : ");
                time_t initialTime = showTime();

                int index = binarySearch(quick_sort_vector, 0, titles_size - 1, ans);

                printf("Final time   : ");
                time_t finalTime = showTime();

                printf("Total time   : %ld second(s)\n\n", finalTime - initialTime);

                printf("Total memory accesses: %d\n\n", quickAccess);

                if (index != -1) {
                    Title t;
                    deserializeModel(&t, index);
                    printModel(t);
                    printf("\n\n");
                }

                else printf("Node not found\n\n");

                printf("Search stack path:\n");
                printf("[BEGIN] -> ");
                printString(quickSearchStackTree);
                printf("[END]\n\n");

                printLine();

                printf("Do you wanna make another ID search? [Y/n]\n");
                scanf("%c", &op2);
                clearBuffer();
            }

            else {
                char title[51];
                printf("This search looks finds the first title that matches with the search string.\n");
                printf("Enter the title you wanna to search for: [MAX LENGTH = 50]\n");
                scanf("%50[^\n]", title);
                clearBuffer();
                printf("\n");

                for (int j = 0; j < strlen(title); j++) {
                    title[j] = tolower(title[j]);
                }

                printf("\nStarting search for the node with title: %s\n\n", title);
                printf("Initial time : ");
                time_t initialTime = showTime();

                int index = binarySearch(quick_sort_vector, 0, titles_size - 1, title);

                printf("Final time   : ");
                time_t finalTime = showTime();

                printf("Total time   : %ld second(s)\n\n", finalTime - initialTime);

                printf("Total memory accesses: %d\n\n", quickAccess);

                if (index != -1) {
                    Title t;
                    deserializeModel(&t, index);
                    printModel(t);
                    printf("\n\n");
                }

                else printf("Node not found\n\n");

                printf("Search stack path:\n");
                printf("[BEGIN] -> ");
                printString(quickSearchStackTree);
                printf("[END]\n\n");

                printLine();

                printf("Do you wanna make another title search? [Y/n]\n");
                scanf("%c", &op2);
                clearBuffer();
            }

            clearString(quickSearchStackTree);
        } while (op2 == 'Y' || op2 == 'y');
    }

    printf("\nDo you wanna make another type of search? [Y/n]\n");
    scanf("%c", &op2);
    printf("\n");

    if (op2 == 'Y' || op2 == 'y') {
        return TRUE;
    }

    return FALSE;
}

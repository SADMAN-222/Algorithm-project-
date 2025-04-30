#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int start;
    int end;
    int priority;
    float resource_required;
    float resource_allocated;
} Event;


typedef struct {
    float total_quantity;
} Resource;

void merge(Event arr[], int l, int m, int r, char key) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    Event* L = (Event*)malloc(n1 * sizeof(Event));
    Event* R = (Event*)malloc(n2 * sizeof(Event));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        int comparison;
        if (key == 'p') {
            comparison = L[i].priority > R[j].priority;
        } else {
            comparison = L[i].start < R[j].start;
        }

        if (comparison) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(Event arr[], int l, int r, char key) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m, key);
        mergeSort(arr, m + 1, r, key);

        merge(arr, l, m, r, key);
    }
}

void fractionalKnapsack(Event events[], int n, float total_resources) {
    float allocated_resources = 0.0;

    for (int i = 0; i < n; i++) {
        if (allocated_resources + events[i].resource_required <= total_resources) {
            events[i].resource_allocated = events[i].resource_required;
            allocated_resources += events[i].resource_required;
        } else {
            float fraction = (total_resources - allocated_resources) / events[i].resource_required;
            events[i].resource_allocated = events[i].resource_required * fraction;
            allocated_resources = total_resources;
            break;
        }
    }
}


int main() {
    int n;
    float total_resources;

    printf("Enter the number of events: ");
    scanf("%d", &n);

    Event* events = (Event*)malloc(n * sizeof(Event));

    for (int i = 0; i < n; i++) {
        printf("Enter start time, end time, priority, and resource required for event %d: ", i + 1);
        scanf("%d %d %d %f", &events[i].start, &events[i].end, &events[i].priority, &events[i].resource_required);
        events[i].resource_allocated = 0;
    }

    printf("Enter the total available resources: ");
    scanf("%f", &total_resources);


    mergeSort(events, 0, n - 1, 'p');

    fractionalKnapsack(events, n, total_resources);

    printf("\n+-------+-------+----------+-------------+-------------+-------------+\n");
    printf("| Event | Start |   End    |   Priority  |  Required   |  Allocated  |\n");
    printf("+-------+-------+----------+-------------+-------------+-------------+\n");
    for (int i = 0; i < n; i++) {
        printf("|  %2d   |  %4d |  %6d  |    %6d   |    %7.2f   |    %7.2f   |\n",
               i + 1, events[i].start, events[i].end, events[i].priority, events[i].resource_required, events[i].resource_allocated);
        printf("+-------+-------+----------+-------------+-------------+-------------+\n");
    }

    free(events);
    return 0;
}

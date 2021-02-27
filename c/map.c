#include <stdio.h>

typedef enum {
    ecu_a = 0,
    ecu_b,
    ecu_c,
    ecu_d,
    ecu_e
} Index;

int data[5] = {0};
int temp_data[5] = {1, 2, 3, 4, 5};

Index map_a[] = {ecu_a, ecu_c, ecu_e};
Index map_b[] = {ecu_b, ecu_d};


void print_data() {
    for (int i = 0; i < 5; i++) {
        printf("data[%d] = %d\n", i, data[i]);
    }
}

void set_map_a() {
    int array_size = sizeof(map_a) / sizeof(map_a[0]);

    for (int i = 0; i < array_size; i++) {
        data[map_a[i]] = temp_data[map_a[i]];
    }

    print_data();
}

void reset_map_a() {

}


int main() {
    set_map_a();

    return 0;
}
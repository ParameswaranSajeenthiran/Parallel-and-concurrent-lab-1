//
// Unit tests for linked list operations
// gcc test_linkedlist.c linkedList.c -o test && ./test
//

#include <stdio.h>
#include <assert.h>

#include "../../linkedList.h"

// =================== TESTS ===================

void testInsert() {
    struct Node* head = NULL;

    // Insert into empty list
    assert(Insert(10, &head) == 1);
    assert(Member(10, head) == 1);

    // Insert smaller (new head)
    assert(Insert(5, &head) == 1);
    assert(Member(5, head) == 1);

    // Insert larger (tail)
    assert(Insert(20, &head) == 1);
    assert(Member(20, head) == 1);

    // Insert in middle
    assert(Insert(15, &head) == 1);
    assert(Member(15, head) == 1);

    // Insert duplicate
    assert(Insert(10, &head) == 0);

    printf("✅ testInsert passed!\n");
}

void testMember() {
    struct Node* head = NULL;

    // Setup list: 5 -> 10 -> 20
    Insert(5, &head);
    Insert(10, &head);
    Insert(20, &head);

    // Check existing
    assert(Member(5, head) == 1);
    assert(Member(10, head) == 1);
    assert(Member(20, head) == 1);

    // Check non-existing
    assert(Member(1, head) == 0);
    assert(Member(15, head) == 0);
    assert(Member(25, head) == 0);

    printf("✅ testMember passed!\n");
}

void testDelete() {
    struct Node* head = NULL;

    // Setup list: 5 -> 10 -> 20
    Insert(5, &head);
    Insert(10, &head);
    Insert(20, &head);

    // Delete head
    assert(Delete(5, &head) == 1);
    assert(Member(5, head) == 0);

    // Delete middle
    assert(Delete(10, &head) == 1);
    assert(Member(10, head) == 0);

    // Delete tail
    assert(Delete(20, &head) == 1);
    assert(Member(20, head) == 0);

    // Delete from empty
    assert(Delete(100, &head) == 0);

    printf("✅ testDelete passed!\n");
}
//
// int main() {
//     testInsert();
//     testMember();
//     testDelete();
//
//     printf("\n🎉 All tests passed successfully!\n");
//     return 0;
// }
// //

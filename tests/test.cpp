#include <gtest/gtest.h>

TEST(StudentListTest, RemoveDuplicatesTest) {
    LinkedList list;
    list._head = new Node("Иванов", "Иван", 3, 4.5);
    list._head->next = new Node("Петров", "Петр", 1, 3.2);
    list._head->next->next = new Node("Сидоров", "Сидор", 2, 4.0);
    list._head->next->next->next = new Node("Иванов", "Иван", 3, 4.5); 
    list._head->next->next->next->next = new Node("Петров", "Петр", 1, 3.2); 
    list.removeDuplicates();

    EXPECT_EQ(list._head->lastName, "Иванов");
    EXPECT_EQ(list._head->firstName, "Иван");
    EXPECT_EQ(list._head->course, 3);
    EXPECT_EQ(list._head->averageScore, 4.5);

    EXPECT_EQ(list._head->next->lastName, "Петров");
    EXPECT_EQ(list._head->next->firstName, "Петр");
    EXPECT_EQ(list._head->next->course, 1);
    EXPECT_EQ(list._head->next->averageScore, 3.2);

    EXPECT_EQ(list._head->next->next->lastName, "Сидоров");
    EXPECT_EQ(list._head->next->next->firstName, "Сидор");
    EXPECT_EQ(list._head->next->next->course, 2);
    EXPECT_EQ(list._head->next->next->averageScore, 4.0);

    EXPECT_EQ(list._head->next->next->next, nullptr);
}
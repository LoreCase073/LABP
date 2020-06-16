#include "gtest/gtest.h"
#include "..\Users\lorec\source\repos\LABP\Project1\Date.h"

TEST(Date, CreateRegularDate) {
    Date d = Date(20,10,2005);
    ASSERT_EQ(20, d.getDay());
    ASSERT_EQ(10, d.getMonth());
    ASSERT_EQ(2005, d.getYear());

    Date d2 = Date(29, 2, 2004);
    ASSERT_EQ(29, d2.getDay());
    ASSERT_EQ(2, d2.getMonth());
    ASSERT_EQ(2004, d2.getYear());

}


TEST(Date, CreateWrongMonth1) {
    //mese superiore a 12
    EXPECT_THROW(Date d = Date(20, 13, 2006),range_error);
    EXPECT_THROW(Date d = Date(20, 25, 2006), range_error);

}


TEST(Date, CreateWrongMonth2) {
    //mese inferiore a 1
    EXPECT_THROW(Date d = Date(20, 0, 2006), range_error);
    EXPECT_THROW(Date d = Date(20, -5, 2006), range_error);

}


TEST(Date, CreateWrongDay) {
    EXPECT_THROW(Date d = Date(29, 2, 2006), range_error);
    EXPECT_THROW(Date d = Date(32, 1, 2006), range_error);
    EXPECT_THROW(Date d = Date(0, 1, 2006), range_error);

}

TEST(Date, CreateWrongYear) {
    EXPECT_THROW(Date d = Date(5, 2, 1800), range_error);
    EXPECT_THROW(Date d = Date(1, 1, -2000), range_error);

}
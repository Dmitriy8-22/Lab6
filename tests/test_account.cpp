#include <gtest/gtest.h>
#include <stdexcept>
#include "Account.h"

TEST(AccountTest, ConstructorSetsValues) {
    Account acc(5, 1000);
    EXPECT_EQ(acc.id(), 5);
    EXPECT_EQ(acc.GetBalance(), 1000);
}

TEST(AccountTest, GetBalanceReturnsCurrentBalance) {
    Account acc(1, 500);
    EXPECT_EQ(acc.GetBalance(), 500);
}

TEST(AccountTest, ChangeBalanceWorksWhenLocked) {
    Account acc(1, 1000);
    acc.Lock();
    acc.ChangeBalance(300);
    EXPECT_EQ(acc.GetBalance(), 1300);
}

TEST(AccountTest, ChangeBalanceThrowsWhenNotLocked) {
    Account acc(1, 1000);
    EXPECT_THROW(acc.ChangeBalance(100), std::runtime_error);
    EXPECT_EQ(acc.GetBalance(), 1000);
}

TEST(AccountTest, LockThrowsWhenAlreadyLocked) {
    Account acc(1, 1000);
    EXPECT_NO_THROW(acc.Lock());
    EXPECT_THROW(acc.Lock(), std::runtime_error);
    EXPECT_NO_THROW(acc.ChangeBalance(100));
    EXPECT_EQ(acc.GetBalance(), 1100);
}

TEST(AccountTest, UnlockAllowsLockAgain) {
    Account acc(1, 1000);
    acc.Lock();
    acc.Unlock();
    EXPECT_NO_THROW(acc.Lock());
}

TEST(AccountTest, MultipleLockUnlockCycles) {
    Account acc(1, 1000);
    for (int i = 0; i < 3; i++) {
        acc.Lock();
        acc.ChangeBalance(100);
        acc.Unlock();
    }
    EXPECT_EQ(acc.GetBalance(), 1300);
}

TEST(AccountTest, UnlockRequiresLockAgain) {
    Account acc(1, 1000);
    acc.Lock();
    acc.ChangeBalance(100);
    acc.Unlock();
    EXPECT_THROW(acc.ChangeBalance(50), std::runtime_error);
}

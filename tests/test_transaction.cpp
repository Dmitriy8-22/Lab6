#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>

#include "Transaction.h"
#include "mock_account.h"

using ::testing::Return;
using ::testing::_;

TEST(TransactionTest, NegativeSumThrowsException) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction transaction;

    EXPECT_THROW(transaction.Make(from, to, -50), std::invalid_argument);
}

TEST(TransactionTest, SumLessThan100ThrowsException) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction transaction;

    EXPECT_THROW(transaction.Make(from, to, 50), std::logic_error);
}

TEST(TransactionTest, SameAccountThrowsException) {
    MockAccount acc(1, 1000);
    Transaction transaction;

    EXPECT_THROW(transaction.Make(acc, acc, 100), std::logic_error);
}

TEST(TransactionTest, FeeTooHighReturnsFalse) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction transaction;
    transaction.set_fee(150);

    bool result = transaction.Make(from, to, 200);
    EXPECT_FALSE(result);
}

TEST(TransactionTest, SuccessfulTransaction) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction transaction;

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(200)).Times(1);
    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(1000))
        .WillOnce(Return(799));
    EXPECT_CALL(from, ChangeBalance(-201)).Times(1);
    EXPECT_CALL(to, GetBalance()).WillOnce(Return(700));
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    bool result = transaction.Make(from, to, 200);
    EXPECT_TRUE(result);
}

TEST(TransactionTest, RollbackOnDebitFailure) {
    MockAccount from(1, 100);
    MockAccount to(2, 500);
    Transaction transaction;

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(200)).Times(1);
    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(100))
        .WillOnce(Return(100));
    EXPECT_CALL(to, ChangeBalance(-200)).Times(1);
    EXPECT_CALL(to, GetBalance()).WillOnce(Return(500));
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    bool result = transaction.Make(from, to, 200);
    EXPECT_FALSE(result);
}

TEST(TransactionTest, DefaultFeeIsOne) {
    Transaction transaction;
    EXPECT_EQ(transaction.fee(), 1);
}

TEST(TransactionTest, SetAndGetFee) {
    Transaction transaction;
    transaction.set_fee(10);
    EXPECT_EQ(transaction.fee(), 10);
    transaction.set_fee(0);
    EXPECT_EQ(transaction.fee(), 0);
}

TEST(TransactionTest, CreditAddsBalance) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;

    transaction.Make(from, to, 200);
    EXPECT_EQ(to.GetBalance(), 700);
}

TEST(TransactionTest, DebitSubtractsBalance) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;

    transaction.Make(from, to, 200);
    EXPECT_EQ(from.GetBalance(), 799);
}

TEST(TransactionTest, SaveToDataBaseOutput) {
    Account from(1, 1000);
    Account to(2, 500);
    Transaction transaction;

    testing::internal::CaptureStdout();
    transaction.Make(from, to, 200);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("1 send to 2 $200"), std::string::npos);
    EXPECT_NE(output.find("Balance 1 is"), std::string::npos);
    EXPECT_NE(output.find("Balance 2 is"), std::string::npos);
}

TEST(TransactionTest, TransactionWithExactBalance) {
    Account from(1, 201);
    Account to(2, 500);
    Transaction transaction;

    bool result = transaction.Make(from, to, 200);

    EXPECT_TRUE(result);
    EXPECT_EQ(from.GetBalance(), 0);
    EXPECT_EQ(to.GetBalance(), 700);
}

TEST(TransactionTest, TransactionWithMinimumSum) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction transaction;

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(100)).Times(1);
    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(1000))
        .WillOnce(Return(899));
    EXPECT_CALL(from, ChangeBalance(-101)).Times(1);
    EXPECT_CALL(to, GetBalance()).WillOnce(Return(600));
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    bool result = transaction.Make(from, to, 100);
    EXPECT_TRUE(result);
}

TEST(TransactionTest, InsufficientFundsReturnsFalse) {
    MockAccount from(1, 100);
    MockAccount to(2, 500);
    Transaction transaction;

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(200)).Times(1);
    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(100))
        .WillOnce(Return(100));
    EXPECT_CALL(to, ChangeBalance(-200)).Times(1);
    EXPECT_CALL(to, GetBalance()).WillOnce(Return(500));
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    bool result = transaction.Make(from, to, 200);
    EXPECT_FALSE(result);
}

TEST(TransactionTest, VerifyLockAndUnlockOrder) {
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    Transaction transaction;

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, ChangeBalance(200)).Times(1);
    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(1000))
        .WillOnce(Return(799));
    EXPECT_CALL(from, ChangeBalance(-201)).Times(1);
    EXPECT_CALL(to, GetBalance()).WillOnce(Return(700));
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    bool result = transaction.Make(from, to, 200);
    EXPECT_TRUE(result);
}

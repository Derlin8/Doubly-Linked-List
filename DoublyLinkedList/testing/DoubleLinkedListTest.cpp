//
// Created by mfbut on 2/14/2019.
//

#include <sstream>
#include <string>
#include <cstdlib>
#include <type_traits>
#include "DoubleLinkedListTest.h"
#include "DoublyLinkedListError.h"
#include "DoublyLinkedListOutOfBoundsError.h"
#include "DoublyLinkedListEmptyError.h"
#include "gmock/gmock.h"

using TestTypes = ::testing::Types<int, std::string>;
TYPED_TEST_SUITE(DoubleLinkedListTest, TestTypes);

TYPED_TEST(DoubleLinkedListTest, EmptyConstructor) {
  DoublyLinkedList<TypeParam> dll;
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, std::vector<TypeParam>()));
}

template<>
std::vector<int> DoubleLinkedListTest<int>::constructorArgs{1, 2, 3, 4, 5, 6};

template<>
std::vector<std::string> DoubleLinkedListTest<std::string>::constructorArgs{"bob", "cat", "sally", "man"};

TYPED_TEST(DoubleLinkedListTest, VectorConstructor) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, TestFixture::constructorArgs));
}

template<>
std::vector<int> DoubleLinkedListTest<int>::pushFrontArgs{10, 20, 30, 40};

template<>
std::vector<std::string> DoubleLinkedListTest<std::string>::pushFrontArgs{"apple", "bear", "cat", "dog"};

template<>
std::vector<int> DoubleLinkedListTest<int>::pushBackArgs{100, 200, 300, 400, 500};

template<>
std::vector<std::string>
    DoubleLinkedListTest<std::string>::pushBackArgs{"help", "investigate", "joust", "kick", "learn"};

TYPED_TEST(DoubleLinkedListTest, PushFront_Once) {
  DoublyLinkedList<TypeParam> dll;
  dll.push_front(TestFixture::pushFrontArgs.at(0));
  ASSERT_EQ(dll.front(), TestFixture::pushFrontArgs.front());
}

TYPED_TEST(DoubleLinkedListTest, PushFront_Once_HeadAndTailSameAfter) {
  DoublyLinkedList<TypeParam> dll;
  dll.push_front(TestFixture::pushFrontArgs.at(0));
  ASSERT_EQ(dll.front(), TestFixture::pushFrontArgs.front());
  ASSERT_EQ(dll.back(), TestFixture::pushFrontArgs.front());
  ASSERT_EQ(dll.front(), dll.back());
}

TYPED_TEST(DoubleLinkedListTest, PushBack_Once) {
  DoublyLinkedList<TypeParam> dll;
  dll.push_back(TestFixture::pushBackArgs.at(0));
  ASSERT_EQ(dll.back(), TestFixture::pushBackArgs.front());
}

TYPED_TEST(DoubleLinkedListTest, PushBack_Once_HeadAndTailSameAfter) {
  DoublyLinkedList<TypeParam> dll;
  dll.push_back(TestFixture::pushBackArgs.at(0));
  ASSERT_EQ(dll.front(), TestFixture::pushBackArgs.front());
  ASSERT_EQ(dll.back(), TestFixture::pushBackArgs.front());
  ASSERT_EQ(dll.front(), dll.back());
}

TYPED_TEST(DoubleLinkedListTest, PushFront_MultiplePushes) {
  DoublyLinkedList<TypeParam> dll;
  for (auto itr = TestFixture::pushFrontArgs.crbegin();
       itr != TestFixture::pushFrontArgs.crend(); ++itr) {
    dll.push_front(*itr);
    ASSERT_EQ(dll.front(), *itr);
  }
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, TestFixture::pushFrontArgs));
}

TYPED_TEST(DoubleLinkedListTest, PushBack_MultiplePushes) {
  DoublyLinkedList<TypeParam> dll;
  for (auto itr = TestFixture::pushBackArgs.cbegin();
       itr != TestFixture::pushBackArgs.cend(); ++itr) {
    dll.push_back(*itr);
    ASSERT_EQ(dll.back(), *itr);
  }
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, TestFixture::pushBackArgs));
}

TYPED_TEST(DoubleLinkedListTest, PushFront_PushBack_Interleaved) {
  DoublyLinkedList<TypeParam> dll;
  std::vector<TypeParam> answerVector;

  auto frontArgsItr = TestFixture::pushFrontArgs.cbegin(),
      backArgsItr = TestFixture::pushBackArgs.cbegin();

  for (;
      frontArgsItr != TestFixture::pushFrontArgs.cend() &&
          backArgsItr != TestFixture::pushBackArgs.cend(); ++backArgsItr) {
    answerVector.insert(answerVector.begin(), *frontArgsItr);
    dll.push_front(*frontArgsItr);
    answerVector.push_back(*backArgsItr);
    dll.push_back(*backArgsItr);
    ASSERT_EQ(dll.front(), answerVector.front());
    ASSERT_EQ(dll.back(), answerVector.back());
  }

  //handle leftovers
  for (; frontArgsItr != TestFixture::pushFrontArgs.cend(); ++frontArgsItr) {
    answerVector.insert(answerVector.begin(), *frontArgsItr);
    dll.push_front(*frontArgsItr);
    ASSERT_EQ(dll.front(), answerVector.front());
    ASSERT_EQ(dll.back(), answerVector.back());
  }

  //handle leftovers
  for (; backArgsItr != TestFixture::pushBackArgs.cend(); ++backArgsItr) {
    answerVector.insert(answerVector.begin(), *backArgsItr);
    dll.push_front(*backArgsItr);
    ASSERT_EQ(dll.front(), answerVector.front());
    ASSERT_EQ(dll.back(), answerVector.back());
  }

  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, answerVector));
}

TYPED_TEST(DoubleLinkedListTest, Erase_FirstElement) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  std::vector<TypeParam> ansVec(TestFixture::constructorArgs);

  auto dllItr = dll.begin();
  dll.erase(dllItr);
  ansVec.erase(ansVec.begin());

  ASSERT_EQ(dll.front(), ansVec.front());
  ASSERT_EQ(dll.back(), ansVec.back());
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
}

TYPED_TEST(DoubleLinkedListTest, Erase_LastElement) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  std::vector<TypeParam> ansVec(TestFixture::constructorArgs);

  auto dllItr = dll.begin();
  auto vecItr = ansVec.begin();

  iterateForward(dllItr, dll.size() - 1);
  iterateForward(vecItr, dll.size() - 1);
  dll.erase(dllItr);
  ansVec.erase(vecItr);

  ASSERT_EQ(dll.front(), ansVec.front());
  ASSERT_EQ(dll.back(), ansVec.back());
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
}

TYPED_TEST(DoubleLinkedListTest, Erase_SecondElement) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  std::vector<TypeParam> ansVec(TestFixture::constructorArgs);

  auto dllItr = dll.begin();
  auto vecItr = ansVec.begin();

  iterateForward(dllItr, 1);
  iterateForward(vecItr, 1);

  dll.erase(dllItr);
  ansVec.erase(vecItr);

  ASSERT_EQ(dll.front(), ansVec.front());
  ASSERT_EQ(dll.back(), ansVec.back());
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
}

TYPED_TEST(DoubleLinkedListTest, Erase_BecomeEmpty) {
  DoublyLinkedList<TypeParam> dll;

  dll.push_front(TestFixture::pushFrontArgs.front());
  auto dllItr = dll.begin();
  dll.erase(dllItr);

  ASSERT_EQ(dll.size(), 0);
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, std::vector<TypeParam>()));
}

TYPED_TEST(DoubleLinkedListTest, Erase_UntilEmpty) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  std::vector<TypeParam> ansVec(TestFixture::constructorArgs);

  srand(0);
  for (unsigned int i = 0; i < TestFixture::constructorArgs.size(); ++i) {
    auto dllItr = dll.begin();
    auto vecItr = ansVec.begin();
    //pick position to delete
    const int pos2Delete = rand() % ansVec.size();

    //advance to delete position
    iterateForward(dllItr, pos2Delete);
    iterateForward(vecItr, pos2Delete);

    //delete the element
    dll.erase(dllItr);
    ansVec.erase(vecItr);

    //check everything is ok
    if (ansVec.size() > 0) {
      ASSERT_EQ(dll.front(), ansVec.front());
      ASSERT_EQ(dll.back(), ansVec.back());
    }
    ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
  }
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
}

TYPED_TEST(DoubleLinkedListTest, Insert_FirstElement) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  std::vector<TypeParam> ansVec(TestFixture::constructorArgs);

  auto dllItr = dll.begin();
  dll.insert(dllItr, TestFixture::pushFrontArgs.front());
  ansVec.insert(ansVec.begin(), TestFixture::pushFrontArgs.front());

  ASSERT_EQ(dll.front(), ansVec.front());
  ASSERT_EQ(dll.back(), ansVec.back());
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
}

TYPED_TEST(DoubleLinkedListTest, Insert_LastElement) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  std::vector<TypeParam> ansVec(TestFixture::constructorArgs);

  auto dllItr = dll.end();
  auto vecItr = ansVec.end();

  dll.insert(dllItr, TestFixture::pushFrontArgs.front());
  ansVec.insert(vecItr, TestFixture::pushFrontArgs.front());

  ASSERT_EQ(dll.front(), ansVec.front());
  ASSERT_EQ(dll.back(), ansVec.back());
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
}

TYPED_TEST(DoubleLinkedListTest, Insert_IntoEmpty) {
  DoublyLinkedList<TypeParam> dll;
  std::vector<TypeParam> ansVec;

  auto dllItr = dll.begin();
  dll.insert(dllItr, TestFixture::pushFrontArgs.front());
  ansVec.insert(ansVec.begin(), TestFixture::pushFrontArgs.front());

  ASSERT_EQ(dll.front(), ansVec.front());
  ASSERT_EQ(dll.back(), ansVec.back());
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
}

TYPED_TEST(DoubleLinkedListTest, Insert_Randomly) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  std::vector<TypeParam> ansVec(TestFixture::constructorArgs);

  srand(0);
  for (unsigned int i = 0; i < TestFixture::pushFrontArgs.size(); ++i) {
    auto dllItr = dll.begin();
    auto vecItr = ansVec.begin();
    //pick position to delete
    const int pos2Insert = rand() % ansVec.size();
    //advance to delete position

    iterateForward(dllItr, pos2Insert);
    iterateForward(vecItr, pos2Insert);

    //insert the element
    dll.insert(dllItr, TestFixture::pushFrontArgs.at(i));
    ansVec.insert(vecItr, TestFixture::pushFrontArgs.at(i));

    //check everything is ok
    if (ansVec.size() > 0) {
      ASSERT_EQ(dll.front(), ansVec.front());
      ASSERT_EQ(dll.back(), ansVec.back());
    }
    ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
  }
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
}

TYPED_TEST(DoubleLinkedListTest, Insert_Erase_Randomly) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  std::vector<TypeParam> ansVec(TestFixture::constructorArgs);
  std::vector<TypeParam> valuesToInsert(TestFixture::pushFrontArgs);

  srand(0);

  constexpr int shouldInsert = 0;
  //constexpr int shouldDelete = 1;

  while (!valuesToInsert.empty()) {
    int action = rand() % 2;
    const unsigned int position = rand() % ansVec.size();
    auto dllItr = dll.begin();
    auto vecItr = ansVec.begin();

    iterateForward(dllItr, position);
    iterateForward(vecItr, position);

    if (ansVec.empty()) {
      action = shouldInsert;
    }

    if (action == shouldInsert) {
      dll.insert(dllItr, valuesToInsert.back());
      ansVec.insert(vecItr, valuesToInsert.back());
      valuesToInsert.pop_back();
    } else {
      dll.erase(dllItr);
      ansVec.erase(vecItr);
    }
    ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
  }

  while (!ansVec.empty()) {
    auto dllItr = dll.begin();
    auto vecItr = ansVec.begin();
    //pick position to delete
    const int pos2Delete = rand() % ansVec.size();

    //advance to delete position
    iterateForward(dllItr, pos2Delete);
    iterateForward(vecItr, pos2Delete);

    //delete the element
    dll.erase(dllItr);
    ansVec.erase(vecItr);

    //check everything is ok
    ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
  }
  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
}

TYPED_TEST(DoubleLinkedListTest, CastToBool) {
  DoublyLinkedList<TypeParam> emptyList;
  DoublyLinkedList<TypeParam> nonEmptyList(TestFixture::constructorArgs);

  ASSERT_EQ(static_cast<bool>(emptyList.begin()), false);
  ASSERT_EQ(static_cast<bool>(emptyList.end()), false);
  ASSERT_EQ(static_cast<bool>(emptyList.crbegin()), false);
  ASSERT_EQ(static_cast<bool>(emptyList.crend()), false);

  ASSERT_EQ(static_cast<bool>(nonEmptyList.end()), false);
  ASSERT_EQ(static_cast<bool>(nonEmptyList.crend()), false);

  auto fItr = nonEmptyList.begin();
  auto rItr = nonEmptyList.crbegin();
  for (unsigned int i = 0; i < TestFixture::constructorArgs.size(); ++i) {
    ASSERT_EQ(static_cast<bool>(fItr), true);
    ASSERT_EQ(static_cast<bool>(rItr), true);
    ++fItr;
    ++rItr;
  }
  ASSERT_EQ(static_cast<bool>(fItr), false);
  ASSERT_EQ(static_cast<bool>(rItr), false);
}

TYPED_TEST(DoubleLinkedListTest, ForwardIterator_decrement) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  std::vector<TypeParam> ansVec(TestFixture::constructorArgs);

  auto dllItr = dll.begin();
  auto vecItr = ansVec.begin();

  iterateForward(dllItr, ansVec.size() - 1);
  iterateForward(vecItr, ansVec.size() - 1);

  for (int i = ansVec.size() - 1; i >= 0; --i) {
    ASSERT_EQ(*dllItr, *vecItr);
    --dllItr;
    --vecItr;
  }
}

TYPED_TEST(DoubleLinkedListTest, ReverseIterator_decrement) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  std::vector<TypeParam> ansVec(TestFixture::constructorArgs);

  auto dllItr = dll.crbegin();
  auto vecItr = ansVec.crbegin();

  iterateForward(dllItr, ansVec.size() - 1);
  iterateForward(vecItr, ansVec.size() - 1);

  for (int i = ansVec.size() - 1; i >= 0; --i) {
    ASSERT_EQ(*dllItr, *vecItr);
    --dllItr;
    --vecItr;
  }
}

TYPED_TEST(DoubleLinkedListTest, ForwardIterator_ModifyValues) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  std::vector<TypeParam> ansVec(TestFixture::constructorArgs);

  auto dllItr = dll.begin();
  auto vecItr = ansVec.begin();

  for (; vecItr != ansVec.end();) {
    *dllItr += TestFixture::constructorArgs.front();
    *vecItr += TestFixture::constructorArgs.front();
    ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
    ++vecItr;
    ++dllItr;
  }
}

TYPED_TEST(DoubleLinkedListTest, InstreamCheck) {
  DoublyLinkedList<TypeParam> dll;
  std::vector<TypeParam> ansVec;
  std::stringstream in1("1 2 cat man pig");
  std::stringstream in2("1 2 cat man pig");

  in1 >> dll;
  in2 >> ansVec;

  ASSERT_TRUE(dllAndVectorMatch<TypeParam>(dll, ansVec));
}

TYPED_TEST(DoubleLinkedListTest, ThrowsOnEmpty) {
  DoublyLinkedList<TypeParam> dll;
  ASSERT_THROW(dll.front(), DoublyLinkedListEmptyError);
  ASSERT_THROW(dll.back(), DoublyLinkedListEmptyError);
}

TYPED_TEST(DoubleLinkedListTest, ThrowsAtEnd) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  ASSERT_THROW(*dll.end(), DoublyLinkedListOutOfBoundsError);
  ASSERT_THROW(*dll.rend(), DoublyLinkedListOutOfBoundsError);
  ASSERT_THROW(*dll.crend(), DoublyLinkedListOutOfBoundsError);
}

TYPED_TEST(DoubleLinkedListTest, ThrowsBeforeBeginning) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  auto fitr = dll.begin();
  auto ritr = dll.rbegin();
  --fitr;
  --ritr;
  ASSERT_THROW(*fitr, DoublyLinkedListOutOfBoundsError);
  ASSERT_THROW(*ritr, DoublyLinkedListOutOfBoundsError);
}

TYPED_TEST(DoubleLinkedListTest, ThrowsGoingPastEnd) {
  DoublyLinkedList<TypeParam> dll(TestFixture::constructorArgs);
  auto fitr = dll.begin();
  auto ritr = dll.rbegin();
  while(fitr != dll.end()){ ++fitr;}
  while(ritr != dll.rend()){++ritr;}

  ASSERT_THROW(*fitr, DoublyLinkedListOutOfBoundsError);
  ASSERT_THROW(*ritr, DoublyLinkedListOutOfBoundsError);
}

TEST(InheritanceChecking, EmptyErrorInherits){
  ASSERT_TRUE((std::is_base_of<DoublyLinkedListError, DoublyLinkedListEmptyError>::value));
}

TEST(InheritanceChecking, OutOfBoundsErrorInherits){
  ASSERT_TRUE((std::is_base_of<DoublyLinkedListError, DoublyLinkedListOutOfBoundsError>::value));
}

TEST(InheritanceChecking, DoublyLinkedListErrorInherits){
  ASSERT_TRUE((std::is_base_of<std::exception, DoublyLinkedListError>::value));
}

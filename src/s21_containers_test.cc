#include "s21_containers.h"

#include <gtest/gtest.h>

#include <queue>
#include <stack>

#include "s21_containersplus.h"

//_________________>>VECTOR>>____________________________________

TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> v;

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, SizeConstructor_1) {
  size_t n = 5;
  s21::vector<int> v(n);

  EXPECT_EQ(v.size(), n);
  EXPECT_GE(v.capacity(), n);
  EXPECT_FALSE(v.empty());
}

TEST(VectorTest, InitializerListConstructor) {
  std::initializer_list<int> items = {1, 2, 3};
  s21::vector<int> v(items);

  EXPECT_EQ(v.size(), 3);
  EXPECT_GE(v.capacity(), 3);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(v1);

  EXPECT_EQ(v2.size(), v1.size());
  EXPECT_EQ(v2.capacity(), v1.capacity());
  EXPECT_EQ(v2[0], v1[0]);
  EXPECT_EQ(v2[1], v1[1]);
  EXPECT_EQ(v2[2], v1[2]);
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(std::move(v1));

  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
  EXPECT_EQ(v1.size(), 0);
}

TEST(VectorTest, CopyAssignment) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2;
  v2 = v1;

  EXPECT_EQ(v2.size(), v1.size());
  EXPECT_EQ(v2.capacity(), v1.capacity());
  EXPECT_EQ(v2[0], v1[0]);
  EXPECT_EQ(v2[1], v1[1]);
  EXPECT_EQ(v2[2], v1[2]);
}

TEST(VectorTest, MoveAssignment) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2;
  v2 = std::move(v1);

  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
  EXPECT_EQ(v1.size(), 0);
}

TEST(VectorTest, Destructor) {
  { s21::vector<int> v = {1, 2, 3}; }
}

TEST(VectorTest, At) {
  s21::vector<int> v = {1, 2, 3};

  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(1), 2);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_THROW(v.at(3), std::out_of_range);
}

TEST(VectorTest, OperatorBracket) {
  s21::vector<int> v = {1, 2, 3};

  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, Front) {
  s21::vector<int> v = {1, 2, 3};

  EXPECT_EQ(v.front(), 1);
}

TEST(VectorTest, Back) {
  s21::vector<int> v = {1, 2, 3};

  EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, Data) {
  s21::vector<int> v = {1, 2, 3};

  int *data = v.data();

  EXPECT_EQ(*data, 1);
  EXPECT_EQ(*(data + 1), 2);
  EXPECT_EQ(*(data + 2), 3);
}

TEST(VectorTest, Begin) {
  s21::vector<int> v = {1, 2, 3};

  EXPECT_EQ(*v.begin(), 1);
}

TEST(VectorTest, End) {
  s21::vector<int> v = {1, 2, 3};

  EXPECT_EQ(*(v.end() - 1), 3);
}

TEST(VectorTest, Empty) {
  s21::vector<int> v;

  EXPECT_TRUE(v.empty());

  v.push_back(1);

  EXPECT_FALSE(v.empty());
}

TEST(VectorTest, Size) {
  s21::vector<int> v;

  EXPECT_EQ(v.size(), 0);

  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_EQ(v.size(), 3);
}

TEST(VectorTest, MaxSize) {
  s21::vector<int> v;

  EXPECT_LE(v.max_size(),
            std::numeric_limits<typename s21::vector<int>::size_type>::max());
}

TEST(VectorTest, Reserve) {
  s21::vector<int> v;

  v.reserve(10);

  EXPECT_GE(v.capacity(), 10);
}

TEST(VectorTest, Capacity) {
  s21::vector<int> v;

  EXPECT_EQ(v.capacity(), 0);

  v.reserve(10);

  EXPECT_GE(v.capacity(), 10);
}

TEST(VectorTest, ShrinkToFit) {
  s21::vector<int> v = {1, 2, 3};

  v.reserve(10);
  v.shrink_to_fit();

  EXPECT_EQ(v.capacity(), 3);
}

TEST(VectorTest, Clear) {
  s21::vector<int> v = {1, 2, 3};

  v.clear();

  EXPECT_EQ(v.size(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Insert) {
  s21::vector<int> v = {1, 2, 3};

  s21::vector<int>::iterator it = v.insert(v.begin() + 1, 5);

  EXPECT_EQ(*it, 5);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 5);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 3);
}

TEST(VectorTest, Erase) {
  s21::vector<int> v = {1, 2, 3};

  auto it = v.begin() + 1;
  v.erase(it);

  EXPECT_EQ(*(v.begin() + 1), 3);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, PushBack) {
  s21::vector<int> v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PopBack) {
  s21::vector<int> v = {1, 2, 3};

  v.pop_back();

  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, Swap) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 2);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[1], 5);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);
}

TEST(S21VectorTest, InsertManyTest) {
  s21::vector<int> vec;

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  auto it = vec.insert_many(vec.begin() + 1, 4, 5, 6);

  ASSERT_EQ(vec.size(), 6);
  ASSERT_EQ(vec[1], 4);
  ASSERT_EQ(vec[2], 5);
  ASSERT_EQ(vec[3], 6);
  ASSERT_EQ(*it, 2);
}

TEST(S21VectorTest, InsertManyEmptyTest) {
  s21::vector<int> vec;

  vec.insert_many(vec.begin(), 1, 2, 3);

  ASSERT_EQ(vec.size(), 3);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
}

TEST(S21VectorTest, InsertManyAtEndTest) {
  s21::vector<int> vec;

  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  vec.insert_many(vec.end(), 4, 5, 6);

  ASSERT_EQ(vec.size(), 6);
  ASSERT_EQ(vec[3], 4);
  ASSERT_EQ(vec[4], 5);
  ASSERT_EQ(vec[5], 6);
}

TEST(S21VectorTest, InsertManyAtBeginningTest) {
  s21::vector<int> vec;

  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);

  vec.insert_many(vec.begin(), 1, 0);

  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 0);
  ASSERT_EQ(vec[2], 2);
  ASSERT_EQ(vec[3], 3);
  ASSERT_EQ(vec[4], 4);
}

TEST(S21VectorTest, InsertManyInMiddleTest) {
  s21::vector<int> vec;

  vec.push_back(1);
  vec.push_back(5);
  vec.push_back(6);

  vec.insert_many(vec.begin() + 1, 2, 3, 4);

  ASSERT_EQ(vec.size(), 6);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 4);
  ASSERT_EQ(vec[4], 5);
  ASSERT_EQ(vec[5], 6);
}

TEST(InsertManyBackTest, InsertSingleArg) {
  s21::vector<int> vec;

  vec.push_back(1);
  vec.insert_many_back(4);

  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 4);
}

TEST(InsertManyBackTest, InsertMultipleArgs) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};

  vec.insert_many_back(1, 2, 3, 4, 5);

  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 4);
  ASSERT_EQ(vec[4], 5);
  ASSERT_EQ(vec[5], 1);
  ASSERT_EQ(vec[6], 2);
  ASSERT_EQ(vec[7], 3);
  ASSERT_EQ(vec[8], 4);
  ASSERT_EQ(vec[9], 5);
}

//__________________<<VECTOR<<____________________

//__________________>>SET>>_______________________

TEST(SetTest, DefaultConstructor) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(0, s.size());
}

TEST(SetTest, InitializerListConstructor) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(3, s.size());
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTest, CopyConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, MoveConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(std::move(s1));
  EXPECT_EQ(3, s2.size());
  EXPECT_TRUE(s1.empty());
}

TEST(SetTest, Destructor) {
  s21::set<int> *s = new s21::set<int>({1, 2, 3});
  delete s;
  EXPECT_TRUE(true);
}

TEST(SetTest, MoveAssignmentOperator) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {4, 5, 6};
  s2 = std::move(s1);
  EXPECT_EQ(3, s2.size());
  EXPECT_FALSE(s1.empty());
}

TEST(SetTest, Begin) {
  s21::set<int> s = {1, 2, 3};
  s21::set<int>::iterator it = s.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
}

TEST(SetTest, End) {
  s21::set<int> s = {1, 2, 3};
  s.end();
}

TEST(SetTest, Empty) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  s.insert(1);
  EXPECT_FALSE(s.empty());
}

TEST(SetTest, Size) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(3, s.size());
}

TEST(SetTest, MaxSize) {
  s21::set<int> s;
  EXPECT_GE(s.max_size(), 0);
}

TEST(SetTest, Clear) {
  s21::set<int> s = {1, 2, 3};
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(0, s.size());
}

TEST(SetTest, Insert) {
  s21::set<int> s;
  std::pair<s21::set<int>::iterator, bool> result = s.insert(1);
  EXPECT_TRUE(result.second);
  EXPECT_TRUE(s.contains(1));
  EXPECT_EQ(1, *(result.first));
  result = s.insert(1);
  EXPECT_FALSE(result.second);
  EXPECT_EQ(1, *(result.first));
}

TEST(SetTest, Erase) {
  s21::set<int> s = {1, 2, 3};
  s21::set<int>::iterator it = s.find(2);
  s.erase(it);
  EXPECT_FALSE(s.contains(2));
}

TEST(SetTest, Swap) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {4, 5, 6};
  s1.swap(s2);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Merge) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {4, 5, 6};
  s1.merge(s2);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(3));
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, Find) {
  s21::set<int> s = {1, 2, 3};
  s21::set<int>::iterator it = s.find(2);
  EXPECT_EQ(2, *it);
}

TEST(SetTest, Contains) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_TRUE(s.contains(1));
  EXPECT_FALSE(s.contains(4));
}

TEST(InsertManyTest, Empty) {
  s21::set<int> s;
  insert_many(s);
  EXPECT_TRUE(s.empty());
}

TEST(InsertManyTest, SingleElement) {
  s21::set<int> s;
  insert_many(s, 1);
  EXPECT_EQ(s.size(), 1);
}

TEST(InsertManyTest, MultipleElements) {
  s21::set<int> s;
  insert_many(s, 1, 2, 3);
  EXPECT_EQ(s.size(), 3);
}

TEST(InsertManyTest, DifferentTypes) {
  s21::set<std::string> s;
  insert_many(s, "hello", "world", "!");
  EXPECT_EQ(s.size(), 3);
}

//_________________<<SET<<__________________

//_________________>>MAP>>__________________

TEST(MapTest, DefaultConstructor) {
  s21::map<int, int> m;
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, InitializerListConstructor) {
  s21::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m[1], 10);
  EXPECT_EQ(m[2], 20);
  EXPECT_EQ(m[3], 30);
  EXPECT_THROW(m.at(4), std::out_of_range);
}

TEST(MapTest, CopyConstructor) {
  s21::map<int, int> m1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int> m2(m1);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1[1], m2[1]);
  EXPECT_EQ(m1[2], m2[2]);
  EXPECT_EQ(m1[3], m2[3]);
}

TEST(MapTest, MoveConstructor) {
  s21::map<int, int> m1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int> m2(std::move(m1));
  EXPECT_EQ(m2.size(), 3);
  EXPECT_EQ(m2[1], 10);
  EXPECT_EQ(m2[2], 20);
  EXPECT_EQ(m2[3], 30);
  EXPECT_TRUE(m1.empty());
  EXPECT_EQ(m1.size(), 0);
}

TEST(MapTest, Destructor) {
  s21::map<int, int> *m = new s21::map<int, int>{{1, 10}, {2, 20}, {3, 30}};
  delete m;
}

TEST(MapTest, AssignmentOperatorMove) {
  s21::map<int, int> m1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int> m2;
  m2 = std::move(m1);
  EXPECT_EQ(m2.size(), 3);
  EXPECT_EQ(m2[1], 10);
  EXPECT_EQ(m2[2], 20);
  EXPECT_EQ(m2[3], 30);
  EXPECT_TRUE(m1.empty());
  EXPECT_EQ(m1.size(), 0);
}

TEST(MapTest, At) {
  s21::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(m.at(1), 10);
  EXPECT_EQ(m.at(2), 20);
  EXPECT_EQ(m.at(3), 30);
  EXPECT_THROW(m.at(4), std::out_of_range);
}

TEST(MapTest, IndexOperator) {
  s21::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(m[1], 10);
  EXPECT_EQ(m[2], 20);
  EXPECT_EQ(m[3], 30);
  m[1] = 100;
  m[4] = 40;
  EXPECT_EQ(m[1], 100);
  EXPECT_EQ(m[4], 40);
}

TEST(MapTest, Iterator) {
  s21::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int>::iterator it = m.begin();
  EXPECT_EQ((*it).first, 1);
  EXPECT_EQ((*it).second, 10);
  ++it;
  EXPECT_EQ((*it).first, 2);
  EXPECT_EQ((*it).second, 20);
  ++it;
  EXPECT_EQ((*it).first, 3);
  EXPECT_EQ((*it).second, 30);
  ++it;
  EXPECT_EQ(it, m.end());
}

TEST(MapTest, Empty) {
  s21::map<int, int> m;
  EXPECT_TRUE(m.empty());
  m.insert({1, 10});
  EXPECT_FALSE(m.empty());
  m.erase(m.begin());
  EXPECT_TRUE(m.empty());
}

TEST(MapTest, Size) {
  s21::map<int, int> m;
  EXPECT_EQ(m.size(), 0);
  m.insert({1, 10});
  m.insert({2, 20});
  m.insert({3, 30});
  EXPECT_EQ(m.size(), 3);
  m.erase(m.begin());
  EXPECT_EQ(m.size(), 2);
  m.clear();
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, MaxSize) {
  s21::map<int, int> m;
  EXPECT_GT(m.max_size(), 0);
}

TEST(MapTest, Clear) {
  s21::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.size(), 3);
  m.clear();
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, InsertValue) {
  s21::map<int, int> m;
  auto res = m.insert({1, 10});
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->data.first, 1);
  EXPECT_EQ(res.first->data.second, 10);
  res = m.insert({1, 20});
  EXPECT_FALSE(res.second);
  EXPECT_EQ(res.first->data.first, 1);
  EXPECT_EQ(res.first->data.second, 10);
}

TEST(MapTest, InsertKeyValue) {
  s21::map<int, int> m;
  auto res = m.insert(1, 10);
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->data.first, 1);
  EXPECT_EQ(res.first->data.second, 10);
  res = m.insert(1, 20);
  EXPECT_FALSE(res.second);
  EXPECT_EQ(res.first->data.first, 1);
  EXPECT_EQ(res.first->data.second, 10);
}

TEST(MapTest, InsertOrAssign) {
  s21::map<int, int> m;
  auto res = m.insert_or_assign(1, 10);
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->data.first, 1);
  EXPECT_EQ(res.first->data.second, 10);
  res = m.insert_or_assign(1, 20);
  EXPECT_FALSE(res.second);
  EXPECT_EQ(res.first->data.first, 1);
  EXPECT_EQ(res.first->data.second, 20);
}

TEST(MapTest, Erase) {
  s21::map<int, int> m;
  m.insert({1, 10});
  m.insert({2, 20});
  m.insert({3, 30});
  EXPECT_EQ(m.size(), 3);
  m.erase(m.begin());
  EXPECT_EQ(m.size(), 2);
}

TEST(MapTest, Swap) {
  s21::map<int, int> m1 = {{1, 10}, {2, 20}};
  s21::map<int, int> m2 = {{3, 30}, {4, 40}};
  m1.swap(m2);
  EXPECT_EQ(m1.size(), 2);
  EXPECT_EQ(m1[3], 30);
  EXPECT_EQ(m1[4], 40);
  EXPECT_EQ(m2.size(), 2);
  EXPECT_EQ(m2[1], 10);
  EXPECT_EQ(m2[2], 20);
}

TEST(MapTest, Merge) {
  s21::map<int, int> m1 = {{1, 10}, {2, 20}};
  s21::map<int, int> m2 = {{2, 30}, {3, 40}};
  m1.merge(m2);
  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m1[1], 10);
  EXPECT_EQ(m1[2], 20);
  EXPECT_EQ(m1[3], 40);
  EXPECT_EQ(m2.size(), 0);
}

TEST(MapTest, Contains) {
  s21::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_TRUE(m.contains(3));
  EXPECT_FALSE(m.contains(4));
}

TEST(MapTest, InsertManyTest) {
  s21::map<int, std::string> myMap;
  insert_many(myMap, std::make_pair(1, "one"), std::make_pair(2, "two"),
              std::make_pair(3, "three"));

  EXPECT_EQ(myMap.size(), 3);
  EXPECT_EQ(myMap[1], "one");
  EXPECT_EQ(myMap[2], "two");
  EXPECT_EQ(myMap[3], "three");
}

TEST(MapTest, InsertManyDuplicateTest) {
  s21::map<int, std::string> myMap;
  insert_many(myMap, std::make_pair(1, "one"), std::make_pair(1, "uno"),
              std::make_pair(2, "two"));

  EXPECT_EQ(myMap.size(), 2);
  EXPECT_EQ(myMap[1], "one");
  EXPECT_EQ(myMap[2], "two");
}

TEST(MapTest, InsertManyDuplicateKeyTest) {
  s21::map<int, std::string> myMap;
  insert_many(myMap, std::make_pair(1, "one"), std::make_pair(1, "uno"),
              std::make_pair(2, "two"));

  EXPECT_EQ(myMap.size(), 2);
  EXPECT_EQ(myMap[1], "one");
  EXPECT_EQ(myMap[2], "two");
}

TEST(MapTest, InsertManyEmptyTest) {
  s21::map<int, std::string> myMap;
  insert_many(myMap);

  EXPECT_TRUE(myMap.empty());
}

TEST(MapTest, InsertManyEmptyKeyTest) {
  s21::map<int, std::string> myMap;
  insert_many(myMap, std::make_pair(1, "one"), std::make_pair(2, "two"),
              std::make_pair(0, "zero"));

  EXPECT_EQ(myMap.size(), 3);
  EXPECT_EQ(myMap[0], "zero");
}

TEST(MapTest, InsertManyLargeKeyTest) {
  s21::map<int, std::string> myMap;
  insert_many(myMap, std::make_pair(999999999, "large"),
              std::make_pair(1000000000, "huge"));

  EXPECT_EQ(myMap.size(), 2);
  EXPECT_EQ(myMap[999999999], "large");
  EXPECT_EQ(myMap[1000000000], "huge");
}

TEST(MapTest, InsertManyRvalueTest) {
  s21::map<int, std::string> myMap;
  std::string value = "test";
  insert_many(myMap, std::make_pair(1, std::move(value)));

  EXPECT_EQ(myMap.size(), 1);
  EXPECT_EQ(myMap[1], "test");
  EXPECT_TRUE(value.empty());
}

TEST(MapTest, InsertManyEmptyTest_2) {
  s21::map<int, std::string> myMap;
  insert_many(myMap);

  EXPECT_TRUE(myMap.empty());
}

//__________________<<MAP<<__________________

//___________________>>ARRAY>>_______________

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 3> arr = {1, 2, 3};
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(3, arr.size());
}

TEST(ArrayTest, ListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(5, arr.size());
  EXPECT_EQ(1, arr.front());
  EXPECT_EQ(5, arr.back());
  EXPECT_EQ(1, arr[0]);
  EXPECT_EQ(5, arr[4]);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2(arr1);
  EXPECT_EQ(3, arr2.size());
  EXPECT_EQ(1, arr2[0]);
  EXPECT_EQ(3, arr2[2]);
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2(std::move(arr1));
  EXPECT_FALSE(arr1.empty());
  EXPECT_EQ(3, arr1.size());
  EXPECT_EQ(3, arr2.size());
  EXPECT_EQ(1, arr2[0]);
  EXPECT_EQ(3, arr2[2]);
}

TEST(ArrayTest, Destructor) { s21::array<int, 3> arr = {1, 2, 3}; }

TEST(ArrayTest, AssignmentOperatorMove) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2;
  arr2 = std::move(arr1);
  EXPECT_FALSE(arr1.empty());
  EXPECT_EQ(3, arr1.size());
  EXPECT_EQ(3, arr2.size());
  EXPECT_EQ(1, arr2[0]);
  EXPECT_EQ(3, arr2[2]);
}

TEST(ArrayTest, AccessOperator) {
  s21::array<int, 3> arr = {1, 2, 3};
  EXPECT_EQ(1, arr.at(0));
  EXPECT_EQ(2, arr[1]);
  EXPECT_EQ(1, arr.front());
  EXPECT_EQ(3, arr.back());
}

TEST(ArrayTest, Iterator) {
  s21::array<int, 3> arr = {1, 2, 3};
  s21::array<int, 3>::iterator it = arr.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  it++;
  EXPECT_EQ(3, *it);
  ++it;
  EXPECT_EQ(arr.end(), it);
}

TEST(ArrayTest, Fill) {
  s21::array<int, 5> arr;
  arr.fill(42);
  EXPECT_EQ(42, arr[0]);
  EXPECT_EQ(42, arr[4]);
}

TEST(ArrayTest, Swap) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2 = {4, 5, 6};
  arr1.swap(arr2);
  EXPECT_EQ(3, arr1.size());
  EXPECT_EQ(4, arr1[0]);
  EXPECT_EQ(5, arr1[1]);
  EXPECT_EQ(3, arr2.size());
  EXPECT_EQ(1, arr2[0]);
  EXPECT_EQ(2, arr2[1]);
}

//__________________<<ARRAY<<__________________

//___________________>>MULTISET>>______________

TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> ms;

  EXPECT_EQ(ms.size(), 0);
  EXPECT_TRUE(ms.empty());
}

TEST(MultisetTest, InitializerListConstructor) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  EXPECT_EQ(ms.size(), 4);
}

TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2(ms1);

  EXPECT_EQ(ms2.size(), 3);
}

TEST(MultisetTest, MoveConstructor) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2(std::move(ms1));

  EXPECT_EQ(ms2.size(), 3);
}

TEST(MultisetTest, Destructor) { s21::multiset<int> ms = {1, 2, 3}; }

TEST(MultisetTest, MoveAssignmentOperator) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2;
  ms2 = std::move(ms1);

  EXPECT_EQ(ms2.size(), 3);
}

TEST(MultisetTest, BeginEnd) {
  s21::multiset<int> ms = {1, 2, 3};

  int i = 1;
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    EXPECT_EQ(*it, i);
    ++i;
  }
}

TEST(MultisetTest, Empty) {
  s21::multiset<int> ms;

  EXPECT_TRUE(ms.empty());

  ms.insert(1);

  EXPECT_FALSE(ms.empty());
}

TEST(MultisetTest, Size) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  EXPECT_EQ(ms.size(), 4);

  ms.erase(ms.begin());

  EXPECT_EQ(ms.size(), 3);
}

TEST(MultisetTest, MaxSize) {
  s21::multiset<int> ms;

  EXPECT_EQ(ms.max_size(), std::numeric_limits<size_t>::max());
}

TEST(MultisetTest, Clear) {
  s21::multiset<int> ms = {1, 2, 3};
  ms.clear();

  EXPECT_TRUE(ms.empty());
}

TEST(MultisetTest, Insert) {
  s21::multiset<int> ms;
  auto it = ms.insert(10);

  EXPECT_EQ(*it, 10);

  it = ms.insert(20);
  it = ms.insert(30);

  EXPECT_EQ(*it, 30);
}

TEST(MultisetTest, Erase) {
  s21::multiset<int> ms = {1, 2, 2, 3};
  ms.erase(ms.begin());

  EXPECT_EQ(ms.size(), 3);

  ms.erase(ms.find(2));

  EXPECT_EQ(ms.size(), 2);
}

TEST(MultisetTest, Swap) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = {4, 5, 6};

  ms1.swap(ms2);

  EXPECT_EQ(ms1.size(), 3);
  EXPECT_EQ(ms2.size(), 3);
}

TEST(MultisetTest, Merge) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = {4, 5, 6};

  ms1.merge(ms2);

  EXPECT_EQ(ms1.size(), 6);
  EXPECT_EQ(ms2.size(), 0);
}

TEST(MultisetTest, Count) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(4), 0);
  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(3), 1);
}

TEST(MultisetTest, Find) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  auto it = ms.find(2);
  EXPECT_EQ(*it, 2);

  it = ms.find(4);
  EXPECT_EQ(it, ms.end());
}

TEST(MultisetTest, Contains) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  EXPECT_TRUE(ms.contains(2));
  EXPECT_FALSE(ms.contains(4));
}

TEST(MultiSetTest, EqualRange) {
  s21::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  ms.insert(3);
  ms.insert(4);

  auto range1 = ms.equal_range(5);
  EXPECT_EQ(range1.first, range1.second);
  EXPECT_EQ(range1.first, ms.end());

  auto range2 = ms.equal_range(2);
  EXPECT_EQ(*range2.first, 2);
  EXPECT_EQ(*range2.second, 3);

  s21::multiset<int> empty_ms;
  auto range3 = empty_ms.equal_range(1);
  EXPECT_EQ(range3.first, range3.second);
}

TEST(MultisetTest, LowerBound) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  auto it = ms.lower_bound(2);
  EXPECT_EQ(*it, 2);

  it = ms.lower_bound(4);
  EXPECT_EQ(it, ms.end());
}

TEST(MultisetTest, UpperBound) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  auto it = ms.upper_bound(2);
  EXPECT_EQ(*it, 3);

  it = ms.upper_bound(4);
  EXPECT_EQ(it, ms.end());
}

TEST(InsertManyTest, InsertMultipleElements) {
  s21::multiset<int> ms;
  insert_many(ms, 4, 2, 6, 2, 8);
  std::vector<int> expected = {2, 2, 4, 6, 8};
  ASSERT_EQ(ms.size(), expected.size());
  for (const auto &elem : expected) {
    ASSERT_TRUE(ms.contains(elem));
  }
}

TEST(InsertManyTest, InsertElementsOfDifferentTypes) {
  s21::multiset<std::string> ms;
  insert_many(ms, "cat", "dog", "elephant");
  std::vector<std::string> expected = {"cat", "dog", "elephant"};
  ASSERT_EQ(ms.size(), expected.size());
  for (const auto &elem : expected) {
    ASSERT_TRUE(ms.contains(elem));
  }
}

TEST(InsertManyTest, InsertSingleElement) {
  s21::multiset<double> ms;
  double num = 3.14;
  insert_many(ms, num);
  ASSERT_EQ(ms.size(), 1);
  ASSERT_TRUE(ms.contains(num));
}

TEST(InsertManyTest, InsertEmptyArguments) {
  s21::multiset<int> ms;
  insert_many(ms);
  ASSERT_EQ(ms.size(), 0);
}

//__________________<<MULTISET<<_______________

//__________________>>List>>___________________
TEST(ListTest, DefaultConstructor) {
  s21::list<int> list;
  EXPECT_EQ(list.size(), 0U);
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, MoveAssignmentOperator) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  s21::list<int> list2;
  list2 = std::move(list1);

  EXPECT_TRUE(list1.empty());

  ASSERT_EQ(list2.size(), 3U);
  int expected_values2[] = {1, 2, 3};
  auto i = 0;
  for (auto it = list2.begin(); it != list2.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected_values2[i]);
  }
}

TEST(ListTest, CopyAssignmentOperator) {
  s21::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  s21::list<int> list2;
  list2 = list1;

  ASSERT_EQ(list1.size(), 3U);
  int expected_values1[] = {1, 2, 3};
  int i = 0;
  for (auto it = list1.begin(); it != list1.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected_values1[i]);
  }

  ASSERT_EQ(list2.size(), 3U);
  int expected_values2[] = {1, 2, 3};
  i = 0;
  for (auto it = list2.begin(); it != list2.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected_values2[i]);
  }
}

TEST(ListTest, PushFrontAndBack) {
  s21::list<int> list;

  list.push_front(1);
  EXPECT_EQ(list.size(), 1U);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 1);

  list.push_back(2);
  EXPECT_EQ(list.size(), 2U);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, PopFrontAndBack) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.pop_front();
  EXPECT_EQ(list.size(), 2U);
  EXPECT_EQ(list.front(), 2);

  list.pop_back();
  EXPECT_EQ(list.size(), 1U);
  EXPECT_EQ(list.back(), 2);
}

TEST(ListTest, ClearList) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.clear();
  EXPECT_EQ(list.size(), 0U);
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, ReverseList) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.reverse();
  EXPECT_EQ(list.front(), 3);
  EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, UniqueList) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(1);
  list.push_back(2);
  list.push_back(2);
  list.push_back(3);
  list.push_back(3);
  list.unique();
  EXPECT_EQ(list.size(), 3U);
}

TEST(ListTest, SortList) {
  s21::list<int> list;
  list.push_back(3);
  list.push_back(1);
  list.push_back(2);
  list.sort();
  s21::list<int>::iterator it = list.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(ListTest, InsertAtBeginning) {
  s21::list<int> list = {1, 2, 3};
  s21::list<int>::iterator it = list.insert(list.begin(), 42);
  EXPECT_EQ(*it, 42);
  EXPECT_EQ(list.size(), 4U);
  EXPECT_EQ(list.front(), 42);
}

TEST(ListTest, EraseFirstElement) {
  s21::list<int> list = {1, 2, 3};
  list.erase(list.begin());
  s21::list<int>::iterator it = list.begin();
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(list.size(), 2U);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, Sort) {
  s21::list<int> list = {8, 3, 2, 10, 7, 4, 6, 1, 9, 5};

  list.sort();

  s21::list<int> expected_list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto it1 = list.begin();
  auto it2 = expected_list.begin();
  while (it1 != list.end() && it2 != expected_list.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  EXPECT_EQ(it1, list.end());
  EXPECT_EQ(it2, expected_list.end());
}

TEST(ListMergeTest, MergeTwoEmptyLists) {
  s21::list<int> list1;
  s21::list<int> list2;

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 0U);
  EXPECT_EQ(list2.size(), 0U);
}

TEST(ListMergeTest, MergeNonEmptyAndEmptyLists) {
  s21::list<int> list1;
  s21::list<int> list2;

  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 3U);
  EXPECT_EQ(list2.size(), 0U);

  int expected[] = {1, 2, 3};
  int i = 0;

  for (auto it = list1.begin(); it != list1.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
}

TEST(ListMergeTest, MergeEmptyAndNonEmptyLists) {
  s21::list<int> list1;
  s21::list<int> list2;

  list2.push_back(1);
  list2.push_back(2);
  list2.push_back(3);

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 3U);
  EXPECT_EQ(list2.size(), 0U);

  int expected[] = {1, 2, 3};
  int i = 0;

  for (auto it = list1.begin(); it != list1.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
}

TEST(ListMergeTest, MergeTwoNonEmptyLists) {
  s21::list<int> list1;
  s21::list<int> list2;

  list1.push_back(1);
  list1.push_back(3);
  list1.push_back(5);

  list2.push_back(2);
  list2.push_back(4);
  list2.push_back(6);

  list1.merge(list2);

  EXPECT_EQ(list1.size(), 6U);
  EXPECT_EQ(list2.size(), 0U);

  int expected[] = {1, 2, 3, 4, 5, 6};
  int i = 0;

  for (auto it = list1.begin(); it != list1.end(); ++it, ++i) {
    EXPECT_EQ(*it, expected[i]);
  }
}

TEST(ListTest, EmplaceInt) {
  s21::list<int> list = {1, 2, 3};
  auto iter = list.cbegin();
  ++iter;
  auto it = list.insert_many(iter, 4);
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(list.size(), 4U);
  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, EmplaceBack) {
  s21::list<int> list;

  list.insert_many_back(1, 2, 3);

  ASSERT_EQ(list.size(), 3U);

  auto iter = list.begin();
  EXPECT_EQ(*iter, 1);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 3);
}

TEST(ListTest, EmplaceFront) {
  s21::list<int> list;

  list.insert_many_front(1, 2, 3);

  ASSERT_EQ(list.size(), 3U);

  auto iter = list.begin();
  EXPECT_EQ(*iter, 3);
  ++iter;
  EXPECT_EQ(*iter, 2);
  ++iter;
  EXPECT_EQ(*iter, 1);
}

//_______________<<List<<____________________

//_________________>>Stack>>_________________

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> my_stack;
  std::stack<int> stl_stack;
  EXPECT_EQ(my_stack.size(), stl_stack.size());
  EXPECT_EQ(my_stack.empty(), stl_stack.empty());
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<unsigned int> s1{1, 2, 3};
  ASSERT_EQ(s1.size(), 3u);
  ASSERT_EQ(s1.top(), 3u);

  s21::stack<std::string> s2{"hello", "world"};
  ASSERT_EQ(s2.size(), 2u);
  ASSERT_EQ(s2.top(), "world");
}

TEST(StackTest, InitializerListConstructorPair) {
  s21::stack<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::stack<std::pair<std::string, int>> q2;
  q2.push({"one", 1});
  q2.push({"two", 2});
  q2.push({"three", 3});
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty()) {
    EXPECT_EQ(q1.top(), q2.top());
    q1.pop();
    q2.pop();
  }
}

TEST(StackTest, EmptyInitializerListConstructor) {
  s21::stack<int> s{};
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(s.size(), 0u);
}

TEST(StackTest, Empty) {
  s21::stack<std::pair<std::string, int>> s;
  std::stack<std::pair<std::string, int>> s_stl;

  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s_stl.empty());

  s.push({"one", 1});
  s_stl.push({"one", 1});

  EXPECT_FALSE(s.empty());
  EXPECT_FALSE(s_stl.empty());

  s.pop();
  s_stl.pop();

  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s_stl.empty());
}

TEST(StackTest, Size) {
  s21::stack<std::pair<std::string, unsigned int>> s;
  std::stack<std::pair<std::string, unsigned int>> s_stl;

  EXPECT_EQ(s.size(), 0u);
  EXPECT_EQ(s_stl.size(), 0u);

  s.push({"one", 1u});
  s_stl.push({"one", 1u});
  EXPECT_EQ(s.size(), s_stl.size());

  s.push({"two", 2u});
  s_stl.push({"two", 2u});
  EXPECT_EQ(s.size(), s_stl.size());

  s.push({"three", 3u});
  s_stl.push({"three", 3u});
  EXPECT_EQ(s.size(), s_stl.size());

  s.pop();
  s_stl.pop();
  EXPECT_EQ(s.size(), s_stl.size());

  s.pop();
  s_stl.pop();
  EXPECT_EQ(s.size(), s_stl.size());

  s.pop();
  s_stl.pop();
  EXPECT_EQ(s.size(), s_stl.size());
}

TEST(StackTest, PushPopTop) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  for (int i = 1; i <= 10; ++i) {
    std_stack.push(i);
    s21_stack.push(i);
  }
  while (!std_stack.empty()) {
    EXPECT_EQ(std_stack.top(), s21_stack.top());
    std_stack.pop();
    s21_stack.pop();
  }
}

TEST(StackTest, PushAndPopString) {
  s21::stack<std::string> s;
  std::stack<std::string> s_stl;

  s.push("one");
  s_stl.push("one");
  EXPECT_EQ(s.top(), s_stl.top());

  s.push("two");
  s_stl.push("two");
  EXPECT_EQ(s.top(), s_stl.top());

  s.pop();
  s_stl.pop();
  EXPECT_EQ(s.top(), s_stl.top());

  s.pop();
  s_stl.pop();
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s_stl.empty());
}

TEST(StackTest, TopPair) {
  s21::stack<std::pair<std::string, int>> s;
  std::stack<std::pair<std::string, int>> s_stl;

  s.push({"one", 1});
  s_stl.push({"one", 1});

  EXPECT_EQ(s.top(), s_stl.top());

  s.push({"two", 2});
  s_stl.push({"two", 2});

  EXPECT_EQ(s.top(), s_stl.top());

  s.pop();
  s_stl.pop();

  EXPECT_EQ(s.top(), s_stl.top());

  s.pop();
  s_stl.pop();

  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(s_stl.empty());
}

TEST(StackTest, CopyConstructor) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  for (int i = 1; i <= 10; ++i) {
    std_stack.push(i);
    s21_stack.push(i);
  }
  std::stack<int> std_copy(std_stack);
  s21::stack<int> s21_copy(s21_stack);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  while (!std_copy.empty()) {
    EXPECT_EQ(std_copy.top(), s21_copy.top());
    std_copy.pop();
    s21_copy.pop();
  }
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(StackTest, CopyConstructorString) {
  s21::stack<std::string> s1;
  std::stack<std::string> s1_stl;

  s1.push("one");
  s1_stl.push("one");
  s1.push("two");
  s1_stl.push("two");

  s21::stack<std::string> s2(s1);
  std::stack<std::string> s2_stl(s1_stl);

  while (!s1.empty() && !s2.empty()) {
    EXPECT_EQ(s1.top(), s2.top());
    EXPECT_EQ(s1_stl.top(), s2_stl.top());
    s1.pop();
    s2.pop();
    s1_stl.pop();
    s2_stl.pop();
  }
}

TEST(StackTest, CopyConstructorPair) {
  s21::stack<std::pair<std::string, int>> s1;
  std::stack<std::pair<std::string, int>> s1_stl;

  s1.push({"one", 1});
  s1_stl.push({"one", 1});
  s1.push({"two", 2});
  s1_stl.push({"two", 2});

  s21::stack<std::pair<std::string, int>> s2(s1);
  std::stack<std::pair<std::string, int>> s2_stl(s1_stl);

  while (!s1.empty() && !s2.empty()) {
    EXPECT_EQ(s1.top(), s2.top());
    EXPECT_EQ(s1_stl.top(), s2_stl.top());
    s1.pop();
    s2.pop();
    s1_stl.pop();
    s2_stl.pop();
  }
}

TEST(StackTest, CopyConstructorEmpty) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  std::stack<int> std_copy(std_stack);
  s21::stack<int> s21_copy(s21_stack);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(StackTest, MoveConstructorPair) {
  s21::stack<std::pair<std::string, int>> s1;
  std::stack<std::pair<std::string, int>> s1_stl;

  s1.push({"one", 1});
  s1_stl.push({"one", 1});
  s1.push({"two", 2});
  s1_stl.push({"two", 2});

  s21::stack<std::pair<std::string, int>> s2(std::move(s1));
  std::stack<std::pair<std::string, int>> s2_stl(std::move(s1_stl));

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.size() == 2);

  EXPECT_TRUE(s1_stl.empty());
  EXPECT_TRUE(s2_stl.size() == 2);
}

TEST(StackTest, MoveConstructorString) {
  s21::stack<std::string> s1;
  std::stack<std::string> s1_stl;

  s1.push("one");
  s1_stl.push("one");
  s1.push("two");
  s1_stl.push("two");

  s21::stack<std::string> s2(std::move(s1));
  std::stack<std::string> s2_stl(std::move(s1_stl));

  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.size() == 2);
  EXPECT_TRUE(s2.top() == "two");

  EXPECT_TRUE(s1_stl.empty());
  EXPECT_TRUE(s2_stl.size() == 2);
  EXPECT_TRUE(s2_stl.top() == "two");
}

TEST(StackTest, CopyAssignmentOperator) {
  s21::stack<int> my_stack;
  std::stack<int> stl_stack;

  for (int i = 0; i < 10; ++i) {
    my_stack.push(i);
    stl_stack.push(i);
  }

  s21::stack<int> my_copy_stack;
  std::stack<int> stl_copy_stack;

  my_copy_stack = my_stack;
  stl_copy_stack = stl_stack;

  EXPECT_EQ(my_copy_stack.size(), stl_copy_stack.size());

  while (!my_copy_stack.empty()) {
    EXPECT_EQ(my_copy_stack.top(), stl_copy_stack.top());
    my_copy_stack.pop();
    stl_copy_stack.pop();
  }

  EXPECT_TRUE(my_copy_stack.empty());
  EXPECT_TRUE(stl_copy_stack.empty());
}

TEST(StackTest, MoveAssignmentOperator) {
  s21::stack<int> my_stack;
  std::stack<int> stl_stack;

  for (int i = 0; i < 10; ++i) {
    my_stack.push(i);
    stl_stack.push(i);
  }

  s21::stack<int> my_move_stack;
  std::stack<int> stl_move_stack;

  my_move_stack = std::move(my_stack);
  stl_move_stack = std::move(stl_stack);

  EXPECT_EQ(my_move_stack.size(), stl_move_stack.size());
  EXPECT_EQ(my_stack.size(), stl_stack.size());

  while (!my_move_stack.empty()) {
    EXPECT_EQ(my_move_stack.top(), stl_move_stack.top());
    my_move_stack.pop();
    stl_move_stack.pop();
  }

  EXPECT_TRUE(my_stack.empty());
  EXPECT_TRUE(stl_stack.empty());
}

TEST(StackTest, AssignmentOperatorEmpty) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;
  std::stack<int> std_copy;
  s21::stack<int> s21_copy;
  std_copy = std_stack;
  s21_copy = s21_stack;
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_stack.size(), s21_stack.size());
}

TEST(StackTest, EmplaceFrontTest) {
  s21::stack<unsigned int> my_stack;
  my_stack.insert_many_front(1);
  my_stack.insert_many_front(2);
  my_stack.insert_many_front(3);

  EXPECT_EQ(my_stack.size(), 3u);
  EXPECT_EQ(my_stack.top(), 3u);

  my_stack.pop();
  EXPECT_EQ(my_stack.size(), 2u);
  EXPECT_EQ(my_stack.top(), 2u);

  my_stack.insert_many_front(4);
  EXPECT_EQ(my_stack.size(), 3u);
  EXPECT_EQ(my_stack.top(), 4u);
}

//________________<<Stack<<__________________

//_________________>>Queue>>_________________

TEST(QueueTest, DefaultConstructor) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  EXPECT_EQ(std_queue.empty(), s21_queue.empty());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, InitializerListConstructor) {
  s21::queue<unsigned int> q1{1, 2, 3};
  ASSERT_EQ(q1.size(), 3u);
  ASSERT_EQ(q1.front(), 1u);
  ASSERT_EQ(q1.back(), 3u);

  s21::queue<std::string> q2{"hello", "world"};
  ASSERT_EQ(q2.size(), 2u);
  ASSERT_EQ(q2.front(), "hello");
  ASSERT_EQ(q2.back(), "world");
}

TEST(QueueTest, InitializerListConstructorPair) {
  s21::queue<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::queue<std::pair<std::string, int>> q2;
  q2.push({"one", 1});
  q2.push({"two", 2});
  q2.push({"three", 3});
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty()) {
    EXPECT_EQ(q1.front().first, q2.front().first);
    EXPECT_EQ(q1.front().second, q2.front().second);
    q1.pop();
    q2.pop();
  }
}

TEST(QueueTest, EmptyInitializerListConstructor) {
  s21::queue<unsigned int> q{};
  ASSERT_TRUE(q.empty());
}

TEST(QueueTest, CopyInitializerListConstructor) {
  s21::queue<unsigned int> q1{1, 2, 3};
  s21::queue<unsigned int> q2{q1};
  ASSERT_EQ(q1.size(), q2.size());
  ASSERT_EQ(q1.front(), q2.front());
  ASSERT_EQ(q1.back(), q2.back());
}

TEST(QueueTest, MoveInitializerListConstructor) {
  s21::queue<unsigned int> q1{1, 2, 3};
  s21::queue<unsigned int> q2{std::move(q1)};
  ASSERT_EQ(q1.size(), 0u);
  ASSERT_EQ(q2.size(), 3u);
  ASSERT_EQ(q2.front(), 1u);
  ASSERT_EQ(q2.back(), 3u);
}

TEST(QueueTest, PushPopFrontBack) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  while (!std_queue.empty()) {
    EXPECT_EQ(std_queue.front(), s21_queue.front());
    EXPECT_EQ(std_queue.back(), s21_queue.back());
    std_queue.pop();
    s21_queue.pop();
  }
}

TEST(QueueTest, FrontBackPair) {
  s21::queue<std::pair<std::string, int>> q{
      {"one", 1}, {"two", 2}, {"three", 3}};
  std::queue<std::pair<std::string, int>> q2;
  q2.push({"one", 1});
  q2.push({"two", 2});
  q2.push({"three", 3});
  EXPECT_EQ(q.front().first, q2.front().first);
  EXPECT_EQ(q.front().second, q2.front().second);
  EXPECT_EQ(q.back().first, q2.back().first);
  EXPECT_EQ(q.back().second, q2.back().second);
}

TEST(QueueTest, PushPopPair) {
  s21::queue<std::pair<std::string, int>> q;
  std::queue<std::pair<std::string, int>> q2;
  q.push({"one", 1});
  q2.push({"one", 1});
  q.push({"two", 2});
  q2.push({"two", 2});
  q.push({"three", 3});
  q2.push({"three", 3});
  EXPECT_EQ(q.empty(), q2.empty());
  EXPECT_EQ(q.size(), q2.size());
  while (!q.empty()) {
    EXPECT_EQ(q.front().first, q2.front().first);
    EXPECT_EQ(q.front().second, q2.front().second);
    q.pop();
    q2.pop();
  }
}

TEST(QueueTest, CopyConstructor) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy(std_queue);
  s21::queue<int> s21_copy(s21_queue);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  while (!std_copy.empty()) {
    EXPECT_EQ(std_copy.front(), s21_copy.front());
    std_copy.pop();
    s21_copy.pop();
  }
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, CopyConstructorPair) {
  s21::queue<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  s21::queue<std::pair<std::string, int>> q2(q1);
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty()) {
    EXPECT_EQ(q1.front().first, q2.front().first);
    EXPECT_EQ(q1.front().second, q2.front().second);
    q1.pop();
    q2.pop();
  }
}

TEST(QueueTest, CopyConstructorEmpty) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  std::queue<int> std_copy(std_queue);
  s21::queue<int> s21_copy(s21_queue);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, CopyConstructorSize) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy(std_queue);
  s21::queue<int> s21_copy(s21_queue);
  std_queue.push(11);
  s21_queue.push(11);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, CopyAssignmentOperator) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy;
  s21::queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  while (!std_copy.empty()) {
    EXPECT_EQ(std_copy.front(), s21_copy.front());
    std_copy.pop();
    s21_copy.pop();
  }
}

TEST(QueueTest, CopyAssignmentPair) {
  s21::queue<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  s21::queue<std::pair<std::string, int>> q2;
  std::queue<std::pair<std::string, int>> q3;
  q2 = q1;
  EXPECT_EQ(q1.empty(), q2.empty());
  EXPECT_EQ(q1.size(), q2.size());
  while (!q1.empty()) {
    EXPECT_EQ(q1.front().first, q2.front().first);
    EXPECT_EQ(q1.front().second, q2.front().second);
    q1.pop();
    q2.pop();
  }
}

TEST(QueueTest, AssignmentOperator) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy;
  s21::queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  while (!std_copy.empty()) {
    EXPECT_EQ(std_copy.front(), s21_copy.front());
    std_copy.pop();
    s21_copy.pop();
  }
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, AssignmentOperatorEmpty) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  std::queue<int> std_copy;
  s21::queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, AssignmentOperatorSize) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_copy;
  s21::queue<int> s21_copy;
  std_copy = std_queue;
  s21_copy = s21_queue;
  std_queue.push(11);
  s21_queue.push(11);
  EXPECT_EQ(std_copy.size(), s21_copy.size());
  EXPECT_EQ(std_queue.size(), s21_queue.size());
}

TEST(QueueTest, MoveAssignmentOperator) {
  std::queue<int> std_queue;
  s21::queue<int> s21_queue;
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
    s21_queue.push(i);
  }
  std::queue<int> std_move;
  s21::queue<int> s21_move;
  std_move = std::move(std_queue);
  s21_move = std::move(s21_queue);
  while (!std_move.empty()) {
    EXPECT_EQ(std_move.front(), s21_move.front());
    std_move.pop();
    s21_move.pop();
  }
}

TEST(QueueTest, MoveAssignmentPair) {
  s21::queue<std::pair<std::string, int>> q1{
      {"one", 1}, {"two", 2}, {"three", 3}};
  s21::queue<std::pair<std::string, int>> q2;
  std::queue<std::pair<std::string, int>> q3;
  q2 = std::move(q1);
  q3.push({"one", 1});
  q3.push({"two", 2});
  q3.push({"three", 3});
  EXPECT_EQ(q1.empty(), true);
  EXPECT_EQ(q2.size(), q3.size());
  while (!q2.empty()) {
    EXPECT_EQ(q2.front().first, q3.front().first);
    EXPECT_EQ(q2.front().second, q3.front().second);
    q2.pop();
    q3.pop();
  }
}

TEST(QueueTest, EmplaceBackTest) {
  s21::queue<unsigned int> q;
  q.insert_many_back(1);
  q.insert_many_back(2);
  q.insert_many_back(3);

  EXPECT_EQ(q.size(), 3u);
  EXPECT_EQ(q.front(), 1u);
  EXPECT_EQ(q.back(), 3u);

  q.pop();
  EXPECT_EQ(q.size(), 2u);
  EXPECT_EQ(q.front(), 2u);

  q.insert_many_back(4);
  EXPECT_EQ(q.size(), 3u);
  EXPECT_EQ(q.back(), 4u);
}

TEST(ListTest, FrontOnEmptyListThrowsException) {
  s21::list<int> empty_list;
  EXPECT_THROW(empty_list.front(), std::out_of_range);
}

TEST(ListTest, BackOnEmptyListThrowsException) {
  s21::list<int> empty_list;
  EXPECT_THROW(empty_list.back(), std::out_of_range);
}

TEST(ListTest, PopOnEmptyListThrowsException) {
  s21::list<int> empty_list;
  EXPECT_THROW(empty_list.pop_back(), std::out_of_range);
}

TEST(ListTest, Pop_frontOnEmptyListThrowsException) {
  s21::list<int> empty_list;
  EXPECT_THROW(empty_list.pop_front(), std::out_of_range);
}

TEST(ListTest, EraseOnEmptyListThrowsException) {
  s21::list<int> empty_list;
  EXPECT_THROW(empty_list.erase(empty_list.begin()), std::out_of_range);
}

//_______________<<Queue<<_____________________________________________

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

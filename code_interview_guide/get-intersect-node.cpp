/**
* @file get-intersect-node.cpp
* @brief
* @version 1.0
* @date 12/19/2018 11:53:03 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include "node_common.h"

using namespace common;

namespace {

int get_intersect_node(Node *link1, Node *link2) {
  print_link(link1);
  print_link(link2);

  if (!link1 || !link2) {
    std::cout << "no intersect" << std::endl;
    return 0;
  }

  if (link1 == link2) {
    std::cout << "inersect node: " << link1->value_ << std::endl;
    return 0;
  }

  auto first_loop_node1 = get_first_loop_node(link1);
  auto first_loop_node2 = get_first_loop_node(link2);
  if ((first_loop_node1 && !first_loop_node2) ||
      (!first_loop_node1 && first_loop_node2)) {
    std::cout << "no intersect" << std::endl;
    return 0;
  }

  if (!first_loop_node1 && !first_loop_node2) {
    int n = 0;
    Node *p1, *p2;

    for (p1 = link1; p1; n++, p1 = p1->next_);
    for (p2 = link2; p2; n--, p2 = p2->next_);
    if (n < 0) {
      n = -n;
      p1 = link2;
      p2 = link1;
    } else {
      p1 = link1;
      p2 = link2;
    }

    for (; n--; p1 = p1->next_); 

    while (p1 != p2) {
      p1 = p1->next_;
      p2 = p2->next_;
    }

    if (p1) {
      std::cout << "inersect node: " << p1->value_ << std::endl;
    } else {
      std::cout << "no intersect" << std::endl;
    }
  } else {
    int n = 0;
    Node *p1, *p2;

    for (p1 = first_loop_node1;
         p1->next_ != first_loop_node1 && p1 != first_loop_node2;
         p1 = p1->next_); 

    if (p1 != first_loop_node2) {
      std::cout << "no intersect" << std::endl;
      return 0;
    }

    if (first_loop_node1 != first_loop_node2) {
      std::cout << "inersect node: " << first_loop_node1->value_ 
       << " or " << first_loop_node2->value_ << std::endl;
      return 0;
    }

    for (p1 = link1; p1 != first_loop_node1; n++, p1 = p1->next_);
    for (p2 = link2; p2 != first_loop_node2; n--, p2 = p2->next_);
    if (n < 0) {
      n = -n;
      p1 = link2;
      p2 = link1;
    } else {
      p1 = link1;
      p2 = link2;
    }

    for (; n--; p1 = p1->next_);
    for (; p1 != p2; p1 = p1->next_, p2 = p2->next_);
    std::cout << "inersect node: " << p1->value_ << std::endl;
  }

  return 0;
}

/**
 * @brief 两个有环链表交于环上不同点
 * @return 0 if success, < 0 otherwise
 */
int test_case1() {
  std::cout << "两个有环链表交于环上不同点" << std::endl;
  auto link1 = build_loop_link(10, 100);
  auto link2 = build_single_link(13);

  auto tmp1 = link1;
  while (tmp1->value_ != 106) {
    tmp1 = tmp1->next_;
  }

  auto tmp2 = link2;
  while (tmp2->next_) {
    tmp2 = tmp2->next_;
  }
  tmp2->next_ = tmp1;

  return get_intersect_node(link1, link2);
}

/**
 * @brief 两个有环链表交于环上相同点
 * @return 0 if success, < 0 otherwise
 */
int test_case2() {
  auto link1 = build_loop_link(10, 100);
  auto link2 = build_single_link(13);

  std::cout << "两个有环链表交于环上相同点" << std::endl;
  auto tmp1 = link1;
  while (tmp1->value_ != 103) {
    tmp1 = tmp1->next_;
  }

  auto tmp2 = link2;
  while (tmp2->next_) {
    tmp2 = tmp2->next_;
  }
  tmp2->next_ = tmp1;

  return get_intersect_node(link1, link2);
}

/**
 * @brief 两个无环链表相交
 * @return 0 if success, < 0 otherwise
 */
int test_case3() {
  auto link1 = build_single_link(7);
  auto link2 = build_single_link(13, 100);

  std::cout << "两个无环链表相交" << std::endl;
  auto tmp1 = link1;
  while (tmp1->value_ != 5) {
    tmp1 = tmp1->next_;
  }

  auto tmp2 = link2;
  while (tmp2->next_) {
    tmp2 = tmp2->next_;
  }
  tmp2->next_ = tmp1;

  return get_intersect_node(link1, link2);
}

/**
 * @brief 两个无环链表不相交
 * @return 0 if success, < 0 otherwise
 */
int test_case4() {
  auto link1 = build_single_link(10);
  auto link2 = build_single_link(5, 100);
  std::cout << "两个无环链表不相交" << std::endl;
  return get_intersect_node(link1, link2);
}

/**
 * @brief 两个有环链表不相交
 * @return 0 if success, < 0 otherwise
 */
int test_case5() {
  auto link1 = build_loop_link(10);
  auto link2 = build_loop_link(5, 100);
  std::cout << "两个有环链表不相交" << std::endl;
  return get_intersect_node(link1, link2);
}

/**
 * @brief 有环链表与无环链表不相交
 * @return 0 if success, < 0 otherwise
 */
int test_case6() {
  auto link1 = build_loop_link(10);
  auto link2 = build_single_link(5, 100);
  std::cout << "有环链表与无环链表不相交" << std::endl;
  return get_intersect_node(link1, link2);
}

int test() {
  test_case1();
  std::cout << "-----------" << std::endl;
  test_case2();
  std::cout << "-----------" << std::endl;
  test_case3();
  std::cout << "-----------" << std::endl;
  test_case4();
  std::cout << "-----------" << std::endl;
  test_case5();
  std::cout << "-----------" << std::endl;
  test_case6();
  return 0;
}

} //namespace

int main() {
  test();
  return 0;
}

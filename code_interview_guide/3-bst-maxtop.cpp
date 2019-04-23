/**
* @file 3-bst-maxtop.cpp
* @brief
* @version 1.0
* @date 04/01/2019 11:02:12 PM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2019 Tencent. All Rights Reserved.
*/
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include  "btree_common.h"

namespace {

/**
 * @brief 
 * @class BstMaxTop
 */
class BstMaxTop
{
 public:
  // 节点的统计量（贡献值）,<左子树的贡献值，右子树的贡献值>
  using NodeStat = std::unordered_map<common::BtreeNode *,
        std::pair<int, int>>;
  /**
   * @brief
   */
  BstMaxTop() {
    (void)init_tree();
  }
  ~BstMaxTop() {
    common::free_array_tree(root_);
  }

  int bst_maxtop1() {
    return bst_maxtop1(root_);
  }

  int bst_maxtop2() {
    NodeStat node_stat;
    return bst_maxtop2(root_, node_stat);
  }

 protected:
 private:
  common::BtreeNode *root_;

  int init_tree() {
    root_ = new common::BtreeNode[15];
    root_[0].value_ = 6;
    root_[0].left_ = &root_[1];
    root_[0].right_ = &root_[2];

    root_[1].value_ = 1;
    root_[1].left_ = &root_[3];
    root_[1].right_ = &root_[4];

    root_[2].value_ = 12;
    root_[2].left_ = &root_[5];
    root_[2].right_ = &root_[6];

    root_[3].value_ = 0;
    root_[4].value_ = 3;

    root_[5].value_ = 10;
    root_[5].left_ = &root_[7];
    root_[5].right_ = &root_[8];

    root_[6].value_ = 13;
    root_[6].left_ = &root_[9];
    root_[6].right_ = &root_[10];

    root_[7].value_ = 4;
    root_[7].left_ = &root_[11];
    root_[7].right_ = &root_[12];

    root_[8].value_ = 14;
    root_[8].left_ = &root_[13];
    root_[8].right_ = &root_[14];

    root_[9].value_ = 20;
    root_[10].value_ = 16;
    root_[11].value_ = 2;
    root_[12].value_ = 5;
    root_[13].value_ = 11;
    root_[14].value_ = 15;

    common::print_tree_graph(root_);

    return 0;
  }

  int bst_maxtop1(common::BtreeNode *root) {
    if (!root) {
      return 0;
    }

    return std::max(bst_maxtop1(root->left_), std::max(
        bst_maxtop1(root->right_), bst_maxtop1_root(root, root)));
  }

  int bst_maxtop1_root(common::BtreeNode *root, common::BtreeNode *cur) {
    if (!root || !cur || !is_bst_node(root, cur)) {
      return 0;
    }
    return bst_maxtop1_root(root, cur->left_) +
      bst_maxtop1_root(root, cur->right_) + 1;
  }

  bool is_bst_node(common::BtreeNode *root, common::BtreeNode *cur) {
    if (!root) {
      return false;
    }
    if (root == cur) {
      return true;
    }

    if (cur->value_ < root->value_) {
      return is_bst_node(root->left_, cur);
    } else {
      return is_bst_node(root->right_, cur);
    }
  }

  int bst_maxtop2(common::BtreeNode *root, NodeStat &node_stat) {
    if (!root) {
      return 0;
    }
    // 左/右子树为根的最大搜索树节点数，同时得到了每个节点的贡献值
    auto const left = bst_maxtop2(root->left_, node_stat);
    auto const right = bst_maxtop2(root->right_, node_stat);

    // 计算当前节点的贡献值
    auto &stat = node_stat[root];
    stat.first = merge_left(root, root->left_, node_stat);
    stat.second = merge_right(root, root->right_, node_stat);
    return std::max(left, std::max(right, stat.first + stat.second + 1));
  }

  int merge_left(common::BtreeNode *root, common::BtreeNode *cur,
                 NodeStat &node_stat) {
    // 左子树最大值必需比root小
    if (!cur || cur->value_ > root->value_) {
      return 0;
    }
    auto &stat = node_stat[cur];
    // 右子树先得有贡献才可以继续判断
    // 若无贡献则表示cur->right_->value_ < cur.value_，不符合要求
    if (stat.second) {
      stat.second = merge_left(root, cur->right_, node_stat);
    }
    return stat.first + stat.second + 1;
  }
  int merge_right(common::BtreeNode *root, common::BtreeNode *cur,
                 NodeStat &node_stat) {
    // 右子树最小值必需比root大
    if (!cur || cur->value_ < root->value_) {
      return 0;
    }
    auto &stat = node_stat[cur];
    // 同理：左子树先得有贡献才可以继续判断
    if (stat.first) {
      stat.first = merge_right(root, cur->left_, node_stat);
    }
    return stat.first + stat.second + 1;
  }
};


} // namespace

int main(int argc, char **argv) {
  BstMaxTop bst_maxtop;

  std::cout << bst_maxtop.bst_maxtop1() << std::endl;
  std::cout << bst_maxtop.bst_maxtop2() << std::endl;

  return 0;
}

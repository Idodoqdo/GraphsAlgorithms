#ifndef SRC_S21_TREENODE_TPP_
#define SRC_S21_TREENODE_TPP_

#if defined(BOOST_FOUND)
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <stdexcept>
#include <string>
#else
#include <iostream>
#endif  // BOOST_FOUND
#include <memory>
#include "s21_tree_node.h"

namespace s21 {

template <typename... Args>
std::string string_format(const std::string& format, Args... args) {
  int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) +
               1;  // Extra space for '\0'
  if (size_s <= 0) {
    throw std::runtime_error("Error during formatting.");
  }
  auto size = static_cast<size_t>(size_s);
  std::unique_ptr<char[]> buf(new char[size]);
  std::snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(),
                     buf.get() + size - 1);  // We don't want the '\0' inside
}

template <class Key, class Value>
TreeNode<Key, Value>::TreeNode(value_type data, node_type nil)
    : value_(data),
      is_black_(true),
      left_(nil),
      right_(nil),
      parent_(nullptr) {}

template <class Key, class Value>
typename TreeNode<Key, Value>::node_type TreeNode<Key, Value>::get_minimum() {
  node_type head = this;
  if (!is_nil())
    while (!head->left_->is_nil()) head = head->left_;
  return head;
}

template <class Key, class Value>
typename TreeNode<Key, Value>::node_type TreeNode<Key, Value>::get_maximum() {
  node_type head = this;
  if (!is_nil())
    while (!head->right_->is_nil()) head = head->right_;
  return head;
}

template <class Key, class Value>
std::string TreeNode<Key, Value>::to_dot_text() {
#if defined(BOOST_FOUND)
  std::stringstream ss;
  ss << static_cast<const void*>(this);
  std::string node_address = ss.str();
  std::string key_str = boost::lexical_cast<std::string>(value_.first);
  std::string value_str = boost::lexical_cast<std::string>(value_.second);

  std::string node_str = string_format(
      "\"%s\"[label=\"key: %s\\n data: %s\", style = filled, fontcolor = "
      "white, color = %s, shape = "
      "circle]\n",
      node_address.c_str(), key_str.c_str(), value_str.c_str(),
      color_to_str().c_str());

  if (parent_) {
    ss.str(std::string());
    ss << static_cast<const void*>(parent_);
    std::string parent_address = ss.str();
    std::string relation_str = string_format(
        "\"%s\"->\"%s\"\n", parent_address.c_str(), node_address.c_str());
    node_str += relation_str;
  }
  if (!left_->is_nil()) node_str += left_->to_dot_text();
  if (!right_->is_nil()) node_str += right_->to_dot_text();
  return node_str;
#else
  std::cerr << "[ERROR]Boost lib not found, can't convert values" << std::endl;
  return "!!!Boost lib not found!!!";
#endif  // BOOST_FOUND
}

template <class Key, class Value>
typename TreeNode<Key, Value>::node_type TreeNode<Key, Value>::copy_tree(
    const TreeNode<Key, Value>& other, const node_type parent_node,
    node_type nil_node) {
  if (other.is_nil()) {
    return nil_node;
  } else {
    node_type new_node = new TreeNode<Key, Value>();
    new_node->value_ = other.value_;
    new_node->is_black_ = other.is_black_;
    new_node->parent_ = parent_node;
    if (other.left_->is_nil()) {
      new_node->left_ = nil_node;
    } else {
      new_node->left_ = copy_tree(*other.left_, new_node, nil_node);
    }
    if (other.right_->is_nil()) {
      new_node->right_ = nil_node;
    } else {
      new_node->right_ = copy_tree(*other.right_, new_node, nil_node);
    }
    if (parent_node == nullptr) {
      nil_node->parent_ = new_node->get_maximum();
    }
    return new_node;
  }
}
}  // namespace s21

#endif  // SRC_S21_TREENODE_TPP_

#include "profile.h"
#include <iostream>

void Profile::addPost(const Post& newPost) {
  myPosts.push_back(newPost);
}

void Profile::printPost(size_t postIndex) const {
  if (!validPostIndex(postIndex)) {
    std::cout << "Error! This post index does not exist." << std::endl;
    return;
  }

  const Post& post = myPosts[postIndex];
  std::cout << "Post number: " << postIndex + 1 << std::endl;
  std::cout << "Caption: " << post.caption << std::endl;
  std::cout << "Hearts: " << post.hearts << std::endl;
}

void Profile::printPosts() const {
  if (myPosts.empty()) {
    std::cout << "This profile does not have any posts yet." << std::endl;
    return;
  }

  std::cout << "\nCurrent profile:" << std::endl;
  for (size_t i = 0; i < myPosts.size(); ++i) {
    printPost(i);
    std::cout << std::endl;
  }
}

int Profile::sumHearts() const {
  int total = 0;
  for (const Post& post : myPosts) {
    total += post.hearts;
  }
  return total;
}

void Profile::removePost(size_t index) {
  if (!validPostIndex(index)) {
    std::cout << "Error! This post index does not exist." << std::endl;
    return;
  }

  myPosts.erase(myPosts.begin() + static_cast<std::vector<Post>::difference_type>(index));
}

void Profile::addHearts(size_t postIndex, int numHearts) {
  if (!validPostIndex(postIndex)) {
    std::cout << "Error! This post index does not exist." << std::endl;
    return;
  }

  myPosts[postIndex].hearts += numHearts;
}

bool Profile::validPostIndex(size_t index) const {
  return index < myPosts.size();
}

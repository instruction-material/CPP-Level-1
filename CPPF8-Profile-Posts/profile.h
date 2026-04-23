#ifndef PROFILE_H
#define PROFILE_H

#include <cstddef>
#include <string>
#include <vector>

struct Post {
  std::string caption;
  int hearts;
};

class Profile {

  private:
    std::vector<Post> myPosts;

    bool validPostIndex(size_t index) const;

  public:
    void addPost(const Post& newPost);
    void printPost(size_t postIndex) const;
    void printPosts() const;
    int sumHearts() const;
    void removePost(size_t index);
    void addHearts(size_t postIndex, int numHearts);
};

#endif // PROFILE_H

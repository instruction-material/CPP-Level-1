#ifndef PROFILE_H
#define PROFILE_H

#include <cstddef>
#include <limits>
#include <string>
#include <vector>

static_assert(std::numeric_limits<int>::digits >= 31,
              "This exercise requires an int with at least 31 value bits.");
inline constexpr std::size_t maxProfilePosts = 1000;
inline constexpr std::size_t maxCaptionBytes = 4096;
inline constexpr int maxPostHearts = 1000000;

struct Post {
    std::string caption;
    int hearts;
};

class Profile {
  private:
    std::vector<Post> myPosts;
    bool validPostIndex(std::size_t index) const;

  public:
    void addPost(const Post& newPost);
    void printPost(std::size_t postIndex) const;
    void printPosts() const;
    int sumHearts() const;
    void removePost(std::size_t index);
    void addHearts(std::size_t postIndex, int numHearts);
    std::size_t size() const;
};

#endif // PROFILE_H

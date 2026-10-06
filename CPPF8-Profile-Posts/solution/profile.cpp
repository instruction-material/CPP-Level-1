#include "profile.h"
#include <iostream>

void Profile::addPost(const Post& newPost) {
    if (myPosts.size() >= maxProfilePosts || newPost.caption.empty() ||
        newPost.caption.size() > maxCaptionBytes || newPost.hearts < 0 ||
        newPost.hearts > maxPostHearts) {
        std::cout << "Error! Invalid post or profile capacity reached.\n";
        return;
    }
    myPosts.push_back(newPost);
}

void Profile::printPost(std::size_t postIndex) const {
    if (!validPostIndex(postIndex)) {
        std::cout << "Error! This post index does not exist.\n";
        return;
    }
    const Post& post = myPosts[postIndex];
    std::cout << "Post number: " << postIndex + 1 << '\n';
    std::cout << "Caption: " << post.caption << '\n';
    std::cout << "Hearts: " << post.hearts << '\n';
}

void Profile::printPosts() const {
    if (myPosts.empty()) {
        std::cout << "This profile does not have any posts yet.\n";
        return;
    }
    std::cout << "\nCurrent profile:\n";
    for (std::size_t index = 0; index < myPosts.size(); ++index) {
        printPost(index);
        std::cout << '\n';
    }
}

int Profile::sumHearts() const {
    int total = 0;
    for (const Post& post : myPosts) {
        total += post.hearts;
    }
    return total;
}

void Profile::removePost(std::size_t index) {
    if (!validPostIndex(index)) {
        std::cout << "Error! This post index does not exist.\n";
        return;
    }
    myPosts.erase(myPosts.begin() +
                  static_cast<std::vector<Post>::difference_type>(index));
}

void Profile::addHearts(std::size_t postIndex, int numHearts) {
    if (!validPostIndex(postIndex)) {
        std::cout << "Error! This post index does not exist.\n";
        return;
    }
    const int current = myPosts[postIndex].hearts;
    // Compare before addition so even INT_MIN/INT_MAX changes are safe.
    if (numHearts < -current || numHearts > maxPostHearts - current) {
        std::cout << "Error! Hearts must stay between 0 and 1000000.\n";
        return;
    }
    myPosts[postIndex].hearts += numHearts;
}

bool Profile::validPostIndex(std::size_t index) const {
    return index < myPosts.size();
}

std::size_t Profile::size() const {
    return myPosts.size();
}

#include "profile.h"
#include <iostream>

void Profile::addPost(const Post& newPost) {
    // TODO: validate caption, hearts and capacity before appending.
    static_cast<void>(newPost);
}
void Profile::printPost(std::size_t postIndex) const {
    // TODO: guard the zero-based API index and print a one-based number.
    static_cast<void>(postIndex);
}
void Profile::printPosts() const {
    // TODO: handle the empty profile and visit each post without mutation.
}
int Profile::sumHearts() const {
    // TODO: sum the bounded records; an empty profile totals zero.
    return 0;
}
void Profile::removePost(std::size_t index) {
    // TODO: guard before erasing; later indexes shift left.
    static_cast<void>(index);
}
void Profile::addHearts(std::size_t postIndex, int numHearts) {
    // TODO: reject invalid indexes and changes before adding.
    static_cast<void>(postIndex);
    static_cast<void>(numHearts);
}
bool Profile::validPostIndex(std::size_t index) const {
    // TODO: compare with the owned vector's size.
    static_cast<void>(index);
    return false;
}
std::size_t Profile::size() const {
    // TODO: report the owned vector's size.
    return 0;
}

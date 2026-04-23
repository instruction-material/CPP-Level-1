#include <iostream>

#include "profile.h"

int main() {
  Profile myProfile;

  myProfile.addPost({"My first post!", 30});
  myProfile.addPost({"Incredible coders come from all backgrounds!", 100});
  myProfile.addPost({"Building with vectors keeps this capstone focused on design.", 45});

  myProfile.printPosts();
  std::cout << "Total hearts: " << myProfile.sumHearts() << std::endl;

  myProfile.addHearts(0, 10);
  myProfile.removePost(1);

  std::cout << "\nAfter editing the profile:" << std::endl;
  myProfile.printPosts();
  std::cout << "Total hearts: " << myProfile.sumHearts() << std::endl;

  return 0;
}

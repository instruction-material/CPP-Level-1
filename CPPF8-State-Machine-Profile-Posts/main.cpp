#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

struct Post {
  std::string caption;
  int hearts;
};

class Profile {
  private:
    std::vector<Post> posts;

  public:
    void addPost(const std::string& caption, int hearts) {
      posts.push_back({caption, hearts});
    }

    void printPosts() const {
      if (posts.empty()) {
        std::cout << "No posts yet." << std::endl;
        return;
      }

      for (size_t i = 0; i < posts.size(); ++i) {
        std::cout << i << ": " << posts[i].caption << " (" << posts[i].hearts << " hearts)" << std::endl;
      }
    }

    void addHearts(size_t index, int hearts) {
      if (index >= posts.size()) {
        std::cout << "Cannot edit post " << index << "." << std::endl;
        return;
      }

      posts[index].hearts += hearts;
      std::cout << "Added " << hearts << " hearts to post " << index << "." << std::endl;
    }

    size_t size() const {
      return posts.size();
    }
};

enum class Screen {
  MainMenu,
  ViewingPosts,
  EditingPost,
  Quit
};

std::string screenName(Screen screen) {
  switch (screen) {
    case Screen::MainMenu:
      return "MainMenu";
    case Screen::ViewingPosts:
      return "ViewingPosts";
    case Screen::EditingPost:
      return "EditingPost";
    case Screen::Quit:
      return "Quit";
  }

  return "Unknown";
}

Screen handleCommand(Screen currentScreen, const std::string& command, Profile& profile) {
  std::cout << "\nState: " << screenName(currentScreen) << ", command: " << command << std::endl;

  switch (currentScreen) {
    case Screen::MainMenu:
      if (command == "view") {
        return Screen::ViewingPosts;
      }
      if (command == "edit") {
        return profile.size() == 0 ? Screen::MainMenu : Screen::EditingPost;
      }
      if (command == "quit") {
        return Screen::Quit;
      }
      std::cout << "Main menu commands: view, edit, quit" << std::endl;
      return Screen::MainMenu;

    case Screen::ViewingPosts:
      profile.printPosts();
      if (command == "back") {
        return Screen::MainMenu;
      }
      if (command == "edit") {
        return Screen::EditingPost;
      }
      std::cout << "Viewing commands: back, edit" << std::endl;
      return Screen::ViewingPosts;

    case Screen::EditingPost:
      if (command == "like-first") {
        profile.addHearts(0, 5);
        return Screen::EditingPost;
      }
      if (command == "back") {
        return Screen::MainMenu;
      }
      std::cout << "Editing commands: like-first, back" << std::endl;
      return Screen::EditingPost;

    case Screen::Quit:
      return Screen::Quit;
  }

  return Screen::Quit;
}

int main() {
  Profile profile;
  profile.addPost("Vectors make this version manageable.", 24);
  profile.addPost("A state diagram keeps the command loop readable.", 31);

  std::vector<std::string> scriptedCommands = {
      "view",
      "edit",
      "like-first",
      "back",
      "view",
      "back",
      "quit"
  };

  Screen screen = Screen::MainMenu;
  for (const std::string& command : scriptedCommands) {
    if (screen == Screen::Quit) {
      break;
    }

    screen = handleCommand(screen, command, profile);
  }

  std::cout << "\nFinal state: " << screenName(screen) << std::endl;
  return 0;
}

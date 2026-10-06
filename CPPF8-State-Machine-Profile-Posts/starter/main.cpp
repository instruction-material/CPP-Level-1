#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

struct Post { std::string caption; int hearts; };
class Profile {
  private:
    std::vector<Post> posts;
  public:
    void addPost(const std::string& caption, int hearts) {
        // TODO: validate the authored bounds before storing a post.
        static_cast<void>(caption); static_cast<void>(hearts);
    }
    void printPosts() const {
        // TODO: display an empty message or each zero-based index and record.
    }
    void addHearts(std::size_t index, int hearts) {
        // TODO: validate the index and signed change before mutation.
        static_cast<void>(index); static_cast<void>(hearts);
    }
    std::size_t size() const {
        // TODO: return the collection size.
        return 0;
    }
};
enum class Screen { MainMenu, ViewingPosts, EditingPost, Quit };
std::string screenName(Screen screen) {
    // TODO: use switch to return the name of every state.
    static_cast<void>(screen);
    return "Incomplete";
}
Screen handleCommand(Screen screen, const std::string& command, Profile& profile) {
    // TODO: implement the state table, guarded edits and absorbing Quit.
    static_cast<void>(command); static_cast<void>(profile);
    return screen;
}
int main() {
    // TODO: seed the two fictional posts and process the repeatable command list.
    // TODO: stop after Quit and print the final state.
    std::cerr << "Complete the profile state-machine starter.\n";
    return 2;
}

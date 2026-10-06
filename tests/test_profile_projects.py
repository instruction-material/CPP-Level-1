"""Independent capstone command, model and state-transition contracts."""
import os
from pathlib import Path
import random
import re
import tempfile
import unittest

from test_foundation_projects import ROOT, execute

CORE = 'CPPF8-Profile-Posts'
STATES = 'CPPF8-State-Machine-Profile-Posts'


class ProfileContracts(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temp = tempfile.TemporaryDirectory(prefix='cpp-profile-contracts-')
        cls.addClassCleanup(cls.temp.cleanup)
        cls.compiler = os.environ.get('CXX', 'c++')
        cls.flags = ['-std=c++20', '-Wall', '-Wextra', '-Wpedantic', '-Werror']
        cls.sanitizers = os.environ.get('SOURCE_SANITIZERS', '1') == '1'
        cls.binaries = {}
        for folder in [CORE, STATES]:
            for part in ['', 'starter', 'solution']:
                directory = ROOT / folder / part
                sources = sorted(directory.glob('*.cpp'))
                binary = Path(cls.temp.name) / (folder + '-' + (part or 'root'))
                code, out, err = execute([cls.compiler, *cls.flags,
                    *map(str, sources), '-o', str(binary)])
                assert code == 0, out + err
                cls.binaries[folder, part] = binary

    def run_core(self, text, part='solution'):
        code, out, err = execute([str(self.binaries[CORE, part])], text=text, timeout=5)
        self.assertEqual((code, err), (0, ''), out + err)
        self.assertEqual(out.count('Goodbye.'), 1)
        return out

    def harness(self, body, *, extension=False):
        path = Path(self.temp.name) / ('states-harness.cpp' if extension else 'profile-harness.cpp')
        common = ('#include <cassert>\n#include <limits>\n#include <sstream>\n'
                  '#include <iostream>\n#include <string>\n')
        if extension:
            includes = '#define main suppliedMain\n#include "main.cpp"\n#undef main\n'
            sources = [str(path)]
            directory = ROOT / STATES / 'solution'
        else:
            includes = '#include "profile.h"\n#include "profile.h"\n'
            sources = [str(path), str(ROOT / CORE / 'solution/profile.cpp')]
            directory = ROOT / CORE / 'solution'
        path.write_text(includes + common + '\nint main() {\n' + body + '\n}\n')
        binary = path.with_suffix('')
        flags = self.flags + (['-g', '-fno-omit-frame-pointer', '-fsanitize=address,undefined'] if self.sanitizers else [])
        code, out, err = execute([self.compiler, *flags, '-I', str(directory), *sources, '-o', str(binary)])
        self.assertEqual(code, 0, out + err)
        code, out, err = execute([str(binary)], timeout=10)
        self.assertEqual((code, err), (0, ''), out + err)
        return out

    def test_starters_have_full_matching_briefs_and_original_source_names(self):
        for folder, message in [(CORE, 'Complete the profile model and interactive driver.\n'),
                                (STATES, 'Complete the profile state-machine starter.\n')]:
            code, out, err = execute([str(self.binaries[folder, 'starter'])])
            self.assertEqual((code, out, err), (2, '', message))
            for part in ['starter', 'solution']:
                self.assertEqual((ROOT / folder / part / 'README.md').read_bytes(),
                                 (ROOT / folder / 'README.md').read_bytes())
            self.assertNotEqual((ROOT / folder / 'starter/main.cpp').read_bytes(),
                                (ROOT / folder / 'solution/main.cpp').read_bytes())
        for part in ['starter', 'solution']:
            self.assertEqual(sorted(p.name for p in (ROOT / CORE / part).glob('*')),
                             ['README.md', 'main.cpp', 'profile.cpp', 'profile.h'])
        self.assertEqual((ROOT / CORE / 'starter/profile.h').read_bytes(),
                         (ROOT / CORE / 'solution/profile.h').read_bytes())
        self.assertNotEqual((ROOT / CORE / 'starter/profile.cpp').read_bytes(),
                            (ROOT / CORE / 'solution/profile.cpp').read_bytes())

    def test_interactive_full_workflow_and_index_shift(self):
        transcript = ('2\n1\nFirst practice post\n30\n1\nSecond practice post\n100\n'
                      '1\nThird practice post\n45\n2\n6\n4\n1\n10\n5\n2\n2\n6\n3\n2\n0\n')
        out = self.run_core(transcript)
        self.assertIn('This profile does not have any posts yet.', out)
        self.assertEqual(re.findall(r'Total hearts: (\d+)', out), ['175', '85'])
        self.assertEqual(out.count('Caption: Second practice post'), 1)
        self.assertIn('Post number: 2\nCaption: Third practice post\nHearts: 45', out)
        self.assertIn('Hearts: 40', out)
        self.assertEqual(self.run_core(transcript, part=''), out)

    def test_bad_numeric_lines_recover_without_partial_operations(self):
        for bad in ['', '2x', '1.5', '1e2', '1 2', '+', '--1', '2147483648', '-2147483649']:
            with self.subTest(bad=bad):
                out = self.run_core('1\nExisting\n10\n' + bad + '\n6\n0\n')
                self.assertIn('Invalid integer. Operation cancelled.', out)
                self.assertEqual(re.findall(r'Total hearts: (\d+)', out), ['10'])
                out = self.run_core('1\nExisting\n10\n1\nCancelled\n' + bad + '\n2\n6\n0\n')
                self.assertNotIn('Caption: Cancelled', out)
                self.assertEqual(re.findall(r'Total hearts: (\d+)', out), ['10'])
                out = self.run_core('1\nExisting\n10\n4\n1\n' + bad + '\n6\n0\n')
                self.assertEqual(re.findall(r'Total hearts: (\d+)', out), ['10'])
        out = self.run_core('  +01 \nSign and zeroes\n +00010 \n6\n99\n0\n')
        self.assertEqual(re.findall(r'Total hearts: (\d+)', out), ['10'])
        self.assertIn('Invalid command.', out)

    def test_input_end_at_every_prompt_exits_once_without_claiming_mutation(self):
        for text in ['', '1\n', '1\nUnfinished\n', '3\n', '4\n', '4\n1\n', '5\n']:
            with self.subTest(text=text):
                out = self.run_core(text)
                self.assertNotIn('Caption: Unfinished', out)
                self.assertNotIn('Total hearts:', out)
        self.run_core('1\nExisting\n10\n4\n1\n')

    def test_index_validation_and_signed_change_limits(self):
        for number in ['0', '-1', '1001', '2147483647', '2']:
            out = self.run_core('1\nKeep\n10\n3\n' + number + '\n4\n' + number +
                               ('\n1' if number == '2' else '') + '\n5\n' + number + '\n6\n0\n')
            self.assertEqual(re.findall(r'Total hearts: (\d+)', out)[-1:], ['10'])
        out = self.run_core('1\nKeep\n10\n4\n1\n-10\n6\n4\n1\n1000000\n6\n'
                            '4\n1\n1\n4\n1\n-1000001\n4\n1\n2147483647\n'
                            '4\n1\n-2147483648\n6\n0\n')
        self.assertEqual(re.findall(r'Total hearts: (\d+)', out), ['0', '1000000', '1000000'])

    def test_model_all_methods_const_views_copy_and_extreme_indexes(self):
        self.harness(r'''
Profile original;
assert(original.size() == 0 && original.sumHearts() == 0);
original.addPost({"First", 30}); original.addPost({"Second", 100});
original.addPost({"Third", 45}); assert(original.sumHearts() == 175);
Profile copy = original; copy.addHearts(0, 10); copy.removePost(1);
assert(copy.size() == 2 && copy.sumHearts() == 85);
assert(original.size() == 3 && original.sumHearts() == 175);
std::ostringstream output; auto previous = std::cout.rdbuf(output.rdbuf());
const Profile& view = copy; view.printPost(1); view.printPosts();
assert(output.str().find("Post number: 2\nCaption: Third\nHearts: 45\n") != std::string::npos);
assert(copy.size() == 2 && copy.sumHearts() == 85);
for (auto index : {std::size_t{2}, std::numeric_limits<std::size_t>::max()}) {
    copy.printPost(index); copy.removePost(index); copy.addHearts(index, 1);
    assert(copy.size() == 2 && copy.sumHearts() == 85);
}
copy.addHearts(0, std::numeric_limits<int>::min());
copy.addHearts(0, std::numeric_limits<int>::max());
assert(copy.sumHearts() == 85);
copy.removePost(1); copy.removePost(0); copy.printPosts();
assert(copy.size() == 0 && copy.sumHearts() == 0);
assert(output.str().find("This profile does not have any posts yet.\n") != std::string::npos);
std::cout.rdbuf(previous);
''')

    def test_model_caption_count_and_heart_boundaries(self):
        self.harness(r'''
Profile p;
std::ostringstream errors; auto old = std::cout.rdbuf(errors.rdbuf());
for (const Post& post : {Post{"", 0}, Post{std::string(4097, 'x'), 1},
                         Post{"negative", -1}, Post{"large", 1000001}}) {
    p.addPost(post); assert(p.size() == 0 && p.sumHearts() == 0);
}
p.addPost({std::string(4096, 'x'), 0}); assert(p.size() == 1);
p.removePost(0);
for (int index = 0; index < 1000; ++index) p.addPost({"Fictional", 1000000});
assert(p.size() == 1000 && p.sumHearts() == 1000000000);
p.addPost({"Extra", 1}); assert(p.size() == 1000 && p.sumHearts() == 1000000000);
p.addHearts(999, -1000000); assert(p.sumHearts() == 999000000);
p.removePost(0); p.addPost({"Replacement", 0});
assert(p.size() == 1000 && p.sumHearts() == 998000000);
std::cout.rdbuf(old);
''')
        out = self.run_core('1\n\n1\n' + 'x' * 4097 + '\n6\n0\n')
        self.assertEqual(re.findall(r'Total hearts: (\d+)', out), ['0'])

    def test_seeded_independent_collection_oracle(self):
        rng = random.Random(20261005)
        posts = []
        body = ['Profile p; std::ostringstream sink; auto old = std::cout.rdbuf(sink.rdbuf());']
        for step in range(350):
            action = rng.choice(['add', 'update', 'remove'])
            if action == 'add':
                hearts = rng.choice([-1, 0, 5, 1000000, 1000001])
                body.append(f'p.addPost({{"Fictional {step}", {hearts}}});')
                if 0 <= hearts <= 1000000 and len(posts) < 1000:
                    posts.append([f'Fictional {step}', hearts])
            else:
                index = rng.randrange(len(posts) + 3)
                if action == 'remove':
                    body.append(f'p.removePost({index});')
                    if index < len(posts): posts.pop(index)
                else:
                    delta = rng.choice([-1000001, -5, 0, 5, 1000001, 2147483647, -2147483647])
                    body.append(f'p.addHearts({index}, {delta});')
                    if index < len(posts) and 0 <= posts[index][1] + delta <= 1000000:
                        posts[index][1] += delta
            body.append(f'assert(p.size() == {len(posts)} && p.sumHearts() == {sum(p[1] for p in posts)});')
        body.append('sink.str(""); p.printPosts(); std::cout.rdbuf(old); std::cout << sink.str();')
        out = self.harness('\n'.join(body))
        observed = re.findall(r'Caption: (.*?)\nHearts: (\d+)\n', out)
        self.assertEqual(observed, [(caption, str(hearts)) for caption, hearts in posts])

    def test_private_collection_cannot_be_mutated_from_driver(self):
        path = Path(self.temp.name) / 'privacy.cpp'
        path.write_text('#include "profile.h"\nint main() { Profile p; p.myPosts.push_back({"Bad", -1}); }\n')
        code, out, err = execute([self.compiler, *self.flags, '-I', str(ROOT / CORE / 'solution'),
                                  '-c', str(path), '-o', str(path.with_suffix('.o'))])
        self.assertNotEqual(code, 0, out + err)
        self.assertIn('private', err)

    def test_optional_state_table_empty_guards_and_absorbing_quit(self):
        self.harness(r'''
Profile p;
assert(handleCommand(Screen::MainMenu, "edit", p) == Screen::MainMenu);
assert(handleCommand(Screen::ViewingPosts, "edit", p) == Screen::ViewingPosts);
assert(handleCommand(Screen::MainMenu, "view", p) == Screen::ViewingPosts);
assert(handleCommand(Screen::MainMenu, "quit", p) == Screen::Quit);
p.addPost("First", 24); p.addPost("Second", 31);
assert(handleCommand(Screen::MainMenu, "edit", p) == Screen::EditingPost);
assert(handleCommand(Screen::ViewingPosts, "edit", p) == Screen::EditingPost);
assert(handleCommand(Screen::ViewingPosts, "back", p) == Screen::MainMenu);
assert(handleCommand(Screen::EditingPost, "back", p) == Screen::MainMenu);
for (Screen screen : {Screen::MainMenu, Screen::ViewingPosts, Screen::EditingPost}) {
    assert(handleCommand(screen, "unknown", p) == screen);
}
assert(handleCommand(Screen::ViewingPosts, "quit", p) == Screen::ViewingPosts);
assert(handleCommand(Screen::EditingPost, "quit", p) == Screen::EditingPost);
assert(handleCommand(Screen::EditingPost, "like-first", p) == Screen::EditingPost);
std::ostringstream output; auto old = std::cout.rdbuf(output.rdbuf());
p.printPosts(); auto before = output.str();
assert(before.find("0: First (29 hearts)") != std::string::npos);
assert(before.find("1: Second (31 hearts)") != std::string::npos);
for (const auto& command : {"like-first", "edit", "view", "back", "quit", "unknown"}) {
    assert(handleCommand(Screen::Quit, command, p) == Screen::Quit);
}
output.str(""); p.printPosts(); assert(output.str() == before);
p.addHearts(0, 999971); output.str(""); p.printPosts();
assert(output.str().find("0: First (1000000 hearts)") != std::string::npos);
p.addHearts(0, 1); p.addHearts(0, std::numeric_limits<int>::min());
p.addHearts(0, std::numeric_limits<int>::max()); p.addHearts(99, 1);
output.str(""); p.printPosts();
assert(output.str().find("0: First (1000000 hearts)") != std::string::npos);
p.addHearts(0, -1000000); output.str(""); p.printPosts();
assert(output.str().find("0: First (0 hearts)") != std::string::npos);
std::cout.rdbuf(old);
''', extension=True)

    def test_optional_script_stays_repeatable_and_distinct_from_interactive_core(self):
        code, out, err = execute([str(self.binaries[STATES, 'solution'])])
        self.assertEqual((code, err), (0, ''))
        self.assertEqual(re.findall(r'State: (\w+), command: ([\w-]+)', out), [
            ('MainMenu', 'view'), ('ViewingPosts', 'edit'), ('EditingPost', 'like-first'),
            ('EditingPost', 'back'), ('MainMenu', 'view'), ('ViewingPosts', 'back'),
            ('MainMenu', 'quit')])
        self.assertIn('0: Vectors make this version manageable. (29 hearts)', out)
        self.assertIn('1: A state diagram keeps the command loop readable. (31 hearts)', out)
        self.assertTrue(out.endswith('Final state: Quit\n'))
        self.assertEqual(execute([str(self.binaries[STATES, ''])]), (code, out, err))

    def test_make_selects_only_one_pack_and_always_rebuilds(self):
        for folder in [CORE, STATES]:
            for part in ['starter', 'solution']:
                code, out, err = execute(['make', '-n', 'PACK=' + part], cwd=ROOT / folder)
                self.assertEqual(code, 0, out + err)
                self.assertIn(part + '/main.cpp', out)
                self.assertNotIn(('solution' if part == 'starter' else 'starter') + '/', out)
                if folder == CORE: self.assertIn(part + '/profile.cpp', out)
            code, out, err = execute(['make', '-n', 'PACK=both'], cwd=ROOT / folder)
            self.assertNotEqual(code, 0)
            self.assertIn('PACK must be starter or solution', err)


if __name__ == '__main__':
    unittest.main()

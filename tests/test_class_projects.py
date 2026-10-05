"""Independent multi-file class contracts, encapsulation and lesson equivalence."""
import os
from pathlib import Path
import tempfile
import unittest

from test_foundation_projects import ROOT, execute

PACKS = ['CPPF4-Person-Class', 'CPPF4-Cat-Class']
REFERENCES = [(PACKS[0] + '/solution', 'person'), (PACKS[1] + '/solution', 'cat'),
              ('CPPF4-Person-Class-with-BMI', 'person'), ('CPPF4-Point-Class', 'point')]


class ClassContracts(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temporary = tempfile.TemporaryDirectory(prefix='cpp-class-contracts-')
        cls.addClassCleanup(cls.temporary.cleanup)
        cls.compiler = os.environ.get('CXX', 'c++')
        cls.flags = ['-std=c++20', '-Wall', '-Wextra', '-Wpedantic', '-Werror']
        cls.instrumented = os.environ.get('SOURCE_SANITIZERS', '1') == '1'
        cls.binaries = {}
        for folder, stem in REFERENCES:
            directory = ROOT / folder
            for sanitized in [False, True] if cls.instrumented else [False]:
                output = Path(cls.temporary.name) / (folder.replace('/', '-') + ('-asan' if sanitized else ''))
                flags = cls.flags + (['-g', '-fno-omit-frame-pointer', '-fsanitize=address,undefined'] if sanitized else [])
                code, out, err = execute([cls.compiler, *flags, str(directory / 'main.cpp'),
                                         str(directory / (stem + '.cpp')), '-o', str(output)])
                assert code == 0, out + err
                cls.binaries[folder, sanitized] = output

    def harness(self, folder, stem, body):
        path = Path(self.temporary.name) / (folder.replace('/', '-') + '-harness.cpp')
        path.write_text('#include "' + stem + '.h"\n#include "' + stem + '.h"\n' +
            '#include <cassert>\n#include <limits>\n#include <sstream>\n#include <iostream>\n' +
            '#include <string>\nint main() {\n' + body + '\n}\n')
        output = path.with_suffix('')
        flags = self.flags + (['-g', '-fno-omit-frame-pointer', '-fsanitize=address,undefined'] if self.instrumented else [])
        code, out, err = execute([self.compiler, *flags, '-I', str(ROOT / folder), str(path),
                                 str(ROOT / folder / (stem + '.cpp')), '-o', str(output)])
        self.assertEqual(code, 0, out + err)
        code, out, err = execute([str(output)], timeout=10)
        self.assertEqual((code, err), (0, ''), out + err)

    def test_incomplete_starters_and_matched_briefs(self):
        for folder, stem in zip(PACKS, ['person', 'cat']):
            directory = ROOT / folder / 'starter'
            output = Path(self.temporary.name) / (stem + '-starter')
            code, out, err = execute([self.compiler, *self.flags, str(directory / 'main.cpp'),
                                     str(directory / (stem + '.cpp')), '-o', str(output)])
            self.assertEqual(code, 0, out + err)
            code, out, err = execute([str(output)])
            self.assertEqual((code, out, err), (2, '', 'Complete the starter class and driver.\n'))
            self.assertIn('TODO', (directory / (stem + '.cpp')).read_text())
            self.assertNotEqual((directory / (stem + '.cpp')).read_bytes(),
                                (ROOT / folder / 'solution' / (stem + '.cpp')).read_bytes())
            for part in ['starter', 'solution']:
                self.assertEqual((ROOT / folder / part / 'README.md').read_bytes(),
                                 (ROOT / folder / 'README.md').read_bytes())
                self.assertEqual((ROOT / folder / part / (stem + '.h')).read_bytes(),
                                 (directory / (stem + '.h')).read_bytes())

    def test_person_all_methods_height_boundaries_and_independent_state(self):
        body = r'''
Person a;
assert(a.getName() == "Unknown" && a.getAge() == 0 && a.getHeight() == 0);
assert(a.getBirthday() == "January 1, 1970");
assert(a.getBirthLocation() == "Somewhere over the rainbow");
assert(a.toString() == "Name: Unknown, Age: 0, Birthday: January 1, 1970, Birth Location: Somewhere over the rainbow, Height: 0' 0\"");
Person b(21, "Jenny", 60, "January 1", "USA");
assert(b.getName() == "Jenny" && b.getAge() == 21 && b.getHeight() == 60);
assert(b.getBirthday() == "January 1" && b.getBirthLocation() == "USA");
Person copy = b;
copy.setName("Alex"); copy.setAge(-1); copy.setHeight(66);
assert(copy.getName() == "Alex" && copy.getAge() == -1 && copy.getHeight() == 66);
assert(copy.getBirthday() == "January 1" && copy.getBirthLocation() == "USA");
assert(copy.toString() == "Name: Alex, Age: -1, Birthday: January 1, Birth Location: USA, Height: 5' 6\"");
assert(b.getName() == "Jenny" && b.getAge() == 21 && b.getHeight() == 60);
assert(a.getName() == "Unknown");
for (int inches : {0, 11, 12, 13, 60, 66, std::numeric_limits<int>::max()}) {
    copy.setHeight(inches);
    auto expected = std::to_string(inches / 12) + "' " + std::to_string(inches % 12) + "\"";
    assert(copy.getHeight() == inches && copy.toString().ends_with("Height: " + expected));
}
copy.setName(""); assert(copy.getName().empty());
copy.setAge(std::numeric_limits<int>::max()); assert(copy.getAge() == std::numeric_limits<int>::max());
copy.setHeight(-1); assert(copy.getHeight() == -1);
'''
        for folder in [PACKS[0] + '/solution', 'CPPF4-Person-Class-with-BMI']:
            self.harness(folder, 'person', body)

    def test_person_initializer_lesson_preserves_complete_interface_and_output(self):
        expected = ('Name: Unknown, Age: 0, Birthday: January 1, 1970, Birth Location: Somewhere over the rainbow, Height: 0\' 0"\n'
                    'Name: Jenny, Age: 21, Birthday: January 1, Birth Location: USA, Height: 5\' 0"\n'
                    'Alex, 22, 66, January 1, USA\n'
                    'Name: Alex, Age: 22, Birthday: January 1, Birth Location: USA, Height: 5\' 6"\n')
        for folder in [PACKS[0] + '/solution', 'CPPF4-Person-Class-with-BMI']:
            self.assertEqual((ROOT / folder / 'person.h').read_bytes(),
                             (ROOT / PACKS[0] / 'solution/person.h').read_bytes())
            code, out, err = execute([str(self.binaries[folder, False])])
            self.assertEqual((code, out, err), (0, expected, ''))

    def test_cat_constructors_updates_pluralization_and_independent_state(self):
        self.harness(PACKS[1] + '/solution', 'cat', r'''
Cat a;
assert(a.toString() == "Hello human, my name is cat. My breed is unknown. I am currently 0 years old. My color is unknown.");
Cat b("Milo", "tabby", 1, "orange"); Cat copy = b;
assert(b.toString() == "Hello human, my name is Milo. My breed is tabby. I am currently 1 year old. My color is orange.");
std::ostringstream output; auto old = std::cout.rdbuf(output.rdbuf());
for (int age : {0, 1, 2, -1, std::numeric_limits<int>::max(), std::numeric_limits<int>::min()}) {
    copy.changeAge(age);
    assert(output.str() == "Age successfully changed to: " + std::to_string(age) + "\n");
    output.str("");
    assert(copy.toString().find("currently " + std::to_string(age) + (age == 1 ? " year old" : " years old")) != std::string::npos);
}
copy.changeBreed("zsh");
assert(output.str() == "Breed successfully changed to: zsh\n");
std::cout.rdbuf(old);
assert(copy.toString().find("breed is zsh") != std::string::npos);
assert(copy.toString().find("name is Milo") != std::string::npos);
assert(copy.toString().find("color is orange") != std::string::npos);
assert(b.toString().find("breed is tabby") != std::string::npos);
assert(b.toString().find("1 year old") != std::string::npos);
assert(a.toString().find("name is cat") != std::string::npos);
''')

    def test_cat_meow_eat_and_pet_output(self):
        self.harness(PACKS[1] + '/solution', 'cat', r'''
Cat a("Milo", "tabby", 2, "orange");
std::ostringstream output; auto old = std::cout.rdbuf(output.rdbuf());
a.meow(0); a.meow(-1); assert(output.str().empty());
a.meow(3);
assert(output.str() == "Hello human, my name is Milo. Meow.\nHello human, my name is Milo. Meow.\nHello human, my name is Milo. Meow.\n");
output.str(""); a.eat(); assert(output.str() == "Milo ate.\n");
output.str(""); a.pet();
assert(output.str() == "Thank you for petting me. I will now meow.\nHello human, my name is Milo. Meow.\n");
std::cout.rdbuf(old);
''')

    def test_point_complete_lesson_output_and_state(self):
        code, out, err = execute([str(self.binaries['CPPF4-Point-Class', False])])
        self.assertEqual((code, out, err), (0,
            'This is a point with coordinates x: 0 and y: 0\n'
            'This is a point with coordinates x: -1 and y: 1\n'
            'This is a point with coordinates x: -1 and y: 0\n0\n', ''))
        self.harness('CPPF4-Point-Class', 'point', r'''
Point a; Point b(-1, 1); Point copy = b;
assert(a.getX() == 0 && a.getY() == 0);
copy.setX(12); copy.setY(-13);
assert(copy.getX() == 12 && copy.getY() == -13);
assert(copy.toString() == "This is a point with coordinates x: 12 and y: -13");
assert(b.getX() == -1 && b.getY() == 1 && a.getY() == 0);
''')

    def test_private_fields_reject_direct_driver_access(self):
        for folder, stem, cls, field in [(PACKS[0] + '/solution', 'person', 'Person', 'mAge'),
                                        (PACKS[1] + '/solution', 'cat', 'Cat', 'myAge'),
                                        ('CPPF4-Point-Class', 'point', 'Point', 'x')]:
            path = Path(self.temporary.name) / (stem + '-private.cpp')
            path.write_text('#include "' + stem + '.h"\nint main() { ' + cls + ' value; return value.' + field + '; }\n')
            code, out, err = execute([self.compiler, *self.flags, '-I', str(ROOT / folder),
                                     '-fsyntax-only', str(path)])
            self.assertNotEqual(code, 0)
            self.assertIn('private', err)

    def test_makefiles_select_one_program_without_recursive_duplicates(self):
        for folder, stem in zip(PACKS, ['person', 'cat']):
            for part in ['starter', 'solution']:
                code, out, err = execute(['make', '-n', '-B', 'PART=' + part], cwd=ROOT / folder)
                self.assertEqual(code, 0, out + err)
                self.assertIn(part + '/main.cpp', out)
                self.assertIn(part + '/' + stem + '.cpp', out)
                self.assertNotIn(('solution' if part == 'starter' else 'starter') + '/', out)

    def test_sanitized_class_and_complete_lesson_drivers(self):
        if not self.instrumented:
            self.skipTest('SOURCE_SANITIZERS=0 explicitly disables instrumentation')
        for folder, _ in REFERENCES:
            code, out, err = execute([str(self.binaries[folder, True])], timeout=10)
            self.assertEqual((code, err), (0, ''), out + err)


if __name__ == '__main__': unittest.main()

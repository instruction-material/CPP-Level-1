"""Independent CPPF6 caller-state, literal transformation and growth contracts."""
import os
from pathlib import Path
import re
import tempfile
import unittest

from test_foundation_projects import ROOT, execute

PACKS = ['CPPF6-Parameter-Passing', 'CPPF6-Defanging-a-Website-URL', 'CPPF6-Chaos-Monkeys']
LESSONS = ['CPPF6-Parameter-Passing-Introduction', 'CPPF6-Structs-Example']


class ParameterContracts(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temporary = tempfile.TemporaryDirectory(prefix='cpp-parameter-contracts-')
        cls.addClassCleanup(cls.temporary.cleanup)
        cls.compiler = os.environ.get('CXX', 'c++')
        cls.flags = ['-std=c++20', '-Wall', '-Wextra', '-Wpedantic', '-Werror']
        cls.instrumented = os.environ.get('SOURCE_SANITIZERS', '1') == '1'
        cls.binaries = {}
        for folder in [*PACKS, *LESSONS, 'CPPF6-Parameter-Passing-Starter']:
            for part in (['', 'starter', 'solution'] if folder in PACKS else ['']):
                directory = ROOT / folder / part
                output = Path(cls.temporary.name) / (folder + '-' + (part or 'root'))
                code, out, err = execute([cls.compiler, *cls.flags, str(directory / 'main.cpp'), '-o', str(output)])
                assert code == 0, out + err
                cls.binaries[folder, part] = output
            if folder in PACKS and cls.instrumented:
                output = Path(cls.temporary.name) / (folder + '-sanitized')
                code, out, err = execute([cls.compiler, *cls.flags, '-g', '-fno-omit-frame-pointer',
                    '-fsanitize=address,undefined', str(ROOT / folder / 'solution/main.cpp'), '-o', str(output)])
                assert code == 0, out + err
                cls.binaries[folder, 'sanitized'] = output

    def harness(self, folder, body, *, expect_compile=True):
        path = Path(self.temporary.name) / (folder + '-harness.cpp')
        path.write_text('#define main supplied_driver\n#include "' +
            str(ROOT / folder / 'solution/main.cpp') + '"\n#undef main\n'
            '#include <cassert>\n#include <sstream>\nint main() {\n' + body + '\n}\n')
        output = path.with_suffix('')
        flags = self.flags + (['-g', '-fno-omit-frame-pointer', '-fsanitize=address,undefined'] if self.instrumented else [])
        code, out, err = execute([self.compiler, *flags, str(path), '-o', str(output)])
        if not expect_compile:
            self.assertNotEqual(code, 0, out + err)
            self.assertRegex(err, r'const|read-only|cannot assign')
            return
        self.assertEqual(code, 0, out + err)
        self.assertEqual(execute([str(output)], timeout=10), (0, '', ''))

    def test_starters_are_incomplete_with_equal_complete_briefs(self):
        reminders = ['parameter-passing predictions and driver', 'defanging starter and its checks', 'chaos-monkeys starter and its checks']
        for folder, reminder in zip(PACKS, reminders):
            self.assertEqual(execute([str(self.binaries[folder, 'starter'])]),
                             (2, '', 'Complete the ' + reminder + '.\n'))
            self.assertIn('TODO', (ROOT / folder / 'starter/main.cpp').read_text())
            self.assertNotEqual((ROOT / folder / 'starter/main.cpp').read_bytes(),
                                (ROOT / folder / 'solution/main.cpp').read_bytes())
            for part in ['starter', 'solution']:
                self.assertEqual((ROOT / folder / part / 'README.md').read_bytes(),
                                 (ROOT / folder / 'README.md').read_bytes())
        self.assertEqual(execute([str(self.binaries['CPPF6-Parameter-Passing-Starter', ''])]),
                         execute([str(self.binaries[PACKS[0], 'starter'])]))

    def test_tracing_reference_checks_all_functions_and_correct_copy_prediction(self):
        code, out, err = execute([str(self.binaries[PACKS[0], 'solution'])])
        self.assertEqual((code, err), (0, ''))
        self.assertIn('Testing passing an int by value: \nExpected: 10; Actual: 10\n', out)
        self.assertEqual(out.count('Expected: 10; Actual: 10'), 2)
        self.assertIn('Expected: 20; Actual: 20', out)
        self.assertIn('Sum of two integers passed by value: 50\n', out)
        self.assertIn('twoVal1: 10\ntwoVal2: 10\n', out)
        self.assertIn('Sum of two integers passed by reference: 50\n', out)
        self.assertIn('twoVal3: 20\ntwoVal4: 30\n', out)
        self.assertIn('Sum of two integers passed by const reference: 20\n', out)
        self.assertIn('twoVal5: 10\ntwoVal6: 10\n', out)
        self.assertEqual(out.count('Expected: Hello World!; Actual: Hello World!'), 2)
        self.assertIn('Expected: !Olleh Dlrow; Actual: !Olleh Dlrow', out)
        self.assertEqual(execute([str(self.binaries[PACKS[0], ''])]), (code, out, err))

    def test_parameter_helpers_preserve_copies_and_observers_and_mutate_aliases(self):
        self.harness(PACKS[0], r'''
for (int input : {-1000000, -1, 0, 1, 1000000}) {
    int value = input; intVal(value); assert(value == input);
    intConstRef(value); assert(value == input);
    intRef(value); assert(value == 20);
    int first = input, second = -input;
    assert(addTwoVals(first, second) == 50 && first == input && second == -input);
    assert(addTwoValsConstRef(first, second) == 0 && first == input && second == -input);
    assert(addTwoValsRef(first, second) == 50 && first == 20 && second == 30);
}
assert(addTwoValsConstRef(1000000, 1000000) == 2000000);
assert(addTwoValsConstRef(-1000000, -1000000) == -2000000);
int shared = 10; assert(addTwoValsRef(shared, shared) == 60 && shared == 30);
for (const auto original : {"", "Hello World!", "two words", "banana"}) {
    std::string text = original; stringVal(text); assert(text == original);
    stringConstRef(text); assert(text == original);
    stringRef(text); assert(text == "!Olleh Dlrow");
}
''')

    def test_const_mutation_is_rejected_without_running_dangling_examples(self):
        self.harness(PACKS[0], 'const int value = 10; value = 20;', expect_compile=False)
        self.harness(PACKS[2], 'const std::string text = "banana"; text.insert(0, 1, \'a\');', expect_compile=False)

    def test_defang_helpers_cover_empty_brackets_utf8_and_bounded_growth(self):
        self.harness(PACKS[1], r'''
const std::string inputs[]{"", "plain", ".", "..", ".example.", "www.example.com", "[.]", "猫.🙂", std::string(4096, '.')};
for (const auto& original : inputs) {
    std::string expected;
    for (std::size_t i = 0; i < original.size(); ++i)
        expected += original[i] == '.' ? "[.]" : std::string(1, original[i]);
    std::string observed = original;
    assert(defangValue(observed) == expected && observed == original);
    defang(observed); assert(observed == expected);
}
std::string dot = "."; defang(dot); assert(dot == "[.]");
defang(dot); assert(dot == "[[.]]");
''')

    def test_defang_driver_token_rules_and_failure_results(self):
        for original in ['plain', '.', '..', '.example.', 'www.example.com', '[.]', '猫.🙂', '.' * 4096]:
            expected = original.replace('.', '[.]')
            for separator in [' ', '\t', '\n', '\r\n']:
                result = execute([str(self.binaries[PACKS[1], 'solution'])], text=separator + original + separator + 'ignored')
                self.assertEqual(result, (0, '\nEnter a website: ' + expected + '\n' + expected + '\n', ''))
        for text, error in [('', 'Missing website address.'), (' \t\r\n', 'Missing website address.'),
                            ('x' * 4097, 'Website address is too long.')]:
            self.assertEqual(execute([str(self.binaries[PACKS[1], 'solution'])], text=text),
                             (1, '\nEnter a website: ', error + '\n'))
        self.assertEqual(execute([str(self.binaries[PACKS[1], ''])], text='www.example.com'),
                         execute([str(self.binaries[PACKS[1], 'solution'])], text='www.example.com'))

    def test_chaos_copy_reference_const_state_and_seeded_repetition(self):
        self.harness(PACKS[2], r'''
std::ostringstream captured; auto* previous = std::cout.rdbuf(captured.rdbuf());
for (const auto& original : {std::string(), std::string("A"), std::string("bananas"), std::string("AaZ!"), std::string(4096, 'X')}) {
    std::string caller = original;
    std::srand(6006); valueMonkey(caller); assert(caller == original);
    const std::string localLine = captured.str(); captured.str("");
    const std::string valuePrefix = "Oh no! The value monkeys changed our value to: ";
    assert(localLine.starts_with(valuePrefix) && localLine.ends_with("\n"));
    const std::string local = localLine.substr(valuePrefix.size(), localLine.size() - valuePrefix.size() - 1);
    std::srand(6006); refMonkey(caller);
    assert(caller == local && caller.size() == original.size() * 2);
    for (std::size_t i = 0; i < original.size(); ++i) {
        assert(caller[2*i] >= 'a' && caller[2*i] <= 'z');
        assert(caller[2*i+1] == original[i]);
    }
    assert(captured.str() == "Oh no! The ref monkeys changed our value to: " + caller + "\n");
    captured.str(""); const auto before = caller; constRefMonkey(caller);
    assert(caller == before && captured.str() == "The const-reference monkeys can only observe: " + caller + "\n");
    captured.str("");
}
std::cout.rdbuf(previous);
''')

    def test_chaos_driver_preserves_original_byte_order_and_printed_caller_state(self):
        for part in ['', 'solution']:
            code, out, err = execute([str(self.binaries[PACKS[2], part])])
            self.assertEqual((code, err), (0, ''))
            self.assertIn('After calling the value monkeys, my value is: bananas\n', out)
            value = re.search(r'value monkeys changed our value to: (\w+)\n', out)[1]
            changed = re.search(r'ref monkeys changed our value to: (\w+)\n', out)[1]
            for text in [value, changed]:
                self.assertEqual(len(text), 14)
                self.assertEqual(text[1::2], 'bananas')
                self.assertRegex(text[::2], r'^[a-z]{7}$')
            self.assertIn('After calling the ref monkeys, my value is: ' + changed + '\n', out)
            self.assertTrue(out.endswith('The const-reference monkeys can only observe: ' + changed + '\n'))

    def test_supplied_intro_and_struct_lessons_have_independent_exact_outputs(self):
        expected = ('Hello World!\nDemonstrating passing by value:\nval1 is: 10\nval2 is: 20\n'
            'Demonstrating passing by reference:\nval1 is: 10\nval2 is now changed to: 40\n'
            'val1 is: 10\nval1 is now changed to: 30\n'
            'There should have been no change to val1, and we could not have modified val2 either.\n')
        self.assertEqual(execute([str(self.binaries[LESSONS[0], ''])]), (0, expected, ''))
        records = [('First', 1, 'Brown', 123443), ('Second', 2, 'Sam', 1234567822), ('Third', 3, 'Addy', 1234567844)]
        expected = '\n'.join(f'{ordinal} Student:\nRoll Number: {roll}\nName: {name}\nPhone Number: {phone}\n'
                             for ordinal, roll, name, phone in records)
        self.assertEqual(execute([str(self.binaries[LESSONS[1], ''])]), (0, expected, ''))

    def test_makefiles_select_one_pack_and_sanitizers_cover_all_references(self):
        for folder in PACKS:
            for part in ['starter', 'solution']:
                code, out, err = execute(['make', '-n', '-B', 'PART=' + part], cwd=ROOT / folder)
                self.assertEqual(code, 0, out + err)
                self.assertIn(part + '/main.cpp', out)
                self.assertNotIn(('solution' if part == 'starter' else 'starter') + '/main.cpp', out)
                code, out, err = execute(['make', '-n', '-B'], cwd=ROOT / folder / part)
                self.assertEqual(code, 0, out + err)
                self.assertIn('main.cpp', out)
        if not self.instrumented:
            self.skipTest('SOURCE_SANITIZERS=0 explicitly disables instrumentation')
        for folder, text, expected_code in [(PACKS[0], '', 0), (PACKS[1], 'www.example.com', 0),
                                           (PACKS[1], '', 1), (PACKS[2], '', 0)]:
            code, out, err = execute([str(self.binaries[folder, 'sanitized'])], text=text)
            self.assertEqual(code, expected_code, out + err)
            self.assertNotIn('AddressSanitizer', err)
            self.assertNotIn('runtime error:', err)


if __name__ == '__main__':
    unittest.main()

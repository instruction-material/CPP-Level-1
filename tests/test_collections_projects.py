"""Independent CPPF5 bounded-domain summaries and input-cancellation contracts."""
import os
from pathlib import Path
import random
import tempfile
import unittest

from test_foundation_projects import ROOT, execute
PACKS = ['CPPF5-Vector-Practice', 'CPPF5-Bank-Accounts']


class CollectionContracts(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temporary = tempfile.TemporaryDirectory(prefix='cpp-collection-contracts-')
        cls.addClassCleanup(cls.temporary.cleanup)
        cls.compiler = os.environ.get('CXX', 'c++')
        cls.flags = ['-std=c++20', '-Wall', '-Wextra', '-Wpedantic', '-Werror']
        cls.instrumented = os.environ.get('SOURCE_SANITIZERS', '1') == '1'
        cls.binaries = {}
        for folder in [*PACKS, 'CPPF5-Vectors-Reference']:
            parts = ['', 'starter', 'solution'] if folder in PACKS else ['']
            for part in parts:
                directory = ROOT / folder / part
                output = Path(cls.temporary.name) / (folder + '-' + (part or 'root'))
                code, out, err = execute([cls.compiler, *cls.flags, str(directory / 'main.cpp'), '-o', str(output)])
                assert code == 0, out + err
                cls.binaries[folder, part] = output
            if cls.instrumented:
                directory = ROOT / folder / ('solution' if folder in PACKS else '')
                output = Path(cls.temporary.name) / (folder + '-sanitized')
                code, out, err = execute([cls.compiler, *cls.flags, '-g', '-fno-omit-frame-pointer',
                    '-fsanitize=address,undefined', str(directory / 'main.cpp'), '-o', str(output)])
                assert code == 0, out + err
                cls.binaries[folder, 'sanitized'] = output

    def run_bank(self, values, code=0, error=''):
        result, out, err = execute([str(self.binaries[PACKS[1], 'solution'])], text=values, timeout=5)
        self.assertEqual((result, err), (code, error), out + err)
        if code:
            self.assertNotIn('You have a balance', out)
        return out

    def harness(self, folder, body):
        path = Path(self.temporary.name) / (folder + '-harness.cpp')
        source = ROOT / folder / 'solution/main.cpp'
        path.write_text('#define main supplied_driver\n#include "' + str(source) +
            '"\n#undef main\n#include <cassert>\nint main() {\n' + body + '\n}\n')
        output = path.with_suffix('')
        flags = self.flags + (['-g', '-fno-omit-frame-pointer', '-fsanitize=address,undefined'] if self.instrumented else [])
        code, out, err = execute([self.compiler, *flags, str(path), '-o', str(output)])
        self.assertEqual(code, 0, out + err)
        code, out, err = execute([str(output)], timeout=5)
        self.assertEqual((code, out, err), (0, '', ''), out + err)

    def test_incomplete_starters_and_equal_briefs(self):
        for folder, reminder in zip(PACKS, ['vector', 'bank-account']):
            code, out, err = execute([str(self.binaries[folder, 'starter'])])
            self.assertEqual((code, out, err), (2, '', f'Complete the {reminder} starter and its checks.\n'))
            self.assertIn('TODO', (ROOT / folder / 'starter/main.cpp').read_text())
            self.assertNotEqual((ROOT / folder / 'starter/main.cpp').read_bytes(),
                                (ROOT / folder / 'solution/main.cpp').read_bytes())
            for part in ['starter', 'solution']:
                self.assertEqual((ROOT / folder / part / 'README.md').read_bytes(),
                                 (ROOT / folder / 'README.md').read_bytes())

    def test_vector_driver_exact_results_and_legacy_entry(self):
        expected = ('Perfect squares: 0 1 4 9 16 25 36 49 64 81 \n'
            'First and last match? 0\nSum of squares: 285\nTotal letters: 20\n')
        for part in ['', 'solution']:
            code, out, err = execute([str(self.binaries[PACKS[0], part])])
            self.assertEqual((code, out, err), (0, expected, ''))

    def test_vector_empty_singleton_endpoints_and_bounded_sum(self):
        self.harness(PACKS[0], r'''
assert(!firstLastMatch({}));
assert(firstLastMatch({-1000000}));
assert(firstLastMatch({1, -2, 1}));
assert(!firstLastMatch({1, -2, 3}));
assert(sumVector({}) == 0);
std::vector<int> mixed{1000000, -1000000, -9, 7, 0};
auto original = mixed;
assert(sumVector(mixed) == -2 && mixed == original);
assert(sumVector(std::vector<int>(1000, 1000000)) == 1000000000);
assert(sumVector(std::vector<int>(1000, -1000000)) == -1000000000);
''')

    def test_ascii_lengths_empty_words_and_input_preservation(self):
        self.harness(PACKS[0], r'''
assert(sumLetters({}) == 0);
assert(sumLetters({"", "", ""}) == 0);
std::vector<std::string> words{"A", "two words", "!?", ""};
auto original = words;
assert(sumLetters(words) == 12 && words == original);
assert(sumLetters({std::string(1000000, 'x')}) == 1000000);
''')

    def test_bank_signed_sums_and_whitespace(self):
        rng = random.Random(5105)
        fixtures = [[], [0], [100, -25, 10], [-2, -3], [1000000, -1000000],
                    [1000000] * 1000, [-1000000] * 1000]
        fixtures += [[rng.randint(-1000000, 1000000) for _ in range(count)] for count in [1, 7, 61]]
        for amounts in fixtures:
            for separator in [' ', '\t', '\n', '\r\n']:
                text = separator.join(map(str, [len(amounts), *amounts]))
                out = self.run_bank(text)
                self.assertEqual(out.count('You have a balance'), 1)
                self.assertTrue(out.endswith(f'You have a balance of ${sum(amounts)} in your account at this time. Thank you!\n'), out)
        self.assertIn('balance of $5 ', self.run_bank('+2 +10 -5 ignored'))
        leading_zeroes = '0' * 70
        self.assertIn('balance of $5 ', self.run_bank(leading_zeroes + '2 ' +
            leading_zeroes + '10 -' + leading_zeroes + '5'))
        self.assertIn('balance of $0 ', self.run_bank(leading_zeroes + '0'))

    def test_bank_count_failure_never_allocates_or_reports_balance(self):
        for text in ['', '-1', '1001', '2147483647', '999999999999999999999',
                     'two', '2.0', '1x', '1e2', '+', '-', '9' * 65]:
            self.run_bank(text, 1, 'Invalid transaction count.\n')

    def test_bank_every_amount_failure_phase_cancels_the_balance(self):
        bad = ['1000001', '-1000001', '2147483647', '-2147483648',
               '99999999999999999999', 'one', '0.5', '2x', '1e3', '+', '-', '9' * 65]
        for position in range(3):
            prefix = '3 ' + ' '.join(['10'] * position) + ' '
            self.run_bank(prefix, 1, 'Invalid transaction amount.\n')
            for token in bad:
                self.run_bank(prefix + token + ' 10 10', 1, 'Invalid transaction amount.\n')

    def test_bank_pure_helper_and_legacy_output(self):
        self.harness(PACKS[1], r'''
assert(calcTotalBalance({}) == 0);
std::vector<int> values{100, -25, 10}; auto original = values;
assert(calcTotalBalance(values) == 85 && values == original);
assert(calcTotalBalance(std::vector<int>(1000, 1000000)) == 1000000000);
assert(calcTotalBalance(std::vector<int>(1000, -1000000)) == -1000000000);
''')
        root = execute([str(self.binaries[PACKS[1], ''])], text='3 100 -25 10')
        reference = execute([str(self.binaries[PACKS[1], 'solution'])], text='3 100 -25 10')
        self.assertEqual(root, reference)

    def test_complete_vector_lesson_and_makefile_selection(self):
        code, out, err = execute([str(self.binaries['CPPF5-Vectors-Reference', ''])])
        expected = ('Scores stored in a vector:\nIndex 0: 88\nIndex 1: 91\nIndex 2: 76\nIndex 3: 95\n'
            '\nThe first score is 88\nThe last score is 95\nThere are 4 total scores.\n'
            '\nAfter improving the second score:\n88 95 76 95 \n'
            '\nLesson labels:\n- warmup\n- practice\n- challenge\n')
        self.assertEqual((code, out, err), (0, expected, ''))
        for folder in PACKS:
            for part in ['starter', 'solution']:
                code, out, err = execute(['make', '-n', '-B', 'PART=' + part], cwd=ROOT / folder)
                self.assertEqual(code, 0, out + err)
                self.assertIn(part + '/main.cpp', out)
                self.assertNotIn(('solution' if part == 'starter' else 'starter') + '/', out)

    def test_sanitized_valid_boundary_and_cancellation_runs(self):
        if not self.instrumented:
            self.skipTest('SOURCE_SANITIZERS=0 explicitly disables instrumentation')
        for folder, text in [(PACKS[0], ''), ('CPPF5-Vectors-Reference', ''),
                             (PACKS[1], '1000 ' + ' '.join(['1000000'] * 1000))]:
            code, out, err = execute([str(self.binaries[folder, 'sanitized'])], text=text, timeout=10)
            self.assertEqual((code, err), (0, ''), out + err)
        code, out, err = execute([str(self.binaries[PACKS[1], 'sanitized'])], text='2 4 1.5', timeout=10)
        self.assertEqual((code, err), (1, 'Invalid transaction amount.\n'))
        self.assertNotIn('You have a balance', out)


if __name__ == '__main__': unittest.main()

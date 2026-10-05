'''Original function-project contracts, cancellation and random outcome domains.'''

import itertools
import math
import os
from pathlib import Path
import re
import tempfile
import unittest

from test_foundation_projects import ROOT, execute

PACKS = ['CPPF3-Function-Practice', 'CPPF3-Probability-Functions', 'CPPF3-Number-Guesser']


class FunctionContracts(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temporary = tempfile.TemporaryDirectory(prefix='cpp-functions-contracts-')
        cls.addClassCleanup(cls.temporary.cleanup)
        cls.compiler = os.environ.get('CXX', 'c++')
        cls.binaries, cls.sanitized = {}, {}
        for folder in PACKS:
            for part in ['starter', 'solution']:
                output = Path(cls.temporary.name) / (folder + '-' + part)
                command = [cls.compiler, '-std=c++20', '-Wall', '-Wextra', '-Wpedantic', '-Werror',
                           str(ROOT / folder / part / 'main.cpp'), '-o', str(output)]
                code, out, err = execute(command)
                assert code == 0, out + err
                cls.binaries[folder + '/' + part] = output
            if os.environ.get('SOURCE_SANITIZERS', '1') == '1':
                output = Path(cls.temporary.name) / (folder + '-sanitized')
                code, out, err = execute([cls.compiler, '-std=c++20', '-Wall', '-Wextra', '-Wpedantic',
                    '-Werror', '-g', '-fno-omit-frame-pointer', '-fsanitize=address,undefined',
                    str(ROOT / folder / 'solution/main.cpp'), '-o', str(output)])
                assert code == 0, out + err
                cls.sanitized[folder] = output
        output = Path(cls.temporary.name) / 'random-reference'
        code, out, err = execute([cls.compiler, '-std=c++20', '-Wall', '-Wextra', '-Wpedantic', '-Werror',
                                str(ROOT / 'CPPF3-rand-Reference/main.cpp'), '-o', str(output)])
        assert code == 0, out + err
        cls.binaries['random'] = output

    def reference(self, folder, text, expected_code=0, error=''):
        code, out, err = execute([str(self.binaries[folder + '/solution'])], text=text, timeout=5)
        self.assertEqual((code, err), (expected_code, error), out + err)
        return out

    def harness(self, folder, body, headers=''):
        path = Path(self.temporary.name) / (folder + '-harness.cpp')
        binary = path.with_suffix('')
        path.write_text('#include <cassert>\n' + headers + '\n#define main reviewedMain\n#include "' +
                        str(ROOT / folder / 'solution/main.cpp') +
                        '"\n#undef main\nint main() {\n' + body + '\n}\n')
        flags = ['-std=c++20', '-Wall', '-Wextra', '-Wpedantic', '-Werror']
        if self.sanitized:
            flags += ['-g', '-fno-omit-frame-pointer', '-fsanitize=address,undefined']
        code, out, err = execute([self.compiler, *flags, str(path), '-o', str(binary)])
        self.assertEqual(code, 0, out + err)
        code, out, err = execute([str(binary)], timeout=10)
        self.assertEqual((code, err), (0, ''), out + err)

    def test_separate_incomplete_starters_and_matched_briefs(self):
        for folder in PACKS:
            code, out, err = execute([str(self.binaries[folder + '/starter'])], timeout=5)
            self.assertEqual((code, out), (2, ''))
            self.assertIn('Complete the starter', err)
            self.assertIn('TODO', (ROOT / folder / 'starter/main.cpp').read_text())
            for part in ['starter', 'solution']:
                self.assertEqual((ROOT / folder / part / 'README.md').read_bytes(),
                                 (ROOT / folder / 'README.md').read_bytes())

    def test_math_console_fixtures_and_safe_endpoints(self):
        for first, second, n, base, power in [(2, 3, 5, 2, 3), (-3, 2, 1, 1, 0),
                (0, 0, 12, 10, 9), (1000000, 1000000, 12, 10, 9),
                (-1000000, -1000000, 1, 1, 9), (-1000000, 1000000, 1, 10, 0)]:
            for separator in [' ', '\r\n']:
                out = self.reference(PACKS[0], separator.join(map(str, [first, second, n, base, power])))
                lines = [f'Sum = {first + second}', f'Average = {(first + second) / 2:.2f}',
                    f'Is {first} even? {str(first % 2 == 0).lower()}', 'Smallest = 1.61803',
                    f'{n}! = {math.factorial(n)}', f'{base}^{power} = {base ** power}']
                self.assertTrue(out.endswith('\n' + '\n'.join(lines) + '\n'), out)

    def test_math_cancellation_never_prints_calculated_results(self):
        cases = [('', 'Invalid pair.'), ('1', 'Invalid pair.'), ('-1000001 2', 'Invalid pair.'),
            ('1 1000001', 'Invalid pair.'), ('1 2', 'Invalid factorial number.'),
            ('1 2 0', 'Invalid factorial number.'), ('1 2 13', 'Invalid factorial number.'),
            ('1 2 1', 'Invalid base or power.'), ('1 2 1 0 1', 'Invalid base or power.'),
            ('1 2 1 11 1', 'Invalid base or power.'), ('1 2 1 2 -1', 'Invalid base or power.'),
            ('1 2 1 2 10', 'Invalid base or power.')]
        for bad in ['1x', '2.5', '999999999999999999', 'x' * 65]:
            cases += [(bad + ' 2 1 2 1', 'Invalid pair.'),
                      ('1 2 ' + bad + ' 2 1', 'Invalid factorial number.'),
                      ('1 2 1 2 ' + bad, 'Invalid base or power.')]
        for text, error in cases:
            out = self.reference(PACKS[0], text, 1, error + '\n')
            for label in ['Sum =', 'Average =', '! =', '^']:
                self.assertNotIn(label, out)

    def test_math_function_contracts_without_console_driver(self):
        self.harness(PACKS[0], r'''
assert(add(-1000000, -1000000) == -2000000);
assert(average(2, 3) == 2.5);
assert(average(-3, 2) == -0.5);
assert(average(std::numeric_limits<int>::max(), std::numeric_limits<int>::max()) == std::numeric_limits<int>::max());
assert(average(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()) == -0.5);
assert(isEven(0) && isEven(-2) && !isEven(-3));
assert(smallest(1.5, 2.5, 3.5) == 1.5);
assert(smallest(3.5, 1.5, 2.5) == 1.5);
assert(smallest(3.5, 2.5, 1.5) == 1.5);
assert(factorial(1) == 1 && factorial(12) == 479001600);
assert(exponent(2, 3) == 8 && exponent(10, 9) == 1000000000 && exponent(10, 0) == 1);
''', '#include <limits>')

    def test_probability_console_domains_and_repeatability(self):
        ranks = ['Ace', *map(str, range(2, 11)), 'Jack', 'Queen', 'King']
        cards = {f'{rank} of {suit}' for rank, suit in itertools.product(ranks, ['Spades', 'Clubs', 'Hearts', 'Diamonds'])}
        for seed in [0, 1, 42, 2147483647]:
            out = self.reference(PACKS[1], str(seed))
            self.assertEqual(out, self.reference(PACKS[1], str(seed)))
            lines = out.splitlines()[-3:]
            self.assertIn(lines[0], ['Coin: heads', 'Coin: tails'])
            self.assertIn(int(lines[1].removeprefix('Dice sum: ')), range(2, 13))
            self.assertIn(lines[2].removeprefix('Card: '), cards)

    def test_probability_all_observed_outcomes_and_two_dice_model(self):
        self.harness(PACKS[1], r'''
std::set<std::string> coins, cards;
std::set<int> sums;
const std::set<std::string> suits = {"Spades", "Clubs", "Hearts", "Diamonds"};
const std::set<std::string> ranks = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
generator.seed(42);
for (int i = 0; i < 20000; ++i) {
    auto coin = flipCoin(); auto sum = diceSum(); auto card = drawCard();
    assert(coin == "heads" || coin == "tails"); assert(sum >= 2 && sum <= 12);
    auto split = card.find(" of "); assert(split != std::string::npos);
    assert(ranks.contains(card.substr(0, split)) && suits.contains(card.substr(split + 4)));
    coins.insert(coin); sums.insert(sum); cards.insert(card);
}
assert(coins.size() == 2 && sums.size() == 11 && cards.size() == 52);
for (unsigned seed = 0; seed < 100; ++seed) {
    generator.seed(seed); std::mt19937 independent(seed);
    std::uniform_int_distribution<int> die(1, 6);
    int first = die(independent); int second = die(independent);
    assert(diceSum() == first + second);
}
''', '#include <set>')

    def test_seed_rejection_never_prints_events_or_starts_game(self):
        for folder in PACKS[1:]:
            for bad in ['', '-1', '2147483648', '42x', '1.5', 'x' * 65]:
                out = self.reference(folder, bad, 1, 'Invalid seed.\n')
                self.assertNotIn('Coin:', out)
                self.assertNotIn('Welcome!', out)

    def test_guesser_first_guess_feedback_and_early_termination(self):
        out = self.reference(PACKS[2], '42 5 5 5 4 4 4 4')
        self.assertIn('Correct! You used 1 guess!', out)
        self.assertEqual(out.count('remaining. What is your guess?'), 1)
        self.assertNotIn('out of guesses', out)
        out = self.reference(PACKS[2], '42 5 5 4 6 5 9')
        self.assertIn('Too low!\n', out)
        self.assertIn('Too high!\n', out)
        self.assertIn('Correct! You used 3 guesses!', out)
        self.assertEqual(out.count('remaining. What is your guess?'), 3)
        for remaining in [5, 4, 3]: self.assertIn(f'You have {remaining} guesses remaining.', out)
        for endpoint in [-2147483648, 2147483647]:
            out = self.reference(PACKS[2], f'0 {endpoint} {endpoint} {endpoint}')
            self.assertIn('Correct! You used 1 guess!', out)

    def test_guesser_five_valid_guesses_only(self):
        for guess, feedback in [(4, 'Too low!'), (6, 'Too high!')]:
            out = self.reference(PACKS[2], '42 5 5 ' + ' '.join([str(guess)] * 6))
            self.assertEqual(out.count(feedback), 5)
            self.assertEqual(out.count('remaining. What is your guess?'), 5)
            self.assertTrue(out.endswith("You're out of guesses. Better luck next time!\n"))
            self.assertNotIn('Correct!', out)

    def test_guesser_range_and_guess_cancellation(self):
        for bad in ['', '2', '2 1', '1x 2', '1 2x', '-2147483649 0', '0 2147483648']:
            out = self.reference(PACKS[2], '42 ' + bad, 1, 'Invalid range.\n')
            self.assertNotIn('guesses remaining.', out)
        for bad in ['', '5x', '5.5', '2147483648', 'x' * 65]:
            out = self.reference(PACKS[2], '42 5 5 4 ' + bad, 1, 'Invalid guess.\n')
            self.assertEqual(out.count('Too low!'), 1)
            self.assertNotIn('Correct!', out)
            self.assertNotIn('out of guesses', out)

    def test_guesser_random_range_including_full_signed_domain(self):
        self.harness(PACKS[2], r'''
for (auto bounds : {std::pair{-3, 3}, std::pair{5, 5},
        std::pair{std::numeric_limits<int>::min(), std::numeric_limits<int>::max()}}) {
    generator.seed(42);
    for (int i = 0; i < 1000; ++i) {
        int value = chooseAnswer(bounds.first, bounds.second);
        assert(value >= bounds.first && value <= bounds.second);
    }
}
generator.seed(42); int first = chooseAnswer(-10, 10);
generator.seed(42); assert(chooseAnswer(-10, 10) == first);
''', '#include <limits>\n#include <utility>')

    def test_random_reference_domains_and_seed_reset(self):
        code, out, err = execute([str(self.binaries['random'])], timeout=5)
        self.assertEqual((code, err), (0, ''))
        lines = out.splitlines()
        pair = lines[0].removeprefix('Same seed, same engine value: ').split()
        self.assertEqual(len(pair), 2)
        self.assertEqual(pair[0], pair[1])
        self.assertEqual(lines[1], 'Five values in the inclusive range 0 through 50:')
        self.assertTrue(all(0 <= int(value) <= 50 for value in lines[2:7]))
        self.assertEqual(lines[7], 'Five values in the inclusive range 100 through 200:')
        self.assertTrue(all(100 <= int(value) <= 200 for value in lines[8:13]))
        self.assertEqual(len(lines), 13)

    def test_sanitized_valid_and_cancelled_console_paths(self):
        if not self.sanitized: self.skipTest('SOURCE_SANITIZERS=0 explicitly disables instrumentation')
        for folder, cases in [(PACKS[0], [('2 3 12 10 9', 0), ('1 2 13', 1)]),
                              (PACKS[1], [('42', 0), ('-1', 1)]),
                              (PACKS[2], [('42 5 5 4 6 5', 0), ('42 2 1', 1), ('42 5 5 4 5x', 1),
                                          ('42 -2147483648 -2147483648 -2147483648', 0)])]:
            for text, expected_code in cases:
                code, out, err = execute([str(self.sanitized[folder])], text=text, timeout=5)
                self.assertEqual(code, expected_code, out + err)
                self.assertNotIn('AddressSanitizer', err)
                self.assertNotIn('runtime error:', err)


if __name__ == '__main__': unittest.main()

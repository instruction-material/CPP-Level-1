"""Independent CPPF7 rectangular-grid and validated input contracts."""
import hashlib
import os
from pathlib import Path
import random
import tempfile
import unittest

from test_foundation_projects import ROOT, execute

PACKS = ['CPPF7-Matrix-Addition', 'CPPF7-Grid-Statistics']
LESSON = 'CPPF7-Grids-and-2D-Vectors-Reference'


class GridContracts(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temporary = tempfile.TemporaryDirectory(prefix='cpp-grid-contracts-')
        cls.addClassCleanup(cls.temporary.cleanup)
        cls.compiler = os.environ.get('CXX', 'c++')
        cls.flags = ['-std=c++20', '-Wall', '-Wextra', '-Wpedantic', '-Werror']
        cls.instrumented = os.environ.get('SOURCE_SANITIZERS', '1') == '1'
        cls.binaries = {}
        for folder in [*PACKS, LESSON]:
            parts = ['', 'starter', 'solution'] if folder in PACKS else ['']
            for part in parts:
                source = ROOT / folder / part / 'main.cpp'
                output = Path(cls.temporary.name) / (folder + '-' + (part or 'root'))
                code, out, err = execute([cls.compiler, *cls.flags, str(source), '-o', str(output)])
                assert code == 0, out + err
                cls.binaries[folder, part] = output
            if cls.instrumented:
                source = ROOT / folder / ('solution/main.cpp' if folder in PACKS else 'main.cpp')
                output = Path(cls.temporary.name) / (folder + '-sanitized')
                code, out, err = execute([cls.compiler, *cls.flags, '-g', '-fno-omit-frame-pointer',
                    '-fsanitize=address,undefined', str(source), '-o', str(output)])
                assert code == 0, out + err
                cls.binaries[folder, 'sanitized'] = output

    def matrix(self, tokens, expected=None, error='', part='solution'):
        code, out, err = execute([str(self.binaries[PACKS[0], part])], text=tokens, timeout=10)
        self.assertEqual((code, err), (1 if error else 0, error), out + err)
        marker = 'Sum of two matrices is: \n'
        if error:
            self.assertNotIn(marker, out)
        else:
            self.assertEqual(out.count(marker), 1)
            rows = out.split(marker)[1].splitlines()
            self.assertEqual(rows, [''.join(str(v) + '  ' for v in row) for row in expected])
        return out

    def harness(self, body, stdout=''):
        path = Path(self.temporary.name) / 'grid-harness.cpp'
        source = ROOT / PACKS[1] / 'solution/main.cpp'
        path.write_text('#define main supplied_driver\n#include "' + str(source) +
            '"\n#undef main\n#include <cassert>\nint main() {\n' + body + '\n}\n')
        output = path.with_suffix('')
        flags = self.flags + (['-g', '-fno-omit-frame-pointer', '-fsanitize=address,undefined'] if self.instrumented else [])
        code, out, err = execute([self.compiler, *flags, str(path), '-o', str(output)])
        self.assertEqual(code, 0, out + err)
        code, out, err = execute([str(output)], timeout=10)
        self.assertEqual((code, out, err), (0, stdout, ''), out + err)

    def test_incomplete_starters_equal_briefs_and_build_selection(self):
        for folder, reminder in zip(PACKS, ['matrix-addition', 'grid-statistics']):
            code, out, err = execute([str(self.binaries[folder, 'starter'])])
            self.assertEqual((code, out, err), (2, '', f'Complete the {reminder} starter and its checks.\n'))
            self.assertIn('TODO', (ROOT / folder / 'starter/main.cpp').read_text())
            self.assertNotEqual((ROOT / folder / 'starter/main.cpp').read_text(),
                                (ROOT / folder / 'solution/main.cpp').read_text())
            for part in ['starter', 'solution']:
                self.assertEqual((ROOT / folder / part / 'README.md').read_bytes(),
                                 (ROOT / folder / 'README.md').read_bytes())
                code, out, err = execute(['make', '-n', '-B', 'PART=' + part], cwd=ROOT / folder)
                self.assertEqual(code, 0, out + err)
                self.assertIn(part + '/main.cpp', out)
                self.assertNotIn(('starter' if part == 'solution' else 'solution') + '/', out)

    def test_matrix_rectangular_random_and_dimension_boundaries(self):
        rng = random.Random(7107)
        for rows, cols in [(1,1), (1,100), (100,1), (100,100), (2,3), (3,2), (7,11)]:
            a = [[rng.randint(-1000000,1000000) for _ in range(cols)] for _ in range(rows)]
            b = [[rng.randint(-1000000,1000000) for _ in range(cols)] for _ in range(rows)]
            expected = [[a[i][j]+b[i][j] for j in range(cols)] for i in range(rows)]
            numbers = [rows,cols,*[v for row in a for v in row],*[v for row in b for v in row]]
            for separator in [' ', '\t', '\n', '\r\n']:
                self.matrix(separator.join(map(str,numbers)), expected)

    def test_matrix_sign_bounds_leading_zeroes_and_legacy_output(self):
        for a,b in [(1000000,1000000), (-1000000,-1000000), (-1000000,1000000), (0,0)]:
            self.matrix(f'1 1 {a} {b}', [[a+b]])
        zeroes = '0'*100
        self.matrix(zeroes+'1 +'+zeroes+'2 -'+zeroes+'5 +'+zeroes+'10 '+zeroes+'2 -'+zeroes+'1 ignored', [[-3,9]])
        data='2 3 1 2 3 4 5 6 6 5 4 3 2 1'
        self.assertEqual(self.matrix(data, [[7,7,7],[7,7,7]], part=''),
                         self.matrix(data, [[7,7,7],[7,7,7]]))

    def test_matrix_dimensions_cancel_before_cell_prompts(self):
        bad=['0','-1','101','2147483647','2147483648','1x','2.0','1e2','+','-','one']
        for prefix in ['', '2 ']:
            for token in ['', *bad]:
                out=self.matrix(prefix+token, error='Invalid matrix dimensions.\n')
                self.assertNotIn('Enter elements of',out)

    def test_matrix_each_cell_failure_cancels_all_results(self):
        bad=['1000001','-1000001','2147483647','-2147483648','2147483648','2x','1.5','1e2','+','-','nope']
        for position in range(8):
            prefix='2 2 '+' '.join(['3']*position)+' '
            for token in ['', *bad]:
                suffix='' if not token else token+' '+' '.join(['4']*(7-position))
                self.matrix(prefix+suffix,error='Invalid matrix element.\n')

    def test_grid_empty_zero_column_and_preservation(self):
        self.harness(r'''
Grid empty; auto original=empty;
assert(rowTotals(empty).empty() && columnTotals(empty).empty());
assert(mainDiagonalTotal(empty)==0);
printLargestValue(empty); printGrid(empty); printVector({});
assert(empty==original);
Grid zero(3); original=zero;
assert(rowTotals(zero)==std::vector<int>({0,0,0}));
assert(columnTotals(zero).empty() && mainDiagonalTotal(zero)==0);
printLargestValue(zero); printGrid(zero);
assert(zero==original);
''','The grid is empty.\n\nThe grid is empty.\n\n\n\n')

    def test_grid_wide_tall_negative_ties_and_const_inputs(self):
        self.harness(r'''
Grid wide{{-9,-2,-2},{-4,-5,-6}}; auto original=wide;
assert(rowTotals(wide)==std::vector<int>({-13,-15}));
assert(columnTotals(wide)==std::vector<int>({-13,-7,-8}));
assert(mainDiagonalTotal(wide)==-14);
printLargestValue(wide); printGrid(wide); printVector(rowTotals(wide));
assert(wide==original);
Grid tall{{1,2},{3,4},{5,6}}; original=tall;
assert(rowTotals(tall)==std::vector<int>({3,7,11}));
assert(columnTotals(tall)==std::vector<int>({9,12}));
assert(mainDiagonalTotal(tall)==5); assert(tall==original);
printLargestValue(tall);
Grid single{{-7}};
assert(rowTotals(single)==std::vector<int>({-7}));
assert(columnTotals(single)==std::vector<int>({-7}));
assert(mainDiagonalTotal(single)==-7); printLargestValue(single);
''','Largest value: -2 at row 0, column 1\n-9\t-2\t-2\t\n-4\t-5\t-6\t\n-13, -15\nLargest value: 6 at row 2, column 1\nLargest value: -7 at row 0, column 0\n')

    def test_grid_maximum_dimensions_and_numeric_domain(self):
        self.harness(r'''
for(int value : {-1000000,1000000}) {
 Grid grid(100,std::vector<int>(100,value)); auto original=grid;
 assert(rowTotals(grid)==std::vector<int>(100,value*100));
 assert(columnTotals(grid)==std::vector<int>(100,value*100));
 assert(mainDiagonalTotal(grid)==value*100 && grid==original);
 printLargestValue(grid);
}
''','Largest value: -1000000 at row 0, column 0\nLargest value: 1000000 at row 0, column 0\n')

    def test_grid_fixed_driver_and_legacy_entry(self):
        expected=('Grid:\n8\t4\t7\t9\t\n6\t5\t3\t2\t\n10\t1\t8\t4\t\n7\t6\t2\t5\t\n'
            '\nRow totals: 28, 16, 23, 20\nColumn totals: 31, 16, 20, 20\n'
            'Main diagonal total: 26\nLargest value: 10 at row 2, column 0\n')
        for part in ['', 'solution']:
            self.assertEqual(execute([str(self.binaries[PACKS[1],part])]), (0,expected,''))

    def test_complete_grid_lesson_exact_original_program_and_output(self):
        source=(ROOT/LESSON/'main.cpp').read_bytes().replace(b'\r\n',b'\n')
        self.assertEqual(hashlib.sha256(source).hexdigest(),'d34a58272124071844f4bfb298bcae664a8622a40d50114b3285601f500f980e')
        expected=('Original grid:\n1 2 3 \n4 5 6 \n7 8 9 \n\nUpdated grid:\n1 2 3 \n4 99 6 \n7 8 9 \n10 11 12 \n'
            '\nRow totals:\nRow 0: 6\nRow 1: 109\nRow 2: 24\nRow 3: 33\n')
        self.assertEqual(execute([str(self.binaries[LESSON,''])]),(0,expected,''))

    def test_sanitized_matrix_boundaries_and_cancellation_and_grid_drivers(self):
        if not self.instrumented:
            self.skipTest('SOURCE_SANITIZERS=0 explicitly disables instrumentation')
        self.matrix('100 100 '+' '.join(['1000000']*20000),
                    [[2000000]*100 for _ in range(100)],part='sanitized')
        self.matrix('1 1 2147483647 1',error='Invalid matrix element.\n',part='sanitized')
        self.matrix('1 1 4 nope',error='Invalid matrix element.\n',part='sanitized')
        for folder in [PACKS[1],LESSON]:
            code,out,err=execute([str(self.binaries[folder,'sanitized'])])
            self.assertEqual((code,err),(0,''),out+err)


if __name__=='__main__': unittest.main()

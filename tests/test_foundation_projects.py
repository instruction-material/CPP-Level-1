"""Independent console contracts for the first two C++ foundation modules."""

from datetime import datetime, timezone
from decimal import Decimal
import itertools
import json
import os
from pathlib import Path
import re
import signal
import subprocess
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[1]
REVIEWED = [
    "CPPF1-Mad-Libs", "CPPF1-Chat-Bot", "CPPF2-Number-Games",
    "CPPF2-Rock-Paper-Scissors", "CPPF2-Fizz-Buzz",
]
TASK = os.environ.get("CLASSES_FAMILY_TASK_ID", "cpp-foundation-source-native")


def execute(command, *, cwd=ROOT, text="", timeout=30):
    child = subprocess.Popen(command, cwd=cwd, stdin=subprocess.PIPE,
                             stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                             start_new_session=True)
    print(json.dumps({"event": "start", "parentTaskId": TASK, "cwd": str(cwd),
                      "command": list(map(str, command)), "pid": child.pid,
                      "time": datetime.now(timezone.utc).isoformat(),
                      "timeoutSeconds": timeout}), flush=True)
    try:
        out, err = child.communicate(text.encode(), timeout=timeout)
    except subprocess.TimeoutExpired:
        os.killpg(child.pid, signal.SIGTERM)
        try:
            out, err = child.communicate(timeout=2)
        except subprocess.TimeoutExpired:
            os.killpg(child.pid, signal.SIGKILL)
            out, err = child.communicate()
        print(json.dumps({"event": "child-process-group-cleanup", "pid": child.pid,
                          "parentTaskId": TASK}), flush=True)
        raise AssertionError(f"Timed out and cleaned process group: {command}")
    print(json.dumps({"event": "end", "parentTaskId": TASK, "pid": child.pid,
                      "exitCode": child.returncode,
                      "time": datetime.now(timezone.utc).isoformat()}), flush=True)
    return child.returncode, out.decode(), err.decode()


class FoundationContracts(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.temporary = tempfile.TemporaryDirectory(prefix="cpp-foundation-contracts-")
        cls.addClassCleanup(cls.temporary.cleanup)
        cls.binaries = {}
        cls.sanitized = {}
        folders = re.findall(r"^\| `([^`]+)` \|$", (ROOT / "COURSE_SOURCE_MANIFEST.md").read_text(), re.M)
        assert len(folders) == 29 and len(set(folders)) == 29
        compiler = os.environ.get("CXX", "c++")
        for folder in folders:
            for part in ["", "starter", "solution"]:
                directory = ROOT / folder / part
                sources = sorted(directory.glob("*.cpp")) if directory.is_dir() else []
                if not sources:
                    continue
                key = folder + ("/" + part if part else "")
                output = Path(cls.temporary.name) / key.replace("/", "-")
                flags = ["-std=c++20", "-Wall", "-Wextra", "-Wpedantic"]
                if folder in REVIEWED or folder in [
                        "CPPF3-Function-Practice", "CPPF3-Probability-Functions",
                        "CPPF3-Number-Guesser", "CPPF3-rand-Reference"]:
                    flags.append("-Werror")
                code, out, err = execute([compiler, *flags, "-I", str(directory),
                                         *map(str, sources), "-o", str(output)])
                assert code == 0, f"{key}: {out}{err}"
                cls.binaries[key] = output
        assert len(cls.binaries) == 45, len(cls.binaries)
        print("Compiled all 45 active native targets; the eight reviewed packs and random reference are warning-clean.", flush=True)
        if os.environ.get("SOURCE_SANITIZERS", "1") == "1":
            for folder in REVIEWED:
                source = ROOT / folder / "solution/main.cpp"
                output = Path(cls.temporary.name) / (folder + "-sanitized")
                code, out, err = execute([compiler, "-std=c++20", "-Wall", "-Wextra",
                                         "-Wpedantic", "-Werror", "-g", "-fno-omit-frame-pointer",
                                         "-fsanitize=address,undefined", str(source), "-o", str(output)])
                assert code == 0, f"{folder}: {out}{err}"
                cls.sanitized[folder] = output

    def run_reference(self, folder, text="", expected_code=0, error=""):
        code, out, err = execute([str(self.binaries[folder + "/solution"])], text=text, timeout=5)
        self.assertEqual(code, expected_code, out + err)
        self.assertEqual(err, error)
        return out

    def test_starters_are_incomplete_and_separate(self):
        for folder in REVIEWED:
            with self.subTest(folder=folder):
                starter = (ROOT / folder / "starter/main.cpp").read_text()
                reference = (ROOT / folder / "solution/main.cpp").read_text()
                self.assertIn("TODO", starter)
                self.assertNotEqual(starter, reference)
                code, out, err = execute([str(self.binaries[folder + "/starter"])], timeout=5)
                self.assertEqual(code, 2)
                self.assertEqual(out, "")
                self.assertIn("Complete the", err)
                for part in ["starter", "solution"]:
                    self.assertEqual((ROOT / folder / part / "README.md").read_bytes(),
                                     (ROOT / folder / "README.md").read_bytes())

    def test_mad_libs_word_order_and_whitespace(self):
        for animal, adjective, verb, ending in [
            ("fox", "curious", "jump", "brave"), ("owl", "quiet", "glide", "wise"),
            ("cat", "tiny", "sleep", "calm"),
        ]:
            expected = f"Long, long ago lived a(n) {adjective} {animal}. It would always {verb} and was very {ending}.\n"
            for separator in [" ", "\n", "\r\n", "\t"]:
                out = self.run_reference("CPPF1-Mad-Libs", separator.join([animal, adjective, verb, ending]) + " extra")
                self.assertTrue(out.endswith("\n" + expected), out)
                self.assertEqual(out.count("Long, long ago"), 1)

    def test_primitive_reference_fixture(self):
        folder = "CPPF1-Primitive-Types-and-Strings-Reference"
        code, out, err = execute([str(self.binaries[folder])], timeout=5)
        self.assertEqual(code, 0)
        self.assertEqual(err, "")
        self.assertEqual(out.splitlines(), ["13", "25", "9.6", "15.708", "9", "0", "1", "M",
                                           "Hello world!", "H", "12", "Hello world! How are you?"])

    def test_for_loop_reference_traces(self):
        for word in ["", "A", "cat"]:
            code, out, err = execute([str(self.binaries["CPPF2-For-Loop-Practice"])], text=word, timeout=5)
            self.assertEqual((code, err), (0, ""))
            actual = out.replace("Enter a word: ", "").splitlines()
            expected = [*map(str, range(11, 21)), *map(str, range(2, 11, 2)), *map(str, range(10, -1, -1)),
                        *word, *reversed(word), "Sum of first 100 = 5050", "Factorial of 10 = 3628800",
                        *map(str, range(10)), *map(str, range(10))]
            self.assertEqual(actual, expected)

    def test_while_loop_reference_traces(self):
        for word in ["", "A", "cat"]:
            code, out, err = execute([str(self.binaries["CPPF2-While-Loop-Practice"])], text=word, timeout=5)
            self.assertEqual((code, err), (0, ""))
            actual = out.replace("Enter a word: ", "").splitlines()
            expected = [*map(str, range(11)), *map(str, range(0, 11, 2)), *map(str, range(10, -1, -1)),
                        *word, *reversed(word), "Sum of first 100 = 5050", "Factorial of 10 = 3628800"]
            self.assertEqual(actual, expected)

    def test_mad_libs_incomplete_input_never_prints_story(self):
        for count in range(4):
            out = self.run_reference("CPPF1-Mad-Libs", " ".join(["fox", "curious", "jump"][:count]), 1, "Input incomplete.\n")
            self.assertNotIn("Long, long ago", out)

    def test_chat_bot_text_and_conversion_fixtures(self):
        fixtures = [
            ("Ada Lovelace", "I like rainy days.", "32", "1", "0.00", "109.01"),
            ("A", "x", "212", "2", "100.00", "218.02"),
            ("Sam", "Hello", "-40", "0", "-40.00", "0.00"),
            ("猫", "🙂 hello", "3.2e1", "1e0", "0.00", "109.01"),
            ("  Sam  ", "  hello  ", "32 ", " 1 ", "0.00", "109.01"),
        ]
        for name, sentence, degrees, dollars, celsius, yen in fixtures:
            for separator in ["\n", "\r\n"]:
                out = self.run_reference("CPPF1-Chat-Bot", separator.join([name, sentence, degrees, dollars, ""]))
                self.assertTrue(out.endswith(f"\nHello, {name}!\nSneeze: **achoo** {sentence}\nCelsius: {celsius}\nExample conversion at 109.01 JPY per USD: {yen} JPY\n"), out)

    def test_chat_bot_numeric_boundaries(self):
        for temperature, dollars in itertools.product(["-100", "300"], ["0", "1000000"]):
            out = self.run_reference("CPPF1-Chat-Bot", f"A\nx\n{temperature}\n{dollars}\n")
            shown = Decimal(re.search(r"Celsius: (-?\d+\.\d{2})", out)[1])
            expected = (Decimal(temperature) - 32) * Decimal(5) / 9
            self.assertLessEqual(abs(shown - expected), Decimal("0.005"))
            self.assertIn(f"{Decimal(dollars) * Decimal('109.01'):.2f} JPY\n", out)

    def test_chat_bot_rejects_bad_and_missing_fields(self):
        cases = [("", "Invalid name."), ("\nx\n32\n1\n", "Invalid name."),
                 ("A\n", "Invalid sentence."), ("A\n\n32\n1\n", "Invalid sentence."),
                 ("A\nx\n", "Invalid temperature."), ("A\nx\n32\n", "Invalid amount.")]
        bad_temperature = ["", "-100.1", "300.1", "nan", "inf", "1e9999", "32x", "32 1", "hello"]
        bad_amount = ["", "-0.1", "1000000.1", "nan", "inf", "1e9999", "1x", "1 2", "hello"]
        cases += [(f"A\nx\n{value}\n1\n", "Invalid temperature.") for value in bad_temperature]
        cases += [(f"A\nx\n32\n{value}\n", "Invalid amount.") for value in bad_amount]
        for text, error in cases:
            out = self.run_reference("CPPF1-Chat-Bot", text, 1, error + "\n")
            self.assertNotIn("Hello,", out)
            self.assertNotIn("Celsius:", out)

    def test_number_games_range_and_batch_fixtures(self):
        for first, last, batch1, batch2 in [
            (1, 3, [2, -1, 5], [4, 6]), (5, 2, [], []),
            (-2, -2, [-5], [5]), (-3, 3, [1, 2], [-1, -2]),
        ]:
            values = [first, last, len(batch1), *batch1, len(batch2), *batch2]
            out = self.run_reference("CPPF2-Number-Games", " ".join(map(str, values)))
            sequence = list(range(first, last + 1))
            for label in ["for", "while"]:
                shown = " ".join(map(str, sequence)) if sequence else "empty"
                self.assertIn(f"Range ({label}): {shown}\n", out)
                self.assertIn(f"Range sum ({label}): {sum(sequence)}\n", out)
            for label, batch in [("for", batch1), ("while", batch2)]:
                mean = f"{sum(batch) / len(batch):.2f}" if batch else "undefined"
                self.assertIn(f"Sum ({label}): {sum(batch)}\nAverage ({label}): {mean}\n", out)

    def test_number_games_bounds_and_wide_accumulation(self):
        values = [-1000, 1000, 100, *([1000000] * 100), 100, *([-1000000] * 100)]
        out = self.run_reference("CPPF2-Number-Games", "\r\n".join(map(str, values)))
        self.assertIn("Range sum (for): 0\n", out)
        self.assertIn("Range sum (while): 0\n", out)
        self.assertIn("Sum (for): 100000000\nAverage (for): 1000000.00\n", out)
        self.assertIn("Sum (while): -100000000\nAverage (while): -1000000.00\n", out)

    def test_number_games_rejection_phase_boundaries(self):
        cases = [("", "Invalid integer input.", "Range (for)"),
                 ("1", "Invalid integer input.", "Range (for)"),
                 ("-1001 1", "Invalid range.", "Range (for)"),
                 ("1 1001", "Invalid range.", "Range (for)"),
                 ("1 3 -1", "Invalid count.", "Sum (for)"),
                 ("1 3 101", "Invalid count.", "Sum (for)"),
                 ("1 3 1 1000001", "Invalid value.", "Sum (for)"),
                 ("1 3 1 -1000001", "Invalid value.", "Sum (for)"),
                 ("1 3 0 -1", "Invalid count.", "Sum (while)"),
                 ("1 3 0 101", "Invalid count.", "Sum (while)"),
                 ("1 3 0 1 1000001", "Invalid value.", "Sum (while)"),
                 ("1 3 0 1 -1000001", "Invalid value.", "Sum (while)")]
        for bad in ["2x", "2.5", "9999999999999999999999", "x" * 65, ""]:
            cases += [(bad + " 3", "Invalid integer input.", "Range (for)"),
                      ("1 3 " + bad, "Invalid integer input.", "Sum (for)"),
                      ("1 3 1 " + bad, "Invalid integer input.", "Sum (for)"),
                      ("1 3 0 1 " + bad, "Invalid integer input.", "Sum (while)")]
        for text, error, failed_result in cases:
            out = self.run_reference("CPPF2-Number-Games", text, 1, error + "\n")
            self.assertNotIn(failed_result + ":", out)

    def test_rock_paper_scissors_all_pairs_and_rejections(self):
        beats = {("rock", "scissors"), ("scissors", "paper"), ("paper", "rock")}
        for first, second in itertools.product(["rock", "paper", "scissors"], repeat=2):
            expected = "Tie!" if first == second else "Player 1 wins!" if (first, second) in beats else "Player 2 wins!"
            out = self.run_reference("CPPF2-Rock-Paper-Scissors", first + "\r\n" + second)
            self.assertTrue(out.endswith("\n" + expected + "\n"), out)
        for first, second in [("Rock", "paper"), ("rock", "Paper"), ("x", "y"), ("rock", "x"), ("x", "rock")]:
            out = self.run_reference("CPPF2-Rock-Paper-Scissors", first + " " + second, 1, "Invalid choice.\n")
            self.assertNotIn("wins!", out)
            self.assertNotIn("Tie!", out)
        for text in ["", "rock", "rock \n"]:
            self.run_reference("CPPF2-Rock-Paper-Scissors", text, 1, "Input incomplete.\n")

    def test_fizz_buzz_all_fifty_outputs(self):
        expected = [str(number) for number in range(1, 51)]
        for multiple in range(3, 51, 3): expected[multiple - 1] = "Fizz"
        for multiple in range(5, 51, 5): expected[multiple - 1] = "Buzz"
        for multiple in range(15, 51, 15): expected[multiple - 1] = "FizzBuzz"
        self.assertEqual(self.run_reference("CPPF2-Fizz-Buzz"), "\n".join(expected) + "\n")

    def test_legacy_direct_entries_forward_to_safe_references(self):
        inputs = {"CPPF1-Mad-Libs": "fox curious jump brave", "CPPF1-Chat-Bot": "A\nx\n32\n1\n",
                  "CPPF2-Number-Games": "1 3 0 0", "CPPF2-Rock-Paper-Scissors": "rock paper", "CPPF2-Fizz-Buzz": ""}
        for folder, text in inputs.items():
            code, out, err = execute([str(self.binaries[folder])], text=text, timeout=5)
            self.assertEqual(code, 0, err)
            self.assertEqual(err, "")
            self.assertEqual(out, self.run_reference(folder, text))

    def test_sanitized_references_normal_and_rejected_runs(self):
        if not self.sanitized:
            self.skipTest("SOURCE_SANITIZERS=0 explicitly disables instrumentation")
        inputs = {"CPPF1-Mad-Libs": ["fox curious jump brave", ""],
                  "CPPF1-Chat-Bot": ["A\nx\n32\n1\n", "A\nx\n32x\n1\n"],
                  "CPPF2-Number-Games": ["1 3 0 0", "1 3 1 2x"],
                  "CPPF2-Rock-Paper-Scissors": ["rock paper", "x y"], "CPPF2-Fizz-Buzz": [""]}
        for folder, texts in inputs.items():
            for index, text in enumerate(texts):
                code, out, err = execute([str(self.sanitized[folder])], text=text, timeout=5)
                self.assertEqual(code, 0 if index == 0 else 1, out + err)
                self.assertNotIn("AddressSanitizer", err)
                self.assertNotIn("runtime error:", err)


if __name__ == "__main__":
    unittest.main()

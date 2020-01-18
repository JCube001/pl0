#include "Parser.hpp"
#include <benchmark/benchmark.h>
#include <iostream>
#include <string>

namespace {

const std::string text{
    "VAR x, y, z, q, r, n, f;\n"
    "\n"
    "PROCEDURE multiply;\n"
    "VAR a, b;\n"
    "BEGIN\n"
    "  a := x;\n"
    "  b := y;\n"
    "  z := 0;\n"
    "  WHILE b > 0 DO\n"
    "  BEGIN\n"
    "    IF ODD b THEN z := z + a;\n"
    "    a := 2 * a;\n"
    "    b := b / 2\n"
    "  END\n"
    "END;\n"
    "\n"
    "PROCEDURE divide;\n"
    "VAR w;\n"
    "BEGIN\n"
    "  r := x;\n"
    "  q := 0;\n"
    "  w := y;\n"
    "  WHILE w <= r DO w := 2 * w;\n"
    "  WHILE w > y DO\n"
    "  BEGIN\n"
    "    q := 2 * q;\n"
    "    w := w / 2;\n"
    "    IF w <= r THEN\n"
    "    BEGIN\n"
    "      r := r - w;\n"
    "      q := q + 1\n"
    "    END\n"
    "  END\n"
    "END;\n"
    "\n"
    "PROCEDURE gcd;\n"
    "VAR f, g;\n"
    "BEGIN\n"
    "  f := x;\n"
    "  g := y;\n"
    "  WHILE f # g DO\n"
    "  BEGIN\n"
    "    IF f < g THEN g := g - f;\n"
    "    IF g < f THEN f := f - g\n"
    "  END;\n"
    "  z := f\n"
    "END;\n"
    "\n"
    "PROCEDURE fact;\n"
    "BEGIN\n"
    "  IF n > 1 THEN\n"
    "  BEGIN\n"
    "    f := n * f;\n"
    "    n := n - 1;\n"
    "    CALL fact\n"
    "  END\n"
    "END;\n"
    "\n"
    "BEGIN\n"
    "  ?x; ?y; CALL multiply; !z;\n"
    "  ?x; ?y; CALL divide; !q; !r;\n"
    "  ?x; ?y; CALL gcd; !z;\n"
    "  ?n; f := 1; CALL fact; !f\n"
    "END.\n"
};

void BM_ParseValidProgram(benchmark::State& state)
{
    std::unique_ptr<PL0::Ast::Program> program;
    for (auto _ : state) {
        benchmark::DoNotOptimize(program = PL0::Parser{text, std::cerr}());
    }
}
BENCHMARK(BM_ParseValidProgram);

} // namespace

BENCHMARK_MAIN();

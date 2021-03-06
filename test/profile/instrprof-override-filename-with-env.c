// RUN: %clang_profgen -o %t -O3 %s
// RUN: env LLVM_PROFILE_FILE=%t.good.profraw %run %t %t.bad.profraw
// RUN: llvm-profdata merge -o %t.profdata %t.good.profraw
// RUN: %clang_profuse=%t.profdata -o - -S -emit-llvm %s | FileCheck %s

void __llvm_profile_override_default_filename(const char *);
int main(int argc, const char *argv[]) {
  // CHECK: br i1 %{{.*}}, label %{{.*}}, label %{{.*}}, !prof ![[PD1:[0-9]+]]
  if (argc < 2)
    return 1;
  __llvm_profile_override_default_filename(argv[1]);
  return 0;
}
// CHECK: ![[PD1]] = !{!"branch_weights", i32 1, i32 2}

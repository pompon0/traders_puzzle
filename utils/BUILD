package(default_visibility = ["//visibility:public"])

cc_library(
    name = "utils",
    hdrs = [
        "bazel.h",
        "ctx.h",
        "enum_flag.h",
        "log.h",
        "number_theory.h",
        "read_file.h",
        "short.h",
        "string.h",
        "sys.h",
        "types.h",
    ],
    srcs = ["log.cc"],
    deps = [
        "@abseil//absl/strings:strings",
        "@abseil//absl/time:time",
        "@abseil//absl/types:optional",
        "@com_google_protobuf//:protobuf",
    ],
)

cc_test(
    name = "number_theory_test",
    srcs = ["number_theory_test.cc"],
    deps = [
        ":utils",
        "@gtest//:gtest_main",
    ],
)

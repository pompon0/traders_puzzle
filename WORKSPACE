load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")

################################
# BAZEL

# "com_google_protobuf" declares some terribly old version of skylib,
# forcing the newest version beforehead
http_archive(
    name = "bazel_skylib",
    sha256 = "e5d90f0ec952883d56747b7604e2a15ee36e288bb556c3d0ed33e818a4d971f2",
    strip_prefix = "bazel-skylib-1.0.2",
    urls = ["https://github.com/bazelbuild/bazel-skylib/archive/1.0.2.tar.gz"],
)

###############################
# LLVM

http_archive(
    # cannot change this name, because files in its workspace refer to it
    name = "com_grail_bazel_toolchain",
    strip_prefix = "bazel-toolchain-e608913c0e106da931234fdd37de9ee37e0b2541",
    urls = ["https://github.com/pompon0/bazel-toolchain/archive/e608913c0e106da931234fdd37de9ee37e0b2541.tar.gz"],
    sha256 = "e09e8ef8a5f97078da2961561e176a5bf461962683159bcbd81674052475cdd0",
)

load("@com_grail_bazel_toolchain//toolchain:deps.bzl", "bazel_toolchain_dependencies")

bazel_toolchain_dependencies()

load("@com_grail_bazel_toolchain//toolchain:rules.bzl", "llvm_toolchain")

llvm_toolchain(
    name = "llvm_toolchain",
    distribution = "clang+llvm-10.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz",
    llvm_version = "10.0.0",
)

load("@llvm_toolchain//:toolchains.bzl", "llvm_register_toolchains")

llvm_register_toolchains()

################################
# C++

http_archive(
    name = "gtest",
    strip_prefix = "googletest-release-1.8.1",
    urls = ["https://github.com/google/googletest/archive/release-1.8.1.zip"],
    sha256 = "927827c183d01734cc5cfef85e0ff3f5a92ffe6188e0d18e909c5efebf28a0c7",
)

http_archive(
    name = "abseil",
    strip_prefix = "abseil-cpp-d659fe54b35ab9b8e35c72e50a4b8814167d5a84",
    urls = ["https://github.com/abseil/abseil-cpp/archive/d659fe54b35ab9b8e35c72e50a4b8814167d5a84.zip"],
    sha256 = "743f879030960c80a0445310567ca99d8eae87468dd0e78fd0c8bfd46f429e37",
)

################################
# PROTO

http_archive(
    name = "rules_proto",
    # sha256 = "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
    sha256 = "9fc210a34f0f9e7cc31598d109b5d069ef44911a82f507d5a88716db171615a8",
    strip_prefix = "rules_proto-f7a30f6f80006b591fa7c437fe5a951eb10bcbcf",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/f7a30f6f80006b591fa7c437fe5a951eb10bcbcf.tar.gz",
        "https://github.com/bazelbuild/rules_proto/archive/f7a30f6f80006b591fa7c437fe5a951eb10bcbcf.tar.gz",
    ],
)

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()



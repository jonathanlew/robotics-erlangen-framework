load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

# Developer tools for working with bazel
git_repository(
    name = "bazel_buildtools",
    commit = "41a45edb9184de83dd29e2791bd995fbb73ea141",
    remote = "git@github.com:bazelbuild/buildtools.git",
)

# Needed for bazel buildifier: it is written in Go and hence needs rules_go to
# be built.
http_archive(
    name = "io_bazel_rules_go",
    sha256 = "b27e55d2dcc9e6020e17614ae6e0374818a3e3ce6f2024036e688ada24110444",
    urls = [
        "https://storage.googleapis.com/bazel-mirror/github.com/bazelbuild/rules_go/releases/download/v0.21.0/rules_go-v0.21.0.tar.gz",
        "https://github.com/bazelbuild/rules_go/releases/download/v0.21.0/rules_go-v0.21.0.tar.gz",
    ],
)

load("@io_bazel_rules_go//go:deps.bzl", "go_register_toolchains", "go_rules_dependencies")

go_rules_dependencies()

go_register_toolchains()

# Needed for bazel buildifier
http_archive(
    name = "bazel_gazelle",
    sha256 = "be9296bfd64882e3c08e3283c58fcb461fa6dd3c171764fcc4cf322f60615a9b",
    urls = [
        "https://storage.googleapis.com/bazel-mirror/github.com/bazelbuild/bazel-gazelle/releases/download/0.18.1/bazel-gazelle-0.18.1.tar.gz",
        "https://github.com/bazelbuild/bazel-gazelle/releases/download/0.18.1/bazel-gazelle-0.18.1.tar.gz",
    ],
)

load("@bazel_gazelle//:deps.bzl", "gazelle_dependencies")

gazelle_dependencies()

# Bazel buildtools, provide us with the bazel formatter ("buildifier")
http_archive(
    name = "com_github_bazelbuild_buildtools",
    sha256 = "46ead728d66d48969f8ae3b88f2fd10fddfc80dd7903fb8b5bff9c568f0ebf25",
    strip_prefix = "buildtools-9e63c6f02e63adaab63e21a3a8feb75f4f7503cb",
    url = "https://github.com/bazelbuild/buildtools/archive/9e63c6f02e63adaab63e21a3a8feb75f4f7503cb.zip",
)

# Qt bazel rules from https://github.com/justbuchanan/bazel_rules_qt
git_repository(
    name = "bazel_rules_qt",
    commit = "7665177f47bf514176d5f8575a7334f030203e3d",
    remote = "https://github.com/justbuchanan/bazel_rules_qt.git",
)

# Right now qt5 is installed on the system using the setup_software.sh script
# We assume we can find the headers in the "standard" path used in this rule
new_local_repository(
    name = "qt",
    build_file = "@bazel_rules_qt//:qt.BUILD",
    path = "/usr/include/x86_64-linux-gnu/qt5/",
)

http_archive(
    name = "rules_proto",
    sha256 = "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
    strip_prefix = "rules_proto-97d8af4dc474595af3900dd85cb3a29ad28cc313",
    url = "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
)

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

maybe(
    git_repository,
    name = "rules_third_party",
    commit = "8d0ba00f9874588c1ea38d1be2859060ac8c8516",
    remote = "https://github.com/DraconicEnt/rules_third_party.git",
)

load("@rules_third_party//libraries:bullet.bzl", "bullet")

bullet()

http_archive(
    name = "rules_foreign_cc",
    sha256 = "33a5690733c5cc2ede39cb62ebf89e751f2448e27f20c8b2fbbc7d136b166804",
    strip_prefix = "rules_foreign_cc-0.5.1",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/0.5.1.tar.gz",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

# This sets up some common toolchains for building targets. For more details, please see
# https://bazelbuild.github.io/rules_foreign_cc/0.5.1/flatten.html#rules_foreign_cc_dependencies
rules_foreign_cc_dependencies()
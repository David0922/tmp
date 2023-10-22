load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# protobuf

git_repository(
    name = "rules_proto",
    remote = "https://github.com/bazelbuild/rules_proto",
    tag = "5.3.0-21.7",
)

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

# grpc

git_repository(
    name = "com_github_grpc_grpc",
    remote = "https://github.com/grpc/grpc",
    # v1.59.1: 'absl/status/status.h' file not found
    # https://github.com/grpc/grpc/issues/33622
    tag = "v1.54.3",
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()

load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
    name = "calc_proto",
    srcs = ["calculator.proto"],
    visibility = ["//visibility:public"],
)

cc_proto_library(
    name = "calc_cc_proto",
    visibility = ["//visibility:public"],
    deps = [":calc_proto"],
)

cc_grpc_library(
    name = "calc_cc_grpc",
    srcs = [":calc_proto"],
    grpc_only = True,
    visibility = ["//visibility:public"],
    deps = [":calc_cc_proto"],
)

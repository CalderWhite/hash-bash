cc_library(
    name = "PTree",
    srcs = ["PTree.cpp"],
    hdrs = [
        "PTree.h",
        "PTreeException.h",
    ],
)

cc_test(
    name = "PTreeTests",
    srcs = ["Ptree.test.cpp"],
    deps = [
        "@gtest//:main",
        ":PTree",
    ]
)

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":PTree",
    ],
)

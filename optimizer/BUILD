cc_library(
    name = "PTree",
    srcs = ["PTree.cpp"],
    copts = ["-Iexternal/gtest/include"],
    hdrs = [
        "PTree.h",
        "PTreeException.h",
    ],
    deps = [
        "@gtest//:main",
    ]
)

cc_test(
    name = "PTreeTests",
    srcs = ["PTree.test.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        ":PTree",
    ]
)

cc_test(
    name = "newtest",
    srcs = ["newtest.test.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        ":PTree",
    ]
)


cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":PTree",
        "@gtest//:main",
    ],
)

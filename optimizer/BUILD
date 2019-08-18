# ============= BigTree =============
cc_library(
    name = "BigTree",
    hdrs = [
        "BigTree.h",
        "BigTreeException.h",
    ],
    deps = [
        ":utils",
    ]
)

# ============= PTree =============
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
        ":utils",
        ":BigTree",
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

# ============= utils =============
cc_library(
    name = "utils",
    srcs = ["utils.cpp"],
    hdrs = ["utils.h"],
)

cc_test(
    name = "UtilsTests",
    srcs = ["utils.test.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@gtest//:main",
        ":utils",
    ]
)

# ============= Predictor =============
cc_library(
    name = "Predictor",
    srcs = ["Predictor.cpp"],
    hdrs = ["Predictor.h"],
    deps = [
        ":BigTree",
        ":PTree",
        "@boost//:serialization",
        "@boost//:iostreams",
    ]
)

# ============= main =============
cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":BigTree",
        ":Predictor",
        ":PTree",
        "@boost//:serialization",
        "@boost//:iostreams",
    ],
)
